// Header file set.hpp
//
// Copyright (c) 2003 Raoul M. Gough
//
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy
// at http://www.boost.org/LICENSE_1_0.txt)
//
// Indexing algorithms support for std::set instances
//
// History
// =======
// 2003/10/28   rmg     File creation from algo_selector.hpp
//
// $Id$
//

#ifndef BOOST_PYTHON_INDEXING_SET_HPP
#define BOOST_PYTHON_INDEXING_SET_HPP

#include <boost/python/suite/indexing/container_traits.hpp>
#include <boost/python/suite/indexing/container_suite.hpp>
#include <boost/python/suite/indexing/algorithms.hpp>
#include <boost/python/suite/indexing/algo_selector.hpp>
#include <set>

namespace boost { namespace python { namespace indexing {
  /////////////////////////////////////////////////////////////////////////
  // ContainerTraits implementation for std::set instances
  /////////////////////////////////////////////////////////////////////////

  template<typename Container>
  struct set_traits : public default_container_traits<Container>
  {
    typedef typename Container::key_type value_type; // probably unused
    typedef typename Container::key_type index_type; // operator[]
    typedef typename Container::key_type key_type;   // find, count, ...

    typedef typename BOOST_PYTHON_INDEXING_CALL_TRAITS <value_type>::param_type
        value_param;
    typedef typename BOOST_PYTHON_INDEXING_CALL_TRAITS <key_type>::param_type
        key_param;
    typedef typename BOOST_PYTHON_INDEXING_CALL_TRAITS <index_type>::param_type
        index_param;

    BOOST_STATIC_CONSTANT (index_style_t, index_style = index_style_nonlinear);
    BOOST_STATIC_CONSTANT (bool, has_find        = true);
    BOOST_STATIC_CONSTANT (bool, has_mutable_ref = false);
    BOOST_STATIC_CONSTANT (bool, is_reorderable  = false);
    // Some compilers seem to deduce has_mutable_ref as true from the
    // set iterator traits. The previous two constants explicitly hide
    // the bad results of that.
  };

  /////////////////////////////////////////////////////////////////////////
  // Algorithms implementation for std::set instances
  /////////////////////////////////////////////////////////////////////////

  template<typename ContainerTraits, typename Ovr = detail::no_override>
  class set_algorithms
    : public assoc_algorithms
        <ContainerTraits,
        typename detail::maybe_override
            <set_algorithms<ContainerTraits, Ovr>, Ovr>
          ::type>
  {
    typedef set_algorithms<ContainerTraits, Ovr> self_type;
    typedef typename detail::maybe_override<self_type, Ovr>::type most_derived;
    typedef assoc_algorithms<ContainerTraits, most_derived> Parent;

  public:
    typedef typename Parent::container container;
    typedef typename Parent::value_param value_param;
    typedef typename Parent::index_param index_param;

    static void      insert     (container &, index_param);
  };

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
  namespace detail {
    ///////////////////////////////////////////////////////////////////////
    // algo_selector support for std::set instances
    ///////////////////////////////////////////////////////////////////////

    template <class Key, class Compare, class Allocator>
    class selector_impl<std::set<Key, Compare, Allocator> >
    {
      typedef std::set<Key, Compare, Allocator> Container;

      typedef set_traits<Container>       mutable_traits;
      typedef set_traits<Container const> const_traits;

    public:
      typedef set_algorithms<mutable_traits> mutable_algorithms;
      typedef set_algorithms<const_traits>   const_algorithms;
    };

    ///////////////////////////////////////////////////////////////////////
    // algo_selector support for std::multiset instances
    ///////////////////////////////////////////////////////////////////////

    template <class Key, class Compare, class Allocator>
    class selector_impl<std::multiset<Key, Compare, Allocator> >
    {
      typedef std::multiset<Key, Compare, Allocator> Container;

      typedef set_traits<Container>       mutable_traits;
      typedef set_traits<Container const> const_traits;

    public:
      typedef set_algorithms<mutable_traits> mutable_algorithms;
      typedef set_algorithms<const_traits>   const_algorithms;
    };
  }
#endif

  template<
    class Container,
    int Flags = 0,
    class Traits = set_traits<Container>
  >
  struct set_suite
    : container_suite<Container, Flags, set_algorithms<Traits> >
  {
  };

  /////////////////////////////////////////////////////////////////////////
  // Insert an element into a set
  /////////////////////////////////////////////////////////////////////////

  template<typename ContainerTraits, typename Ovr>
  void
  set_algorithms<ContainerTraits, Ovr>::insert(
      container &c, index_param ix)
  {
    if (!c.insert (ix).second)
      {
        PyErr_SetString(
            PyExc_ValueError, "Set already holds value for insertion");

        boost::python::throw_error_already_set ();
      }
  }
} } }

#endif // BOOST_PYTHON_INDEXING_SET_HPP
