// -*- mode:c++ -*-
//
// Header file container_suite.hpp
//
// Copyright (c) 2003 Raoul M. Gough
//
// This material is provided "as is", with absolutely no warranty expressed
// or implied. Any use is at your own risk.
//
// Permission to use or copy this material for any purpose is hereby
// granted without fee, provided the above notices are retained on all
// copies.  Permission to modify the material and to distribute modified
// versions is granted, provided the above notices are retained, and a
// notice that the material was modified is included with the above
// copyright notice.
//
// History
// =======
// 2003/ 8/23	rmg	File creation
// 2003/ 9/ 8	rmg	Extracted trait facilities into container_traits.hpp
//
// $Id$
//

#ifndef container_suite_rmg_20030823_included
#define container_suite_rmg_20030823_included

#include "container_traits.hpp"
#include "slice_handler.hpp"

#include <boost/python/return_by_value.hpp>
#include <boost/python/return_value_policy.hpp>
#include <boost/python/def_visitor.hpp>
#include <boost/python/iterator.hpp>

// #include <boost/python/return_internal_reference.hpp>

namespace indexing {
  template<IndexStyle>
  struct maybe_add_getitem {
    template<class PythonClass, class Algorithms, class Policy>
    static void apply (PythonClass &, Algorithms const &, Policy const &) { }
  };

  template<>
  struct maybe_add_getitem<index_style_nonlinear> {
    template<class PythonClass, class Algorithms, class Policy>
    static void apply (PythonClass &pyClass
		       , Algorithms const &
		       , Policy const &policy)
    {
      pyClass.def ("__getitem__", &Algorithms::get, policy);
    }
  };

  template<>
  struct maybe_add_getitem<index_style_linear> {
    template<class PythonClass, class Algorithms, class Policy>
    static void apply (PythonClass &pyClass
		       , Algorithms const &
		       , Policy const &policy)
    {
      pyClass.def ("__getitem__", &Algorithms::get, policy);
      pyClass.def ("__getitem__"
		   , slice_handler<Algorithms, Policy>::make_getitem (policy));
    }
  };

  template<IndexStyle>
  struct maybe_add_setitem {
    template<class PythonClass, class Algorithms, class Policy>
    static void apply (PythonClass &, Algorithms const &, Policy const &) { }
  };

  template<>
  struct maybe_add_setitem<index_style_nonlinear> {
    template<class PythonClass, class Algorithms, class Policy>
    static void apply (PythonClass &pyClass
		       , Algorithms const &
		       , Policy const &policy)
    {
      pyClass.def ("__setitem__", &Algorithms::assign, policy);
    }
  };

  template<>
  struct maybe_add_setitem<index_style_linear> {
    template<class PythonClass, class Algorithms, class Policy>
    static void apply (PythonClass &pyClass
		       , Algorithms const &
		       , Policy const &policy)
    {
      pyClass.def ("__setitem__", &Algorithms::assign, policy);
      // *FIXME* add slicing support
    }
  };

  template<bool doit>
  struct maybe_add_iter {
    template<class PythonClass, class Algorithms, class Policy>
    static void apply (PythonClass &, Algorithms const &, Policy const &) { }
  };

  template<>
  struct maybe_add_iter<true> {
    template<class PythonClass, class Algorithms, class Policy>
    static void apply (PythonClass &pyClass
		       , Algorithms const &
		       , Policy const &policy)
    {
      pyClass.def ("__iter__"
		   , boost::python::range<Policy> (Algorithms::begin
						   , Algorithms::end));
    }
  };

  template<bool doit>
  struct maybe_add_append {
    template<class PythonClass, class Algorithms, class Policy>
    static void apply (PythonClass &, Algorithms const &, Policy const &) { }
  };

  template<>
  struct maybe_add_append<true> {
    template<class PythonClass, class Algorithms, class Policy>
    static void apply (PythonClass &pyClass
		       , Algorithms const &
		       , Policy const &policy)
    {
      pyClass.def ("append", &Algorithms::push_back, policy);
    }
  };

  template<class Container, class Policy, class Traits>
  class container_suite_impl
    : public boost::python::def_visitor <container_suite_impl<Container, Policy, Traits> >
  {
    Policy mPolicy;

  public:
    typedef typename Traits::algorithms algorithms;
    typedef typename Traits::reference reference_return;
    typedef Policy return_policy;

    container_suite_impl (Policy const &policy) : mPolicy (policy) { }

    template <class PythonClass>
    void visit (PythonClass &pyClass) const
    {
      maybe_add_getitem<Traits::index_style>
	::apply (pyClass, algorithms(), mPolicy);

      maybe_add_setitem<Traits::index_style>
	::apply (pyClass, algorithms(), mPolicy);

      maybe_add_iter<((Traits::index_style != index_style_linear)
		      && Traits::has_copyable_iter)>
	::apply (pyClass, algorithms(), mPolicy);

      maybe_add_append<Traits::has_push_back>
	::apply (pyClass, algorithms(), mPolicy);
    }
  };

  template<class Container, class Traits = container_traits<Container> >
  struct container_suite
  {
    typedef boost::python::return_value_policy<boost::python::return_by_value>
    default_policies;

    static
    container_suite_impl <Container, default_policies, Traits>
    generate ()
    {
      return container_suite_impl <Container, default_policies, Traits> (default_policies());
    }

    template<typename Policy>
    static
    container_suite_impl <Container, Policy, Traits>
    generate (Policy const &policy)
    {
      return container_suite_impl <Container, Policy, Traits> (policy);
    }
  };
}

#endif // container_suite_rmg_20030823_included
