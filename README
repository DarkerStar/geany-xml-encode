Geany XML encode plugin
=======================


What is it?
-----------

_Geany XML encode plugin_ is a plugin for [Geany](http://www.geany.org/)
that adds new menu commands to convert XML special characters (“`&`”,
“`<`”, “`>`”, “`'`” and “`"`”) in a section, or the whole document, into
XML character entities.


Latest version
--------------

The latest release can be downloaded from the [github project downloads
page](https://github.com/DarkerStar/geany-xml-encode/downloads).


Documentation
-------------

Once the plugin is installed, it may be activated by the Geany plugin
manager. Select Tools->Plugin Manager from the main menu, and you should
see the “XML Encode” plugin. Select it to activate it, then restart
Geany.

Once the plugin is active, there will be a new item in the Geany Tools
menu, called “Encode XML special characters” whenever there is a
document open in Geany. This item wil lead to a submenu with two
options: “Document” and “Selection”.

Both options do the same thing, but the first works on the whole
document, while the second only applies to the current selection (if
there is no selection, nothing is done). Depending on the option, all of
the special XML characters in the document or selection will be
converted to XML entity references.

The special XML characters are “`&`”, “`<`”, “`>`”, “`'`” and “`"`”.
These characters have special meaning in XML syntax, and there are
several places they cannot be used in text data without causing
problems. By converting them to entity references - “`&amp;`”,
“`&lt;`”, “`&gt;`”, “`&apos;`” and “`&quot;`” respectively - these
problems can be avoided.

This plugin does that conversion automatically, so that the selection or
document converted can be embedded as text data in an XML file without
problems. This is especially useful for embedding source code in (X)HTML
files.


Installation
------------

Normally, the package may be built and installed with the following
sequence of commands:

*   `./configure`
    
*   `make`
    
*   `make install`

If installation requires root privileges, then it may necessary to
change the last command to “`sudo make install`”, or to first request
root privileges with “`su`”, then run “`make install`”.

This sequence of commands will normally build the plugin and install it
in the default location for Geany plugins. All that should be necessary
then is to restart Geany, and the plugin should be available in the
plugin manager.

If Geany is in a non-standard location, it may be necessary to run the
configure script with the “`--with-geany-libdir`” option. For example:

*   `./configure --with-geany-libdir=/path/to/geany/libdir`

After that, the regular “`make`” and “`make install`” commands should
build the plugin and install it in the desired location.

In some cases, it may be required to run the “autogen.sh” script first.
This should normally only be run by developers to prepare the project
for the end user.

For more details, please see the file called “`INSTALL`”.


Development information
-----------------------

### __Why isn't this part of the geany-plugins project?__

I doubt they would be interested in such a trivial plugin. More likely
than not, there's already something in the standard Geany UI, or the
default plugins, or in the geany-plugins, that does this. I just haven't
been able to find it, and this took all of two afternoons to put
together, so... yeah.

But if there is nothing like it in the existing plugins or the standard
Geany functions, and if enough people think this is worth including,
then I'd be happy to port it over.

### __Why Autotools?__

Geany itself uses Autotools, as does the geany-plugins project.

### __Why C?__

The plugin's functions are so simple, there was simply no need for the
power of C++.

### __Known issues and potential improvements__

*   When the last character of the selection is a special character, it
    gets moved outside of the selection after converting. It should
    remain within the selection. (This applies to both document and
    selection conversions.)
    
*   A message could be displayed, possibly in the status bar at the
    bottom or in the status window, giving the number of entities
    converted, similar to how the normal Replace function works.
    
*   XML _de_code?
    
*   Currently the characters and entities are hardcoded in the source.
    Instead of that, they could be stored in the Geany configuration
    file, so that users have the option of changing the conversion
    behaviour. (For example, if they don't want “`'`” converted to
    “`&apos;`”.)
    
*   Especially if the above is implemented, perhaps the conversion
    options could be set in a configure dialog.
    
*   A help dialog could be implemented, even if all it does is give more
    info about the plugin.
    
*   Currently the conversion only works on single characters - and that
    means single-byte UTF-8 characters. For more generic replacements,
    perhaps the code could be redesigned to handle replacing strings.
    However, that's not a trivial change, and there are a lot of issues
    to take into account, like precedence (for example, if you want to
    replace “`x`” with one thing and “`xx`” with another, you'd have to
    give the latter higher precendence, or it will be treated as two
    “`x`”s rather than “`xx`”).
    
*   Rather than _just_ an XML entity encoder, perhaps a more generalized
    transformation plugin might be handy, with XML encoding being just
    one of a number of specialized transformations. But what other
    transformations might there be?


Licensing
---------

Please see the file called `COPYING`.


Contacts
--------

For contact information, check out the
[github project page](https://github.com/DarkerStar/geany-xml-encode).
