// -*- mode:c++; switch-modules-target: "container_proxy.hpp" -*-
//
// Module testcontprox.cpp
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
// 2003/ 8/26	rmg	File creation
//
// $Id$
//

#include "container_proxy.hpp"
#include <cstdio>
#include <vector>
#include <sstream>
#include <ostream>
#include <iostream>
#include <iterator>
#include <boost/iterator/indirect_iterator.hpp>

int unique_int() {
  static int counter = 400;

  return counter++;
}

int main ()
{
  int i = unique_int();
  typedef std::vector<int> Container;
  typedef container_proxy<Container, Container *, deref<Container> > ContainerProxy;

  Container raw_container;
  raw_container.push_back (i);

  ContainerProxy proxy (&raw_container);

  std::cout
    << proxy.container().front()   // Should be first element
    << " "
    << *proxy.at (0)       // Should be the same
    << "\n";

  ContainerProxy::value_type ptr (proxy.at (0));

  std::cout
    << *ptr                       // Should be first element
    << " "
    << ptr.use_count();            // Should be 2 (internal map has a ref)

  {
    ContainerProxy::const_value_type
      const_ptr (const_cast<ContainerProxy const &>(proxy).at(0));

    std::cout
      << ", "
      << *const_ptr                  // Should also be first element
      << " "
      << ptr.use_count();            // Should be 3 (two proxies and internal)
  }

  proxy.replace (0, unique_int());

  std::cout
    << ", "
    << *ptr                       // Should be *original* first element
    << " "
    << ptr.use_count()             // Should be 1 (detached)
    << ", "
    << proxy.at (0)                // Should be new first element
    << "\n";

  ptr = proxy.at (0);       // Proxy to new first element (attached)

  proxy.insert (proxy.begin(), unique_int());
  proxy.insert (proxy.begin(), unique_int());

  int array[4];
  for (int count = 0; count < 4; ++count) array[count] = unique_int();

  proxy.insert (proxy.begin(), array, array + 4);

  std::cout << "(" << *ptr << ", " << ptr.use_count() << ") ";
  std::copy (raw_container.begin(), raw_container.end()
	     , std::ostream_iterator<int>(std::cout, " "));
  std::cout << "\n";

  proxy.erase (proxy.begin());
  proxy.erase (proxy.begin(), proxy.begin() + 3);

  std::cout << "(" << *ptr << ", " << ptr.use_count() << ") ";
  std::copy (raw_container.begin(), raw_container.end()
	     , std::ostream_iterator<int>(std::cout, " "));
  std::cout << "\n";

  std::stringstream strm;
  strm << unique_int();
  strm << " " << unique_int();
  proxy.insert (proxy.begin()
		, std::istream_iterator<int> (strm)
		, std::istream_iterator<int> ());

  std::cout << "(" << *ptr << ", " << ptr.use_count() << ") ";
  std::copy (raw_container.begin(), raw_container.end()
	     , std::ostream_iterator<int>(std::cout, " "));
  std::cout << "\n";

  // Example set_item implementation - replacing the slice [1:4] with a
  // single element
  proxy.detach_proxy (1);
  proxy.at(1) = unique_int(); // Replace with new element
  proxy.erase (proxy.begin() + 2, proxy.begin() + 4);

  std::cout << "(" << *ptr << ", " << ptr.use_count() << ") ";


  // Try indirect_iterator just for fun, but this creates proxies for
  // every element in the container!

  using boost::make_indirect_iterator;

  std::copy (make_indirect_iterator(proxy.begin())
	     , make_indirect_iterator(proxy.end())
	     , std::ostream_iterator<int>(std::cout, " "));

  std::cout << "\n";

  // Try erasing the whole container, make sure proxy has value and is unique
  proxy.erase (proxy.begin(), proxy.end());
  std::cout
    << "(" << *ptr << ", " << ptr.use_count() << ") "
    << proxy.size() << "\n";
}
