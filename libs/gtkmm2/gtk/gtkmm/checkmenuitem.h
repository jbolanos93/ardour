// -*- c++ -*-
// Generated by gtkmmproc -- DO NOT MODIFY!
#ifndef _GTKMM_CHECKMENUITEM_H
#define _GTKMM_CHECKMENUITEM_H


#include <glibmm.h>

/* $Id$ */

/* checkmenuitem.h
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

#include <gtkmm/menuitem.h>


#ifndef DOXYGEN_SHOULD_SKIP_THIS
typedef struct _GtkCheckMenuItem GtkCheckMenuItem;
typedef struct _GtkCheckMenuItemClass GtkCheckMenuItemClass;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */


namespace Gtk
{ class CheckMenuItem_Class; } // namespace Gtk
namespace Gtk
{

/** A menu item that maintains the state of a boolean value in addition to a Gtk::MenuItem's usual role in activating application code.
 * A check box indicating the state of the boolean value is displayed at the left side of the Gtk::MenuItem.
 * Activating the Gtk::MenuItem toggles the value.
 * @ingroup Widgets
 * @ingroup Menus
 */

class CheckMenuItem : public MenuItem
{
  public:
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  typedef CheckMenuItem CppObjectType;
  typedef CheckMenuItem_Class CppClassType;
  typedef GtkCheckMenuItem BaseObjectType;
  typedef GtkCheckMenuItemClass BaseClassType;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

  virtual ~CheckMenuItem();

#ifndef DOXYGEN_SHOULD_SKIP_THIS

private:
  friend class CheckMenuItem_Class;
  static CppClassType checkmenuitem_class_;

  // noncopyable
  CheckMenuItem(const CheckMenuItem&);
  CheckMenuItem& operator=(const CheckMenuItem&);

protected:
  explicit CheckMenuItem(const Glib::ConstructParams& construct_params);
  explicit CheckMenuItem(GtkCheckMenuItem* castitem);

#endif /* DOXYGEN_SHOULD_SKIP_THIS */

public:
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  static GType get_type()      G_GNUC_CONST;
  static GType get_base_type() G_GNUC_CONST;
#endif

  ///Provides access to the underlying C GtkObject.
  GtkCheckMenuItem*       gobj()       { return reinterpret_cast<GtkCheckMenuItem*>(gobject_); }

  ///Provides access to the underlying C GtkObject.
  const GtkCheckMenuItem* gobj() const { return reinterpret_cast<GtkCheckMenuItem*>(gobject_); }


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
  virtual void on_toggled();
#endif //GLIBMM_DEFAULT_SIGNAL_HANDLERS_ENABLED


private:

  
public:

  CheckMenuItem();
  explicit CheckMenuItem(const Glib::ustring& label, bool mnemonic = false);
  

  void set_active(bool state = true);
  
  /** Returns whether the check menu item is active. See
   * set_active().
   * @return <tt>true</tt> if the menu item is checked.
   */
  bool get_active() const;

  
  void toggled();

  
  /** If the user has selected a range of elements (such as some text or
   * spreadsheet cells) that are affected by a boolean setting, and the
   * current values in that range are inconsistent, you may want to
   * display the check in an "in between" state. This function turns on
   * "in between" display.  Normally you would turn off the inconsistent
   * state again if the user explicitly selects a setting. This has to be
   * done manually, set_inconsistent() only affects
   * visual appearance, it doesn't affect the semantics of the widget.
   * @param setting <tt>true</tt> to display an "inconsistent" third state check.
   */
  void set_inconsistent(bool setting = true);
  
  /** Retrieves the value set by set_inconsistent().
   * @return <tt>true</tt> if inconsistent.
   */
  bool get_inconsistent() const;

  
  /** Sets whether @a check_menu_item  is drawn like a Gtk::RadioMenuItem
   * 
   * @newin2p4
   * @param draw_as_radio Whether @a check_menu_item  is drawn like a Gtk::RadioMenuItem.
   */
  void set_draw_as_radio(bool draw_as_radio = true);
  
  /** Returns whether @a check_menu_item  looks like a Gtk::RadioMenuItem
   * @return Whether @a check_menu_item  looks like a Gtk::RadioMenuItem
   * 
   * @newin2p4.
   */
  bool get_draw_as_radio() const;
  
  /** Triggered when the item changes state
   * (Note : changing the item's state with set_active() will also trigger
   * this signal)
   */
  
/**
   * @par Prototype:
   * <tt>void %toggled()</tt>
   */

  Glib::SignalProxy0< void > signal_toggled();


  #ifdef GLIBMM_PROPERTIES_ENABLED
/** Whether the menu item is checked.
   *
   * You rarely need to use properties because there are get_ and set_ methods for almost all of them.
   * @return A PropertyProxy that allows you to get or set the property of the value, or receive notification when
   * the value of the property changes.
   */
  Glib::PropertyProxy<bool> property_active() ;
#endif //#GLIBMM_PROPERTIES_ENABLED

#ifdef GLIBMM_PROPERTIES_ENABLED
/** Whether the menu item is checked.
   *
   * You rarely need to use properties because there are get_ and set_ methods for almost all of them.
   * @return A PropertyProxy that allows you to get or set the property of the value, or receive notification when
   * the value of the property changes.
   */
  Glib::PropertyProxy_ReadOnly<bool> property_active() const;
#endif //#GLIBMM_PROPERTIES_ENABLED

  #ifdef GLIBMM_PROPERTIES_ENABLED
/** Whether to display an inconsistent state.
   *
   * You rarely need to use properties because there are get_ and set_ methods for almost all of them.
   * @return A PropertyProxy that allows you to get or set the property of the value, or receive notification when
   * the value of the property changes.
   */
  Glib::PropertyProxy<bool> property_inconsistent() ;
#endif //#GLIBMM_PROPERTIES_ENABLED

#ifdef GLIBMM_PROPERTIES_ENABLED
/** Whether to display an inconsistent state.
   *
   * You rarely need to use properties because there are get_ and set_ methods for almost all of them.
   * @return A PropertyProxy that allows you to get or set the property of the value, or receive notification when
   * the value of the property changes.
   */
  Glib::PropertyProxy_ReadOnly<bool> property_inconsistent() const;
#endif //#GLIBMM_PROPERTIES_ENABLED

  #ifdef GLIBMM_PROPERTIES_ENABLED
/** Whether the menu item looks like a radio menu item.
   *
   * You rarely need to use properties because there are get_ and set_ methods for almost all of them.
   * @return A PropertyProxy that allows you to get or set the property of the value, or receive notification when
   * the value of the property changes.
   */
  Glib::PropertyProxy<bool> property_draw_as_radio() ;
#endif //#GLIBMM_PROPERTIES_ENABLED

#ifdef GLIBMM_PROPERTIES_ENABLED
/** Whether the menu item looks like a radio menu item.
   *
   * You rarely need to use properties because there are get_ and set_ methods for almost all of them.
   * @return A PropertyProxy that allows you to get or set the property of the value, or receive notification when
   * the value of the property changes.
   */
  Glib::PropertyProxy_ReadOnly<bool> property_draw_as_radio() const;
#endif //#GLIBMM_PROPERTIES_ENABLED


protected:
  /** Triggered when the item is redrawn (e.g.after being toggled)
   * Overload this signal if you want to implement your own check item
   * look. Otherwise, you most likely don't care about it.
   * The GdkRectangle specifies the area of the widget which will get
   * redrawn.
   */
  #ifdef GLIBMM_VFUNCS_ENABLED
  virtual void draw_indicator_vfunc(GdkRectangle* area);
#endif //GLIBMM_VFUNCS_ENABLED


};

} /* namespace Gtk */


namespace Glib
{
  /** @relates Gtk::CheckMenuItem
   * @param object The C instance
   * @param take_copy False if the result should take ownership of the C instance. True if it should take a new copy or ref.
   * @result A C++ instance that wraps this C instance.
   */
  Gtk::CheckMenuItem* wrap(GtkCheckMenuItem* object, bool take_copy = false);
} //namespace Glib


#endif /* _GTKMM_CHECKMENUITEM_H */

