//  (C) Copyright R.W. Grosse-Kunstleve 2002.
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies. This
//  software is provided "as is" without express or implied warranty, and
//  with no claim as to its suitability for any purpose.
#ifndef BOOST_PYTHON_OBJECT_PICKLE_SUPPORT_RWGK20020603_HPP
#define BOOST_PYTHON_OBJECT_PICKLE_SUPPORT_RWGK20020603_HPP

#include <boost/python/object/class.hpp>
#include <boost/python/tuple.hpp>

namespace boost { namespace python {

handle<> make_instance_reduce_function();

namespace error_messages {

  template <class T>
  struct missing_pickle_support_function_or_incorrect_signature {};

}

class pickle_support_base
{
  private:
    struct dummy_return_type_ {};

  public:
    template <class Class_, class Tgetinitargs>
    static
    void
    register_(
      Class_& cl,
      tuple (*getinitargs_fn)(Tgetinitargs),
      dummy_return_type_* (*getstate_fn)(),
      dummy_return_type_* (*setstate_fn)(),
      bool)
    {
      cl.enable_pickle_support(false);
      cl.def("__getinitargs__", getinitargs_fn);
    }

    template <class Class_, class Tgetstate, class Tsetstate>
    static
    void
    register_(
      Class_& cl,
      dummy_return_type_* (*getinitargs_fn)(),
      tuple (*getstate_fn)(Tgetstate),
      void (*setstate_fn)(Tsetstate, object),
      bool getstate_manages_dict)
    {
      cl.enable_pickle_support(getstate_manages_dict);
      cl.def("__getstate__", getstate_fn);
      cl.def("__setstate__", setstate_fn);
    }

    template <class Class_,
              class Tgetinitargs, class Tgetstate, class Tsetstate>
    static
    void
    register_(
      Class_& cl,
      tuple (*getinitargs_fn)(Tgetinitargs),
      tuple (*getstate_fn)(Tgetstate),
      void (*setstate_fn)(Tsetstate, object),
      bool getstate_manages_dict)
    {
      cl.enable_pickle_support(getstate_manages_dict);
      cl.def("__getinitargs__", getinitargs_fn);
      cl.def("__getstate__", getstate_fn);
      cl.def("__setstate__", setstate_fn);
    }

    template <class Class_>
    static
    void
    register_(
      Class_&,
      ...)
    {
      typedef typename
        error_messages::missing_pickle_support_function_or_incorrect_signature<
          Class_>::error_type error_type;
    }

    static dummy_return_type_* getinitargs() { return 0; }
    static dummy_return_type_* getstate() { return 0; }
    static dummy_return_type_* setstate() { return 0; }

    static bool getstate_manages_dict() { return false; }
};

}} // namespace boost::python

#endif // BOOST_PYTHON_OBJECT_PICKLE_SUPPORT_RWGK20020603_HPP
