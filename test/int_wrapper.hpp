// -*- mode:c++ -*-
//
// Header file int_wrapper.hpp
//
// Copyright (c) 2003 Raoul M. Gough
//
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy
// at http://www.boost.org/LICENSE_1_0.txt)
//
// History
// =======
// 2003/ 9/10   rmg     File creation as IntWrapper.hpp
// 2003/10/15   rmg     Renamed int_wrapper.hpp (Boost naming convention)
//
// $Id$
//

#ifndef int_wrapper_rmg_20030910_included
#define int_wrapper_rmg_20030910_included

#include <ostream>
#include <boost/shared_ptr.hpp>
#include <stdio.h>

struct int_wrapper {
  static bool our_trace_flag;
  static unsigned our_object_counter;
  int mObjNumber;
  int mI;

  inline int_wrapper ();
  inline explicit int_wrapper (int i);
  inline int_wrapper (int_wrapper const &other);
  inline int_wrapper &operator= (int_wrapper const &other);
  inline ~int_wrapper ();

  inline void increment();

  inline operator boost::shared_ptr<int_wrapper> () const;

  inline static void setTrace (bool onoff);
};

inline bool operator== (int_wrapper const &lhs, int_wrapper const &rhs);
inline bool operator!= (int_wrapper const &lhs, int_wrapper const &rhs);
inline bool operator< (int_wrapper const &lhs, int_wrapper const &rhs);
inline int compare (int_wrapper const &lhs, int_wrapper const &rhs);
inline std::ostream &operator<< (std::ostream &strm, int_wrapper const &iw);

//
// This is ugly. Put all of this stuff inline to avoid needing a
// separate object file for testing (don't know how to do this in
// Jam). Client module will have to define the following variables:
//
// bool int_wrapper::our_trace_flag = true;
// unsigned int_wrapper::our_object_counter = 0;
// 

int_wrapper::int_wrapper ()
  : mObjNumber (our_object_counter++)
  , mI (0)
{
  if (our_trace_flag)
    {
      printf ("int_wrapper %u ()\n", mObjNumber);
    }
}

int_wrapper::int_wrapper (int i)
  : mObjNumber (our_object_counter++)
  , mI (i)
{
  if (our_trace_flag)
    {
      printf ("int_wrapper %u (%d)\n"
              , mObjNumber
              , mI);
    }
}

int_wrapper::int_wrapper (int_wrapper const &other)
  : mObjNumber (our_object_counter++)
  , mI (other.mI)
{
  if (our_trace_flag)
    {
      printf ("int_wrapper %u (int_wrapper %u)\n"
              , mObjNumber
              , other.mObjNumber);
    }
}

int_wrapper &int_wrapper::operator= (int_wrapper const &other)
{
  if (our_trace_flag)
    {
      printf ("int_wrapper %u = int_wrapper %u\n"
              , mObjNumber
              , other.mObjNumber);
    }

  mI = other.mI;

  return *this;
}

int_wrapper::~int_wrapper ()
{
  if (our_trace_flag)
    {
      printf ("~int_wrapper %u\n", mObjNumber);
    }

  mI = 0xbaaaaaad;
}

void int_wrapper::increment()
{
  if (our_trace_flag)
    {
      printf ("int_wrapper %u::increment\n", mObjNumber);
    }

  ++mI;
}

int_wrapper::operator boost::shared_ptr<int_wrapper> () const
{
  if (our_trace_flag)
    {
      printf ("int_wrapper %u shared_ptr conversion\n", mObjNumber);
    }

  return boost::shared_ptr<int_wrapper> (new int_wrapper (*this));
}

void int_wrapper::setTrace (bool onoff)
{
  our_trace_flag = onoff;
}

bool operator== (int_wrapper const &lhs, int_wrapper const &rhs)
{
  return lhs.mI == rhs.mI;
}

bool operator!= (int_wrapper const &lhs, int_wrapper const &rhs)
{
  return lhs.mI != rhs.mI;
}

bool operator< (int_wrapper const &lhs, int_wrapper const &rhs)
{
  return lhs.mI < rhs.mI;
}

int compare (int_wrapper const &lhs, int_wrapper const &rhs)
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

std::ostream &operator<< (std::ostream &strm, int_wrapper const &iw)
{
  strm << iw.mI;
  return strm;
}

#endif // int_wrapper_rmg_20030910_included
