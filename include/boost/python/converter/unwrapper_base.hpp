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
# include <boost/python/detail/config.hpp>

namespace boost { namespace python { namespace converter { 

struct BOOST_PYTHON_DECL unwrapper_base : body
{
 public:
    unwrapper_base(type_id_t); // registers
    ~unwrapper_base();         // unregisters

    // Must return non-null iff the conversion will be successful. Any
    // non-null pointer is acceptable, and will be passed on to the
    // convert() function, so useful data can be stored there.
    virtual void* can_convert(PyObject*) const = 0;
    
 protected:
    // this is an arbitrary non-null pointer you can use to indicate success
    static void* const non_null;
    
 private: // body required interface implementation
    void destroy_handle(handle*) const {}
};

}}} // namespace boost::python::converter

#endif // UNWRAPPER_BASE_DWA20011215_HPP
