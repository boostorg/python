// -*- mode:c++; switch-modules-target: "testcontprox.cpp" -*-
//
// Header file container_proxy.hpp
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

#ifndef container_proxy_rmg_20030826_included
#define container_proxy_rmg_20030826_included

#include "shared_proxy_impl.hpp"
#include <map>
#include <memory>
#include <cassert>
#include <iterator>
#include <boost/shared_ptr.hpp>

template<typename T> struct identity {
  static T &       get(T &       obj) { return obj; }
  static T const & get(T const & obj) { return obj; }
  // FIXME: should add copy, assign and destroy static members
};

template<typename T> struct deref {
  template<typename U> static T &       get (U &       ptr) { return *ptr; }
  template<typename U> static T const & get (U const & ptr) { return *ptr; }
  // FIXME: should add copy, assign and destroy static members
};

template<class Container
	 , typename HeldType = Container
	 , class Accessor = identity<Container> >
class container_proxy
{
  typedef container_proxy<Container, HeldType, Accessor> self_type;
  typedef typename Container::iterator raw_iterator;
  typedef std::iterator_traits<raw_iterator> raw_iterator_traits;

public:
  typedef typename Container::size_type size_type;
  typedef typename Container::difference_type difference_type;

  typedef shared_proxy_impl<self_type> shared_proxy;

  typedef typename Container::value_type raw_value_type;

  struct const_element_proxy;

  class element_proxy
  {
    friend class const_element_proxy;

    typedef shared_proxy proxy_type;
    typedef boost::shared_ptr<proxy_type> proxy_pointer;

    proxy_pointer mPtr;

  public:
    typedef typename proxy_type::value_type value_type;
    typedef typename proxy_type::reference reference;
    typedef typename proxy_type::pointer pointer;
    typedef typename proxy_type::iterator_category iterator_category;
    typedef typename proxy_type::difference_type difference_type;

    typedef value_type element_type;      // Alias for register_ptr_to_python

    element_proxy () : mPtr () { }
    explicit element_proxy (proxy_type *ptr) : mPtr (ptr) { }
    element_proxy (proxy_pointer const &ptr) : mPtr (ptr) { }

    explicit element_proxy (raw_value_type const &val)
      : mPtr (new proxy_type(val))
    {
      // Create new standalone value (i.e. detached)
    }

    reference operator* () const { return mPtr->operator*(); }
    pointer operator-> () const { return (*mPtr).operator->(); }
    pointer get () const { return operator->(); }  // Alias for pointer_holder

    // Implicit conversion to raw_value_type
    operator reference () const { return operator*(); }

    // These are necessary (at least) while the indexing suite insists
    // on converting the real container's value_type to the proxy
    // container's value_type when going from Python to C++. If the
    // suite would just pass the real container's value_type through,
    // our implicit conversion to value_type might suffice.
    bool operator== (value_type const &other) { return (**this) == other; }
    bool operator!= (value_type const &other) { return (**this) != other; }
    bool operator< (value_type const &other) { return (**this) < other; }
    bool operator> (value_type const &other) { return (**this) > other; }

    element_proxy &operator= (value_type const &copy)
    {
      proxy_type &proxy (*mPtr);
      container_proxy *container = proxy.owner();
      size_type index = proxy.index();

      if (container)
	{
	  container->replace (index, copy);
	  // Proxy was attached before, but is now detached. Make sure
	  // we now refer to the new element, instead of the detached
	  // copy of the old element
	  mPtr = container->at (index).mPtr;

	  // Note: in the special case that this we and the container
	  // proxy itself have the only references to the
	  // shared_proxy_impl, it is not necessary to first detach
	  // the proxy. Maybe best to implement when changing to
	  // intrusive_ptr instead of shared_ptr.
	}

      else
	{
	  *proxy = copy;
	}

      return *this;
    }

    element_proxy &operator= (element_proxy const &copy)
    {
      // This is the most dubious bit of the fudge. The indexing_suite's
      // implementation of __setitem__ tries to pass us our value_type,
      // which is actually of type element_proxy
      return (*this) = *copy;
    }

    size_t use_count() const { return mPtr.use_count(); } // For debugging
  };

  struct const_element_proxy
  {
    typedef shared_proxy proxy_type;
    typedef boost::shared_ptr<proxy_type> proxy_pointer;

    proxy_pointer mPtr;

  public:
    typedef typename proxy_type::value_type const value_type;
    typedef value_type &reference;
    typedef value_type *pointer;
    typedef typename proxy_type::iterator_category iterator_category;
    typedef typename proxy_type::difference_type difference_type;

    const_element_proxy () : mPtr () { }
    explicit const_element_proxy (proxy_type *ptr) : mPtr (ptr) { }
    const_element_proxy (proxy_pointer const &ptr) : mPtr (ptr) { }
    const_element_proxy (element_proxy const &copy) : mPtr (copy.mPtr) { }

    explicit const_element_proxy (raw_value_type const &val)
      : mPtr (new proxy_type(val))
    {
      // Create new standalone value (i.e. detached)
    }

    reference operator* () const { return mPtr->operator*(); }
    pointer operator-> () const { return mPtr->operator->(); }

    // Implicit conversion to raw_value_type
    operator reference () const { return operator*(); }

    size_t use_count() const { return mPtr.use_count(); } // For debugging
  };

  typedef element_proxy value_type;
  typedef element_proxy reference;  // Already has reference semantics
  typedef const_element_proxy const_value_type;

public:
  struct iterator
  {
    typedef typename raw_iterator_traits::difference_type difference_type;
    typedef std::random_access_iterator_tag iterator_category;
    typedef element_proxy value_type;
    typedef element_proxy *pointer;
    typedef element_proxy reference;  // Already has reference semantics

    iterator (container_proxy *p, size_type i) : ptr (p), index (i) { }

    iterator (container_proxy *p, raw_iterator iter)
      : ptr (p), index (iter - p->container().begin())
    {
    }

    reference operator*() const { return ptr->at(index); }
    pointer operator->() const { return &ptr->at(index); }
    reference operator[](size_type s) { return ptr->at (index + s); }

    iterator &operator++ () { ++index; return *this; }
    iterator &operator++ (int) { ++index; return *this; }
    iterator &operator+= (size_type s) { index += s; return *this; }

    iterator &operator-- () { --index; return *this; }
    iterator &operator-- (int) { --index; return *this; }
    iterator &operator-= (size_type s) { index -= s; return *this; }

    iterator operator+ (size_type s) const { return iterator(*this) += s; }
    iterator operator- (size_type s) const { return iterator(*this) -= s; }
    difference_type operator- (iterator i) const { return index - i.index; }

    bool operator== (iterator const &other) const {
      return (ptr == other.ptr) && (index == other.index);
    }

    bool operator!= (iterator const &other) const { return !(*this == other); }

    //  public:
    // Extensions to the normal iterator interface
    //    void replace (value_type const &copy) { ptr->replace (index, copy); }

  public:
    friend class container_proxy;
    container_proxy *ptr;
    size_type index;
  };

public:
  // Constructors
  container_proxy ();
  explicit container_proxy (HeldType const &h);
  template<typename Iter> container_proxy (Iter, Iter);

  container_proxy (container_proxy const &);
  container_proxy &operator= (container_proxy const &);
  ~container_proxy ();

  Container &      container();         // Should be private?
  Container const &container() const;   // Should be private?

  element_proxy       at (size_type index);
  const_element_proxy at (size_type index) const;

  element_proxy       operator[] (size_type index)       { return at(index); }
  const_element_proxy operator[] (size_type index) const { return at(index); }

  size_type size() const { return container().size(); }
  size_type capacity() const { return container().capacity(); }
  void reserve(size_type s) { container().reserve(s); }

public:
  iterator begin() { return iterator (this, 0); }
  iterator end() { return iterator (this, container().size()); }

  iterator erase (iterator);
  iterator erase (iterator, iterator);
  iterator insert (iterator, raw_value_type const &);
  template<typename Iter> void insert (iterator, Iter, Iter);

  void push_back (raw_value_type const &copy) { insert (end(), copy); }

  element_proxy pop_back () {
    element_proxy result = at (end() - 1);
    erase (end() - 1);
    return result;
  }

public:
  // Proxies for a given index must be detached before overwriting
  // that container element.
  void detach_proxy (size_type index);
  void detach_proxies (size_type from, size_type to);
  void detach_proxies (iterator from, iterator to);

public:
  // Convenient replacement of elements (automatic proxy detachment)
  void replace (size_type index, raw_value_type const &);
  template<typename Iter> void replace (size_type index, Iter, Iter);

private:
  // Overloads for insertions with/without useful std::distance
  template<typename Iter>
  void insert (iterator, Iter, Iter, std::forward_iterator_tag);

  template<typename Iter>
  void insert (iterator, Iter, Iter, std::input_iterator_tag);

private:
  typedef boost::shared_ptr<shared_proxy> pointer_impl;
  typedef std::map<size_type, pointer_impl> MapType;
  typedef typename MapType::iterator MapIterator;
  typedef typename MapType::value_type MapEntry;

private:
  static void detach_if_shared (MapEntry const &);
  void adjustIndexes (MapIterator, MapIterator, long);

private:
  HeldType myHeldType;
  MapType myMap;
};

template<class Container, typename HeldType, class Accessor>
container_proxy<Container, HeldType, Accessor>
::container_proxy ()
  : myHeldType ()
  , myMap ()
{
}

template<class Container, typename HeldType, class Accessor>
container_proxy<Container, HeldType, Accessor>
::container_proxy (HeldType const &heldType)
  : myHeldType (heldType)
  , myMap ()
{
}

template<class Container, typename HeldType, class Accessor>
template<typename Iter>
container_proxy<Container, HeldType, Accessor>
::container_proxy (Iter start, Iter finish)
  : myHeldType ()
  , myMap ()
{
  insert (begin(), start, finish);
}

template<class Container, typename HeldType, class Accessor>
container_proxy<Container, HeldType, Accessor>
::container_proxy (container_proxy const &copy)
  : myHeldType (copy.myHeldType)
  , myMap ()                      // Do *not* duplicate map
{
}

template<class Container, typename HeldType, class Accessor>
container_proxy<Container, HeldType, Accessor> &
container_proxy<Container, HeldType, Accessor>
::operator= (container_proxy const &copy)
{
  // All of our contained values are about to be dis-owned
  std::for_each (myMap.begin(), myMap.end(), detach_if_shared);
  myMap.clear();
  myHeldType = copy.myHeldType;
}

template<class Container, typename HeldType, class Accessor>
container_proxy<Container, HeldType, Accessor>
::~container_proxy ()
{
  // All of our contained values are about to be dis-owned
  std::for_each (myMap.begin(), myMap.end(), detach_if_shared);
}

template<class Container, typename HeldType, class Accessor>
Container &
container_proxy<Container, HeldType, Accessor>
::container ()
{
  return Accessor::get (myHeldType);
}

template<class Container, typename HeldType, class Accessor>
Container const &
container_proxy<Container, HeldType, Accessor>
::container () const
{
  return Accessor::get (myHeldType);
}

template<class Container, typename HeldType, class Accessor>
typename container_proxy<Container, HeldType, Accessor>::element_proxy
container_proxy<Container, HeldType, Accessor>
::at (size_type index)
{
  pointer_impl &entry = myMap[index];

  if (!entry.get())
    {
      entry.reset (new shared_proxy (this, index));
    }

  return element_proxy (entry);
}

template<class Container, typename HeldType, class Accessor>
typename container_proxy<Container, HeldType, Accessor>::const_element_proxy
container_proxy<Container, HeldType, Accessor>
::at (size_type index) const
{
  // const_cast allows insertion into map. Maybe this is wrong, and
  // there can be no const-version of at. Alternatively, maybe
  // the map member variable should be declared mutable.

  container_proxy *mutable_this = const_cast<container_proxy *>(this);

  return const_element_proxy (mutable_this->at (index));
}

template<class Container, typename HeldType, class Accessor>
void
container_proxy<Container, HeldType, Accessor>
::replace (size_type index, raw_value_type const &copy)
{
  detach_proxy (index);
  container().at(index) = copy;
}

template<class Container, typename HeldType, class Accessor>
template<typename Iter>
void
container_proxy<Container, HeldType, Accessor>
::replace (size_type index, Iter from, Iter to)
{
  while (from != to)
    {
      replace (index++, *from++);
    }
}

template<class Container, typename HeldType, class Accessor>
typename container_proxy<Container, HeldType, Accessor>::iterator
container_proxy<Container, HeldType, Accessor>
::erase (iterator iter)
{
  return erase (iter, iter + 1);
}

template<class Container, typename HeldType, class Accessor>
typename container_proxy<Container, HeldType, Accessor>::iterator
container_proxy<Container, HeldType, Accessor>
::erase (iterator from, iterator to)
{
  assert (from.ptr == this);
  assert (to.ptr == this);

  size_type deleting = to.index - from.index;
  MapIterator erase_begin = myMap.lower_bound (from.index);
  MapIterator erase_end = myMap.lower_bound (to.index);

  // Detach any proxies for the soon-to-be-erased elements
  std::for_each (erase_begin, erase_end, detach_if_shared);
  myMap.erase (erase_begin, erase_end);  // Note: erase_end remains valid

  // Adjust the indexes of any following proxies
  adjustIndexes (erase_end, myMap.end(), -deleting);

  // Erase the elements from the real container
  raw_iterator result = container().erase (container().begin() + from.index
					   , container().begin() + to.index);

  return iterator (this, result);
}

template<class Container, typename HeldType, class Accessor>
typename container_proxy<Container, HeldType, Accessor>::iterator
container_proxy<Container, HeldType, Accessor>
::insert (iterator iter, raw_value_type const &copy)
{
  assert (iter.ptr == this);

  // Adjust indexes from iter.index, since insert will go before iter
  adjustIndexes (myMap.lower_bound (iter.index), myMap.end(), 1);

  // Insert the element into the real container
  raw_iterator result = container().insert (container().begin() + iter.index
					    , copy);

  return iterator (this, result);
}

template<class Container, typename HeldType, class Accessor>
template<typename Iter>
void
container_proxy<Container, HeldType, Accessor>
::insert (iterator iter, Iter from, Iter to)
{
  // Forward insertion to the right overloaded version
  typedef typename std::iterator_traits<Iter>::iterator_category category;
  insert (iter, from, to, category());
}

template<class Container, typename HeldType, class Accessor>
template<typename Iter>
void
container_proxy<Container, HeldType, Accessor>
::insert (iterator iter, Iter from, Iter to, std::forward_iterator_tag)
{
  // insert overload for iterators where we can get distance()

  assert (iter.ptr == this);

  // Adjust indexes from iter.index, since insert will go before iter
  adjustIndexes (myMap.lower_bound (iter.index)
		 , myMap.end()
		 , std::distance (from, to));

  // Insert the element into the real container
  container().insert (container().begin() + iter.index, from, to);
}

template<class Container, typename HeldType, class Accessor>
template<typename Iter>
void
container_proxy<Container, HeldType, Accessor>
::insert (iterator iter, Iter from, Iter to, std::input_iterator_tag)
{
  // insert overload for iterators where we *can't* get distance()
  // so just insert elements one at a time
  while (from != to)
    {
      iter = insert (iter, *from++) + 1;
    }
}

template<class Container, typename HeldType, class Accessor>
void
container_proxy<Container, HeldType, Accessor>
::detach_if_shared (MapEntry const &ent)
{
  if (!ent.second.unique())
    {
      ent.second->detach();
    }
  // If the pointer isn't shared, don't bother causing a copy of the
  // container element, since the proxy is about to be deleted.
}

template<class Container, typename HeldType, class Accessor>
void
container_proxy<Container, HeldType, Accessor>
::detach_proxy (size_type index)
{
  MapIterator iter = myMap.find (index);

  if (iter != myMap.end())
    {
      detach_if_shared (*iter);
      myMap.erase (iter);
    }
}

template<class Container, typename HeldType, class Accessor>
void
container_proxy<Container, HeldType, Accessor>
::detach_proxies (size_type fromIndex, size_type toIndex)
{
  MapIterator from = myMap.lower_bound (fromIndex);
  MapIterator to = myMap.lower_bound (toIndex);
  std::for_each (from, to, detach_if_shared);
  myMap.erase (from, to);
}

template<class Container, typename HeldType, class Accessor>
void
container_proxy<Container, HeldType, Accessor>
::detach_proxies (iterator from, iterator to)
{
  assert (from.ptr == this);
  assert (to.ptr == this);
  detach_proxies (from.index, to.index);
}

template<class Container, typename HeldType, class Accessor>
void
container_proxy<Container, HeldType, Accessor>
::adjustIndexes (MapIterator from, MapIterator to, long offset)
{
  // Adjust indexes in the given range of proxies by the given offset.
  // The adjustment is done by erasing and re-inserting the entries
  // in the map.
  //
  // Could provide a hint iterator to the map insertion calls, except
  // in the case that "from" is right at the start of the container
  // (the hint must be the element *before* the one to be inserted,
  // and there is no element before the first one). This would mean
  // additional complexity to deal with the special case somehow.

  while (from != to)
    {
      MapIterator next (from);
      ++next;  // Find next element before invalidating the current one

      pointer_impl ptr (from->second);  // Copy the shared pointer
      myMap.erase (from);               // Remove the map copy of it

      if (!ptr.unique())
	{
	  // Reinsert only if there are other pointers "out there"
	  // referring to the shared proxy

	  ptr->myIndex += offset;
	  myMap.insert (typename MapType::value_type (ptr->myIndex, ptr));
	}

      from = next;
    }
}

#endif // container_proxy_rmg_20030826_included
