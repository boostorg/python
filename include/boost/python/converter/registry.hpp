//  Copyright David Abrahams 2001. Permission to copy, use,
//  modify, sell and distribute this software is granted provided this
//  copyright notice appears in all copies. This software is provided
//  "as is" without express or implied warranty, and with no claim as
//  to its suitability for any purpose.
#ifndef REGISTRY_DWA20011127_HPP
# define REGISTRY_DWA20011127_HPP
# include <boost/python/type_id.hpp>
# include <boost/python/detail/config.hpp>
# include <boost/python/detail/wrap_python.hpp>
# include <boost/python/converter/to_python_function_type.hpp>
# include <boost/python/converter/rvalue_from_python_data.hpp>
# include <boost/python/converter/constructor_function.hpp>

namespace boost { namespace python { namespace converter {

struct lvalue_from_python_registration;
struct rvalue_from_python_registration;

// This namespace acts as a sort of singleton
namespace registry
{
  BOOST_PYTHON_DECL lvalue_from_python_registration*& lvalue_converters(type_info);
  BOOST_PYTHON_DECL rvalue_from_python_registration*& rvalue_converters(type_info);
  
  BOOST_PYTHON_DECL to_python_function_t const&
  get_to_python_function(type_info);
  
  BOOST_PYTHON_DECL void insert(to_python_function_t, type_info);

  // Insert an lvalue from_python converter
  BOOST_PYTHON_DECL void insert(void* (*convert)(PyObject*), type_info);

  // Insert an rvalue from_python converter
  BOOST_PYTHON_DECL void insert(
      void* (*convertible)(PyObject*)
      , constructor_function
      , type_info
      );
  
  // Insert an rvalue from_python converter at the tail of the
  // chain. Used for implicit conversions
  BOOST_PYTHON_DECL void push_back(
      void* (*convertible)(PyObject*)
      , constructor_function
      , type_info
      );
  
  BOOST_PYTHON_DECL PyTypeObject*& class_object(type_info key);
}

}}} // namespace boost::python::converter

#endif // REGISTRY_DWA20011127_HPP
