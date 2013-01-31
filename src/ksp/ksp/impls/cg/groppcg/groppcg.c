/*
 author: Pieter Ghysels, Universiteit Antwerpen, Intel Exascience lab Flanders

 This file implements a CG method due to B. Gropp that can overlap one reduction
 with application of the preconditioner and the other reduction can be
 overlapped with the matrix-vector product.

 see:
 http://www.cs.uiuc.edu/~wgropp/bib/talks/tdata/2012/icerm.pdf
 */

#include <petsc-private/kspimpl.h>

/*
 KSPSetUp_GROPPCG - Sets up the workspace needed by the GROPPCG method.

 This is called once, usually automatically by KSPSolve() or KSPSetUp()
 but can be called directly by KSPSetUp()
*/
#undef __FUNCT__
#define __FUNCT__ "KSPSetUp_GROPPCG"
PetscErrorCode KSPSetUp_GROPPCG(KSP ksp)
{
  PetscErrorCode ierr;

  PetscFunctionBegin;
  ierr = KSPDefaultGetWork(ksp,6);CHKERRQ(ierr);
  PetscFunctionReturn(0);
}

/*
 KSPSolve_GROPPCG

 Input Parameter:
 .     ksp - the Krylov space object that was set to use conjugate gradient, by, for
             example, KSPCreate(MPI_Comm,KSP *ksp); KSPSetType(ksp,KSPCG);
*/
#undef __FUNCT__
#define __FUNCT__ "KSPSolve_GROPPCG"
PetscErrorCode  KSPSolve_GROPPCG(KSP ksp)
{
  PetscErrorCode ierr;
  PetscInt       i;
  PetscScalar    alpha,beta = 0.0,gamma,gammaNew,t;
  PetscReal      dp = 0.0;
  Vec            x,b,r,p,s,S,z,Z;
  Mat            Amat,Pmat;
  MatStructure   pflag;
  PetscBool      diagonalscale;

  PetscFunctionBegin;
  ierr = PCGetDiagonalScale(ksp->pc,&diagonalscale);CHKERRQ(ierr);
  if (diagonalscale) SETERRQ1(((PetscObject)ksp)->comm,PETSC_ERR_SUP,"Krylov method %s does not support diagonal scaling",((PetscObject)ksp)->type_name);

  x = ksp->vec_sol;
  b = ksp->vec_rhs;
  r = ksp->work[0];
  p = ksp->work[1];
  s = ksp->work[2];
  S = ksp->work[3];
  z = ksp->work[4];
  Z = ksp->work[5];

  ierr = PCGetOperators(ksp->pc,&Amat,&Pmat,&pflag);CHKERRQ(ierr);

  ksp->its = 0;
  if (!ksp->guess_zero) {
    ierr = KSP_MatMult(ksp,Amat,x,r);CHKERRQ(ierr);            /*     r <- b - Ax     */
    ierr = VecAYPX(r,-1.0,b);CHKERRQ(ierr);
  } else {
    ierr = VecCopy(b,r);CHKERRQ(ierr);                         /*     r <- b (x is 0) */
  }

  ierr = KSP_PCApply(ksp,r,z);CHKERRQ(ierr);                   /*     z <- Br   */
  ierr = VecCopy(z,p);CHKERRQ(ierr);                           /*     p <- z    */
  ierr = VecDotBegin(r,z,&gamma);CHKERRQ(ierr);                  /*     gamma <- z'*r       */
  ierr = PetscCommSplitReductionBegin(((PetscObject)r)->comm);CHKERRQ(ierr);
  ierr = KSP_MatMult(ksp,Amat,p,s);CHKERRQ(ierr);              /*     s <- Ap   */
  ierr = VecDotEnd(r,z,&gamma);CHKERRQ(ierr);                  /*     gamma <- z'*r       */

  switch (ksp->normtype) {
  case KSP_NORM_PRECONDITIONED:
    /* This could be merged with the computation of gamma above */
    ierr = VecNorm(z,NORM_2,&dp);CHKERRQ(ierr);                /*     dp <- z'*z = e'*A'*B'*B*A'*e'     */
    break;
  case KSP_NORM_UNPRECONDITIONED:
    /* This could be merged with the computation of gamma above */
    ierr = VecNorm(r,NORM_2,&dp);CHKERRQ(ierr);                /*     dp <- r'*r = e'*A'*A*e            */
    break;
  case KSP_NORM_NATURAL:
    if (PetscIsInfOrNanScalar(gamma)) SETERRQ(((PetscObject)ksp)->comm,PETSC_ERR_FP,"Infinite or not-a-number generated in dot product");
    dp = PetscSqrtReal(PetscAbsScalar(gamma));                  /*     dp <- r'*z = r'*B*r = e'*A'*B*A*e */
    break;
  case KSP_NORM_NONE:
    dp = 0.0;
    break;
  default: SETERRQ1(((PetscObject)ksp)->comm,PETSC_ERR_SUP,"%s",KSPNormTypes[ksp->normtype]);
  }
  KSPLogResidualHistory(ksp,dp);
  ierr       = KSPMonitor(ksp,0,dp);CHKERRQ(ierr);
  ksp->rnorm = dp;
  ierr       = (*ksp->converged)(ksp,0,dp,&ksp->reason,ksp->cnvP);CHKERRQ(ierr); /* test for convergence */
  if (ksp->reason) PetscFunctionReturn(0);

  i = 0;
  do {
    ksp->its = i+1;
    i++;

    ierr = VecDotBegin(p,s,&t);CHKERRQ(ierr);
    ierr = PetscCommSplitReductionBegin(((PetscObject)p)->comm);CHKERRQ(ierr);

    ierr = KSP_PCApply(ksp,s,S);CHKERRQ(ierr);         /*   S <- Bs       */

    ierr = VecDotEnd(p,s,&t);CHKERRQ(ierr);

    alpha = gamma / t;
    ierr  = VecAXPY(x, alpha,p);CHKERRQ(ierr);   /*     x <- x + alpha * p   */
    ierr  = VecAXPY(r,-alpha,s);CHKERRQ(ierr);   /*     r <- r - alpha * s   */
    ierr  = VecAXPY(z,-alpha,S);CHKERRQ(ierr);   /*     z <- z - alpha * S   */

    if (ksp->normtype == KSP_NORM_UNPRECONDITIONED) {
      ierr = VecNormBegin(r,NORM_2,&dp);CHKERRQ(ierr);
    } else if (ksp->normtype == KSP_NORM_PRECONDITIONED) {
      ierr = VecNormBegin(z,NORM_2,&dp);CHKERRQ(ierr);
    }
    ierr = VecDotBegin(r,z,&gammaNew);CHKERRQ(ierr);
    ierr = PetscCommSplitReductionBegin(((PetscObject)r)->comm);CHKERRQ(ierr);

    ierr = KSP_MatMult(ksp,Amat,z,Z);CHKERRQ(ierr);      /*   Z <- Az       */

    if (ksp->normtype == KSP_NORM_UNPRECONDITIONED) {
      ierr = VecNormEnd(r,NORM_2,&dp);CHKERRQ(ierr);
    } else if (ksp->normtype == KSP_NORM_PRECONDITIONED) {
      ierr = VecNormEnd(z,NORM_2,&dp);CHKERRQ(ierr);
    }
    ierr = VecDotEnd(r,z,&gammaNew);CHKERRQ(ierr);

    if (ksp->normtype == KSP_NORM_NATURAL) {
      if (PetscIsInfOrNanScalar(gammaNew)) SETERRQ(((PetscObject)ksp)->comm,PETSC_ERR_FP,"Infinite or not-a-number generated in dot product");
      dp = PetscSqrtReal(PetscAbsScalar(gammaNew));                  /*     dp <- r'*z = r'*B*r = e'*A'*B*A*e */
    } else if (ksp->normtype == KSP_NORM_NONE) {
      dp = 0.0;
    }
    ksp->rnorm = dp;
    KSPLogResidualHistory(ksp,dp);
    ierr = KSPMonitor(ksp,i,dp);CHKERRQ(ierr);
    ierr = (*ksp->converged)(ksp,i,dp,&ksp->reason,ksp->cnvP);CHKERRQ(ierr);
    if (ksp->reason) break;

    beta  = gammaNew / gamma;
    gamma = gammaNew;
    ierr  = VecAYPX(p,beta,z);CHKERRQ(ierr);   /*     p <- z + beta * p   */
    ierr  = VecAYPX(s,beta,Z);CHKERRQ(ierr);   /*     s <- Z + beta * s   */

  } while (i<ksp->max_it);

  if (i >= ksp->max_it) ksp->reason = KSP_DIVERGED_ITS;
  PetscFunctionReturn(0);
}

#undef __FUNCT__
#define __FUNCT__ "KSPCreate_GROPPCG"
PETSC_EXTERN_C PetscErrorCode KSPCreate_GROPPCG(KSP ksp)
{
  PetscErrorCode ierr;

  PetscFunctionBegin;
  ierr = KSPSetSupportedNorm(ksp,KSP_NORM_UNPRECONDITIONED,PC_LEFT,1);CHKERRQ(ierr);
  ierr = KSPSetSupportedNorm(ksp,KSP_NORM_PRECONDITIONED,PC_LEFT,1);CHKERRQ(ierr);
  ierr = KSPSetSupportedNorm(ksp,KSP_NORM_NATURAL,PC_LEFT,1);CHKERRQ(ierr);
  ierr = KSPSetSupportedNorm(ksp,KSP_NORM_NONE,PC_LEFT,1);CHKERRQ(ierr);

  ksp->ops->setup          = KSPSetUp_GROPPCG;
  ksp->ops->solve          = KSPSolve_GROPPCG;
  ksp->ops->destroy        = KSPDefaultDestroy;
  ksp->ops->view           = 0;
  ksp->ops->setfromoptions = 0;
  ksp->ops->buildsolution  = KSPDefaultBuildSolution;
  ksp->ops->buildresidual  = KSPDefaultBuildResidual;
  PetscFunctionReturn(0);
}
