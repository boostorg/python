// Copyright David Abrahams 2001. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#include <boost/python/converter/body.hpp>

namespace boost { namespace python { namespace converter { 

// default implementation is a no-op. Most handles will not hold any
// data that needs to be managed. Unwrap objects which convert
// by-value are an exception. Fortunately, the concrete body subclass
// has that knowledge.
void body::destroy_handle(handle*) const
{
}

}}} // namespace boost::python::converter
