// Copyright David Abrahams 2001. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef UNWRAPPER_DWA2001127_HPP
# define UNWRAPPER_DWA2001127_HPP

# include <boost/python/converter/unwrapper_base.hpp>
# include <boost/python/converter/unwrap.hpp>
# include <boost/python/converter/body.hpp>

namespace boost { namespace python { namespace converter { 

template <class T> struct unwrap_more_;

// Abstract base for all unwrappers of Ts
template <class T>
struct unwrapper : unwrapper_base
{
 public:
    unwrapper();

    T do_conversion(unwrap_more_<T> const* handle) const;
    
 private:
    virtual T convert(PyObject*, void*&) const = 0;
    
 private: // body required interface implementation
    void destroy_handle(handle*) const {}
};

//
// implementations
//
template <class T>
unwrapper<T>::unwrapper()
    : unwrapper_base(type_id<T>())
{
}

// We could think about making this virtual in an effort to get its
// code generated in the module where the unwrapper is defined, but
// it's not clear that it's a good tradeoff.
template <class T>
T unwrapper<T>::do_conversion(unwrap_more_<T> const* handle) const
{
    return convert(handle->source(), handle->m_storage);
}

}}} // namespace boost::python::converter

#endif // UNWRAPPER_DWA2001127_HPP
