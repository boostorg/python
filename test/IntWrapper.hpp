// -*- mode:c++ -*-
//
// Header file IntWrapper.hpp
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

#ifndef IntWrapper_rmg_20030910_included
#define IntWrapper_rmg_20030910_included

#include <ostream>
#include <boost/shared_ptr.hpp>
#include <stdio.h>

struct IntWrapper {
  static bool gIntWrapperTrace;
  static unsigned ourObjectCounter;
  int mObjNumber;
  int mI;

  inline IntWrapper ();
  inline explicit IntWrapper (int i);
  inline IntWrapper (IntWrapper const &other);
  inline IntWrapper &operator= (IntWrapper const &other);
  inline ~IntWrapper ();

  inline void increment();

  inline operator boost::shared_ptr<IntWrapper> () const;

  inline static void setTrace (bool onoff);
};

inline bool operator== (IntWrapper const &lhs, IntWrapper const &rhs);
inline bool operator!= (IntWrapper const &lhs, IntWrapper const &rhs);
inline bool operator< (IntWrapper const &lhs, IntWrapper const &rhs);
inline int compare (IntWrapper const &lhs, IntWrapper const &rhs);
inline std::ostream &operator<< (std::ostream &strm, IntWrapper const &iw);

//
// This is ugly. Put all of this stuff inline to avoid needing a
// separate object file for testing (don't know how to do this in
// Jam). Client module will have to define the following variables:
//
// bool IntWrapper::gIntWrapperTrace = true;
// unsigned IntWrapper::ourObjectCounter = 0;
// 

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

void IntWrapper::setTrace (bool onoff)
{
  gIntWrapperTrace = onoff;
}

bool operator== (IntWrapper const &lhs, IntWrapper const &rhs)
{
  return lhs.mI == rhs.mI;
}

bool operator!= (IntWrapper const &lhs, IntWrapper const &rhs)
{
  return lhs.mI != rhs.mI;
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

#endif // IntWrapper_rmg_20030910_included
