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

#include "signals.h"

/* API transition defines *****************************************************/
#define XML_ENCODE_OLD_API_VERSION 211
#define XML_ENCODE_NEW_API_VERSION 225

#if GEANY_API_VERSION >= XML_ENCODE_NEW_API_VERSION

// Nothing needed.

#else // GEANY_API_VERSION < XML_ENCODE_NEW_API_VERSION

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

#endif // GEANY_API_VERSION >= XML_ENCODE_NEW_API_VERSION

/* Exported functions *********************************************************/

/* plugin_init
 * 
 * Sets up translations, and the menu items.
 */
void do_plugin_init(GeanyData* data, GtkWidget** main_menu)
{
  // Initialize translations
  main_locale_init(LOCALEDIR, GETTEXT_PACKAGE);
  
  // Main menu item
  *main_menu = gtk_menu_item_new_with_mnemonic(_("Encode _XML special characters"));
  gtk_widget_show_all(*main_menu);
  gtk_container_add(GTK_CONTAINER(data->main_widgets->tools_menu), *main_menu);
  
  // Submenu
  GtkWidget* main_menu_submenu = gtk_menu_new();
  gtk_menu_item_set_submenu(GTK_MENU_ITEM(*main_menu), main_menu_submenu);
  
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
  ui_add_document_sensitive(*main_menu);
}

/* plugin_cleanup
 * 
 * Destroys the menu items created by plugin_init().
 */
void do_plugin_cleanup(GtkWidget* main_menu)
{
  // Destroy the menu
  gtk_widget_destroy(main_menu);
}

#if GEANY_API_VERSION >= XML_ENCODE_NEW_API_VERSION

/* New 1.26 API ***************************************************************/

/* plugin_init
 * 
 * Sets up the menu items.
 */
static gboolean plugin_init(GeanyPlugin* plugin, gpointer pdata)
{
  GtkWidget* main_menu = NULL;
  
  do_plugin_init(plugin->geany_data, &main_menu);
  geany_plugin_set_data(plugin, main_menu, NULL);
  
  return TRUE;
}

/* plugin_cleanup
 * 
 * Destroys the menu items.
 */
static void plugin_cleanup(GeanyPlugin*, gpointer pdata)
{
  GtkWidget* main_menu = (GtkWidget*)pdata;
  
  do_plugin_cleanup(main_menu);
}

/* geany_load_module
 * 
 * Plugin entry point.
 */
G_MODULE_EXPORT
void geany_load_module(GeanyPlugin* plugin)
{
  main_locale_init(LOCALEDIR, GETTEXT_PACKAGE);
  
  plugin->info->name        = _("XML Encode");
  plugin->info->description = _("Encode XML special characters as entities");
  plugin->info->version     = VERSION;
  plugin->info->author      = "Mark A. Gibbs <indi.in.the.wired@gmail.com>";
  
  plugin->funcs->init    = plugin_init;
  plugin->funcs->cleanup = plugin_cleanup;
  
  geany_plugin_register(plugin, GEANY_API_VERSION, XML_ENCODE_NEW_API_VERSION,
    GEANY_ABI_VERSION);
}

#else // GEANY_API_VERSION < XML_ENCODE_NEW_API_VERSION

/* Old (pre 1.26) API *********************************************************/

/* plugin_init
 * 
 * Sets up translations, and the menu items.
 */
void plugin_init(GeanyData* data)
{
  do_plugin_init(geany, &main_menu);
}

/* plugin_cleanup
 * 
 * Destroys the menu items created by plugin_init().
 */
void plugin_cleanup(void)
{
  do_plugin_cleanup(main_menu);
  main_menu = NULL;
}

#endif //  GEANY_API_VERSION >= XML_ENCODE_NEW_API_VERSION
