// -*- c++ -*-
#ifndef _GLIBMM_OBJECTBASE_H
#define _GLIBMM_OBJECTBASE_H

/* $Id: objectbase.h 779 2009-01-19 17:58:50Z murrayc $ */

/* Copyright 2002 The gtkmm Development Team
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free
 * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include <glibmm/signalproxy.h>
#include <glibmm/propertyproxy.h>
#include <glibmm/ustring.h>
#include <glibmm/value.h>
#include <glibmm/quark.h>
#include <sigc++/trackable.h>
#include <typeinfo>
#include <glibmmconfig.h>
#include <glibmm/debug.h>

#include <glibmmconfig.h>

GLIBMM_USING_STD(type_info)

#ifndef DOXYGEN_SHOULD_SKIP_THIS
extern "C" { typedef struct _GObject GObject; }
#endif


namespace Glib
{

#ifndef DOXYGEN_SHOULD_SKIP_THIS
class GSigConnectionNode;
#endif

//This inherits virtually from sigc::trackable so that people can multiply inherit glibmm classes from other sigc::trackable-derived classes.
//See bugzilla.gnome.org bug # 116280
/** Glib::ObjectBase is a common base class for Objects and Interfaces.
 *
 * This is used as virtual base class.  This means the ObjectBase
 * constructor runs before all others, either implicitly or explicitly.  Each of
 * the available constructors initializes custom_type_name_ in a different way.
 */
class GLIBMM_API ObjectBase : virtual public sigc::trackable
{
protected:
  /** This default constructor is called implicitly from the constructor of user-derived
   * classes, even if, for instance, Gtk::Button calls a different ObjectBase constructor.
   * This is normal behaviour for C++ virtual inheritance.
   * 
   * The GType name will be gtkmm__anonymous_custom_type.
   */
  ObjectBase();

  /** A derived constructor always overrides this choice.
   * The C++ language itself ensures that the constructor
   * is only invoked once.
   * 
   * All classes generated by gtkmmproc use this constructor, with custom_type_name = 0,
   * which essentially means it's not a custom type.  This is used to optimize
   * vfunc and signal handler callbacks -- since the C++ virtual methods are
   * not overridden, invocation can be skipped.
   *
   * The GType name will be @a custom_type_name.
   */
  explicit ObjectBase(const char* custom_type_name);

  /** This constructor is a special feature to allow creation of derived types on the
   * fly, without having to use g_object_new() manually.  This feature is
   * sometimes necessary, e.g. to implement a custom Gtk::CellRenderer.  The
   * neat trick with the virtual base class ctor makes it possible to reuse
   * the same direct base class' constructor as with non-custom types.
   *
   * The GType name will be @a custom_type_info.name().
   */
  explicit ObjectBase(const std::type_info& custom_type_info);

  virtual ~ObjectBase() = 0;

  // Called by Glib::Object and Glib::Interface constructors. See comments there.
  void initialize(GObject* castitem);

public:

  /// You probably want to use a specific property_*() accessor method instead.
  void set_property_value(const Glib::ustring& property_name, const Glib::ValueBase& value);

  /// You probably want to use a specific property_*() accessor method instead.
  void get_property_value(const Glib::ustring& property_name, Glib::ValueBase& value) const;

  /// You probably want to use a specific property_*() accessor method instead.
  template <class PropertyType>
  void set_property(const Glib::ustring& property_name, const PropertyType& value);

  /// You probably want to use a specific property_*() accessor method instead.
  template <class PropertyType>
  void get_property(const Glib::ustring& property_name, PropertyType& value) const;

  /** You can use the signal_changed() signal of the property proxy instead, 
   * but this is necessary when using the reduced API.
   *
   * See also connect_property_changed_with_return().
   */
  void connect_property_changed(const Glib::ustring& property_name, const sigc::slot<void>& slot);

  /** You can use the signal_changed() signal of the property proxy instead, 
   * but this is necessary when using the reduced API.
   *
   * This method was added because connect_property_changed() does not return a sigc::connection, 
   * and we could not break the ABI by changing that function.
   */
  sigc::connection connect_property_changed_with_return(const Glib::ustring& property_name, const sigc::slot<void>& slot);

  //TODO: Why are these virtual?
  /** Increment the reference count for this object.
   * You should never need to do this manually - use the object via a RefPtr instead.
   */
  virtual void reference() const;

  /** Decrement the reference count for this object.
   * You should never need to do this manually - use the object via a RefPtr instead.
   */
  virtual void unreference() const;

  ///Provides access to the underlying C GObject.
  inline GObject*       gobj()       { return gobject_; }

  ///Provides access to the underlying C GObject.
  inline const GObject* gobj() const { return gobject_; }

  /// Give a ref-ed copy to someone. Use for direct struct access.
  GObject* gobj_copy() const;

#ifndef DOXYGEN_SHOULD_SKIP_THIS

  /// This is for use by gtkmm wrappers only, and not by applications.
  static ObjectBase* _get_current_wrapper(GObject* object); //We keep this non-inline version, to preserve ABI.

  // This is commented-out because it's not clear yet whether it's a worthwhile optimization.
  /// This is for use by gtkmm wrappers only, and not by applications.
  //
  //inline static ObjectBase* _get_current_wrapper_inline(GObject* object)
  //{
  //  // This is what g_object_get_qdata does internally. However,
  //  // g_object_get_qdata does an addition G_IS_OBJECT(object) check that
  //  // needs three times as much time as the actual lookup.
  //  if(object)
  //    return static_cast<ObjectBase*>(g_datalist_id_get_data(&object->qdata, Glib::quark_));
  //  else
  //    return 0;
  //}

  bool _cpp_destruction_is_in_progress() const;
#endif //DOXYGEN_SHOULD_SKIP_THIS

protected:

#ifndef DOXYGEN_SHOULD_SKIP_THIS
  GObject*            gobject_; // the GLib/GDK/GTK+ object instance
  const char*         custom_type_name_;
  bool                cpp_destruction_in_progress_;

  bool is_anonymous_custom_() const;

public: //  is_derived_() must be public, so that overridden vfuncs and signal handlers can call it via ObjectBase.

  /// This is for use by gtkmm wrappers only, and not by applications.
  bool is_derived_() const; //We keep this non-inline version, to preserve ABI.

  //This is commented-out because it's not clear yet whether it's a worthwhile optimization.
  //
  /// This is for use by gtkmm wrappers only, and not by applications.
  //inline bool is_derived_inline_() const
  //{
  //  return (custom_type_name_ != 0);
  //}

protected:
  static  void destroy_notify_callback_(void* data);
  virtual void destroy_notify_();

  void _set_current_wrapper(GObject* object);
#endif //DOXYGEN_SHOULD_SKIP_THIS

private:
  // noncopyable
  ObjectBase(const ObjectBase&);
  ObjectBase& operator=(const ObjectBase&);

#ifndef DOXYGEN_SHOULD_SKIP_THIS
  virtual void set_manage(); // calls g_error()
#endif //DOXYGEN_SHOULD_SKIP_THIS

#ifndef DOXYGEN_SHOULD_SKIP_THIS
  friend class Glib::GSigConnectionNode; // for GSigConnectionNode::notify()
#endif
};

#ifndef DOXYGEN_SHOULD_SKIP_THIS

template <class PropertyType> inline
void ObjectBase::set_property(const Glib::ustring& property_name, const PropertyType& value)
{
  Glib::Value<PropertyType> property_value;
  property_value.init(Glib::Value<PropertyType>::value_type());

  property_value.set(value);
  this->set_property_value(property_name, property_value);
}

template <class PropertyType> inline
void ObjectBase::get_property(const Glib::ustring& property_name, PropertyType& value) const
{
  Glib::Value<PropertyType> property_value;
  property_value.init(Glib::Value<PropertyType>::value_type());

  this->get_property_value(property_name, property_value);

  value = property_value.get();
}

#endif /* DOXYGEN_SHOULD_SKIP_THIS */


bool _gobject_cppinstance_already_deleted(GObject* gobject);

} // namespace Glib


#endif /* _GLIBMM_OBJECTBASE_H */

