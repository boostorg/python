//  (C) Copyright David Abrahams 2000. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
//  The author gratefully acknowleges the support of Dragon Systems, Inc., in
//  producing this work.

#ifndef BASE_OBJECT_DWA051600_H_
# define BASE_OBJECT_DWA051600_H_

# include "pyconfig.h"
# include "signatures.h" // really just for Type<>
# include "wrap_python.h"
# include <cstring>

namespace py { namespace detail {

// BaseObject - adds a constructor and non-virtual destructor to a
// base Python type (e.g. PyObject, PyTypeObject).
template <class PythonType>
struct BaseObject : PythonType
{
    typedef PythonType BasePythonType;

    // Initializes type and reference count. All other fields of BasePythonType are 0
    BaseObject(PyTypeObject* type_object);

    // Decrements reference count on the type
    ~BaseObject();
};

// Easy typedefs for common usage
typedef BaseObject<PyObject> PythonObject;
typedef BaseObject<PyTypeObject> PythonType;


//
// Class template member function implementations 
//
template <class PythonType>
BaseObject<PythonType>::BaseObject(PyTypeObject* type_object)
{
    BasePythonType* bp = this;
#if !defined(_MSC_VER) || defined(__STLPORT)
    std::
#endif
		memset(bp, 0, sizeof(BasePythonType));
    ob_refcnt = 1;
    ob_type = type_object;
    Py_INCREF(type_object);
}

template <class PythonType>
inline BaseObject<PythonType>::~BaseObject()
{
    Py_DECREF(ob_type);
}

}} // namespace py::detail

#endif // BASE_OBJECT_DWA051600_H_
