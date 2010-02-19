/*
    Copyright (C) 2010 Paul Davis 

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

*/

#ifndef __pbd_properties_h__
#define __pbd_properties_h__

#include <string>
#include <sstream>
#include <list>
#include <set>
#include <glib.h>

#include "pbd/xml++.h"

namespace PBD {

typedef GQuark PropertyID;

template<typename T> 
struct PropertyDescriptor {
    PropertyID id;
    typedef T value_type;
};

class PropertyChange : public std::set<PropertyID> 
{
  public:
	PropertyChange() { }
	template<typename T> PropertyChange(PropertyDescriptor<T> p) { insert (p.id); }
        PropertyChange(const PropertyChange& other) : std::set<PropertyID> (other) { }
	
	PropertyChange operator= (const PropertyChange& other) {
		clear ();
		insert (other.begin(), other.end());
		return *this;
	}

	template<typename T> PropertyChange operator= (PropertyDescriptor<T> p) {
		clear ();
		insert (p.id);
		return *this;
	}

	template<typename T> bool contains (PropertyDescriptor<T> p) const { return find (p.id) != end(); }

	bool contains (const PropertyChange& other) const { 
		for (const_iterator x = other.begin(); x != other.end(); ++x) {
			if (find (*x) != end()) {
			    return true;
			}
		}
		return false;
	}

	void add (PropertyID id) { (void) insert (id); }
	void add (const PropertyChange& other) { (void) insert (other.begin(), other.end()); }
	template<typename T> void add (PropertyDescriptor<T> p) { (void) insert (p.id); }
};

/** Base (non template) part of Property */	
class PropertyBase
{
public:
	PropertyBase (PropertyID pid)
		: _have_old (false)
		, _property_id (pid)
	{

	}

	/** Forget about any old value for this state */
	void clear_history () {
		_have_old = false;
	}

	virtual void diff (XMLNode *, XMLNode *) const = 0;
	virtual void diff (PropertyChange&) const = 0;
	virtual bool set_state (XMLNode const &) = 0;
	virtual void add_state (XMLNode &) const = 0;

	const gchar* property_name() const { return g_quark_to_string (_property_id); }
	PropertyID id() const { return _property_id; }

	bool operator== (PropertyID pid) const {
		return _property_id == pid;
	}

protected:
	bool _have_old;
	PropertyID _property_id;
};

/** Parent class for classes which represent a single property in a Stateful object */
template <class T>
class PropertyTemplate : public PropertyBase
{
public:
	PropertyTemplate (PropertyDescriptor<T> p, T const & v)
		: PropertyBase (p.id)
		, _current (v)
	{

	}
	PropertyTemplate<T> & operator= (PropertyTemplate<T> const & s) {
		/* XXX: isn't there a nicer place to do this? */
		_have_old = s._have_old;
		_property_id = s._property_id;
		
		_current = s._current;
		_old = s._old;
		return *this;
	}

	T & operator= (T const & v) {
		set (v);
		return _current;
	}

	T & operator+= (T const & v) {
		set (_current + v);
		return _current;
	}
	
	bool operator== (const T& other) const {
		return _current == other;
	}

	bool operator!= (const T& other) const {
		return _current != other;
	}

	operator T const & () const {
		return _current;
	}

	T const & val () const {
		return _current;
	}

	void diff (XMLNode* old, XMLNode* current) const {
		if (_have_old) {
			old->add_property (property_name(), to_string (_old));
			current->add_property (property_name(), to_string (_current));
		}
	}
	
	void diff (PropertyChange& c) const {
		if (_have_old) {
			c.add (_property_id);
		}
	}

	/** Try to set state from the property of an XML node.
	 *  @param node XML node.
	 *  @return true if the value of the property is changed
	 */
	bool set_state (XMLNode const & node) {
		XMLProperty const * p = node.property (property_name());

		if (p) {
			T const v = from_string (p->value ());

			if (v != _current) {
				set (v);
				return true;
			}
		} 

		return false;
	}

	void add_state (XMLNode & node) const {
		node.add_property (property_name(), to_string (_current));
	}

protected:
	void set (T const & v) {
		_old = _current;
		_have_old = true;
		_current = v;
	}

	virtual std::string to_string (T const & v) const = 0;
	virtual T from_string (std::string const & s) const = 0;
		
	T _current;
	T _old;
};

template<class T>	
std::ostream& operator<< (std::ostream& os, PropertyTemplate<T> const & s)
{
	return os << s.val();
}

/** Representation of a single piece of state in a Stateful; for use
 *  with types that can be written to / read from stringstreams.
 */
template <class T>
class Property : public PropertyTemplate<T>
{
public:
	Property (PropertyDescriptor<T> q, T const & v)
		: PropertyTemplate<T> (q, v)
	{

	}
	
	T & operator= (T const & v) {
		this->set (v);
		return this->_current;
	}
	
private:	
        /* note that we do not set a locale for the streams used
	   in to_string() or from_string(), because we want the
	   format to be portable across locales (i.e. C or
	   POSIX). Also, there is the small matter of
	   std::locale aborting on OS X if used with anything
	   other than C or POSIX locales.
	*/
        std::string to_string (T const & v) const {
		std::stringstream s;
		s.precision (12); // in case its floating point
		s << v;
		return s.str ();
	}
	
	T from_string (std::string const & s) const {
		std::stringstream t (s);
		T v;
		t >> v;
		return v;
	}
};

/** Specialization, for std::string which is common and special (see to_string() and from_string()
    Using stringstream to read from a std::string is easy to get wrong because of whitespace
    delineation, etc.
 */
template <>
class Property<std::string> : public PropertyTemplate<std::string>
{
public:
	Property (PropertyDescriptor<std::string> q, std::string const & v)
		: PropertyTemplate<std::string> (q, v)
	{

	}

	std::string & operator= (std::string const & v) {
		this->set (v);
		return this->_current;
	}
	
private:	
        std::string to_string (std::string const & v) const {
		return _current;
	}
	
	std::string from_string (std::string const & s) const {
		return s;
	}
};

class PropertyList : public std::map<PropertyID,PropertyBase*>
{
public:
    PropertyList() : property_owner (true) {}
    virtual ~PropertyList() {
	    if (property_owner)
		    for (std::map<PropertyID,PropertyBase*>::iterator i = begin(); i != end(); ++i) {
			    delete i->second;
		    }
    }
    /* classes that own property lists use this to add their
       property members to their plists.
    */
    bool add (PropertyBase& p) {
	    return insert (value_type (p.id(), &p)).second;
    }

    /* code that is constructing a property list for use 
       in setting the state of an object uses this.
    */
    template<typename T, typename V> bool add (PropertyDescriptor<T> pid, const V& v) {
	    return insert (value_type (pid.id, new Property<T> (pid, (T) v))).second;
    }

protected:
    bool property_owner;
};

/** A variant of PropertyList that does not delete its
    property list in its destructor. Objects with their
    own Properties store them in an OwnedPropertyList
    to avoid having them deleted at the wrong time.
*/

class OwnedPropertyList : public PropertyList
{
public:
    OwnedPropertyList() { property_owner = false; }
};
	    
} /* namespace PBD */

#endif /* __pbd_properties_h__ */
