// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#include <boost/python/module.hpp>
#include <boost/python/object.hpp>

using namespace boost::python;

object call_object_3(object f)
{
    return f(3);
}

object message()
{
    return object("hello, world!");
}

object number()
{
    return object(42);
}

object obj_getattr(object x, char const* name)
{
    return x._(name);
}

object obj_const_getattr(object const& x, char const* name)
{
    return x._(name);
}

void obj_setattr(object x, char const* name, object value)
{
    x._(name) = value;
}

void obj_setattr42(object x, char const* name)
{
    x._(name) = 42;
}

void obj_moveattr(object& x, char const* src, char const* dst)
{
    x._(dst) = x._(src);
}

object obj_getitem(object x, object key)
{
    return x[key];
}

object obj_getitem3(object x)
{
    return x[3];
}

object obj_const_getitem(object const& x, object key)
{
    return x[key];
}

void obj_setitem(object x, object key, object value)
{
    x[key] = value;
}

void obj_setitem42(object x, object key)
{
    x[key] = 42;
}

void obj_moveitem(object& x, object src, object dst)
{
    x[dst] = x[src];
}

void obj_moveitem2(object const& x_src, object k_src, object& x_dst, object k_dst)
{
    x_dst[k_dst] = x_src[k_src];
}

bool test(object y)
{
    return y;
}

bool test_not(object y)
{
    return !y;
}

bool test_attr(object y, char* name)
{
    return y._(name);
}

bool test_not_attr(object y, char* name)
{
    return !y._(name);
}

bool test_item(object y, object key)
{
    return y[key];
}

bool test_not_item(object y, object key)
{
    return !y[key];
}

BOOST_PYTHON_MODULE_INIT(object_ext)
{
    module("object_ext")
        .def("call_object_3", call_object_3)
        .def("message", message)
        .def("number", number)
        
        .def("obj_getattr", obj_getattr)
        .def("obj_const_getattr", obj_const_getattr)
        .def("obj_setattr", obj_setattr)
        .def("obj_setattr42", obj_setattr42)
        .def("obj_moveattr", obj_moveattr)

        
        .def("obj_getitem", obj_getitem)
        .def("obj_getitem3", obj_getitem)
        .def("obj_const_getitem", obj_const_getitem)
        .def("obj_setitem", obj_setitem)
        .def("obj_setitem42", obj_setitem42)
        .def("obj_moveitem", obj_moveitem)
        .def("obj_moveitem2", obj_moveitem2)
        
        .def("test", test)
        .def("test_not", test_not)

        .def("test_attr", test_attr)
        .def("test_not_attr", test_not_attr)

        .def("test_item", test_item)
        .def("test_not_item", test_not_item)
        ;
}

#include "module_tail.cpp"
