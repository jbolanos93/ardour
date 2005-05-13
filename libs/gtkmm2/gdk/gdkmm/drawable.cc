// Generated by gtkmmproc -- DO NOT MODIFY!

#include <gdkmm/drawable.h>
#include <gdkmm/private/drawable_p.h>

#include <gdk/gdkenumtypes.h>
// -*- c++ -*-
/* $Id$ */

/* Copyright 1998-2002 The gtkmm Development Team
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

#include <gdkmm/gc.h>
#include <gdkmm/display.h>
#include <gdkmm/pixbuf.h>
#include <gdk/gdkdrawable.h>

namespace Gdk
{

void Drawable::draw_points(const Glib::RefPtr<const GC>& gc, const Glib::ArrayHandle<Point>& points)
{
  // Don't assume the reinterpret_cast<> works everywhere.  Gdk::Point is *special*.
  gdk_draw_points(
      gobj(), const_cast<GdkGC*>(Glib::unwrap<Gdk::GC>(gc)),
      reinterpret_cast<GdkPoint*>(const_cast<Point*>(points.data())),
      points.size());
}

void Drawable::draw_lines(const Glib::RefPtr<const GC>& gc, const Glib::ArrayHandle<Point>& points)
{
  // Don't assume the reinterpret_cast<> works everywhere.  Gdk::Point is *special*.
  gdk_draw_lines(
      gobj(), const_cast<GdkGC*>(Glib::unwrap<Gdk::GC>(gc)),
      reinterpret_cast<GdkPoint*>(const_cast<Point*>(points.data())),
      points.size());
}

void Drawable::draw_polygon(const Glib::RefPtr<const GC>& gc, bool filled,
                            const Glib::ArrayHandle<Point>& points)
{
  // Don't assume the reinterpret_cast<> works everywhere.  Gdk::Point is *special*.
  gdk_draw_polygon(
      gobj(), const_cast<GdkGC*>(Glib::unwrap<Gdk::GC>(gc)), filled,
      reinterpret_cast<GdkPoint*>(const_cast<Point*>(points.data())),
      points.size());
}

void Drawable::copy_to_image(const Glib::RefPtr<Image>& image, int src_x, int src_y, int dest_x, int dest_y, int width, int height) const
{
  gdk_drawable_copy_to_image(const_cast<GdkDrawable*>(gobj()), Glib::unwrap(image), src_x, src_y, dest_x, dest_y, width, height);
}


} // namespace Gdk


namespace
{
} // anonymous namespace

// static
GType Glib::Value<Gdk::RgbDither>::value_type()
{
  return gdk_rgb_dither_get_type();
}


namespace Glib
{

Glib::RefPtr<Gdk::Drawable> wrap(GdkDrawable* object, bool take_copy)
{
  return Glib::RefPtr<Gdk::Drawable>( dynamic_cast<Gdk::Drawable*> (Glib::wrap_auto ((GObject*)(object), take_copy)) );
  //We use dynamic_cast<> in case of multiple inheritance.
}

} /* namespace Glib */


namespace Gdk
{


/* The *_Class implementation: */

const Glib::Class& Drawable_Class::init()
{
  if(!gtype_) // create the GType if necessary
  {
    // Glib::Class has to know the class init function to clone custom types.
    class_init_func_ = &Drawable_Class::class_init_function;

    // This is actually just optimized away, apparently with no harm.
    // Make sure that the parent type has been created.
    //CppClassParent::CppObjectType::get_type();

    // Create the wrapper type, with the same class/instance size as the base type.
    register_derived_type(gdk_drawable_get_type());

    // Add derived versions of interfaces, if the C type implements any interfaces:
  }

  return *this;
}

void Drawable_Class::class_init_function(void* g_class, void* class_data)
{
  BaseClassType *const klass = static_cast<BaseClassType*>(g_class);
  CppClassParent::class_init_function(klass, class_data);

}


Glib::ObjectBase* Drawable_Class::wrap_new(GObject* object)
{
  return new Drawable((GdkDrawable*)object);
}


/* The implementation: */

GdkDrawable* Drawable::gobj_copy()
{
  reference();
  return gobj();
}

Drawable::Drawable(const Glib::ConstructParams& construct_params)
:
  Glib::Object(construct_params)
{}

Drawable::Drawable(GdkDrawable* castitem)
:
  Glib::Object((GObject*)(castitem))
{}

Drawable::~Drawable()
{}


Drawable::CppClassType Drawable::drawable_class_; // initialize static member

GType Drawable::get_type()
{
  return drawable_class_.init().get_type();
}

GType Drawable::get_base_type()
{
  return gdk_drawable_get_type();
}


Drawable::Drawable()
:
  Glib::ObjectBase(0), //Mark this class as gtkmmproc-generated, rather than a custom class, to allow vfunc optimisations.
  Glib::Object(Glib::ConstructParams(drawable_class_.init()))
{
  }

Glib::RefPtr<Drawable> Drawable::create()
{
  return Glib::RefPtr<Drawable>( new Drawable() );
}
void Drawable::get_size(int& width, int& height)
{
  gdk_drawable_get_size(gobj(), &width, &height);
}

int Drawable::get_depth() const
{
  return gdk_drawable_get_depth(const_cast<GdkDrawable*>(gobj()));
}

void Drawable::set_colormap(const Glib::RefPtr<Colormap>& colormap)
{
  gdk_drawable_set_colormap(gobj(), Glib::unwrap(colormap));
}

Glib::RefPtr<Colormap> Drawable::get_colormap()
{

  Glib::RefPtr<Colormap> retvalue = Glib::wrap(gdk_drawable_get_colormap(gobj()));

  if(retvalue)
    retvalue->reference(); //The function does not do a ref for us.
  return retvalue;
}

Glib::RefPtr<Visual> Drawable::get_visual()
{

  Glib::RefPtr<Visual> retvalue = Glib::wrap(gdk_drawable_get_visual(gobj()));

  if(retvalue)
    retvalue->reference(); //The function does not do a ref for us.
  return retvalue;
}

void Drawable::draw_point(const Glib::RefPtr<const GC>& gc, int x, int y)
{
  gdk_draw_point(gobj(), const_cast<GdkGC*>(Glib::unwrap<GC>(gc)), x, y);
}

void Drawable::draw_line(const Glib::RefPtr<const GC>& gc, int x1, int y1, int x2, int y2)
{
  gdk_draw_line(gobj(), const_cast<GdkGC*>(Glib::unwrap<GC>(gc)), x1, y1, x2, y2);
}

void Drawable::draw_rectangle(const Glib::RefPtr<const GC>& gc, bool filled, int x, int y, int width, int height)
{
  gdk_draw_rectangle(gobj(), const_cast<GdkGC*>(Glib::unwrap<GC>(gc)), static_cast<int>(filled), x, y, width, height);
}

void Drawable::draw_arc(const Glib::RefPtr<const GC>& gc, bool filled, int x, int y, int width, int height, int angle1, int angle2)
{
  gdk_draw_arc(gobj(), const_cast<GdkGC*>(Glib::unwrap<GC>(gc)), static_cast<int>(filled), x, y, width, height, angle1, angle2);
}

void Drawable::draw_drawable(const Glib::RefPtr<const GC>& gc, const Glib::RefPtr<const Drawable>& src, int xsrc, int ysrc, int xdest, int ydest, int width, int height)
{
  gdk_draw_drawable(gobj(), const_cast<GdkGC*>(Glib::unwrap<GC>(gc)), const_cast<GdkDrawable*>(Glib::unwrap<Drawable>(src)), xsrc, ysrc, xdest, ydest, width, height);
}

void Drawable::draw_image(const Glib::RefPtr<const GC>& gc, const Glib::RefPtr<const Image>& image, int xsrc, int ysrc, int xdest, int ydest, int width, int height)
{
  gdk_draw_image(gobj(), const_cast<GdkGC*>(Glib::unwrap<GC>(gc)), const_cast<GdkImage*>(Glib::unwrap<Image>(image)), xsrc, ysrc, xdest, ydest, width, height);
}

void Drawable::draw_segments(const Glib::RefPtr<const GC>& gc, GdkSegment* segs, int nsegs)
{
  gdk_draw_segments(gobj(), const_cast<GdkGC*>(Glib::unwrap<GC>(gc)), segs, nsegs);
}

void Drawable::draw_glyphs(const Glib::RefPtr<const GC>& gc, const Glib::RefPtr<const Pango::Font>& font, int x, int y, const Pango::GlyphString& glyphs)
{
  gdk_draw_glyphs(gobj(), const_cast<GdkGC*>(Glib::unwrap<GC>(gc)), const_cast<PangoFont*>(Glib::unwrap<Pango::Font>(font)), x, y, const_cast<PangoGlyphString*>(glyphs.gobj()));
}

void Drawable::draw_layout_line(const Glib::RefPtr<const GC>& gc, int x, int y, const Glib::RefPtr<const Pango::LayoutLine>& line)
{
  gdk_draw_layout_line(gobj(), const_cast<GdkGC*>(Glib::unwrap<GC>(gc)), x, y, const_cast<PangoLayoutLine*>(Glib::unwrap<Pango::LayoutLine>(line)));
}

void Drawable::draw_layout_line(const Glib::RefPtr<const GC>& gc, int x, int y, const Glib::RefPtr<const Pango::LayoutLine>& line, const Color& foreground, const Color& background)
{
  gdk_draw_layout_line_with_colors(gobj(), const_cast<GdkGC*>(Glib::unwrap<GC>(gc)), x, y, const_cast<PangoLayoutLine*>(Glib::unwrap<Pango::LayoutLine>(line)), (foreground).gobj(), (background).gobj());
}

void Drawable::draw_layout(const Glib::RefPtr<const GC>& gc, int x, int y, const Glib::RefPtr<const Pango::Layout>& layout)
{
  gdk_draw_layout(gobj(), const_cast<GdkGC*>(Glib::unwrap<GC>(gc)), x, y, const_cast<PangoLayout*>(Glib::unwrap<Pango::Layout>(layout)));
}

void Drawable::draw_layout(const Glib::RefPtr<const GC>& gc, int x, int y, const Glib::RefPtr<const Pango::Layout>& layout, const Color& foreground, const Color& background)
{
  gdk_draw_layout_with_colors(gobj(), const_cast<GdkGC*>(Glib::unwrap<GC>(gc)), x, y, const_cast<PangoLayout*>(Glib::unwrap<Pango::Layout>(layout)), (foreground).gobj(), (background).gobj());
}

void Drawable::draw_pixbuf(const Glib::RefPtr<const GC>& gc, const Glib::RefPtr<Pixbuf>& pixbuf, int src_x, int src_y, int dest_x, int dest_y, int width, int height, RgbDither dither, int x_dither, int y_dither)
{
  gdk_draw_pixbuf(gobj(), const_cast<GdkGC*>(Glib::unwrap<GC>(gc)), Glib::unwrap(pixbuf), src_x, src_y, dest_x, dest_y, width, height, ((GdkRgbDither)(dither)), x_dither, y_dither);
}

Glib::RefPtr<Image> Drawable::get_image(int x, int y, int width, int height) const
{
  return Glib::wrap(gdk_drawable_get_image(const_cast<GdkDrawable*>(gobj()), x, y, width, height));
}

Region Drawable::get_clip_region() const
{
  return Region(gdk_drawable_get_clip_region(const_cast<GdkDrawable*>(gobj())));
}

Region Drawable::get_visible_region() const
{
  return Region(gdk_drawable_get_visible_region(const_cast<GdkDrawable*>(gobj())));
}

void Drawable::draw_rgb_image(const Glib::RefPtr<const GC>& gc, int x, int y, int width, int height, RgbDither dith, const guchar* rgb_buf, int rowstride)
{
  gdk_draw_rgb_image(gobj(), const_cast<GdkGC*>(Glib::unwrap<GC>(gc)), x, y, width, height, ((GdkRgbDither)(dith)), const_cast<guchar*>(rgb_buf), rowstride);
}

void Drawable::draw_rgb_image_dithalign(const Glib::RefPtr<const GC>& gc, int x, int y, int width, int height, RgbDither dith, const guchar* rgb_buf, int rowstride, int xdith, int ydith)
{
  gdk_draw_rgb_image_dithalign(gobj(), const_cast<GdkGC*>(Glib::unwrap<GC>(gc)), x, y, width, height, ((GdkRgbDither)(dith)), const_cast<guchar*>(rgb_buf), rowstride, xdith, ydith);
}

void Drawable::draw_rgb_32_image(const Glib::RefPtr<const GC>& gc, int x, int y, int width, int height, RgbDither dith, const guchar* rgb_buf, int rowstride)
{
  gdk_draw_rgb_32_image(gobj(), const_cast<GdkGC*>(Glib::unwrap<GC>(gc)), x, y, width, height, ((GdkRgbDither)(dith)), const_cast<guchar*>(rgb_buf), rowstride);
}

void Drawable::draw_rgb_32_image_dithalign(const Glib::RefPtr<const GC>& gc, int x, int y, int width, int height, RgbDither dith, const guchar* buf, int rowstride, int xdith, int ydith)
{
  gdk_draw_rgb_32_image_dithalign(gobj(), const_cast<GdkGC*>(Glib::unwrap<GC>(gc)), x, y, width, height, ((GdkRgbDither)(dith)), const_cast<guchar*>(buf), rowstride, xdith, ydith);
}

void Drawable::draw_gray_image(const Glib::RefPtr<const GC>& gc, int x, int y, int width, int height, RgbDither dith, const guchar* rgb_buf, int rowstride)
{
  gdk_draw_gray_image(gobj(), const_cast<GdkGC*>(Glib::unwrap<GC>(gc)), x, y, width, height, ((GdkRgbDither)(dith)), const_cast<guchar*>(rgb_buf), rowstride);
}

void Drawable::draw_indexed_image(const Glib::RefPtr<const GC>& gc, int x, int y, int width, int height, RgbDither dith, const guchar* rgb_buf, int rowstride, const RgbCmap& cmap)
{
  gdk_draw_indexed_image(gobj(), const_cast<GdkGC*>(Glib::unwrap<GC>(gc)), x, y, width, height, ((GdkRgbDither)(dith)), const_cast<guchar*>(rgb_buf), rowstride, const_cast<GdkRgbCmap*>(cmap.gobj()));
}

Glib::RefPtr<Screen> Drawable::get_screen()
{

  Glib::RefPtr<Screen> retvalue = Glib::wrap(gdk_drawable_get_screen(gobj()));

  if(retvalue)
    retvalue->reference(); //The function does not do a ref for us.
  return retvalue;
}

Glib::RefPtr<const Screen> Drawable::get_screen() const
{

  Glib::RefPtr<const Screen> retvalue = Glib::wrap(gdk_drawable_get_screen(const_cast<GdkDrawable*>(gobj())));

  if(retvalue)
    retvalue->reference(); //The function does not do a ref for us.
  return retvalue;
}

Glib::RefPtr<Display> Drawable::get_display()
{

  Glib::RefPtr<Display> retvalue = Glib::wrap(gdk_drawable_get_display(gobj()));

  if(retvalue)
    retvalue->reference(); //The function does not do a ref for us.
  return retvalue;
}

Glib::RefPtr<const Display> Drawable::get_display() const
{

  Glib::RefPtr<const Display> retvalue = Glib::wrap(gdk_drawable_get_display(const_cast<GdkDrawable*>(gobj())));

  if(retvalue)
    retvalue->reference(); //The function does not do a ref for us.
  return retvalue;
}


} // namespace Gdk


