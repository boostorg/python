// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef OBJECT_PROTOCOL_DWA2002615_HPP
# define OBJECT_PROTOCOL_DWA2002615_HPP

# include <boost/python/detail/config.hpp>
# include <boost/python/detail/wrap_python.hpp>
# include <boost/python/object_protocol_core.hpp>
# include <boost/python/object_core.hpp>

namespace boost { namespace python { 

template <class Target, class Key>
inline object getattr(Target const& target, Key const& key)
{
    return getattr(object(target), object(key));
}


template <class Key, class Value>
inline void setattr(object const& target, Key const& key, Value const& value)
{
    return setattr(target, object(key), object(value));
}

template <class Target, class Key>
inline object getitem(Target const& target, Key const& key)
{
    return getitem(object(target), object(key));
}


template <class Key, class Value>
inline void setitem(object const& target, Key const& key, Value const& value)
{
    return setitem(target, object(key), object(value));
}


}} // namespace boost::python

#endif // OBJECT_PROTOCOL_DWA2002615_HPP
