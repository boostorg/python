// -*- mode:c++ -*-
//
// Module IntWrapper.cpp
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

#include "IntWrapper.hpp"
#include <ostream>

bool IntWrapper::gIntWrapperTrace = true;

unsigned IntWrapper::ourObjectCounter = 0;

IntWrapper::IntWrapper ()
  : mObjNumber (ourObjectCounter++)
  , mI (0)
{
  if (gIntWrapperTrace)
    {
      printf ("IntWrapper %u ()\n", mObjNumber);
    }
}

IntWrapper::IntWrapper (int i)
  : mObjNumber (ourObjectCounter++)
  , mI (i)
{
  if (gIntWrapperTrace)
    {
      printf ("IntWrapper %u (%d)\n"
	      , mObjNumber
	      , mI);
    }
}

IntWrapper::IntWrapper (IntWrapper const &other)
  : mObjNumber (ourObjectCounter++)
  , mI (other.mI)
{
  if (gIntWrapperTrace)
    {
      printf ("IntWrapper %u (IntWrapper %u)\n"
	      , mObjNumber
	      , other.mObjNumber);
    }
}

IntWrapper &IntWrapper::operator= (IntWrapper const &other)
{
  if (gIntWrapperTrace)
    {
      printf ("IntWrapper %u = IntWrapper %u\n"
	      , mObjNumber
	      , other.mObjNumber);
    }

  mI = other.mI;

  return *this;
}

IntWrapper::~IntWrapper ()
{
  if (gIntWrapperTrace)
    {
      printf ("~IntWrapper %u\n", mObjNumber);
    }

  mI = 0xbaaaaaad;
}

void IntWrapper::increment()
{
  if (gIntWrapperTrace)
    {
      printf ("IntWrapper %u::increment\n", mObjNumber);
    }

  ++mI;
}

IntWrapper::operator boost::shared_ptr<IntWrapper> () const
{
  if (gIntWrapperTrace)
    {
      printf ("IntWrapper %u shared_ptr conversion\n", mObjNumber);
    }

  return boost::shared_ptr<IntWrapper> (new IntWrapper (*this));
}

void IntWrapper::setTrace (int onoff)
{
  gIntWrapperTrace = onoff;
}

bool operator== (IntWrapper const &lhs, IntWrapper const &rhs)
{
  return lhs.mI == rhs.mI;
}

bool operator< (IntWrapper const &lhs, IntWrapper const &rhs)
{
  return lhs.mI < rhs.mI;
}

int compare (IntWrapper const &lhs, IntWrapper const &rhs)
{
  if (lhs < rhs)
    {
      return -1;
    }

  else if (rhs < lhs)
    {
      return 1;
    }

  else
    {
      return 0;
    }
}

std::ostream &operator<< (std::ostream &strm, IntWrapper const &iw)
{
  strm << iw.mI;
  return strm;
}
