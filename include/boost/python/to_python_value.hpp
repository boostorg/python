// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef TO_PYTHON_VALUE_DWA200221_HPP
# define TO_PYTHON_VALUE_DWA200221_HPP

# include <boost/type_traits/transform_traits.hpp>
# include <boost/python/converter/type_id.hpp>
# include <boost/python/converter/registry.hpp>
# include <boost/python/converter/to_python_function.hpp>
# include <boost/python/converter/builtin_converters.hpp>

namespace boost { namespace python { 

template <class T>
struct to_python_value
{
    typedef typename add_reference<
        typename add_const<T>::type
    >::type argument_type;
    
    static bool convertible();
    PyObject* operator()(argument_type) const;
};


template <class T>
bool to_python_value<T>::convertible()
{
    // if this assert fires, our static variable hasn't been set up yet.
    return converter::to_python_function<argument_type>::value != 0;
}

template <class T>
PyObject* to_python_value<T>::operator()(argument_type x) const
{
    // This might be further optimized on platforms which dynamically
    // link without specific imports/exports
    return converter::to_python_function<argument_type>::value(&x);
}

}} // namespace boost::python

#endif // TO_PYTHON_VALUE_DWA200221_HPP
