// -*- mode:c++ -*-
//
// Header file algorithms.hpp
//
// Uniform interface layer for all containers.
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
// 2003/ 9/11	rmg	File creation from suite_utils.hpp
//
// $Id$
//

#ifndef algorithms_rmg_20030823_included
#define algorithms_rmg_20030823_included

#include "suite_utils.hpp"
#include <boost/type_traits.hpp>
#include <boost/call_traits.hpp>
#include <algorithm>
#include <stdexcept>
#include <limits>
#include <string>

namespace indexing {
  template<typename ContainerTraits>
  struct default_algorithms
  {
    typedef ContainerTraits container_traits;

    typedef typename ContainerTraits::container container;
    typedef typename ContainerTraits::iterator iterator;
    typedef typename ContainerTraits::reference reference;
    typedef typename ContainerTraits::key_type key_type;
    typedef typename ContainerTraits::size_type size_type;
    typedef typename ContainerTraits::value_type value_type;
    typedef long index_type; // Ignore container traits (need signed repr.)

    typedef typename boost::call_traits<value_type>::param_type value_param;
    typedef typename boost::call_traits<key_type>::param_type key_param;
    typedef typename boost::call_traits<index_type>::param_type index_param;

    static size_type size       (container &);
    static iterator  find       (container &, key_param);
    static size_type count      (container &, key_param);
    static void      reverse    (container &);
    static reference get        (container &, index_param);
    static void      assign     (container &, index_param, value_param);
    static void      insert     (container &, index_param, value_param);
    static void      erase_one  (container &, index_param);
    static void      erase_range(container &, index_param, index_param);
    static void      push_back  (container &, value_param);
    static void      sort       (container &);
    //    static void      sort       (container &, PyObject *);

    static iterator  begin      (container &c) { return c.begin(); }
    static iterator  end        (container &c) { return c.end(); }

    template<typename PythonClass, typename Policy>
    static void visitor_helper (PythonClass &, Policy const &);

  private:
    static size_type bounds_check (container &, index_param, char const *msg
				   , bool one_past = false);
    // Throws std::out_of_range if necessary. If one_past is set, then
    // indexes up to container.size() *inclusive* are allowed. Otherwise
    // returns a normalized index.
  };

  /////////////////////////////////////////////////////////////////////////
  // Special cases for std::list
  /////////////////////////////////////////////////////////////////////////

  template<typename ContainerTraits>
  struct list_algorithms : public default_algorithms<ContainerTraits>
  {
  private:
    typedef default_algorithms<ContainerTraits> Parent;

  public:
    typedef typename Parent::container container;

    // Use member functions for the following (hiding base class versions)
    static void      reverse    (container &);
    static void      sort       (container &);
    //    static void      sort       (container &, PyObject *);
  };

  /////////////////////////////////////////////////////////////////////////
  // Special cases for associative containers
  /////////////////////////////////////////////////////////////////////////

  template<typename ContainerTraits>
  struct assoc_algorithms : public default_algorithms<ContainerTraits>
  {
  private:
    typedef default_algorithms<ContainerTraits> Parent;

  public:
    typedef typename Parent::iterator iterator;
    typedef typename Parent::size_type size_type;
    typedef typename Parent::container container;
    typedef typename Parent::reference reference;
    typedef typename Parent::key_param key_param;
    typedef typename Parent::value_param value_param;

    // Use the trait's index type information to support non-integer indexes
    typedef typename ContainerTraits::index_type index_type;
    typedef typename boost::call_traits<index_type>::param_type index_param;

    static reference get        (container &, index_param);
    static void      assign     (container &, index_param, value_param);

    // Use member functions for the following (hiding base class versions)
    static void      erase_one (container &, key_param);
    static iterator  find  (container &, key_param);
    static size_type count (container &, key_param);
  };
}

/////////////////////////////////////////////////////////////////////////
// Get the size of a container
/////////////////////////////////////////////////////////////////////////

template<typename ContainerTraits>
typename indexing::default_algorithms<ContainerTraits>::size_type
indexing::default_algorithms<ContainerTraits>::size (container &c)
{
  return c.size();
}

/////////////////////////////////////////////////////////////////////////
// Range check an index and throw out_of_range if necessary
/////////////////////////////////////////////////////////////////////////

template<typename ContainerTraits>
typename indexing::default_algorithms<ContainerTraits>::size_type
indexing::default_algorithms<ContainerTraits>::bounds_check (container &c
							     , index_param ix
							     , char const *msg
							     , bool one_past)
{
  size_type bound = size(c) + (one_past ? 1 : 0);
  size_type result;

  if (ix < 0)
    {
      if (size_type(-ix) > bound)
	{
	  throw std::out_of_range (msg);
	}

      result = bound + ix;
    }

  else
    {
      result = ix;
    }

  if (result >= bound)
    {
      throw std::out_of_range (msg);
    }

  return result;
}

/////////////////////////////////////////////////////////////////////////
// Find an element in a container (std algorithm version)
/////////////////////////////////////////////////////////////////////////

template<typename ContainerTraits>
typename indexing::default_algorithms<ContainerTraits>::iterator
indexing::default_algorithms<ContainerTraits>::find (container &c
						     , key_param key)
{
  return std::find (begin(c), end(c), key);
}

/////////////////////////////////////////////////////////////////////////
// Count occurances of an element in a container (std algorithm version)
/////////////////////////////////////////////////////////////////////////

template<typename ContainerTraits>
typename indexing::default_algorithms<ContainerTraits>::size_type
indexing::default_algorithms<ContainerTraits>::count (container &c
						      , key_param key)
{
  return std::count (begin(c), end(c), key);
}

/////////////////////////////////////////////////////////////////////////
// Index into a container (generic version)
/////////////////////////////////////////////////////////////////////////

template<typename ContainerTraits>
typename indexing::default_algorithms<ContainerTraits>::reference
indexing::default_algorithms<ContainerTraits>::get (container &c
						    , index_param ix)
{
  return c[bounds_check (c, ix, "get")];
}

/////////////////////////////////////////////////////////////////////////
// Assign a value at a particular index (generic version)
/////////////////////////////////////////////////////////////////////////

template<typename ContainerTraits>
void
indexing::default_algorithms<ContainerTraits>::assign (container &c
						       , index_param ix
						       , value_param val)
{
  c[bounds_check (c, ix, "assign")] = val;
}

/////////////////////////////////////////////////////////////////////////
// Insert at end of a container (generic version)
/////////////////////////////////////////////////////////////////////////

template<typename ContainerTraits>
void
indexing::default_algorithms<ContainerTraits>::push_back (container &c
							  , value_param v)
{
  c.push_back (v);
}

/////////////////////////////////////////////////////////////////////////
// Insert at an index in the container (generic version)
/////////////////////////////////////////////////////////////////////////

template<typename ContainerTraits>
void
indexing::default_algorithms<ContainerTraits>::insert (container &c
						       , index_param i
						       , value_param v)
{
  // Index may range up to c.size() inclusive to allow inserting at end
  c.insert (c.begin() + bounds_check (c, i, "insert", true), v);
}

/////////////////////////////////////////////////////////////////////////
// Erase between given indexes in the container (generic version)
/////////////////////////////////////////////////////////////////////////

template<typename ContainerTraits>
void
indexing::default_algorithms<ContainerTraits>::erase_range (container &c
							    , index_param from
							    , index_param to)
{
  // End index is one-past-the-end, so may range up to c.size() inclusive

  c.erase (c.begin() + bounds_check (c, from, "erase_range (from)")
	   , c.begin() + bounds_check (c, to, "erase_range (to)", true));
}

/////////////////////////////////////////////////////////////////////////
// Erase one element at the given index in the container (generic version)
/////////////////////////////////////////////////////////////////////////

template<typename ContainerTraits>
void
indexing::default_algorithms<ContainerTraits>::erase_one (container &c
							  , index_param ix)
{
  c.erase (c.begin() + bounds_check (c, ix, "erase_one"));
}

/////////////////////////////////////////////////////////////////////////
// Reverse the contents of a container (std algorithm version)
/////////////////////////////////////////////////////////////////////////

template<typename ContainerTraits>
void indexing::default_algorithms<ContainerTraits>::reverse (container &c)
{
  std::reverse (begin(c), end(c));
}

/////////////////////////////////////////////////////////////////////////
// Sort the contents of a container (std algorithm version)
/////////////////////////////////////////////////////////////////////////

template<typename ContainerTraits>
void indexing::default_algorithms<ContainerTraits>::sort (container &c)
{
  std::sort (begin(c), end(c));
}

/////////////////////////////////////////////////////////////////////////
// Visitor helper function (default version)
/////////////////////////////////////////////////////////////////////////

template<typename ContainerTraits>
template<typename PythonClass, typename Policy>
void
indexing::default_algorithms<ContainerTraits>
::visitor_helper (PythonClass &pyClass, Policy const &policy)
{
  container_traits::visitor_helper (pyClass, policy);
}

/////////////////////////////////////////////////////////////////////////
// Reverse the contents of a list (member function version)
/////////////////////////////////////////////////////////////////////////

template<typename ContainerTraits>
void indexing::list_algorithms<ContainerTraits>::reverse (container &c)
{
  c.reverse();
}

/////////////////////////////////////////////////////////////////////////
// Sort the contents of a container (std algorithm version)
/////////////////////////////////////////////////////////////////////////

template<typename ContainerTraits>
void indexing::list_algorithms<ContainerTraits>::sort (container &c)
{
  c.sort();
}

/////////////////////////////////////////////////////////////////////////
// Index into a container (associative version)
/////////////////////////////////////////////////////////////////////////

template<typename ContainerTraits>
typename indexing::assoc_algorithms<ContainerTraits>::reference
indexing::assoc_algorithms<ContainerTraits>::get (container &c, index_param ix)
{
  iterator iter = find (c, ix);

  if (iter == end(c))
    {
      // ? Is domain_error appropriate here?
      throw std::domain_error
	(std::string ("associative container get: key not found"));
    }

  else
    {
      return iter->second;
    }
}

/////////////////////////////////////////////////////////////////////////
// Erase elements with the given key (associative version)
/////////////////////////////////////////////////////////////////////////

template<typename ContainerTraits>
void
indexing::assoc_algorithms<ContainerTraits>::erase_one (container &c
							, key_param key)
{
  if (c.erase (key) == 0)
    {
      // ? Is domain_error appropriate here?
      throw std::domain_error
	(std::string ("associative container erase: key not found"));
    }
}

/////////////////////////////////////////////////////////////////////////
// Assign a value at a particular index (associative version)
/////////////////////////////////////////////////////////////////////////

template<typename ContainerTraits>
void
indexing::assoc_algorithms<ContainerTraits>::assign (container &c
						     , index_param ix
						     , value_param val)
{
  c[ix] = val;
}

/////////////////////////////////////////////////////////////////////////
// Find an element in an associative container
/////////////////////////////////////////////////////////////////////////

template<typename ContainerTraits>
typename indexing::assoc_algorithms<ContainerTraits>::iterator
indexing::assoc_algorithms<ContainerTraits>::find (container &c, key_param key)
{
  return c.find (key);
}

/////////////////////////////////////////////////////////////////////////
// Count occurances of an element in a container (associative version)
/////////////////////////////////////////////////////////////////////////

template<typename ContainerTraits>
typename indexing::assoc_algorithms<ContainerTraits>::size_type
indexing::assoc_algorithms<ContainerTraits>::count (container &c
						    , key_param key)
{
  return c.count (key);
}

#endif // algorithms_rmg_20030823_included
