// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef REGISTRATIONS_DWA2002223_HPP
# define REGISTRATIONS_DWA2002223_HPP

# include <boost/python/detail/wrap_python.hpp>
# include <boost/python/converter/convertible_function.hpp>
# include <boost/python/converter/constructor_function.hpp>
# include <boost/python/converter/to_python_function_type.hpp>
# include <boost/python/type_id.hpp>

namespace boost { namespace python { namespace converter { 

struct lvalue_from_python_chain
{
    convertible_function convert;
    lvalue_from_python_chain* next;
};

struct rvalue_from_python_chain
{
    convertible_function convertible;
    constructor_function construct;
    rvalue_from_python_chain* next;
};

struct registration
{
    explicit registration(type_info);
    
    const python::type_info target_type;

    // The chain of eligible from_python converters when an lvalue is required
    lvalue_from_python_chain* lvalue_chain;

    // The chain of eligible from_python converters when an rvalue is acceptable
    rvalue_from_python_chain* rvalue_chain;
    
    // The unique to_python converter for the associated C++ type.
    to_python_function_t to_python;

    // The class object associated with this type
    PyTypeObject* class_object;
};

//
// implementations
//
inline registration::registration(type_info target_type)
    : target_type(target_type)
      , lvalue_chain(0)
      , rvalue_chain(0)
      , to_python(0)
      , class_object(0)
{}

inline bool operator<(registration const& lhs, registration const& rhs)
{
    return lhs.target_type < rhs.target_type;
}

}}} // namespace boost::python::converter

#endif // REGISTRATIONS_DWA2002223_HPP
