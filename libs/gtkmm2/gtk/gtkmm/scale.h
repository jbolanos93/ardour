// -*- c++ -*-
// Generated by gtkmmproc -- DO NOT MODIFY!
#ifndef _GTKMM_SCALE_H
#define _GTKMM_SCALE_H


#include <glibmm.h>

/* $Id$ */

/* scale.h
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

#include <gtkmm/range.h>


#ifndef DOXYGEN_SHOULD_SKIP_THIS
typedef struct _GtkScale GtkScale;
typedef struct _GtkScaleClass GtkScaleClass;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */


namespace Gtk
{ class Scale_Class; } // namespace Gtk
#ifndef DOXYGEN_SHOULD_SKIP_THIS
typedef struct _GtkVScale GtkVScale;
typedef struct _GtkVScaleClass GtkVScaleClass;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */


namespace Gtk
{ class VScale_Class; } // namespace Gtk
#ifndef DOXYGEN_SHOULD_SKIP_THIS
typedef struct _GtkHScale GtkHScale;
typedef struct _GtkHScaleClass GtkHScaleClass;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */


namespace Gtk
{ class HScale_Class; } // namespace Gtk
namespace Gtk
{

/** Abstract base clase for Gtk::HScale and Gtk::VScale.
 * 
 * A Gtk::Scale is a slider control used to select a numeric value. To use it,
 * you'll probably want to investigate the methods on its base class,
 * Gtk::Range, in addition to the methods for Gtk::Scale itself. To set the
 * value of a scale, you would normally use set_value(). To detect
 * changes to the value, you would normally use signal_value_changed().
 *
 * The Gtk::Scale widget is an abstract class, used only for deriving the
 * subclasses Gtk::HScale and Gtk::VScale, so you should instantiate them
 * instead.
 *
 * @ingroup Widgets
 */

class Scale : public Range
{
  public:
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  typedef Scale CppObjectType;
  typedef Scale_Class CppClassType;
  typedef GtkScale BaseObjectType;
  typedef GtkScaleClass BaseClassType;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

  virtual ~Scale();

#ifndef DOXYGEN_SHOULD_SKIP_THIS

private:
  friend class Scale_Class;
  static CppClassType scale_class_;

  // noncopyable
  Scale(const Scale&);
  Scale& operator=(const Scale&);

protected:
  explicit Scale(const Glib::ConstructParams& construct_params);
  explicit Scale(GtkScale* castitem);

#endif /* DOXYGEN_SHOULD_SKIP_THIS */

public:
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  static GType get_type()      G_GNUC_CONST;
  static GType get_base_type() G_GNUC_CONST;
#endif

  ///Provides access to the underlying C GtkObject.
  GtkScale*       gobj()       { return reinterpret_cast<GtkScale*>(gobject_); }

  ///Provides access to the underlying C GtkObject.
  const GtkScale* gobj() const { return reinterpret_cast<GtkScale*>(gobject_); }


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
  virtual Glib::ustring on_format_value(double value);
#endif //GLIBMM_DEFAULT_SIGNAL_HANDLERS_ENABLED


private:

protected:
  Scale();
public:
  
  /** Set the number of decimal digits.
   * 
   * This also causes the adjustment to be rounded off so the retrieved value
   * matches the value the user sees. Setting digits to 1 gives for example
   * 1.0, 2 gives 1.00, etc.
   */
  
  void set_digits(int digits);

  /** Get the number of decimal digits.
   */
  
  int get_digits() const;

  /** Set whether the current value is displayed as a string next to the slider. 
   */
  
  void set_draw_value(bool draw_value = true);

  /** Get whether the current value is displayed as a string next to the slider. 
   */
  
  bool get_draw_value() const;


  /** Set the position in which the value is displayed.
   */
  
  void set_value_pos(PositionType pos);

  /** Get the position in which the value is displayed.
   */
  
  PositionType get_value_pos() const;

  
  /** Gets the Pango::Layout used to display the scale. The returned object
   * is owned by the scale so does not need to be freed by the caller.
   * @return The Pango::Layout for this scale, or <tt>0</tt> if the draw_value property
   * is <tt>false</tt>.
   * 
   * @newin2p4.
   */
  Glib::RefPtr<Pango::Layout> get_layout();
  
  /** Gets the Pango::Layout used to display the scale. The returned object
   * is owned by the scale so does not need to be freed by the caller.
   * @return The Pango::Layout for this scale, or <tt>0</tt> if the draw_value property
   * is <tt>false</tt>.
   * 
   * @newin2p4.
   */
  Glib::RefPtr<const Pango::Layout> get_layout() const;
  
  /** Obtains the coordinates where the scale will draw the Pango::Layout
   * representing the text in the scale. Remember
   * when using the Pango::Layout function you need to convert to
   * and from pixels using PANGO_PIXELS() or Pango::SCALE. 
   * 
   * If the draw_value property is <tt>false</tt>, the return values are 
   * undefined.
   * 
   * @newin2p4
   * @param x Location to store X offset of layout, or <tt>0</tt>.
   * @param y Location to store Y offset of layout, or <tt>0</tt>.
   */
  void get_layout_offsets(int& x, int& y) const;
  
      
  /** Determines how the value is formatted.
   * 
   * This can be used to connect a custom function for determining how the
   * value is formatted. The function (or function object) is given a the value
   * as a double and should return the representation of it as a Glib::ustring.
   */ 
  
/**
   * @par Prototype:
   * <tt>Glib::ustring %format_value(double value)</tt>
   */

  Glib::SignalProxy1< Glib::ustring,double > signal_format_value();

  // TODO: When we can break ABI, this signal needs to be
  // Glib::ustring format_value(double value, bool& use_default_formatting), 
  // where use_default_formatting specifies whether the return value will actually be a null char*.

  /** Number of displayed decimal digits.
   */
  #ifdef GLIBMM_PROPERTIES_ENABLED
/** The number of decimal places that are displayed in the value.
   *
   * You rarely need to use properties because there are get_ and set_ methods for almost all of them.
   * @return A PropertyProxy that allows you to get or set the property of the value, or receive notification when
   * the value of the property changes.
   */
  Glib::PropertyProxy<int> property_digits() ;
#endif //#GLIBMM_PROPERTIES_ENABLED

#ifdef GLIBMM_PROPERTIES_ENABLED
/** The number of decimal places that are displayed in the value.
   *
   * You rarely need to use properties because there are get_ and set_ methods for almost all of them.
   * @return A PropertyProxy that allows you to get or set the property of the value, or receive notification when
   * the value of the property changes.
   */
  Glib::PropertyProxy_ReadOnly<int> property_digits() const;
#endif //#GLIBMM_PROPERTIES_ENABLED


  /** Whether to draw the value as a string next to slider.
   */
  #ifdef GLIBMM_PROPERTIES_ENABLED
/** Whether the current value is displayed as a string next to the slider.
   *
   * You rarely need to use properties because there are get_ and set_ methods for almost all of them.
   * @return A PropertyProxy that allows you to get or set the property of the value, or receive notification when
   * the value of the property changes.
   */
  Glib::PropertyProxy<bool> property_draw_value() ;
#endif //#GLIBMM_PROPERTIES_ENABLED

#ifdef GLIBMM_PROPERTIES_ENABLED
/** Whether the current value is displayed as a string next to the slider.
   *
   * You rarely need to use properties because there are get_ and set_ methods for almost all of them.
   * @return A PropertyProxy that allows you to get or set the property of the value, or receive notification when
   * the value of the property changes.
   */
  Glib::PropertyProxy_ReadOnly<bool> property_draw_value() const;
#endif //#GLIBMM_PROPERTIES_ENABLED


  /** The position in which the value is displayed.
   */
  #ifdef GLIBMM_PROPERTIES_ENABLED
/** The position in which the current value is displayed.
   *
   * You rarely need to use properties because there are get_ and set_ methods for almost all of them.
   * @return A PropertyProxy that allows you to get or set the property of the value, or receive notification when
   * the value of the property changes.
   */
  Glib::PropertyProxy<PositionType> property_value_pos() ;
#endif //#GLIBMM_PROPERTIES_ENABLED

#ifdef GLIBMM_PROPERTIES_ENABLED
/** The position in which the current value is displayed.
   *
   * You rarely need to use properties because there are get_ and set_ methods for almost all of them.
   * @return A PropertyProxy that allows you to get or set the property of the value, or receive notification when
   * the value of the property changes.
   */
  Glib::PropertyProxy_ReadOnly<PositionType> property_value_pos() const;
#endif //#GLIBMM_PROPERTIES_ENABLED


protected:

  #ifdef GLIBMM_VFUNCS_ENABLED
  virtual void draw_value_vfunc();
#endif //GLIBMM_VFUNCS_ENABLED

  
  virtual int calc_digits_(double step) const;


};

/** A vertical slider for selecting values.
 * 
 * The Gtk::VScale widget is used to allow the user to select a value using a
 * vertical slider. See the Gtk::Scale documentation for more information
 * on how to use a Gtk::VScale.
 *
 * @ingroup Widgets
 */

class VScale : public Scale
{
  public:
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  typedef VScale CppObjectType;
  typedef VScale_Class CppClassType;
  typedef GtkVScale BaseObjectType;
  typedef GtkVScaleClass BaseClassType;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

  virtual ~VScale();

#ifndef DOXYGEN_SHOULD_SKIP_THIS

private:
  friend class VScale_Class;
  static CppClassType vscale_class_;

  // noncopyable
  VScale(const VScale&);
  VScale& operator=(const VScale&);

protected:
  explicit VScale(const Glib::ConstructParams& construct_params);
  explicit VScale(GtkVScale* castitem);

#endif /* DOXYGEN_SHOULD_SKIP_THIS */

public:
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  static GType get_type()      G_GNUC_CONST;
  static GType get_base_type() G_GNUC_CONST;
#endif

  ///Provides access to the underlying C GtkObject.
  GtkVScale*       gobj()       { return reinterpret_cast<GtkVScale*>(gobject_); }

  ///Provides access to the underlying C GtkObject.
  const GtkVScale* gobj() const { return reinterpret_cast<GtkVScale*>(gobject_); }


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
  VScale();

  /**
  * Construct a VScale with the given minimum and maximum. The step size is the
  * distance the slider moves when the arrow keys are used to adjust the scale
  * value.
  */
  VScale(double min, double max, double step);
  explicit VScale(Adjustment& adjustment);
  

};

/** A horizontal slider for selecting values.
 *
 * The Gtk::HScale widget is used to allow the user to select a value using a
 * horizontal slider. See the Gtk::Scale documentation for more information
 * on how to use a Gtk::HScale.
 * 
 * @ingroup Widgets
 */

class HScale : public Scale
{
  public:
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  typedef HScale CppObjectType;
  typedef HScale_Class CppClassType;
  typedef GtkHScale BaseObjectType;
  typedef GtkHScaleClass BaseClassType;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

  virtual ~HScale();

#ifndef DOXYGEN_SHOULD_SKIP_THIS

private:
  friend class HScale_Class;
  static CppClassType hscale_class_;

  // noncopyable
  HScale(const HScale&);
  HScale& operator=(const HScale&);

protected:
  explicit HScale(const Glib::ConstructParams& construct_params);
  explicit HScale(GtkHScale* castitem);

#endif /* DOXYGEN_SHOULD_SKIP_THIS */

public:
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  static GType get_type()      G_GNUC_CONST;
  static GType get_base_type() G_GNUC_CONST;
#endif

  ///Provides access to the underlying C GtkObject.
  GtkHScale*       gobj()       { return reinterpret_cast<GtkHScale*>(gobject_); }

  ///Provides access to the underlying C GtkObject.
  const GtkHScale* gobj() const { return reinterpret_cast<GtkHScale*>(gobject_); }


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
  HScale();
  /**
  * Construct a HScale with the given minimum and maximum. The step size is the
  * distance the slider moves when the arrow keys are used to adjust the scale
  * value.
  */
  HScale(double min, double max, double step);
  explicit HScale(Adjustment& adjustment);
  

};

} /* namespace Gtk */


namespace Glib
{
  /** @relates Gtk::Scale
   * @param object The C instance
   * @param take_copy False if the result should take ownership of the C instance. True if it should take a new copy or ref.
   * @result A C++ instance that wraps this C instance.
   */
  Gtk::Scale* wrap(GtkScale* object, bool take_copy = false);
} //namespace Glib


namespace Glib
{
  /** @relates Gtk::VScale
   * @param object The C instance
   * @param take_copy False if the result should take ownership of the C instance. True if it should take a new copy or ref.
   * @result A C++ instance that wraps this C instance.
   */
  Gtk::VScale* wrap(GtkVScale* object, bool take_copy = false);
} //namespace Glib


namespace Glib
{
  /** @relates Gtk::HScale
   * @param object The C instance
   * @param take_copy False if the result should take ownership of the C instance. True if it should take a new copy or ref.
   * @result A C++ instance that wraps this C instance.
   */
  Gtk::HScale* wrap(GtkHScale* object, bool take_copy = false);
} //namespace Glib


#endif /* _GTKMM_SCALE_H */

