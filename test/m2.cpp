// Copyright David Abrahams 2001. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.

#include <boost/python/convert.hpp>
#include <boost/python/module.hpp>
#include "simple_type.hpp"

using boost::python::wrap;
using boost::python::unwrap;

extern "C" {
    PyObject*
    unwrap_simple(PyObject* self, PyObject* args)
    {
        PyObject* p;
        if (!PyArg_ParseTuple(args, "O", &p))
            return 0;

        boost::python::unwrap<simple> in(p);
        if (!in)
            return 0;
    
        simple x = *in;
    
        return PyString_FromString(x.s);
    };

    PyObject*
    unwrap_simple_ref(PyObject* self, PyObject* args)
    {
        PyObject* p;
        if (!PyArg_ParseTuple(args, "O", &p))
            return 0;

        unwrap<simple&> in(p);
        if (!in)
            return 0;
    
        simple& x = *in;
    
        return PyString_FromString(x.s);
    };

    PyObject*
    unwrap_simple_const_ref(PyObject* self, PyObject* args)
    {
        PyObject* p;
        if (!PyArg_ParseTuple(args, "O", &p))
            return 0;
    
        unwrap<simple const&> in(p);
        if (!in)
            return 0;
    
        simple const& x = *in;
    
        return PyString_FromString(x.s);
    };

    PyObject*
    unwrap_int(PyObject* self, PyObject* args)
    {
        PyObject* p;
        if (!PyArg_ParseTuple(args, "O", &p))
            return 0;
    
        unwrap<int> in(p);
        if (!in)
            return 0;
    
        int x = *in;
    
        return PyInt_FromLong(x);
    };

    PyObject*
    unwrap_int_ref(PyObject* self, PyObject* args)
    {
        PyObject* p;
        if (!PyArg_ParseTuple(args, "O", &p))
            return 0;
    
        unwrap<int&> in(p);
        if (!in)
            return 0;
    
        int& x = *in;
    
        return PyInt_FromLong(x);
    };

    PyObject*
    unwrap_int_const_ref(PyObject* self, PyObject* args)
    {
        PyObject* p;
        if (!PyArg_ParseTuple(args, "O", &p))
            return 0;
    
        unwrap<int&> in(p);
        if (!in)
            return 0;
    
        int const& x = *in;
    
        return PyInt_FromLong(x);
    };

    // -------------------
}
template <class T> struct xxxx;

template <class T>
PyObject*
rewrap(PyObject* self, PyObject* args, xxxx<T>* = 0)
{
    PyObject* p;
    if (!PyArg_ParseTuple(args, "O", &p))
        return 0;

    boost::python::unwrap<T> in(p);
    if (!in)
        return 0;

    boost::python::wrap<T> out;
    if (!out)
        return 0;
    
    T x = *in;
    return out(x);
}

extern "C"
{
    PyObject*
    wrap_simple(PyObject* self, PyObject* args)
    {
        return rewrap<simple>(self, args);
    };

    PyObject*
    wrap_simple_ref(PyObject* self, PyObject* args)
    {
        return rewrap<simple&>(self, args);
    };

    PyObject*
    wrap_simple_const_ref(PyObject* self, PyObject* args)
    {
        return rewrap<simple const&>(self, args);
    };

    PyObject*
    wrap_int(PyObject* self, PyObject* args)
    {
        return rewrap<int>(self, args);
    };

    PyObject*
    wrap_int_ref(PyObject* self, PyObject* args)
    {
        return rewrap<int&>(self, args);
    };

    PyObject*
    wrap_int_const_ref(PyObject* self, PyObject* args)
    {
        return rewrap<int const&>(self, args);
    };
}

PyMethodDef initial_methods[] =
{
    { "unwrap_int", unwrap_int, METH_VARARGS, 0 },
    { "unwrap_int_ref", unwrap_int_ref, METH_VARARGS, 0 },
    { "unwrap_int_const_ref", unwrap_int_const_ref, METH_VARARGS, 0 },
    { "unwrap_simple", unwrap_simple, METH_VARARGS, 0 },
    { "unwrap_simple_ref", unwrap_simple_ref, METH_VARARGS, 0 },
    { "unwrap_simple_const_ref", unwrap_simple_const_ref, METH_VARARGS, 0 },

    { "wrap_int", wrap_int, METH_VARARGS, 0 },
    { "wrap_int_ref", wrap_int_ref, METH_VARARGS, 0 },
    { "wrap_int_const_ref", wrap_int_const_ref, METH_VARARGS, 0 },
    { "wrap_simple", wrap_simple, METH_VARARGS, 0 },
    { "wrap_simple_ref", wrap_simple_ref, METH_VARARGS, 0 },
    { "wrap_simple_const_ref", wrap_simple_const_ref, METH_VARARGS, 0 },
    { 0, 0, 0, 0 }
};

BOOST_PYTHON_MODULE_INIT(m2)
{
    Py_InitModule(const_cast<char*>("m2"), initial_methods);
}

#include "module_tail.cpp"
