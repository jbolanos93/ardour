// -*- c++ -*-
// Generated by gtkmmproc -- DO NOT MODIFY!
#ifndef _GTKMM_BUTTON_H
#define _GTKMM_BUTTON_H


#include <glibmm.h>

/* $Id$ */

/* box.h
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

#include <gtkmm/bin.h>
#include <gtkmm/stockid.h>


#ifndef DOXYGEN_SHOULD_SKIP_THIS
typedef struct _GtkButton GtkButton;
typedef struct _GtkButtonClass GtkButtonClass;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */


namespace Gtk
{ class Button_Class; } // namespace Gtk
namespace Gtk
{

namespace Stock { struct BuiltinStockID; }


/** A widget that creates a signal when clicked on.
 *
 * This widget is generally used with a signal handler that is called when the button is pressed.
 * It can hold any valid child widget.  The most commonly used child is the Gtk::Label.
 *
 * @ingroup Widgets
 */

class Button : public Bin
{
  public:
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  typedef Button CppObjectType;
  typedef Button_Class CppClassType;
  typedef GtkButton BaseObjectType;
  typedef GtkButtonClass BaseClassType;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

  virtual ~Button();

#ifndef DOXYGEN_SHOULD_SKIP_THIS

private:
  friend class Button_Class;
  static CppClassType button_class_;

  // noncopyable
  Button(const Button&);
  Button& operator=(const Button&);

protected:
  explicit Button(const Glib::ConstructParams& construct_params);
  explicit Button(GtkButton* castitem);

#endif /* DOXYGEN_SHOULD_SKIP_THIS */

public:
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  static GType get_type()      G_GNUC_CONST;
  static GType get_base_type() G_GNUC_CONST;
#endif

  ///Provides access to the underlying C GtkObject.
  GtkButton*       gobj()       { return reinterpret_cast<GtkButton*>(gobject_); }

  ///Provides access to the underlying C GtkObject.
  const GtkButton* gobj() const { return reinterpret_cast<GtkButton*>(gobject_); }


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
  virtual void on_pressed();
  virtual void on_released();
  virtual void on_clicked();
  virtual void on_enter();
  virtual void on_leave();
  virtual void on_activate();
#endif //GLIBMM_DEFAULT_SIGNAL_HANDLERS_ENABLED


private:

public:

  /** Create an empty button.
   * With an empty button, you can Gtk::Button::add() a widget
   * such as a Gtk::Pixmap or Gtk::Box.
   *
   * If you just wish to add a Gtk::Label,
   * you may want to
   * use the Gtk::Button(const Glib::ustring& label) ctor
   * directly instead.
   */
  Button();


  /** Simple Push Button with label.
   * Create a button with the given label inside. You won't be able
   * to add a widget in this button since it already has a Gtk::Label
   * in it
   */
  explicit Button(const Glib::ustring& label, bool mnemonic = false);

  /** Creates a new Button containing the image and text from a stock item.
   * Stock ids have identifiers like Gtk::Stock::OK and Gtk::Stock::APPLY.
   * @param stock_id The stock item.
   */
  explicit Button(const StockID& stock_id);


  void pressed();
  
  void released();
  
  void clicked();
  
  void enter();
  
  void leave();

  
  void set_relief(ReliefStyle newstyle);
  
  ReliefStyle get_relief() const;

  
  /** Sets the text of the label of the button to @a str . This text is
   * also used to select the stock item if set_use_stock()
   * is used.
   * 
   * This will also clear any previously set labels.
   * @param label A string.
   */
  void set_label(const Glib::ustring& label);
  
  /** Fetches the text from the label of the button, as set by
   * set_label(). If the label text has not 
   * been set the return value will be <tt>0</tt>. This will be the 
   * case if you create an empty button with new() to 
   * use as a container.
   * @return The text of the label widget. This string is owned
   * by the widget and must not be modified or freed.
   */
  Glib::ustring get_label() const;
  
  /** If true, an underline in the text of the button label indicates
   * the next character should be used for the mnemonic accelerator key.
   * @param use_underline <tt>true</tt> if underlines in the text indicate mnemonics.
   */
  void set_use_underline(bool use_underline = true);
  
  /** Return value: <tt>true</tt> if an embedded underline in the button label
   * @return <tt>true</tt> if an embedded underline in the button label
   * indicates the mnemonic accelerator keys.
   */
  bool get_use_underline() const;
  
  /** If <tt>true</tt>, the label set on the button is used as a
   * stock id to select the stock item for the button.
   * @param use_stock <tt>true</tt> if the button should use a stock item.
   */
  void set_use_stock(bool use_stock = true);
  
  /** Return value: <tt>true</tt> if the button label is used to
   * @return <tt>true</tt> if the button label is used to
   * select a stock item instead of being
   * used directly as the label text.
   */
  bool get_use_stock() const;

  
  /** Sets whether the button will grab focus when it is clicked with the mouse.
   * Making mouse clicks not grab focus is useful in places like toolbars where
   * you don't want the keyboard focus removed from the main area of the
   * application.
   * 
   * @newin2p4
   * @param focus_on_click Whether the button grabs focus when clicked with the mouse.
   */
  void set_focus_on_click(bool focus_on_click = true);
  
  /** Return value: <tt>true</tt> if the button grabs focus when it is clicked with
   * @return <tt>true</tt> if the button grabs focus when it is clicked with
   * the mouse.
   * 
   * @newin2p4.
   */
  bool get_focus_on_click() const;

  
  /** Sets the alignment of the child. This property has no effect unless 
   * the child is a Gtk::Misc or a Gtk::Aligment.
   * 
   * @newin2p4
   * @param xalign The horizontal position of the child, 0.0 is left aligned, 
   * 1.0 is right aligned.
   * @param yalign The vertical position of the child, 0.0 is top aligned, 
   * 1.0 is bottom aligned.
   */
  void set_alignment(float xalign, float yalign);
  
  /** Gets the alignment of the child in the button.
   * 
   * @newin2p4
   * @param xalign Return location for horizontal alignment.
   * @param yalign Return location for vertical alignment.
   */
  void get_alignment(float& xalign, float& yalign);

  
  /** Set the image of @a button  to the given widget. Note that
   * it depends on the Gtk::Settings:gtk-button-images setting whether the
   * image will be displayed or not, you don't have to call
   * Gtk::Widget::show() on @a image  yourself.
   * 
   * @newin2p6
   * @param image A widget to set as the image for the button.
   */
  void set_image(Widget& image);
  
  /** Gets the widget that is currenty set as the image of @a button .
   *     This may have been explicitly set by set_image()
   *     or specified as a stock item to the constructor.
   * 
   *     @a newin2p6 
   */
  Widget* get_image();
  
  /** Gets the widget that is currenty set as the image of @a button .
   *     This may have been explicitly set by set_image()
   *     or specified as a stock item to the constructor.
   * 
   *     @a newin2p6 
   */
  const Widget* get_image() const;

  
  /** Sets the position of the image relative to the text 
   * inside the button.
   * 
   * @newin2p10
   * @param position The position.
   */
  void set_image_position(PositionType position);
  
  /** Gets the position of the image relative to the text 
   * inside the button.
   * @return The position
   * 
   * @newin2p10.
   */
  PositionType get_image_position() const;

  
  /**
   * @par Prototype:
   * <tt>void on_my_%pressed()</tt>
   */

  Glib::SignalProxy0< void > signal_pressed();

  
  /**
   * @par Prototype:
   * <tt>void on_my_%released()</tt>
   */

  Glib::SignalProxy0< void > signal_released();

  
  /**
   * @par Prototype:
   * <tt>void on_my_%clicked()</tt>
   */

  Glib::SignalProxy0< void > signal_clicked();

  
  /**
   * @par Prototype:
   * <tt>void on_my_%enter()</tt>
   */

  Glib::SignalProxy0< void > signal_enter();

  
  /**
   * @par Prototype:
   * <tt>void on_my_%leave()</tt>
   */

  Glib::SignalProxy0< void > signal_leave();

  
  /**
   * @par Prototype:
   * <tt>void on_my_%activate()</tt>
   */

  Glib::SignalProxy0< void > signal_activate();


  #ifdef GLIBMM_PROPERTIES_ENABLED
/** Text of the label widget inside the button
   *
   * You rarely need to use properties because there are get_ and set_ methods for almost all of them.
   * @return A PropertyProxy that allows you to get or set the property of the value, or receive notification when
   * the value of the property changes.
   */
  Glib::PropertyProxy<Glib::ustring> property_label() ;
#endif //#GLIBMM_PROPERTIES_ENABLED

#ifdef GLIBMM_PROPERTIES_ENABLED
/** Text of the label widget inside the button
   *
   * You rarely need to use properties because there are get_ and set_ methods for almost all of them.
   * @return A PropertyProxy that allows you to get or set the property of the value, or receive notification when
   * the value of the property changes.
   */
  Glib::PropertyProxy_ReadOnly<Glib::ustring> property_label() const;
#endif //#GLIBMM_PROPERTIES_ENABLED

  #ifdef GLIBMM_PROPERTIES_ENABLED
/** The border relief style.
   *
   * You rarely need to use properties because there are get_ and set_ methods for almost all of them.
   * @return A PropertyProxy that allows you to get or set the property of the value, or receive notification when
   * the value of the property changes.
   */
  Glib::PropertyProxy<ReliefStyle> property_relief() ;
#endif //#GLIBMM_PROPERTIES_ENABLED

#ifdef GLIBMM_PROPERTIES_ENABLED
/** The border relief style.
   *
   * You rarely need to use properties because there are get_ and set_ methods for almost all of them.
   * @return A PropertyProxy that allows you to get or set the property of the value, or receive notification when
   * the value of the property changes.
   */
  Glib::PropertyProxy_ReadOnly<ReliefStyle> property_relief() const;
#endif //#GLIBMM_PROPERTIES_ENABLED

  #ifdef GLIBMM_PROPERTIES_ENABLED
/** If set
   *
   * You rarely need to use properties because there are get_ and set_ methods for almost all of them.
   * @return A PropertyProxy that allows you to get or set the property of the value, or receive notification when
   * the value of the property changes.
   */
  Glib::PropertyProxy<bool> property_use_underline() ;
#endif //#GLIBMM_PROPERTIES_ENABLED

#ifdef GLIBMM_PROPERTIES_ENABLED
/** If set
   *
   * You rarely need to use properties because there are get_ and set_ methods for almost all of them.
   * @return A PropertyProxy that allows you to get or set the property of the value, or receive notification when
   * the value of the property changes.
   */
  Glib::PropertyProxy_ReadOnly<bool> property_use_underline() const;
#endif //#GLIBMM_PROPERTIES_ENABLED

  #ifdef GLIBMM_PROPERTIES_ENABLED
/** If set
   *
   * You rarely need to use properties because there are get_ and set_ methods for almost all of them.
   * @return A PropertyProxy that allows you to get or set the property of the value, or receive notification when
   * the value of the property changes.
   */
  Glib::PropertyProxy<bool> property_use_stock() ;
#endif //#GLIBMM_PROPERTIES_ENABLED

#ifdef GLIBMM_PROPERTIES_ENABLED
/** If set
   *
   * You rarely need to use properties because there are get_ and set_ methods for almost all of them.
   * @return A PropertyProxy that allows you to get or set the property of the value, or receive notification when
   * the value of the property changes.
   */
  Glib::PropertyProxy_ReadOnly<bool> property_use_stock() const;
#endif //#GLIBMM_PROPERTIES_ENABLED

  #ifdef GLIBMM_PROPERTIES_ENABLED
/** Whether the button grabs focus when it is clicked with the mouse.
   *
   * You rarely need to use properties because there are get_ and set_ methods for almost all of them.
   * @return A PropertyProxy that allows you to get or set the property of the value, or receive notification when
   * the value of the property changes.
   */
  Glib::PropertyProxy<bool> property_focus_on_click() ;
#endif //#GLIBMM_PROPERTIES_ENABLED

#ifdef GLIBMM_PROPERTIES_ENABLED
/** Whether the button grabs focus when it is clicked with the mouse.
   *
   * You rarely need to use properties because there are get_ and set_ methods for almost all of them.
   * @return A PropertyProxy that allows you to get or set the property of the value, or receive notification when
   * the value of the property changes.
   */
  Glib::PropertyProxy_ReadOnly<bool> property_focus_on_click() const;
#endif //#GLIBMM_PROPERTIES_ENABLED

  #ifdef GLIBMM_PROPERTIES_ENABLED
/** Horizontal position of child in available space. 0.0 is left aligned
   *
   * You rarely need to use properties because there are get_ and set_ methods for almost all of them.
   * @return A PropertyProxy that allows you to get or set the property of the value, or receive notification when
   * the value of the property changes.
   */
  Glib::PropertyProxy<float> property_xalign() ;
#endif //#GLIBMM_PROPERTIES_ENABLED

#ifdef GLIBMM_PROPERTIES_ENABLED
/** Horizontal position of child in available space. 0.0 is left aligned
   *
   * You rarely need to use properties because there are get_ and set_ methods for almost all of them.
   * @return A PropertyProxy that allows you to get or set the property of the value, or receive notification when
   * the value of the property changes.
   */
  Glib::PropertyProxy_ReadOnly<float> property_xalign() const;
#endif //#GLIBMM_PROPERTIES_ENABLED

  #ifdef GLIBMM_PROPERTIES_ENABLED
/** Vertical position of child in available space. 0.0 is top aligned
   *
   * You rarely need to use properties because there are get_ and set_ methods for almost all of them.
   * @return A PropertyProxy that allows you to get or set the property of the value, or receive notification when
   * the value of the property changes.
   */
  Glib::PropertyProxy<float> property_yalign() ;
#endif //#GLIBMM_PROPERTIES_ENABLED

#ifdef GLIBMM_PROPERTIES_ENABLED
/** Vertical position of child in available space. 0.0 is top aligned
   *
   * You rarely need to use properties because there are get_ and set_ methods for almost all of them.
   * @return A PropertyProxy that allows you to get or set the property of the value, or receive notification when
   * the value of the property changes.
   */
  Glib::PropertyProxy_ReadOnly<float> property_yalign() const;
#endif //#GLIBMM_PROPERTIES_ENABLED

  #ifdef GLIBMM_PROPERTIES_ENABLED
/** Child widget to appear next to the button text.
   *
   * You rarely need to use properties because there are get_ and set_ methods for almost all of them.
   * @return A PropertyProxy that allows you to get or set the property of the value, or receive notification when
   * the value of the property changes.
   */
  Glib::PropertyProxy<Gtk::Widget*> property_image() ;
#endif //#GLIBMM_PROPERTIES_ENABLED

#ifdef GLIBMM_PROPERTIES_ENABLED
/** Child widget to appear next to the button text.
   *
   * You rarely need to use properties because there are get_ and set_ methods for almost all of them.
   * @return A PropertyProxy that allows you to get or set the property of the value, or receive notification when
   * the value of the property changes.
   */
  Glib::PropertyProxy_ReadOnly<Gtk::Widget*> property_image() const;
#endif //#GLIBMM_PROPERTIES_ENABLED

  #ifdef GLIBMM_PROPERTIES_ENABLED
/** The position of the image relative to the text.
   *
   * You rarely need to use properties because there are get_ and set_ methods for almost all of them.
   * @return A PropertyProxy that allows you to get or set the property of the value, or receive notification when
   * the value of the property changes.
   */
  Glib::PropertyProxy<PositionType> property_image_position() ;
#endif //#GLIBMM_PROPERTIES_ENABLED

#ifdef GLIBMM_PROPERTIES_ENABLED
/** The position of the image relative to the text.
   *
   * You rarely need to use properties because there are get_ and set_ methods for almost all of them.
   * @return A PropertyProxy that allows you to get or set the property of the value, or receive notification when
   * the value of the property changes.
   */
  Glib::PropertyProxy_ReadOnly<PositionType> property_image_position() const;
#endif //#GLIBMM_PROPERTIES_ENABLED


};

/*! A Gtk::Button example.
 * Example 1: @link book/buttons/button/buttons.h @endlink
 * Example 2: @link book/buttons/button/buttons.cc @endlink
 * Example 3: @link book/buttons/button/main.cc @endlink
 */

} // namespace Gtk


namespace Glib
{
  /** A Glib::wrap() method for this object.
   * 
   * @param object The C instance.
   * @param take_copy False if the result should take ownership of the C instance. True if it should take a new copy or ref.
   * @result A C++ instance that wraps this C instance.
   *
   * @relates Gtk::Button
   */
  Gtk::Button* wrap(GtkButton* object, bool take_copy = false);
} //namespace Glib


#endif /* _GTKMM_BUTTON_H */

