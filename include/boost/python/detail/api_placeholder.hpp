#ifndef BOOST_PYTHON_API_PLACE_HOLDER_HPP
#define BOOST_PYTHON_API_PLACE_HOLDER_HPP

namespace boost { namespace python {

    inline long len(object const& obj)
    {
        long result = PyObject_Length(obj.ptr());
        if (PyErr_Occurred()) throw_error_already_set();
        return result;
    }

    inline object getattr(object const& a0, const char* a1, object const& a2)
    {
        handle<> result(allow_null(PyObject_GetAttrString(
          a0.ptr(), const_cast<char*>(a1))));
        if (!PyErr_Occurred()) return object(result);
        PyErr_Clear();
        return a2;
    }

}} // namespace boost::python

#endif // BOOST_PYTHON_API_PLACE_HOLDER_HPP
