// -*- mode:c++ -*-
//
// Header file suite_utils.hpp
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
#include <boost/call_traits.hpp>
#include <algorithm>

namespace indexing {
  template<typename T>
  class is_mutable_ref
  {
    typedef typename boost::remove_reference<T>::type maybe_const;

  public:
    static bool const value = ! boost::is_const<maybe_const>::value;
  };

  template<typename ContainerTraits>
  struct container_algorithms
  {
    typedef typename ContainerTraits::container container;
    typedef typename ContainerTraits::iterator iterator;
    typedef typename ContainerTraits::key_type key_type;
    typedef typename ContainerTraits::size_type size_type;
    typedef typename ContainerTraits::index_type index_type;

    typedef typename boost::call_traits<key_type>::param_type key_param;
    typedef typename boost::call_traits<index_type>::param_type index_param;

    static size_type size       (container &);
    static iterator  find       (container &, key_param);
    static size_type count      (container &, key_param);
    static void      reverse    (container &);
    static iterator  at         (container&, index_param);
    static void      sort       (container &);
    //    static void      sort       (container &, PyObject *);
  };

  /////////////////////////////////////////////////////////////////////////
  // Get the size of a container
  /////////////////////////////////////////////////////////////////////////

  template<typename ContainerTraits>
  typename container_algorithms<ContainerTraits>::size_type
  container_algorithms<ContainerTraits>::size (container &c)
  {
    return c.size();
  }

  /////////////////////////////////////////////////////////////////////////
  // Find an element in a container (std algorithm version)
  /////////////////////////////////////////////////////////////////////////

  template<typename ContainerTraits>
  typename container_algorithms<ContainerTraits>::iterator
  container_algorithms<ContainerTraits>::find (container &c
					       , key_param key)
  {
    return std::find (c.begin(), c.end(), key);
  }

  /////////////////////////////////////////////////////////////////////////
  // Count occurances of an element in a container (std algorithm version)
  /////////////////////////////////////////////////////////////////////////

  template<typename ContainerTraits>
  typename container_algorithms<ContainerTraits>::size_type
  container_algorithms<ContainerTraits>::count (container &c
						, key_param key)
  {
    return std::count (c.begin(), c.end(), key);
  }

  /////////////////////////////////////////////////////////////////////////
  // Index into a container (iterator version)
  /////////////////////////////////////////////////////////////////////////

  template<typename ContainerTraits>
  typename container_algorithms<ContainerTraits>::iterator
  container_algorithms<ContainerTraits>::at (container &c, index_param ix)
  {
    return c.begin() + ix;
  }

  /////////////////////////////////////////////////////////////////////////
  // Reverse the contents of a container (std algorithm version)
  /////////////////////////////////////////////////////////////////////////

  template<typename ContainerTraits>
  void container_algorithms<ContainerTraits>::reverse (container &c)
  {
    std::reverse (c.begin(), c.end());
  }

  /////////////////////////////////////////////////////////////////////////
  // Sort the contents of a container (std algorithm version)
  /////////////////////////////////////////////////////////////////////////

  template<typename ContainerTraits>
  void container_algorithms<ContainerTraits>::sort (container &c)
  {
    std::sort (c.begin(), c.end());
  }

  /////////////////////////////////////////////////////////////////////////
  // Special cases for std::list
  /////////////////////////////////////////////////////////////////////////

  template<typename ContainerTraits>
  struct list_algorithms : public container_algorithms<ContainerTraits>
  {
  private:
    typedef container_algorithms<ContainerTraits> Parent;

  public:
    typedef typename Parent::container container;

    // Use member functions for the following (hiding base class versions)
    static void      reverse    (container &);
    static void      sort       (container &);
    //    static void      sort       (container &, PyObject *);
  };

  /////////////////////////////////////////////////////////////////////////
  // Reverse the contents of a list (member function version)
  /////////////////////////////////////////////////////////////////////////

  template<typename ContainerTraits>
  void list_algorithms<ContainerTraits>::reverse (container &c)
  {
    c.reverse();
  }

  /////////////////////////////////////////////////////////////////////////
  // Sort the contents of a container (std algorithm version)
  /////////////////////////////////////////////////////////////////////////

  template<typename ContainerTraits>
  void list_algorithms<ContainerTraits>::sort (container &c)
  {
    c.sort();
  }

  /////////////////////////////////////////////////////////////////////////
  // Special cases for associative containers
  /////////////////////////////////////////////////////////////////////////

  template<typename ContainerTraits>
  struct assoc_algorithms : public container_algorithms<ContainerTraits>
  {
  private:
    typedef container_algorithms<ContainerTraits> Parent;

  public:
    typedef typename Parent::iterator iterator;
    typedef typename Parent::size_type size_type;
    typedef typename Parent::container container;
    typedef typename Parent::key_param key_param;

    // Use member functions for the following (hiding base class versions)
    static iterator  find  (container &, key_param);
    static size_type count (container &, key_param);
  };

  /////////////////////////////////////////////////////////////////////////
  // Find an element in an associative container
  /////////////////////////////////////////////////////////////////////////

  template<typename ContainerTraits>
  typename assoc_algorithms<ContainerTraits>::iterator
  assoc_algorithms<ContainerTraits>::find (container &c, key_param key)
  {
    return c.find (key);
  }

  /////////////////////////////////////////////////////////////////////////
  // Count occurances of an element in a container (std algorithm version)
  /////////////////////////////////////////////////////////////////////////

  template<typename ContainerTraits>
  typename assoc_algorithms<ContainerTraits>::size_type
  assoc_algorithms<ContainerTraits>::count (container &c, key_param key)
  {
    return c.count (key);
  }
}

#endif // suite_utils_rmg_20030823_included
