#include <boost/python/module.hpp>
#include <boost/python/class.hpp>
#include <boost/python/reference_existing_object.hpp>
#include <boost/python/return_value_policy.hpp>

struct A {};

struct V 
{

 virtual void f() = 0;

 const A* inside() {return &a;}

 A a;
};

const A* outside(const V& v) {return &v.a;}

BOOST_PYTHON_MODULE_INIT(bienstman1_ext)
{
  using namespace boost::python;
  using boost::shared_ptr;
  using boost::python::return_value_policy;
  using boost::python::reference_existing_object;

  module m("bienstman1_ext");
  
  m
    .add(class_<A, shared_ptr<A> >("A"))

    .add(
      class_<V, boost::noncopyable>("V")
      .def("inside", &V::inside, 
           return_value_policy<reference_existing_object>())
      .def("outside", outside, 
           return_value_policy<reference_existing_object>())
      )
    ;
}

