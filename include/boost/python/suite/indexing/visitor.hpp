// -*- mode:c++ -*-
//
// Header file visitor.hpp
//
// Copyright (c) 2003 Raoul M. Gough
//
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy
// at http://www.boost.org/LICENSE_1_0.txt)
//
// History
// =======
// 2003/ 9/11   rmg     File creation from container_suite.hpp
//
// $Id$
//

#ifndef BOOST_PYTHON_INDEXING_VISITOR_HPP
#define BOOST_PYTHON_INDEXING_VISITOR_HPP

#include <boost/python/suite/indexing/slice_handler.hpp>

#include <boost/python/def_visitor.hpp>
#include <boost/python/iterator.hpp>
#include <boost/bind.hpp>
#include <functional>

namespace boost { namespace python { namespace indexing {
  namespace detail {
    template<typename PrecallPolicy>
    struct precall_only : public boost::python::default_call_policies
    {
      // This policies struct uses default policies for everything
      // except precall, which must be provided by the template
      // argument.

      precall_only () : m_precall () { }
      explicit precall_only (PrecallPolicy const &copy) : m_precall (copy) { }

      bool precall (PyObject *args) { return m_precall.precall (args); }
      bool precall (PyObject *args) const { return m_precall.precall (args); }

    private:
      PrecallPolicy m_precall;
    };
  }

  //////////////////////////////////////////////////////////////////////////
  // __len__ dummy
  //////////////////////////////////////////////////////////////////////////

  template<bool doit>
  struct maybe_add_len {
    template<class PythonClass, class Algorithms, class Policy>
    static void apply (PythonClass &, Algorithms const &, Policy const &) { }
  };

  //////////////////////////////////////////////////////////////////////////
  // __len__ real
  //////////////////////////////////////////////////////////////////////////

  template<>
  struct maybe_add_len<true> {
    template<class PythonClass, class Algorithms, class Policy>
    static void apply (
        PythonClass &pyClass
        , Algorithms const &
        , Policy const &policy)
    {
      pyClass.def ("__len__", &Algorithms::size, policy);
    }
  };

  //////////////////////////////////////////////////////////////////////////
  // __getitem__ dummy
  //////////////////////////////////////////////////////////////////////////

  template<IndexStyle>
  struct maybe_add_getitem {
    template<class PythonClass, class Algorithms, class Policy>
    static void apply (PythonClass &, Algorithms const &, Policy const &) { }
  };

  //////////////////////////////////////////////////////////////////////////
  // __getitem__ no-slice
  //////////////////////////////////////////////////////////////////////////

  template<>
  struct maybe_add_getitem<index_style_nonlinear> {
    template<class PythonClass, class Algorithms, class Policy>
    static void apply (
        PythonClass &pyClass
        , Algorithms const &
        , Policy const &policy)
    {
      pyClass.def ("__getitem__", &Algorithms::get, policy);
    }
  };

  //////////////////////////////////////////////////////////////////////////
  // __getitem__ with slice
  //////////////////////////////////////////////////////////////////////////

  template<>
  struct maybe_add_getitem<index_style_linear> {
    template<class PythonClass, class Algorithms, class Policy>
    static void apply (
        PythonClass &pyClass
        , Algorithms const &
        , Policy const &policy)
    {
      pyClass.def ("__getitem__", &Algorithms::get, policy);
      pyClass.def (
          "__getitem__"
          , slice_handler<Algorithms, Policy>::make_getitem (policy));
    }
  };

  //////////////////////////////////////////////////////////////////////////
  // __setitem__ dummy
  //////////////////////////////////////////////////////////////////////////

  template<bool doit, IndexStyle style>
  struct maybe_add_setitem {
    template<class PythonClass, class Algorithms, class Policy>
    static void apply (PythonClass &, Algorithms const &, Policy const &) { }
  };

  //////////////////////////////////////////////////////////////////////////
  // __setitem__ no-slice
  //////////////////////////////////////////////////////////////////////////

  template<>
  struct maybe_add_setitem<true, index_style_nonlinear> {
    template<class PythonClass, class Algorithms, class Policy>
    static void apply (
        PythonClass &pyClass
        , Algorithms const &
        , Policy const &policy)
    {
      pyClass.def ("__setitem__", &Algorithms::assign, policy);
    }
  };

  //////////////////////////////////////////////////////////////////////////
  // __setitem__ with slice
  //////////////////////////////////////////////////////////////////////////

  template<>
  struct maybe_add_setitem<true, index_style_linear> {
    template<class PythonClass, class Algorithms, class Policy>
    static void apply (
        PythonClass &pyClass
        , Algorithms const &
        , Policy const &policy)
    {
      pyClass.def ("__setitem__", &Algorithms::assign, policy);
      pyClass.def (
          "__setitem__"
          , slice_handler<Algorithms, Policy>::make_setitem (policy));
    }
  };

  //////////////////////////////////////////////////////////////////////////
  // __delitem__ dummy
  //////////////////////////////////////////////////////////////////////////

  template<bool doit, IndexStyle style>
  struct maybe_add_delitem {
    template<class PythonClass, class Algorithms, class Policy>
    static void apply (PythonClass &, Algorithms const &, Policy const &) { }
  };

  //////////////////////////////////////////////////////////////////////////
  // __delitem__ no-slice
  //////////////////////////////////////////////////////////////////////////

  template<>
  struct maybe_add_delitem<true, index_style_nonlinear> {
    template<class PythonClass, class Algorithms, class Policy>
    static void apply (
        PythonClass &pyClass
        , Algorithms const &
        , Policy const &policy)
    {
      pyClass.def ("__delitem__", &Algorithms::erase_one, policy);
    }
  };

  //////////////////////////////////////////////////////////////////////////
  // __delitem__ with slice
  //////////////////////////////////////////////////////////////////////////

  template<>
  struct maybe_add_delitem<true, index_style_linear> {
    template<class PythonClass, class Algorithms, class Policy>
    static void apply (
        PythonClass &pyClass
        , Algorithms const &
        , Policy const &policy)
    {
      pyClass.def ("__delitem__", &Algorithms::erase_one, policy);
      pyClass.def (
          "__delitem__"
          , slice_handler<Algorithms, Policy>::make_delitem (policy));
    }
  };

  //////////////////////////////////////////////////////////////////////////
  // __iter__ dummy
  //////////////////////////////////////////////////////////////////////////

  template<bool doit>
  struct maybe_add_iter {
    template<class PythonClass, class Algorithms, class Policy>
    static void apply (PythonClass &, Algorithms const &, Policy const &) { }
  };

  //////////////////////////////////////////////////////////////////////////
  // __iter__ real
  //////////////////////////////////////////////////////////////////////////

  template<>
  struct maybe_add_iter<true> {
    template<class PythonClass, class Algorithms, class Policy>
    static void apply (
        PythonClass &pyClass
        , Algorithms const &
        , Policy const &policy)
    {
      // *FIXME* seperate precall and postcall portions of the
      // policy (precall when generating the range object, postcall
      // when returing from range.next())
      pyClass.def (
          "__iter__"
          , boost::python::range<Policy> (
              Algorithms::begin
              , Algorithms::end));
    }
  };

  //////////////////////////////////////////////////////////////////////////
  // sort dummy
  //////////////////////////////////////////////////////////////////////////

  template<bool doit, bool lessthan_comparable>
  struct maybe_add_sort {
    template<class PythonClass, class Algorithms, class Policy>
    static void apply (PythonClass &, Algorithms const &, Policy const &) { }
  };

  //////////////////////////////////////////////////////////////////////////
  // sort real
  //////////////////////////////////////////////////////////////////////////

  template<>
  struct maybe_add_sort<true, true> {
    template<class PythonClass, class Algorithms, class Policy>
    static void apply (
        PythonClass &pyClass
        , Algorithms const &
        , Policy const &policy)
    {
      pyClass.def ("sort", &Algorithms::sort, policy);
    }
  };

  //////////////////////////////////////////////////////////////////////////
  // reverse dummy
  //////////////////////////////////////////////////////////////////////////

  template<bool doit>
  struct maybe_add_reverse {
    template<class PythonClass, class Algorithms, class Policy>
    static void apply (PythonClass &, Algorithms const &, Policy const &) { }
  };

  //////////////////////////////////////////////////////////////////////////
  // reverse real
  //////////////////////////////////////////////////////////////////////////

  template<>
  struct maybe_add_reverse<true> {
    template<class PythonClass, class Algorithms, class Policy>
    static void apply (
        PythonClass &pyClass
        , Algorithms const &
        , Policy const &policy)
    {
      pyClass.def ("reverse", &Algorithms::reverse, policy);
    }
  };

  //////////////////////////////////////////////////////////////////////////
  // append dummy
  //////////////////////////////////////////////////////////////////////////

  template<bool doit>
  struct maybe_add_append {
    template<class PythonClass, class Algorithms, class Policy>
    static void apply (PythonClass &, Algorithms const &, Policy const &) { }
  };

  //////////////////////////////////////////////////////////////////////////
  // append real
  //////////////////////////////////////////////////////////////////////////

  template<>
  struct maybe_add_append<true> {
    template<class PythonClass, class Algorithms, class Policy>
    static void apply (
        PythonClass &pyClass
        , Algorithms const &
        , Policy const &policy)
    {
      pyClass.def ("append", &Algorithms::push_back, policy);
    }
  };

  //////////////////////////////////////////////////////////////////////////
  // extend dummy
  //////////////////////////////////////////////////////////////////////////

  template<bool doit>
  struct maybe_add_insert {
    template<class PythonClass, class Algorithms, class Policy>
    static void apply (PythonClass &, Algorithms const &, Policy const &) { }
  };

  //////////////////////////////////////////////////////////////////////////
  // insert real
  //////////////////////////////////////////////////////////////////////////

  template<>
  struct maybe_add_insert<true> {
    template<class PythonClass, class Algorithms, class Policy>
    static void apply (
        PythonClass &pyClass
        , Algorithms const &
        , Policy const &policy)
    {
      pyClass.def ("insert", Algorithms::insert, policy);
    }
  };

  //////////////////////////////////////////////////////////////////////////
  // extend dummy
  //////////////////////////////////////////////////////////////////////////

  template<bool doit>
  struct maybe_add_extend {
    template<class PythonClass, class Algorithms, class Policy>
    static void apply (PythonClass &, Algorithms const &, Policy const &) { }
  };

  //////////////////////////////////////////////////////////////////////////
  // extend real
  //////////////////////////////////////////////////////////////////////////

  template<>
  struct maybe_add_extend<true> {
    template<class PythonClass, class Algorithms, class Policy>
    static void apply (
        PythonClass &pyClass
        , Algorithms const &
        , Policy const &policy)
    {
      pyClass.def (
          "extend"
          , slice_handler<Algorithms, Policy>::make_extend (policy));
    }
  };

  //////////////////////////////////////////////////////////////////////////
  // index dummy
  //////////////////////////////////////////////////////////////////////////

  template<bool doit>
  struct maybe_add_index {
    template<class PythonClass, class Algorithms, class Policy>
    static void apply (PythonClass &, Algorithms const &, Policy const &) { }
  };

  //////////////////////////////////////////////////////////////////////////
  // index real
  //////////////////////////////////////////////////////////////////////////

  template<>
  struct maybe_add_index<true> {
    template<class PythonClass, class Algorithms, class Policy>
    static void apply (
        PythonClass &pyClass
        , Algorithms const &
        , Policy const &policy)
    {
      pyClass.def ("index", Algorithms::get_index, policy);
    }
  };

  //////////////////////////////////////////////////////////////////////////
  // count dummy
  //////////////////////////////////////////////////////////////////////////

  template<bool doit, IndexStyle>
  struct maybe_add_count {
    template<class PythonClass, class Algorithms, class Policy>
    static void apply (PythonClass &, Algorithms const &, Policy const &) { }
  };

  //////////////////////////////////////////////////////////////////////////
  // count real (sequences without indexing)
  //////////////////////////////////////////////////////////////////////////

  template<>
  struct maybe_add_count<true, index_style_none> {
    template<class PythonClass, class Algorithms, class Policy>
    static void apply (
        PythonClass &pyClass
        , Algorithms const &
        , Policy const &policy)
    {
      pyClass.def ("count", Algorithms::count, policy);
      pyClass.def ("contains", Algorithms::contains, policy);
    }
  };


  //////////////////////////////////////////////////////////////////////////
  // count real (sequences with indexing)
  //////////////////////////////////////////////////////////////////////////

  template<>
  struct maybe_add_count<true, index_style_linear> {
    template<class PythonClass, class Algorithms, class Policy>
    static void apply (
        PythonClass &pyClass
        , Algorithms const &
        , Policy const &policy)
    {
      // This is identical to the index_style_none version. Doing it
      // this way avoids using a partial specialization for
      // <true, *>
      pyClass.def ("count", Algorithms::count, policy);
      pyClass.def ("__contains__", Algorithms::contains, policy);
    }
  };

  //////////////////////////////////////////////////////////////////////////
  // count real (associative containers). add has_key
  //////////////////////////////////////////////////////////////////////////

  template<>
  struct maybe_add_count<true, index_style_nonlinear> {
    template<class PythonClass, class Algorithms, class Policy>
    static void apply (
        PythonClass &pyClass
        , Algorithms const &
        , Policy const &policy)
    {
      // Nearest equivalent is has_key, since Python dictionaries
      // have at most one value for a key.
      pyClass.def ("has_key", Algorithms::contains, policy);
      pyClass.def ("__contains__", Algorithms::contains, policy);

      // Maybe this makes sense for multimap or multiset. Then again,
      // maybe they should always return a list of elements for a key?
      pyClass.def ("count", Algorithms::count, policy);
    }
  };

  //////////////////////////////////////////////////////////////////////////
  // Do-all visitor
  //////////////////////////////////////////////////////////////////////////

  template<class Algorithms, class Policy>
  class visitor
    : public boost::python::def_visitor< visitor< Algorithms, Policy > >
  {
    Policy m_policy;

  public:
    typedef Algorithms algorithms;
    typedef typename algorithms::container_traits traits;
    typedef typename traits::value_traits_ value_traits_;

    explicit visitor (Policy const &policy = Policy()) : m_policy (policy) { }

    template <class PythonClass>
    void visit (PythonClass &pyClass) const
    {
      detail::precall_only<Policy> precallPolicy (m_policy);

      // Note - this will add __len__ for anything that can determine
      // its size, even if that might be inefficient (e.g. have linear
      // time complexity). It might be better to add a new feature
      // selection flag to the container_traits to make this
      // configurable.
      maybe_add_len<traits::has_copyable_iter>
        ::apply (pyClass, algorithms(), precallPolicy);

      maybe_add_getitem<traits::index_style>
        ::apply (pyClass, algorithms(), m_policy);

      maybe_add_setitem<traits::has_mutable_ref, traits::index_style>
        ::apply (pyClass, algorithms(), m_policy);

      maybe_add_delitem<traits::has_erase, traits::index_style>
        ::apply (pyClass, algorithms(), m_policy);

      maybe_add_iter
        <(traits::index_style != index_style_linear)
          && traits::has_copyable_iter>
        ::apply (pyClass, algorithms(), m_policy);

      maybe_add_sort
        <traits::is_reorderable, value_traits_::lessthan_comparable>
        ::apply (pyClass, algorithms(), precallPolicy);

      maybe_add_reverse<traits::is_reorderable>
        ::apply (pyClass, algorithms(), precallPolicy);

      maybe_add_append<traits::has_push_back>
        ::apply (pyClass, algorithms(), precallPolicy);

      maybe_add_insert<traits::has_insert>
        ::apply (pyClass, algorithms(), precallPolicy);

      maybe_add_extend
        <traits::has_insert && traits::index_style == index_style_linear>
        ::apply (pyClass, algorithms(), precallPolicy);

      maybe_add_index
        <traits::has_find && (traits::index_style == index_style_linear)>
        ::apply (pyClass, algorithms(), precallPolicy);

      maybe_add_count<traits::has_find, traits::index_style>
        ::apply (pyClass, algorithms(), precallPolicy);

      Algorithms::visitor_helper (pyClass, m_policy);
    }
  };
} } }

#endif // BOOST_PYTHON_INDEXING_VISITOR_HPP
