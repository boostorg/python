// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef MAKE_HOLDER_DWA2002416_HPP
# define MAKE_HOLDER_DWA2002416_HPP

template<>
struct make_holder<0>
{
    template<class Holder,class ArgList>
    struct apply 
    {
        static void execute(PyObject*p)
        {
            (new Holder(p))->install(p);
        }
 
    };
};
template<>
struct make_holder<1>
{
    template<class Holder,class ArgList>
    struct apply 
    {
        typedef typename mpl::at<0,ArgList>::type t0;
        typedef typename forward<t0>::type f0;
        static void execute(PyObject*p,t0 a0)
        {
            (new Holder(p,f0(a0)))->install(p);
        }
 
    };
};
template<>
struct make_holder<2>
{
    template<class Holder,class ArgList>
    struct apply 
    {
        typedef typename mpl::at<0,ArgList>::type t0;
        typedef typename forward<t0>::type f0;
        typedef typename mpl::at<1,ArgList>::type t1;
        typedef typename forward<t1>::type f1;
        static void execute(PyObject*p,t0 a0,t1 a1)
        {
            (new Holder(p,f0(a0),f1(a1)))->install(p);
        }
 
    };
};
template<>
struct make_holder<3>
{
    template<class Holder,class ArgList>
    struct apply 
    {
        typedef typename mpl::at<0,ArgList>::type t0;
        typedef typename forward<t0>::type f0;
        typedef typename mpl::at<1,ArgList>::type t1;
        typedef typename forward<t1>::type f1;
        typedef typename mpl::at<2,ArgList>::type t2;
        typedef typename forward<t2>::type f2;
        static void execute(PyObject*p,t0 a0,t1 a1,t2 a2)
        {
            (new Holder(p,f0(a0),f1(a1),f2(a2)))->install(p);
        }
 
    };
};
template<>
struct make_holder<4>
{
    template<class Holder,class ArgList>
    struct apply 
    {
        typedef typename mpl::at<0,ArgList>::type t0;
        typedef typename forward<t0>::type f0;
        typedef typename mpl::at<1,ArgList>::type t1;
        typedef typename forward<t1>::type f1;
        typedef typename mpl::at<2,ArgList>::type t2;
        typedef typename forward<t2>::type f2;
        typedef typename mpl::at<3,ArgList>::type t3;
        typedef typename forward<t3>::type f3;
        static void execute(PyObject*p,t0 a0,t1 a1,t2 a2,t3 a3)
        {
            (new Holder(p,f0(a0),f1(a1),f2(a2),f3(a3)))->install(p);
        }
 
    };
};
template<>
struct make_holder<5>
{
    template<class Holder,class ArgList>
    struct apply 
    {
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
        static void execute(PyObject*p,t0 a0,t1 a1,t2 a2,t3 a3,t4 a4)
        {
            (new Holder(p,f0(a0),f1(a1),f2(a2),f3(a3),f4(a4)))->install(p);
        }
 
    };
};
template<>
struct make_holder<6>
{
    template<class Holder,class ArgList>
    struct apply 
    {
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
        static void execute(PyObject*p,t0 a0,t1 a1,t2 a2,t3 a3,t4 a4,t5 a5)
        {
            (new Holder(p,f0(a0),f1(a1),f2(a2),f3(a3),f4(a4),f5(a5)))->install(p);
        }
 
    };
};
template<>
struct make_holder<7>
{
    template<class Holder,class ArgList>
    struct apply 
    {
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
        typedef typename mpl::at<6,ArgList>::type t6;
        typedef typename forward<t6>::type f6;
        static void execute(PyObject*p,t0 a0,t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6)
        {
            (new Holder(p,f0(a0),f1(a1),f2(a2),f3(a3),f4(a4),f5(a5),f6(a6)))->install(p);
        }
 
    };
};
template<>
struct make_holder<8>
{
    template<class Holder,class ArgList>
    struct apply 
    {
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
        typedef typename mpl::at<6,ArgList>::type t6;
        typedef typename forward<t6>::type f6;
        typedef typename mpl::at<7,ArgList>::type t7;
        typedef typename forward<t7>::type f7;
        static void execute(PyObject*p,t0 a0,t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7)
        {
            (new Holder(p,f0(a0),f1(a1),f2(a2),f3(a3),f4(a4),f5(a5),f6(a6),f7(a7)))->install(p);
        }
 
    };
};
template<>
struct make_holder<9>
{
    template<class Holder,class ArgList>
    struct apply 
    {
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
        typedef typename mpl::at<6,ArgList>::type t6;
        typedef typename forward<t6>::type f6;
        typedef typename mpl::at<7,ArgList>::type t7;
        typedef typename forward<t7>::type f7;
        typedef typename mpl::at<8,ArgList>::type t8;
        typedef typename forward<t8>::type f8;
        static void execute(PyObject*p,t0 a0,t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8)
        {
            (new Holder(p,f0(a0),f1(a1),f2(a2),f3(a3),f4(a4),f5(a5),f6(a6),f7(a7),f8(a8)))->install(p);
        }
 
    };
};

#endif // MAKE_HOLDER_DWA2002416_HPP
