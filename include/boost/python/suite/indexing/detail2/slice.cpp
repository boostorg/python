// -*- mode:c++ -*-
//
// Module slice.cpp
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

#include <boost/python/suite/indexing/slice.hpp>

/////////////////////////////////////////////////////////////////////////////
// Check that setLength has been called, and throw otherwise
/////////////////////////////////////////////////////////////////////////////

void boost::python::indexing::slice::validate () const
{
  if (mDirection == 0)
    {
      PyErr_SetString (PyExc_RuntimeError
                       , "slice access attempted before setLength called");
      boost::python::throw_error_already_set();
    }
}

/////////////////////////////////////////////////////////////////////////////
// Set up our member variables for a sequence of a given length
/////////////////////////////////////////////////////////////////////////////

void boost::python::indexing::slice::setLength (int sequenceLength)
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

bool boost::python::indexing::slice::inRange (int index)
{
  return ((mStop - index) * mDirection) > 0;
}
