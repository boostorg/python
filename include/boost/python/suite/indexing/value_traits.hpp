// -*- mode:c++ -*-
//
// Header file value_traits.hpp
//
// Traits information about container element types for use in
// determining which Python methods to support for a container.
//
// Copyright (c) 2003 Raoul M. Gough
//
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy
// at http://www.boost.org/LICENSE_1_0.txt)
//
// History
// =======
// 2003/ 9/12   rmg     File creation
//
// $Id$
//

#ifndef BOOST_PYTHON_INDEXING_VALUE_TRAITS_HPP
#define BOOST_PYTHON_INDEXING_VALUE_TRAITS_HPP

#include <boost/config.hpp>
#include <functional>

namespace boost { namespace python { namespace indexing {
  template<typename T>
  struct value_traits {
    BOOST_STATIC_CONSTANT (bool, equality_comparable = true);
    typedef std::equal_to<T> equal_to;

    BOOST_STATIC_CONSTANT (bool, lessthan_comparable = true);
    typedef std::less<T> less;

    // Default, do-nothing, version of visitor_helper
    template<typename PythonClass, typename Policy>
    static void visitor_helper (PythonClass &, Policy const &) { }
  };
} } }

#endif // BOOST_PYTHON_INDEXING_VALUE_TRAITS_HPP
