//  Copyright David Abrahams 2001. Permission to copy, use,
//  modify, sell and distribute this software is granted provided this
//  copyright notice appears in all copies. This software is provided
//  "as is" without express or implied warranty, and with no claim as
//  to its suitability for any purpose.
#ifndef REGISTRY_DWA20011127_HPP
# define REGISTRY_DWA20011127_HPP
# include <boost/python/converter/type_id.hpp>
# include <boost/python/detail/config.hpp>
# include <boost/python/detail/wrap_python.hpp>
# include <boost/python/converter/to_python_function.hpp>

namespace boost { namespace python { namespace converter {

struct BOOST_PYTHON_DECL from_python_converter_base;

// This namespace acts as a sort of singleton
namespace registry
{
  BOOST_PYTHON_DECL to_python_value_function const&
  to_python_function(undecorated_type_id_t);
  
  BOOST_PYTHON_DECL void insert(to_python_value_function, undecorated_type_id_t);
  
  BOOST_PYTHON_DECL from_python_converter_base*& from_python_chain(type_id_t);
  
  BOOST_PYTHON_DECL PyTypeObject*& class_object(undecorated_type_id_t key);
}

}}} // namespace boost::python::converter

#endif // REGISTRY_DWA20011127_HPP
