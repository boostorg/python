// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef MAKE_KEYWORD_RANGE_FN_DWA2002927_HPP
# define MAKE_KEYWORD_RANGE_FN_DWA2002927_HPP

# include <boost/python/args_fwd.hpp>
# include <boost/python/detail/caller.hpp>
# include <boost/python/object/function_object.hpp>
# include <boost/python/object/make_holder.hpp>

namespace boost { namespace python { namespace detail { 

template <class F, class Policies>
object make_keyword_range_function(F f, Policies const& policies, keyword_range const& kw)
{
    enum { n_arguments = detail::arg_tuple_size<F>::value };
    return objects::function_object(
        ::boost::bind<PyObject*>(detail::caller(), f, _1, _2, policies)
        , n_arguments
        , kw);
}

template <class ArgList, class HolderGenerator, class Policies>
object make_keyword_range_constructor(
    Policies const& policies
    , detail::keyword_range const& kw
    , HolderGenerator* = 0
    , ArgList* = 0)
{
    enum { nargs = mpl::size<ArgList>::value };
    
    return objects::function_object(
            ::boost::bind<PyObject*>(detail::caller(),
                 objects::make_holder<nargs>
                            ::template apply<HolderGenerator,ArgList>::execute
                 , _1, _2, policies)
        , nargs + 1, kw);
}

}}} // namespace boost::python::detail

#endif // MAKE_KEYWORD_RANGE_FN_DWA2002927_HPP
