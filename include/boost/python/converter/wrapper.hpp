#error obsolete 
// Copyright David Abrahams 2001. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef WRAPPER_DWA2001127_HPP
# define WRAPPER_DWA2001127_HPP
# include <boost/python/converter/wrapper_base.hpp>
# include <boost/python/detail/wrap_python.hpp>
# include <boost/python/converter/type_id.hpp>
# include <boost/python/converter/wrap.hpp>
# include <boost/python/converter/source_holder.hpp>

namespace boost { namespace python { namespace converter { 

extern BOOST_PYTHON_DECL body& identity_wrapper;

template <class T>
struct wrapper : wrapper_base
{
 public:
    wrapper();
    
    PyObject* do_conversion(wrap_base const&, source_holder_base const&) const;
    
    // This does the actual conversion
    virtual PyObject* convert(T source) const = 0;
};

//
// implementations
//

template <class T>
wrapper<T>::wrapper()
    : wrapper_base(type_id<T>())
{
}


template <class T>
PyObject* wrapper<T>::do_conversion(wrap_base const& handle_, source_holder_base const& data_) const
{
    // Casting pointers instead of references suppresses a CWPro7 bug.
    wrap_more_<T> const& handle = *static_cast<wrap_more_<T> const*>(&handle_);
    source_holder<T> const& data = *static_cast<source_holder<T> const*>(&data_);
    if (handle.target() == 0)
    {
        handle.hold_result(convert(data.value));
    }
    return handle.target();
}

}}} // namespace boost::python::converter

#endif // WRAPPER_DWA2001127_HPP
