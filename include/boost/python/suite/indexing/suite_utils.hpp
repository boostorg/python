// -*- mode:c++ -*-
//
// Header file suite_utils.hpp
//
// Shared utilities for the indexing suite.
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
// 2003/ 8/23	rmg	File creation
//
// $Id$
//

#ifndef suite_utils_rmg_20030823_included
#define suite_utils_rmg_20030823_included

#include <boost/type_traits.hpp>

namespace indexing {
  template<typename T>
  class is_mutable_ref
  {
    typedef typename boost::remove_reference<T>::type maybe_const;

  public:
    static bool const value = ! boost::is_const<maybe_const>::value;
  };
}

#endif // suite_utils_rmg_20030823_included
