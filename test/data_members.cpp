// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#include <boost/python/class.hpp>
#include <boost/python/module.hpp>
#include <boost/python/return_value_policy.hpp>
#include <boost/python/return_by_value.hpp>
#include "test_class.hpp"

#if defined(_AIX) && defined(__EDG_VERSION__) && __EDG_VERSION__ < 245
# include <iostream> // works around a KCC intermediate code generation bug
#endif


using namespace boost::python;

typedef test_class<> X;

typedef test_class<1> Y;

double get_fair_value(X const& x) { return x.value(); }

struct Var
{
    Var(std::string name_) : name(name_), value(), name2(name.c_str()) {}
    std::string const name;
    std::string get_name1() const { return name; }
    std::string const& get_name2() const { return name; }
    float value;
    char const* name2;
};

BOOST_PYTHON_MODULE(data_members_ext)
{
    class_<X>("X", init<int>())
        .def("value", &X::value)
        .def("set", &X::set)
        .def_readonly("x", &X::x)
        .add_property("fair_value", &get_fair_value)
        ;
    
    class_<Y>("Y", init<int>())
        .def("value", &Y::value)
        .def("set", &Y::set)
        .def_readwrite("x", &Y::x)
        ;

    class_<Var>("Var", init<std::string>())
        .def_readonly("name", &Var::name)
        .def_readonly("name2", &Var::name2)
        .def_readwrite("value", &Var::value)
        
        // Test return_by_value for plain values and for
        // pointers... return_by_value was implemented as a
        // side-effect of implementing data member support, so it made
        // sense to add the test here.
        .def("get_name1", &Var::get_name1, return_value_policy<return_by_value>())
        .def("get_name2", &Var::get_name2, return_value_policy<return_by_value>())
        ;
}

#include "module_tail.cpp"
