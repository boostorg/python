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

// #include <boost/python/extract.hpp>

namespace indexing
{
  struct slice
  {
    long start;
    long step;   // Extended slices (currently unsupported)
    long stop;

    // Implement from_python using:
    //
    // PySlice_GetIndices
    // (PySliceObject *slice, int length, int *start, int *stop, int *step)
  };

  template<class Algorithms, class Policy>
  struct slice_handler
  {
    typedef typename Algorithms::container container;
    typedef typename Algorithms::index_param index_param;
    typedef typename Algorithms::value_type value_type;
    typedef typename Algorithms::reference reference;

    static PyObject *get_slice (container &c, slice const &sl)
    {
      boost::python::list temp;

      for (long index = sl.start; index < sl.stop; index += sl.step)
	{
	  // *FIXME* handle return policies for each element?
	  temp.append (Algorithms::get (c, index));
	}

      PyObject *result = list.ptr();
      Py_INCREF (result);
      return result;
    }

    static reference get_plain (container &c, index_param ix)
    {
      return Algorithms::get (c, ix);
    }

    static PyObject *get_automatic (PyObject *args
				    , PyObject *keywords
				    , boost::python::object plain_function
				    , boost::python::object slice_function)
    {
      // ?
      return 0;
    }

    static boost::python::object make_getitem (Policy const &policy)
    {
      // ? Is there an easy way to generate a function that will
      // call get_plain or get_slice depending on the arguments?
      //
      // Could be done by using get_automatic as a dispatcher, with
      // the last two parameters bound to wrappers for the two
      // implementations, but maybe there is a better way.

      return boost::python::make_function (get_plain, policy);
    }
  };
}

#endif // slice_handler_rmg_20030909_included
