// Module test_container_proxy.cpp
//
// Copyright (c) 2003 Raoul M. Gough
//
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy
// at http://www.boost.org/LICENSE_1_0.txt)
//
// Additional test cases for the container_proxy template, including
// direct access to the raw container.
//
// History
// =======
// 2003/10/23   rmg     File creation
//
// $Id$
//

#include <boost/python/suite/indexing/container_proxy.hpp>
#include <boost/test/minimal.hpp>
#include <vector>
#include <deque>

#include "int_wrapper.hpp"

// Some messiness from not having a separate int_wrapper.cpp file
bool int_wrapper::our_trace_flag = true;
unsigned int_wrapper::our_object_counter = 0;

template<typename ProxyContainer>
void initial_tests (ProxyContainer &proxy_container)
{
  typedef typename ProxyContainer::reference reference;

  BOOST_CHECK (proxy_container.size() == 4);
  BOOST_CHECK (proxy_container.is_valid());

  proxy_container.insert (proxy_container.begin(), int_wrapper (1));

  reference ref0 (proxy_container[0]);
  BOOST_CHECK (ref0.use_count() == 2);
  BOOST_CHECK (ref0 == int_wrapper (1));

  proxy_container.insert (proxy_container.begin(), int_wrapper (2));
  BOOST_CHECK (proxy_container.is_valid());

  BOOST_CHECK (ref0.use_count() == 2);
  BOOST_CHECK (ref0 == int_wrapper (1));
  BOOST_CHECK (proxy_container[0] == int_wrapper (2));

  proxy_container.swap_elements (0, 1);
  BOOST_CHECK (proxy_container.is_valid());

  BOOST_CHECK (ref0.use_count() == 2);
  BOOST_CHECK (ref0 == int_wrapper (1));
  BOOST_CHECK (proxy_container[1] == int_wrapper (2));

  proxy_container.swap_elements (0, 1);
  proxy_container.erase (proxy_container.begin());
  BOOST_CHECK (proxy_container.is_valid());

  BOOST_CHECK (ref0.use_count() == 2);
  ((int_wrapper &) proxy_container[0]).increment (2);
  BOOST_CHECK (ref0 == int_wrapper (3));
  BOOST_CHECK (proxy_container[0] == int_wrapper (3));

  proxy_container.erase (proxy_container.begin());
  BOOST_CHECK (proxy_container.is_valid());

  BOOST_CHECK (ref0.use_count() == 1);
  BOOST_CHECK (ref0 == int_wrapper (3));
  BOOST_CHECK (proxy_container[0] == int_wrapper ());

  BOOST_CHECK (proxy_container.size() == 4);
  BOOST_CHECK (proxy_container.is_valid());
}

template<typename RawContainer, typename Generator>
void test_direct_proxy ()
{
  namespace indexing = boost::python::indexing;

  typedef RawContainer raw_container_type;
  typedef indexing::identity<raw_container_type> holder_type;
  typedef indexing::container_proxy<raw_container_type, holder_type, Generator>
    proxy_container_type;

  typedef typename proxy_container_type::reference reference;

  raw_container_type raw_container (4);

  {
    std::auto_ptr<proxy_container_type> proxy_auto_p (
        new proxy_container_type (raw_container));

    initial_tests (*proxy_auto_p);

    reference ref0 ((*proxy_auto_p)[0]);
    reference refn ((*proxy_auto_p)[proxy_auto_p->size() - 1]);
    static_cast<int_wrapper &>(ref0).increment (5);
    static_cast<int_wrapper &>(refn).increment (10);
    BOOST_CHECK (ref0 == int_wrapper (5));
    BOOST_CHECK (refn == int_wrapper (10));
    BOOST_CHECK (ref0.use_count() == 2);
    BOOST_CHECK (refn.use_count() == 2);

    proxy_auto_p.reset();     // Invoke container_proxy destructor

    BOOST_CHECK (ref0.use_count() == 1);  // Detached
    BOOST_CHECK (refn.use_count() == 1);  // Detached
    BOOST_CHECK (ref0 == int_wrapper (5));   // Value copied
    BOOST_CHECK (refn == int_wrapper (10));  // Value copied
  }

  {
    // Check construction from iterators
    proxy_container_type proxy_container (
        raw_container.begin(), raw_container.end());

    BOOST_CHECK (proxy_container.is_valid());
    BOOST_CHECK (proxy_container.size() == raw_container.size());

    reference ref1 (proxy_container[1]);
    static_cast<int_wrapper &>(ref1).increment (5);

    proxy_container_type temp;
    temp.push_back (int_wrapper (10));
    reference ref2 (temp[0]);

    proxy_container = temp;  // Use assignment operator

    BOOST_CHECK (proxy_container.is_valid());
    BOOST_CHECK (temp.is_valid());
    BOOST_CHECK (ref2.use_count() == 2);
    BOOST_CHECK (ref2 == int_wrapper (10));
    BOOST_CHECK (proxy_container[0] == int_wrapper (10));
    BOOST_CHECK (ref1.use_count() == 1);
    BOOST_CHECK (ref1 == int_wrapper (5));
  }
}

template<typename RawContainer, typename Generator>
void test_indirect_proxy ()
{
  namespace indexing = boost::python::indexing;

  typedef RawContainer raw_container_type;
  typedef indexing::deref<raw_container_type *> holder_type;

  typedef indexing::container_proxy<raw_container_type, holder_type, Generator>
    proxy_container_type;

  typedef typename proxy_container_type::reference reference;

  raw_container_type raw_container (4);

  proxy_container_type proxy_container (&raw_container);

  initial_tests (proxy_container);

  // Test cases where the client code has direct mutable access to the
  // raw container.

  reference ref2 (proxy_container[2]);
  BOOST_CHECK (ref2.use_count() == 2);   // Still attached
  static_cast<int_wrapper &>(proxy_container[2]).increment (5);
  BOOST_CHECK (ref2 == int_wrapper (5));

  // Notify proxy of insert in raw container (*after* insert)
  raw_container.insert (raw_container.begin(), int_wrapper(7));
  proxy_container.notify_insertion (0, 1);
  BOOST_CHECK (proxy_container.is_valid());
  BOOST_CHECK (ref2.use_count() == 2);   // Still attached
  static_cast<int_wrapper &>(proxy_container[3]).increment (5);
  BOOST_CHECK (ref2 == int_wrapper (10));

  // Create reference to about-to-be-erased value
  reference ref0 (proxy_container[0]);
  BOOST_CHECK (ref0.use_count() == 2);
  BOOST_CHECK (ref0 == int_wrapper (7));

  // Notify proxy of erase in raw container (*before* erase)
  proxy_container.prepare_erase (0, 2);
  raw_container.erase (raw_container.begin(), raw_container.begin() + 2);
  BOOST_CHECK (proxy_container.is_valid());
  BOOST_CHECK (ref0.use_count() == 1);  // Ref to erased value detached
  BOOST_CHECK (ref0 == int_wrapper (7)); // Value copied before erase
  BOOST_CHECK (ref2.use_count() == 2);  // Other ref still attached
  static_cast<int_wrapper &>(proxy_container[1]).increment (5);
  BOOST_CHECK (ref2 == int_wrapper (15));

  // Notify proxy of replacement in raw container (*before* assignment)
  proxy_container.detach_proxy (1);
  raw_container[1] = int_wrapper (4);
  BOOST_CHECK (proxy_container.is_valid());
  BOOST_CHECK (proxy_container[1] == int_wrapper (4)); // New value installed
  BOOST_CHECK (ref2.use_count() == 1);  // Ref is detached
  BOOST_CHECK (ref2 == int_wrapper (15)); // Value copied before overwrite
}

template<typename RawContainer, typename Generator>
void test_proxy()
{
  test_direct_proxy<RawContainer, Generator> ();
  test_indirect_proxy<RawContainer, Generator> ();
}

struct deque_generator {
  // Generates deque type for any element type. This matches the
  // performance characteristics of the real container and the pointer
  // index container, e.g. for insert/erase at the beginning.
  template<typename Element> struct apply {
    typedef std::deque<Element> type;
  };
};

int test_main (int argc, char *argv[])
{
  namespace indexing = boost::python::indexing;

  int_wrapper::setTrace (false);
  test_proxy<std::vector<int_wrapper>, indexing::vector_generator>();
  test_proxy<std::deque<int_wrapper>, ::deque_generator>();
  return 0;
}
