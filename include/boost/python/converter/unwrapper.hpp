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
# include <boost/type.hpp>

namespace boost { namespace python { namespace converter { 

template <class T> struct unwrap_more_;

// Abstract base for all unwrappers of Ts
template <class T>
struct unwrapper : unwrapper_base
{
 public:
    unwrapper();

    virtual T convert(PyObject*, void* data, boost::type<T>) const = 0;
};

//
// implementations
//
template <class T>
unwrapper<T>::unwrapper()
    : unwrapper_base(type_id<T>())
{
}

}}} // namespace boost::python::converter

#endif // UNWRAPPER_DWA2001127_HPP
