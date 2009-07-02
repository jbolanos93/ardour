// Generated by gtkmmproc -- DO NOT MODIFY!


#include <glibmm/regex.h>
#include <glibmm/private/regex_p.h>

/* Copyright (C) 2007 The glibmm Development Team
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

#include <glibmm/utility.h>

namespace Glib
{

#ifdef GLIBMM_EXCEPTIONS_ENABLED
Glib::RefPtr<Glib::Regex> Regex::create(const Glib::ustring& pattern,
                                        RegexCompileFlags compile_options,
                                        RegexMatchFlags match_options)
#else
Glib::RefPtr<Glib::Regex> Regex::create(const Glib::ustring& pattern,
                                        RegexCompileFlags compile_options,
                                        RegexMatchFlags match_options,
                                        std::auto_ptr<Glib::Error>& error)
#endif /* GLIBMM_EXCEPTIONS_ENABLED */
{
  GError* gerror = 0;
  GRegex* regex  = g_regex_new(pattern.c_str(), (GRegexCompileFlags)compile_options,
                               (GRegexMatchFlags)match_options, &gerror);

  if(gerror)
#ifdef GLIBMM_EXCEPTIONS_ENABLED
    Glib::Error::throw_exception(gerror);
#else
    error = Glib::Error::throw_exception(gerror);
#endif
  return Glib::wrap(regex);
}

// static
Glib::ustring Regex::escape_string(const Glib::ustring& string)
{
  const Glib::ScopedPtr<char> buf (g_regex_escape_string(string.raw().c_str(),
                                                         string.raw().size()));
  return Glib::ustring(buf.get());
}

bool Regex::match(const Glib::ustring& string, RegexMatchFlags match_options)
{
  return g_regex_match(gobj(), string.c_str(), (GRegexMatchFlags)(match_options), 0);
}


#ifdef GLIBMM_EXCEPTIONS_ENABLED
bool Regex::match(const Glib::ustring& string, int start_position, RegexMatchFlags match_options)
#else
bool Regex::match(const Glib::ustring& string, int start_position, RegexMatchFlags match_options, std::auto_ptr<Glib::Error>& error)
#endif //GLIBMM_EXCEPTIONS_ENABLED
{
  GError* gerror = 0;
  bool retvalue = g_regex_match_full(gobj(), string.c_str(), -1, start_position, ((GRegexMatchFlags)(match_options)), 0, &(gerror));
#ifdef GLIBMM_EXCEPTIONS_ENABLED
  if(gerror)
    ::Glib::Error::throw_exception(gerror);
#else
  if(gerror)
    error = ::Glib::Error::throw_exception(gerror);
#endif //GLIBMM_EXCEPTIONS_ENABLED

  return retvalue;
}

#ifdef GLIBMM_EXCEPTIONS_ENABLED
bool Regex::match(const Glib::ustring& string, gssize string_len, int start_position, RegexMatchFlags match_options)
#else
bool Regex::match(const Glib::ustring& string, gssize string_len, int start_position, RegexMatchFlags match_options, std::auto_ptr<Glib::Error>& error)
#endif //GLIBMM_EXCEPTIONS_ENABLED
{
  GError* gerror = 0;
  bool retvalue = g_regex_match_full(gobj(), string.c_str(), string_len, start_position, ((GRegexMatchFlags)(match_options)), 0, &(gerror));
#ifdef GLIBMM_EXCEPTIONS_ENABLED
  if(gerror)
    ::Glib::Error::throw_exception(gerror);
#else
  if(gerror)
    error = ::Glib::Error::throw_exception(gerror);
#endif //GLIBMM_EXCEPTIONS_ENABLED

  return retvalue;
}


bool Regex::match_all(const Glib::ustring& string, RegexMatchFlags match_options)
{
  return g_regex_match_all(gobj(), string.c_str(), ((GRegexMatchFlags)(match_options)), 0);
}


#ifdef GLIBMM_EXCEPTIONS_ENABLED
bool Regex::match_all(const Glib::ustring& string, int start_position, RegexMatchFlags match_options)
#else
bool Regex::match_all(const Glib::ustring& string, int start_position, RegexMatchFlags match_options, std::auto_ptr<Glib::Error>& error)
#endif //GLIBMM_EXCEPTIONS_ENABLED
{
  GError* gerror = 0;
  bool retvalue = g_regex_match_all_full(gobj(), string.c_str(), -1, start_position, ((GRegexMatchFlags)(match_options)), 0, &(gerror));
#ifdef GLIBMM_EXCEPTIONS_ENABLED
  if(gerror)
    ::Glib::Error::throw_exception(gerror);
#else
  if(gerror)
    error = ::Glib::Error::throw_exception(gerror);
#endif //GLIBMM_EXCEPTIONS_ENABLED

  return retvalue;
}

#ifdef GLIBMM_EXCEPTIONS_ENABLED
bool Regex::match_all(const Glib::ustring& string, gssize string_len, int start_position, RegexMatchFlags match_options)
#else
bool Regex::match_all(const Glib::ustring& string, gssize string_len, int start_position, RegexMatchFlags match_options, std::auto_ptr<Glib::Error>& error)
#endif //GLIBMM_EXCEPTIONS_ENABLED
{
  GError* gerror = 0;
  bool retvalue = g_regex_match_all_full(gobj(), string.c_str(), string_len, start_position, ((GRegexMatchFlags)(match_options)), 0, &(gerror));
#ifdef GLIBMM_EXCEPTIONS_ENABLED
  if(gerror)
    ::Glib::Error::throw_exception(gerror);
#else
  if(gerror)
    error = ::Glib::Error::throw_exception(gerror);
#endif //GLIBMM_EXCEPTIONS_ENABLED

  return retvalue;
}


#ifdef GLIBMM_EXCEPTIONS_ENABLED
Glib::ustring Regex::replace(const Glib::ustring& string, int start_position, const Glib::ustring& replacement, RegexMatchFlags match_options)
#else
Glib::ustring Regex::replace(const Glib::ustring& string, int start_position, const Glib::ustring& replacement, RegexMatchFlags match_options, std::auto_ptr<Glib::Error>& error)
#endif //GLIBMM_EXCEPTIONS_ENABLED
{
  GError* gerror = 0;
  Glib::ustring retvalue = Glib::convert_return_gchar_ptr_to_ustring(g_regex_replace(gobj(), string.c_str(), -1, start_position, replacement.c_str(), ((GRegexMatchFlags)(match_options)), &(gerror)));
#ifdef GLIBMM_EXCEPTIONS_ENABLED
  if(gerror)
    ::Glib::Error::throw_exception(gerror);
#else
  if(gerror)
    error = ::Glib::Error::throw_exception(gerror);
#endif //GLIBMM_EXCEPTIONS_ENABLED

  return retvalue;
}


#ifdef GLIBMM_EXCEPTIONS_ENABLED
Glib::ustring Regex::replace_literal(const Glib::ustring& string, int start_position, const Glib::ustring& replacement, RegexMatchFlags match_options)
#else
Glib::ustring Regex::replace_literal(const Glib::ustring& string, int start_position, const Glib::ustring& replacement, RegexMatchFlags match_options, std::auto_ptr<Glib::Error>& error)
#endif //GLIBMM_EXCEPTIONS_ENABLED
{
  GError* gerror = 0;
  Glib::ustring retvalue = Glib::convert_return_gchar_ptr_to_ustring(g_regex_replace_literal(gobj(), string.c_str(), -1, start_position, replacement.c_str(), ((GRegexMatchFlags)(match_options)), &(gerror)));
#ifdef GLIBMM_EXCEPTIONS_ENABLED
  if(gerror)
    ::Glib::Error::throw_exception(gerror);
#else
  if(gerror)
    error = ::Glib::Error::throw_exception(gerror);
#endif //GLIBMM_EXCEPTIONS_ENABLED

  return retvalue;
}

#ifdef GLIBMM_EXCEPTIONS_ENABLED
Glib::StringArrayHandle Regex::split(const Glib::ustring& string, int start_position, RegexMatchFlags match_options, int max_tokens) const
#else
Glib::StringArrayHandle Regex::split(const Glib::ustring& string, int start_position, RegexMatchFlags match_options, int max_tokens, std::auto_ptr<Glib::Error>& error) const
#endif //GLIBMM_EXCEPTIONS_ENABLED
{
  GError* gerror = 0;
  Glib::StringArrayHandle retvalue = Glib::StringArrayHandle(g_regex_split_full(const_cast<GRegex*>(gobj()), string.c_str(), -1, start_position, ((GRegexMatchFlags)(match_options)), max_tokens, &(gerror)), Glib::OWNERSHIP_DEEP);
#ifdef GLIBMM_EXCEPTIONS_ENABLED
  if(gerror)
    ::Glib::Error::throw_exception(gerror);
#else
  if(gerror)
    error = ::Glib::Error::throw_exception(gerror);
#endif //GLIBMM_EXCEPTIONS_ENABLED

  return retvalue;
}

} // namespace Glib

namespace
{
} // anonymous namespace


Glib::RegexError::RegexError(Glib::RegexError::Code error_code, const Glib::ustring& error_message)
:
  Glib::Error (G_REGEX_ERROR, error_code, error_message)
{}

Glib::RegexError::RegexError(GError* gobject)
:
  Glib::Error (gobject)
{}

Glib::RegexError::Code Glib::RegexError::code() const
{
  return static_cast<Code>(Glib::Error::code());
}

#ifdef GLIBMM_EXCEPTIONS_ENABLED
void Glib::RegexError::throw_func(GError* gobject)
{
  throw Glib::RegexError(gobject);
}
#else
//When not using exceptions, we just pass the Exception object around without throwing it:
std::auto_ptr<Glib::Error> Glib::RegexError::throw_func(GError* gobject)
{
  return std::auto_ptr<Glib::Error>(new Glib::RegexError(gobject));
}
#endif //GLIBMM_EXCEPTIONS_ENABLED


/* Why reinterpret_cast<Regex*>(gobject) is needed:
 *
 * A Regex instance is in fact always a GRegex instance.
 * Unfortunately, GRegex cannot be a member of Regex,
 * because it is an opaque struct.  Also, the C interface does not provide
 * any hooks to install a destroy notification handler, thus we cannot
 * wrap it dynamically either.
 *
 * The cast works because Regex does not have any member data, and
 * it is impossible to derive from it.  This is ensured by not implementing
 * the (protected) default constructor.  The ctor is protected rather than
 * private just to avoid a compile warning.
 */

namespace Glib
{

Glib::RefPtr<Glib::Regex> wrap(GRegex* object, bool take_copy)
{
  if(take_copy && object)
    g_regex_ref(object);

  // See the comment at the top of this file, if you want to know why the cast works.
  return Glib::RefPtr<Glib::Regex>(reinterpret_cast<Glib::Regex*>(object));
}

} // namespace Glib


namespace Glib
{


void Regex::reference() const
{
  // See the comment at the top of this file, if you want to know why the cast works.
  g_regex_ref(reinterpret_cast<GRegex*>(const_cast<Regex*>(this)));
}

void Regex::unreference() const
{
  // See the comment at the top of this file, if you want to know why the cast works.
  g_regex_unref(reinterpret_cast<GRegex*>(const_cast<Regex*>(this)));
}

GRegex* Regex::gobj()
{
  // See the comment at the top of this file, if you want to know why the cast works.
  return reinterpret_cast<GRegex*>(this);
}

const GRegex* Regex::gobj() const
{
  // See the comment at the top of this file, if you want to know why the cast works.
  return reinterpret_cast<const GRegex*>(this);
}

GRegex* Regex::gobj_copy() const
{
  // See the comment at the top of this file, if you want to know why the cast works.
  GRegex *const gobject = reinterpret_cast<GRegex*>(const_cast<Regex*>(this));
  g_regex_ref(gobject);
  return gobject;
}


Glib::ustring Regex::get_pattern() const
{
  return Glib::convert_const_gchar_ptr_to_ustring(g_regex_get_pattern(const_cast<GRegex*>(gobj())));
}

int Regex::get_max_backref() const
{
  return g_regex_get_max_backref(const_cast<GRegex*>(gobj()));
}

int Regex::get_capture_count() const
{
  return g_regex_get_capture_count(const_cast<GRegex*>(gobj()));
}

int Regex::get_string_number(const Glib::ustring& name) const
{
  return g_regex_get_string_number(const_cast<GRegex*>(gobj()), name.c_str());
}

bool Regex::match_simple(const Glib::ustring& pattern, const Glib::ustring& string, RegexCompileFlags compile_options, RegexMatchFlags match_options)
{
  return g_regex_match_simple(pattern.c_str(), string.c_str(), ((GRegexCompileFlags)(compile_options)), ((GRegexMatchFlags)(match_options)));
}


Glib::StringArrayHandle Regex::split_simple(const Glib::ustring& pattern, const Glib::ustring& string, RegexCompileFlags compile_options, RegexMatchFlags match_options)
{
  return Glib::StringArrayHandle(g_regex_split_simple(pattern.c_str(), string.c_str(), ((GRegexCompileFlags)(compile_options)), ((GRegexMatchFlags)(match_options))), Glib::OWNERSHIP_DEEP);
}


Glib::StringArrayHandle Regex::split(const Glib::ustring& string, RegexMatchFlags match_options)
{
  return Glib::StringArrayHandle(g_regex_split(gobj(), string.c_str(), ((GRegexMatchFlags)(match_options))), Glib::OWNERSHIP_DEEP);
}

#ifdef GLIBMM_EXCEPTIONS_ENABLED
Glib::StringArrayHandle Regex::split(const gchar* string, gssize string_len, int start_position, RegexMatchFlags match_options, int max_tokens) const
#else
Glib::StringArrayHandle Regex::split(const gchar* string, gssize string_len, int start_position, RegexMatchFlags match_options, int max_tokens, std::auto_ptr<Glib::Error>& error) const
#endif //GLIBMM_EXCEPTIONS_ENABLED
{
  GError* gerror = 0;
  Glib::StringArrayHandle retvalue = Glib::StringArrayHandle(g_regex_split_full(const_cast<GRegex*>(gobj()), string, string_len, start_position, ((GRegexMatchFlags)(match_options)), max_tokens, &(gerror)), Glib::OWNERSHIP_DEEP);
#ifdef GLIBMM_EXCEPTIONS_ENABLED
  if(gerror)
    ::Glib::Error::throw_exception(gerror);
#else
  if(gerror)
    error = ::Glib::Error::throw_exception(gerror);
#endif //GLIBMM_EXCEPTIONS_ENABLED

  return retvalue;

}

#ifdef GLIBMM_EXCEPTIONS_ENABLED
Glib::ustring Regex::replace(const gchar* string, gssize string_len, int start_position, const Glib::ustring& replacement, RegexMatchFlags match_options)
#else
Glib::ustring Regex::replace(const gchar* string, gssize string_len, int start_position, const Glib::ustring& replacement, RegexMatchFlags match_options, std::auto_ptr<Glib::Error>& error)
#endif //GLIBMM_EXCEPTIONS_ENABLED
{
  GError* gerror = 0;
  Glib::ustring retvalue = Glib::convert_return_gchar_ptr_to_ustring(g_regex_replace(gobj(), string, string_len, start_position, replacement.c_str(), ((GRegexMatchFlags)(match_options)), &(gerror)));
#ifdef GLIBMM_EXCEPTIONS_ENABLED
  if(gerror)
    ::Glib::Error::throw_exception(gerror);
#else
  if(gerror)
    error = ::Glib::Error::throw_exception(gerror);
#endif //GLIBMM_EXCEPTIONS_ENABLED

  return retvalue;

}

#ifdef GLIBMM_EXCEPTIONS_ENABLED
Glib::ustring Regex::replace_literal(const gchar * string, gssize string_len, int start_position, const Glib::ustring& replacement, RegexMatchFlags match_options)
#else
Glib::ustring Regex::replace_literal(const gchar * string, gssize string_len, int start_position, const Glib::ustring& replacement, RegexMatchFlags match_options, std::auto_ptr<Glib::Error>& error)
#endif //GLIBMM_EXCEPTIONS_ENABLED
{
  GError* gerror = 0;
  Glib::ustring retvalue = Glib::convert_return_gchar_ptr_to_ustring(g_regex_replace_literal(gobj(), string, string_len, start_position, replacement.c_str(), ((GRegexMatchFlags)(match_options)), &(gerror)));
#ifdef GLIBMM_EXCEPTIONS_ENABLED
  if(gerror)
    ::Glib::Error::throw_exception(gerror);
#else
  if(gerror)
    error = ::Glib::Error::throw_exception(gerror);
#endif //GLIBMM_EXCEPTIONS_ENABLED

  return retvalue;

}

#ifdef GLIBMM_EXCEPTIONS_ENABLED
Glib::ustring Regex::replace_eval(const Glib::ustring& string, gssize string_len, int start_position, RegexMatchFlags match_options, GRegexEvalCallback eval, gpointer user_data)
#else
Glib::ustring Regex::replace_eval(const Glib::ustring& string, gssize string_len, int start_position, RegexMatchFlags match_options, GRegexEvalCallback eval, gpointer user_data, std::auto_ptr<Glib::Error>& error)
#endif //GLIBMM_EXCEPTIONS_ENABLED
{
  GError* gerror = 0;
  Glib::ustring retvalue = Glib::convert_return_gchar_ptr_to_ustring(g_regex_replace_eval(gobj(), string.c_str(), string_len, start_position, ((GRegexMatchFlags)(match_options)), eval, user_data, &(gerror)));
#ifdef GLIBMM_EXCEPTIONS_ENABLED
  if(gerror)
    ::Glib::Error::throw_exception(gerror);
#else
  if(gerror)
    error = ::Glib::Error::throw_exception(gerror);
#endif //GLIBMM_EXCEPTIONS_ENABLED

  return retvalue;

}

#ifdef GLIBMM_EXCEPTIONS_ENABLED
bool Regex::check_replacement(const Glib::ustring& replacement, gboolean* has_references)
#else
bool Regex::check_replacement(const Glib::ustring& replacement, gboolean* has_references, std::auto_ptr<Glib::Error>& error)
#endif //GLIBMM_EXCEPTIONS_ENABLED
{
  GError* gerror = 0;
  bool retvalue = g_regex_check_replacement(replacement.c_str(), has_references, &(gerror));

#ifdef GLIBMM_EXCEPTIONS_ENABLED
  if(gerror)
    ::Glib::Error::throw_exception(gerror);
#else
  if(gerror)
    error = ::Glib::Error::throw_exception(gerror);
#endif //GLIBMM_EXCEPTIONS_ENABLED

  return retvalue;
}


} // namespace Glib


