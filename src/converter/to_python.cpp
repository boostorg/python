// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.

#include <boost/python/converter/to_python.hpp>
#include <boost/python/converter/registry.hpp>

namespace boost { namespace python { namespace converter {

to_python_converter_base::to_python_converter_base(type_id_t key, to_python_function_base convert)
    : body(key)
    , m_convert(convert)
{
    registry::insert(*this);
}

to_python_converter_base::~to_python_converter_base()
{
    registry::remove(*this);
}

}}} // namespace boost::python::converter
