// Copyright David Abrahams 2001. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#include <boost/python/converter/unwrapper.hpp>
#include <boost/python/converter/registry.hpp>
#include <boost/type_traits/same_traits.hpp>

namespace boost { namespace python { namespace converter { 

unwrapper_base::unwrapper_base(type_id_t key)
    : body(key)
{
    registry::insert(*this);
}

unwrapper_base::~unwrapper_base()
{
    if (can_unregister())
        registry::remove(*this);
}

}}} // namespace boost::python::converter
