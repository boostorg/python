// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.

#include <boost/python/module_init.hpp>
#include <boost/python/def.hpp>
#include <boost/python/class.hpp>
#include <boost/python/implicit.hpp>
#include <boost/mpl/list.hpp>

struct Type1 {};

struct Term {Term(Type1 const&) {} };

struct Expression {void add(Term const&) {} };

BOOST_PYTHON_MODULE_INIT(bienstman4_ext)
{
  using namespace boost::python;
  using boost::mpl::list;

  implicitly_convertible<Type1,Term>();

  class_<Expression>("Expression")
      .def("add", &Expression::add)
      ;
  
  class_<Type1>("T1")
      ;
  
  class_<Term>("Term", args<Type1&>())
      ;
  
  Type1 t1;
  Expression e;
  e.add(t1);
}

