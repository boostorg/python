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

#ifndef BOOST_PYTHON_INDEXING_SLICE_HPP
#define BOOST_PYTHON_INDEXING_SLICE_HPP

#include <boost/python/object.hpp>
#include <boost/python/errors.hpp>
#include <boost/python/converter/pytype_object_mgr_traits.hpp>

namespace boost { namespace python { namespace indexing {
  struct BOOST_PYTHON_DECL slice : public boost::python::object
  {
    // This is just a thin wrapper around boost::python::object
    // so that it is possible to register a special converter for
    // PySlice_Type and overload C++ functions on slice

#if defined (BOOST_NO_MEMBER_TEMPLATES)
    // MSVC6 doesn't seem to be able to invoke the templated
    // constructor, so provide explicit overloads to match the
    // (currently) known boost::python::object constructors
    explicit slice (::boost::python::handle<> const&);
    explicit slice (::boost::python::detail::borrowed_reference);
    explicit slice (::boost::python::detail::new_reference);
    explicit slice (::boost::python::detail::new_non_null_reference);
#else
    // Better compilers make life easier
    template<typename T> inline slice (T const &ref);
#endif

    slice (slice const &); // Copy constructor
  };

  struct BOOST_PYTHON_DECL integer_slice
  {
    // This class provides a convenient interface to Python slice
    // objects that contain integer bound and stride values.

    typedef int index_type;

    integer_slice (slice const &, index_type length);
    // integer_slice must know how big the container is so it can
    // adjust for negative indexes, etc...

    index_type start() const { return m_start; }
    index_type step() const  { return m_step; }
    index_type stop() const  { return m_stop; }

    index_type size() const { return (m_stop - m_start) / m_step; }

    bool in_range (index_type index);

  private:
    slice m_slice;
    index_type m_start;
    index_type m_step;
    index_type m_stop;
    index_type m_direction;
  };
} } }

#if !defined (BOOST_NO_MEMBER_TEMPLATES)
template<typename T>
boost::python::indexing::slice::slice (T const &ref)
  : boost::python::object (ref)
{
  if (!PySlice_Check (this->ptr()))
    {
      PyErr_SetString (
          PyExc_TypeError, "slice constructor: passed a non-slice object");

      boost::python::throw_error_already_set();
    }
}
#endif

namespace boost { namespace python { namespace converter {
  // Specialized converter to handle PySlice_Type objects
  template<>
  struct object_manager_traits<boost::python::indexing::slice>
    : pytype_object_manager_traits <
         &PySlice_Type, ::boost::python::indexing::slice>
  {
  };
}}}

#endif // BOOST_PYTHON_INDEXING_SLICE_HPP
