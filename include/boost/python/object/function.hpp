// Copyright David Abrahams 2001. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef FUNCTION_DWA20011214_HPP
# define FUNCTION_DWA20011214_HPP

# include <boost/python/detail/wrap_python.hpp>
# include <boost/python/export.hpp>
# include <boost/function.hpp>

namespace boost { namespace python { namespace object { 

// We use boost::function to avoid generating lots of virtual tables
typedef boost::function2<PyObject*, PyObject*, PyObject*> py_function;

struct BOOST_PYTHON_EXPORT function : PyObject
{
    function(py_function);
    ~function();
    
    PyObject* call(PyObject*, PyObject*) const;
 private:    
    py_function m_fn;
};

extern BOOST_PYTHON_EXPORT PyTypeObject function_type;

//
// implementations
//

}}} // namespace boost::python::object

#endif // FUNCTION_DWA20011214_HPP
