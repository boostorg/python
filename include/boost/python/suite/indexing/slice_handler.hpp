// -*- mode:c++ -*-
//
// Header file slice_handler.hpp
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
// 2003/ 9/ 9	rmg	File creation
//
// $Id$
//

#ifndef slice_handler_rmg_20030909_included
#define slice_handler_rmg_20030909_included

#include <boost/python/object.hpp>
#include <boost/python/list.hpp>
#include <boost/python/converter/pytype_object_mgr_traits.hpp>
#include <algorithm>

// #include <boost/python/extract.hpp>

namespace indexing
{
  class slice : public boost::python::object
  {
    int mStart;
    int mStep;
    int mStop;
    bool mLengthSet;

    void validate () const {
      if (!mLengthSet)
	{
	  PyErr_SetString (PyExc_RuntimeError
			   , "slice access attempted before setLength called");
	  boost::python::throw_error_already_set();
	}
    }

  public:
    slice (boost::python::detail::borrowed_reference ref)
      : boost::python::object (ref)
      , mStart (0)
      , mStep (0)
      , mStop (0)
      , mLengthSet (false)
    {
      if (!PySlice_Check (this->ptr()))
	{
	  PyErr_SetString (PyExc_TypeError
			   , "slice constructor: passed a non-slice object");

	  boost::python::throw_error_already_set();
	}

      //
      // *** WARNING ***
      //
      // The slice object is useless until setLength is called
      //
    }

    void setLength (int sequenceLength)
    {
      PySlice_GetIndices ((PySliceObject *) this->ptr()
			  , sequenceLength
			  , &mStart
			  , &mStop
			  , &mStep);

      mStart = std::max (0, std::min (sequenceLength, mStart));
      mStop = std::max (0, std::min (sequenceLength, mStop));

      mLengthSet = true;
    }

    int start() const { validate(); return mStart; }
    int step() const  { validate(); return mStep; }
    int stop() const  { validate(); return mStop; }
  };

  template<class Algorithms, class Policy>
  struct slice_handler
  {
    typedef typename Algorithms::container container;
    typedef typename Algorithms::index_param index_param;
    typedef typename Algorithms::value_type value_type;
    typedef typename Algorithms::reference reference;

    static PyObject *get_slice (container &c, slice sl)
    {
      boost::python::list temp;

      sl.setLength (Algorithms::size(c));

      int direction = (sl.step() > 0) ? 1 : ((sl.step() == 0) ? 0 : -1);

      for (int index = sl.start()
	     ; ((sl.stop() - index) * direction) > 0
	     ; index += sl.step())
	{
	  // *FIXME* handle return policies for each element?
	  temp.append (Algorithms::get (c, index));
	}

      PyObject *result = temp.ptr();
      Py_INCREF (result);  // ????
      return result;
    }

    static boost::python::object make_getitem (Policy const &policy)
    {
      return boost::python::make_function (get_slice, policy);
    }
  };
}

namespace boost { namespace python { namespace converter {
  // Specialized converter to handle PySlice_Type objects
  template<>
  struct object_manager_traits<indexing::slice>
    : pytype_object_manager_traits<&PySlice_Type, ::indexing::slice>
  {
  };
}}}

#endif // slice_handler_rmg_20030909_included
