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
#include <boost/python/errors.hpp>
#include <boost/python/converter/pytype_object_mgr_traits.hpp>

namespace boost { namespace python { namespace indexing {
  struct BOOST_PYTHON_DECL slice : public boost::python::object
  {
    // This is just a thin wrapper around boost::python::object
    // so that it is possible to register a special converter for
    // PySlice_Type and overload C++ functions on slice

    slice (slice const &);

    template<typename T> inline slice (T const &ref);
  };

  struct BOOST_PYTHON_DECL integer_slice
  {
    // This class provides a convenient interface to Python slice
    // objects that contain integer bound and stride values.

    typedef int index_type;

    integer_slice (slice const &, index_type sequenceLength);
    // integer_slice must know how big the container is so it can
    // adjust for negative indexes, etc...

    index_type start() const { return mStart; }
    index_type step() const  { return mStep; }
    index_type stop() const  { return mStop; }

    index_type size() const { return (mStop - mStart) / mStep; }

    bool in_range (index_type index);

  private:
    slice mSlice;
    index_type mStart;
    index_type mStep;
    index_type mStop;
    index_type mDirection;
  };
} } }

template<typename T>
boost::python::indexing::slice::slice (T const &ref)
  : boost::python::object (ref)
{
  if (!PySlice_Check (this->ptr()))
    {
      PyErr_SetString (PyExc_TypeError
                       , "slice constructor: passed a non-slice object");

      boost::python::throw_error_already_set();
    }
}

namespace boost { namespace python { namespace converter {
  // Specialized converter to handle PySlice_Type objects
  template<>
  struct object_manager_traits<boost::python::indexing::slice>
    : pytype_object_manager_traits<&PySlice_Type
                                   , ::boost::python::indexing::slice>
  {
  };
}}}

#endif // slice_rmg_20030910_included
