// Copyright David Abrahams 2001. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef MAKE_FUNCTION_DWA20011221_HPP
# define MAKE_FUNCTION_DWA20011221_HPP

# include <boost/python/object/function.hpp>
# include <boost/python/object/make_holder.hpp>
# include <boost/python/detail/caller.hpp>
# include <boost/python/detail/arg_tuple_size.hpp>
# include <boost/mpl/size.hpp>
# include <boost/function.hpp>
# include <boost/bind.hpp>

namespace boost { namespace python {

template <class F>
objects::function* make_function(F f)
{
    return new objects::function(
        objects::py_function(
            ::boost::bind<PyObject*>(detail::caller(), f, _1, _2))
        , detail::arg_tuple_size<F>::value);
}

template <class T, class ArgList, class Generator>
objects::function* make_constructor(T* = 0, ArgList* = 0, Generator* = 0)
{
    enum { nargs = mpl::size<ArgList>::value };
    return new objects::function(
        objects::py_function(
            ::boost::bind<PyObject*>(detail::caller(),
                 objects::make_holder<nargs>
                            ::template apply<T,Generator,ArgList>::execute
                 , _1, _2))
        , nargs + 1);
}

}} // namespace boost::python

#endif // MAKE_FUNCTION_DWA20011221_HPP
