// -*- mode:c++ -*-
//
// Header file iterator_pair.hpp
//
// Emulate an STL container using a pair of iterators. Doesn't support
// insertion or deletion, for the obvious reasons.
//
// Copyright (c) 2003 Raoul M. Gough
//
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy
// at http://www.boost.org/LICENSE_1_0.txt)
//
// History
// =======
// 2003/ 9/ 9   rmg     File creation
//
// $Id$
//

#ifndef iterator_pair_rmg_20030909_included
#define iterator_pair_rmg_20030909_included

#include <iterator>
#include <stdexcept>
#include <algorithm>
#include <boost/type_traits.hpp>

namespace boost { namespace python { namespace indexing {
  template<typename Iterator>
  class iterator_pair
  {
  private:
    typedef typename boost::call_traits<Iterator>::param_type iterator_param;
    typedef std::iterator_traits<Iterator> std_traits;

  public:
    typedef typename std_traits::reference       reference;
    typedef Iterator                             iterator;
    typedef typename std_traits::difference_type size_type;
    typedef typename std_traits::difference_type difference_type;
    typedef typename std_traits::value_type      value_type;
    typedef typename std_traits::pointer         pointer;

    // Can't provide: const_iterator, allocator_type, reverse_iterator
    // or const_reverse_iterator. Could probably provide (but don't)
    // const_reference and const_pointer. These would be the same
    // as reference and pointer if Iterator is itself a const_iterator.

  public:
    iterator_pair (iterator_param, iterator_param);

    iterator begin() const;
    iterator end() const;

  public:
    // Only sensible for random_access iterators
    size_type size () const;
    reference operator[] (size_type) const;
    reference at (size_type) const;

  private:
    iterator myBegin;
    iterator myEnd;
  };

  template<typename Iterator>
  iterator_pair<Iterator>::iterator_pair (iterator_param begin
                                          , iterator_param end)
    : myBegin (begin)
    , myEnd (end)
  {
  }

  template<typename Iterator>
  typename iterator_pair<Iterator>::iterator
  iterator_pair<Iterator>::begin() const
  {
    return myBegin;
  }

  template<typename Iterator>
  typename iterator_pair<Iterator>::iterator
  iterator_pair<Iterator>::end() const
  {
    return myEnd;
  }

  template<typename Iterator>
  typename iterator_pair<Iterator>::size_type
  iterator_pair<Iterator>::size() const
  {
    return std::distance (begin(), end());
  }

  template<typename Iterator>
  typename iterator_pair<Iterator>::reference
  iterator_pair<Iterator>::operator[](size_type index) const
  {
    iterator temp (begin());
    std::advance (temp, index);
    return *temp;
  }

  template<typename Iterator>
  typename iterator_pair<Iterator>::reference
  iterator_pair<Iterator>::at (size_type index) const
  {
    if (index >= size())
      {
        throw std::out_of_range
          (std::string ("iterator_pair: index out of range"));
      }

    else
      {
        return (*this)[index];
      }
  }

  template<typename T, std::size_t N>
  T *begin (T(&array)[N]) {
    return array;
  }

  template<typename T, std::size_t N>
  T *end (T(&array)[N]) {
    return array + N;
  }
} } }

#endif // iterator_pair_rmg_20030909_included
