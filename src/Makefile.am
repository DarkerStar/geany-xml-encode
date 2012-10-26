
AM_CPPFLAGS = \
-DLOCALEDIR=\""$(LOCALEDIR)"\" \
-DPREFIX=\""$(prefix)"\" \
-DDOCDIR=\""$(docdir)"\" \
-DGEANYPLUGINS_DATADIR=\""$(datadir)"\" \
-DPKGDATADIR=\""$(pkgdatadir)"\" \
-DLIBDIR=\""$(libdir)"\" \
-DPKGLIBDIR=\""$(pkglibdir)"\" \
$(GEANY_CFLAGS)

AM_LDFLAGS = -no-undefined -module -avoid-version -export-dynamic

geanyplugins_LTLIBRARIES = xmlencode.la

xmlencode_la_SOURCES = xml-encode.c
xmlencode_la_LIBADD  = $(GEANY_LIBS) $(INTLLIBS)
