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
# include <boost/python/detail/eval.hpp>

namespace boost { namespace python { namespace objects { 

template <int nargs> struct make_holder;

template <>
struct make_holder<0>
{
    template <class T, class Generator, class ArgList>
    struct apply
    {
        typedef typename python::detail::eval<Generator,T>::type holder;
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
        typedef typename python::detail::eval<Generator,T>::type holder;
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
        typedef typename python::detail::eval<Generator,T>::type holder;
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
        typedef typename python::detail::eval<Generator,T>::type holder;
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

template <>
struct make_holder<4>
{
    template <class T, class Generator, class ArgList>
    struct apply
    {
        typedef typename python::detail::eval<Generator,T>::type holder;
        typedef typename mpl::at<0,ArgList>::type t0;
        typedef typename forward<t0>::type f0;
        typedef typename mpl::at<1,ArgList>::type t1;
        typedef typename forward<t1>::type f1;
        typedef typename mpl::at<2,ArgList>::type t2;
        typedef typename forward<t2>::type f2;
        typedef typename mpl::at<3,ArgList>::type t3;
        typedef typename forward<t3>::type f3;
        
        static void execute(
            PyObject* p, t0 a0, t1 a1, t2 a2, t3 a3)
        {
            (new holder(p, f0(a0), f1(a1), f2(a2), f3(a3)))->install(p);
        }
    };
};

template <>
struct make_holder<5>
{
    template <class T, class Generator, class ArgList>
    struct apply
    {
        typedef typename python::detail::eval<Generator,T>::type holder;
        typedef typename mpl::at<0,ArgList>::type t0;
        typedef typename forward<t0>::type f0;
        typedef typename mpl::at<1,ArgList>::type t1;
        typedef typename forward<t1>::type f1;
        typedef typename mpl::at<2,ArgList>::type t2;
        typedef typename forward<t2>::type f2;
        typedef typename mpl::at<3,ArgList>::type t3;
        typedef typename forward<t3>::type f3;
        typedef typename mpl::at<4,ArgList>::type t4;
        typedef typename forward<t4>::type f4;
        
        static void execute(
            PyObject* p, t0 a0, t1 a1, t2 a2, t3 a3, t4 a4)
        {
            (new holder(p, f0(a0), f1(a1), f2(a2), f3(a3), f4(a4)))->install(p);
        }
    };
};

template <>
struct make_holder<6>
{
    template <class T, class Generator, class ArgList>
    struct apply
    {
        typedef typename python::detail::eval<Generator,T>::type holder;
        typedef typename mpl::at<0,ArgList>::type t0;
        typedef typename forward<t0>::type f0;
        typedef typename mpl::at<1,ArgList>::type t1;
        typedef typename forward<t1>::type f1;
        typedef typename mpl::at<2,ArgList>::type t2;
        typedef typename forward<t2>::type f2;
        typedef typename mpl::at<3,ArgList>::type t3;
        typedef typename forward<t3>::type f3;
        typedef typename mpl::at<4,ArgList>::type t4;
        typedef typename forward<t4>::type f4;
        typedef typename mpl::at<5,ArgList>::type t5;
        typedef typename forward<t5>::type f5;
        
        static void execute(
            PyObject* p, t0 a0, t1 a1, t2 a2, t3 a3, t4 a4, t5 a5)
        {
            (new holder(p, f0(a0), f1(a1), f2(a2), f3(a3), f4(a4), f5(a5)))->install(p);
        }
    };
};

}}} // namespace boost::python::objects

#endif // MAKE_HOLDER_DWA20011215_HPP
