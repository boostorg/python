// -*- mode:c++ -*-
//
// Header file iterator_traits.hpp
//
// Traits information about iterators for use in determining what
// Python methods to support for a container.
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
// 2003/ 8/23	rmg	File creation as iterator_suite.hpp
// 2003/ 9/12	rmg	Renamed iterator_traits.hpp
//
// $Id$
//

#ifndef iterator_traits_rmg_20030823_included
#define iterator_traits_rmg_20030823_included

#include "suite_utils.hpp"

#include <iterator>
#include <boost/call_traits.hpp>
#include <boost/type_traits.hpp>

namespace indexing {
  enum IndexStyle {
    index_style_none         // No random access (iteration only)
    , index_style_nonlinear  // Random access by key (no slicing)
    , index_style_linear     // Random access by integer index (allows slicing)
  };

  //////////////////////////////////////////////////////////////////////////
  // Indexing traits for containers based on iterator pairs
  //////////////////////////////////////////////////////////////////////////

  template<typename Iterator>
  struct input_iterator_traits
  {
  private:
    typedef std::iterator_traits<Iterator> std_traits;

  public:
    typedef Iterator                              iterator;
    typedef typename std_traits::value_type       value_type;
    typedef typename std_traits::reference        reference;
    typedef typename std_traits::difference_type  difference_type;

    BOOST_STATIC_CONSTANT (bool,   has_copyable_iter = false);
    BOOST_STATIC_CONSTANT (bool,   is_reversible     = false);
    BOOST_STATIC_CONSTANT (bool,   has_mutable_ref
			   = is_mutable_ref<reference>::value);

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
    BOOST_STATIC_CONSTANT (bool,   is_reversible = has_mutable_ref);
  };

  template<typename Iterator>
  struct random_access_iterator_traits
    : public bidirectional_iterator_traits<Iterator>
  {
    BOOST_STATIC_CONSTANT (IndexStyle,   index_style = index_style_linear);
  };

  namespace iterator_detail {
    typedef char input_iter_sizer[1];
    typedef char forward_iter_sizer[2];
    typedef char bidirectional_iter_sizer[3];
    typedef char random_access_iter_sizer[4];

    input_iter_sizer &sizer (std::input_iterator_tag const &);
    forward_iter_sizer &sizer (std::forward_iterator_tag const &);
    bidirectional_iter_sizer &sizer (std::bidirectional_iterator_tag const &);
    random_access_iter_sizer &sizer (std::random_access_iterator_tag const &);

    template<size_t Size> struct traits_by_size { };

    template<>
    struct traits_by_size<sizeof(input_iter_sizer)> {
      template<typename Iterator>
	struct traits {
	  typedef input_iterator_traits<Iterator> type;
	};
    };

    template<>
    struct traits_by_size<sizeof(forward_iter_sizer)> {
      template<typename Iterator>
	struct traits {
	  typedef forward_iterator_traits<Iterator> type;
	};
    };

    template<>
    struct traits_by_size<sizeof(bidirectional_iter_sizer)> {
      template<typename Iterator>
	struct traits {
	  typedef bidirectional_iterator_traits<Iterator> type;
	};
    };

    template<>
    struct traits_by_size<sizeof(random_access_iter_sizer)> {
      template<typename Iterator>
	struct traits {
	  typedef random_access_iterator_traits<Iterator> type;
	};
    };

    template<typename Iterator>
    class traits_by_category {
      typedef typename std::iterator_traits<Iterator>::iterator_category
        iterator_category;

      BOOST_STATIC_CONSTANT (size_t,   size
			     = sizeof(sizer(iterator_category())));

    public:
      typedef typename traits_by_size<size>::traits<Iterator>::type type;
    };
  }

  template<typename Iterator>
  struct iterator_traits
    : public iterator_detail::traits_by_category<Iterator>::type
  {
  };
}

#endif // iterator_traits_rmg_20030823_included
