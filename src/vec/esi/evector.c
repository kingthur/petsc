



/*
      Interfaces the ESI_VEctor class to the PETSc
    Map object class.
*/

#include "petsc/vector.h"

esi::petsc::Vector<double,int>::Vector( esi::MapPartition<int> *inmap)
{
  esi::ErrorCode  ierr;
  int             n,N;
  MPI_Comm        *comm;

  ierr = inmap->getRunTimeModel("MPI",static_cast<void *>(comm));

  ierr = inmap->getLocalSize(n);
  ierr = inmap->getGlobalSize(N);
  ierr = VecCreateMPI(*comm,n,N,&this->vec);
  this->pobject = (PetscObject)this->vec;
  this->map = (esi::MapPartition<int> *)inmap;
  PetscObjectGetComm((PetscObject)this->vec,&this->comm);
}

esi::petsc::Vector<double,int>::Vector( Vec pvec)
{
  esi::ErrorCode  ierr;
  int             n,N;
  
  this->vec     = pvec;
  this->pobject = (PetscObject)this->vec;
  PetscObjectGetComm((PetscObject)this->vec,&this->comm);

  ierr =  VecGetSize(pvec,&N);
  ierr = VecGetLocalSize(pvec,&n);
  this->map = (esi::MapPartition<int> *)(new esi::petsc::Map<int>(this->comm,n,N));
}


esi::petsc::Vector<double,int>::~Vector()
{
  int ierr;
  ierr = VecDestroy(this->vec);
}


/* ---------------esi::Object methods ------------------------------------------------------------ */

esi::ErrorCode esi::petsc::Vector<double,int>::getInterface(const char* name, void *& iface)
{
  PetscTruth flg;
  if (PetscStrcmp(name,"esi::Object",&flg),flg){
    iface = (void *) (esi::Object *) this;
  } else if (PetscStrcmp(name,"esi::Vector",&flg),flg){
    iface = (void *) (esi::Vector<double,int> *) this;
  } else if (PetscStrcmp(name,"esi::petsc::Vector",&flg),flg){
    iface = (void *) (esi::petsc::Vector<double,int> *) this;
  } else {
    iface = 0;
  }
  return 0;
}


esi::ErrorCode esi::petsc::Vector<double,int>::getInterfacesSupported(esi::Argv * list)
{
  list->appendArg("esi::Object");
  list->appendArg("esi::Vector");
  list->appendArg("esi::petsc::Vector");
  return 0;
}

/*
    Note: this returns the map used in creating the vector;
  it is not the same as the PETSc map contained inside the PETSc vector
*/
esi::ErrorCode esi::petsc::Vector<double,int>::getMapPartition( esi::MapPartition<int>*& outmap)
{
  outmap = this->map;
  return 0;
}

esi::ErrorCode esi::petsc::Vector<double,int>::getGlobalSize( int & dim) 
{
  return VecGetSize(this->vec,&dim);
}


esi::ErrorCode esi::petsc::Vector<double,int>::clone( esi::Vector<double,int>*& outvector)  
{
  int ierr;
  esi::MapPartition<int> *lmap; 
  esi::MapPartition<int> *amap; 

  ierr = this->getMapPartition(lmap);CHKERRQ(ierr);
  ierr = lmap->getInterface("esi::MapPartition",static_cast<void *>(amap));CHKERRQ(ierr);
  outvector = (esi::Vector<double,int> *) new esi::petsc::Vector<double,int>(amap);
  return 0;
}

/*
  Currently only works if both vectors are PETSc 
*/
esi::ErrorCode esi::petsc::Vector<double,int>::copy( esi::Vector<double,int> &yy)
{
  esi::petsc::Vector<double,int> *y = 0;  
  int ierr;

  ierr = yy.getInterface("esi::petsc::Vector",static_cast<void*>(y));CHKERRQ(ierr);
  if (!y) return 1;

  return VecCopy(this->vec,y->vec);
}

esi::ErrorCode esi::petsc::Vector<double,int>::put( double scalar)
{
  return VecSet(&scalar,this->vec);
}

esi::ErrorCode esi::petsc::Vector<double,int>::scale( double scalar)
{
  return VecScale(&scalar,this->vec);
}

/*
  Currently only works if both vectors are PETSc 
*/
esi::ErrorCode esi::petsc::Vector<double,int>::scaleDiagonal( esi::Vector<double,int> &yy)
{
  esi::ErrorCode                        ierr;
  esi::petsc::Vector<double,int> *y;  
  
  ierr = yy.getInterface("esi::petsc::Vector",static_cast<void*>(y));CHKERRQ(ierr);
  if (!y) return 1;

  return VecPointwiseMult(this->vec,y->vec,this->vec);
}

esi::ErrorCode esi::petsc::Vector<double,int>::norm1(double &scalar) 
{
  return VecNorm(this->vec,NORM_1,&scalar);
}

esi::ErrorCode esi::petsc::Vector<double,int>::norm2(double &scalar) 
{
  return VecNorm(this->vec,NORM_2,&scalar);
}

esi::ErrorCode esi::petsc::Vector<double,int>::norm2squared(double &scalar) 
{
  int ierr = VecNorm(this->vec,NORM_2,&scalar);CHKERRQ(ierr);
  scalar *= scalar;
  return 0;
}

esi::ErrorCode esi::petsc::Vector<double,int>::normInfinity(double &scalar) 
{
  return VecNorm(this->vec,NORM_INFINITY,&scalar);
}

/*
  Currently only works if both vectors are PETSc 
*/
esi::ErrorCode esi::petsc::Vector<double,int>::dot( esi::Vector<double,int> &yy,double &product) 
{
  int ierr;

  esi::petsc::Vector<double,int> *y;  ierr = yy.getInterface("esi::petsc::Vector",static_cast<void*>(y));CHKERRQ(ierr);
  if (!y) return 1;
  return  VecDot(this->vec,y->vec,&product);
}

/*
  Currently only works if both vectors are PETSc 
*/
esi::ErrorCode esi::petsc::Vector<double,int>::axpy(  esi::Vector<double,int> &yy,double scalar)
{
  int ierr;

  esi::petsc::Vector<double,int> *y;  ierr = yy.getInterface("esi::petsc::Vector",static_cast<void*>(y));CHKERRQ(ierr);
  if (!y) return 1;
  return VecAXPY(&scalar,this->vec,y->vec);
}

esi::ErrorCode esi::petsc::Vector<double,int>::axpby(double y1,  esi::Vector<double,int> &yy1,double y2,  esi::Vector<double,int> &yy2)
{
  int ierr;

  esi::petsc::Vector<double,int> *y;  ierr = yy1.getInterface("esi::petsc::Vector",static_cast<void*>(y));CHKERRQ(ierr);
  if (!y) return 1;
  esi::petsc::Vector<double,int> *w;  ierr = yy2.getInterface("esi::petsc::Vector",static_cast<void*>(w));CHKERRQ(ierr);
  if (!w) return 1;
  ierr = VecCopy(this->vec,w->vec); CHKERRQ(ierr);
  ierr = VecScale(&y1,w->vec); CHKERRQ(ierr);
  ierr = VecAXPY(&y2,y->vec,w->vec); CHKERRQ(ierr);
}

/*
  Currently only works if both vectors are PETSc 
*/
esi::ErrorCode esi::petsc::Vector<double,int>::aypx(double scalar,  esi::Vector<double,int> &yy)
{
  int ierr;
  
  esi::petsc::Vector<double,int> *y;  ierr = yy.getInterface("esi::petsc::Vector",static_cast<void*>(y));CHKERRQ(ierr);
  if (!y) return 1;
  return VecAXPY(&scalar,this->vec,y->vec);
}

esi::ErrorCode esi::petsc::Vector<double,int>::getCoefPtrReadLock(double *&pointer) 
{
  int ierr;

  return VecGetArray(this->vec,&pointer);
}

esi::ErrorCode esi::petsc::Vector<double,int>::getCoefPtrReadWriteLock(double *&pointer)
{
  int ierr;

  return VecGetArray(this->vec,&pointer);
}

esi::ErrorCode esi::petsc::Vector<double,int>::releaseCoefPtrLock(double *&pointer)  
{
  int ierr;
  return VecRestoreArray(this->vec,&pointer);
}

esi::ErrorCode esi::petsc::Vector<double,int>::setArrayPointer(double *pointer,int length)
{
  return VecPlaceArray(this->vec,pointer);
}

/*
      Private operation
*/
esi::ErrorCode esi::petsc::Vector<double,int>::getPETScVec(Vec *outvec)
{
  *outvec = this->vec;
  return 0;
}





