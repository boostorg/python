// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#include <boost/python.hpp>

using namespace boost::python;

struct Callback
{
    Callback(PyObject* o) : mSelf(o) {}
    PyObject* mSelf;
};

struct A
{
    virtual ~A(){}
    virtual std::string f() { return "A::f()"; }
};

struct ACallback :  A,  Callback
{
    ACallback (PyObject* self) : Callback(self) {}
    
    
    std::string f()
    {
        return call_method<std::string>(mSelf, "f");
    }
    
    std::string default_f()
    {
        return A::f();
    }
};

struct B : A
{
    virtual std::string f() { return "B::f()"; }
};

A& getBCppObj ()
{
    static B b;
    return b;
}

std::string call_f(A& a) { return a.f(); }

BOOST_PYTHON_MODULE_INIT(polymorphism_ext)
{
    class_<A,boost::noncopyable,ACallback>("A")
        .def("f", &A::f, &ACallback::default_f)
        ;
    
    def("getBCppObj", getBCppObj, return_value_policy<reference_existing_object>());

    def("call_f", call_f);
}

//#include "module_tail.cpp"
