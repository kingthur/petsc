/*$Id: sortd.c,v 1.29 2001/08/07 21:29:06 bsmith Exp $*/
/*
   This file contains routines for sorting doubles.  Values are sorted in place.
   These are provided because the general sort routines incur a great deal
   of overhead in calling the comparision routines.

   The word "register"  in this code is used to identify data that is not
   aliased.  For some compilers, this can cause the compiler to fail to
   place inner-loop variables into registers.
 */
#include "petscconfig.h"
#include "petsc.h"                /*I  "petsc.h"  I*/
#include "petscsys.h"             /*I  "petscsys.h"    I*/

#define SWAP(a,b,t) {t=a;a=b;b=t;}
   
#undef __FUNCT__  
#define __FUNCT__ "PetsciDqsort"
/* A simple version of quicksort; taken from Kernighan and Ritchie, page 87 */
static int PetsciDqsort(PetscReal *v,int right)
{
  int       i,last;
  PetscReal vl,tmp;
  
  PetscFunctionBegin;
  if (right <= 1) {
    if (right == 1) {
      if (v[0] > v[1]) SWAP(v[0],v[1],tmp);
    }
    PetscFunctionReturn(0);
  }
  SWAP(v[0],v[right/2],tmp);
  vl   = v[0];
  last = 0;
  for (i=1; i<=right; i++) {
    if (v[i] < vl) {last++; SWAP(v[last],v[i],tmp);}
  }
  SWAP(v[0],v[last],tmp);
  PetsciDqsort(v,last-1);
  PetsciDqsort(v+last+1,right-(last+1));
  PetscFunctionReturn(0);
}

#undef __FUNCT__  
#define __FUNCT__ "PetscSortReal"
/*@
   PetscSortReal - Sorts an array of doubles in place in increasing order.

   Not Collective

   Input Parameters:
+  n  - number of values
-  v  - array of doubles

   Level: intermediate

   Concepts: sorting^doubles

.seealso: PetscSortInt(), PetscSortRealWithPermutation()
@*/
int PetscSortReal(int n,PetscReal v[])
{
  int       j,k;
  PetscReal tmp,vk;

  PetscFunctionBegin;
  if (n<8) {
    for (k=0; k<n; k++) {
      vk = v[k];
      for (j=k+1; j<n; j++) {
	if (vk > v[j]) {
	  SWAP(v[k],v[j],tmp);
	  vk = v[k];
	}
      }
    }
  } else {
    PetsciDqsort(v,n-1);
  }
  PetscFunctionReturn(0);
}

