// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef PYTYPE_RESULT_FROM_PYTHON_DWA2002716_HPP
# define PYTYPE_RESULT_FROM_PYTHON_DWA2002716_HPP

# include <boost/python/detail/raw_pyobject.hpp>

namespace boost { namespace python { namespace converter { 

BOOST_PYTHON_DECL python::detail::new_reference
pytype_result_from_python(PyTypeObject*, PyObject* source);

}}} // namespace boost::python::converter

#endif // PYTYPE_RESULT_FROM_PYTHON_DWA2002716_HPP
