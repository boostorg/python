// Header file map.hpp
//
// Copyright (c) 2003 Raoul M. Gough
//
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy
// at http://www.boost.org/LICENSE_1_0.txt)
//
// Indexing algorithms support for std::map instances
//
// History
// =======
// 2003/10/28   rmg     File creation from algo_selector.hpp
//
// $Id$
//

#ifndef BOOST_PYTHON_INDEXING_MAP_HPP
#define BOOST_PYTHON_INDEXING_MAP_HPP

#include <boost/python/suite/indexing/container_traits.hpp>
#include <boost/python/suite/indexing/container_suite.hpp>
#include <boost/python/suite/indexing/algorithms.hpp>
#include <boost/python/suite/indexing/algo_selector.hpp>
#include <boost/python/suite/indexing/algo_selector.hpp>
#include <boost/detail/workaround.hpp>
#include <map>

namespace boost { namespace python { namespace indexing {
  /////////////////////////////////////////////////////////////////////////
  // ContainerTraits implementation for std::map instances
  /////////////////////////////////////////////////////////////////////////

  template<typename Container>
  struct map_traits : public default_container_traits<Container>
  {
# if BOOST_WORKAROUND (BOOST_MSVC, <= 1200)
    // MSVC6 has a nonstandard name for mapped_type in std::map
    typedef typename Container::referent_type value_type;
# else
    typedef typename Container::mapped_type value_type;
# endif
    typedef value_type &                    reference;
    typedef typename Container::key_type    index_type; // operator[]
    typedef typename Container::key_type    key_type;   // find, count, ...

    typedef typename BOOST_PYTHON_INDEXING_CALL_TRAITS <value_type>::param_type
      value_param;
    typedef typename BOOST_PYTHON_INDEXING_CALL_TRAITS <key_type>::param_type
      key_param;
    typedef typename BOOST_PYTHON_INDEXING_CALL_TRAITS <index_type>::param_type
      index_param;

    BOOST_STATIC_CONSTANT (index_style_t, index_style = index_style_nonlinear);
    BOOST_STATIC_CONSTANT (bool,   has_find       = true);
    BOOST_STATIC_CONSTANT (bool,   is_reorderable = false);
    // std::map::reference (reference to the mapped type) is mutable,
    // so explicitly override the base-class assumption of
    // is_reorderable
  };

  /////////////////////////////////////////////////////////////////////////
  // Algorithms implementation for std::map instances
  /////////////////////////////////////////////////////////////////////////

  template<typename ContainerTraits, typename Ovr = detail::no_override>
  class map_algorithms
    : public assoc_algorithms
        <ContainerTraits
        , typename detail::maybe_override
            <map_algorithms<ContainerTraits, Ovr>, Ovr>
          ::type>
  {
    typedef map_algorithms<ContainerTraits, Ovr> self_type;
    typedef typename detail::maybe_override<self_type, Ovr>::type most_derived;
    typedef assoc_algorithms<ContainerTraits, most_derived> Parent;

  public:
    typedef typename Parent::container container;
    typedef typename Parent::reference reference;
    typedef typename Parent::index_param index_param;
    typedef typename Parent::value_param value_param;

    static reference get (container &, index_param);
    // Version to return only the mapped type

    static void      assign     (container &, index_param, value_param);
    static void      insert     (container &, index_param, value_param);
  };

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
  namespace detail {
    ///////////////////////////////////////////////////////////////////////
    // algo_selector support for std::map instances
    ///////////////////////////////////////////////////////////////////////

    template <class Key, class T, class Compare, class Allocator>
    class selector_impl<std::map<Key, T, Compare, Allocator> >
    {
      typedef std::map<Key, T, Compare, Allocator> Container;

      typedef map_traits<Container>       mutable_traits;
      typedef map_traits<Container const> const_traits;

    public:
      typedef map_algorithms<mutable_traits> mutable_algorithms;
      typedef map_algorithms<const_traits>   const_algorithms;
    };

    ///////////////////////////////////////////////////////////////////////
    // algo_selector support for std::multimap instances
    ///////////////////////////////////////////////////////////////////////

    template <class Key, class T, class Compare, class Allocator>
    class selector_impl<std::multimap<Key, T, Compare, Allocator> >
    {
      typedef std::multimap<Key, T, Compare, Allocator> Container;

      typedef map_traits<Container>       mutable_traits;
      typedef map_traits<Container const> const_traits;

    public:
      typedef map_algorithms<mutable_traits> mutable_algorithms;
      typedef map_algorithms<const_traits>   const_algorithms;
    };
  }
#endif

  template <
    class Container
    , int Flags = 0
    , class Traits = map_traits<Container>
  >
  struct map_suite
    : container_suite<Container, Flags, map_algorithms<Traits> >
  {
  };

  /////////////////////////////////////////////////////////////////////////
  // Index into a container (map version)
  /////////////////////////////////////////////////////////////////////////

  template<typename ContainerTraits, typename Ovr>
  BOOST_DEDUCED_TYPENAME map_algorithms<ContainerTraits, Ovr>::reference
  map_algorithms<ContainerTraits, Ovr>::get (container &c, index_param ix)
  {
    return most_derived::find_or_throw (c, ix)->second;
  }

  /////////////////////////////////////////////////////////////////////////
  // Assign a value at a particular index (map version)
  /////////////////////////////////////////////////////////////////////////

  template<typename ContainerTraits, typename Ovr>
  void
  map_algorithms<ContainerTraits, Ovr>::assign (
      container &c, index_param ix, value_param val)
  {
    c[ix] = val;   // Handles overwrite and insert
  }


  /////////////////////////////////////////////////////////////////////////
  // Insert a new key, value pair into a map
  /////////////////////////////////////////////////////////////////////////

  template<typename ContainerTraits, typename Ovr>
  void
  map_algorithms<ContainerTraits, Ovr>::insert (
      container &c, index_param ix, value_param val)
  {
    typedef std::pair
      <BOOST_DEDUCED_TYPENAME self_type::container_traits::index_type
      , BOOST_DEDUCED_TYPENAME self_type::container_traits::value_type>
      pair_type;

    // Can't use std::make_pair, because param types may be references

    if (!c.insert (pair_type (ix, val)).second)
      {
        PyErr_SetString (
            PyExc_ValueError, "Map already holds value for insertion");

        boost::python::throw_error_already_set ();
      }
  }
} } }

#endif // BOOST_PYTHON_INDEXING_MAP_HPP
