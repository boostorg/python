// Copyright David Abrahams 2001. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.

#include <boost/python/converter/registry.hpp>
#include <boost/python/converter/wrapper.hpp>

namespace boost { namespace python { namespace converter { 

wrapper_base::wrapper_base(type_id_t type)
    : body(type)
{
    // static assertions for target<T>. These would go in a header,
    // but Metrowerks only respects BOOST_STATIC_ASSERT if it is in an
    // instantiated function
#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#else
#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION 
    registry::insert(*this);
}

wrapper_base::~wrapper_base()
{
    if (can_unregister())
        registry::remove(*this);
}

}}} // namespace boost::python::converter
