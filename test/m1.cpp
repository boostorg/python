// Copyright David Abrahams 2001. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.


#include "simple_type.hpp"
#include "complicated.hpp"
#include <boost/python/module.hpp>
#include <boost/python/class.hpp>
#include <boost/python/type_from_python.hpp>
#include <boost/python/object/value_holder.hpp>
#include <boost/python/object/pointer_holder.hpp>
#include <boost/python/object/class.hpp>
#include <boost/python/copy_const_reference.hpp>
#include <boost/python/return_value_policy.hpp>
#include <boost/python/to_python_converter.hpp>
#include <boost/python/errors.hpp>
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
struct SimpleObject
{
    PyObject_HEAD
    simple x;
};

struct extract_simple_object
{
    static simple& execute(SimpleObject& o) { return o.x; }
};

PyTypeObject SimpleType = {
    PyObject_HEAD_INIT(NULL)
    0,
    "Simple",
    sizeof(SimpleObject),
    0,
    dealloc,    /*tp_dealloc*/
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
using boost::python::to_python_converter;

// Wrap a simple by copying it into a Simple
struct simple_to_python
    : to_python_converter<simple, simple_to_python>
{
    static PyObject* convert(simple const& x)
    {
        SimpleObject* p = PyObject_New(SimpleObject, &SimpleType);
        p->x = x;
        return (PyObject*)p;
    }
};

struct int_from_noddy_extractor
{
    static int& execute(NoddyObject& p)
    {
        return p.x;
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

int f_mutable_ref(simple& s)
{
    return strlen(s.s);
}

int f_mutable_ptr(simple* s)
{
    return strlen(s->s);
}

int f_const_ptr(simple const* s)
{
    return strlen(s->s);
}

int f2(SimpleObject const& s)
{
    return strlen(s.x.s);
}

// A trivial passthru function for simple objects
simple const& g(simple const& x)
{
    return x;
}

struct A
{
    A() : x(0) {}
    virtual ~A() {}
    char const* name() { return "A"; }
    int x;
};

struct B : A
{
    B() : x(1) {}
    static char const* name(B*) { return "B"; }
    int x;
};


struct C : A
{
    C() : x(2) {}
    char const* name() { return "C"; }
    virtual ~C() {}
    int x;
};

struct D : B, C
{
    D() : x(3) {}
    char const* name() { return "D"; }
    int x;
};

A take_a(A const& a) { return a; }
B take_b(B const& b) { return b; }
C take_c(C const& c) { return c; }
D take_d(D const& d) { return d; }
    
BOOST_PYTHON_MODULE_INIT(m1)
{
    using namespace boost::python;
    using boost::shared_ptr;
    
    simple_to_python();

    type_from_python<&NoddyType,int_from_noddy_extractor>();

    boost::python::type_from_python<
        &SimpleType
#if !defined(BOOST_MSVC) || BOOST_MSVC > 1300
        , member_extractor<SimpleObject, simple, &SimpleObject::x>
#else 
        , extract_simple_object
#endif 
        >();

    type_from_python<&SimpleType, identity_extractor<SimpleObject> >();
    
    module m1("m1");

    m1
      // Insert the metaclass for all extension classes
      .setattr("xclass", boost::python::objects::class_metatype())
    
      // Insert the base class for all extension classes
      .setattr("xinst", boost::python::objects::class_type())

      .def("new_noddy", new_noddy)
      .def("new_simple", new_simple)

      // Expose f() in all its variations
      .def("f", f)
      .def("f_mutable_ref", f_mutable_ref)
      .def("f_mutable_ptr", f_mutable_ptr)
      .def("f_const_ptr", f_const_ptr)

      .def("f2", f2)
        
      // Expose g()
      .def("g", g , return_value_policy<copy_const_reference>()
          )

      .def("take_a", take_a)
      .def("take_b", take_b)
      .def("take_c", take_c)
      .def("take_d", take_d)

      .add(
          class_<A, shared_ptr<A> >("A")
          .def_init()
          .def("name", &A::name)
          )
        
        ;

    // sequence points don't ensure that "A" is constructed before "B"
    // or "C" below if we make them part of the same chain
    m1
        .add(
            class_<B,bases<A>, shared_ptr<B> >("B")
            .def_init()
            .def("name", &B::name)
            )
        
        .add(
            class_<C,bases<A>, shared_ptr<C> >("C")
            .def_init()
            .def("name", &C::name)
            )
        ;

    m1
        .add(
            class_<D,shared_ptr<D>, bases<B,C> >("D")
            .def_init()
            .def("name", &D::name)
            )

        .add(
            class_<complicated>("complicated")
            .def_init(args<simple const&,int>())
            .def_init(args<simple const&>())
            .def("get_n", &complicated::get_n)
            )
        ;
}

#include "module_tail.cpp"
