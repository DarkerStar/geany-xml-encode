#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "geanyplugin.h"

GeanyPlugin*    geany_plugin;
GeanyData*      geany_data;
GeanyFunctions* geany_functions;

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

static GtkWidget* main_menu = NULL;

typedef struct entity_data
{
	gchar        character;
	gchar const* entity;
	unsigned int entity_length;
} entity_data;

void do_encode(unsigned long begin, unsigned long end)
{
	static gchar const amp_entity[]  = "&amp;";
	static gchar const lt_entity[]   = "&lt;";
	static gchar const gt_entity[]   = "&gt;";
	static gchar const quot_entity[] = "&quot;";
	static gchar const apos_entity[] = "&apos;";
	
	static entity_data const entities[] = {
		{ '&',  amp_entity,  sizeof(amp_entity) - 1  },
		{ '<',  lt_entity,   sizeof(lt_entity) - 1   },
		{ '>',  gt_entity,   sizeof(gt_entity) - 1   },
		{ '"',  quot_entity, sizeof(quot_entity) - 1 },
		{ '\'', apos_entity, sizeof(apos_entity) - 1 },
	};
	unsigned int const num_entities = sizeof(entities) / sizeof(entities[0]);
	
	GeanyDocument* document = document_get_current();
	if (document && begin != end)
	{
		ScintillaObject* sci = document->editor->sci;
		
		// Save original target info
		unsigned long t_beg = scintilla_send_message(sci, SCI_GETTARGETSTART, 0, 0);
		unsigned long t_end = scintilla_send_message(sci, SCI_GETTARGETEND, 0, 0);
		
		// Start undo action (so a single undo undoes all changes at once)
		scintilla_send_message(sci, SCI_BEGINUNDOACTION, 0, 0);
		
		while (begin < end)
		{
			// Get next character
			gchar c = (gchar)scintilla_send_message(sci, SCI_GETCHARAT, begin, 0);
			
			// See if it's a special character
			entity_data const* entity = NULL;
			for (unsigned int n = 0; n < num_entities; ++n)
			{
				if (entities[n].character == c)
				{
					entity = &entities[n];
					break;
				}
			}
			
			// If it is, do the replace; otherwise, just move on
			if (entity)
			{
				// Mark the character as the target
				scintilla_send_message(sci, SCI_SETTARGETSTART, begin, 0);
				scintilla_send_message(sci, SCI_SETTARGETEND, begin + 1, 0);
				
				// Replace
				scintilla_send_message(sci, SCI_REPLACETARGET,
					entity->entity_length,
					(sptr_t)entity->entity
				);
				
				// Advance past the inserted entity
				begin += entity->entity_length;
				
				// The text size has grown by the additional entity characters
				end += entity->entity_length - 1;
			}
			else
			{
				// Move on to the next char
				++begin;
			}
		}
		
		// End undo action
		scintilla_send_message(sci, SCI_ENDUNDOACTION, 0, 0);
		
		// Restore original target info
		scintilla_send_message(sci, SCI_SETTARGETSTART, t_beg, 0);
		scintilla_send_message(sci, SCI_SETTARGETEND, t_end, 0);
	}
}

void activate_encode_doc(GtkMenuItem* menu_item, gpointer gdata)
{
	GeanyDocument* document = document_get_current();
	if (document)
	{
		ScintillaObject* sci = document->editor->sci;
		
		unsigned long sel_beg = 0;
		unsigned long sel_end = scintilla_send_message(sci, SCI_GETLENGTH, 0, 0);
		
		do_encode(sel_beg, sel_end);
	}
}

void activate_encode_sel(GtkMenuItem* menu_item, gpointer gdata)
{
	GeanyDocument* document = document_get_current();
	if (document)
	{
		ScintillaObject* sci = document->editor->sci;
		
		unsigned long sel_beg = scintilla_send_message(sci, SCI_GETSELECTIONSTART, 0, 0);
		unsigned long sel_end = scintilla_send_message(sci, SCI_GETSELECTIONEND, 0, 0);
		
		do_encode(sel_beg, sel_end);
	}
}

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

void plugin_cleanup(void)
{
	// Destroy the menu
  gtk_widget_destroy(main_menu);
  main_menu = NULL;
}
