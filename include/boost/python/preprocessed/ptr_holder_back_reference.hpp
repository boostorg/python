//Copyright David Abrahams 2002.Permission to copy,use,
//modify,sell and distribute this software is granted provided this
//copyright notice appears in all copies.This software is provided
//"as is" without express or implied warranty,and with no claim as
//to its suitability for any purpose.
#ifndef POINTER_HOLDER_BACK_REFERENCE_DWA2002411_HPP
#define POINTER_HOLDER_BACK_REFERENCE_DWA2002411_HPP

// emacs commands used to pre-clean preprocessor output:
// (replace-regexp ": *m_p *(" "\n: m_p(")
// (replace-regexp "held_type(" "held_type(\n")
// (replace-regexp ", *(" "\n, (")

pointer_holder_back_reference(PyObject*p)
    :m_p(new held_type(
             p))
{
    void const*x=&instance_finder<held_type>::registration;
    (void)x;
}
template<class A0>
pointer_holder_back_reference(PyObject*p,A0 a0)
    :m_p(new held_type(
             p 
             ,(typename unforward<A0>::type)(a0)))
{
    void const*x=&instance_finder<held_type>::registration;
    (void)x;
}
template<class A0,class A1>
pointer_holder_back_reference(PyObject*p,A0 a0,A1 a1)
    :m_p(new held_type(
             p 
             ,(typename unforward<A0>::type)(a0)
             ,(typename unforward<A1>::type)(a1)))
{
    void const*x=&instance_finder<held_type>::registration;
    (void)x;
}
template<class A0,class A1,class A2>
pointer_holder_back_reference(PyObject*p,A0 a0,A1 a1,A2 a2)
    :m_p(new held_type(
             p 
             ,(typename unforward<A0>::type)(a0)
             ,(typename unforward<A1>::type)(a1)
             ,(typename unforward<A2>::type)(a2)))
{
    void const*x=&instance_finder<held_type>::registration;
    (void)x;
}
template<class A0,class A1,class A2,class A3>
pointer_holder_back_reference(PyObject*p,A0 a0,A1 a1,A2 a2,A3 a3)
    :m_p(new held_type(
             p 
             ,(typename unforward<A0>::type)(a0)
             ,(typename unforward<A1>::type)(a1)
             ,(typename unforward<A2>::type)(a2)
             ,(typename unforward<A3>::type)(a3)))
{
    void const*x=&instance_finder<held_type>::registration;
    (void)x;
}
template<class A0,class A1,class A2,class A3,class A4>
pointer_holder_back_reference(PyObject*p,A0 a0,A1 a1,A2 a2,A3 a3,A4 a4)
    :m_p(new held_type(
             p 
             ,(typename unforward<A0>::type)(a0)
             ,(typename unforward<A1>::type)(a1)
             ,(typename unforward<A2>::type)(a2)
             ,(typename unforward<A3>::type)(a3)
             ,(typename unforward<A4>::type)(a4)))
{
    void const*x=&instance_finder<held_type>::registration;
    (void)x;
}
template<class A0,class A1,class A2,class A3,class A4,class A5>
pointer_holder_back_reference(PyObject*p,A0 a0,A1 a1,A2 a2,A3 a3,A4 a4,A5 a5)
    :m_p(new held_type(
             p 
             ,(typename unforward<A0>::type)(a0)
             ,(typename unforward<A1>::type)(a1)
             ,(typename unforward<A2>::type)(a2)
             ,(typename unforward<A3>::type)(a3)
             ,(typename unforward<A4>::type)(a4)
             ,(typename unforward<A5>::type)(a5)))
{
    void const*x=&instance_finder<held_type>::registration;
    (void)x;
}
template<class A0,class A1,class A2,class A3,class A4,class A5,class A6>
pointer_holder_back_reference(PyObject*p,A0 a0,A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6)
    :m_p(new held_type(
             p 
             ,(typename unforward<A0>::type)(a0)
             ,(typename unforward<A1>::type)(a1)
             ,(typename unforward<A2>::type)(a2)
             ,(typename unforward<A3>::type)(a3)
             ,(typename unforward<A4>::type)(a4)
             ,(typename unforward<A5>::type)(a5)
             ,(typename unforward<A6>::type)(a6)))
{
    void const*x=&instance_finder<held_type>::registration;
    (void)x;
}
template<class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7>
pointer_holder_back_reference(PyObject*p,A0 a0,A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6,A7 a7)
    :m_p(new held_type(
             p 
             ,(typename unforward<A0>::type)(a0)
             ,(typename unforward<A1>::type)(a1)
             ,(typename unforward<A2>::type)(a2)
             ,(typename unforward<A3>::type)(a3)
             ,(typename unforward<A4>::type)(a4)
             ,(typename unforward<A5>::type)(a5)
             ,(typename unforward<A6>::type)(a6)
             ,(typename unforward<A7>::type)(a7)))
{
    void const*x=&instance_finder<held_type>::registration;
    (void)x;
}
template<class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8>
pointer_holder_back_reference(PyObject*p,A0 a0,A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6,A7 a7,A8 a8)
    :m_p(new held_type(
             p 
             ,(typename unforward<A0>::type)(a0)
             ,(typename unforward<A1>::type)(a1)
             ,(typename unforward<A2>::type)(a2)
             ,(typename unforward<A3>::type)(a3)
             ,(typename unforward<A4>::type)(a4)
             ,(typename unforward<A5>::type)(a5)
             ,(typename unforward<A6>::type)(a6)
             ,(typename unforward<A7>::type)(a7)
             ,(typename unforward<A8>::type)(a8)))
{
    void const*x=&instance_finder<held_type>::registration;
    (void)x;
}
template<class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8,class A9>
pointer_holder_back_reference(PyObject*p,A0 a0,A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6,A7 a7,A8 a8,A9 a9)
    :m_p(new held_type(
             p 
             ,(typename unforward<A0>::type)(a0)
             ,(typename unforward<A1>::type)(a1)
             ,(typename unforward<A2>::type)(a2)
             ,(typename unforward<A3>::type)(a3)
             ,(typename unforward<A4>::type)(a4)
             ,(typename unforward<A5>::type)(a5)
             ,(typename unforward<A6>::type)(a6)
             ,(typename unforward<A7>::type)(a7)
             ,(typename unforward<A8>::type)(a8)
             ,(typename unforward<A9>::type)(a9)))
{
    void const*x=&instance_finder<held_type>::registration;
    (void)x;
}
template<class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8,class A9,class A10>
pointer_holder_back_reference(PyObject*p,A0 a0,A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6,A7 a7,A8 a8,A9 a9,A10 a10)
    :m_p(new held_type(
             p 
             ,(typename unforward<A0>::type)(a0)
             ,(typename unforward<A1>::type)(a1)
             ,(typename unforward<A2>::type)(a2)
             ,(typename unforward<A3>::type)(a3)
             ,(typename unforward<A4>::type)(a4)
             ,(typename unforward<A5>::type)(a5)
             ,(typename unforward<A6>::type)(a6)
             ,(typename unforward<A7>::type)(a7)
             ,(typename unforward<A8>::type)(a8)
             ,(typename unforward<A9>::type)(a9)
             ,(typename unforward<A10>::type)(a10)))
{
    void const*x=&instance_finder<held_type>::registration;
    (void)x;
}
template<class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8,class A9,class A10,class A11>
pointer_holder_back_reference(PyObject*p,A0 a0,A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6,A7 a7,A8 a8,A9 a9,A10 a10,A11 a11)
    :m_p(new held_type(
             p 
             ,(typename unforward<A0>::type)(a0)
             ,(typename unforward<A1>::type)(a1)
             ,(typename unforward<A2>::type)(a2)
             ,(typename unforward<A3>::type)(a3)
             ,(typename unforward<A4>::type)(a4)
             ,(typename unforward<A5>::type)(a5)
             ,(typename unforward<A6>::type)(a6)
             ,(typename unforward<A7>::type)(a7)
             ,(typename unforward<A8>::type)(a8)
             ,(typename unforward<A9>::type)(a9)
             ,(typename unforward<A10>::type)(a10)
             ,(typename unforward<A11>::type)(a11)))
{
    void const*x=&instance_finder<held_type>::registration;
    (void)x;
}
template<class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8,class A9,class A10,class A11,class A12>
pointer_holder_back_reference(PyObject*p,A0 a0,A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6,A7 a7,A8 a8,A9 a9,A10 a10,A11 a11,A12 a12)
    :m_p(new held_type(
             p 
             ,(typename unforward<A0>::type)(a0)
             ,(typename unforward<A1>::type)(a1)
             ,(typename unforward<A2>::type)(a2)
             ,(typename unforward<A3>::type)(a3)
             ,(typename unforward<A4>::type)(a4)
             ,(typename unforward<A5>::type)(a5)
             ,(typename unforward<A6>::type)(a6)
             ,(typename unforward<A7>::type)(a7)
             ,(typename unforward<A8>::type)(a8)
             ,(typename unforward<A9>::type)(a9)
             ,(typename unforward<A10>::type)(a10)
             ,(typename unforward<A11>::type)(a11)
             ,(typename unforward<A12>::type)(a12)))
{
    void const*x=&instance_finder<held_type>::registration;
    (void)x;
}
template<class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8,class A9,class A10,class A11,class A12,class A13>
pointer_holder_back_reference(PyObject*p,A0 a0,A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6,A7 a7,A8 a8,A9 a9,A10 a10,A11 a11,A12 a12,A13 a13)
    :m_p(new held_type(
             p 
             ,(typename unforward<A0>::type)(a0)
             ,(typename unforward<A1>::type)(a1)
             ,(typename unforward<A2>::type)(a2)
             ,(typename unforward<A3>::type)(a3)
             ,(typename unforward<A4>::type)(a4)
             ,(typename unforward<A5>::type)(a5)
             ,(typename unforward<A6>::type)(a6)
             ,(typename unforward<A7>::type)(a7)
             ,(typename unforward<A8>::type)(a8)
             ,(typename unforward<A9>::type)(a9)
             ,(typename unforward<A10>::type)(a10)
             ,(typename unforward<A11>::type)(a11)
             ,(typename unforward<A12>::type)(a12)
             ,(typename unforward<A13>::type)(a13)))
{
    void const*x=&instance_finder<held_type>::registration;
    (void)x;
}
template<class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8,class A9,class A10,class A11,class A12,class A13,class A14>
pointer_holder_back_reference(PyObject*p,A0 a0,A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6,A7 a7,A8 a8,A9 a9,A10 a10,A11 a11,A12 a12,A13 a13,A14 a14)
    :m_p(new held_type(
             p 
             ,(typename unforward<A0>::type)(a0)
             ,(typename unforward<A1>::type)(a1)
             ,(typename unforward<A2>::type)(a2)
             ,(typename unforward<A3>::type)(a3)
             ,(typename unforward<A4>::type)(a4)
             ,(typename unforward<A5>::type)(a5)
             ,(typename unforward<A6>::type)(a6)
             ,(typename unforward<A7>::type)(a7)
             ,(typename unforward<A8>::type)(a8)
             ,(typename unforward<A9>::type)(a9)
             ,(typename unforward<A10>::type)(a10)
             ,(typename unforward<A11>::type)(a11)
             ,(typename unforward<A12>::type)(a12)
             ,(typename unforward<A13>::type)(a13)
             ,(typename unforward<A14>::type)(a14)))
{
    void const*x=&instance_finder<held_type>::registration;
    (void)x;
}
#endif//POINTER_HOLDER_BACK_REFERENCE_DWA2002411_HPP
