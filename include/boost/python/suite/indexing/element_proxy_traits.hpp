// Header file element_proxy_traits.hpp
//
// Copyright (c) 2003 Raoul M. Gough
//
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy
// at http://www.boost.org/LICENSE_1_0.txt)
//
// This is a separate header so that element_proxy.hpp is not
// dependant on register_ptr_to_python.hpp. This avoids a problem with
// two-phase name lookup, where register_ptr_to_python must be
// included *after* the element_proxy overload of boost::get_pointer
// is defined.
//
// History
// =======
// 2003/10/23   rmg     File creation
//
// $Id$
//

#ifndef BOOST_PYTHON_INDEXING_ELEMENT_PROXY_TRAITS_HPP
#define BOOST_PYTHON_INDEXING_ELEMENT_PROXY_TRAITS_HPP

#include <boost/python/suite/indexing/element_proxy.hpp>
#include <boost/python/suite/indexing/value_traits.hpp>
#include <boost/python/register_ptr_to_python.hpp>
#include <boost/python/implicit.hpp>

namespace boost { namespace python { namespace indexing {
  template<typename ContainerProxy>
  struct element_proxy_traits
    : public value_traits <
          BOOST_DEDUCED_TYPENAME ContainerProxy::raw_value_type>
  {
    typedef element_proxy<ContainerProxy> element_proxy_;
    typedef typename ContainerProxy::raw_value_type raw_value_type;
    typedef value_traits<raw_value_type> base_type;

    // Wrap the base class versions of the comparisons using
    // indirection
    struct less
      : std::binary_function<element_proxy_, element_proxy_, bool>
    {
      typename base_type::less m_base_compare;

      bool operator() (
          element_proxy_ const &p1, element_proxy_ const &p2) const
      {
        return m_base_compare (*p1, *p2);
      }
    };

    struct equal_to
      : std::binary_function<raw_value_type, element_proxy_, bool>
    {
      // First param is raw_value_type to interface smoothly with the
      // bind1st used in default_algorithms::find

      typename base_type::equal_to m_base_compare;

      bool operator() (
          raw_value_type const &v, element_proxy_ const &p) const
      {
        return m_base_compare (v, *p);
      }
    };

    template<typename PythonClass, typename Policy>
    static void visitor_helper (PythonClass &, Policy const &)
    {
      boost::python::register_ptr_to_python<element_proxy_>();
      boost::python::implicitly_convertible<raw_value_type, element_proxy_>();
    }
  };

#if !defined (BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
  // value_traits partial specialization for element_proxy instances
  template<typename ContainerProxy>
  struct value_traits<element_proxy<ContainerProxy> >
    : element_proxy_traits<ContainerProxy>
  {
  };
#endif
} } }

#endif // BOOST_PYTHON_INDEXING_ELEMENT_PROXY_TRAITS_HPP
