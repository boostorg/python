// -*- mode:c++ -*-
//
// Module python_iterator.cpp
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

#include <boost/python/suite/indexing/python_iterator.hpp>

////////////////////////////////////////////////////////////////////////////
// python_iterator factory
///////////////////////////////////////////////////////////////////////////

std::auto_ptr<boost::python::indexing::python_iterator>
boost::python::indexing::make_iterator (boost::python::object temp)
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

boost::python::indexing::python_iterator::~python_iterator ()
{
}

////////////////////////////////////////////////////////////////////////////
// python_getitem_iterator constructor
///////////////////////////////////////////////////////////////////////////

boost::python::indexing::python_getitem_iterator
::python_getitem_iterator (boost::python::object obj)
  : mGetitemMethod (obj.attr ("__getitem__"))
  , mIndex (0)
  , mCurrent()
{
}

////////////////////////////////////////////////////////////////////////////
// Get our next item (if any)
///////////////////////////////////////////////////////////////////////////

bool boost::python::indexing::python_getitem_iterator::next ()
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

boost::python::object
boost::python::indexing::python_getitem_iterator::current () const
{
  return mCurrent;
}

////////////////////////////////////////////////////////////////////////////
// python_iter_iterator constructor
///////////////////////////////////////////////////////////////////////////

boost::python::indexing::python_iter_iterator
::python_iter_iterator (boost::python::object obj)
  : mNextMethod (obj.attr ("__iter__")().attr ("next"))
  , mCurrent()
{
}

////////////////////////////////////////////////////////////////////////////
// Get our next item (if any)
///////////////////////////////////////////////////////////////////////////

bool boost::python::indexing::python_iter_iterator::next ()
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

boost::python::object
boost::python::indexing::python_iter_iterator::current () const
{
  return mCurrent;
}
