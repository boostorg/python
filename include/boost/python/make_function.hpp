// Copyright David Abrahams 2001. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef MAKE_FUNCTION_DWA20011221_HPP
# define MAKE_FUNCTION_DWA20011221_HPP

# include <boost/mpl/size.hpp>
# include <boost/function.hpp>
# include <boost/bind.hpp>
# include <boost/python/object/function.hpp>
# include <boost/python/object/make_holder.hpp>
# include <boost/python/detail/caller.hpp>

namespace boost { namespace python {

template <class F>
PyObject* make_function(F f)
{
    return new object::function(
        object::py_function(
            bind<PyObject*>(detail::caller(), f, _1, _2)));
}

template <class T, class ArgList, class Generator>
PyObject* make_constructor(T* = 0, ArgList* = 0, Generator* = 0)
{
    enum { nargs = mpl::size<ArgList>::value };
    return new object::function(
        object::py_function(
            bind<PyObject*>(detail::caller(),
                 object::make_holder<nargs>
                            ::template apply<T,Generator,ArgList>::execute
                 , _1, _2)));
}

}} // namespace boost::python

#endif // MAKE_FUNCTION_DWA20011221_HPP
