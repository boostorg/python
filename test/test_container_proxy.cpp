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

#include <boost/type_traits/broken_compiler_spec.hpp>
#include <boost/python/suite/indexing/container_proxy.hpp>
#include <boost/python/suite/indexing/workaround.hpp>
#include <boost/test/minimal.hpp>
#include <vector>
#include <deque>

#include "int_wrapper.hpp"

// Some messiness from not having a separate int_wrapper.cpp file
bool int_wrapper::our_trace_flag = true;
unsigned int_wrapper::our_object_counter = 0;

// For exception safety tests
struct throwing_int : public int_wrapper {
  static bool our_throw_flag;

  throwing_int () : int_wrapper () { }
  explicit throwing_int (int p) : int_wrapper (p) { }

  throwing_int (throwing_int const &other)
    : int_wrapper (other)
  {
    maybe_throw ();
  }

  throwing_int &operator= (throwing_int const &other)
  {
    int_wrapper::operator= (other);
    maybe_throw ();
    return *this;
  }

private:
  void maybe_throw () const
  {
    if (our_throw_flag)
      {
        if (our_trace_flag) {
          printf ("throwing a bool\n");
        }

        throw our_throw_flag;
      }
  }
};

bool throwing_int::our_throw_flag = false;

#if !BOOST_WORKAROUND (BOOST_MSVC, <= 1300)
// Works with element_proxy instances because of the reference
// conversion operator
static void increment (throwing_int &int_wrap, int val) {
  int_wrap.increment (val);
}
#else
// The implicit conversion provided by element_proxy doesn't work
// with MSVC[67]. Instead use the element_proxy operator->
template<typename T>
static void increment (T const &proxy, int val) {
  proxy->increment (val);
}
#endif

template<typename ProxyContainer>
void initial_tests (ProxyContainer &proxy_container)
{
  typedef typename ProxyContainer::reference reference;

  BOOST_CHECK (proxy_container.size() == 4);
  BOOST_CHECK (proxy_container.is_valid());

  proxy_container.insert (proxy_container.begin(), throwing_int (1));

  reference ref0 (proxy_container[0]);
  BOOST_CHECK (ref0.use_count() == 2);
  BOOST_CHECK (ref0 == throwing_int (1));

  proxy_container.insert (proxy_container.begin(), throwing_int (2));
  BOOST_CHECK (proxy_container.is_valid());

  BOOST_CHECK (ref0.use_count() == 2);
  BOOST_CHECK (ref0 == throwing_int (1));
  BOOST_CHECK (proxy_container[0] == throwing_int (2));

  proxy_container.swap_elements (0, 1);
  BOOST_CHECK (proxy_container.is_valid());

  BOOST_CHECK (ref0.use_count() == 2);
  BOOST_CHECK (ref0 == throwing_int (1));
  BOOST_CHECK (proxy_container[1] == throwing_int (2));

  proxy_container.swap_elements (0, 1);
  proxy_container.erase (proxy_container.begin());
  BOOST_CHECK (proxy_container.is_valid());

  BOOST_CHECK (ref0.use_count() == 2);
  ::increment (proxy_container[0], 2);
  BOOST_CHECK (ref0 == throwing_int (3));
  BOOST_CHECK (proxy_container[0] == throwing_int (3));

  proxy_container.erase (proxy_container.begin());
  BOOST_CHECK (proxy_container.is_valid());

  BOOST_CHECK (ref0.use_count() == 1);
  BOOST_CHECK (ref0 == throwing_int (3));
  BOOST_CHECK (proxy_container[0] == throwing_int ());

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
    ::increment (ref0, 5);
    ::increment (refn, 10);
    BOOST_CHECK (ref0 == throwing_int (5));
    BOOST_CHECK (refn == throwing_int (10));
    BOOST_CHECK (ref0.use_count() == 2);
    BOOST_CHECK (refn.use_count() == 2);

    // Invoke container_proxy destructor
    BOOST_PYTHON_INDEXING_RESET_AUTO_PTR (proxy_auto_p, 0);

    BOOST_CHECK (ref0.use_count() == 1);  // Detached
    BOOST_CHECK (refn.use_count() == 1);  // Detached
    BOOST_CHECK (ref0 == throwing_int (5));   // Value copied
    BOOST_CHECK (refn == throwing_int (10));  // Value copied
  }

  {
    // Check construction from iterators
    proxy_container_type proxy_container (
        raw_container.begin(), raw_container.end());

    BOOST_CHECK (proxy_container.is_valid());
    BOOST_CHECK (proxy_container.size() == raw_container.size());

    reference ref1 (proxy_container[1]);
    ::increment (ref1, 5);
    proxy_container_type temp;
    temp.push_back (throwing_int (10));
    reference ref2 (temp[0]);

    proxy_container = temp;  // Use assignment operator

    BOOST_CHECK (proxy_container.is_valid());
    BOOST_CHECK (temp.is_valid());
    BOOST_CHECK (ref2.use_count() == 2);
    BOOST_CHECK (ref2 == throwing_int (10));
    BOOST_CHECK (proxy_container[0] == throwing_int (10));
    BOOST_CHECK (ref1.use_count() == 1);
    BOOST_CHECK (ref1 == throwing_int (5));
  }

  {
    // Very basic check on exception safety of assignment operator. A
    // better test would cause an exception during the allocation of
    // proxies, maybe by using the Generator parameter to install a
    // container with a throwing allocator.

    proxy_container_type temp1;
    proxy_container_type temp2;
    temp1.push_back (throwing_int (10));
    temp2.push_back (throwing_int (20));

    throwing_int::our_throw_flag = true;

    try
      {
        temp1 = temp2; // Should throw
        BOOST_ERROR ("No exception thrown from assignment");
      }
    catch (bool)
      {
        // Container contents unchanged
        BOOST_CHECK (temp1.is_valid());
        BOOST_CHECK (temp2.is_valid());
        BOOST_CHECK (temp1[0] == throwing_int (10));
        BOOST_CHECK (temp2[0] == throwing_int (20));
      }

    throwing_int::our_throw_flag = false;
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
  ::increment (proxy_container[2], 5);
  BOOST_CHECK (ref2 == throwing_int (5));

  // Notify proxy of insert in raw container (*after* insert)
  raw_container.insert (raw_container.begin(), throwing_int(7));
  proxy_container.notify_insertion (0, 1);
  BOOST_CHECK (proxy_container.is_valid());
  BOOST_CHECK (ref2.use_count() == 2);   // Still attached
  ::increment (proxy_container[3], 5);
  BOOST_CHECK (ref2 == throwing_int (10));

  // Create reference to about-to-be-erased value
  reference ref0 (proxy_container[0]);
  BOOST_CHECK (ref0.use_count() == 2);
  BOOST_CHECK (ref0 == throwing_int (7));

  // Notify proxy of erase in raw container (*before* erase)
  proxy_container.prepare_erase (0, 2);
  raw_container.erase (raw_container.begin(), raw_container.begin() + 2);
  BOOST_CHECK (proxy_container.is_valid());
  BOOST_CHECK (ref0.use_count() == 1);  // Ref to erased value detached
  BOOST_CHECK (ref0 == throwing_int (7)); // Value copied before erase
  BOOST_CHECK (ref2.use_count() == 2);  // Other ref still attached
  ::increment (proxy_container[1], 5);
  BOOST_CHECK (ref2 == throwing_int (15));

  // Notify proxy of replacement in raw container (*before* assignment)
  proxy_container.detach_proxy (1);
  raw_container[1] = throwing_int (4);
  BOOST_CHECK (proxy_container.is_valid());
  BOOST_CHECK (proxy_container[1] == throwing_int (4)); // New value installed
  BOOST_CHECK (ref2.use_count() == 1);  // Ref is detached
  BOOST_CHECK (ref2 == throwing_int (15)); // Value copied before overwrite
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

// Make the indirect holders work with broken compilers
BOOST_TT_BROKEN_COMPILER_SPEC (std::vector<throwing_int>)
BOOST_TT_BROKEN_COMPILER_SPEC (std::deque<throwing_int>)

int test_main (int argc, char *argv[])
{
  namespace indexing = boost::python::indexing;

  throwing_int::setTrace (false);
  test_proxy<std::vector<throwing_int>, indexing::vector_generator>();
  test_proxy<std::deque<throwing_int>, ::deque_generator>();
  return 0;
}
