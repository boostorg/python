// -*- mode:c++ -*-
//
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

#ifndef suite_utils_rmg_20030823_included
#define suite_utils_rmg_20030823_included

#include <boost/type_traits.hpp>

namespace boost { namespace python { namespace indexing {
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

#endif // suite_utils_rmg_20030823_included
