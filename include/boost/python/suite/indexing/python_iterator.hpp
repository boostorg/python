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
  struct python_iterator
  {
    virtual ~python_iterator ();
    virtual bool next () = 0;
    virtual boost::python::object current() const = 0;
  };

  std::auto_ptr<python_iterator> make_iterator (boost::python::object);
  // Returns null auto_ptr if object does not provide __iter__ nor
  // __getitem__, otherwise a pointer to a suitable implementation of
  // python_iterator

  struct python_getitem_iterator : public python_iterator
  {
  public:
    python_getitem_iterator (boost::python::object);
    virtual bool next ();
    virtual boost::python::object current() const;

  private:
    boost::python::object mGetitemMethod;
    int mIndex;
    boost::python::object mCurrent;
  };

  struct python_iter_iterator : public python_iterator
  {
  public:
    python_iter_iterator (boost::python::object);
    virtual bool next ();
    virtual boost::python::object current() const;

  private:
    boost::python::object mNextMethod;
    boost::python::object mCurrent;
  };
} } }

#endif // python_iterator_rmg_20030910_included
