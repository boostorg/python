// Copyright (c) 2003 Raoul M. Gough
//
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy
// at http://www.boost.org/LICENSE_1_0.txt)
//
// Header file visitor.hpp:
//
// def_visitor implementation to install the container_suite's Python
// methods in an object of a boost::python::class_<> instance.
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
#include <boost/python/suite/indexing/suite_utils.hpp> // Get index_style_t

#include <boost/python/def_visitor.hpp>
#include <boost/python/iterator.hpp>
#include <boost/python/default_call_policies.hpp>
#include <boost/type_traits/ice.hpp>
#include <boost/bind.hpp>
#include <functional>

# if defined (BOOST_MSVC)
    // Prevent MSVC int-to-bool truncation warning (C4305)
#   define QUIET_BOOL(val) static_cast<bool>(val)
# else
#   define QUIET_BOOL(val) (val)
# endif

# define ICE_AND(a, b) ::boost::type_traits::ice_and <(a), (b)>::value
# define ICE_NOT(a) ::boost::type_traits::ice_not <QUIET_BOOL(a)>::value
// these three macros undef'd at end of header

namespace boost { namespace python { namespace indexing {
  enum visitor_flags {
    disable_len = 1,
    disable_slices = 2,
    disable_search = 4,
    disable_reorder = 8,
    disable_extend = 16,
    disable_insert = 32,
    minimum_support = 0xffff   // Disable all optional features
  };

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
    static void apply(
        PythonClass &pyClass,
        Algorithms const &,
        Policy const &policy)
    {
      pyClass.def ("__len__", &Algorithms::size, policy);
    }
  };

  //////////////////////////////////////////////////////////////////////////
  // __getitem__ dummy
  //////////////////////////////////////////////////////////////////////////

  template<bool doit, bool with_slice>
  struct maybe_add_getitem {
    template<class PythonClass, class Algorithms, class Policy>
    static void apply (PythonClass &, Algorithms const &, Policy const &) { }
  };

  //////////////////////////////////////////////////////////////////////////
  // __getitem__ no-slice
  //////////////////////////////////////////////////////////////////////////

  template<>
  struct maybe_add_getitem<true, false> {
    template<class PythonClass, class Algorithms, class Policy>
    static void apply(
        PythonClass &pyClass,
        Algorithms const &,
        Policy const &policy)
    {
      pyClass.def ("__getitem__", &Algorithms::get, policy);
    }
  };

  //////////////////////////////////////////////////////////////////////////
  // __getitem__ with slice
  //////////////////////////////////////////////////////////////////////////

  template<>
  struct maybe_add_getitem<true, true> {
    template<class PythonClass, class Algorithms, class Policy>
    static void apply(
        PythonClass &pyClass,
        Algorithms const &,
        Policy const &policy)
    {
      pyClass.def ("__getitem__", &Algorithms::get, policy);
      pyClass.def(
          "__getitem__",
          slice_handler<Algorithms, Policy>::make_getitem (policy));
    }
  };

  //////////////////////////////////////////////////////////////////////////
  // __setitem__ dummy
  //////////////////////////////////////////////////////////////////////////

  template<bool doit, bool with_slice>
  struct maybe_add_setitem {
    template<class PythonClass, class Algorithms, class Policy>
    static void apply (PythonClass &, Algorithms const &, Policy const &) { }
  };

  //////////////////////////////////////////////////////////////////////////
  // __setitem__ no-slice
  //////////////////////////////////////////////////////////////////////////

  template<>
  struct maybe_add_setitem<true, false> {
    template<class PythonClass, class Algorithms, class Policy>
    static void apply(
        PythonClass &pyClass,
        Algorithms const &,
        Policy const &policy)
    {
      pyClass.def ("__setitem__", &Algorithms::assign, policy);
    }
  };

  //////////////////////////////////////////////////////////////////////////
  // __setitem__ with slice
  //////////////////////////////////////////////////////////////////////////

  template<>
  struct maybe_add_setitem<true, true> {
    template<class PythonClass, class Algorithms, class Policy>
    static void apply(
        PythonClass &pyClass,
        Algorithms const &,
        Policy const &policy)
    {
      pyClass.def ("__setitem__", &Algorithms::assign, policy);
      pyClass.def(
          "__setitem__",
          slice_handler<Algorithms, Policy>::make_setitem (policy));
    }
  };

  //////////////////////////////////////////////////////////////////////////
  // __delitem__ dummy
  //////////////////////////////////////////////////////////////////////////

  template<bool doit, bool with_slicing>
  struct maybe_add_delitem {
    template<class PythonClass, class Algorithms, class Policy>
    static void apply (PythonClass &, Algorithms const &, Policy const &) { }
  };

  //////////////////////////////////////////////////////////////////////////
  // __delitem__ no-slice
  //////////////////////////////////////////////////////////////////////////

  template<>
  struct maybe_add_delitem<true, false> {
    template<class PythonClass, class Algorithms, class Policy>
    static void apply(
        PythonClass &pyClass,
        Algorithms const &,
        Policy const &policy)
    {
      pyClass.def ("__delitem__", &Algorithms::erase_one, policy);
    }
  };

  //////////////////////////////////////////////////////////////////////////
  // __delitem__ with slice
  //////////////////////////////////////////////////////////////////////////

  template<>
  struct maybe_add_delitem<true, true> {
    template<class PythonClass, class Algorithms, class Policy>
    static void apply(
        PythonClass &pyClass,
        Algorithms const &,
        Policy const &policy)
    {
      pyClass.def ("__delitem__", &Algorithms::erase_one, policy);
      pyClass.def(
          "__delitem__",
          slice_handler<Algorithms, Policy>::make_delitem (policy));
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
    static void apply(
        PythonClass &pyClass,
        Algorithms const &,
        Policy const &)
    {
      // Should maybe separate precall and postcall portions of the
      // policy (precall when generating the range object, postcall
      // when returing from range.next())?

      pyClass.def(
          "__iter__",
          boost::python::range<Policy>(
              Algorithms::begin,
              Algorithms::end));
    }
  };

  //////////////////////////////////////////////////////////////////////////
  // sort dummy
  //////////////////////////////////////////////////////////////////////////

  template<bool doit>
  struct maybe_add_sort {
    template<class PythonClass, class Algorithms, class Policy>
    static void apply (PythonClass &, Algorithms const &, Policy const &) { }
  };

  //////////////////////////////////////////////////////////////////////////
  // sort real
  //////////////////////////////////////////////////////////////////////////

  template<>
  struct maybe_add_sort<true> {
    template<class PythonClass, class Algorithms, class Policy>
    static void apply(
        PythonClass &pyClass,
        Algorithms const &,
        Policy const &policy)
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
    static void apply(
        PythonClass &pyClass,
        Algorithms const &,
        Policy const &policy)
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
    static void apply(
        PythonClass &pyClass,
        Algorithms const &,
        Policy const &policy)
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
    static void apply(
        PythonClass &pyClass,
        Algorithms const &,
        Policy const &policy)
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
    static void apply(
        PythonClass &pyClass,
        Algorithms const &,
        Policy const &policy)
    {
      pyClass.def(
          "extend",
          slice_handler<Algorithms, Policy>::make_extend (policy));
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
    static void apply(
        PythonClass &pyClass,
        Algorithms const &,
        Policy const &policy)
    {
      pyClass.def ("index", Algorithms::get_index, policy);
    }
  };

  //////////////////////////////////////////////////////////////////////////
  // count dummy
  //////////////////////////////////////////////////////////////////////////

  template<bool doit, index_style_t style>
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
    static void apply(
        PythonClass &pyClass,
        Algorithms const &,
        Policy const &policy)
    {
      pyClass.def ("count", Algorithms::count, policy);
      pyClass.def ("__contains__", Algorithms::contains, policy);
    }
  };


  //////////////////////////////////////////////////////////////////////////
  // count real (sequences with indexing)
  //////////////////////////////////////////////////////////////////////////

  template<>
  struct maybe_add_count<true, index_style_linear> {
    template<class PythonClass, class Algorithms, class Policy>
    static void apply(
        PythonClass &pyClass,
        Algorithms const &,
        Policy const &policy)
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
    static void apply(
        PythonClass &pyClass,
        Algorithms const &,
        Policy const &policy)
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

  template<class Algorithms, class Policy, int Flags = 0>
  class visitor
    : public boost::python::def_visitor< visitor< Algorithms, Policy, Flags > >
  {
    Policy m_policy;

  public:
    typedef Algorithms algorithms_type;
    typedef typename algorithms_type::container_traits traits;
    typedef typename traits::value_traits_type value_traits_type;

    explicit visitor (Policy const &policy = Policy()) : m_policy (policy) { }

  private:
    BOOST_STATIC_CONSTANT(
        bool, has_indexing = traits::index_style >= index_style_nonlinear);

    BOOST_STATIC_CONSTANT(
        bool, has_slicing = ICE_AND(
            traits::index_style == index_style_linear,
            ICE_NOT (Flags & disable_slices)));

  public:
    template <class PythonClass>
    void visit (PythonClass &pyClass) const
    {
      detail::precall_only<Policy> precallPolicy (m_policy);

      // Note - this will add __len__ for anything that can determine
      // its size, even if that might be inefficient (e.g. have linear
      // time complexity). Disable by setting disable_len in Flags
      maybe_add_len<
        ICE_AND(
            traits::has_copyable_iter,
            ICE_NOT (Flags & disable_len))
      >::apply (pyClass, algorithms_type(), precallPolicy);

      maybe_add_getitem <has_indexing, has_slicing>
        ::apply (pyClass, algorithms_type(), m_policy);

      maybe_add_setitem<
          ICE_AND (traits::has_mutable_ref, has_indexing),
          has_slicing
      >::apply (pyClass, algorithms_type(), m_policy);

      maybe_add_delitem<ICE_AND (traits::has_erase, has_indexing), has_slicing>
        ::apply (pyClass, algorithms_type(), m_policy);

      maybe_add_iter<
        ICE_AND(
            traits::index_style != index_style_linear,
            traits::has_copyable_iter)
      >::apply (pyClass, algorithms_type(), m_policy);

      maybe_add_sort<
        ICE_AND(
            ICE_AND(
                traits::is_reorderable,
                value_traits_type::less_than_comparable),
            ICE_NOT (Flags & disable_reorder))
      >::apply (pyClass, algorithms_type(), precallPolicy);

      maybe_add_reverse<
        ICE_AND (traits::is_reorderable, ICE_NOT (Flags & disable_reorder))
      >::apply (pyClass, algorithms_type(), precallPolicy);

      maybe_add_append<traits::has_push_back>
        ::apply (pyClass, algorithms_type(), precallPolicy);

      maybe_add_insert<
        ICE_AND (traits::has_insert, ICE_NOT (Flags & disable_insert))
      >::apply (pyClass, algorithms_type(), precallPolicy);

      maybe_add_extend<
        ICE_AND(
            ICE_AND(
                traits::index_style == index_style_linear,
                traits::has_insert),
            ICE_NOT (Flags & disable_extend))
      >::apply (pyClass, algorithms_type(), precallPolicy);

      maybe_add_index<
        ICE_AND(
            ICE_AND(
                traits::index_style == index_style_linear,
                traits::has_find),
            ICE_NOT (Flags & disable_search))
      >::apply (pyClass, algorithms_type(), precallPolicy);

      maybe_add_count<
        ICE_AND(
            traits::has_find,
            ICE_NOT (Flags & disable_search)),
        traits::index_style
      >::apply (pyClass, algorithms_type(), precallPolicy);

      Algorithms::visit_container_class (pyClass, m_policy);
    }
  };
} } }

#undef ICE_NOT
#undef ICE_AND
#undef QUIET_BOOL

#endif // BOOST_PYTHON_INDEXING_VISITOR_HPP
