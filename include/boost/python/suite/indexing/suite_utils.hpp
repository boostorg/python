// Header file suite_utils.hpp
//
// Shared utilities for the indexing suite.
//
// Copyright (c) 2003 Raoul M. Gough
//
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy
// at http://www.boost.org/LICENSE_1_0.txt)
//
// History
// =======
// 2003/ 8/23   rmg     File creation
//
// $Id$
//

#ifndef BOOST_PYTHON_INDEXING_SUITE_UTILS_HPP
#define BOOST_PYTHON_INDEXING_SUITE_UTILS_HPP

#include <boost/type_traits.hpp>

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

  template<typename T>
  class is_mutable_ref
  {
    typedef typename boost::remove_reference<T>::type maybe_const;

  public:
    static bool const value = ! boost::is_const<maybe_const>::value;
  };

  // make_signed attempts to identify the signed version of any
  // numeric type (useful in this case because Python container
  // indexes can be negative).
  template<typename T> struct make_signed {
    typedef T type;
  };

  template<> struct make_signed<char> {
    // Raw "char" could be signed or unsigned. "signed char"
    // guarantess signedness
    typedef signed char type;
  };

  template<> struct make_signed<unsigned char> {
    typedef signed char type;
  };

  template<> struct make_signed<unsigned short> {
    typedef short type;
  };

  template<> struct make_signed<unsigned int> {
    typedef int type;
  };

  template<> struct make_signed<unsigned long> {
    typedef long type;
  };

#if defined (BOOST_HAS_LONG_LONG)
  template<> struct make_signed<unsigned long long> {
    typedef long long type;
  };
#elif defined (BOOST_HAS_MS_INT64)
  template<> struct make_signed<unsigned __int64> {
    typedef __int64 type;
  };
#endif
} } }

#endif // BOOST_PYTHON_INDEXING_SUITE_UTILS_HPP
