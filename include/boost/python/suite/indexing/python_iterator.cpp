// -*- mode:c++ -*-
//
// Module python_iterator.cpp
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

#include "python_iterator.hpp"

////////////////////////////////////////////////////////////////////////////
// python_iterator factory
///////////////////////////////////////////////////////////////////////////

std::auto_ptr<indexing::python_iterator>
indexing::make_iterator (boost::python::object temp)
{
  std::auto_ptr<python_iterator> result;

  try
    {
      result.reset (new python_iter_iterator (temp));
    }

  catch (boost::python::error_already_set const &)
    {
      PyErr_Clear ();

      try
	{
	  result.reset (new python_getitem_iterator (temp));
	}

      catch (boost::python::error_already_set const &)
	{
	  PyErr_Clear ();
	}
    }

  return result;
}

////////////////////////////////////////////////////////////////////////////
// Base class (virtual) destructor
///////////////////////////////////////////////////////////////////////////

indexing::python_iterator::~python_iterator ()
{
}

////////////////////////////////////////////////////////////////////////////
// python_getitem_iterator constructor
///////////////////////////////////////////////////////////////////////////

indexing::python_getitem_iterator
::python_getitem_iterator (boost::python::object obj)
  : mGetitemMethod (obj.attr ("__getitem__"))
  , mIndex (0)
  , mCurrent()
{
}

////////////////////////////////////////////////////////////////////////////
// Get our next item (if any)
///////////////////////////////////////////////////////////////////////////

bool indexing::python_getitem_iterator::next ()
{
  bool result = true; // Assume success

  try
    {
      mCurrent = mGetitemMethod (mIndex);
      ++mIndex;
    }

  catch (boost::python::error_already_set const &)
    {
      if (PyErr_ExceptionMatches (PyExc_IndexError))
	{
	  // Eat this exception
	  PyErr_Clear ();
	  mCurrent = boost::python::object ();
	  result = false;
	}

      else
	{
	  // Pass it up the line
	  throw;
	}
    }

  return result;
}

////////////////////////////////////////////////////////////////////////////
// Return our current item
///////////////////////////////////////////////////////////////////////////

boost::python::object indexing::python_getitem_iterator::current () const
{
  return mCurrent;
}

////////////////////////////////////////////////////////////////////////////
// python_iter_iterator constructor
///////////////////////////////////////////////////////////////////////////

indexing::python_iter_iterator
::python_iter_iterator (boost::python::object obj)
  : mNextMethod (obj.attr ("__iter__")().attr ("next"))
  , mCurrent()
{
}

////////////////////////////////////////////////////////////////////////////
// Get our next item (if any)
///////////////////////////////////////////////////////////////////////////

bool indexing::python_iter_iterator::next ()
{
  bool result = true; // Assume success

  try
    {
      mCurrent = mNextMethod ();
    }

  catch (boost::python::error_already_set const &)
    {
      if (PyErr_ExceptionMatches (PyExc_StopIteration))
	{
	  // Eat this exception
	  PyErr_Clear ();
	  mCurrent = boost::python::object ();
	  result = false;
	}

      else
	{
	  // Pass it up the line
	  throw;
	}
    }

  return result;
}

////////////////////////////////////////////////////////////////////////////
// Return our current item
///////////////////////////////////////////////////////////////////////////

boost::python::object indexing::python_iter_iterator::current () const
{
  return mCurrent;
}
