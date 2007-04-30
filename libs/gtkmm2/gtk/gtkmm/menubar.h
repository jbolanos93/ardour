// -*- c++ -*-
// Generated by gtkmmproc -- DO NOT MODIFY!
#ifndef _GTKMM_MENUBAR_H
#define _GTKMM_MENUBAR_H


#include <glibmm.h>

/* $Id$ */


/* menubar.h
 * 
 * Copyright (C) 1998-2002 The gtkmm Development Team
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the Free
 * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */
 
#include <gtkmm/menushell.h>
#include <gtkmm/menuitem.h>


#ifndef DOXYGEN_SHOULD_SKIP_THIS
typedef struct _GtkMenuBar GtkMenuBar;
typedef struct _GtkMenuBarClass GtkMenuBarClass;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */


namespace Gtk
{ class MenuBar_Class; } // namespace Gtk
namespace Gtk
{

/** A standard menu bar which usually holds Gtk::Menu submenu items.
 * The useful methods are in the base class - Gtk::MenuShell.
 * @ingroup Widgets
 * @ingroup Menus
 */

class MenuBar : public MenuShell
{
  public:
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  typedef MenuBar CppObjectType;
  typedef MenuBar_Class CppClassType;
  typedef GtkMenuBar BaseObjectType;
  typedef GtkMenuBarClass BaseClassType;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

  virtual ~MenuBar();

#ifndef DOXYGEN_SHOULD_SKIP_THIS

private:
  friend class MenuBar_Class;
  static CppClassType menubar_class_;

  // noncopyable
  MenuBar(const MenuBar&);
  MenuBar& operator=(const MenuBar&);

protected:
  explicit MenuBar(const Glib::ConstructParams& construct_params);
  explicit MenuBar(GtkMenuBar* castitem);

#endif /* DOXYGEN_SHOULD_SKIP_THIS */

public:
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  static GType get_type()      G_GNUC_CONST;
  static GType get_base_type() G_GNUC_CONST;
#endif

  ///Provides access to the underlying C GtkObject.
  GtkMenuBar*       gobj()       { return reinterpret_cast<GtkMenuBar*>(gobject_); }

  ///Provides access to the underlying C GtkObject.
  const GtkMenuBar* gobj() const { return reinterpret_cast<GtkMenuBar*>(gobject_); }


public:
  //C++ methods used to invoke GTK+ virtual functions:
#ifdef GLIBMM_VFUNCS_ENABLED
#endif //GLIBMM_VFUNCS_ENABLED

protected:
  //GTK+ Virtual Functions (override these to change behaviour):
#ifdef GLIBMM_VFUNCS_ENABLED
#endif //GLIBMM_VFUNCS_ENABLED

  //Default Signal Handlers::
#ifdef GLIBMM_DEFAULT_SIGNAL_HANDLERS_ENABLED
#endif //GLIBMM_DEFAULT_SIGNAL_HANDLERS_ENABLED


private:


public:
  MenuBar();

  // append, prepend and insert are defined in menushell

private:
  void init_accels_handler_(void);


};

} // namespace Gtk


namespace Glib
{
  /** @relates Gtk::MenuBar
   * @param object The C instance
   * @param take_copy False if the result should take ownership of the C instance. True if it should take a new copy or ref.
   * @result A C++ instance that wraps this C instance.
   */
  Gtk::MenuBar* wrap(GtkMenuBar* object, bool take_copy = false);
} //namespace Glib


#endif /* _GTKMM_MENUBAR_H */

