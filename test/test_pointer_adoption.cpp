// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#include <boost/python/module.hpp>
#include <boost/python/return_value_policy.hpp>
#include <boost/python/manage_new_object.hpp>
#include <boost/python/return_internal_reference.hpp>
#include <boost/python/class.hpp>
#include <boost/mpl/type_list.hpp>

using namespace boost::python;
using boost::mpl::type_list;

int a_instances = 0;

int num_a_instances() { return a_instances; }

struct inner
{
    inner(std::string const& s)
        : s(s)
    {}

    void change(std::string const& new_s)
    {
        this->s = new_s;
    }
    
    std::string s;
};

struct A
{
    A(std::string const& s)
        : x(s)
    {
        ++a_instances;
    }
    
    ~A()
    {
        --a_instances;
    }

    std::string content() const
    {
        return x.s;
    }

    inner& get_inner()
    {
        return x;
    }

    inner x;
};

struct B
{
    B() : x(0) {}
    
    inner const* adopt(A* x) { this->x = x; return &x->get_inner(); }

    std::string a_content()
    {
        return x ? x->content() : std::string("empty");
    }

    A* x;
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
            .def("get_inner", &A::get_inner, return_internal_reference<>())
            )

        .add(
            class_<inner>()
            .def("change", &inner::change)
            )
        
        .add(
            class_<B>("B")
            .def_init()
            
            .def("adopt", &B::adopt
                 // Adopt returns a pointer referring to a subobject of its 2nd argument (1st being "self")
                 , return_internal_reference<2
                      // Meanwhile, self holds a reference to the 2nd argument.
                      , with_custodian_and_ward<1,2> >()
                )
            
            .def("a_content", &B::a_content)
            )
        ;
}

