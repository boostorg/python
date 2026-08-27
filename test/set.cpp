// Copyright Fady Essam 2019. Distributed under the Boost
// Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#include <boost/python/module.hpp>
#define BOOST_ENABLE_ASSERT_HANDLER
#include <boost/assert.hpp>

#include <boost/python/def.hpp>
#include <boost/python/class.hpp>
#include <boost/python/set.hpp>
#include <exception>
#include <string>
#include <iostream>

using namespace boost::python;

object new_set()
{
  return set();
}

object data_set()
{
  set tmp1;
  tmp1.add("value1");

  tmp1.add(2);
  return tmp1;
}

object set_from_sequence(object sequence)
{
  return set(sequence);
}


void work_with_set(set data1)
{
  if (!data1.contains("k1")) {
	std::cout << "data1 doesn't have k1" << std::endl;
  }
  data1.add("k1");

  if (data1.contains("k1")) {
	std::cout << "data1 now has k1" << std::endl;
  }

  data1.discard("k1");
  if (!data1.contains("k1")) {
	std::cout << "data1 doesn't have k1 again" << std::endl;
  }

}

void test_templates(object print)
{
  std::string key = "key";

  set tmp;
  tmp.add("a test string");
  print(tmp);
  tmp.add(13);
  print(tmp.contains(1.5));
  print(tmp.contains(13));
  print(tmp);

  BOOST_ASSERT(tmp.__len__() == 2);
}

BOOST_PYTHON_MODULE(set_ext)
{
  def("new_set", new_set);
  def("data_set", data_set);
  def("set_from_sequence", set_from_sequence);
  def("work_with_set", work_with_set);
  def("test_templates", test_templates);
}

#include "module_tail.cpp"
