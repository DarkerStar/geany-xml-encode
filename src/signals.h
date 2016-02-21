/*
 * This file is part of the Geany XML encode plugin.
 * 
 * The Geany XML encode plugin is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * The Geany XML encode plugin is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with the Geany XML encode plugin.  If not, see
 * <http://www.gnu.org/licenses/>.
 */

#ifndef GEANY_XML_signals_h_
#define GEANY_XML_signals_h_

#include "geanyplugin.h"

void activate_encode_doc(GtkMenuItem*, gpointer);
void activate_encode_sel(GtkMenuItem*, gpointer);

#endif // include guard
