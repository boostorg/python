// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.

#include <boost/python/module.hpp>
#include <boost/python/class.hpp>
#include <boost/python/extract.hpp>
#include <boost/python/def.hpp>
#include "test_class.hpp"

#include <memory>

using namespace boost::python;

typedef test_class<> X;

int look(std::auto_ptr<X> const& x)
{
    return (x.get()) ? x->value() : -1;
}

int steal(std::auto_ptr<X> x)
{
    return x->value();
}

int maybe_steal(std::auto_ptr<X>& x, bool doit)
{
    int n = x->value();
    if (doit)
        x.release();
    return n;
}

std::auto_ptr<X> make()
{
    return std::auto_ptr<X>(new X(77));
}

std::auto_ptr<X> callback(object f)
{
    std::auto_ptr<X> x(new X(77));
    return call<std::auto_ptr<X> >(f.ptr(), x);
}

std::auto_ptr<X> extract_(object o)
{
    return extract<std::auto_ptr<X>&>(o);
}

BOOST_PYTHON_MODULE(auto_ptr_ext)
{
    class_<X, std::auto_ptr<X>, boost::noncopyable>("X", init<int>())
        .def("value", &X::value)
        ;
    
    def("look", look);
    def("steal", steal);
    def("maybe_steal", maybe_steal);
    def("make", make);
    def("callback", callback);
    def("extract", extract_);
}

#include "module_tail.cpp"

