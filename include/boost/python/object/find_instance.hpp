// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef FIND_INSTANCE_DWA2002312_HPP
# define FIND_INSTANCE_DWA2002312_HPP

# include <boost/python/converter/type_id.hpp>
# include <boost/python/converter/registry.hpp>

namespace boost { namespace python { namespace objects { 

// Given an undecorated type_id, find the instance data which
// corresponds to it, or return 0 in case no such type is held.
BOOST_PYTHON_DECL void* find_instance_impl(PyObject*, converter::undecorated_type_id_t);

// This produces a function with the right signature for use in from_python conversions
template <class T>
struct instance_finder
{
    instance_finder()
    {
        converter::registry::insert(&execute, converter::undecorated_type_id<T>());
    }

    static instance_finder const registration;
 private:
    static inline void* execute(PyObject* p)
    {
        return find_instance_impl(p, converter::undecorated_type_id<T>());
    }
};

template <class T>
instance_finder<T> const instance_finder<T>::registration;

}}} // namespace boost::python::objects

#endif // FIND_INSTANCE_DWA2002312_HPP
