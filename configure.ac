################################################################################
#                                                                              #
# This file is part of the Geany XML encode plugin.                            #
#                                                                              #
# The Geany XML encode plugin is free software: you can redistribute it and/or #
# modify it under the terms of the GNU General Public License as published by  #
# the Free Software Foundation, either version 3 of the License, or            #
# (at your option) any later version.                                          #
#                                                                              #
# The Geany XML encode plugin is distributed in the hope that it will be       #
# useful, but WITHOUT ANY WARRANTY; without even the implied warranty of       #
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                #
# GNU General Public License for more details.                                 #
#                                                                              #
# You should have received a copy of the GNU General Public License            #
# along with the Geany XML encode plugin.  If not, see                         #
# <http://www.gnu.org/licenses/>.                                              #
#                                                                              #
################################################################################

# Initialize autoconf ##########################################################
AC_PREREQ([2.69])

AC_INIT([Geany XML encode plugin], [0.1], [indi.in.the.wired@gmail.com])

AC_CONFIG_SRCDIR([src/xml-encode.c])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])

# Initialize automake and libtool ##############################################
AM_INIT_AUTOMAKE([-Wall -Werror])
LT_INIT([disable-static])

# Set up program checks ########################################################
AC_PROG_CC
AC_PROG_CC_STDC

# Set up intltool and translation stuff ########################################
IT_PROG_INTLTOOL([0.50.0])

GETTEXT_PACKAGE=geany-xml-encode
AC_SUBST(GETTEXT_PACKAGE)
AC_DEFINE_UNQUOTED([GETTEXT_PACKAGE], ["$GETTEXT_PACKAGE"], [The domain to use with gettext])
LOCALEDIR="${datadir}/locale"
AC_SUBST(LOCALEDIR)
AM_GLIB_GNU_GETTEXT

# Set up Geany #################################################################
GP_CHECK_GEANY(1.22)

# Output #######################################################################
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile src/Makefile po/Makefile.in])
AC_OUTPUT
