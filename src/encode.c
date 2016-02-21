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

#include "assert.h"

#include "geanyplugin.h"

#include "encode.h"

typedef struct entity_data
{
  gchar        character;
  gchar const* entity;
  unsigned int entity_length;
} entity_data;

/* geany_xml_encode_entity
 * 
 * Get the encoded entity info for the character given, or NULL if there
 * is none.
 */
static entity_data const* geany_xml_encode_entity(gchar c)
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
    { '\'', apos_entity, sizeof(apos_entity) - 1 }
  };
  size_t const num_entities = sizeof(entities) / sizeof(entities[0]);
  
  for (size_t n = 0; n < num_entities; ++n)
  {
    if (entities[n].character == c)
      return &entities[n];
  }
  
  return NULL;
}

/* geany_xml_encode_notify
 * 
 * Display a status notification message saying how many entities were
 * encoded.
 */
static void geany_xml_encode_notify(GeanyDocument* document, int count)
{
  assert(document);
  
  if (count)
  {
    gchar const* file_name = g_path_get_basename(DOC_FILENAME(document));
    
    // Statusbar message for %n replacements in file %s
    gchar const* msg = g_dngettext(
      NULL,
      "%s: replaced %d XML special character with an entity reference.",
      "%s: replaced %d XML special characters with entity references.",
      count
    );
    
    ui_set_statusbar(TRUE, msg, file_name, count);
    
    g_free((gchar*)file_name);
  }
  else
  {
    // Statusbar message when no replacements were done
    ui_set_statusbar(FALSE, _("No XML special characters found."));
  }
}

/* geany_xml_encode
 * 
 * Encode the XML entities in the document given, between the begin and
 * end markers.
 */
static int geany_xml_encode(GeanyDocument* document, unsigned long begin, unsigned long end)
{
  assert(document);
  
  ScintillaObject* sci = document->editor->sci;
  
  assert(sci);
  assert(begin <= scintilla_send_message(sci, SCI_GETLENGTH, 0, 0));
  assert(end   <= scintilla_send_message(sci, SCI_GETLENGTH, 0, 0));
  assert(begin <= end);
  
  // Save original target info
  unsigned long t_beg = scintilla_send_message(sci, SCI_GETTARGETSTART, 0, 0);
  unsigned long t_end = scintilla_send_message(sci, SCI_GETTARGETEND, 0, 0);
  
  // Start undo action (so a single undo undoes all changes at once)
  scintilla_send_message(sci, SCI_BEGINUNDOACTION, 0, 0);
  
  // Counter to count replacements
  int replaced = 0;
  
  while (begin < end)
  {
    // Get next character
    gchar c = (gchar)scintilla_send_message(sci, SCI_GETCHARAT, begin, 0);
    
    // See if it's a special character
    // If it is, do the replace; otherwise, just move on
    entity_data const* entity = geany_xml_encode_entity(c);
    if (entity)
    {
      // Get the selection info
      unsigned long sel_beg = scintilla_send_message(sci, SCI_GETSELECTIONSTART, 0, 0);
      unsigned long sel_end = scintilla_send_message(sci, SCI_GETSELECTIONEND, 0, 0);
      
      // Mark the character as the target
      scintilla_send_message(sci, SCI_SETTARGETSTART, begin, 0);
      scintilla_send_message(sci, SCI_SETTARGETEND, begin + 1, 0);
      
      // Replace
      scintilla_send_message(sci, SCI_REPLACETARGET,
        entity->entity_length,
        (sptr_t)entity->entity
      );
      
      // How far to advance (the difference in length between original text
      // and replaced text)
      int advance = entity->entity_length - 1;
      
      // Update the selection, if necessary
      if (sel_beg == begin)
        scintilla_send_message(sci, SCI_SETSELECTIONSTART, sel_beg, 0);
      if (sel_end == (begin + 1))
        scintilla_send_message(sci, SCI_SETSELECTIONEND, sel_end + advance, 0);
      
      // Advance all the relevant values
      begin += advance;
      end += advance;
      
      // Count replacement
      ++replaced;
    }
    
    // Move on to the next char
    ++begin;
  }
  
  // Restore original target info
  scintilla_send_message(sci, SCI_SETTARGETSTART, t_beg, 0);
  scintilla_send_message(sci, SCI_SETTARGETEND, t_end, 0);
  
  // End undo action
  scintilla_send_message(sci, SCI_ENDUNDOACTION, 0, 0);
  
  return replaced;
}

/* geany_xml_encode_document
 * 
 * Encode the XML entities in the entire document.
 */
void geany_xml_encode_document()
{
  GeanyDocument* document = document_get_current();
  if (document)
  {
    ScintillaObject* sci = document->editor->sci;
    
    unsigned long sel_beg = 0;
    unsigned long sel_end = scintilla_send_message(sci, SCI_GETLENGTH, 0, 0);
    
    int replaced = geany_xml_encode(document, sel_beg, sel_end);
    
    // Display notification in status area.
    geany_xml_encode_notify(document, replaced);
  }
}

/* geany_xml_encode_selection
 * 
 * Encode the XML entities in the current selection.
 */
void geany_xml_encode_selection()
{
  GeanyDocument* document = document_get_current();
  if (document)
  {
    ScintillaObject* sci = document->editor->sci;
    
    unsigned long sel_beg = scintilla_send_message(sci, SCI_GETSELECTIONSTART, 0, 0);
    unsigned long sel_end = scintilla_send_message(sci, SCI_GETSELECTIONEND, 0, 0);
    
    int replaced = geany_xml_encode(document, sel_beg, sel_end);
    
    // Display notification in status area.
    geany_xml_encode_notify(document, replaced);
  }
}
