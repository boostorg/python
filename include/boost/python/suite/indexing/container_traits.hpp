// -*- mode:c++ -*-
//
// Header file container_traits.hpp
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
// 2003/ 8/23	rmg	File creation as container_suite.hpp
// 2003/ 9/ 8	rmg	Renamed container_traits.hpp
//
// $Id$
//

#ifndef container_traits_rmg_20030823_included
#define container_traits_rmg_20030823_included

#include "suite_utils.hpp"
#include "iterator_suite.hpp"
#include <boost/type_traits.hpp>

namespace indexing {
  /////////////////////////////////////////////////////////////////////////
  // Traits for the iterator_pair container emulator
  /////////////////////////////////////////////////////////////////////////

  template<typename IteratorPair>
  struct iterator_pair_traits
    : public
    iterator_detail::traits_by_category<typename IteratorPair::iterator>::type
  {
    typedef IteratorPair container;
    typedef typename IteratorPair::size_type        size_type;
    typedef typename IteratorPair::size_type        index_type; // at()

    static bool const has_insert         = false;
    static bool const has_erase          = false;
    static bool const has_pop_back       = false;
    static bool const has_push_back      = false;
  };

  /////////////////////////////////////////////////////////////////////////
  // Lowest common denominator (almost all "real" containers would
  // meet at least these requirements)
  /////////////////////////////////////////////////////////////////////////

  template<typename Container>
  struct default_container_traits
  {
  protected:
    static bool const is_mutable = ! boost::is_const<Container>::value;

  public:
    typedef Container container;

    // *FIXME* should use value_type const and const_reference if !is_mutable
    typedef typename Container::value_type       value_type;
    typedef typename Container::reference        reference;

    typedef typename Container::difference_type  difference_type;
    typedef typename Container::size_type        size_type;
    typedef typename Container::size_type        index_type; // at()
    typedef value_type                           key_type; // find, count, ...

    // Should probably select iterator or const_iterator on the
    // basis of is_mutable
    typedef typename Container::iterator         iterator;
    typedef typename Container::const_iterator   const_iterator;

    static bool const has_copyable_iter  = true;

    static IndexStyle const index_style
      = ::indexing::iterator_traits<iterator>::index_style;

    static bool const has_mutable_ref
      = is_mutable && is_mutable_ref<reference>::value;

    // has_mutable_ref basically means that the container supports
    // in-place replacement of values (e.g. the associative containers
    // *don't*)

    static bool const is_reversible      = has_mutable_ref;

    static bool const has_insert         = is_mutable;
    static bool const has_erase          = is_mutable;
    static bool const has_pop_back       = false;
    static bool const has_push_back      = false;
  };

  /////////////////////////////////////////////////////////////////////////
  // Sequences (list, deque, vector)
  /////////////////////////////////////////////////////////////////////////

  template<typename Container>
  struct default_sequence_traits : public default_container_traits<Container>
  {
    static bool const has_pop_back       = is_mutable;
    static bool const has_push_back      = is_mutable;
  };

  /////////////////////////////////////////////////////////////////////////
  // Associative containers set and multiset
  /////////////////////////////////////////////////////////////////////////

  template<typename Container>
  struct set_traits : public default_container_traits<Container>
  {
    static IndexStyle const index_style = index_style_nonlinear;
  };

  /////////////////////////////////////////////////////////////////////////
  // Associative containers map and multimap
  /////////////////////////////////////////////////////////////////////////

  template<typename Container>
  struct map_traits : public default_container_traits<Container>
  {
    // *FIXME* handle const maps
    typedef typename Container::mapped_type value_type;
    typedef value_type &                    reference;
    typedef typename Container::key_type    index_type; // at()
    typedef typename Container::key_type    key_type; // find, count, ...

    static IndexStyle const index_style = index_style_nonlinear;
  };
}

#endif // container_suite_rmg_20030823_included
