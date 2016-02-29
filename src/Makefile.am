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

## Global flags
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

## Recipies to create libraries
geanyplugins_LTLIBRARIES = xmlencode.la

xmlencode_la_SOURCES = xml-encode.c \
                       signals.h \
                       signals.c \
                       encode.h \
                       encode.c

xmlencode_la_LIBADD  = $(GEANY_LIBS) $(INTLLIBS)
