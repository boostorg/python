// Copyright David Abrahams 2006. Distributed under the Boost
// Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#include <boost/noncopyable.hpp>
#include <boost/python.hpp>

using namespace boost;

struct foo {
  virtual PyObject* f() {
    return NULL;
  }
};

struct foo_wrap : foo, python::wrapper<foo> {
  virtual PyObject* f() {
    python::override const o = get_override("f");
    if (o) {
      return o();
    } else {
      return foo::f();
    }
  }
};

BOOST_PYTHON_MODULE(override_null_ext) {
  python::class_<foo_wrap, noncopyable>("foo"
    , python::no_init)
    .def(python::init<>())
    .def("f", &foo_wrap::f);
}
