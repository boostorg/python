// -*- mode:c++ -*-
//
// Header file python_iterator.hpp
//
// Handy Python iterable iterators
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
// 2003/ 9/10	rmg	File creation
//
// $Id$
//

#ifndef python_iterator_rmg_20030910_included
#define python_iterator_rmg_20030910_included

#include <boost/python/object.hpp>
#include <memory>

namespace indexing {
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
}

#endif // python_iterator_rmg_20030910_included
