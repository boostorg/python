// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef VALUE_HOLDER_DWA2002411_HPP
# define VALUE_HOLDER_DWA2002411_HPP

value_holder(PyObject*)
    :m_held()
{

}
template<class A0>value_holder(PyObject*,A0 a0)
    :m_held(
        (typename unforward<A0>::type)(a0))
{

}
template<class A0,class A1>value_holder(PyObject*,A0 a0,A1 a1)
    :m_held(
        (typename unforward<A0>::type)(a0),
        (typename unforward<A1>::type)(a1))
{

}
template<class A0,class A1,class A2>value_holder(PyObject*,A0 a0,A1 a1,A2 a2)
    :m_held(
        (typename unforward<A0>::type)(a0),
        (typename unforward<A1>::type)(a1),
        (typename unforward<A2>::type)(a2))
{

}
template<class A0,class A1,class A2,class A3>value_holder(PyObject*,A0 a0,A1 a1,A2 a2,A3 a3)
    :m_held(
        (typename unforward<A0>::type)(a0),
        (typename unforward<A1>::type)(a1),
        (typename unforward<A2>::type)(a2),
        (typename unforward<A3>::type)(a3))
{

}
template<class A0,class A1,class A2,class A3,class A4>value_holder(PyObject*,A0 a0,A1 a1,A2 a2,A3 a3,A4 a4)
    :m_held(
        (typename unforward<A0>::type)(a0),
        (typename unforward<A1>::type)(a1),
        (typename unforward<A2>::type)(a2),
        (typename unforward<A3>::type)(a3),
        (typename unforward<A4>::type)(a4))
{

}
template<class A0,class A1,class A2,class A3,class A4,class A5>value_holder(PyObject*,A0 a0,A1 a1,A2 a2,A3 a3,A4 a4,A5 a5)
    :m_held(
        (typename unforward<A0>::type)(a0),
        (typename unforward<A1>::type)(a1),
        (typename unforward<A2>::type)(a2),
        (typename unforward<A3>::type)(a3),
        (typename unforward<A4>::type)(a4),
        (typename unforward<A5>::type)(a5))
{

}
template<class A0,class A1,class A2,class A3,class A4,class A5,class A6>value_holder(PyObject*,A0 a0,A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6)
    :m_held(
        (typename unforward<A0>::type)(a0),
        (typename unforward<A1>::type)(a1),
        (typename unforward<A2>::type)(a2),
        (typename unforward<A3>::type)(a3),
        (typename unforward<A4>::type)(a4),
        (typename unforward<A5>::type)(a5),
        (typename unforward<A6>::type)(a6))
{

}
template<class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7>value_holder(PyObject*,A0 a0,A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6,A7 a7)
    :m_held(
        (typename unforward<A0>::type)(a0),
        (typename unforward<A1>::type)(a1),
        (typename unforward<A2>::type)(a2),
        (typename unforward<A3>::type)(a3),
        (typename unforward<A4>::type)(a4),
        (typename unforward<A5>::type)(a5),
        (typename unforward<A6>::type)(a6),
        (typename unforward<A7>::type)(a7))
{

}
template<class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8>value_holder(PyObject*,A0 a0,A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6,A7 a7,A8 a8)
    :m_held(
        (typename unforward<A0>::type)(a0),
        (typename unforward<A1>::type)(a1),
        (typename unforward<A2>::type)(a2),
        (typename unforward<A3>::type)(a3),
        (typename unforward<A4>::type)(a4),
        (typename unforward<A5>::type)(a5),
        (typename unforward<A6>::type)(a6),
        (typename unforward<A7>::type)(a7),
        (typename unforward<A8>::type)(a8))
{

}       

#endif // VALUE_HOLDER_DWA2002411_HPP
