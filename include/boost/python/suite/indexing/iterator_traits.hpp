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

namespace boost { namespace python { namespace indexing {
#if !BOOST_MSVC
  enum IndexStyle {
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
  typedef int IndexStyle;
  IndexStyle const index_style_none = 0;
  IndexStyle const index_style_nonlinear = 1;
  IndexStyle const index_style_linear = 2;
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
    typedef Iterator                              iterator;
    typedef typename std_traits::value_type       value_type;
    typedef typename std_traits::reference        reference;
    typedef typename std_traits::difference_type  difference_type;

    BOOST_STATIC_CONSTANT (bool,   has_copyable_iter = false);
    BOOST_STATIC_CONSTANT (bool,   is_reorderable    = false);
    BOOST_STATIC_CONSTANT (
        bool, has_mutable_ref = is_mutable_ref<reference>::value);

    BOOST_STATIC_CONSTANT (IndexStyle,   index_style = index_style_none);
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
    BOOST_STATIC_CONSTANT (IndexStyle,   index_style = index_style_linear);
  };

  namespace iterator_detail {
    typedef char input_sizer[1];
    typedef char forward_sizer[2];
    typedef char bidirectional_sizer[3];
    typedef char random_access_sizer[4];

#if BOOST_WORKAROUND(__EDG_VERSION__, <= 238)
    // Fix tested on "MIPSpro Compilers: Version 7.3.1.3m", where the
    // overload resolution variant causes an "ambiguous by inheritance"
    // error without even instantiating traits_by_category

    template<typename Category> struct is_random_access {
      static bool const value = ::boost::is_convertible<
        Category, std::random_access_iterator_tag>::value;
    };

    template<typename Category> struct is_bidirectional {
      static bool const value = ::boost::is_convertible<
        Category, std::bidirectional_iterator_tag>::value;
    };

    template<typename Category> struct is_forward {
      static bool const value = ::boost::is_convertible<
        Category, std::forward_iterator_tag>::value;
    };

    template<typename Category> struct is_input {
      static bool const value = ::boost::is_convertible<
        Category, std::input_iterator_tag>::value;
    };

    template<typename Category> struct sizer_struct {
      BOOST_STATIC_CONSTANT (size_t, value =
          (is_random_access<Category>::value
           ? sizeof (random_access_sizer)
           : (is_bidirectional<Category>::value
              ? sizeof (bidirectional_sizer)
              : (is_forward<Category>::value
                 ? sizeof (forward_sizer)
                 : (is_input<Category>::value
                    ? sizeof (input_sizer)
                    : 0)))));
    };

#else

    input_sizer &sizer_fn (std::input_iterator_tag const &);
    forward_sizer &sizer_fn (std::forward_iterator_tag const &);
    bidirectional_sizer &sizer_fn (std::bidirectional_iterator_tag const &);
    random_access_sizer &sizer_fn (std::random_access_iterator_tag const &);

    template<typename Category> struct sizer_struct {
      BOOST_STATIC_CONSTANT (size_t, value =
          sizeof (sizer_fn (Category())));
    };

#endif

    template<size_t Size> struct traits_by_size { };

    template<>
    struct traits_by_size<sizeof(input_sizer)> {
      template<typename Iterator>
        struct traits {
          typedef input_iterator_traits<Iterator> type;
        };
    };

    template<>
    struct traits_by_size<sizeof(forward_sizer)> {
      template<typename Iterator>
        struct traits {
          typedef forward_iterator_traits<Iterator> type;
        };
    };

    template<>
    struct traits_by_size<sizeof(bidirectional_sizer)> {
      template<typename Iterator>
        struct traits {
          typedef bidirectional_iterator_traits<Iterator> type;
        };
    };

    template<>
    struct traits_by_size<sizeof(random_access_sizer)> {
      template<typename Iterator>
        struct traits {
          typedef random_access_iterator_traits<Iterator> type;
        };
    };

    template<typename Iterator>
    class traits_by_category {
      typedef typename BOOST_ITERATOR_CATEGORY<Iterator>::type category;

      BOOST_STATIC_CONSTANT (
          size_t, size = sizer_struct<category>::value);

    public:
      typedef typename traits_by_size<size>
        ::template traits<Iterator>::type type;
    };
  }

  template<typename Iterator>
  struct iterator_traits
    : public iterator_detail::traits_by_category<Iterator>::type
  {
  };
} } }

#endif // BOOST_PYTHON_INDEXING_ITERATOR_TRAITS_HPP
