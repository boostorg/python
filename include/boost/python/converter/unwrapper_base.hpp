// Copyright David Abrahams 2001. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef UNWRAPPER_BASE_DWA20011215_HPP
# define UNWRAPPER_BASE_DWA20011215_HPP
# include <boost/python/converter/type_id.hpp>
# include <boost/python/converter/body.hpp>
# include <boost/python/detail/wrap_python.hpp>
# include <boost/python/export.hpp>

namespace boost { namespace python { namespace converter { 

struct BOOST_PYTHON_EXPORT unwrapper_base : body
{
 public:
    unwrapper_base(type_id_t); // registers
    ~unwrapper_base();         // unregisters
    virtual bool convertible(PyObject*) const = 0;
};

}}} // namespace boost::python::converter

#endif // UNWRAPPER_BASE_DWA20011215_HPP
