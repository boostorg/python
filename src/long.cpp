// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#include <boost/python/long.hpp>

namespace boost { namespace python { 

detail::new_non_null_reference long_::call(object const& arg_)
{
    return (detail::new_non_null_reference)PyObject_CallFunction(
        (PyObject*)&PyLong_Type, "(O)", 
        arg_.ptr());
}

detail::new_non_null_reference long_::call(object const& arg_, object const& base)
{
    return (detail::new_non_null_reference)PyObject_CallFunction(
        (PyObject*)&PyLong_Type, "(OO)", 
        arg_.ptr(), base.ptr());
}

long_::long_()
    : object(
        detail::new_reference(
            PyObject_CallFunction((PyObject*)&PyLong_Type, "()"))
        )
{}

long_::long_(object_cref arg)
    : object(long_::call(arg))
{}

long_::long_(object_cref arg, object_cref base)
    : object(long_::call(arg, base))
{}


}} // namespace boost::python
