// -*- mode:c++ -*-
//
// Header file python_iterator.hpp
//
// Handy Python iterable iterators
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

#ifndef BOOST_PYTHON_INDEXING_PYTHON_ITERATOR_HPP
#define BOOST_PYTHON_INDEXING_PYTHON_ITERATOR_HPP

#include <boost/python/object.hpp>

namespace boost { namespace python { namespace indexing {
  struct BOOST_PYTHON_DECL python_iterator
  {
    python_iterator (boost::python::object);
    // Sets a python type exception and calls throw_error_already_set if
    // the passed object is not iterable via PyObject_GetIter

    bool next ();
    // Get the next item from the iterator, returning true for success

    boost::python::object current() const;
    // Callable only after a successful next()

  private:
    ::boost::python::object m_iter_obj;
    ::boost::python::object m_next_method;
    ::boost::python::object m_current;
  };
} } }

#endif // BOOST_PYTHON_INDEXING_PYTHON_ITERATOR_HPP
