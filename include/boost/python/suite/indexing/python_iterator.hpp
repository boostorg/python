// -*- mode:c++ -*-
//
// Header file python_iterator.hpp
//
// Handy Python iterable iterators
//
// Copyright (c) 2003 Raoul M. Gough
//
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy
// at http://www.boost.org/LICENSE_1_0.txt)
//
// History
// =======
// 2003/ 9/10   rmg     File creation
//
// $Id$
//

#ifndef python_iterator_rmg_20030910_included
#define python_iterator_rmg_20030910_included

#include <boost/python/object.hpp>
#include <memory>

namespace boost { namespace python { namespace indexing {
  struct BOOST_PYTHON_DECL python_iterator
  {
    virtual ~python_iterator ();
    virtual bool next () = 0;
    virtual boost::python::object current() const = 0;
  };

  BOOST_PYTHON_DECL
  std::auto_ptr<python_iterator>
  make_iterator (boost::python::object);
  // Returns null auto_ptr if object does not provide __iter__ nor
  // __getitem__, otherwise a pointer to a suitable implementation of
  // python_iterator

  struct BOOST_PYTHON_DECL python_getitem_iterator : public python_iterator
  {
  public:
    python_getitem_iterator (boost::python::object);
    virtual bool next ();
    virtual boost::python::object current() const;

  private:
    boost::python::object m_getitem_method;
    int m_index;
    boost::python::object m_current;
  };

  struct BOOST_PYTHON_DECL python_iter_iterator : public python_iterator
  {
  public:
    python_iter_iterator (boost::python::object);
    virtual bool next ();
    virtual boost::python::object current() const;

  private:
    boost::python::object m_next_method;
    boost::python::object m_current;
  };
} } }

#endif // python_iterator_rmg_20030910_included
