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
        static void
        execute(PyObject*p)
        {
            (new
             Holder(p))->install(p);
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
        static void
        execute(PyObject*p,t0 a0)
        {
            (new
             Holder(p,f0(a0)))->install(p);
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
        static void
        execute(PyObject*p,t0 a0,t1 a1)
        {
            (new
             Holder(p,f0(a0),f1(a1)))->install(p);
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
        static void
        execute(PyObject*p,t0 a0,t1 a1,t2 a2)
        {
            (new
             Holder(p,f0(a0),f1(a1),f2(a2)))->install(p);
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
        static void
        execute(PyObject*p,t0 a0,t1 a1,t2 a2,t3 a3)
        {
            (new
             Holder(p,f0(a0),f1(a1),f2(a2),f3(a3)))->install(p);
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
        static void
        execute(PyObject*p,t0 a0,t1 a1,t2 a2,t3 a3,t4 a4)
        {
            (new
             Holder(p,f0(a0),f1(a1),f2(a2),f3(a3),f4(a4)))->install(p);
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
        static void
        execute(PyObject*p,t0 a0,t1 a1,t2 a2,t3 a3,t4 a4,t5 a5)
        {
            (new
             Holder(p,f0(a0),f1(a1),f2(a2),f3(a3),f4(a4),f5(a5)))->install(p);
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
        static void
        execute(PyObject*p,t0 a0,t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6)
        {
            (new
             Holder(p,f0(a0),f1(a1),f2(a2),f3(a3),f4(a4),f5(a5),f6(a6)))->install(p);
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
        static void
        execute(PyObject*p,t0 a0,t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7)
        {
            (new
             Holder(p,f0(a0),f1(a1),f2(a2),f3(a3),f4(a4),f5(a5),f6(a6),f7(a7)))->install(p);
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
        static void
        execute(PyObject*p,t0 a0,t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8)
        {
            (new
             Holder(p,f0(a0),f1(a1),f2(a2),f3(a3),f4(a4),f5(a5),f6(a6),f7(a7),f8(a8)))->install(p);
        }
 
    };

};
template<>
struct make_holder<10>
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
        typedef typename mpl::at<9,ArgList>::type t9;
        typedef typename forward<t9>::type f9;
        static void
        execute(PyObject*p,t0 a0,t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9)
        {
            (new
             Holder(p,f0(a0),f1(a1),f2(a2),f3(a3),f4(a4),f5(a5),f6(a6),f7(a7),f8(a8),f9(a9)))->install(p);
        }
 
    };

};
template<>
struct make_holder<11>
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
        typedef typename mpl::at<9,ArgList>::type t9;
        typedef typename forward<t9>::type f9;
        typedef typename mpl::at<10,ArgList>::type t10;
        typedef typename forward<t10>::type f10;
        static void
        execute(PyObject*p,t0 a0,t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9,t10 a10)
        {
            (new
             Holder(p,f0(a0),f1(a1),f2(a2),f3(a3),f4(a4),f5(a5),f6(a6),f7(a7),f8(a8),f9(a9),f10(a10)))->install(p);
        }
 
    };

};
template<>
struct make_holder<12>
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
        typedef typename mpl::at<9,ArgList>::type t9;
        typedef typename forward<t9>::type f9;
        typedef typename mpl::at<10,ArgList>::type t10;
        typedef typename forward<t10>::type f10;
        typedef typename mpl::at<11,ArgList>::type t11;
        typedef typename forward<t11>::type f11;
        static void
        execute(PyObject*p,t0 a0,t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9,t10 a10,t11 a11)
        {
            (new
             Holder(p,f0(a0),f1(a1),f2(a2),f3(a3),f4(a4),f5(a5),f6(a6),f7(a7),f8(a8),f9(a9),f10(a10),f11(a11)))->install(p);
        }
 
    };

};
template<>
struct make_holder<13>
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
        typedef typename mpl::at<9,ArgList>::type t9;
        typedef typename forward<t9>::type f9;
        typedef typename mpl::at<10,ArgList>::type t10;
        typedef typename forward<t10>::type f10;
        typedef typename mpl::at<11,ArgList>::type t11;
        typedef typename forward<t11>::type f11;
        typedef typename mpl::at<12,ArgList>::type t12;
        typedef typename forward<t12>::type f12;
        static void
        execute(PyObject*p,t0 a0,t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9,t10 a10,t11 a11,t12 a12)
        {
            (new
             Holder(p,f0(a0),f1(a1),f2(a2),f3(a3),f4(a4),f5(a5),f6(a6),f7(a7),f8(a8),f9(a9),f10(a10),f11(a11),f12(a12)))->install(p);
        }
 
    };

};
template<>
struct make_holder<14>
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
        typedef typename mpl::at<9,ArgList>::type t9;
        typedef typename forward<t9>::type f9;
        typedef typename mpl::at<10,ArgList>::type t10;
        typedef typename forward<t10>::type f10;
        typedef typename mpl::at<11,ArgList>::type t11;
        typedef typename forward<t11>::type f11;
        typedef typename mpl::at<12,ArgList>::type t12;
        typedef typename forward<t12>::type f12;
        typedef typename mpl::at<13,ArgList>::type t13;
        typedef typename forward<t13>::type f13;
        static void
        execute(PyObject*p,t0 a0,t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9,t10 a10,t11 a11,t12 a12,t13 a13)
        {
            (new
             Holder(p,f0(a0),f1(a1),f2(a2),f3(a3),f4(a4),f5(a5),f6(a6),f7(a7),f8(a8),f9(a9),f10(a10),f11(a11),f12(a12),f13(a13)))->install(p);
        }
 
    };

};
template<>
struct make_holder<15>
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
        typedef typename mpl::at<9,ArgList>::type t9;
        typedef typename forward<t9>::type f9;
        typedef typename mpl::at<10,ArgList>::type t10;
        typedef typename forward<t10>::type f10;
        typedef typename mpl::at<11,ArgList>::type t11;
        typedef typename forward<t11>::type f11;
        typedef typename mpl::at<12,ArgList>::type t12;
        typedef typename forward<t12>::type f12;
        typedef typename mpl::at<13,ArgList>::type t13;
        typedef typename forward<t13>::type f13;
        typedef typename mpl::at<14,ArgList>::type t14;
        typedef typename forward<t14>::type f14;
        static void
        execute(PyObject*p,t0 a0,t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9,t10 a10,t11 a11,t12 a12,t13 a13,t14 a14)
        {
            (new
             Holder(p,f0(a0),f1(a1),f2(a2),f3(a3),f4(a4),f5(a5),f6(a6),f7(a7),f8(a8),f9(a9),f10(a10),f11(a11),f12(a12),f13(a13),f14(a14)))->install(p);
        }
 
    };

};
#endif // MAKE_HOLDER_DWA2002416_HPP


