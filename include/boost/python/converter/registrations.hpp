// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef REGISTRATIONS_DWA2002223_HPP
# define REGISTRATIONS_DWA2002223_HPP

# include <boost/python/converter/convertible_function.hpp>
# include <boost/python/converter/constructor_function.hpp>
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

struct from_python_registration
{
    explicit from_python_registration(type_info);
    
    const python::type_info target_type;
    lvalue_from_python_chain* lvalue_chain;
    rvalue_from_python_chain* rvalue_chain;
};

//
// implementations
//
inline from_python_registration::from_python_registration(type_info target_type)
    : target_type(target_type)
      , lvalue_chain(0)
      , rvalue_chain(0)
{}

}}} // namespace boost::python::converter

#endif // REGISTRATIONS_DWA2002223_HPP
