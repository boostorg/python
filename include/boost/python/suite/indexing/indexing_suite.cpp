// -*- mode:c++ -*-
//
// Module indexing_suite.cc
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
// 2003/ 8/22	rmg	File creation
//
// $Id$
//

#include "container_suite.hpp"
#include "iterator_suite.hpp"

#include <iterator>
#include <typeinfo>
#include <iostream>
#include <ostream>
#include <vector>
#include <deque>
#include <list>
#include <set>

#ifdef __GNUC__
#include <cxxabi.h>
   static int DEMANGLE_STATUS = 0;
#  define TYPENAME(t) \
      abi::__cxa_demangle(typeid(t).name(), 0, 0, &DEMANGLE_STATUS)
#else
#  define TYPENAME(t) \
      typeid(t).name()
#endif // __GXX__

template<typename Traits>
void test ()
{
  std::cout
    << TYPENAME(Traits)
    << "\n"

    << Traits::has_copyable_iter
    << " iterator_traits<T>::has_copyable_iter\n"

    << Traits::is_reversible
    << " iterator_traits<T>::is_reversible\n"

    << Traits::has_random_access
    << " iterator_traits<T>::has_random_access\n"

    << Traits::has_mutable_ref
    << " iterator_traits<T>::has_mutable_ref\n"

    << Traits::has_insert
    << " iterator_traits<T>::has_insert\n"

    << Traits::has_erase
    << " iterator_traits<T>::has_erase\n"

    << Traits::has_pop_back
    << " iterator_traits<T>::has_pop_back\n"

    << Traits::has_push_back
    << " iterator_traits<T>::has_push_back\n"

    << "=====================================\n"
    ;
}

int main ()
{
  using indexing::iterator_traits;
  using indexing::container_traits;
  using indexing::iterator_pair;

  test<container_traits <iterator_pair<std::istream_iterator<int> > > >();
  test<container_traits <iterator_pair<std::set<int>::const_iterator> > >();
  test<container_traits <iterator_pair<std::set<int>::iterator> > >();
  test<container_traits <iterator_pair<std::list<int>::const_iterator> > >();
  test<container_traits <iterator_pair<std::list<int>::iterator> > >();
  test<container_traits <iterator_pair<std::deque<int>::const_iterator> > >();
  test<container_traits <iterator_pair<std::deque<int>::iterator> > >();
  test<container_traits <iterator_pair<std::vector<int>::const_iterator> > >();
  test<container_traits <iterator_pair<std::vector<int>::iterator> > >();
  test<container_traits <iterator_pair<int const *> > >();
  test<container_traits <iterator_pair<int *> > >();

  test<container_traits <std::list<int> > >();
  test<container_traits <std::list<int> const> >();
  test<container_traits <std::deque<int> > >();
  test<container_traits <std::deque<int> const> >();
  test<container_traits <std::vector<int> > >();
  test<container_traits <std::vector<int> const> >();
  test<container_traits <std::set<int> > >();
  test<container_traits <std::set<int> const> >();

  typedef iterator_pair<int *> Range;
  int array[16] = {0, 0, 0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
  Range range (array, array + 16);

  container_traits<Range>::algorithms::reverse (range);

  std::cout
    << *container_traits<Range>::algorithms::at (range, 0) << " "
    << *container_traits<Range>::algorithms::at (range, 1) << " "
    << *container_traits<Range>::algorithms::at (range, 2) << " "
    << "\n";

  container_traits<Range>::algorithms::sort (range);

  std::cout
    << *container_traits<Range>::algorithms::at (range, 3) << " "
    << *container_traits<Range>::algorithms::at (range, 4) << " "
    << *container_traits<Range>::algorithms::at (range, 5) << " "
    << "\n";

  std::cout
    << container_traits<Range>::algorithms::size (range)
    << "\n"
    << container_traits<Range>::algorithms::find (range, 8) - array
    << "\n"
    << container_traits<Range>::algorithms::count (range, 0)
    << "\n"
    ;

  typedef std::list<int> List;
  List l (array, array + 16);

  container_traits<List>::algorithms::reverse (l);
  std::copy (l.begin(), l.end(), std::ostream_iterator<int>(std::cout, " "));
  std::cout << "\n";

  container_traits<List>::algorithms::sort (l);
  std::copy (l.begin(), l.end(), std::ostream_iterator<int>(std::cout, " "));
  std::cout << "\n";

  typedef std::set<int> Set;
  Set s (l.begin(), l.end());
  std::cout
    << container_traits<Set>::algorithms::count (s, 0)
    << "\n"
    << *container_traits<Set>::algorithms::find (s, 8)
    << "\n"
    ;

  typedef std::multiset<int> Multiset;
  Multiset multi_s (l.begin(), l.end());
  std::cout
    << container_traits<Multiset>::algorithms::count (multi_s, 0)
    << "\n"
    << *container_traits<Multiset>::algorithms::find (multi_s, 8)
    << "\n"
    ;
}
