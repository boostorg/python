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
#include <algorithm>

/////////////////////////////////////////////////////////////////////////////
// slice copy constructor
/////////////////////////////////////////////////////////////////////////////

boost::python::indexing::slice::slice (slice const &copy)
  : object (copy)
{
}

/////////////////////////////////////////////////////////////////////////////
// integer_slice constructor
/////////////////////////////////////////////////////////////////////////////

boost::python::indexing::integer_slice
::integer_slice (slice const &sl, index_type sequenceLength)
  : mSlice (sl)
  // Leave index members uninitialized
{
  PySlice_GetIndices (reinterpret_cast<PySliceObject *> (mSlice.ptr())
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
// Check if an index is within the range of this integer_slice
/////////////////////////////////////////////////////////////////////////////

bool boost::python::indexing::integer_slice::in_range (index_type index)
{
  return ((mStop - index) * mDirection) > 0;
}
