// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef OBJECT_ITEMS_DWA2002615_HPP
# define OBJECT_ITEMS_DWA2002615_HPP

# include <boost/python/proxy.hpp>
# include <boost/python/object_core.hpp>
# include <boost/python/object_protocol.hpp>

namespace boost { namespace python { namespace api {

struct const_item_policies
{
    static object get(object const& target, object const& key);
};
  
struct item_policies : const_item_policies
{
    static object const& set(object const& target, object const& key, object const& value);
};

//
// implementation
//
template <class U>
inline object_item
object_operators<U>::operator[](self_cref key)
{
    return object_item(*static_cast<U*>(this), key);
}

template <class U>
inline const_object_item
object_operators<U>::operator[](self_cref key) const
{
    return const_object_item(*static_cast<U const*>(this), key);
}

# if !defined(BOOST_MSVC) || BOOST_MSVC > 1300
template <class U>
template <class T>
inline const_object_item
object_operators<U>::operator[](T const& key) const
{
    return (*this)[object(key)];
}

template <class U>
template <class T>
inline object_item
object_operators<U>::operator[](T const& key)
{
    return (*this)[object(key)];
}
# endif 


inline object const_item_policies::get(object const& target, object const& key)
{
    return python::getitem(target, key);
}

inline object const& item_policies::set(
    object const& target
    , object const& key
    , object const& value)
{
    python::setitem(target, key, value);
    return value;
}

} // namespace api

namespace converter
{
  // These specializations are a lie; the proxies do not directly
  // manage an object. What actually happens is that the implicit
  // conversion to object takes hold and its conversion to_python is
  // used. That's OK in part because the object temporary *is*
  // actually managing the object during the duration of the
  // conversion.
  template <>
  struct is_object_manager<api::object_item>
  {
      BOOST_STATIC_CONSTANT(bool, value = true);
  };

  template <>
  struct is_object_manager<api::const_object_item>
  {
      BOOST_STATIC_CONSTANT(bool, value = true);
  };
}

}} // namespace boost::python

#endif // OBJECT_ITEMS_DWA2002615_HPP
