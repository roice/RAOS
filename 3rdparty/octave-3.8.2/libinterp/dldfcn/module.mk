## DO NOT EDIT -- generated from module-files by config-module.awk

EXTRA_DIST += \
  dldfcn/config-module.sh \
  dldfcn/config-module.awk \
  dldfcn/module-files \
  dldfcn/oct-qhull.h

DLDFCN_SRC = \
  dldfcn/__delaunayn__.cc \
  dldfcn/__dsearchn__.cc \
  dldfcn/__eigs__.cc \
  dldfcn/__fltk_uigetfile__.cc \
  dldfcn/__glpk__.cc \
  dldfcn/__init_fltk__.cc \
  dldfcn/__init_gnuplot__.cc \
  dldfcn/__magick_read__.cc \
  dldfcn/__voronoi__.cc \
  dldfcn/amd.cc \
  dldfcn/ccolamd.cc \
  dldfcn/chol.cc \
  dldfcn/colamd.cc \
  dldfcn/convhulln.cc \
  dldfcn/dmperm.cc \
  dldfcn/fftw.cc \
  dldfcn/qr.cc \
  dldfcn/symbfact.cc \
  dldfcn/symrcm.cc \
  dldfcn/tsearch.cc

DLDFCN_LIBS = $(DLDFCN_SRC:.cc=.la)

if AMCOND_ENABLE_DYNAMIC_LINKING

octlib_LTLIBRARIES += $(DLDFCN_LIBS)

## Use stamp files to avoid problems with checking timestamps
## of symbolic links

dldfcn/$(am__leading_dot)__delaunayn__.oct-stamp: dldfcn/__delaunayn__.la
	rm -f $(<:.la=.oct)
	la=$(<F) && \
	  of=$(<F:.la=.oct) && \
	  cd dldfcn && \
	  $(LN_S) .libs/`$(SED) -n -e "s/dlname='\([^']*\)'/\1/p" < $$la` $$of && \
	  touch $(@F)

dldfcn/$(am__leading_dot)__dsearchn__.oct-stamp: dldfcn/__dsearchn__.la
	rm -f $(<:.la=.oct)
	la=$(<F) && \
	  of=$(<F:.la=.oct) && \
	  cd dldfcn && \
	  $(LN_S) .libs/`$(SED) -n -e "s/dlname='\([^']*\)'/\1/p" < $$la` $$of && \
	  touch $(@F)

dldfcn/$(am__leading_dot)__eigs__.oct-stamp: dldfcn/__eigs__.la
	rm -f $(<:.la=.oct)
	la=$(<F) && \
	  of=$(<F:.la=.oct) && \
	  cd dldfcn && \
	  $(LN_S) .libs/`$(SED) -n -e "s/dlname='\([^']*\)'/\1/p" < $$la` $$of && \
	  touch $(@F)

dldfcn/$(am__leading_dot)__fltk_uigetfile__.oct-stamp: dldfcn/__fltk_uigetfile__.la
	rm -f $(<:.la=.oct)
	la=$(<F) && \
	  of=$(<F:.la=.oct) && \
	  cd dldfcn && \
	  $(LN_S) .libs/`$(SED) -n -e "s/dlname='\([^']*\)'/\1/p" < $$la` $$of && \
	  touch $(@F)

dldfcn/$(am__leading_dot)__glpk__.oct-stamp: dldfcn/__glpk__.la
	rm -f $(<:.la=.oct)
	la=$(<F) && \
	  of=$(<F:.la=.oct) && \
	  cd dldfcn && \
	  $(LN_S) .libs/`$(SED) -n -e "s/dlname='\([^']*\)'/\1/p" < $$la` $$of && \
	  touch $(@F)

dldfcn/$(am__leading_dot)__init_fltk__.oct-stamp: dldfcn/__init_fltk__.la
	rm -f $(<:.la=.oct)
	la=$(<F) && \
	  of=$(<F:.la=.oct) && \
	  cd dldfcn && \
	  $(LN_S) .libs/`$(SED) -n -e "s/dlname='\([^']*\)'/\1/p" < $$la` $$of && \
	  touch $(@F)

dldfcn/$(am__leading_dot)__init_gnuplot__.oct-stamp: dldfcn/__init_gnuplot__.la
	rm -f $(<:.la=.oct)
	la=$(<F) && \
	  of=$(<F:.la=.oct) && \
	  cd dldfcn && \
	  $(LN_S) .libs/`$(SED) -n -e "s/dlname='\([^']*\)'/\1/p" < $$la` $$of && \
	  touch $(@F)

dldfcn/$(am__leading_dot)__magick_read__.oct-stamp: dldfcn/__magick_read__.la
	rm -f $(<:.la=.oct)
	la=$(<F) && \
	  of=$(<F:.la=.oct) && \
	  cd dldfcn && \
	  $(LN_S) .libs/`$(SED) -n -e "s/dlname='\([^']*\)'/\1/p" < $$la` $$of && \
	  touch $(@F)

dldfcn/$(am__leading_dot)__voronoi__.oct-stamp: dldfcn/__voronoi__.la
	rm -f $(<:.la=.oct)
	la=$(<F) && \
	  of=$(<F:.la=.oct) && \
	  cd dldfcn && \
	  $(LN_S) .libs/`$(SED) -n -e "s/dlname='\([^']*\)'/\1/p" < $$la` $$of && \
	  touch $(@F)

dldfcn/$(am__leading_dot)amd.oct-stamp: dldfcn/amd.la
	rm -f $(<:.la=.oct)
	la=$(<F) && \
	  of=$(<F:.la=.oct) && \
	  cd dldfcn && \
	  $(LN_S) .libs/`$(SED) -n -e "s/dlname='\([^']*\)'/\1/p" < $$la` $$of && \
	  touch $(@F)

dldfcn/$(am__leading_dot)ccolamd.oct-stamp: dldfcn/ccolamd.la
	rm -f $(<:.la=.oct)
	la=$(<F) && \
	  of=$(<F:.la=.oct) && \
	  cd dldfcn && \
	  $(LN_S) .libs/`$(SED) -n -e "s/dlname='\([^']*\)'/\1/p" < $$la` $$of && \
	  touch $(@F)

dldfcn/$(am__leading_dot)chol.oct-stamp: dldfcn/chol.la
	rm -f $(<:.la=.oct)
	la=$(<F) && \
	  of=$(<F:.la=.oct) && \
	  cd dldfcn && \
	  $(LN_S) .libs/`$(SED) -n -e "s/dlname='\([^']*\)'/\1/p" < $$la` $$of && \
	  touch $(@F)

dldfcn/$(am__leading_dot)colamd.oct-stamp: dldfcn/colamd.la
	rm -f $(<:.la=.oct)
	la=$(<F) && \
	  of=$(<F:.la=.oct) && \
	  cd dldfcn && \
	  $(LN_S) .libs/`$(SED) -n -e "s/dlname='\([^']*\)'/\1/p" < $$la` $$of && \
	  touch $(@F)

dldfcn/$(am__leading_dot)convhulln.oct-stamp: dldfcn/convhulln.la
	rm -f $(<:.la=.oct)
	la=$(<F) && \
	  of=$(<F:.la=.oct) && \
	  cd dldfcn && \
	  $(LN_S) .libs/`$(SED) -n -e "s/dlname='\([^']*\)'/\1/p" < $$la` $$of && \
	  touch $(@F)

dldfcn/$(am__leading_dot)dmperm.oct-stamp: dldfcn/dmperm.la
	rm -f $(<:.la=.oct)
	la=$(<F) && \
	  of=$(<F:.la=.oct) && \
	  cd dldfcn && \
	  $(LN_S) .libs/`$(SED) -n -e "s/dlname='\([^']*\)'/\1/p" < $$la` $$of && \
	  touch $(@F)

dldfcn/$(am__leading_dot)fftw.oct-stamp: dldfcn/fftw.la
	rm -f $(<:.la=.oct)
	la=$(<F) && \
	  of=$(<F:.la=.oct) && \
	  cd dldfcn && \
	  $(LN_S) .libs/`$(SED) -n -e "s/dlname='\([^']*\)'/\1/p" < $$la` $$of && \
	  touch $(@F)

dldfcn/$(am__leading_dot)qr.oct-stamp: dldfcn/qr.la
	rm -f $(<:.la=.oct)
	la=$(<F) && \
	  of=$(<F:.la=.oct) && \
	  cd dldfcn && \
	  $(LN_S) .libs/`$(SED) -n -e "s/dlname='\([^']*\)'/\1/p" < $$la` $$of && \
	  touch $(@F)

dldfcn/$(am__leading_dot)symbfact.oct-stamp: dldfcn/symbfact.la
	rm -f $(<:.la=.oct)
	la=$(<F) && \
	  of=$(<F:.la=.oct) && \
	  cd dldfcn && \
	  $(LN_S) .libs/`$(SED) -n -e "s/dlname='\([^']*\)'/\1/p" < $$la` $$of && \
	  touch $(@F)

dldfcn/$(am__leading_dot)symrcm.oct-stamp: dldfcn/symrcm.la
	rm -f $(<:.la=.oct)
	la=$(<F) && \
	  of=$(<F:.la=.oct) && \
	  cd dldfcn && \
	  $(LN_S) .libs/`$(SED) -n -e "s/dlname='\([^']*\)'/\1/p" < $$la` $$of && \
	  touch $(@F)

dldfcn/$(am__leading_dot)tsearch.oct-stamp: dldfcn/tsearch.la
	rm -f $(<:.la=.oct)
	la=$(<F) && \
	  of=$(<F:.la=.oct) && \
	  cd dldfcn && \
	  $(LN_S) .libs/`$(SED) -n -e "s/dlname='\([^']*\)'/\1/p" < $$la` $$of && \
	  touch $(@F)

else

noinst_LTLIBRARIES += $(DLDFCN_LIBS)

endif

dldfcn___delaunayn___la_SOURCES = dldfcn/__delaunayn__.cc
dldfcn/__delaunayn__.df: CPPFLAGS += $(QHULL_CPPFLAGS)
dldfcn___delaunayn___la_CPPFLAGS = $(QHULL_CPPFLAGS) $(AM_CPPFLAGS)
dldfcn___delaunayn___la_LDFLAGS = -avoid-version -module $(NO_UNDEFINED_LDFLAG) $(QHULL_LDFLAGS) $(OCT_LINK_OPTS)
dldfcn___delaunayn___la_LIBADD = $(DLD_LIBOCTINTERP_LIBADD) ../liboctave/liboctave.la $(QHULL_LIBS) $(OCT_LINK_DEPS)

dldfcn___dsearchn___la_SOURCES = dldfcn/__dsearchn__.cc
dldfcn___dsearchn___la_LDFLAGS = -avoid-version -module $(NO_UNDEFINED_LDFLAG)  $(OCT_LINK_OPTS)
dldfcn___dsearchn___la_LIBADD = $(DLD_LIBOCTINTERP_LIBADD) ../liboctave/liboctave.la  $(OCT_LINK_DEPS)

dldfcn___eigs___la_SOURCES = dldfcn/__eigs__.cc
dldfcn/__eigs__.df: CPPFLAGS += $(ARPACK_CPPFLAGS) $(SPARSE_XCPPFLAGS)
dldfcn___eigs___la_CPPFLAGS = $(ARPACK_CPPFLAGS) $(SPARSE_XCPPFLAGS) $(AM_CPPFLAGS)
dldfcn___eigs___la_LDFLAGS = -avoid-version -module $(NO_UNDEFINED_LDFLAG) $(ARPACK_LDFLAGS) $(SPARSE_XLDFLAGS) $(OCT_LINK_OPTS)
dldfcn___eigs___la_LIBADD = $(DLD_LIBOCTINTERP_LIBADD) ../liboctave/liboctave.la $(ARPACK_LIBS) $(SPARSE_XLIBS) $(LAPACK_LIBS) $(BLAS_LIBS) $(OCT_LINK_DEPS)

dldfcn___fltk_uigetfile___la_SOURCES = dldfcn/__fltk_uigetfile__.cc
dldfcn/__fltk_uigetfile__.df: CPPFLAGS += $(GRAPHICS_CFLAGS) $(FT2_CPPFLAGS)
dldfcn___fltk_uigetfile___la_CPPFLAGS = $(GRAPHICS_CFLAGS) $(FT2_CPPFLAGS) $(AM_CPPFLAGS)
dldfcn___fltk_uigetfile___la_LDFLAGS = -avoid-version -module $(NO_UNDEFINED_LDFLAG) $(GRAPHICS_LDFLAGS) $(FT2_LDFLAGS) $(OCT_LINK_OPTS)
dldfcn___fltk_uigetfile___la_LIBADD = $(DLD_LIBOCTINTERP_LIBADD) ../liboctave/liboctave.la $(GRAPHICS_LIBS) $(FT2_LIBS) $(OCT_LINK_DEPS)

dldfcn___glpk___la_SOURCES = dldfcn/__glpk__.cc
dldfcn/__glpk__.df: CPPFLAGS += $(GLPK_CPPFLAGS)
dldfcn___glpk___la_CPPFLAGS = $(GLPK_CPPFLAGS) $(AM_CPPFLAGS)
dldfcn___glpk___la_LDFLAGS = -avoid-version -module $(NO_UNDEFINED_LDFLAG) $(GLPK_LDFLAGS) $(OCT_LINK_OPTS)
dldfcn___glpk___la_LIBADD = $(DLD_LIBOCTINTERP_LIBADD) ../liboctave/liboctave.la $(GLPK_LIBS) $(OCT_LINK_DEPS)

dldfcn___init_fltk___la_SOURCES = dldfcn/__init_fltk__.cc
dldfcn/__init_fltk__.df: CPPFLAGS += $(GRAPHICS_CFLAGS) $(FT2_CPPFLAGS) $(FONTCONFIG_CPPFLAGS)
dldfcn___init_fltk___la_CPPFLAGS = $(GRAPHICS_CFLAGS) $(FT2_CPPFLAGS) $(FONTCONFIG_CPPFLAGS) $(AM_CPPFLAGS)
dldfcn___init_fltk___la_LDFLAGS = -avoid-version -module $(NO_UNDEFINED_LDFLAG) $(GRAPHICS_LDFLAGS) $(FT2_LDFLAGS) $(OCT_LINK_OPTS)
dldfcn___init_fltk___la_LIBADD = $(DLD_LIBOCTINTERP_LIBADD) ../liboctave/liboctave.la $(GRAPHICS_LIBS) $(FT2_LIBS) $(OPENGL_LIBS) $(OCT_LINK_DEPS)

dldfcn___init_gnuplot___la_SOURCES = dldfcn/__init_gnuplot__.cc
dldfcn/__init_gnuplot__.df: CPPFLAGS += $(FT2_CPPFLAGS) $(FONTCONFIG_CPPFLAGS)
dldfcn___init_gnuplot___la_CPPFLAGS = $(FT2_CPPFLAGS) $(FONTCONFIG_CPPFLAGS) $(AM_CPPFLAGS)
dldfcn___init_gnuplot___la_LDFLAGS = -avoid-version -module $(NO_UNDEFINED_LDFLAG)  $(OCT_LINK_OPTS)
dldfcn___init_gnuplot___la_LIBADD = $(DLD_LIBOCTINTERP_LIBADD) ../liboctave/liboctave.la  $(OCT_LINK_DEPS)

dldfcn___magick_read___la_SOURCES = dldfcn/__magick_read__.cc
dldfcn/__magick_read__.df: CPPFLAGS += $(MAGICK_CPPFLAGS)
dldfcn___magick_read___la_CPPFLAGS = $(MAGICK_CPPFLAGS) $(AM_CPPFLAGS)
dldfcn___magick_read___la_LDFLAGS = -avoid-version -module $(NO_UNDEFINED_LDFLAG) $(MAGICK_LDFLAGS) $(OCT_LINK_OPTS)
dldfcn___magick_read___la_LIBADD = $(DLD_LIBOCTINTERP_LIBADD) ../liboctave/liboctave.la $(MAGICK_LIBS) $(OCT_LINK_DEPS)

dldfcn___voronoi___la_SOURCES = dldfcn/__voronoi__.cc
dldfcn/__voronoi__.df: CPPFLAGS += $(QHULL_CPPFLAGS)
dldfcn___voronoi___la_CPPFLAGS = $(QHULL_CPPFLAGS) $(AM_CPPFLAGS)
dldfcn___voronoi___la_LDFLAGS = -avoid-version -module $(NO_UNDEFINED_LDFLAG) $(QHULL_LDFLAGS) $(OCT_LINK_OPTS)
dldfcn___voronoi___la_LIBADD = $(DLD_LIBOCTINTERP_LIBADD) ../liboctave/liboctave.la $(QHULL_LIBS) $(OCT_LINK_DEPS)

dldfcn_amd_la_SOURCES = dldfcn/amd.cc
dldfcn/amd.df: CPPFLAGS += $(SPARSE_XCPPFLAGS)
dldfcn_amd_la_CPPFLAGS = $(SPARSE_XCPPFLAGS) $(AM_CPPFLAGS)
dldfcn_amd_la_LDFLAGS = -avoid-version -module $(NO_UNDEFINED_LDFLAG) $(SPARSE_XLDFLAGS) $(OCT_LINK_OPTS)
dldfcn_amd_la_LIBADD = $(DLD_LIBOCTINTERP_LIBADD) ../liboctave/liboctave.la $(SPARSE_XLIBS) $(OCT_LINK_DEPS)

dldfcn_ccolamd_la_SOURCES = dldfcn/ccolamd.cc
dldfcn/ccolamd.df: CPPFLAGS += $(SPARSE_XCPPFLAGS)
dldfcn_ccolamd_la_CPPFLAGS = $(SPARSE_XCPPFLAGS) $(AM_CPPFLAGS)
dldfcn_ccolamd_la_LDFLAGS = -avoid-version -module $(NO_UNDEFINED_LDFLAG) $(SPARSE_XLDFLAGS) $(OCT_LINK_OPTS)
dldfcn_ccolamd_la_LIBADD = $(DLD_LIBOCTINTERP_LIBADD) ../liboctave/liboctave.la $(SPARSE_XLIBS) $(OCT_LINK_DEPS)

dldfcn_chol_la_SOURCES = dldfcn/chol.cc
dldfcn/chol.df: CPPFLAGS += $(SPARSE_XCPPFLAGS)
dldfcn_chol_la_CPPFLAGS = $(SPARSE_XCPPFLAGS) $(AM_CPPFLAGS)
dldfcn_chol_la_LDFLAGS = -avoid-version -module $(NO_UNDEFINED_LDFLAG) $(SPARSE_XLDFLAGS) $(OCT_LINK_OPTS)
dldfcn_chol_la_LIBADD = $(DLD_LIBOCTINTERP_LIBADD) ../liboctave/liboctave.la $(SPARSE_XLIBS) $(OCT_LINK_DEPS)

dldfcn_colamd_la_SOURCES = dldfcn/colamd.cc
dldfcn/colamd.df: CPPFLAGS += $(SPARSE_XCPPFLAGS)
dldfcn_colamd_la_CPPFLAGS = $(SPARSE_XCPPFLAGS) $(AM_CPPFLAGS)
dldfcn_colamd_la_LDFLAGS = -avoid-version -module $(NO_UNDEFINED_LDFLAG) $(SPARSE_XLDFLAGS) $(OCT_LINK_OPTS)
dldfcn_colamd_la_LIBADD = $(DLD_LIBOCTINTERP_LIBADD) ../liboctave/liboctave.la $(SPARSE_XLIBS) $(OCT_LINK_DEPS)

dldfcn_convhulln_la_SOURCES = dldfcn/convhulln.cc
dldfcn/convhulln.df: CPPFLAGS += $(QHULL_CPPFLAGS)
dldfcn_convhulln_la_CPPFLAGS = $(QHULL_CPPFLAGS) $(AM_CPPFLAGS)
dldfcn_convhulln_la_LDFLAGS = -avoid-version -module $(NO_UNDEFINED_LDFLAG) $(QHULL_LDFLAGS) $(OCT_LINK_OPTS)
dldfcn_convhulln_la_LIBADD = $(DLD_LIBOCTINTERP_LIBADD) ../liboctave/liboctave.la $(QHULL_LIBS) $(OCT_LINK_DEPS)

dldfcn_dmperm_la_SOURCES = dldfcn/dmperm.cc
dldfcn/dmperm.df: CPPFLAGS += $(SPARSE_XCPPFLAGS)
dldfcn_dmperm_la_CPPFLAGS = $(SPARSE_XCPPFLAGS) $(AM_CPPFLAGS)
dldfcn_dmperm_la_LDFLAGS = -avoid-version -module $(NO_UNDEFINED_LDFLAG) $(SPARSE_XLDFLAGS) $(OCT_LINK_OPTS)
dldfcn_dmperm_la_LIBADD = $(DLD_LIBOCTINTERP_LIBADD) ../liboctave/liboctave.la $(SPARSE_XLIBS) $(OCT_LINK_DEPS)

dldfcn_fftw_la_SOURCES = dldfcn/fftw.cc
dldfcn/fftw.df: CPPFLAGS += $(FFTW_XCPPFLAGS)
dldfcn_fftw_la_CPPFLAGS = $(FFTW_XCPPFLAGS) $(AM_CPPFLAGS)
dldfcn_fftw_la_LDFLAGS = -avoid-version -module $(NO_UNDEFINED_LDFLAG) $(FFTW_XLDFLAGS) $(OCT_LINK_OPTS)
dldfcn_fftw_la_LIBADD = $(DLD_LIBOCTINTERP_LIBADD) ../liboctave/liboctave.la $(FFTW_XLIBS) $(OCT_LINK_DEPS)

dldfcn_qr_la_SOURCES = dldfcn/qr.cc
dldfcn/qr.df: CPPFLAGS += $(QRUPDATE_CPPFLAGS) $(SPARSE_XCPPFLAGS)
dldfcn_qr_la_CPPFLAGS = $(QRUPDATE_CPPFLAGS) $(SPARSE_XCPPFLAGS) $(AM_CPPFLAGS)
dldfcn_qr_la_LDFLAGS = -avoid-version -module $(NO_UNDEFINED_LDFLAG) $(QRUPDATE_LDFLAGS) $(SPARSE_XLDFLAGS) $(OCT_LINK_OPTS)
dldfcn_qr_la_LIBADD = $(DLD_LIBOCTINTERP_LIBADD) ../liboctave/liboctave.la $(QRUPDATE_LIBS) $(SPARSE_XLIBS) $(OCT_LINK_DEPS)

dldfcn_symbfact_la_SOURCES = dldfcn/symbfact.cc
dldfcn/symbfact.df: CPPFLAGS += $(SPARSE_XCPPFLAGS)
dldfcn_symbfact_la_CPPFLAGS = $(SPARSE_XCPPFLAGS) $(AM_CPPFLAGS)
dldfcn_symbfact_la_LDFLAGS = -avoid-version -module $(NO_UNDEFINED_LDFLAG) $(SPARSE_XLDFLAGS) $(OCT_LINK_OPTS)
dldfcn_symbfact_la_LIBADD = $(DLD_LIBOCTINTERP_LIBADD) ../liboctave/liboctave.la $(SPARSE_XLIBS) $(OCT_LINK_DEPS)

dldfcn_symrcm_la_SOURCES = dldfcn/symrcm.cc
dldfcn/symrcm.df: CPPFLAGS += $(SPARSE_XCPPFLAGS)
dldfcn_symrcm_la_CPPFLAGS = $(SPARSE_XCPPFLAGS) $(AM_CPPFLAGS)
dldfcn_symrcm_la_LDFLAGS = -avoid-version -module $(NO_UNDEFINED_LDFLAG) $(SPARSE_XLDFLAGS) $(OCT_LINK_OPTS)
dldfcn_symrcm_la_LIBADD = $(DLD_LIBOCTINTERP_LIBADD) ../liboctave/liboctave.la $(SPARSE_XLIBS) $(OCT_LINK_DEPS)

dldfcn_tsearch_la_SOURCES = dldfcn/tsearch.cc
dldfcn_tsearch_la_LDFLAGS = -avoid-version -module $(NO_UNDEFINED_LDFLAG)  $(OCT_LINK_OPTS)
dldfcn_tsearch_la_LIBADD = $(DLD_LIBOCTINTERP_LIBADD) ../liboctave/liboctave.la  $(OCT_LINK_DEPS)
