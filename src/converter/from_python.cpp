// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.

#include <boost/python/converter/find_from_python.hpp>
#include <boost/python/converter/registrations.hpp>
#include <boost/python/converter/from_python_data.hpp>

namespace boost { namespace python { namespace converter { 

BOOST_PYTHON_DECL rvalue_stage1_data find(
    PyObject* source
    , rvalue_from_python_registration const* chain)
{
    rvalue_stage1_data data;
    data.convertible = 0;
    for (;chain != 0; chain = chain->next)
    {
        void* r = chain->convertible(source);
        if (r != 0)
        {
            data.convertible = r;
            data.construct = chain->construct;
            break;
        }
    }
    return data;
}

BOOST_PYTHON_DECL rvalue_from_python_registration const* find_chain(
    PyObject* source
    , rvalue_from_python_registration const* chain)
{
    for (;chain != 0; chain = chain->next)
    {
        if (chain->convertible(source))
            break;
    }
    return chain;
}

BOOST_PYTHON_DECL void* find(
    PyObject* source
    , lvalue_from_python_registration const* chain)
{
    for (;chain != 0; chain = chain->next)
    {
        void* r = chain->convert(source);
        if (r != 0)
            return r;
    }
    return 0;
}

}}} // namespace boost::python::converter
