// Copyright David Abrahams 2001. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef FUNCTION_DWA20011214_HPP
# define FUNCTION_DWA20011214_HPP

# include <boost/python/detail/wrap_python.hpp>
# include <boost/python/detail/config.hpp>
# include <boost/python/handle.hpp>
# include <boost/function/function2.hpp>
# include <boost/python/object_fwd.hpp>

namespace boost { namespace python { namespace objects { 

// We use boost::function to avoid generating lots of virtual tables
typedef boost::function2<PyObject*, PyObject*, PyObject*> py_function;

struct BOOST_PYTHON_DECL function : PyObject
{
    function(py_function, unsigned min_args, unsigned max_args = 0);
    ~function();
    
    PyObject* call(PyObject*, PyObject*) const;

    // Add an attributeto the name_space with the given name. If it is
    // a function object (this class), and an existing function is
    // already there, add it as an overload.
    static void add_to_namespace(
        object const& name_space, char const* name, object const& attribute);
    
 private: // helper functions
    void argument_error(PyObject* args, PyObject* keywords) const;
    void add_overload(function*);
    
 private: // data members
    py_function m_fn;
    unsigned m_min_args;
    unsigned m_max_args;
    function* m_overloads;
};

}}} // namespace boost::python::objects

#endif // FUNCTION_DWA20011214_HPP
