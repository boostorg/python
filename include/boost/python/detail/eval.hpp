// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef EVAL_DWA2002124_HPP
# define EVAL_DWA2002124_HPP

# include <boost/mpl/apply.hpp>

namespace boost { namespace python { namespace detail { 

template <class T> struct undefined;
template <class UnaryMetaFunction, class T>
struct eval
{
# if defined(BOOST_MSVC) && BOOST_MSVC <= 1200
   // based on the (non-conforming) MSVC trick from MPL
    template<bool>
    struct unarymetafunction_vc : UnaryMetaFunction {};

    // illegal C++ which causes VC to admit that unarymetafunction_vc
    // can have a nested template:
    template<>
    struct unarymetafunction_vc<true>
    {
        template<class> struct apply;
    };

    typedef typename unarymetafunction_vc<
        ::boost::mpl::detail::msvc_never_true<UnaryMetaFunction>::value
    >::template apply<T>::type type;
# else
    typedef typename UnaryMetaFunction::template apply<T>::type type;
# endif
};

}}} // namespace boost::python::detail

#endif // EVAL_DWA2002124_HPP
