#include "boost/python/slice.hpp"

// Copyright (c) 2004 Jonathan Brandmeyer
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


namespace boost { namespace python {

slice::slice()
	: object( boost::python::detail::new_reference( 
		PySlice_New( NULL, NULL, NULL)))
{
}

object
slice::start()
{
	return object( detail::borrowed_reference(
		((PySliceObject*)this->ptr())->start));
}

object
slice::stop()
{
	return object( detail::borrowed_reference(
		((PySliceObject*)this->ptr())->stop));
}

object
slice::step()
{
	return object( detail::borrowed_reference(
		((PySliceObject*)this->ptr())->step));
}

} } // !namespace boost::python
