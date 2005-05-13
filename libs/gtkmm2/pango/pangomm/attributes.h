// -*- c++ -*-
// Generated by gtkmmproc -- DO NOT MODIFY!
#ifndef _PANGOMM_ATTRIBUTES_H
#define _PANGOMM_ATTRIBUTES_H

#include <glibmm.h>

/* attributes.h
 *
 * Copyright (C) 2002 The gtkmm Development Team
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

#include <pangomm/language.h>
#include <pangomm/rectangle.h>
#include <pangomm/color.h>
#include <pangomm/fontdescription.h>
#include <pango/pango-attributes.h>


namespace Pango
{


/** @addtogroup pangommEnums Enums and Flags */

/** Pango::AttrType distinguishes between different types of attributes.
 * Along with the predefined values, it is possible to allocate additional values for
 * custom attributes using Pango::Attribute::register_type(). The predefined values
 * are given below.
 * @ingroup pangommEnums
 */
enum AttrType
{
  ATTR_INVALID,
  ATTR_LANGUAGE,
  ATTR_FAMILY,
  ATTR_STYLE,
  ATTR_WEIGHT,
  ATTR_VARIANT,
  ATTR_STRETCH,
  ATTR_SIZE,
  ATTR_FONT_DESC,
  ATTR_FOREGROUND,
  ATTR_BACKGROUND,
  ATTR_UNDERLINE,
  ATTR_STRIKETHROUGH,
  ATTR_RISE,
  ATTR_SHAPE,
  ATTR_SCALE,
  ATTR_FALLBACK,
  ATTR_LETTER_SPACING,
  ATTR_UNDERLINE_COLOR,
  ATTR_STRIKETHROUGH_COLOR
};

} // namespace Pango


#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace Glib
{

template <>
class Value<Pango::AttrType> : public Glib::Value_Enum<Pango::AttrType>
{
public:
  static GType value_type() G_GNUC_CONST;
};

} // namespace Glib
#endif /* DOXYGEN_SHOULD_SKIP_THIS */


namespace Pango
{


/** A Pango::Underline is used to specify whether text should be underlined, and if so, the type of underlining.
 * @ingroup pangommEnums
 */
enum Underline
{
  UNDERLINE_NONE,
  UNDERLINE_SINGLE,
  UNDERLINE_DOUBLE,
  UNDERLINE_LOW,
  UNDERLINE_ERROR
};

} // namespace Pango


#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace Glib
{

template <>
class Value<Pango::Underline> : public Glib::Value_Enum<Pango::Underline>
{
public:
  static GType value_type() G_GNUC_CONST;
};

} // namespace Glib
#endif /* DOXYGEN_SHOULD_SKIP_THIS */


namespace Pango
{


/** A Pango::LogAttr stores information about the attributes of a single character.
 */
typedef PangoLogAttr LogAttr;


class AttrString;
class AttrLanguage;
class AttrColor;
class AttrInt;
class AttrFloat;
class AttrFontDesc;
class AttrShape;

/** The Pango::Attribute structure represents the common portions of all attributes.
 * Particular types of attributes derive this class. It holds the range in which the
 * value in the type-specific part of the attribute applies.
 *
 * Attributed text is used in a number of places in pango. It is used as the input to
 * the itemization process and also when creating a Pango::Layout.
 */
class Attribute
{
  public:
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  typedef Attribute CppObjectType;
  typedef PangoAttribute BaseObjectType;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

private:

  
public:
  /** Constructs an invalid attribute.
   */
  Attribute();

  Attribute(const Attribute& src);
  explicit Attribute(PangoAttribute* castitem, bool take_copy=true);
  ~Attribute();

  Attribute& operator=(const Attribute& src);

  /** Gets the type ID for this attribute.
   * @return The type ID for this attribute or ATTR_INVALID if the attribute is invalid.
   */
  AttrType get_type() const;

  /** Allocate a new attribute type ID.
   * @param name An identifier for the type (currently unused).
   * @return The new type ID.
   */
  static AttrType register_type(const Glib::ustring& name);

  /** Gets the start index of the range.
   * @return The start index of the range.
   */
  unsigned int get_start_index() const;

  /** Gets the end index of the range. The character at this index is not included in the range.
   * @return The end index of the range.
   */
  unsigned int get_end_index() const;

  /** Sets the start index of the range.
   * @param value The new start index.
   */
  void set_start_index(const unsigned int& value);

  /** Sets the end index of the range. The character at this index is not included in the range.
   * @param value The new end index.
   */
  void set_end_index(const unsigned int& value);

  
  /** Compare two attributes for equality. This compares only the
   * actual value of the two attributes and not the ranges that the
   * attributes apply to.
   * @param attr2 Another Pango::Attribute.
   * @return <tt>true</tt> if the two attributes have the same value.
   */
  bool equal(const Attribute& attr2) const;

  /// Provides access to the underlying C GObject.  
  PangoAttribute*       gobj()       { return gobject_; }
  /// Provides access to the underlying C GObject.
  PangoAttribute* const gobj() const { return gobject_; }

  /** Create a new font family attribute.
   * @param family The family or comma separated list of families.
   * @return An attribute of type AttrString.
   */
  static AttrString create_attr_family(const Glib::ustring& family);

  /** Create a new language tag attribute
   * @param language The language tag.
   * @return An attribute of type AttrLanguage.
   */
  static AttrLanguage create_attr_language(const Language& language);

  /** Create a new foreground color attribute.
   * @param red The red value (ranging from 0 to 65535).
   * @param green The green value (ranging from 0 to 65535).
   * @param blue The blue value (ranging from 0 to 65535).
   * @return An attribute of type AttrColor.
   */
  static AttrColor create_attr_foreground(guint16 red, guint16 green, guint16 blue);

  /** Create a new background color attribute.
   * @param red The red value (ranging from 0 to 65535).
   * @param green The green value (ranging from 0 to 65535).
   * @param blue The blue value (ranging from 0 to 65535).
   * @return An attribute of type AttrColor.
   */
  static AttrColor create_attr_background(guint16 red, guint16 green, guint16 blue);

  /** Create a new font-size attribute.
   * @param size The font size, in 1000ths of a point.
   * @return An attribute of type AttrInt.
   */
  static AttrInt create_attr_size(int size);

  /** Create a new font slant style attribute.
   * @param style The slant style.
   * @return An attribute of type AttrInt.
   */
  static AttrInt create_attr_style(Style style);

  /** Create a new font weight attribute.
   * @param weight The weight.
   * @return An attribute of type AttrInt.
   */
  static AttrInt create_attr_weight(Weight weight);

  /** Create a new font variant attribute (normal or small caps).
   * @param variant The variant.
   * @return An attribute of type AttrInt.
   */
  static AttrInt create_attr_variant(Variant variant);

  /** Create a new font stretch attribute.
   * @param stretch The stretch.
   * @return An attribute of type AttrInt.
   */
  static AttrInt create_attr_stretch(Stretch stretch);

  /** Create a new font description attribute.
   * This attribute allows setting family, style, weight, variant, stretch, and size simultaneously.
   * @param desc The font description.
   * @return An attribute of type AttrFontDesc.
   */
  static AttrFontDesc create_attr_font_desc(const FontDescription& desc);

  /** Create a new underline-style object.
   * @param underline The underline style.
   * @return An attribute of type AttrInt.
   */
  static AttrInt create_attr_underline(Underline underline);

  /** Create a new font strike-through attribute.
   * @param strikethrough True indicates the text should be struck-through.
   * @return An attribute of type AttrInt.
   */
  static AttrInt create_attr_strikethrough(bool strikethrough);

  /** Create a new baseline displacement attribute.
   * @param rise The amount that the text should be displaced vertically, in 10'000ths of an em. Positive values displace the text upwards.
   * @return An attribute of type AttrInt.
   */
  static AttrInt create_attr_rise(int rise);

  /** Create a new font size scale attribute.
   * The base font for the affected text will have its size multiplied by scale_factor.
   * @param scale_factor Factor to scale the font.
   * @return An attribute of type AttrFloat.
   */
  static AttrFloat create_attr_scale(double scale_factor);

  /** Create a new shape attribute.
   * A shape is used to impose a particular ink and logical rect on the result of shaping a particular glyph.
   * This might be used, for instance, for embedding a picture or a widget inside a PangoLayout.
   * @param ink_rect Ink rectangle to assign to each character.
   * @param logical_rect Logical rectangle assign to each character.
   * @return An attribute of type AttrShape.
   */
  static AttrShape create_attr_shape(const Rectangle& ink_rect, const Rectangle& logical_rect);

protected:
  PangoAttribute* gobject_;


};

/** @relates Pango::Attribute */
inline bool operator==(const Attribute& lhs, const Attribute& rhs)
{
  return lhs.equal(rhs);
}

/** @relates Pango::Attribute */
inline bool operator!=(const Attribute& lhs, const Attribute& rhs)
{
  return lhs.equal(rhs);
}


/** A Pango::AttrString is used to represent an attribute with a string value.
 */
class AttrString : public Attribute
{
  public:
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  typedef AttrString CppObjectType;
  typedef PangoAttrString BaseObjectType;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

private:


protected:
  AttrString();
public:
  AttrString(const AttrString& src);
  explicit AttrString(PangoAttrString* castitem, bool take_copy=true);

  AttrString& operator=(const AttrString& src);

  /** Gets the string which is the value of the attribute.
   * @return The string value of the attribute.
   */
  Glib::ustring get_string() const;

  /** Sets the string which is the value of the attribute.
   * @param string The new string value for the attribute.
   */
  void set_string(const Glib::ustring& string);

  /// Provides access to the underlying C GObject.  
  PangoAttrString*       gobj()       { return reinterpret_cast<PangoAttrString*>(gobject_); }
  /// Provides access to the underlying C GObject.
  const PangoAttrString* gobj() const { return reinterpret_cast<const PangoAttrString*>(gobject_); }


};


/** A Pango::AttrLanguage is used to represent an attribute that is a language.
 */
class AttrLanguage : public Attribute
{
  public:
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  typedef AttrLanguage CppObjectType;
  typedef PangoAttrLanguage BaseObjectType;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

private:


protected:
  AttrLanguage();
public:
  AttrLanguage(const AttrLanguage& src);
  explicit AttrLanguage(PangoAttrLanguage* castitem, bool take_copy=true);

  AttrLanguage& operator=(const AttrLanguage& src);

  /** Gets the language which is the value of the attribute.
   * @return The language tag of the attribute.
   */
  Language get_language() const;

  /** Sets the language which is the value of the attribute.
   * @param value The new language tag for the attribute.
   */
  void set_language(const Language& value);

  /// Provides access to the underlying C GObject.  
  PangoAttrLanguage*       gobj()       { return reinterpret_cast<PangoAttrLanguage*>(gobject_); }
  /// Provides access to the underlying C GObject.
  const PangoAttrLanguage* gobj() const { return reinterpret_cast<const PangoAttrLanguage*>(gobject_); }


};


/** A Pango::AttrColor is used to represent an attribute which is a color.
 */
class AttrColor : public Attribute
{
  public:
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  typedef AttrColor CppObjectType;
  typedef PangoAttrColor BaseObjectType;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

private:


protected:
  AttrColor();
public:
  AttrColor(const AttrColor& src);
  explicit AttrColor(PangoAttrColor* castitem, bool take_copy=true);

  AttrColor& operator=(const AttrColor& src);

  /** Gets the color which is the value of the attribute.
   * @return The color value of the attribute.
   */
  Color get_color() const;

  /** Sets the color which is the value of the attribute.
   * @param value The new color value for the attribute.
   */
  void set_color(const Color& value);

  /// Provides access to the underlying C GObject.  
  PangoAttrColor*       gobj()       { return reinterpret_cast<PangoAttrColor*>(gobject_); }
  /// Provides access to the underlying C GObject.
  const PangoAttrColor* gobj() const { return reinterpret_cast<const PangoAttrColor*>(gobject_); }


};


/** A Pango::AttrInt is used to represent an attribute with an integer or enumeration value.
 */
class AttrInt : public Attribute
{
  public:
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  typedef AttrInt CppObjectType;
  typedef PangoAttrInt BaseObjectType;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

private:


protected:
  AttrInt();
public:
  AttrInt(const AttrInt& src);
  explicit AttrInt(PangoAttrInt* castitem, bool take_copy=true);

  AttrInt& operator=(const AttrInt& src);

  /** Gets the integer value of the attribute.
   * @return The integer value of the attribute.
   */
  int get_value() const;

  /** Sets the integer value of the attribute.
   * @param value The new integer value for the attribute.
   */
  void set_value(const int& value);

  /// Provides access to the underlying C GObject.  
  PangoAttrInt*       gobj()       { return reinterpret_cast<PangoAttrInt*>(gobject_); }
  /// Provides access to the underlying C GObject.
  const PangoAttrInt* gobj() const { return reinterpret_cast<const PangoAttrInt*>(gobject_); }


};


/** A Pango::AttrFloat is used to represent an attribute with a float or double value.
 */
class AttrFloat : public Attribute
{
  public:
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  typedef AttrFloat CppObjectType;
  typedef PangoAttrFloat BaseObjectType;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

private:


protected:
  AttrFloat();
public:
  AttrFloat(const AttrFloat& src);
  explicit AttrFloat(PangoAttrFloat* castitem, bool take_copy=true);

  AttrFloat& operator=(const AttrFloat& src);

  /** Gets the floating point value of the attribute.
   * @return The floating point value of the attribute.
   */
  double get_value() const;

  /** Sets the floating point value of the attribute.
   * @param value The new floating point value for the attribute.
   */
  void set_value(const double& value);

  /// Provides access to the underlying C GObject.
  PangoAttrFloat*       gobj()       { return reinterpret_cast<PangoAttrFloat*>(gobject_); }
  /// Provides access to the underlying C GObject.
  const PangoAttrFloat* gobj() const { return reinterpret_cast<const PangoAttrFloat*>(gobject_); }


};


/** A Pango::AttrFontDesc is used to represent an attribute that sets all aspects of the font description at once.
 */
class AttrFontDesc : public Attribute
{
  public:
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  typedef AttrFontDesc CppObjectType;
  typedef PangoAttrFontDesc BaseObjectType;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

private:


protected:
  AttrFontDesc();
public:
  AttrFontDesc(const AttrFontDesc& src);
  explicit AttrFontDesc(PangoAttrFontDesc* castitem, bool take_copy=true);

  AttrFontDesc& operator=(const AttrFontDesc& src);

  /** Gets the font description which is the value of the attribute.
   * @return The font description of the attribute.
   */
  FontDescription get_desc() const;

  /** Sets the font description which is the value of the attribute.
   * @param desc The new font description for the attribute.
   */
  void set_desc(const FontDescription& desc);
  
  /// Provides access to the underlying C GObject.
  PangoAttrFontDesc*       gobj()       { return reinterpret_cast<PangoAttrFontDesc*>(gobject_); }
  /// Provides access to the underlying C GObject.
  const PangoAttrFontDesc* gobj() const { return reinterpret_cast<const PangoAttrFontDesc*>(gobject_); }


};


/** A Pango::AttrShape structure is used to represent an attribute which imposes shape restrictions.
 */
class AttrShape : public Attribute
{
  public:
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  typedef AttrShape CppObjectType;
  typedef PangoAttrShape BaseObjectType;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

private:


protected:
  AttrShape();
public:
  AttrShape(const AttrShape& src);
  explicit AttrShape(PangoAttrShape* castitem, bool take_copy=true);

  AttrShape& operator=(const AttrShape& src);

  /** Gets the ink rectangle to restrict to.
   * @return The ink rectangle of the attribute.
   */
  Rectangle get_ink_rect() const;

  /** Gets the logical rectangle to restrict to.
   * @return The logical rectangle of the attribute.
   */
  Rectangle get_logical_rect() const;

  /** Sets the ink rectangle to restrict to.
   * @param value The new ink rectangle for the attribute.
   */
  void set_ink_rect(const Rectangle& value);

  /** Sets the logical rectangle to restrict to.
   * @param value The new logical rectangle for the attribute.
   */
  void set_logical_rect(const Rectangle& value);

  /// Provides access to the underlying C GObject.  
  PangoAttrShape*       gobj()       { return reinterpret_cast<PangoAttrShape*>(gobject_); }
  /// Provides access to the underlying C GObject.
  const PangoAttrShape* gobj() const { return reinterpret_cast<const PangoAttrShape*>(gobject_); }


};


struct AttributeTraits
{
  typedef Pango::Attribute      CppType;
  typedef const PangoAttribute* CType;
  typedef PangoAttribute*       CTypeNonConst;

  static CType   to_c_type      (const CppType& obj) { return obj.gobj(); }
  static CType   to_c_type      (CType ptr) { return ptr; }
  static CppType to_cpp_type    (CType ptr) { return CppType(const_cast<CTypeNonConst>(ptr), true); }
  static void    release_c_type (CType ptr) { pango_attribute_destroy(const_cast<CTypeNonConst>(ptr)); }
};

typedef Glib::SListHandle<Attribute, AttributeTraits> SListHandle_Attribute;

} // namespace Pango


namespace Glib
{

/** @relates Pango::Attribute */
Pango::Attribute wrap(PangoAttribute* object, bool take_copy = false);

/** @relates Pango::AttrString */
Pango::AttrString wrap(PangoAttrString* object, bool take_copy = false);

/** @relates Pango::AttrLanguage */
Pango::AttrLanguage wrap(PangoAttrLanguage* object, bool take_copy = false);

/** @relates Pango::AttrColor */
Pango::AttrColor wrap(PangoAttrColor* object, bool take_copy = false);

/** @relates Pango::AttrInt */
Pango::AttrInt wrap(PangoAttrInt* object, bool take_copy = false);

/** @relates Pango::AttrFloat */
Pango::AttrFloat wrap(PangoAttrFloat* object, bool take_copy = false);

/** @relates Pango::AttrFontDesc */
Pango::AttrFontDesc wrap(PangoAttrFontDesc* object, bool take_copy = false);

/** @relates Pango::AttrShape */
Pango::AttrShape wrap(PangoAttrShape* object, bool take_copy = false);

} //namespace Glib


#endif /* _PANGOMM_ATTRIBUTES_H */

