// Copyright David Abrahams 2001. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef MAKE_FUNCTION_DWA20011221_HPP
# define MAKE_FUNCTION_DWA20011221_HPP

# include <boost/python/object/function_object.hpp>
# include <boost/python/args_fwd.hpp>
# include <boost/python/object/make_holder.hpp>
# include <boost/python/detail/caller.hpp>
# include <boost/python/detail/arg_tuple_size.hpp>
# include <boost/mpl/size.hpp>
# include <boost/bind.hpp>
# include <boost/python/default_call_policies.hpp>

namespace boost { namespace python {

template <class F>
object make_function(F f)
{
    return objects::function_object(
        ::boost::bind<PyObject*>(detail::caller(), f, _1, _2, default_call_policies())
        , detail::arg_tuple_size<F>::value);
}

template <class F, class Policies>
object make_function(F f, Policies const& policies)
{
    return objects::function_object(
        ::boost::bind<PyObject*>(detail::caller(), f, _1, _2, policies)
        , detail::arg_tuple_size<F>::value);
}

template <class F, class Policies, class Keywords>
object make_function(F f, Policies const& policies, Keywords const& keywords)
{
    enum { n_arguments = detail::arg_tuple_size<F>::value };
    typedef typename detail::error::more_keywords_than_function_arguments<
        Keywords::size, n_arguments
        >::too_many_keywords assertion;
    
   return objects::function_object(
        ::boost::bind<PyObject*>(detail::caller(), f, _1, _2, policies)
        , n_arguments
        , keywords.range());
}

template <class ArgList, class HolderGenerator>
object make_constructor(HolderGenerator* = 0, ArgList* = 0)
{
    enum { nargs = mpl::size<ArgList>::value };
    
    return objects::function_object(
            ::boost::bind<PyObject*>(
                detail::caller()
                , objects::make_holder<nargs>
                                ::template apply<HolderGenerator,ArgList>::execute
                 , _1, _2, default_call_policies())
        , nargs + 1);
}

template <class ArgList, class HolderGenerator, class Policies>
object make_constructor(Policies const& policies, HolderGenerator* = 0, ArgList* = 0)
{
    enum { nargs = mpl::size<ArgList>::value };
    
    return objects::function_object(
            ::boost::bind<PyObject*>(detail::caller(),
                 objects::make_holder<nargs>
                            ::template apply<HolderGenerator,ArgList>::execute
                 , _1, _2, policies)
        , nargs + 1);
}

}} // namespace boost::python

#endif // MAKE_FUNCTION_DWA20011221_HPP
