// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef CLASS_OBJECT_DWA200222_HPP
# define CLASS_OBJECT_DWA200222_HPP

# include <boost/python/type_id.hpp>
# include <boost/python/converter/registry.hpp>

namespace boost { namespace python { namespace objects { 

template <class T>
struct class_object
{
    static PyTypeObject*& reference;
};

template <class T>
PyTypeObject*& class_object<T>::reference
    = converter::registry::class_object(python::type_id<T>());

}}} // namespace boost::python::objects

#endif // CLASS_OBJECT_DWA200222_HPP
