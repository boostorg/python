// -*- mode:c++ -*-
//
// Header file element_proxy.hpp
//
// Proxy objects for invidivual elements in a container wrapped by
// container_proxy
//
// Copyright (c) 2003 Raoul M. Gough
//
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy
// at http://www.boost.org/LICENSE_1_0.txt)
//
// History
// =======
// 2003/ 9/15   rmg     File creation from container_proxy.hpp
//
// $Id$
//

#ifndef element_proxy_rmg_20030915_included
#define element_proxy_rmg_20030915_included

#include <boost/python/suite/indexing/shared_proxy_impl.hpp>
#include <boost/python/suite/indexing/value_traits.hpp>

#include <boost/shared_ptr.hpp>
#include <boost/get_pointer.hpp>

// More headers are included near the bottom of this file

namespace boost { namespace python { namespace indexing {
  template<typename ContainerProxy>
  class element_proxy
  {
    template<typename T> friend struct const_element_proxy;

    typedef ContainerProxy container_proxy;
    typedef typename container_proxy::shared_proxy proxy_type;
    typedef boost::shared_ptr<proxy_type> proxy_pointer;
    typedef typename container_proxy::raw_value_type raw_value_type;
    typedef typename container_proxy::size_type size_type;

    proxy_pointer mPtr;

  public:
    typedef typename proxy_type::value_type value_type;
    typedef typename proxy_type::reference reference;
    typedef typename proxy_type::pointer pointer;
    typedef typename proxy_type::iterator_category iterator_category;
    typedef typename proxy_type::difference_type difference_type;

    typedef value_type element_type;      // Alias for register_ptr_to_python

    element_proxy () : mPtr () { }
    explicit element_proxy (proxy_type *ptr) : mPtr (ptr) { }
    element_proxy (proxy_pointer const &ptr) : mPtr (ptr) { }

    explicit element_proxy (raw_value_type const &val)
      : mPtr (new proxy_type(val))
    {
      // Create new standalone value (i.e. detached)
    }

    reference operator* () const { return mPtr->operator*(); }
    pointer operator-> () const { return (*mPtr).operator->(); }
    pointer get () const { return operator->(); }  // Alias for pointer_holder

    // Implicit conversion to raw_value_type
    operator reference () const { return operator*(); }

    // These are necessary (at least) while the indexing suite insists
    // on converting the real container's value_type to the proxy
    // container's value_type when going from Python to C++. If the
    // suite would just pass the real container's value_type through,
    // our implicit conversion to value_type might suffice.
    bool operator== (value_type const &other) { return (**this) == other; }
    bool operator!= (value_type const &other) { return (**this) != other; }
    bool operator< (value_type const &other) { return (**this) < other; }
    bool operator> (value_type const &other) { return (**this) > other; }

    element_proxy &operator= (value_type const &copy)
    {
      proxy_type &proxy (*mPtr);
      container_proxy *container = proxy.owner();
      size_type index = proxy.index();

      if (container)
        {
          container->replace (index, copy);
          // Proxy was attached before, but is now detached. Make sure
          // we now refer to the new element, instead of the detached
          // copy of the old element
          mPtr = container->at (index).mPtr;

          // Note: in the special case that this we and the container
          // proxy itself have the only references to the
          // shared_proxy_impl, it is not necessary to first detach
          // the proxy. Maybe best to implement when changing to
          // intrusive_ptr instead of shared_ptr.
        }

      else
        {
          *proxy = copy;
        }

      return *this;
    }

    element_proxy &operator= (element_proxy const &copy)
    {
      // This is the most dubious bit of the fudge. The indexing_suite's
      // implementation of __setitem__ tries to pass us our value_type,
      // which is actually of type element_proxy
      return (*this) = *copy;
    }

    size_t use_count() const { return mPtr.use_count(); } // For debugging
  };

  template<typename ContainerProxy>
  struct const_element_proxy
  {
    typedef ContainerProxy container_proxy;
    typedef typename container_proxy::shared_proxy proxy_type;
    typedef boost::shared_ptr<proxy_type> proxy_pointer;
    typedef typename container_proxy::raw_value_type raw_value_type;

    proxy_pointer mPtr;

  public:
    typedef typename proxy_type::value_type const value_type;
    typedef value_type &reference;
    typedef value_type *pointer;
    typedef typename proxy_type::iterator_category iterator_category;
    typedef typename proxy_type::difference_type difference_type;

    const_element_proxy () : mPtr () { }
    explicit const_element_proxy (proxy_type *ptr) : mPtr (ptr) { }
    const_element_proxy (proxy_pointer const &ptr) : mPtr (ptr) { }

    const_element_proxy (element_proxy<container_proxy> const &copy)
      : mPtr (copy.mPtr)
    {
    }

    explicit const_element_proxy (raw_value_type const &val)
      : mPtr (new proxy_type(val))
    {
      // Create new standalone value (i.e. detached)
    }

    reference operator* () const { return mPtr->operator*(); }
    pointer operator-> () const { return mPtr->operator->(); }

    // Implicit conversion to raw_value_type
    operator reference () const { return operator*(); }

    size_t use_count() const { return mPtr.use_count(); } // For debugging
  };
} } }

namespace boost
{
  template<typename ContainerProxy>
  typename ContainerProxy::raw_value_type *
  get_pointer (python::indexing::element_proxy<ContainerProxy> const &proxy)
  {
    return &(*proxy);
  }
}

// Including more headers here is a little weird, but it make sure
// that our overload of get_pointer is in scope during both
// name-lookup phases (if the compiler implements two-phase name
// lookup). get_pointer is used unqualified within some templates used
// by register_ptr_to_python.

#include <boost/python/implicit.hpp>
#include <boost/python/register_ptr_to_python.hpp>

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

#endif // element_proxy_rmg_20030915_included
