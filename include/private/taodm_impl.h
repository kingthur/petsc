#ifndef __TAODM_IMPL_H
#define __TAODM_IMPL_H
#include "petscdm.h"
#include "taodm.h"

struct _TaoDMOps {
  PetscErrorCode (*computeobjectiveandgradientlocal)(DMDALocalInfo*,PetscScalar **, PetscScalar *, PetscScalar **, void*);
  PetscErrorCode (*computeobjectivelocal)(DMDALocalInfo*,PetscScalar**, PetscScalar*, void*);
  PetscErrorCode (*computegradientlocal)(DMDALocalInfo*,PetscScalar**, PetscScalar**, void*);
  PetscErrorCode (*computehessianlocal)(DMDALocalInfo*,PetscScalar**,Mat,void*);
  PetscErrorCode (*computeobjectiveandgradient)(TaoSolver,Vec,PetscScalar*,Vec,void*);
  PetscErrorCode (*computeobjective)(TaoSolver,Vec,PetscScalar*,void*);
  PetscErrorCode (*computegradient)(TaoSolver,Vec,Vec,void*);
  PetscErrorCode (*computehessian)(TaoSolver,Vec,Mat*,Mat*,MatStructure*,void*);
  PetscErrorCode (*computebounds)(TaoDM, Vec, Vec);
  PetscErrorCode (*computeinitialguess)(TaoDM, Vec);
  PetscErrorCode (*levelmonitor)(TaoDM,PetscInt,void*);
};

struct _p_TaoDM {
  PETSCHEADER(struct _TaoDMOps);
  DM             dm;  /* Grid information at this level */
  Vec            x;   /* solution on this level */
  Mat            hessian;   /* Hessian on this level */
  Mat            hessian_pre;  
  Mat            R;   /* Restriction to next coarser level  (not defined for level 0) */
  Vec            Rscale;
  PetscInt       nlevels; /* # of levels above this one (== total levels for level 0) */
  void           *user; /* user context */
  MatType        mtype;
  TaoSolverType  ttype;
  ISColoringType isctype;
  TaoSolver      tao; /* TaoSolver at this level */
  PetscReal fatol;
  PetscReal frtol;
  PetscReal gatol;
  PetscReal grtol;
  PetscReal gttol;
  void *userfctx;
  void *usergctx;
  void *userhctx;
  void *userfgctx;
  void *usermonitor;
};

#endif
