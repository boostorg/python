// -*- mode:c++ -*-
//
// Header file proxy_iterator.hpp
//
// Copyright (c) 2003 Raoul M. Gough
//
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy
// at http://www.boost.org/LICENSE_1_0.txt)
//
// History
// =======
// 2003/10/ 8   rmg     File creation
//
// $Id$
//

#ifndef proxy_iterator_rmg_20031008_included
#define proxy_iterator_rmg_20031008_included

#include <iterator>

namespace boost { namespace python { namespace indexing {
  template<class ContainerProxy>
  struct proxy_iterator
  {
    template<class C, class H> friend class container_proxy;

    typedef ContainerProxy container_proxy_;
    typedef typename container_proxy_::raw_iterator_traits raw_iterator_traits;
    typedef typename raw_iterator_traits::difference_type difference_type;
    typedef typename container_proxy_::size_type size_type;
    typedef typename container_proxy_::value_type value_type;
    typedef typename container_proxy_::raw_iterator raw_iterator;
    typedef value_type *pointer;
    typedef value_type reference;  // Already has reference semantics
    typedef std::random_access_iterator_tag iterator_category;

    proxy_iterator (container_proxy_ *p, size_type i) : ptr (p), index (i) { }
 
    proxy_iterator (container_proxy_ *p, raw_iterator iter)
      : ptr (p), index (iter - p->raw_container().begin())
    {
    }

    reference operator*() const { return ptr->at(index); }
    pointer operator->() const { return &ptr->at(index); }
    reference operator[](size_type s) { return ptr->at (index + s); }

    proxy_iterator &operator++ () { ++index; return *this; }
    proxy_iterator &operator+= (size_type s) { index += s; return *this; }

    proxy_iterator &operator-- () { --index; return *this; }

    proxy_iterator operator++ (int) {
      proxy_iterator temp(*this);
      ++index;
      return temp;
    }

    proxy_iterator operator-- (int) {
      proxy_iterator temp(*this);
      --index;
      return temp;
    }

    proxy_iterator &operator-= (size_type s) { index -= s; return *this; }

    proxy_iterator operator+ (size_type s) const {
      return proxy_iterator(*this) += s;
    }

    proxy_iterator operator- (size_type s) const {
      return proxy_iterator(*this) -= s;
    }

    difference_type operator- (proxy_iterator i) const {
      return index - i.index;
    }

    bool operator== (proxy_iterator const &other) const {
      return (ptr == other.ptr) && (index == other.index);
    }

    bool operator!= (proxy_iterator const &other) const {
      return !(*this == other);
    }

    bool operator< (proxy_iterator const &other) const {
      return index < other.index;
    }

    bool operator> (proxy_iterator const &other) const {
      return index > other.index;
    }

    void iter_swap (proxy_iterator const &other) const {
      ptr->swap_elements (index, other.index);
    }

    //  public:
    // Extensions to the normal iterator interface
    //    void replace (value_type const &copy) { ptr->replace (index, copy); }

  public:
    container_proxy_ *ptr;
    size_type index;
  };
} } }

namespace std {
  template<class C>
  void iter_swap (boost::python::indexing::proxy_iterator<C> const &first
                  , boost::python::indexing::proxy_iterator<C> const &second)
  {
    first.iter_swap (second);
  }
}

#endif // proxy_iterator_rmg_20031008_included
