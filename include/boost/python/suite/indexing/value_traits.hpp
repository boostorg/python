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
#include <boost/shared_ptr.hpp>
#include <functional>

namespace boost { namespace python { namespace indexing {
  // The value_traits template is used by default by all
  // ContainerTraits templates. It can be overridden by specialization
  // or by supplying the optional ValueTraits parameter to a container
  // traits template.
  template<typename T> struct value_traits;

  // Implementation for default use
  template<typename T>
  struct default_value_traits {
    BOOST_STATIC_CONSTANT (bool, equality_comparable = true);
    typedef std::equal_to<T> equal_to;

    BOOST_STATIC_CONSTANT (bool, lessthan_comparable = true);
    typedef std::less<T> less;

    // Default, do-nothing, version of visitor_helper
    template<typename PythonClass, typename Policy>
    static void visitor_helper (PythonClass &, Policy const &) { }
  };

  // Implementation using pointer indirection
  template <typename Ptr>
  struct indirect_value_traits : default_value_traits<Ptr> {
    // Hide the base class versions of the comparisons, using these
    // indirect versions
    struct less : std::binary_function<Ptr, Ptr, bool> {
      bool operator() (Ptr const &p1, Ptr const &p2) const {
        return *p1 < *p2;
      }
    };

    struct equal_to : std::binary_function<Ptr, Ptr, bool> {
      bool operator() (Ptr const &p1, Ptr const &p2) const {
        return *p1 == *p2;
      }
    };
  };

  // Default implementation selection
  template<typename T>
  struct value_traits
    : default_value_traits<T>
  {
  };

#if !defined (BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
  // Partial specialization for instances of boost::shared_ptr
  template<typename T>
  struct value_traits< ::boost::shared_ptr<T> >
    : indirect_value_traits< ::boost::shared_ptr<T> >
  {
  };
#endif
} } }

#endif // BOOST_PYTHON_INDEXING_VALUE_TRAITS_HPP
