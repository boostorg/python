// -*- mode:c++ -*-
//
// Header file iterator_traits.hpp
//
// Traits information about iterators for use in determining what
// Python methods to support for a container.
//
// Copyright (c) 2003 Raoul M. Gough
//
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy
// at http://www.boost.org/LICENSE_1_0.txt)
//
// History
// =======
// 2003/ 8/23   rmg     File creation as iterator_suite.hpp
// 2003/ 9/12   rmg     Renamed iterator_traits.hpp
//
// $Id$
//

#ifndef BOOST_PYTHON_INDEXING_ITERATOR_TRAITS_HPP
#define BOOST_PYTHON_INDEXING_ITERATOR_TRAITS_HPP

#include <boost/python/suite/indexing/suite_utils.hpp>

#include <boost/call_traits.hpp>
#include <boost/type_traits.hpp>
#include <boost/iterator/iterator_traits.hpp>
#include <boost/iterator/iterator_categories.hpp>

namespace boost { namespace python { namespace indexing {
#if !BOOST_MSVC
  enum index_style_t {
    index_style_none         // No random access (iteration only)
    , index_style_nonlinear  // Random access by key (no slicing)
    , index_style_linear     // Random access by integer index (allows slicing)
  };
#else
  // MSVC seems to have problems with static member variable constants
  // of enumerated types, where it doesn't believe that an expression
  // like (traits::index_style == index_style_linear) is a
  // compile-time constant. However, the problem doesn't exist for
  // int.
  typedef int index_style_t;
  index_style_t const index_style_none = 0;
  index_style_t const index_style_nonlinear = 1;
  index_style_t const index_style_linear = 2;
#endif

  //////////////////////////////////////////////////////////////////////////
  // Indexing traits for containers based on iterator pairs
  //////////////////////////////////////////////////////////////////////////

  template<typename Iterator>
  struct input_iterator_traits
  {
  private:
    typedef ::boost::detail::iterator_traits<Iterator> std_traits;

  public:
    typedef Iterator                                           iterator;
    typedef BOOST_DEDUCED_TYPENAME std_traits::value_type      value_type;
    typedef BOOST_DEDUCED_TYPENAME std_traits::reference       reference;
    typedef BOOST_DEDUCED_TYPENAME std_traits::difference_type difference_type;

    BOOST_STATIC_CONSTANT (bool,   has_copyable_iter = false);
    BOOST_STATIC_CONSTANT (bool,   is_reorderable    = false);
    BOOST_STATIC_CONSTANT (
        bool, has_mutable_ref = is_mutable_ref<reference>::value);

    BOOST_STATIC_CONSTANT (index_style_t, index_style = index_style_none);
  };

  template<typename Iterator>
  struct forward_iterator_traits
    : public input_iterator_traits<Iterator>
  {
    BOOST_STATIC_CONSTANT (bool,   has_copyable_iter = true);
  };

  template<typename Iterator>
  struct bidirectional_iterator_traits
    : public forward_iterator_traits<Iterator>
  {
    typedef bidirectional_iterator_traits<Iterator> self_type;
    BOOST_STATIC_CONSTANT (bool,   is_reorderable = self_type::has_mutable_ref);
  };

  template<typename Iterator>
  struct random_access_iterator_traits
    : public bidirectional_iterator_traits<Iterator>
  {
    BOOST_STATIC_CONSTANT (index_style_t, index_style = index_style_linear);
  };

  namespace iterator_detail {
    template<typename TraversalTag> struct traits_by_category { };

    template<>
    struct traits_by_category<std::input_iterator_tag> {
      template<typename Iterator>
        struct traits {
          typedef input_iterator_traits<Iterator> type;
        };
    };

    template<>
    struct traits_by_category<std::forward_iterator_tag> {
      template<typename Iterator>
        struct traits {
          typedef forward_iterator_traits<Iterator> type;
        };
    };

    template<>
    struct traits_by_category<std::bidirectional_iterator_tag> {
      template<typename Iterator>
        struct traits {
          typedef bidirectional_iterator_traits<Iterator> type;
        };
    };

    template<>
    struct traits_by_category<std::random_access_iterator_tag > {
      template<typename Iterator>
        struct traits {
          typedef random_access_iterator_traits<Iterator> type;
        };
    };

    template<typename Iterator>
    class deduced_traits {
      typedef BOOST_DEDUCED_TYPENAME BOOST_ITERATOR_CATEGORY<
          Iterator>::type category;

      typedef BOOST_DEDUCED_TYPENAME ::boost::detail::std_category <
          category>::type max_category;

    public:
      typedef typename traits_by_category <max_category>
        ::template traits<Iterator>::type type;
    };
  }

  template<typename Iterator>
  struct iterator_traits
    : public iterator_detail::deduced_traits<Iterator>::type
  {
  };
} } }

#endif // BOOST_PYTHON_INDEXING_ITERATOR_TRAITS_HPP
