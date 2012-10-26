AC_PREREQ([2.69])

AC_INIT([Geany XML encode plugin], [0.1], [indi.in.the.wired@gmail.com])

AC_CONFIG_SRCDIR([src/xml-encode.c])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])

AM_INIT_AUTOMAKE([-Wall -Werror])
LT_INIT([disable-static])

AC_PROG_CC
AC_PROG_CC_STDC

IT_PROG_INTLTOOL([0.50.0])

GETTEXT_PACKAGE=geany-xml-encode
AC_SUBST(GETTEXT_PACKAGE)
AC_DEFINE_UNQUOTED([GETTEXT_PACKAGE], ["$GETTEXT_PACKAGE"], [The domain to use with gettext])
LOCALEDIR=[${datadir}/locale]
AC_SUBST(LOCALEDIR)
AM_GLIB_GNU_GETTEXT

GP_CHECK_GEANY(1.22)

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile src/Makefile po/Makefile.in])
AC_OUTPUT
