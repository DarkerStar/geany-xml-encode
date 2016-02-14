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

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "geanyplugin.h"

#include "encode.h"

/* External variables *********************************************************/
GeanyPlugin*    geany_plugin;
GeanyData*      geany_data;
GeanyFunctions* geany_functions;

/* Plugin information *********************************************************/
PLUGIN_VERSION_CHECK(211)

PLUGIN_SET_TRANSLATABLE_INFO(
  LOCALEDIR,
  GETTEXT_PACKAGE,
  // Plugin name
  _("XML Encode"),
  // Plugin description
  _("Encode XML special characters as entities"),
  VERSION,
  "Mark A. Gibbs <indi.in.the.wired@gmail.com>"
);

/* Plugin private stuff *******************************************************/
static GtkWidget* main_menu = NULL;

/* activate_encode_doc
 * 
 * Callback function for "activate" signal from menu item to encode XML chars
 * in the entire document.
 */
void activate_encode_doc(GtkMenuItem* menu_item, gpointer gdata)
{
  geany_xml_encode_document();
}

/* activate_encode_sel
 * 
 * Callback function for "activate" signal from menu item to encode XML chars
 * in the selection.
 */
void activate_encode_sel(GtkMenuItem* menu_item, gpointer gdata)
{
  geany_xml_encode_selection();
}

/* Exported functions *********************************************************/

/* plugin_init
 * 
 * Sets up translations, and the menu items.
 */
void plugin_init(GeanyData* data)
{
  // Initialize translations
  main_locale_init(LOCALEDIR, GETTEXT_PACKAGE);
  
  // Main menu item
  main_menu = gtk_menu_item_new_with_mnemonic(_("Encode _XML special characters"));
  gtk_widget_show_all(main_menu);
  gtk_container_add(GTK_CONTAINER(geany->main_widgets->tools_menu), main_menu);
  
  // Submenu
  GtkWidget* main_menu_submenu = gtk_menu_new();
  gtk_menu_item_set_submenu(GTK_MENU_ITEM(main_menu), main_menu_submenu);
  
  // "Encode document" submenu item
  GtkWidget* mi_encode_doc = gtk_menu_item_new_with_mnemonic(_("_Document"));
  g_signal_connect(mi_encode_doc, "activate", G_CALLBACK(activate_encode_doc), NULL);
  gtk_container_add(GTK_CONTAINER(main_menu_submenu), mi_encode_doc);
  
  // "Encode selection" submenu item
  GtkWidget* mi_encode_sel = gtk_menu_item_new_with_mnemonic(_("_Selection"));
  g_signal_connect(mi_encode_sel, "activate", G_CALLBACK(activate_encode_sel), NULL);
  gtk_container_add(GTK_CONTAINER(main_menu_submenu), mi_encode_sel);
  
  // Show the submenu items
  gtk_widget_show(mi_encode_doc);
  gtk_widget_show(mi_encode_sel);
  
  // Set main menu item to be active only when there's a document
  ui_add_document_sensitive(main_menu);
}

/* plugin_cleanup
 * 
 * Destroys the menu items created by plugin_init().
 */
void plugin_cleanup(void)
{
  // Destroy the menu
  gtk_widget_destroy(main_menu);
  main_menu = NULL;
}
