// Copyright David Abrahams 2001. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.


#include "simple_type.hpp"
#include "complicated.hpp"
#include <boost/python/module.hpp>
#include <boost/python/class.hpp>
#include <boost/python/object/value_holder.hpp>
#include <boost/python/object/pointer_holder.hpp>
#include <boost/python/object/class.hpp>
//#include <boost/python/object/inheritance.hpp>
#include <boost/python/converter/class.hpp>
#include <boost/python/reference_from_python.hpp>
#include <boost/python/value_from_python.hpp>
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
struct SimpleObject
{
    PyObject_HEAD
    simple x;

    static simple& extract(SimpleObject& o) { return o.x; }
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
using boost::python::converter::from_python_data;

// Wrap a simple by converting it to a Simple
PyObject* simple_to_python(simple const& x)
{
    SimpleObject* p = PyObject_New(SimpleObject, &SimpleType);
    p->x = x;
    return (PyObject*)p;
}


// wrap a mutable reference to a simple by converting it to a
// Simple. Normally we wouldn't do it this way, since modifications to
// the result clearly don't change the original object, but here we're
// just proving that the mechanism works.
PyObject* simple_ref_to_python(simple& x)
{
    SimpleObject* p = PyObject_New(SimpleObject, &SimpleType);
    p->x = x;
    return (PyObject*)p;
}

int noddy_to_int(PyObject* p, from_python_data&)
{
    return static_cast<NoddyObject*>(p)->x;
}

// Extract a mutable reference to an int from a Noddy.
int& noddy_to_int_ref(PyObject* p, from_python_data&) 
{
    return static_cast<NoddyObject*>(p)->x;
}

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
    char const* name() { return "B"; }
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

int take_a(A const& a) { return a.x; }
int take_b(B const& b) { return b.x; }
int take_c(C const& c) { return c.x; }
int take_d(D const& d) { return d.x; }
    
BOOST_PYTHON_MODULE_INIT(m1)
{
    using boost::python::module;
    using boost::python::class_;
    using boost::python::converter::to_python_converter;
    using boost::python::converter::from_python_converter;
    using boost::python::reference_from_python;
    using boost::python::value_from_python;
    using boost::python::type_from_python;
    using boost::python::get_member;
    
    // Create the converters; they are self-registering/unregistering.
    static to_python_converter<simple const&> c1(simple_to_python);

    static from_python_converter<int> c2(
        &(boost::python::type_from_python<&NoddyType>::convertible), noddy_to_int);
    
    static from_python_converter<int&> c3(
        &(boost::python::type_from_python<&NoddyType>::convertible), noddy_to_int_ref);

    static boost::python::reference_from_python<
        &SimpleType
        , simple
        , SimpleObject
        , &SimpleObject::extract
        >
        unwrap_simple;
    
    static to_python_converter<simple&> simple_ref_wrapper(simple_ref_to_python);

    module m1("m1");

    typedef boost::python::objects::pointer_holder_generator<
        boost::python::objects::shared_ptr_generator
    > use_shared_ptr;

    m1
      // Insert the metaclass for all extension classes
      .setattr("xclass", boost::python::objects::class_metatype())
    
      // Insert the base class for all extension classes
      .setattr("xinst", boost::python::objects::class_type())

      .def("new_noddy", new_noddy)
      .def("new_simple", new_simple)

      // Expose f()
      .def("f", f)

      // Expose g()
      .def("g", g)

      .def("take_a", take_a)
      .def("take_b", take_b)
      .def("take_c", take_c)
      .def("take_d", take_d)

      .add(
          class_<A, bases<>, use_shared_ptr>("A")
          .def_init()
          .def("name", &A::name)
          )
        
        ;

    // sequence points don't ensure that "A" is constructed before "B"
    // or "C" below if we make them part of the same chain
    m1
        .add(
            class_<B,bases<A>, use_shared_ptr>("B")
            .def_init()
            .def("name", &B::name)
            )
        
        .add(
            class_<C,bases<A>, use_shared_ptr>("C")
            .def_init()
            .def("name", &C::name)
            )
        ;

    m1
        .add(
            class_<D,bases<B,C>, use_shared_ptr>("D")
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
