// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.

#include <boost/python/converter/find_from_python.hpp>
#include <boost/python/converter/registrations.hpp>
#include <boost/python/converter/from_python_data.hpp>

namespace boost { namespace python { namespace converter { 

BOOST_PYTHON_DECL void* find(
    PyObject* source
    , rvalue_from_python_registration const* chain
    , rvalue_stage1_data& data)
{
    for (;chain != 0; chain = chain->next)
    {
        void* r = chain->convertible(source);
        if (r != 0)
        {
            data.construct = chain->construct;
            return data.convertible = r;
        }
    }
    return data.convertible = 0;
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
