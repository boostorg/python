// Header file container_traits.hpp
//
// Traits information about entire containers for use in determining
// what Python methods to support for a container.
//
// Copyright (c) 2003 Raoul M. Gough
//
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy
// at http://www.boost.org/LICENSE_1_0.txt)
//
// History
// =======
// 2003/ 8/23   rmg     File creation as container_suite.hpp
// 2003/ 9/ 8   rmg     Renamed container_traits.hpp
// 2003/10/28   rmg     Split container-specific versions into separate headers
//
// $Id$
//

#ifndef BOOST_PYTHON_INDEXING_CONTAINER_TRAITS_HPP
#define BOOST_PYTHON_INDEXING_CONTAINER_TRAITS_HPP

#include <boost/python/suite/indexing/suite_utils.hpp>
#include <boost/python/suite/indexing/iterator_traits.hpp>
#include <boost/python/suite/indexing/value_traits.hpp>

#include <boost/type_traits.hpp>
#include <boost/call_traits.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/ice.hpp>

#define ICE_AND(a, b) type_traits::ice_and<(a), (b)>::value
// #undef'd later in this header

namespace boost { namespace python { namespace indexing {
#if BOOST_WORKAROUND (BOOST_MSVC, <= 1200)
  // MSVC6 has problems with get_signature if parameter types have
  // top-level const qualification (e.g. int const). Unfortunately,
  // this is exactly what happens with boost::call_traits, so we
  // substitute a really dumb version of it instead.

  template<typename T> struct broken_call_traits {
    typedef T const & param_type;
  };
# define BOOST_PYTHON_INDEXING_CALL_TRAITS broken_call_traits
#else
# define BOOST_PYTHON_INDEXING_CALL_TRAITS ::boost::call_traits
#endif

  /////////////////////////////////////////////////////////////////////////
  // Lowest common denominator traits - applicable to real containers
  // and iterator pairs
  /////////////////////////////////////////////////////////////////////////

  template<typename Container, typename ValueTraits = detail::no_override>
  struct base_container_traits
    : public ::boost::python::indexing::iterator_traits<
        BOOST_DEDUCED_TYPENAME mpl::if_<
          is_const<Container>,
          BOOST_DEDUCED_TYPENAME Container::const_iterator,
          BOOST_DEDUCED_TYPENAME Container::iterator
        >::type
      >
  {
  protected:
    typedef ::boost::python::indexing::iterator_traits<
      BOOST_DEDUCED_TYPENAME mpl::if_<
        is_const<Container>,
        BOOST_DEDUCED_TYPENAME Container::const_iterator,
        BOOST_DEDUCED_TYPENAME Container::iterator
      >::type
    > base_type;

    BOOST_STATIC_CONSTANT(
        bool, is_mutable = ! boost::is_const<Container>::value);

  public:
    typedef Container container;

    typedef typename container::size_type  size_type;
    typedef typename base_type::value_type value_type; // insert
    typedef typename base_type::value_type key_type;   // find

    typedef typename make_signed<size_type>::type index_type;
    // at(), operator[]. Signed to support Python -ve indexes

    typedef typename BOOST_PYTHON_INDEXING_CALL_TRAITS <value_type>::param_type
        value_param;
    typedef typename BOOST_PYTHON_INDEXING_CALL_TRAITS <key_type>::param_type
        key_param;
    typedef typename BOOST_PYTHON_INDEXING_CALL_TRAITS <index_type>::param_type
        index_param;

    // Allow client code to replace the default value traits via our
    // second (optional) template parameter
    typedef value_traits<typename base_type::value_type> default_value_traits;

    typedef typename detail::maybe_override<
        default_value_traits, ValueTraits>::type value_traits_;

    BOOST_STATIC_CONSTANT(
        bool, has_mutable_ref
        = ICE_AND (base_type::has_mutable_ref, is_mutable));

    BOOST_STATIC_CONSTANT(
        bool, has_find = value_traits_::equality_comparable);

    // Assume the worst for everything else
    BOOST_STATIC_CONSTANT (bool, has_insert    = false);
    BOOST_STATIC_CONSTANT (bool, has_erase     = false);
    BOOST_STATIC_CONSTANT (bool, has_pop_back  = false);
    BOOST_STATIC_CONSTANT (bool, has_push_back = false);

    // Forward visitor_helper to value_traits_
    template<typename PythonClass, typename Policy>
    static void visitor_helper (PythonClass &pyClass, Policy const &policy)
    {
      value_traits_::visitor_helper (pyClass, policy);
    }
  };

  /////////////////////////////////////////////////////////////////////////
  // Default container traits - almost all "real" containers would meet
  // at least these requirements
  /////////////////////////////////////////////////////////////////////////

  template<typename Container, typename ValueTraits = detail::no_override>
  struct default_container_traits
    : public base_container_traits<Container, ValueTraits>
  {
    typedef default_container_traits<Container, ValueTraits> self_type;
    BOOST_STATIC_CONSTANT (bool, has_insert = self_type::is_mutable);
    BOOST_STATIC_CONSTANT (bool, has_erase  = self_type::is_mutable);
  };

  /////////////////////////////////////////////////////////////////////////
  // Sequences (list, deque, vector)
  /////////////////////////////////////////////////////////////////////////

  template<typename Container, typename ValueTraits = detail::no_override>
  struct default_sequence_traits
    : public default_container_traits<Container, ValueTraits>
  {
    typedef default_sequence_traits<Container, ValueTraits> self_type;
    BOOST_STATIC_CONSTANT (bool, has_pop_back  = self_type::is_mutable);
    BOOST_STATIC_CONSTANT (bool, has_push_back = self_type::is_mutable);
  };

} } }

#undef ICE_AND

#endif // BOOST_PYTHON_INDEXING_CONTAINER_SUITE_HPP
