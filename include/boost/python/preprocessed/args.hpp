// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef ARGS_DWA2002417_HPP
# define ARGS_DWA2002417_HPP

template<>
struct size<boost::python::args<> >
{
    BOOST_STATIC_CONSTANT(long,value=0);
};
template<class A0>
struct size<boost::python::args<A0> >
{
    BOOST_STATIC_CONSTANT(long,value=1);
};
template<class A0,class A1>
struct size<boost::python::args<A0,A1> >
{
    BOOST_STATIC_CONSTANT(long,value=2);
};
template<class A0,class A1,class A2>
struct size<boost::python::args<A0,A1,A2> >
{
    BOOST_STATIC_CONSTANT(long,value=3);
};
template<class A0,class A1,class A2,class A3>
struct size<boost::python::args<A0,A1,A2,A3> >
{
    BOOST_STATIC_CONSTANT(long,value=4);
};
template<class A0,class A1,class A2,class A3,class A4>
struct size<boost::python::args<A0,A1,A2,A3,A4> >
{
    BOOST_STATIC_CONSTANT(long,value=5);
};
template<class A0,class A1,class A2,class A3,class A4,class A5>
struct size<boost::python::args<A0,A1,A2,A3,A4,A5> >
{
    BOOST_STATIC_CONSTANT(long,value=6);
};
template<class A0,class A1,class A2,class A3,class A4,class A5,class A6>
struct size<boost::python::args<A0,A1,A2,A3,A4,A5,A6> >
{
    BOOST_STATIC_CONSTANT(long,value=7);
};
template<class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7>
struct size<boost::python::args<A0,A1,A2,A3,A4,A5,A6,A7> >
{
    BOOST_STATIC_CONSTANT(long,value=8);
};
template<class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8>
struct size<boost::python::args<A0,A1,A2,A3,A4,A5,A6,A7,A8> >
{
    BOOST_STATIC_CONSTANT(long,value=9);
};
template<class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8,class A9>
struct size<boost::python::args<A0,A1,A2,A3,A4,A5,A6,A7,A8,A9> >
{
    BOOST_STATIC_CONSTANT(long,value=10);
};
template<class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8,class A9,class A10>
struct size<boost::python::args<A0,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10> >
{
    BOOST_STATIC_CONSTANT(long,value=11);
};
template<class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8,class A9,class A10,class A11>
struct size<boost::python::args<A0,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11> >
{
    BOOST_STATIC_CONSTANT(long,value=12);
};
template<class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8,class A9,class A10,class A11,class A12>
struct size<boost::python::args<A0,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12> >
{
    BOOST_STATIC_CONSTANT(long,value=13);
};
template<class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8,class A9,class A10,class A11,class A12,class A13>
struct size<boost::python::args<A0,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13> >
{
    BOOST_STATIC_CONSTANT(long,value=14);
};
template<class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8,class A9,class A10,class A11,class A12,class A13,class A14>
struct size<boost::python::args<A0,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13,A14> >
{
    BOOST_STATIC_CONSTANT(long,value=15);
};

 


template<class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8,class A9,class A10,class A11,class A12,class A13,class A14>
struct at<0,boost::python::args<A0,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13,A14> >
{
    typedef A0 type;
};
template<class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8,class A9,class A10,class A11,class A12,class A13,class A14>
struct at<1,boost::python::args<A0,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13,A14> >
{
    typedef A1 type;
};
template<class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8,class A9,class A10,class A11,class A12,class A13,class A14>
struct at<2,boost::python::args<A0,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13,A14> >
{
    typedef A2 type;
};
template<class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8,class A9,class A10,class A11,class A12,class A13,class A14>
struct at<3,boost::python::args<A0,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13,A14> >
{
    typedef A3 type;
};
template<class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8,class A9,class A10,class A11,class A12,class A13,class A14>
struct at<4,boost::python::args<A0,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13,A14> >
{
    typedef A4 type;
};
template<class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8,class A9,class A10,class A11,class A12,class A13,class A14>
struct at<5,boost::python::args<A0,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13,A14> >
{
    typedef A5 type;
};
template<class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8,class A9,class A10,class A11,class A12,class A13,class A14>
struct at<6,boost::python::args<A0,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13,A14> >
{
    typedef A6 type;
};
template<class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8,class A9,class A10,class A11,class A12,class A13,class A14>
struct at<7,boost::python::args<A0,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13,A14> >
{
    typedef A7 type;
};
template<class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8,class A9,class A10,class A11,class A12,class A13,class A14>
struct at<8,boost::python::args<A0,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13,A14> >
{
    typedef A8 type;
};
template<class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8,class A9,class A10,class A11,class A12,class A13,class A14>
struct at<9,boost::python::args<A0,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13,A14> >
{
    typedef A9 type;
};
template<class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8,class A9,class A10,class A11,class A12,class A13,class A14>
struct at<10,boost::python::args<A0,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13,A14> >
{
    typedef A10 type;
};
template<class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8,class A9,class A10,class A11,class A12,class A13,class A14>
struct at<11,boost::python::args<A0,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13,A14> >
{
    typedef A11 type;
};
template<class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8,class A9,class A10,class A11,class A12,class A13,class A14>
struct at<12,boost::python::args<A0,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13,A14> >
{
    typedef A12 type;
};
template<class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8,class A9,class A10,class A11,class A12,class A13,class A14>
struct at<13,boost::python::args<A0,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13,A14> >
{
    typedef A13 type;
};
template<class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8,class A9,class A10,class A11,class A12,class A13,class A14>
struct at<14,boost::python::args<A0,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13,A14> >
{
    typedef A14 type;
};

#endif // ARGS_DWA2002417_HPP
