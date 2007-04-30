// Generated by gtkmmproc -- DO NOT MODIFY!


#include <gtkmm/toolitem.h>
#include <gtkmm/private/toolitem_p.h>

// -*- c++ -*-
/* $Id$ */

/* 
 *
 * Copyright 1998-2002 The gtkmm Development Team
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

#include <gtk/gtktoolitem.h>

namespace Gtk
{


} // namespace Gtk


namespace
{


static gboolean ToolItem_signal_create_menu_proxy_callback(GtkToolItem* self, void* data)
{
  using namespace Gtk;
  typedef sigc::slot< bool > SlotType;

  // Do not try to call a signal on a disassociated wrapper.
  if(Glib::ObjectBase::_get_current_wrapper((GObject*) self))
  {
    #ifdef GLIBMM_EXCEPTIONS_ENABLED
    try
    {
    #endif //GLIBMM_EXCEPTIONS_ENABLED
      if(sigc::slot_base *const slot = Glib::SignalProxyNormal::data_to_slot(data))
        return static_cast<int>((*static_cast<SlotType*>(slot))());
    #ifdef GLIBMM_EXCEPTIONS_ENABLED
    }
    catch(...)
    {
      Glib::exception_handlers_invoke();
    }
    #endif //GLIBMM_EXCEPTIONS_ENABLED
  }

  typedef gboolean RType;
  return RType();
}

static gboolean ToolItem_signal_create_menu_proxy_notify_callback(GtkToolItem* self,  void* data)
{
  using namespace Gtk;
  typedef sigc::slot< void > SlotType;

  // Do not try to call a signal on a disassociated wrapper.
  if(Glib::ObjectBase::_get_current_wrapper((GObject*) self))
  {
    #ifdef GLIBMM_EXCEPTIONS_ENABLED
    try
    {
    #endif //GLIBMM_EXCEPTIONS_ENABLED
      if(sigc::slot_base *const slot = Glib::SignalProxyNormal::data_to_slot(data))
        (*static_cast<SlotType*>(slot))();
    #ifdef GLIBMM_EXCEPTIONS_ENABLED
    }
    catch(...)
    {
      Glib::exception_handlers_invoke();
    }
    #endif //GLIBMM_EXCEPTIONS_ENABLED
  }

  typedef gboolean RType;
  return RType();
}

static const Glib::SignalProxyInfo ToolItem_signal_create_menu_proxy_info =
{
  "create_menu_proxy",
  (GCallback) &ToolItem_signal_create_menu_proxy_callback,
  (GCallback) &ToolItem_signal_create_menu_proxy_notify_callback
};


static const Glib::SignalProxyInfo ToolItem_signal_toolbar_reconfigured_info =
{
  "toolbar_reconfigured",
  (GCallback) &Glib::SignalProxyNormal::slot0_void_callback,
  (GCallback) &Glib::SignalProxyNormal::slot0_void_callback
};


static gboolean ToolItem_signal_set_tooltip_callback(GtkToolItem* self, GtkTooltips* p0,const gchar* p1,const gchar* p2,void* data)
{
  using namespace Gtk;
  typedef sigc::slot< bool,Tooltips*,const Glib::ustring&,const Glib::ustring& > SlotType;

  // Do not try to call a signal on a disassociated wrapper.
  if(Glib::ObjectBase::_get_current_wrapper((GObject*) self))
  {
    #ifdef GLIBMM_EXCEPTIONS_ENABLED
    try
    {
    #endif //GLIBMM_EXCEPTIONS_ENABLED
      if(sigc::slot_base *const slot = Glib::SignalProxyNormal::data_to_slot(data))
        return static_cast<int>((*static_cast<SlotType*>(slot))(Glib::wrap(p0)
, Glib::convert_const_gchar_ptr_to_ustring(p1)
, Glib::convert_const_gchar_ptr_to_ustring(p2)
));
    #ifdef GLIBMM_EXCEPTIONS_ENABLED
    }
    catch(...)
    {
      Glib::exception_handlers_invoke();
    }
    #endif //GLIBMM_EXCEPTIONS_ENABLED
  }

  typedef gboolean RType;
  return RType();
}

static gboolean ToolItem_signal_set_tooltip_notify_callback(GtkToolItem* self, GtkTooltips* p0,const gchar* p1,const gchar* p2, void* data)
{
  using namespace Gtk;
  typedef sigc::slot< void,Tooltips*,const Glib::ustring&,const Glib::ustring& > SlotType;

  // Do not try to call a signal on a disassociated wrapper.
  if(Glib::ObjectBase::_get_current_wrapper((GObject*) self))
  {
    #ifdef GLIBMM_EXCEPTIONS_ENABLED
    try
    {
    #endif //GLIBMM_EXCEPTIONS_ENABLED
      if(sigc::slot_base *const slot = Glib::SignalProxyNormal::data_to_slot(data))
        (*static_cast<SlotType*>(slot))(Glib::wrap(p0)
, Glib::convert_const_gchar_ptr_to_ustring(p1)
, Glib::convert_const_gchar_ptr_to_ustring(p2)
);
    #ifdef GLIBMM_EXCEPTIONS_ENABLED
    }
    catch(...)
    {
      Glib::exception_handlers_invoke();
    }
    #endif //GLIBMM_EXCEPTIONS_ENABLED
  }

  typedef gboolean RType;
  return RType();
}

static const Glib::SignalProxyInfo ToolItem_signal_set_tooltip_info =
{
  "set_tooltip",
  (GCallback) &ToolItem_signal_set_tooltip_callback,
  (GCallback) &ToolItem_signal_set_tooltip_notify_callback
};


} // anonymous namespace


namespace Glib
{

Gtk::ToolItem* wrap(GtkToolItem* object, bool take_copy)
{
  return dynamic_cast<Gtk::ToolItem *> (Glib::wrap_auto ((GObject*)(object), take_copy));
}

} /* namespace Glib */

namespace Gtk
{


/* The *_Class implementation: */

const Glib::Class& ToolItem_Class::init()
{
  if(!gtype_) // create the GType if necessary
  {
    // Glib::Class has to know the class init function to clone custom types.
    class_init_func_ = &ToolItem_Class::class_init_function;

    // This is actually just optimized away, apparently with no harm.
    // Make sure that the parent type has been created.
    //CppClassParent::CppObjectType::get_type();

    // Create the wrapper type, with the same class/instance size as the base type.
    register_derived_type(gtk_tool_item_get_type());

    // Add derived versions of interfaces, if the C type implements any interfaces:
  }

  return *this;
}

void ToolItem_Class::class_init_function(void* g_class, void* class_data)
{
  BaseClassType *const klass = static_cast<BaseClassType*>(g_class);
  CppClassParent::class_init_function(klass, class_data);

#ifdef GLIBMM_VFUNCS_ENABLED
#endif //GLIBMM_VFUNCS_ENABLED

#ifdef GLIBMM_DEFAULT_SIGNAL_HANDLERS_ENABLED
  klass->create_menu_proxy = &create_menu_proxy_callback;
  klass->toolbar_reconfigured = &toolbar_reconfigured_callback;
#endif //GLIBMM_DEFAULT_SIGNAL_HANDLERS_ENABLED
}

#ifdef GLIBMM_VFUNCS_ENABLED
#endif //GLIBMM_VFUNCS_ENABLED

#ifdef GLIBMM_DEFAULT_SIGNAL_HANDLERS_ENABLED
gboolean ToolItem_Class::create_menu_proxy_callback(GtkToolItem* self)
{
  CppObjectType *const obj = dynamic_cast<CppObjectType*>(
      Glib::ObjectBase::_get_current_wrapper((GObject*)self));

  // Non-gtkmmproc-generated custom classes implicitly call the default
  // Glib::ObjectBase constructor, which sets is_derived_. But gtkmmproc-
  // generated classes can use this optimisation, which avoids the unnecessary
  // parameter conversions if there is no possibility of the virtual function
  // being overridden:
  if(obj && obj->is_derived_())
  {
    #ifdef GLIBMM_EXCEPTIONS_ENABLED
    try // Trap C++ exceptions which would normally be lost because this is a C callback.
    {
    #endif //GLIBMM_EXCEPTIONS_ENABLED
      // Call the virtual member method, which derived classes might override.
      return static_cast<int>(obj->on_create_menu_proxy());
    #ifdef GLIBMM_EXCEPTIONS_ENABLED
    }
    catch(...)
    {
      Glib::exception_handlers_invoke();
    }
    #endif //GLIBMM_EXCEPTIONS_ENABLED
  }
  else
  {
    BaseClassType *const base = static_cast<BaseClassType*>(
        g_type_class_peek_parent(G_OBJECT_GET_CLASS(self)) // Get the parent class of the object class (The original underlying C class).
    );

    // Call the original underlying C function:
    if(base && base->create_menu_proxy)
      return (*base->create_menu_proxy)(self);
  }

  typedef gboolean RType;
  return RType();
}
void ToolItem_Class::toolbar_reconfigured_callback(GtkToolItem* self)
{
  CppObjectType *const obj = dynamic_cast<CppObjectType*>(
      Glib::ObjectBase::_get_current_wrapper((GObject*)self));

  // Non-gtkmmproc-generated custom classes implicitly call the default
  // Glib::ObjectBase constructor, which sets is_derived_. But gtkmmproc-
  // generated classes can use this optimisation, which avoids the unnecessary
  // parameter conversions if there is no possibility of the virtual function
  // being overridden:
  if(obj && obj->is_derived_())
  {
    #ifdef GLIBMM_EXCEPTIONS_ENABLED
    try // Trap C++ exceptions which would normally be lost because this is a C callback.
    {
    #endif //GLIBMM_EXCEPTIONS_ENABLED
      // Call the virtual member method, which derived classes might override.
      obj->on_toolbar_reconfigured();
    #ifdef GLIBMM_EXCEPTIONS_ENABLED
    }
    catch(...)
    {
      Glib::exception_handlers_invoke();
    }
    #endif //GLIBMM_EXCEPTIONS_ENABLED
  }
  else
  {
    BaseClassType *const base = static_cast<BaseClassType*>(
        g_type_class_peek_parent(G_OBJECT_GET_CLASS(self)) // Get the parent class of the object class (The original underlying C class).
    );

    // Call the original underlying C function:
    if(base && base->toolbar_reconfigured)
      (*base->toolbar_reconfigured)(self);
  }
}
#endif //GLIBMM_DEFAULT_SIGNAL_HANDLERS_ENABLED


Glib::ObjectBase* ToolItem_Class::wrap_new(GObject* o)
{
  return manage(new ToolItem((GtkToolItem*)(o)));

}


/* The implementation: */

ToolItem::ToolItem(const Glib::ConstructParams& construct_params)
:
  Gtk::Bin(construct_params)
{
  }

ToolItem::ToolItem(GtkToolItem* castitem)
:
  Gtk::Bin((GtkBin*)(castitem))
{
  }

ToolItem::~ToolItem()
{
  destroy_();
}

ToolItem::CppClassType ToolItem::toolitem_class_; // initialize static member

GType ToolItem::get_type()
{
  return toolitem_class_.init().get_type();
}

GType ToolItem::get_base_type()
{
  return gtk_tool_item_get_type();
}


ToolItem::ToolItem()
:
  Glib::ObjectBase(0), //Mark this class as gtkmmproc-generated, rather than a custom class, to allow vfunc optimisations.
  Gtk::Bin(Glib::ConstructParams(toolitem_class_.init()))
{
  }

void ToolItem::set_homogeneous(bool homogeneous)
{
gtk_tool_item_set_homogeneous(gobj(), static_cast<int>(homogeneous)); 
}

bool ToolItem::get_homogeneous() const
{
  return gtk_tool_item_get_homogeneous(const_cast<GtkToolItem*>(gobj()));
}

void ToolItem::set_expand(bool expand)
{
gtk_tool_item_set_expand(gobj(), static_cast<int>(expand)); 
}

bool ToolItem::get_expand() const
{
  return gtk_tool_item_get_expand(const_cast<GtkToolItem*>(gobj()));
}

void ToolItem::set_tooltip(Tooltips& tooltips, const Glib::ustring& tip_text, const Glib::ustring& tip_private)
{
gtk_tool_item_set_tooltip(gobj(), (tooltips).gobj(), tip_text.c_str(), tip_private.c_str()); 
}

void ToolItem::set_use_drag_window(bool use_drag_window)
{
gtk_tool_item_set_use_drag_window(gobj(), static_cast<int>(use_drag_window)); 
}

bool ToolItem::get_use_drag_window() const
{
  return gtk_tool_item_get_use_drag_window(const_cast<GtkToolItem*>(gobj()));
}

void ToolItem::set_visible_horizontal(bool visible_horizontal)
{
gtk_tool_item_set_visible_horizontal(gobj(), static_cast<int>(visible_horizontal)); 
}

bool ToolItem::get_visible_horizontal() const
{
  return gtk_tool_item_get_visible_horizontal(const_cast<GtkToolItem*>(gobj()));
}

void ToolItem::set_visible_vertical(bool visible_vertical)
{
gtk_tool_item_set_visible_vertical(gobj(), static_cast<int>(visible_vertical)); 
}

bool ToolItem::get_visible_vertical() const
{
  return gtk_tool_item_get_visible_vertical(const_cast<GtkToolItem*>(gobj()));
}

bool ToolItem::get_is_important() const
{
  return gtk_tool_item_get_is_important(const_cast<GtkToolItem*>(gobj()));
}

void ToolItem::set_is_important(bool is_important)
{
gtk_tool_item_set_is_important(gobj(), static_cast<int>(is_important)); 
}

IconSize ToolItem::get_icon_size() const
{
  return IconSize(static_cast<int>(gtk_tool_item_get_icon_size(const_cast<GtkToolItem*>(gobj()))));
}

Orientation ToolItem::get_orientation() const
{
  return ((Orientation)(gtk_tool_item_get_orientation(const_cast<GtkToolItem*>(gobj()))));
}

ToolbarStyle ToolItem::get_toolbar_style() const
{
  return ((ToolbarStyle)(gtk_tool_item_get_toolbar_style(const_cast<GtkToolItem*>(gobj()))));
}

ReliefStyle ToolItem::get_relief_style() const
{
  return ((ReliefStyle)(gtk_tool_item_get_relief_style(const_cast<GtkToolItem*>(gobj()))));
}

Widget* ToolItem::retrieve_proxy_menu_item()
{
  return Glib::wrap(gtk_tool_item_retrieve_proxy_menu_item(gobj()));
}

const Widget* ToolItem::retrieve_proxy_menu_item() const
{
  return const_cast<ToolItem*>(this)->retrieve_proxy_menu_item();
}

Widget* ToolItem::get_proxy_menu_item(const Glib::ustring& menu_item_id)
{
  return Glib::wrap(gtk_tool_item_get_proxy_menu_item(gobj(), menu_item_id.c_str()));
}

const Widget* ToolItem::get_proxy_menu_item(const Glib::ustring& menu_item_id) const
{
  return const_cast<ToolItem*>(this)->get_proxy_menu_item(menu_item_id);
}

void ToolItem::set_proxy_menu_item(const Glib::ustring& menu_item_id, Widget& menu_item)
{
gtk_tool_item_set_proxy_menu_item(gobj(), menu_item_id.c_str(), (menu_item).gobj()); 
}

void ToolItem::rebuild_menu()
{
gtk_tool_item_rebuild_menu(gobj()); 
}


Glib::SignalProxy0< bool > ToolItem::signal_create_menu_proxy()
{
  return Glib::SignalProxy0< bool >(this, &ToolItem_signal_create_menu_proxy_info);
}


Glib::SignalProxy0< void > ToolItem::signal_toolbar_reconfigured()
{
  return Glib::SignalProxy0< void >(this, &ToolItem_signal_toolbar_reconfigured_info);
}


Glib::SignalProxy3< bool,Tooltips*,const Glib::ustring&,const Glib::ustring& > ToolItem::signal_set_tooltip()
{
  return Glib::SignalProxy3< bool,Tooltips*,const Glib::ustring&,const Glib::ustring& >(this, &ToolItem_signal_set_tooltip_info);
}


#ifdef GLIBMM_PROPERTIES_ENABLED
Glib::PropertyProxy<bool> ToolItem::property_visible_horizontal() 
{
  return Glib::PropertyProxy<bool>(this, "visible-horizontal");
}
#endif //GLIBMM_PROPERTIES_ENABLED

#ifdef GLIBMM_PROPERTIES_ENABLED
Glib::PropertyProxy_ReadOnly<bool> ToolItem::property_visible_horizontal() const
{
  return Glib::PropertyProxy_ReadOnly<bool>(this, "visible-horizontal");
}
#endif //GLIBMM_PROPERTIES_ENABLED

#ifdef GLIBMM_PROPERTIES_ENABLED
Glib::PropertyProxy<bool> ToolItem::property_visible_vertical() 
{
  return Glib::PropertyProxy<bool>(this, "visible-vertical");
}
#endif //GLIBMM_PROPERTIES_ENABLED

#ifdef GLIBMM_PROPERTIES_ENABLED
Glib::PropertyProxy_ReadOnly<bool> ToolItem::property_visible_vertical() const
{
  return Glib::PropertyProxy_ReadOnly<bool>(this, "visible-vertical");
}
#endif //GLIBMM_PROPERTIES_ENABLED

#ifdef GLIBMM_PROPERTIES_ENABLED
Glib::PropertyProxy<bool> ToolItem::property_is_important() 
{
  return Glib::PropertyProxy<bool>(this, "is-important");
}
#endif //GLIBMM_PROPERTIES_ENABLED

#ifdef GLIBMM_PROPERTIES_ENABLED
Glib::PropertyProxy_ReadOnly<bool> ToolItem::property_is_important() const
{
  return Glib::PropertyProxy_ReadOnly<bool>(this, "is-important");
}
#endif //GLIBMM_PROPERTIES_ENABLED


#ifdef GLIBMM_DEFAULT_SIGNAL_HANDLERS_ENABLED
bool Gtk::ToolItem::on_create_menu_proxy()
{
  BaseClassType *const base = static_cast<BaseClassType*>(
      g_type_class_peek_parent(G_OBJECT_GET_CLASS(gobject_)) // Get the parent class of the object class (The original underlying C class).
  );

  if(base && base->create_menu_proxy)
    return (*base->create_menu_proxy)(gobj());

  typedef bool RType;
  return RType();
}
void Gtk::ToolItem::on_toolbar_reconfigured()
{
  BaseClassType *const base = static_cast<BaseClassType*>(
      g_type_class_peek_parent(G_OBJECT_GET_CLASS(gobject_)) // Get the parent class of the object class (The original underlying C class).
  );

  if(base && base->toolbar_reconfigured)
    (*base->toolbar_reconfigured)(gobj());
}
#endif //GLIBMM_DEFAULT_SIGNAL_HANDLERS_ENABLED

#ifdef GLIBMM_VFUNCS_ENABLED
#endif //GLIBMM_VFUNCS_ENABLED


} // namespace Gtk


