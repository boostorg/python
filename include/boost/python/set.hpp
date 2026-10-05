// Copyright Fady Essam 2019. Distributed under the Boost
// Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#ifndef SET_BOOST_PYTHON_HH
#define SET_BOOST_PYTHON_HH

#include <boost/python/ssize_t.hpp>
#include <boost/python.hpp>


namespace boost {
  namespace python {

	namespace detail
	{
	  struct BOOST_PYTHON_DECL set_base : object
	  {
		void add(object_cref); // add object to set

		object pop(); // remove and return item at top

		void discard(object_cref x); // discard value from set

		long __len__(); // length of set

		void clear(); // empties set

	  protected:
		set_base();
		explicit set_base(object_cref sequence); // new set initialized from sequence's items

		BOOST_PYTHON_FORWARD_OBJECT_CONSTRUCTORS(set_base, object)
	  private:
		static detail::new_non_null_reference call(object const&);
	  };


	}






	class set : public detail::set_base
	{
	  typedef detail::set_base base;
	public:
	  set() {}

	  template <class T>
	  explicit set(T const& sequence)
		: base(object(sequence))
	  {
	  }

	  template <class T>
	  void add(T const& x)
	  {
		base::add(object(x));
	  }

	  object pop() { return base::pop(); }

	  template <class T>
	  void discard(T const& value)
	  {
		base::discard(object(value));
	  }

	  void clear() { base::clear(); }

	  long __len__() { return base::__len__(); }



	public:
	  BOOST_PYTHON_FORWARD_OBJECT_CONSTRUCTORS(set, base)
	};


	namespace converter
	{
	  template <>
	  struct object_manager_traits<set>
		: pytype_object_manager_traits<&PySet_Type, set>
	  {
	  };
	}


  }

}





#endif // !SET_BOOST_PYTHON_HH
