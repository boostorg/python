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

#include <string>
#include <sstream>
#include <algorithm>
#include <stdio.h>
#include <boost/type_traits/broken_compiler_spec.hpp>

struct int_wrapper {
  static bool our_trace_flag;
  static unsigned our_object_counter;
  int m_obj_number;
  int m_int;

  inline int_wrapper ();
  inline explicit int_wrapper (int i);
  inline int_wrapper (int_wrapper const &other);
  inline int_wrapper &operator= (int_wrapper const &other);
  inline ~int_wrapper ();

  inline void increment (int);
  inline std::string repr () const;

  inline static void setTrace (bool onoff);
};

BOOST_TT_BROKEN_COMPILER_SPEC (int_wrapper)

inline bool operator== (int_wrapper const &lhs, int_wrapper const &rhs);
inline bool operator!= (int_wrapper const &lhs, int_wrapper const &rhs);
inline bool operator< (int_wrapper const &lhs, int_wrapper const &rhs);
inline int compare (int_wrapper const &lhs, int_wrapper const &rhs);

//
// This is ugly. Put all of this stuff inline to avoid needing a
// separate object file for testing (don't know how to do this in
// Jam). Client module will have to define the following variables:
//
// bool int_wrapper::our_trace_flag = true;
// unsigned int_wrapper::our_object_counter = 0;
// 

int_wrapper::int_wrapper ()
  : m_obj_number (our_object_counter++),
    m_int (0)
{
  if (our_trace_flag)
    {
      printf ("int_wrapper %u () at %p\n", m_obj_number, this);
    }
}

int_wrapper::int_wrapper (int i)
  : m_obj_number (our_object_counter++),
    m_int (i)
{
  if (our_trace_flag)
    {
      printf ("int_wrapper %u (%d) at %p\n",
              m_obj_number,
              m_int,
              this);
    }
}

int_wrapper::int_wrapper (int_wrapper const &other)
  : m_obj_number (our_object_counter++),
    m_int (other.m_int)
{
  if (our_trace_flag)
    {
      printf ("int_wrapper %u (int_wrapper %u at %p) at %p\n",
              m_obj_number,
              other.m_obj_number,
              &other,
              this);
    }
}

int_wrapper &int_wrapper::operator= (int_wrapper const &other)
{
  if (our_trace_flag)
    {
      printf ("int_wrapper %u at %p = int_wrapper %u at %p\n",
              m_obj_number,
              this,
              other.m_obj_number,
              &other);
    }

  m_int = other.m_int;

  return *this;
}

int_wrapper::~int_wrapper ()
{
  if (our_trace_flag)
    {
      printf ("~int_wrapper %u at %p\n", m_obj_number, this);
    }

  m_int = 0xbaaaaaad;
}

void int_wrapper::increment(int change)
{
  if (our_trace_flag)
    {
      printf ("int_wrapper %u::increment(%d)\n", m_obj_number, change);
    }

  m_int += change;
}

std::string int_wrapper::repr () const
{
  std::stringstream temp;
  temp << m_int;
  return temp.str();
}

void int_wrapper::setTrace (bool onoff)
{
  our_trace_flag = onoff;
}

bool operator== (int_wrapper const &lhs, int_wrapper const &rhs)
{
  return lhs.m_int == rhs.m_int;
}

bool operator!= (int_wrapper const &lhs, int_wrapper const &rhs)
{
  return lhs.m_int != rhs.m_int;
}

bool operator< (int_wrapper const &lhs, int_wrapper const &rhs)
{
  return lhs.m_int < rhs.m_int;
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

namespace std {
  void swap (int_wrapper &first, int_wrapper &second) {
    if (int_wrapper::our_trace_flag)
      {
        printf ("std::swap (int_wrapper %u at %p, int_wrapper %u at %p)\n",
                first.m_obj_number,
                &first,
                second.m_obj_number,
                &second);
      }

    swap (first.m_int, second.m_int); // Don't swap object numbers
  }
}

#endif // int_wrapper_rmg_20030910_included
