//  (C) Copyright David Abrahams 2000. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
//  The author gratefully acknowleges the support of Dragon Systems, Inc., in
//  producing this work.

#ifndef BASE_OBJECT_DWA051600_H_
# define BASE_OBJECT_DWA051600_H_

# include <boost/python/detail/config.hpp>
# include <boost/python/detail/signatures.hpp> // really just for type<>
# include <boost/python/detail/wrap_python.hpp>
# include <cstring>

namespace boost { namespace python { namespace detail {

// base_object - adds a constructor and non-virtual destructor to a
// base Python type (e.g. PyObject, PyTypeObject).
template <class python_type>
struct base_object : python_type
{
    typedef python_type base_python_type;

    // Initializes type and reference count. All other fields of base_python_type are 0
    base_object(PyTypeObject* type_obj);

    // Decrements reference count on the type
    ~base_object();
};

// Easy typedefs for common usage
typedef base_object<PyObject> python_object;
typedef base_object<PyTypeObject> python_type;


//
// class_t template member function implementations 
//
template <class python_type>
base_object<python_type>::base_object(PyTypeObject* type_obj)
{
    base_python_type* bp = this;
#if !defined(_MSC_VER) || defined(__STLPORT)
    std::
#endif
		memset(bp, 0, sizeof(base_python_type));
    ob_refcnt = 1;
    ob_type = type_obj;
    Py_INCREF(type_obj);
}

template <class python_type>
inline base_object<python_type>::~base_object()
{
    Py_DECREF(ob_type);
}

}}} // namespace boost::python::detail

#endif // BASE_OBJECT_DWA051600_H_
