// -*- mode:c++ -*-
//
// Module slice.cpp
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

#include "slice.hpp"

/////////////////////////////////////////////////////////////////////////////
// Check that setLength has been called, and throw otherwise
/////////////////////////////////////////////////////////////////////////////

void indexing::slice::validate () const
{
  if (mDirection == 0)
    {
      PyErr_SetString (PyExc_RuntimeError
		       , "slice access attempted before setLength called");
      boost::python::throw_error_already_set();
    }
}

/////////////////////////////////////////////////////////////////////////////
// Slice constructor
/////////////////////////////////////////////////////////////////////////////

indexing::slice::slice (boost::python::detail::borrowed_reference ref)
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

  // This slice object is useless until setLength is called
}

/////////////////////////////////////////////////////////////////////////////
// Set up our member variables for a sequence of a given length
/////////////////////////////////////////////////////////////////////////////

void indexing::slice::setLength (int sequenceLength)
{
  PySlice_GetIndices ((PySliceObject *) this->ptr()
		      , sequenceLength
		      , &mStart
		      , &mStop
		      , &mStep);

  if (mStep == 0)
    {
      // Can happen with Python prior to 2.3
      PyErr_SetString (PyExc_ValueError, "slice step cannot be zero");
      boost::python::throw_error_already_set ();
    }

  mStart = std::max (0, std::min (sequenceLength, mStart));
  mStop = std::max (0, std::min (sequenceLength, mStop));
  mDirection = (mStep > 0) ? 1 : -1;
}

/////////////////////////////////////////////////////////////////////////////
// Check if an index is within the range of this slice
/////////////////////////////////////////////////////////////////////////////

bool indexing::slice::inRange (int index)
{
  return ((mStop - index) * mDirection) > 0;
}
