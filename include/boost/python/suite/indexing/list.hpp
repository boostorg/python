// Header file list.hpp
//
// Copyright (c) 2003 Raoul M. Gough
//
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy
// at http://www.boost.org/LICENSE_1_0.txt)
//
// Indexing algorithms support for std::list instances
//
// History
// =======
// 2003/10/28   rmg     File creation from algo_selector.hpp
//
// $Id$
//

#ifndef BOOST_PYTHON_INDEXING_LIST_HPP
#define BOOST_PYTHON_INDEXING_LIST_HPP

#include <boost/python/suite/indexing/container_traits.hpp>
#include <boost/python/suite/indexing/algorithms.hpp>
#include <boost/python/suite/indexing/algo_selector.hpp>
#include <list>

namespace boost { namespace python { namespace indexing {
  /////////////////////////////////////////////////////////////////////////
  // Algorithms implementation for std::list instances
  /////////////////////////////////////////////////////////////////////////

  template<typename ContainerTraits, typename Ovr = detail::no_override>
  class list_algorithms
    : public default_algorithms
        <ContainerTraits
        , typename detail::maybe_override
            <list_algorithms<ContainerTraits, Ovr>, Ovr>
          ::type>
  {
    typedef list_algorithms<ContainerTraits, Ovr> self_type;
    typedef typename detail::maybe_override<self_type, Ovr>::type most_derived;
    typedef default_algorithms<ContainerTraits, most_derived> Parent;

  public:
    typedef typename Parent::container container;

    // Use member functions for the following (hiding base class versions)
    static void      reverse    (container &);
    static void      sort       (container &);
    //    static void      sort       (container &, PyObject *);
  };

  namespace detail {
    ///////////////////////////////////////////////////////////////////////
    // algo_selector support for std::list instances
    ///////////////////////////////////////////////////////////////////////

    template <class T, class Allocator>
    class selector_impl<std::list<T, Allocator> >
    {
      typedef std::list<T, Allocator> Container;

      typedef default_sequence_traits<Container>       mutable_traits;
      typedef default_sequence_traits<Container const> const_traits;

    public:
      typedef list_algorithms<mutable_traits> mutable_algorithms;
      typedef list_algorithms<const_traits>   const_algorithms;
    };
  }

  /////////////////////////////////////////////////////////////////////////
  // Reverse the contents of a list (using member function)
  /////////////////////////////////////////////////////////////////////////

  template<typename ContainerTraits, typename Ovr>
  void list_algorithms<ContainerTraits, Ovr>::reverse (container &c)
  {
    c.reverse();
  }

  /////////////////////////////////////////////////////////////////////////
  // Sort the contents of a list (using member function)
  /////////////////////////////////////////////////////////////////////////

  template<typename ContainerTraits, typename Ovr>
  void list_algorithms<ContainerTraits, Ovr>::sort (container &c)
  {
    c.sort();
  }
} } }

#endif // BOOST_PYTHON_INDEXING_LIST_HPP
