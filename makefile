IPETSCDIR = .

CFLAGS   = $(OPT) -I$(IPETSCDIR)/include -I.. -I$(IPETSCDIR) $(CONF)
SOURCEC  =
SOURCEF  =
WSOURCEC = 
SOURCEH  = 
OBJSC    =
WOBJS    = 
OBJSF    =
LIBBASE  = libpetscvec
LINCLUDE = $(SOURCEH)
DIRS     = src include pinclude

include $(IPETSCDIR)/bmake/$(PETSC_ARCH)/$(PETSC_ARCH)

all: chkpetsc_dir
	-@if [ ! -d $(PDIR) ]; then \
          echo $(PDIR) ; mkdir -p $(PDIR) ; fi
	-$(RM) -f $(PDIR)/*.a
	-@$(OMAKE) BOPT=$(BOPT) PETSC_ARCH=$(PETSC_ARCH) \
           PETSC_VERSION=$(PETSC_VERSION) ACTION=libfast  tree 
	$(RANLIB) $(PDIR)/*.a

ranlib:
	$(RANLIB) $(PDIR)/*.a

deletelibs:
	-$(RM) -f $(PDIR)/*.a $(PDIR)/complex/* $(PDIR)/c++/*

deletemanpages:
	$(RM) -f $(PETSC_DIR)/Keywords $(PETSC_DIR)/docs/man/man*/*

deletewwwpages:
	$(RM) -f $(PETSC_DIR)/docs/www/man*/* $(PETSC_DIR)/docs/www/www.cit

deletelatexpages:
	$(RM) -f $(PETSC_DIR)/docs/tex/rsum/*sum*.tex

#  To access the tags in emacs, type M-x visit-tags-table and specify
#  the file petsc/TAGS.  Then, to move to where a PETSc function is
#  defined, enter M-. and the function name.  To search for a string
#  and move to the first occurrence, use M-x tags-search and the string.
#  To locate later occurrences, use M-,

etags:
	$(RM) -f TAGS
	etags -f TAGS    src/*/impls/*/*.h src/*/impls/*/*/*.h src/*/examples/*.c
	etags -a -f TAGS src/*/*.h src/*/*.c src/*/src/*.c src/*/impls/*/*.c 
	etags -a -f TAGS src/*/impls/*/*/*.c src/*/utils/*.c
	etags -a -f TAGS docs/tex/manual.tex src/sys/error/*.c
	etags -a -f TAGS include/*.h pinclude/*.h
	etags -a -f TAGS src/*/impls/*.c src/sys/*.c
	etags -a -f TAGS makefile src/*/src/makefile src/makefile 
	etags -a -f TAGS src/*/impls/makefile src/*/impls/*/makefile
	etags -a -f TAGS bmake/common docs/tex/routin.tex
	etags -a -f TAGS src/*/utils/makefile src/*/examples/makefile
	etags -a -f TAGS src/*/makefile src/*/impls/*/*/makefile
	chmod g+w TAGS

runexamples:
