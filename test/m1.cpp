// Copyright David Abrahams 2001. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.

// Seems to be neccessary to suppress an ICE with MSVC
#include "boost/mpl/comparison/less.hpp"

#include "simple_type.hpp"
#include "complicated.hpp"
#include <boost/python/converter/wrapper.hpp>
#include <boost/python/converter/unwrapper.hpp>
#include <boost/python/detail/config.hpp>
#include <boost/python/convert.hpp>
#include <boost/python/object/value_holder.hpp>
#include <boost/python/object/class.hpp>
#include <boost/python/converter/class.hpp>
#include <boost/python/make_function.hpp>
#include <boost/python/errors.hpp>
#include <boost/mpl/type_list.hpp>
#include <string.h>

extern "C" void
dealloc(PyObject* self)
{
    PyObject_Del(self);
}

struct NoddyObject : PyObject
{
    int x;
};

PyTypeObject NoddyType = {
    PyObject_HEAD_INIT(NULL)
    0,
    "Noddy",
    sizeof(NoddyObject),
    0,
    dealloc, /*tp_dealloc*/
    0,          /*tp_print*/
    0,          /*tp_getattr*/
    0,          /*tp_setattr*/
    0,          /*tp_compare*/
    0,          /*tp_repr*/
    0,          /*tp_as_number*/
    0,          /*tp_as_sequence*/
    0,          /*tp_as_mapping*/
    0,          /*tp_hash */
};

struct SimpleObject : PyObject
{
    simple x;
};

PyTypeObject SimpleType = {
    PyObject_HEAD_INIT(NULL)
    0,
    "Simple",
    sizeof(SimpleObject),
    0,
    dealloc, /*tp_dealloc*/
    0,          /*tp_print*/
    0,          /*tp_getattr*/
    0,          /*tp_setattr*/
    0,          /*tp_compare*/
    0,          /*tp_repr*/
    0,          /*tp_as_number*/
    0,          /*tp_as_sequence*/
    0,          /*tp_as_mapping*/
    0,          /*tp_hash */
};

extern "C" PyObject*
new_noddy(PyObject* self, PyObject* args)
{
    NoddyObject* noddy;

    if (!PyArg_ParseTuple(args,":new_noddy")) 
        return NULL;

    noddy = PyObject_New(NoddyObject, &NoddyType);
    noddy->x = 42;
    
    return (PyObject*)noddy;
}

extern "C" PyObject*
new_simple(PyObject* self, PyObject* args)
{
    SimpleObject* simple;

    if (!PyArg_ParseTuple(args,":new_simple")) 
        return NULL;

    simple = PyObject_New(SimpleObject, &SimpleType);
    simple->x.s = "hello, world";
    
    return (PyObject*)simple;
}

static PyMethodDef methods[] = {
    { "new_noddy", new_noddy, METH_VARARGS },
    { "new_simple", new_simple, METH_VARARGS },
    {0, 0, 0, 0}
};

struct int_wrapper
    : boost::python::converter::wrapper<int const&>
{
    PyObject* convert(int const& x) const
    {
        return PyInt_FromLong(x);
    }
};

struct simple_wrapper
    : boost::python::converter::wrapper<simple const&>
{
    PyObject* convert(simple const& x) const
    {
        SimpleObject* p = PyObject_New(SimpleObject, &SimpleType);
        p->x = x;
        return p;
    }
};

struct simple_ref_wrapper
    : boost::python::converter::wrapper<simple&>
{
    PyObject* convert(simple& x) const
    {
        SimpleObject* p = PyObject_New(SimpleObject, &SimpleType);
        p->x = x;
        return p;
    }
};

struct native_int_unwrapper
    : boost::python::converter::unwrapper<int>
{
    void* can_convert(PyObject* p) const
    {
        return PyInt_Check(p) ? non_null : 0;
    }
    
    int convert(PyObject* p, void*, boost::type<int>) const
    {
        return PyInt_AsLong(p);
    }
};

struct noddy_int_unwrapper
    : boost::python::converter::unwrapper<int>
{
    void* can_convert(PyObject* p) const
    {
        return p->ob_type == &NoddyType ? non_null : 0;
    }
    
    int convert(PyObject* p, void*, boost::type<int>) const
    {
        return static_cast<NoddyObject*>(p)->x;
    }
};

struct noddy_int_ref_unwrapper
    : boost::python::converter::unwrapper<int&>
{
    void* can_convert(PyObject* p) const
    {
        return p->ob_type == &NoddyType ? non_null : 0;
    }
    
    int& convert(PyObject* p, void*, boost::type<int&>) const
    {
        return static_cast<NoddyObject*>(p)->x;
    }
};

struct simple_ref_unwrapper
    : boost::python::converter::unwrapper<simple&>
{
    void* can_convert(PyObject* p) const
    {
        return p->ob_type == &SimpleType ? non_null : 0;
    }
    
    simple& convert(PyObject* p, void*, boost::type<simple&>) const
    {
        return static_cast<SimpleObject*>(p)->x;
    }
};

struct simple_const_ref_unwrapper
    : boost::python::converter::unwrapper<simple const&>
{
    void* can_convert(PyObject* p) const
    {
        return p->ob_type == &SimpleType ? non_null : 0;
    }
    
    simple const& convert(PyObject* p, void*, boost::type<simple const&>) const
    {
        return static_cast<SimpleObject*>(p)->x;
    }
};

int f(simple const& s)
{
    return strlen(s.s);
}

simple const& g(simple const& x)
{
    return x;
}

BOOST_PYTHON_MODULE_INIT(m1)
{
    PyObject* m1 = Py_InitModule(const_cast<char*>("m1"), methods);

    static int_wrapper wrap_int;
    static simple_wrapper wrap_simple;
    static native_int_unwrapper unwrap_int1;
    static noddy_int_unwrapper unwrap_int2;
    static noddy_int_ref_unwrapper unwrap_int3;
    static simple_ref_unwrapper unwrap_simple;
    static simple_const_ref_unwrapper unwrap_simple_const_ref;
#ifdef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    // These compilers will need additional converters
    static simple_ref_wrapper wrap_simple_ref;
#endif
    static boost::python::converter::class_unwrapper<complicated> unwrap_complicated;
    
    PyObject* d = PyModule_GetDict(m1);
    if (d == NULL)
        return;

    if (PyDict_SetItemString(
            d, "xclass", (PyObject *)boost::python::object::class_metatype()) < 0)
        return;

    if (PyDict_SetItemString(
            d, "xinst", (PyObject *)boost::python::object::class_type()) < 0)
        return;

    if (PyDict_SetItemString(
            d, "f", boost::python::make_function(f)) < 0)
        return;

    if (PyDict_SetItemString(
            d, "g", boost::python::make_function(g)) < 0)
        return;

    if (PyDict_SetItemString(
            d, "get_n", boost::python::make_function(&complicated::get_n)) < 0)
        return;

    if (PyDict_SetItemString(
            d, "init1"
            , boost::python::make_constructor<
                complicated
                , boost::mpl::type_list<simple const&,int>
                , boost::python::object::value_holder_generator>()
            ) < 0)
        return;

    if (PyDict_SetItemString(
            d, "init2"
            , boost::python::make_constructor<
                complicated
                , boost::mpl::type_list<simple const&>
                , boost::python::object::value_holder_generator>()
            ) < 0)
        return;
}

#include "module_tail.cpp"
