// Copyright David Abrahams 2001. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.

#include "simple_type.hpp"
#include "complicated.hpp"
#include <boost/python/converter/wrapper.hpp>
#include <boost/python/converter/unwrapper.hpp>
#include <boost/python/detail/config.hpp>
#include <boost/python/convert.hpp>
#include <boost/python/module.hpp>
#include <boost/python/object/value_holder.hpp>
#include <boost/python/object/class.hpp>
#include <boost/python/converter/class.hpp>
#include <boost/python/make_function.hpp>
#include <boost/python/errors.hpp>
#include <boost/mpl/type_list.hpp>
#include <string.h>

// Declare some straightforward extension types
extern "C" void
dealloc(PyObject* self)
{
    PyObject_Del(self);
}

// Noddy is a type we got from one of the Python sample files
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

// Create a Noddy containing 42
PyObject* new_noddy()
{
    NoddyObject* noddy = PyObject_New(NoddyObject, &NoddyType);
    noddy->x = 42;
    return (PyObject*)noddy;
}

// Simple is a wrapper around a struct simple, which just contains a char*
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

// Create a Simple containing "hello, world"
PyObject* new_simple()
{
    SimpleObject* simple = PyObject_New(SimpleObject, &SimpleType);
    simple->x.s = "hello, world";
    return (PyObject*)simple;
}

//
// Declare some wrappers/unwrappers to test the low-level conversion
// mechanism. See boost/python/converter/source.hpp,target.hpp for a
// description of how the type parameters to wrapper<> and unwrapper<>
// are selected.
//

// Wrap an int by converting it to a Python Int
struct int_wrapper
    : boost::python::converter::wrapper<int const&>
{
    PyObject* convert(int const& x) const
    {
        return PyInt_FromLong(x);
    }
};

// Wrap a simple by converting it to a Simple
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

// wrap a mutable reference to a simple by converting it to a
// Simple. Normally we wouldn't do it this way, since modifications to
// the result clearly don't change the original object, but here we're
// just proving that the mechanism works.
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

// extract an int from a Python Int by converting it to an int. Since
// int is a scalar type, we convert by-value. Since Python Ints are
// immutable, there's no non-const reference converter.
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

// Extract an int from a Noddy
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

// Extract a mutable reference to an int from a Noddy.
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

// Extract a mutable reference to a simple from a Simple
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

// Extract a const reference to a simple from a Simple
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

//
// Some C++ functions to expose to Python
//

// Returns the length of s's held string
int f(simple const& s)
{
    return strlen(s.s);
}

// A trivial passthru function for simple objects
simple const& g(simple const& x)
{
    return x;
}

BOOST_PYTHON_MODULE_INIT(m1)
{
    boost::python::module m1("m1");

    // Create the converters; they are self-registering/unregistering.
    static int_wrapper wrap_int;
    static simple_wrapper wrap_simple;
    static native_int_unwrapper unwrap_int1;
    static noddy_int_unwrapper unwrap_int2;
    static noddy_int_ref_unwrapper unwrap_int3;
    static simple_ref_unwrapper unwrap_simple;
    static simple_const_ref_unwrapper unwrap_simple_const_ref;
    static simple_ref_wrapper wrap_simple_ref;

    // This unwrapper extracts pointers and references to the "complicated" class.
    static boost::python::converter::class_unwrapper<complicated> unwrap_complicated;
    
    // Insert the extension metaclass object
    m1.add(boost::python::objects::class_metatype(), "xclass");
    
    // Insert the base class for all extension classes
    m1.add(boost::python::objects::class_type(), "xinst");

    m1.def(new_noddy, "new_noddy");
    m1.def(new_simple, "new_simple");
    
    // Expose f()
    m1.def(f, "f");

    // Expose g()
    m1.def(g, "g");

    // Expose complicated's get_n() member function. See newtest.py
    // for how it's used to build an extension class.
    m1.def(&complicated::get_n, "get_n");

    // Expose complicated::complicated(simple const&, int) as init1
    boost::python::objects::function* init = boost::python::make_constructor<
        complicated
        , boost::mpl::type_list<simple const&,int>
        , boost::python::objects::value_holder_generator>();
    
    boost::python::ref manager(init);
    
    init->add_overload(
        boost::python::make_constructor<
        complicated
        , boost::mpl::type_list<simple const&>
        , boost::python::objects::value_holder_generator>());
    
    m1.add(manager, "init1");
}

#include "module_tail.cpp"
