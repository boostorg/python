// Module test_vector_shared_ext.cpp
//
// Copyright (c) 2003 Raoul M. Gough
//
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy
// at http://www.boost.org/LICENSE_1_0.txt)
//
// History
// =======
// 2003/10/15   rmg     File creation from test_vector_ext.cpp
//
// $Id$
//

#include "int_wrapper.hpp"
#include <boost/shared_ptr.hpp>
#include <boost/type_traits/broken_compiler_spec.hpp>

typedef boost::shared_ptr<int_wrapper> int_wrapper_holder;

#if !BOOST_WORKAROUND (BOOST_MSVC, == 1200)
// Declare overloads for correct sort and find of int_wrappers via
// shared pointers
bool operator< (int_wrapper_holder const &, int_wrapper_holder const &);
bool operator== (int_wrapper_holder const &, int_wrapper_holder const &);
bool operator!= (int_wrapper_holder const &, int_wrapper_holder const &);
#endif

BOOST_TT_BROKEN_COMPILER_SPEC (boost::shared_ptr<int_wrapper>)

#include <boost/python/suite/indexing/container_suite.hpp>
#include <boost/python/suite/indexing/vector.hpp>
#include <vector>
#include <boost/python/class.hpp>
#include <boost/python/module.hpp>
#include <boost/python/def.hpp>
#include <boost/python/implicit.hpp>

// More messiness from not having a separate int_wrapper.cpp file
bool int_wrapper::our_trace_flag = true;
unsigned int_wrapper::our_object_counter = 0;

#if !BOOST_WORKAROUND (BOOST_MSVC, == 1200)
bool operator< (int_wrapper_holder const &lhs, int_wrapper_holder const &rhs)
{
  return (*lhs) < (*rhs);
}

bool operator== (int_wrapper_holder const &lhs, int_wrapper_holder const &rhs)
{
  return (*lhs) == (*rhs);
}

bool operator!= (int_wrapper_holder const &lhs, int_wrapper_holder const &rhs)
{
  return (*lhs) != (*rhs);
}
#endif

namespace indexing = boost::python::indexing;

typedef std::vector<int_wrapper_holder> Container1;

#if BOOST_WORKAROUND (BOOST_MSVC, == 1200)
// Unfortunately, the comparison operator overloads don't work under
// MSVC6, so we have to use a sledgehammer and replace the
// implementations of some of the search functions

struct bound_compare {
  int_wrapper_holder m_lhs;
  bound_compare (int_wrapper_holder const &lhs) : m_lhs (lhs) { }
  bool operator()(int_wrapper_holder const &rhs) { return (*m_lhs) == (*rhs); }
};

struct msvc6_vector_shared_algorithms
  : public indexing::default_algorithms <
        indexing::default_sequence_traits<Container1>
        , msvc6_vector_shared_algorithms
    >
{
  typedef indexing::default_algorithms <
      indexing::default_sequence_traits<Container1>
      , msvc6_vector_shared_algorithms
  > base_type;

  typedef msvc6_vector_shared_algorithms self_type;

  // key_param will be boost::shared_ptr<int_wrapper> or ref to same

  static bool less_than (key_param lhs, key_param rhs) {
    return (*lhs) < (*rhs);
  }

  static iterator find (container &c, key_param k) {
    return std::find_if (c.begin(), c.end(), bound_compare (k));
  }

  static size_type count (container &c, key_param k) {
    return std::count_if (c.begin(), c.end(), bound_compare (k));
  }

  static void sort (container &c) {
    std::sort (c.begin(), c.end(), self_type::less_than);
  }
};

#endif

BOOST_PYTHON_MODULE(test_vector_shared_ext)
{
  boost::python::implicitly_convertible <int, int_wrapper>();

  boost::python::def ("setTrace", &int_wrapper::setTrace);

  boost::python::class_<int_wrapper, int_wrapper_holder>
    ("int_wrapper", boost::python::init<int>())
    .def ("increment", &int_wrapper::increment)
    .def ("__repr__", &int_wrapper::repr)
    .def ("__cmp__", compare)
    ;

#if BOOST_WORKAROUND (BOOST_MSVC, == 1200)
  // MSVC6 version here
  typedef indexing::container_suite <
      Container1, msvc6_vector_shared_algorithms> Suite1;

#elif !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
  // Normal version here
  typedef indexing::container_suite<Container1> Suite1;

#else
  // For any other compilers that don't have partial specialization
  typedef indexing::vector_suite<Container1> Suite1;
#endif

  boost::python::class_<Container1>("Vector_shared")
    .def (Suite1())
    .def ("reserve", &Container1::reserve)
    ;
}
