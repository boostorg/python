// -*- mode:c++ -*-
//
// Header file visitor.hpp
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
// 2003/ 9/11	rmg	File creation from container_suite.hpp
//
// $Id$
//

#ifndef visitor_rmg_20030823_included
#define visitor_rmg_20030823_included

#include "slice_handler.hpp"

#include <boost/python/def_visitor.hpp>
#include <boost/python/iterator.hpp>

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
      pyClass.def ("__setitem__"
		   , slice_handler<Algorithms, Policy>::make_setitem (policy));
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

  template<class Algorithms, class Policy>
  class visitor
    : public boost::python::def_visitor< visitor< Algorithms, Policy > >
  {
    Policy mPolicy;

  public:
    typedef Algorithms algorithms;
    typedef typename algorithms::container_traits traits;

    visitor (Policy const &policy) : mPolicy (policy) { }

    template <class PythonClass>
    void visit (PythonClass &pyClass) const
    {
      maybe_add_getitem<traits::index_style>
	::apply (pyClass, algorithms(), mPolicy);

      maybe_add_setitem<traits::index_style>
	::apply (pyClass, algorithms(), mPolicy);

      maybe_add_iter<((traits::index_style != index_style_linear)
		      && traits::has_copyable_iter)>
	::apply (pyClass, algorithms(), mPolicy);

      maybe_add_append<traits::has_push_back>
	::apply (pyClass, algorithms(), mPolicy);
    }
  };
}

#endif // visitor_rmg_20030823_included
