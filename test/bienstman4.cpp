// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.

#include <boost/python/module.hpp>
#include <boost/python/class.hpp>
#include <boost/python/implicit.hpp>
#include <boost/mpl/type_list.hpp>

struct Type1 {};

struct Term {Term(Type1 const&) {} };

struct Expression {void add(Term const&) {} };

BOOST_PYTHON_MODULE_INIT(bienstman4_ext)
{
  using namespace boost::python;
  using boost::mpl::type_list;

  implicitly_convertible<Type1,Term>();

  module("bienstman4_ext")
    .add(class_<Expression>("Expression")
         .def("add", &Expression::add))
    .add(class_<Type1>("T1"))
    .add(class_<Term>("Term")
         .def_init(type_list<Type1&>()))
    ;
  

  Type1 t1;
  Expression e;
  e.add(t1);
}

