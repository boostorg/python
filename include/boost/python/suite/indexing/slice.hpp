// -*- mode:c++ -*-
//
// Header file slice.hpp
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

#ifndef slice_rmg_20030910_included
#define slice_rmg_20030910_included

#include <boost/python/object.hpp>
#include <boost/python/converter/pytype_object_mgr_traits.hpp>

namespace indexing
{
  struct slice : public boost::python::object
  {
    //
    // *** WARNING ***
    //
    // A newly constructed slice object is useless until setLength is called
    //

    template<typename T> slice (T const &ref);

    void setLength (int sequenceLength);

    int start() const { validate(); return mStart; }
    int step() const  { validate(); return mStep; }
    int stop() const  { validate(); return mStop; }

    int size() const { validate(); return (mStop - mStart) / mStep; }

    bool inRange (int index);

  private:
    void validate () const; // throws unless setLength has been called

    int mStart;
    int mStep;
    int mStop;
    int mDirection;
  };
}

template<typename T>
indexing::slice::slice (T const &ref)
  : boost::python::object (ref)
  , mStart (0)
  , mStep (0)
  , mStop (0)
  , mDirection (0)
{
  if (!PySlice_Check (this->ptr()))
    {
      PyErr_SetString (PyExc_TypeError
		       , "slice constructor: passed a non-slice object");

      boost::python::throw_error_already_set();
    }

  // This slice object is still useless until setLength is called
}

namespace boost { namespace python { namespace converter {
  // Specialized converter to handle PySlice_Type objects
  template<>
  struct object_manager_traits<indexing::slice>
    : pytype_object_manager_traits<&PySlice_Type, ::indexing::slice>
  {
  };
}}}

#endif // slice_rmg_20030910_included
