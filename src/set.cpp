// Copyright Fady Essam 2019. Distributed under the Boost
// Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#include <boost/python/set.hpp>


namespace boost {
  namespace python {
	namespace detail {


	  detail::new_non_null_reference set_base::call(object_cref arg_)
	  {
		return (detail::new_non_null_reference)
		  (expect_non_null)(
			PySet_New(arg_.ptr())
			);
	  }

	  set_base::set_base()
		: object(detail::new_reference(PySet_New(NULL)))
	  {}

	  set_base::set_base(object_cref sequence)
		: object(set_base::call(sequence))
	  {}

	  void set_base::add(object_cref x)
	  {
		if (PyAnySet_CheckExact(this->ptr()))
		{
		  if (PySet_Add(this->ptr(), x.ptr()) == -1)
			throw_error_already_set();
		}
		else
		{
		  this->attr("add")(x);
		}
	  }


	  void set_base::discard(object_cref x)
	  {
		if (PyAnySet_CheckExact(this->ptr()))
		{
		  if (PySet_Discard(this->ptr(), x.ptr()) == -1)
			throw_error_already_set();
		}
		else
		{
		  this->attr("discrad")(x);
		}
	  }

	  object set_base::pop()
	  {
		return this->attr("pop")();
	  }

	  void set_base::clear()
	  {
		this->attr("clear")();
	  }

	  long set_base::__len__()
	  {
		return extract<long>(object(PySet_Size(this->ptr())))();
	  }


	  static struct register_set_pytype_ptr
	  {
		register_set_pytype_ptr()
		{
		  const_cast<converter::registration &>(
			converter::registry::lookup(boost::python::type_id<boost::python::set>())
			).m_class_object = &PySet_Type;
		}
	  }register_set_pytype_ptr_;

	}
  }
}
