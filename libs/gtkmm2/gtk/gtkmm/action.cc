// Generated by gtkmmproc -- DO NOT MODIFY!


#include <gtkmm/action.h>
#include <gtkmm/private/action_p.h>

// -*- c++ -*-
/* $Id$ */

/* Copyright 2003 The gtkmm Development Team
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

#include <gtk/gtkaction.h>

#include <gtkmm/menuitem.h>
#include <gtkmm/toolitem.h>
#include <gtkmm/image.h>
#include <gtkmm/widget.h>

typedef Gtk::Action Action; 

namespace Gtk
{

Action::Action(const Glib::ustring& name, const Gtk::StockID& stock_id, const Glib::ustring& label, const Glib::ustring& tooltip)
:
  Glib::ObjectBase(0), //Mark this class as gtkmmproc-generated, rather than a custom class, to allow vfunc optimisations.
  Glib::Object(Glib::ConstructParams(action_class_.init(), "name",name.c_str(),"stock_id",stock_id.get_c_str(),"label",(label.empty() ? 0 : label.c_str()),"tooltip",(tooltip.empty() ? 0 : tooltip.c_str()), (char*) 0))
{}

Glib::RefPtr<Action> Action::create(const Glib::ustring& name, const Glib::ustring& label, const Glib::ustring& tooltip)
{
  return Glib::RefPtr<Action>( new Action(name, Gtk::StockID(), label, tooltip) );
}

Glib::RefPtr<Action> Action::create(const Glib::ustring& name, const Gtk::StockID& stock_id, const Glib::ustring& label, const Glib::ustring& tooltip)
{
  return Glib::RefPtr<Action>( new Action(name, stock_id, label, tooltip) );
}


void Action::set_tooltip(const Glib::ustring& tooltip)
{
#ifdef GLIBMM_PROPERTIES_ENABLED
  property_tooltip() = tooltip;
#else
  set_property("tooltip", tooltip);
#endif
}


} // namespace Gtk


namespace
{


static const Glib::SignalProxyInfo Action_signal_activate_info =
{
  "activate",
  (GCallback) &Glib::SignalProxyNormal::slot0_void_callback,
  (GCallback) &Glib::SignalProxyNormal::slot0_void_callback
};


} // anonymous namespace


namespace Glib
{

Glib::RefPtr<Gtk::Action> wrap(GtkAction* object, bool take_copy)
{
  return Glib::RefPtr<Gtk::Action>( dynamic_cast<Gtk::Action*> (Glib::wrap_auto ((GObject*)(object), take_copy)) );
  //We use dynamic_cast<> in case of multiple inheritance.
}

} /* namespace Glib */


namespace Gtk
{


/* The *_Class implementation: */

const Glib::Class& Action_Class::init()
{
  if(!gtype_) // create the GType if necessary
  {
    // Glib::Class has to know the class init function to clone custom types.
    class_init_func_ = &Action_Class::class_init_function;

    // This is actually just optimized away, apparently with no harm.
    // Make sure that the parent type has been created.
    //CppClassParent::CppObjectType::get_type();

    // Create the wrapper type, with the same class/instance size as the base type.
    register_derived_type(gtk_action_get_type());

    // Add derived versions of interfaces, if the C type implements any interfaces:
  }

  return *this;
}

void Action_Class::class_init_function(void* g_class, void* class_data)
{
  BaseClassType *const klass = static_cast<BaseClassType*>(g_class);
  CppClassParent::class_init_function(klass, class_data);

#ifdef GLIBMM_VFUNCS_ENABLED
  klass->create_menu_item = &create_menu_item_vfunc_callback;
  klass->create_tool_item = &create_tool_item_vfunc_callback;
  klass->connect_proxy = &connect_proxy_vfunc_callback;
  klass->disconnect_proxy = &disconnect_proxy_vfunc_callback;
#endif //GLIBMM_VFUNCS_ENABLED

#ifdef GLIBMM_DEFAULT_SIGNAL_HANDLERS_ENABLED
  klass->activate = &activate_callback;
#endif //GLIBMM_DEFAULT_SIGNAL_HANDLERS_ENABLED
}

#ifdef GLIBMM_VFUNCS_ENABLED
GtkWidget* Action_Class::create_menu_item_vfunc_callback(GtkAction* self)
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
      return (GtkWidget*)Glib::unwrap(obj->create_menu_item_vfunc());
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
    if(base && base->create_menu_item)
      return (*base->create_menu_item)(self);
  }

  typedef GtkWidget* RType;
  return RType();
}
GtkWidget* Action_Class::create_tool_item_vfunc_callback(GtkAction* self)
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
      return (GtkWidget*)Glib::unwrap(obj->create_tool_item_vfunc());
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
    if(base && base->create_tool_item)
      return (*base->create_tool_item)(self);
  }

  typedef GtkWidget* RType;
  return RType();
}
void Action_Class::connect_proxy_vfunc_callback(GtkAction* self, GtkWidget* proxy)
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
      obj->connect_proxy_vfunc(Glib::wrap(proxy)
);
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
    if(base && base->connect_proxy)
      (*base->connect_proxy)(self, proxy);
  }
}
void Action_Class::disconnect_proxy_vfunc_callback(GtkAction* self, GtkWidget* proxy)
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
      obj->disconnect_proxy_vfunc(Glib::wrap(proxy)
);
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
    if(base && base->disconnect_proxy)
      (*base->disconnect_proxy)(self, proxy);
  }
}
#endif //GLIBMM_VFUNCS_ENABLED

#ifdef GLIBMM_DEFAULT_SIGNAL_HANDLERS_ENABLED
void Action_Class::activate_callback(GtkAction* self)
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
      obj->on_activate();
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
    if(base && base->activate)
      (*base->activate)(self);
  }
}
#endif //GLIBMM_DEFAULT_SIGNAL_HANDLERS_ENABLED


Glib::ObjectBase* Action_Class::wrap_new(GObject* object)
{
  return new Action((GtkAction*)object);
}


/* The implementation: */

GtkAction* Action::gobj_copy()
{
  reference();
  return gobj();
}

Action::Action(const Glib::ConstructParams& construct_params)
:
  Glib::Object(construct_params)
{}

Action::Action(GtkAction* castitem)
:
  Glib::Object((GObject*)(castitem))
{}

Action::~Action()
{}


Action::CppClassType Action::action_class_; // initialize static member

GType Action::get_type()
{
  return action_class_.init().get_type();
}

GType Action::get_base_type()
{
  return gtk_action_get_type();
}


Action::Action()
:
  Glib::ObjectBase(0), //Mark this class as gtkmmproc-generated, rather than a custom class, to allow vfunc optimisations.
  Glib::Object(Glib::ConstructParams(action_class_.init()))
{
  }

Glib::RefPtr<Action> Action::create()
{
  return Glib::RefPtr<Action>( new Action() );
}
Glib::ustring Action::get_name() const
{
  return Glib::convert_const_gchar_ptr_to_ustring(gtk_action_get_name(const_cast<GtkAction*>(gobj())));
}

bool Action::is_sensitive() const
{
  return gtk_action_is_sensitive(const_cast<GtkAction*>(gobj()));
}

bool Action::get_sensitive() const
{
  return gtk_action_get_sensitive(const_cast<GtkAction*>(gobj()));
}

void Action::set_sensitive(bool sensitive)
{
gtk_action_set_sensitive(gobj(), static_cast<int>(sensitive)); 
}

bool Action::is_visible() const
{
  return gtk_action_is_visible(const_cast<GtkAction*>(gobj()));
}

bool Action::get_visible() const
{
  return gtk_action_get_visible(const_cast<GtkAction*>(gobj()));
}

void Action::set_visible(bool visible)
{
gtk_action_set_visible(gobj(), static_cast<int>(visible)); 
}

void Action::activate()
{
gtk_action_activate(gobj()); 
}

Image* Action::create_icon(IconSize icon_size)
{
  return Glib::wrap((GtkImage*)(gtk_action_create_icon(gobj(), static_cast<GtkIconSize>(int(icon_size)))));
}

MenuItem* Action::create_menu_item()
{
  return Glib::wrap((GtkMenuItem*)(gtk_action_create_menu_item(gobj())));
}

ToolItem* Action::create_tool_item()
{
  return Glib::wrap((GtkToolItem*)(gtk_action_create_tool_item(gobj())));
}

void Action::connect_proxy(Widget& proxy)
{
gtk_action_connect_proxy(gobj(), (proxy).gobj()); 
}

void Action::disconnect_proxy(Widget& proxy)
{
gtk_action_disconnect_proxy(gobj(), (proxy).gobj()); 
}

Glib::SListHandle<Widget*> Action::get_proxies()
{
  return Glib::SListHandle<Widget*>(gtk_action_get_proxies(gobj()), Glib::OWNERSHIP_NONE);
}

Glib::SListHandle<const Widget*> Action::get_proxies() const
{
  return Glib::SListHandle<const Widget*>(gtk_action_get_proxies(const_cast<GtkAction*>(gobj())), Glib::OWNERSHIP_NONE);
}

void Action::connect_accelerator()
{
gtk_action_connect_accelerator(gobj()); 
}

void Action::disconnect_accelerator()
{
gtk_action_disconnect_accelerator(gobj()); 
}

Glib::ustring Action::get_accel_path() const
{
  return Glib::convert_const_gchar_ptr_to_ustring(gtk_action_get_accel_path(const_cast<GtkAction*>(gobj())));
}

void Action::set_accel_path(const Glib::ustring& accel_path)
{
gtk_action_set_accel_path(gobj(), accel_path.c_str()); 
}

void Action::set_accel_group(const Glib::RefPtr<AccelGroup>& accel_group)
{
gtk_action_set_accel_group(gobj(), Glib::unwrap(accel_group)); 
}

void Action::block_activate_from(Widget& proxy)
{
gtk_action_block_activate_from(gobj(), (proxy).gobj()); 
}

void Action::unblock_activate_from(Widget& proxy)
{
gtk_action_unblock_activate_from(gobj(), (proxy).gobj()); 
}


Glib::SignalProxy0< void > Action::signal_activate()
{
  return Glib::SignalProxy0< void >(this, &Action_signal_activate_info);
}


#ifdef GLIBMM_PROPERTIES_ENABLED
Glib::PropertyProxy_ReadOnly<Glib::ustring> Action::property_name() const
{
  return Glib::PropertyProxy_ReadOnly<Glib::ustring>(this, "name");
}
#endif //GLIBMM_PROPERTIES_ENABLED

#ifdef GLIBMM_PROPERTIES_ENABLED
Glib::PropertyProxy<Glib::ustring> Action::property_label() 
{
  return Glib::PropertyProxy<Glib::ustring>(this, "label");
}
#endif //GLIBMM_PROPERTIES_ENABLED

#ifdef GLIBMM_PROPERTIES_ENABLED
Glib::PropertyProxy_ReadOnly<Glib::ustring> Action::property_label() const
{
  return Glib::PropertyProxy_ReadOnly<Glib::ustring>(this, "label");
}
#endif //GLIBMM_PROPERTIES_ENABLED

#ifdef GLIBMM_PROPERTIES_ENABLED
Glib::PropertyProxy<Glib::ustring> Action::property_short_label() 
{
  return Glib::PropertyProxy<Glib::ustring>(this, "short-label");
}
#endif //GLIBMM_PROPERTIES_ENABLED

#ifdef GLIBMM_PROPERTIES_ENABLED
Glib::PropertyProxy_ReadOnly<Glib::ustring> Action::property_short_label() const
{
  return Glib::PropertyProxy_ReadOnly<Glib::ustring>(this, "short-label");
}
#endif //GLIBMM_PROPERTIES_ENABLED

#ifdef GLIBMM_PROPERTIES_ENABLED
Glib::PropertyProxy<Glib::ustring> Action::property_tooltip() 
{
  return Glib::PropertyProxy<Glib::ustring>(this, "tooltip");
}
#endif //GLIBMM_PROPERTIES_ENABLED

#ifdef GLIBMM_PROPERTIES_ENABLED
Glib::PropertyProxy_ReadOnly<Glib::ustring> Action::property_tooltip() const
{
  return Glib::PropertyProxy_ReadOnly<Glib::ustring>(this, "tooltip");
}
#endif //GLIBMM_PROPERTIES_ENABLED

#ifdef GLIBMM_PROPERTIES_ENABLED
Glib::PropertyProxy<StockID> Action::property_stock_id() 
{
  return Glib::PropertyProxy<StockID>(this, "stock-id");
}
#endif //GLIBMM_PROPERTIES_ENABLED

#ifdef GLIBMM_PROPERTIES_ENABLED
Glib::PropertyProxy_ReadOnly<StockID> Action::property_stock_id() const
{
  return Glib::PropertyProxy_ReadOnly<StockID>(this, "stock-id");
}
#endif //GLIBMM_PROPERTIES_ENABLED

#ifdef GLIBMM_PROPERTIES_ENABLED
Glib::PropertyProxy<bool> Action::property_visible_horizontal() 
{
  return Glib::PropertyProxy<bool>(this, "visible-horizontal");
}
#endif //GLIBMM_PROPERTIES_ENABLED

#ifdef GLIBMM_PROPERTIES_ENABLED
Glib::PropertyProxy_ReadOnly<bool> Action::property_visible_horizontal() const
{
  return Glib::PropertyProxy_ReadOnly<bool>(this, "visible-horizontal");
}
#endif //GLIBMM_PROPERTIES_ENABLED

#ifdef GLIBMM_PROPERTIES_ENABLED
Glib::PropertyProxy<bool> Action::property_visible_vertical() 
{
  return Glib::PropertyProxy<bool>(this, "visible-vertical");
}
#endif //GLIBMM_PROPERTIES_ENABLED

#ifdef GLIBMM_PROPERTIES_ENABLED
Glib::PropertyProxy_ReadOnly<bool> Action::property_visible_vertical() const
{
  return Glib::PropertyProxy_ReadOnly<bool>(this, "visible-vertical");
}
#endif //GLIBMM_PROPERTIES_ENABLED

#ifdef GLIBMM_PROPERTIES_ENABLED
Glib::PropertyProxy<bool> Action::property_is_important() 
{
  return Glib::PropertyProxy<bool>(this, "is-important");
}
#endif //GLIBMM_PROPERTIES_ENABLED

#ifdef GLIBMM_PROPERTIES_ENABLED
Glib::PropertyProxy_ReadOnly<bool> Action::property_is_important() const
{
  return Glib::PropertyProxy_ReadOnly<bool>(this, "is-important");
}
#endif //GLIBMM_PROPERTIES_ENABLED

#ifdef GLIBMM_PROPERTIES_ENABLED
Glib::PropertyProxy<bool> Action::property_hide_if_empty() 
{
  return Glib::PropertyProxy<bool>(this, "hide-if-empty");
}
#endif //GLIBMM_PROPERTIES_ENABLED

#ifdef GLIBMM_PROPERTIES_ENABLED
Glib::PropertyProxy_ReadOnly<bool> Action::property_hide_if_empty() const
{
  return Glib::PropertyProxy_ReadOnly<bool>(this, "hide-if-empty");
}
#endif //GLIBMM_PROPERTIES_ENABLED

#ifdef GLIBMM_PROPERTIES_ENABLED
Glib::PropertyProxy<bool> Action::property_sensitive() 
{
  return Glib::PropertyProxy<bool>(this, "sensitive");
}
#endif //GLIBMM_PROPERTIES_ENABLED

#ifdef GLIBMM_PROPERTIES_ENABLED
Glib::PropertyProxy_ReadOnly<bool> Action::property_sensitive() const
{
  return Glib::PropertyProxy_ReadOnly<bool>(this, "sensitive");
}
#endif //GLIBMM_PROPERTIES_ENABLED

#ifdef GLIBMM_PROPERTIES_ENABLED
Glib::PropertyProxy<bool> Action::property_visible() 
{
  return Glib::PropertyProxy<bool>(this, "visible");
}
#endif //GLIBMM_PROPERTIES_ENABLED

#ifdef GLIBMM_PROPERTIES_ENABLED
Glib::PropertyProxy_ReadOnly<bool> Action::property_visible() const
{
  return Glib::PropertyProxy_ReadOnly<bool>(this, "visible");
}
#endif //GLIBMM_PROPERTIES_ENABLED


#ifdef GLIBMM_DEFAULT_SIGNAL_HANDLERS_ENABLED
void Gtk::Action::on_activate()
{
  BaseClassType *const base = static_cast<BaseClassType*>(
      g_type_class_peek_parent(G_OBJECT_GET_CLASS(gobject_)) // Get the parent class of the object class (The original underlying C class).
  );

  if(base && base->activate)
    (*base->activate)(gobj());
}
#endif //GLIBMM_DEFAULT_SIGNAL_HANDLERS_ENABLED

#ifdef GLIBMM_VFUNCS_ENABLED
Widget* Gtk::Action::create_menu_item_vfunc() 
{
  BaseClassType *const base = static_cast<BaseClassType*>(
      g_type_class_peek_parent(G_OBJECT_GET_CLASS(gobject_)) // Get the parent class of the object class (The original underlying C class).
  );

  if(base && base->create_menu_item)
    return Glib::wrap((*base->create_menu_item)(gobj()));

  typedef Widget* RType;
  return RType();
}
Widget* Gtk::Action::create_tool_item_vfunc() 
{
  BaseClassType *const base = static_cast<BaseClassType*>(
      g_type_class_peek_parent(G_OBJECT_GET_CLASS(gobject_)) // Get the parent class of the object class (The original underlying C class).
  );

  if(base && base->create_tool_item)
    return Glib::wrap((*base->create_tool_item)(gobj()));

  typedef Widget* RType;
  return RType();
}
void Gtk::Action::connect_proxy_vfunc(Widget* proxy) 
{
  BaseClassType *const base = static_cast<BaseClassType*>(
      g_type_class_peek_parent(G_OBJECT_GET_CLASS(gobject_)) // Get the parent class of the object class (The original underlying C class).
  );

  if(base && base->connect_proxy)
    (*base->connect_proxy)(gobj(),(GtkWidget*)Glib::unwrap(proxy));
}
void Gtk::Action::disconnect_proxy_vfunc(Widget* proxy) 
{
  BaseClassType *const base = static_cast<BaseClassType*>(
      g_type_class_peek_parent(G_OBJECT_GET_CLASS(gobject_)) // Get the parent class of the object class (The original underlying C class).
  );

  if(base && base->disconnect_proxy)
    (*base->disconnect_proxy)(gobj(),(GtkWidget*)Glib::unwrap(proxy));
}
#endif //GLIBMM_VFUNCS_ENABLED


} // namespace Gtk


