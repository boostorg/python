// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#include <boost/python/module.hpp>
#include <boost/python/return_value_policy.hpp>
#include <boost/python/manage_new_object.hpp>
#include <boost/python/class.hpp>
#include <boost/mpl/type_list.hpp>

using namespace boost::python;
using boost::mpl::type_list;

int a_instances = 0;

int num_a_instances() { return a_instances; }

struct A
{
    A(std::string const& s)
        : s(s)
    {
        ++a_instances;
    }
    
    ~A()
    {
        --a_instances;
    }

    std::string content() const
    {
        return s;
    }
    
    std::string s;
};

A* create(std::string const& s)
{
    return new A(s);
}

BOOST_PYTHON_MODULE_INIT(test_pointer_adoption_ext)
{
    boost::python::module("test_pointer_adoption_ext")
        .def("num_a_instances", num_a_instances)

        // Specify the manage_new_object return policy to take
        // ownership of create's result
        .def("create", create, return_value_policy<manage_new_object>())
        
        .add(
            class_<A>()
                .def("content", &A::content)
            )
        
        ;
}

