// Copyright David Abrahams 2002.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/python/converter/pyobject_type.hpp>

namespace boost { namespace python { namespace converter { 

PyObject* checked_downcast_impl(PyObject* obj, PyTypeObject* type)
{
	return (PyType_IsSubtype(Py_TYPE(obj), type) ? obj : NULL);
}

}}} // namespace boost::python::conve
