// -*- mode:c++ -*-
//
// Header file slice.hpp
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

#ifndef slice_rmg_20030910_included
#define slice_rmg_20030910_included

#include <boost/python/object.hpp>
#include <boost/python/converter/pytype_object_mgr_traits.hpp>

namespace boost { namespace python { namespace indexing {
  struct BOOST_PYTHON_DECL slice : public boost::python::object
  {
    //
    // *** WARNING ***
    //
    // A newly constructed slice object is useless until setLength is called
    //

    template<typename T> slice (T const &ref);

    void setLength (int sequenceLength);

    int start() const { validate(); return mStart; }
    int step() const  { validate(); return mStep; }
    int stop() const  { validate(); return mStop; }

    int size() const { validate(); return (mStop - mStart) / mStep; }

    bool inRange (int index);

  private:
    void validate () const; // throws unless setLength has been called

    int mStart;
    int mStep;
    int mStop;
    int mDirection;
  };
} } }

template<typename T>
boost::python::indexing::slice::slice (T const &ref)
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

  // This slice object is still useless until setLength is called
}

namespace boost { namespace python { namespace converter {
  // Specialized converter to handle PySlice_Type objects
  template<>
  struct object_manager_traits<boost::python::indexing::slice>
    : pytype_object_manager_traits<&PySlice_Type, ::boost::python::indexing::slice>
  {
  };
}}}

#endif // slice_rmg_20030910_included
