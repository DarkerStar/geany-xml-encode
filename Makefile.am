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

## Tell automake where to find extra m4 macros
ACLOCAL_AMFLAGS = -I m4

## Tell automake about the subdirectories to look into
SUBDIRS = src po

## Intltool stuff
INTLTOOL_FILES = intltool-extract.in \
                 intltool-merge.in \
                 intltool-update.in

EXTRA_DIST = $(INTLTOOL_FILES)

DISTCLEANFILES = intltool-extract \
                 intltool-merge \
                 intltool-update \
                 po/.intltool-merge-cache

# Remove the Libtool library
install-exec-hook:
	rm -f $(geanypluginsdir)/xmlencode.la

# Remove the plugin
uninstall-hook:
	rm -f $(geanypluginsdir)/xmlencode.so

