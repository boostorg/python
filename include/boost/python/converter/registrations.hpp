// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef REGISTRATIONS_DWA2002223_HPP
# define REGISTRATIONS_DWA2002223_HPP

# include <boost/python/converter/from_python_function.hpp>

namespace boost { namespace python { namespace converter { 

struct lvalue_from_python_registration
{
    void* (*convert)(PyObject* source);
    lvalue_from_python_registration* next;
};

struct rvalue_from_python_registration
{
    void* (*convertible)(PyObject*);
    constructor_function construct;
    rvalue_from_python_registration* next;
};

}}} // namespace boost::python::converter

#endif // REGISTRATIONS_DWA2002223_HPP
