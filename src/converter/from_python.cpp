// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.

#include <boost/python/converter/from_python.hpp>
#include <boost/python/converter/registry.hpp>

namespace boost { namespace python { namespace converter { 

from_python_converter_base::from_python_converter_base(
    type_id_t type
    , from_python_check checker
    )
    : body(type)
    , m_convertible(checker)

{
    // Insert this in the converter chain.
    from_python_converter_base*& head = registry::from_python_chain(type);
    m_next = head;
    head = this;
}

}}} // namespace boost::python::converter
