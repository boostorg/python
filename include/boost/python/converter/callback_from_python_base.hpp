// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef CALLBACK_FROM_PYTHON_BASE_DWA200237_HPP
# define CALLBACK_FROM_PYTHON_BASE_DWA200237_HPP

namespace boost { namespace python { namespace converter { 

namespace detail
{

  // Throw an exception
  BOOST_PYTHON_DECL void throw_if_not_registered(rvalue_from_python_stage1_data const&);
  BOOST_PYTHON_DECL void* convert_rvalue(PyObject*, rvalue_from_python_stage1_data&, void* storage);
  
  BOOST_PYTHON_DECL void throw_if_not_registered(lvalue_from_python_registration*const&);
  BOOST_PYTHON_DECL void* callback_convert_reference(PyObject*, lvalue_from_python_registration*const&);
  BOOST_PYTHON_DECL void* callback_convert_pointer(PyObject*, lvalue_from_python_registration*const&);
  BOOST_PYTHON_DECL void absorb_result(PyObject*);
}

}}} // namespace boost::python::converter

#endif // CALLBACK_FROM_PYTHON_BASE_DWA200237_HPP
