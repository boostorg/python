// -*- mode:c++ -*-
//
// Header file IntWrapper.hpp
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

#ifndef IntWrapper_rmg_20030910_included
#define IntWrapper_rmg_20030910_included

#include <iosfwd>
#include <boost/shared_ptr.hpp>

struct IntWrapper {
  static bool gIntWrapperTrace;
  static unsigned ourObjectCounter;
  int mObjNumber;
  int mI;

  IntWrapper ();
  explicit IntWrapper (int i);
  IntWrapper (IntWrapper const &other);
  IntWrapper &operator= (IntWrapper const &other);
  ~IntWrapper ();

  void increment();

  operator boost::shared_ptr<IntWrapper> () const;

  static void setTrace (int onoff);
};

bool operator== (IntWrapper const &lhs, IntWrapper const &rhs);
bool operator< (IntWrapper const &lhs, IntWrapper const &rhs);
std::ostream &operator<< (std::ostream &strm, IntWrapper const &iw);

#endif // IntWrapper_rmg_20030910_included
