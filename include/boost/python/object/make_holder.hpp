// Copyright David Abrahams 2001. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef MAKE_HOLDER_DWA20011215_HPP
# define MAKE_HOLDER_DWA20011215_HPP

# include <boost/mpl/at.hpp>
# include <boost/python/object/forward.hpp>
# include <boost/python/object/class.hpp>
# include <boost/python/detail/wrap_python.hpp>

namespace boost { namespace python { namespace object { 


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


template <int nargs> struct make_holder;

template <>
struct make_holder<0>
{
    template <class T, class Generator, class ArgList>
    struct apply
    {
        typedef typename eval<Generator,T>::type holder;
        static void execute(
            PyObject* p)
        {
            (new holder(p))->install(p);
        }
    };
};


template <>
struct make_holder<1>
{
    template <class T, class Generator, class ArgList>
    struct apply
    {
        typedef typename eval<Generator,T>::type holder;
        typedef typename mpl::at<0,ArgList>::type t0;
        typedef typename forward<t0>::type f0;
        
        static void execute(
            PyObject* p
            , t0 a0)
        {
            (new holder(p, f0(a0)))->install(p);
        }
    };
};

template <>
struct make_holder<2>
{
    template <class T, class Generator, class ArgList>
    struct apply
    {
        typedef typename eval<Generator,T>::type holder;
        typedef typename mpl::at<0,ArgList>::type t0;
        typedef typename forward<t0>::type f0;
        typedef typename mpl::at<1,ArgList>::type t1;
        typedef typename forward<t1>::type f1;
        
        static void execute(
            PyObject* p, t0 a0, t1 a1)
        {
            (new holder(p, f0(a0), f1(a1)))->install(p);
        }
    };
};

template <>
struct make_holder<3>
{
    template <class T, class Generator, class ArgList>
    struct apply
    {
        typedef typename eval<Generator,T>::type holder;
        typedef typename mpl::at<0,ArgList>::type t0;
        typedef typename forward<t0>::type f0;
        typedef typename mpl::at<1,ArgList>::type t1;
        typedef typename forward<t1>::type f1;
        typedef typename mpl::at<2,ArgList>::type t2;
        typedef typename forward<t2>::type f2;
        
        static void execute(
            PyObject* p, t0 a0, t1 a1, t2 a2)
        {
            (new holder(p, f0(a0), f1(a1), f2(a2)))->install(p);
        }
    };
};

}}} // namespace boost::python::object

#endif // MAKE_HOLDER_DWA20011215_HPP
