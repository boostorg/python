//
// Header file element_proxy_traits.hpp
//
// Copyright (c) 2003 Raoul M. Gough
//
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy
// at http://www.boost.org/LICENSE_1_0.txt)
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
  struct value_traits<element_proxy<ContainerProxy> >
    : public value_traits<typename ContainerProxy::raw_value_type>
  {
    template<typename PythonClass, typename Policy>
    static void visitor_helper (PythonClass &, Policy const &)
    {
      typedef element_proxy<ContainerProxy> element_proxy_;
      typedef typename ContainerProxy::raw_value_type raw_value_type;

      boost::python::register_ptr_to_python<element_proxy_>();
      boost::python::implicitly_convertible<raw_value_type, element_proxy_>();
    }
  };
} } }

#endif // BOOST_PYTHON_INDEXING_ELEMENT_PROXY_TRAITS_HPP
