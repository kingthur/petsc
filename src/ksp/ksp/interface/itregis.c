
#include <petsc/private/kspimpl.h>  /*I "petscksp.h" I*/

PETSC_EXTERN PetscErrorCode KSPCreate_Richardson(KSP);
PETSC_EXTERN PetscErrorCode KSPCreate_Chebyshev(KSP);
PETSC_EXTERN PetscErrorCode KSPCreate_CG(KSP);
PETSC_EXTERN PetscErrorCode KSPCreate_GROPPCG(KSP);
PETSC_EXTERN PetscErrorCode KSPCreate_PIPECG(KSP);
PETSC_EXTERN PetscErrorCode KSPCreate_PIPECGRR(KSP);
PETSC_EXTERN PetscErrorCode KSPCreate_CGNE(KSP);
PETSC_EXTERN PetscErrorCode KSPCreate_CGNASH(KSP);
PETSC_EXTERN PetscErrorCode KSPCreate_CGSTCG(KSP);
PETSC_EXTERN PetscErrorCode KSPCreate_CGGLTR(KSP);
PETSC_EXTERN PetscErrorCode KSPCreate_TCQMR(KSP);
PETSC_EXTERN PetscErrorCode KSPCreate_FCG(KSP);
PETSC_EXTERN PetscErrorCode KSPCreate_PIPEFCG(KSP);
PETSC_EXTERN PetscErrorCode KSPCreate_GMRES(KSP);
PETSC_EXTERN PetscErrorCode KSPCreate_BCGS(KSP);
PETSC_EXTERN PetscErrorCode KSPCreate_IBCGS(KSP);
PETSC_EXTERN PetscErrorCode KSPCreate_FBCGS(KSP);
PETSC_EXTERN PetscErrorCode KSPCreate_FBCGSR(KSP);
PETSC_EXTERN PetscErrorCode KSPCreate_BCGSL(KSP);
PETSC_EXTERN PetscErrorCode KSPCreate_CGS(KSP);
PETSC_EXTERN PetscErrorCode KSPCreate_TFQMR(KSP);
PETSC_EXTERN PetscErrorCode KSPCreate_LSQR(KSP);
PETSC_EXTERN PetscErrorCode KSPCreate_PREONLY(KSP);
PETSC_EXTERN PetscErrorCode KSPCreate_CR(KSP);
PETSC_EXTERN PetscErrorCode KSPCreate_PIPECR(KSP);
PETSC_EXTERN PetscErrorCode KSPCreate_QCG(KSP);
PETSC_EXTERN PetscErrorCode KSPCreate_BiCG(KSP);
PETSC_EXTERN PetscErrorCode KSPCreate_FGMRES(KSP);
PETSC_EXTERN PetscErrorCode KSPCreate_PIPEFGMRES(KSP);
PETSC_EXTERN PetscErrorCode KSPCreate_MINRES(KSP);
PETSC_EXTERN PetscErrorCode KSPCreate_SYMMLQ(KSP);
PETSC_EXTERN PetscErrorCode KSPCreate_LGMRES(KSP);
PETSC_EXTERN PetscErrorCode KSPCreate_LCD(KSP);
PETSC_EXTERN PetscErrorCode KSPCreate_GCR(KSP);
PETSC_EXTERN PetscErrorCode KSPCreate_PIPEGCR(KSP);
PETSC_EXTERN PetscErrorCode KSPCreate_PGMRES(KSP);
#if !defined(PETSC_USE_COMPLEX)
PETSC_EXTERN PetscErrorCode KSPCreate_DGMRES(KSP);
#endif
PETSC_EXTERN PetscErrorCode KSPCreate_TSIRM(KSP);
PETSC_EXTERN PetscErrorCode KSPCreate_CGLS(KSP);
PETSC_EXTERN PetscErrorCode KSPCreate_FETIDP(KSP);

/*
    This is used by KSPSetType() to make sure that at least one
    KSPRegisterAll() is called. In general, if there is more than one
    DLL, then KSPRegisterAll() may be called several times.
*/
extern PetscBool KSPRegisterAllCalled;

/*@C
  KSPRegisterAll - Registers all of the Krylov subspace methods in the KSP package.

  Not Collective

  Level: advanced

.keywords: KSP, register, all

.seealso:  KSPRegisterDestroy()
@*/
PetscErrorCode  KSPRegisterAll(void)
{
  PetscErrorCode ierr;

  PetscFunctionBegin;
  if (KSPRegisterAllCalled) PetscFunctionReturn(0);
  KSPRegisterAllCalled = PETSC_TRUE;

  ierr = KSPRegister(KSPCG,          KSPCreate_CG);CHKERRQ(ierr);
  ierr = KSPRegister(KSPGROPPCG,     KSPCreate_GROPPCG);CHKERRQ(ierr);
  ierr = KSPRegister(KSPPIPECG,      KSPCreate_PIPECG);CHKERRQ(ierr);
  ierr = KSPRegister(KSPPIPECGRR,    KSPCreate_PIPECGRR);CHKERRQ(ierr);
  ierr = KSPRegister(KSPCGNE,        KSPCreate_CGNE);CHKERRQ(ierr);
  ierr = KSPRegister(KSPCGNASH,      KSPCreate_CGNASH);CHKERRQ(ierr);
  ierr = KSPRegister(KSPCGSTCG,      KSPCreate_CGSTCG);CHKERRQ(ierr);
  ierr = KSPRegister(KSPCGGLTR,      KSPCreate_CGGLTR);CHKERRQ(ierr);
  ierr = KSPRegister(KSPRICHARDSON,  KSPCreate_Richardson);CHKERRQ(ierr);
  ierr = KSPRegister(KSPCHEBYSHEV,   KSPCreate_Chebyshev);CHKERRQ(ierr);
  ierr = KSPRegister(KSPGMRES,       KSPCreate_GMRES);CHKERRQ(ierr);
  ierr = KSPRegister(KSPTCQMR,       KSPCreate_TCQMR);CHKERRQ(ierr);
  ierr = KSPRegister(KSPFCG  ,       KSPCreate_FCG);CHKERRQ(ierr);
  ierr = KSPRegister(KSPPIPEFCG,     KSPCreate_PIPEFCG);CHKERRQ(ierr);
  ierr = KSPRegister(KSPBCGS,        KSPCreate_BCGS);CHKERRQ(ierr);
  ierr = KSPRegister(KSPIBCGS,       KSPCreate_IBCGS);CHKERRQ(ierr);
  ierr = KSPRegister(KSPFBCGS,       KSPCreate_FBCGS);CHKERRQ(ierr);
  ierr = KSPRegister(KSPFBCGSR,      KSPCreate_FBCGSR);CHKERRQ(ierr);
  ierr = KSPRegister(KSPBCGSL,       KSPCreate_BCGSL);CHKERRQ(ierr);
  ierr = KSPRegister(KSPCGS,         KSPCreate_CGS);CHKERRQ(ierr);
  ierr = KSPRegister(KSPTFQMR,       KSPCreate_TFQMR);CHKERRQ(ierr);
  ierr = KSPRegister(KSPCR,          KSPCreate_CR);CHKERRQ(ierr);
  ierr = KSPRegister(KSPPIPECR,      KSPCreate_PIPECR);CHKERRQ(ierr);
  ierr = KSPRegister(KSPLSQR,        KSPCreate_LSQR);CHKERRQ(ierr);
  ierr = KSPRegister(KSPPREONLY,     KSPCreate_PREONLY);CHKERRQ(ierr);
  ierr = KSPRegister(KSPQCG,         KSPCreate_QCG);CHKERRQ(ierr);
  ierr = KSPRegister(KSPBICG,        KSPCreate_BiCG);CHKERRQ(ierr);
  ierr = KSPRegister(KSPFGMRES,      KSPCreate_FGMRES);CHKERRQ(ierr);
  ierr = KSPRegister(KSPPIPEFGMRES,  KSPCreate_PIPEFGMRES);CHKERRQ(ierr);
  ierr = KSPRegister(KSPMINRES,      KSPCreate_MINRES);CHKERRQ(ierr);
  ierr = KSPRegister(KSPSYMMLQ,      KSPCreate_SYMMLQ);CHKERRQ(ierr);
  ierr = KSPRegister(KSPLGMRES,      KSPCreate_LGMRES);CHKERRQ(ierr);
  ierr = KSPRegister(KSPLCD,         KSPCreate_LCD);CHKERRQ(ierr);
  ierr = KSPRegister(KSPGCR,         KSPCreate_GCR);CHKERRQ(ierr);
  ierr = KSPRegister(KSPPIPEGCR,     KSPCreate_PIPEGCR);CHKERRQ(ierr);
  ierr = KSPRegister(KSPPGMRES,      KSPCreate_PGMRES);CHKERRQ(ierr);
#if !defined(PETSC_USE_COMPLEX)
  ierr = KSPRegister(KSPDGMRES,      KSPCreate_DGMRES);CHKERRQ(ierr);
#endif
  ierr = KSPRegister(KSPTSIRM,       KSPCreate_TSIRM);CHKERRQ(ierr);
  ierr = KSPRegister(KSPCGLS,        KSPCreate_CGLS);CHKERRQ(ierr);
  ierr = KSPRegister(KSPFETIDP,      KSPCreate_FETIDP);CHKERRQ(ierr);
  PetscFunctionReturn(0);
}

