// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef TO_PYTHON_FUNCTION_TYPE_DWA200236_HPP
# define TO_PYTHON_FUNCTION_TYPE_DWA200236_HPP
# include <boost/python/detail/wrap_python.hpp>

namespace boost { namespace python { namespace converter { 

// The type of stored function pointers which actually do conversion
// by-value. The void* points to the object to be converted, and
// type-safety is preserved through runtime registration.
typedef PyObject* (*to_python_function_t)(void const*);

// Given a typesafe to_python conversion function, produces a
// to_python_function_t which can be registered in the usual way.
template <class T, class ToPython>
struct as_to_python_function
{
    static PyObject* convert(void const* x)
    {
        return ToPython::convert(*(T const*)x);
    }
};

}}} // namespace boost::python::converter

#endif // TO_PYTHON_FUNCTION_TYPE_DWA200236_HPP
