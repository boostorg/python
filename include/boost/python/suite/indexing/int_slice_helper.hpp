// -*- mode:c++ -*-
//
// Header file int_slice_helper.hpp
//
// Copyright (c) 2003 Raoul M. Gough
//
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy
// at http://www.boost.org/LICENSE_1_0.txt)
//
// History
// =======
// 2003/10/13   rmg     File creation
//
// $Id$
//

#ifndef BOOST_PYTHON_INDEXING_INT_SLICE_HELPER_HPP
#define BOOST_PYTHON_INDEXING_INT_SLICE_HELPER_HPP

# include <boost/python/errors.hpp>
# include <boost/python/suite/indexing/workaround.hpp>

namespace boost { namespace python { namespace indexing {
  template<typename Algorithms, typename SliceType>
  struct int_slice_helper
  {
    // Works with a SliceType that provides an int-like index_type
    // that is convertible to the algorithm's index_param

    typedef Algorithms algorithms;
    typedef SliceType slice_type;

    typedef typename algorithms::container container;
    typedef typename algorithms::reference reference;
    typedef typename algorithms::value_param value_param;
    typedef typename algorithms::container_traits container_traits;
    typedef typename slice_type::index_type index_type;

    int_slice_helper (container &c, slice_type const &);

    bool next();

    reference current () const;
    void write (value_param val);
    void erase_remaining () const;

  private:
    void assign (value_param val) const;
    void insert (value_param val);

  private:
    slice_type m_slice;
    container *m_ptr;
    index_type m_pos;
  };

  template<typename Algorithms, typename SliceType>
  int_slice_helper<Algorithms, SliceType>
  ::int_slice_helper (container &c, slice_type const &sl)
    : m_slice (sl)
    , m_ptr (&c)
    , m_pos (-1)
  {
  }

  template<typename Algorithms, typename SliceType>
  bool
  int_slice_helper<Algorithms, SliceType>::next()
  {
    bool result = false; // Assume the worst

    if (m_pos == -1)
      {
        // First time call - get to start of the slice (if any)
        m_pos = m_slice.start();
        result = m_slice.in_range (m_pos);
      }

    else if (m_slice.in_range (m_pos))
      {
        // Subsequent calls - advance by the slice's stride
        m_pos += m_slice.step();
        result = m_slice.in_range (m_pos);
      }

    return result;
  }

  template<typename Algorithms, typename SliceType>
  typename int_slice_helper<Algorithms, SliceType>::reference
  int_slice_helper<Algorithms, SliceType>::current () const
  {
    return algorithms::get (*m_ptr, m_pos);
  }

  template<typename Algorithms, typename SliceType>
  void int_slice_helper<Algorithms, SliceType>::write (value_param val)
  {
    if (next())
      {
        assign (val);
      }

    else
      {
        insert (val);
      }
  }

  template<typename Algorithms, typename SliceType>
  void int_slice_helper<Algorithms, SliceType>::assign (value_param val) const
  {
    algorithms::assign (*m_ptr, m_pos, val);
  }

  namespace detail {
    template<bool doit> struct maybe_insert {
      template<class Algorithms>
      static void apply (
# if defined (BOOST_NO_MEMBER_TEMPLATES) \
        && defined (BOOST_MSVC6_MEMBER_TEMPLATES)
          // Can't explicitly instantiate member function - must let
          // the compiler deduce the argument type from a dummy
          // parameter. Same applies throughout
          Algorithms *,
# endif
          typename Algorithms::container &
          , typename Algorithms::index_param
          , typename Algorithms::value_param)
      {
        PyErr_SetString (
            PyExc_TypeError
            , "container does not support insertion into slice");

        boost::python::throw_error_already_set ();
      }
    };

    template<> struct maybe_insert<true> {
      template<class Algorithms>
      static void apply (
# if defined (BOOST_NO_MEMBER_TEMPLATES) \
        && defined (BOOST_MSVC6_MEMBER_TEMPLATES)
          Algorithms *,
# endif
          typename Algorithms::container &c
          , typename Algorithms::index_param i
          , typename Algorithms::value_param v)
      {
        Algorithms::insert (c, i, v);
      }
    };
  }

  template<typename Algorithms, typename SliceType>
  void int_slice_helper<Algorithms, SliceType>::insert (value_param val)
  {
    if (m_slice.step() != 1)
      {
        PyErr_SetString (
            PyExc_ValueError, "attempt to insert via extended slice");

        boost::python::throw_error_already_set ();
      }

    else
      {
        detail::maybe_insert<container_traits::has_insert>
          ::BOOST_PYTHON_INDEXING_NESTED_TEMPLATE apply
# if defined (BOOST_NO_MEMBER_TEMPLATES) \
        && defined (BOOST_MSVC6_MEMBER_TEMPLATES)
          (static_cast<Algorithms *>(0),
# else
          <Algorithms> (
# endif
              *m_ptr, m_pos, val);

        ++m_pos;  // Advance for any subsequent inserts
      }
  }

  namespace detail {
    template<bool doit> struct maybe_erase {
      template<class Algorithms>
      static void apply (
# if defined (BOOST_NO_MEMBER_TEMPLATES) \
        && defined (BOOST_MSVC6_MEMBER_TEMPLATES)
          Algorithms *,
# endif
          typename Algorithms::container &
          , typename Algorithms::index_param
          , typename Algorithms::index_param)
      {
        PyErr_SetString (
            PyExc_TypeError, "container does not support item deletion");

        boost::python::throw_error_already_set ();
      }
    };

    template<> struct maybe_erase<true> {
      template<class Algorithms>
      static void apply (
# if defined (BOOST_NO_MEMBER_TEMPLATES) \
        && defined (BOOST_MSVC6_MEMBER_TEMPLATES)
          Algorithms *,
# endif
          typename Algorithms::container &c
          , typename Algorithms::index_param from
          , typename Algorithms::index_param to)
      {
        Algorithms::erase_range (c, from, to);
      }
    };
  }

  template<typename Algorithms, typename SliceType>
  void int_slice_helper<Algorithms, SliceType>::erase_remaining () const
  {
    if (m_slice.step() != 1)
      {
        PyErr_SetString (
            PyExc_ValueError, "attempt to delete via extended slice");

        boost::python::throw_error_already_set ();
      }

    else
      {
        detail::maybe_erase<container_traits::has_erase>
          ::BOOST_PYTHON_INDEXING_NESTED_TEMPLATE apply
# if defined (BOOST_NO_MEMBER_TEMPLATES) \
        && defined (BOOST_MSVC6_MEMBER_TEMPLATES)
          (static_cast<Algorithms *>(0),
# else
          <Algorithms> (
# endif
              *m_ptr, m_pos, m_slice.stop());
      }
  }

} } }

#endif // BOOST_PYTHON_INDEXING_INT_SLICE_HELPER_HPP
