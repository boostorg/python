// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef MEMBER_FUNCTION_CAST_DWA2002410_HPP
# define MEMBER_FUNCTION_CAST_DWA2002410_HPP

// emacs commands used to pre-clean preprocessor output
// (replace-regexp "> *stage1(" ">\nstage1(")

template<class S,class R>
static cast_helper<S,R(T::*)()>
stage1(R(S::*)())
{
    return cast_helper<S,R(T::*)()>();
}
template<class S,class R,class A1>
static cast_helper<S,R(T::*)(A1)>
stage1(R(S::*)(A1))
{
    return cast_helper<S,R(T::*)(A1)>();
}
template<class S,class R,class A1,class A2>
static cast_helper<S,R(T::*)(A1,A2)>
stage1(R(S::*)(A1,A2))
{
    return cast_helper<S,R(T::*)(A1,A2)>();
}
template<class S,class R,class A1,class A2,class A3>
static cast_helper<S,R(T::*)(A1,A2,A3)>
stage1(R(S::*)(A1,A2,A3))
{
    return cast_helper<S,R(T::*)(A1,A2,A3)>();
}
template<class S,class R,class A1,class A2,class A3,class A4>
static cast_helper<S,R(T::*)(A1,A2,A3,A4)>
stage1(R(S::*)(A1,A2,A3,A4))
{
    return cast_helper<S,R(T::*)(A1,A2,A3,A4)>();
}
template<class S,class R,class A1,class A2,class A3,class A4,class A5>
static cast_helper<S,R(T::*)(A1,A2,A3,A4,A5)>
stage1(R(S::*)(A1,A2,A3,A4,A5))
{
    return cast_helper<S,R(T::*)(A1,A2,A3,A4,A5)>();
}
template<class S,class R,class A1,class A2,class A3,class A4,class A5,class A6>
static cast_helper<S,R(T::*)(A1,A2,A3,A4,A5,A6)>
stage1(R(S::*)(A1,A2,A3,A4,A5,A6))
{
    return cast_helper<S,R(T::*)(A1,A2,A3,A4,A5,A6)>();
}
template<class S,class R,class A1,class A2,class A3,class A4,class A5,class A6,class A7>
static cast_helper<S,R(T::*)(A1,A2,A3,A4,A5,A6,A7)>
stage1(R(S::*)(A1,A2,A3,A4,A5,A6,A7))
{
    return cast_helper<S,R(T::*)(A1,A2,A3,A4,A5,A6,A7)>();
}
template<class S,class R,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8>
static cast_helper<S,R(T::*)(A1,A2,A3,A4,A5,A6,A7,A8)>
stage1(R(S::*)(A1,A2,A3,A4,A5,A6,A7,A8))
{
    return cast_helper<S,R(T::*)(A1,A2,A3,A4,A5,A6,A7,A8)>();
}
template<class S,class R,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8,class A9>
static cast_helper<S,R(T::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9)>
stage1(R(S::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9))
{
    return cast_helper<S,R(T::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9)>();
}
template<class S,class R,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8,class A9,class A10>
static cast_helper<S,R(T::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10)>
stage1(R(S::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10))
{
    return cast_helper<S,R(T::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10)>();
}
template<class S,class R,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8,class A9,class A10,class A11>
static cast_helper<S,R(T::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11)>
stage1(R(S::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11))
{
    return cast_helper<S,R(T::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11)>();
}
template<class S,class R,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8,class A9,class A10,class A11,class A12>
static cast_helper<S,R(T::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12)>
stage1(R(S::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12))
{
    return cast_helper<S,R(T::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12)>();
}
template<class S,class R,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8,class A9,class A10,class A11,class A12,class A13>
static cast_helper<S,R(T::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13)>
stage1(R(S::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13))
{
    return cast_helper<S,R(T::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13)>();
}
template<class S,class R,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8,class A9,class A10,class A11,class A12,class A13,class A14>
static cast_helper<S,R(T::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13,A14)>
stage1(R(S::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13,A14))
{
    return cast_helper<S,R(T::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13,A14)>();
}
template<class S,class R,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8,class A9,class A10,class A11,class A12,class A13,class A14,class A15>
static cast_helper<S,R(T::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13,A14,A15)>
stage1(R(S::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13,A14,A15))
{
    return cast_helper<S,R(T::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13,A14,A15)>();
}
template<class S,class R>
static cast_helper<S,R(T::*)()const>
stage1(R(S::*)()const)
{
    return cast_helper<S,R(T::*)()const>();
}
template<class S,class R,class A1>
static cast_helper<S,R(T::*)(A1)const>
stage1(R(S::*)(A1)const)
{
    return cast_helper<S,R(T::*)(A1)const>();
}
template<class S,class R,class A1,class A2>
static cast_helper<S,R(T::*)(A1,A2)const>
stage1(R(S::*)(A1,A2)const)
{
    return cast_helper<S,R(T::*)(A1,A2)const>();
}
template<class S,class R,class A1,class A2,class A3>
static cast_helper<S,R(T::*)(A1,A2,A3)const>
stage1(R(S::*)(A1,A2,A3)const)
{
    return cast_helper<S,R(T::*)(A1,A2,A3)const>();
}
template<class S,class R,class A1,class A2,class A3,class A4>
static cast_helper<S,R(T::*)(A1,A2,A3,A4)const>
stage1(R(S::*)(A1,A2,A3,A4)const)
{
    return cast_helper<S,R(T::*)(A1,A2,A3,A4)const>();
}
template<class S,class R,class A1,class A2,class A3,class A4,class A5>
static cast_helper<S,R(T::*)(A1,A2,A3,A4,A5)const>
stage1(R(S::*)(A1,A2,A3,A4,A5)const)
{
    return cast_helper<S,R(T::*)(A1,A2,A3,A4,A5)const>();
}
template<class S,class R,class A1,class A2,class A3,class A4,class A5,class A6>
static cast_helper<S,R(T::*)(A1,A2,A3,A4,A5,A6)const>
stage1(R(S::*)(A1,A2,A3,A4,A5,A6)const)
{
    return cast_helper<S,R(T::*)(A1,A2,A3,A4,A5,A6)const>();
}
template<class S,class R,class A1,class A2,class A3,class A4,class A5,class A6,class A7>
static cast_helper<S,R(T::*)(A1,A2,A3,A4,A5,A6,A7)const>
stage1(R(S::*)(A1,A2,A3,A4,A5,A6,A7)const)
{
    return cast_helper<S,R(T::*)(A1,A2,A3,A4,A5,A6,A7)const>();
}
template<class S,class R,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8>
static cast_helper<S,R(T::*)(A1,A2,A3,A4,A5,A6,A7,A8)const>
stage1(R(S::*)(A1,A2,A3,A4,A5,A6,A7,A8)const)
{
    return cast_helper<S,R(T::*)(A1,A2,A3,A4,A5,A6,A7,A8)const>();
}
template<class S,class R,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8,class A9>
static cast_helper<S,R(T::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9)const>
stage1(R(S::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9)const)
{
    return cast_helper<S,R(T::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9)const>();
}
template<class S,class R,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8,class A9,class A10>
static cast_helper<S,R(T::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10)const>
stage1(R(S::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10)const)
{
    return cast_helper<S,R(T::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10)const>();
}
template<class S,class R,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8,class A9,class A10,class A11>
static cast_helper<S,R(T::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11)const>
stage1(R(S::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11)const)
{
    return cast_helper<S,R(T::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11)const>();
}
template<class S,class R,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8,class A9,class A10,class A11,class A12>
static cast_helper<S,R(T::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12)const>
stage1(R(S::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12)const)
{
    return cast_helper<S,R(T::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12)const>();
}
template<class S,class R,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8,class A9,class A10,class A11,class A12,class A13>
static cast_helper<S,R(T::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13)const>
stage1(R(S::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13)const)
{
    return cast_helper<S,R(T::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13)const>();
}
template<class S,class R,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8,class A9,class A10,class A11,class A12,class A13,class A14>
static cast_helper<S,R(T::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13,A14)const>
stage1(R(S::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13,A14)const)
{
    return cast_helper<S,R(T::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13,A14)const>();
}
template<class S,class R,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8,class A9,class A10,class A11,class A12,class A13,class A14,class A15>
static cast_helper<S,R(T::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13,A14,A15)const>
stage1(R(S::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13,A14,A15)const)
{
    return cast_helper<S,R(T::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13,A14,A15)const>();
}
template<class S,class R>
static cast_helper<S,R(T::*)()volatile>
stage1(R(S::*)()volatile)
{
    return cast_helper<S,R(T::*)()volatile>();
}
template<class S,class R,class A1>
static cast_helper<S,R(T::*)(A1)volatile>
stage1(R(S::*)(A1)volatile)
{
    return cast_helper<S,R(T::*)(A1)volatile>();
}
template<class S,class R,class A1,class A2>
static cast_helper<S,R(T::*)(A1,A2)volatile>
stage1(R(S::*)(A1,A2)volatile)
{
    return cast_helper<S,R(T::*)(A1,A2)volatile>();
}
template<class S,class R,class A1,class A2,class A3>
static cast_helper<S,R(T::*)(A1,A2,A3)volatile>
stage1(R(S::*)(A1,A2,A3)volatile)
{
    return cast_helper<S,R(T::*)(A1,A2,A3)volatile>();
}
template<class S,class R,class A1,class A2,class A3,class A4>
static cast_helper<S,R(T::*)(A1,A2,A3,A4)volatile>
stage1(R(S::*)(A1,A2,A3,A4)volatile)
{
    return cast_helper<S,R(T::*)(A1,A2,A3,A4)volatile>();
}
template<class S,class R,class A1,class A2,class A3,class A4,class A5>
static cast_helper<S,R(T::*)(A1,A2,A3,A4,A5)volatile>
stage1(R(S::*)(A1,A2,A3,A4,A5)volatile)
{
    return cast_helper<S,R(T::*)(A1,A2,A3,A4,A5)volatile>();
}
template<class S,class R,class A1,class A2,class A3,class A4,class A5,class A6>
static cast_helper<S,R(T::*)(A1,A2,A3,A4,A5,A6)volatile>
stage1(R(S::*)(A1,A2,A3,A4,A5,A6)volatile)
{
    return cast_helper<S,R(T::*)(A1,A2,A3,A4,A5,A6)volatile>();
}
template<class S,class R,class A1,class A2,class A3,class A4,class A5,class A6,class A7>
static cast_helper<S,R(T::*)(A1,A2,A3,A4,A5,A6,A7)volatile>
stage1(R(S::*)(A1,A2,A3,A4,A5,A6,A7)volatile)
{
    return cast_helper<S,R(T::*)(A1,A2,A3,A4,A5,A6,A7)volatile>();
}
template<class S,class R,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8>
static cast_helper<S,R(T::*)(A1,A2,A3,A4,A5,A6,A7,A8)volatile>
stage1(R(S::*)(A1,A2,A3,A4,A5,A6,A7,A8)volatile)
{
    return cast_helper<S,R(T::*)(A1,A2,A3,A4,A5,A6,A7,A8)volatile>();
}
template<class S,class R,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8,class A9>
static cast_helper<S,R(T::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9)volatile>
stage1(R(S::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9)volatile)
{
    return cast_helper<S,R(T::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9)volatile>();
}
template<class S,class R,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8,class A9,class A10>
static cast_helper<S,R(T::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10)volatile>
stage1(R(S::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10)volatile)
{
    return cast_helper<S,R(T::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10)volatile>();
}
template<class S,class R,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8,class A9,class A10,class A11>
static cast_helper<S,R(T::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11)volatile>
stage1(R(S::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11)volatile)
{
    return cast_helper<S,R(T::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11)volatile>();
}
template<class S,class R,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8,class A9,class A10,class A11,class A12>
static cast_helper<S,R(T::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12)volatile>
stage1(R(S::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12)volatile)
{
    return cast_helper<S,R(T::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12)volatile>();
}
template<class S,class R,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8,class A9,class A10,class A11,class A12,class A13>
static cast_helper<S,R(T::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13)volatile>
stage1(R(S::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13)volatile)
{
    return cast_helper<S,R(T::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13)volatile>();
}
template<class S,class R,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8,class A9,class A10,class A11,class A12,class A13,class A14>
static cast_helper<S,R(T::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13,A14)volatile>
stage1(R(S::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13,A14)volatile)
{
    return cast_helper<S,R(T::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13,A14)volatile>();
}
template<class S,class R,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8,class A9,class A10,class A11,class A12,class A13,class A14,class A15>
static cast_helper<S,R(T::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13,A14,A15)volatile>
stage1(R(S::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13,A14,A15)volatile)
{
    return cast_helper<S,R(T::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13,A14,A15)volatile>();
}
template<class S,class R>
static cast_helper<S,R(T::*)()const volatile>
stage1(R(S::*)()const volatile)
{
    return cast_helper<S,R(T::*)()const volatile>();
}
template<class S,class R,class A1>
static cast_helper<S,R(T::*)(A1)const volatile>
stage1(R(S::*)(A1)const volatile)
{
    return cast_helper<S,R(T::*)(A1)const volatile>();
}
template<class S,class R,class A1,class A2>
static cast_helper<S,R(T::*)(A1,A2)const volatile>
stage1(R(S::*)(A1,A2)const volatile)
{
    return cast_helper<S,R(T::*)(A1,A2)const volatile>();
}
template<class S,class R,class A1,class A2,class A3>
static cast_helper<S,R(T::*)(A1,A2,A3)const volatile>
stage1(R(S::*)(A1,A2,A3)const volatile)
{
    return cast_helper<S,R(T::*)(A1,A2,A3)const volatile>();
}
template<class S,class R,class A1,class A2,class A3,class A4>
static cast_helper<S,R(T::*)(A1,A2,A3,A4)const volatile>
stage1(R(S::*)(A1,A2,A3,A4)const volatile)
{
    return cast_helper<S,R(T::*)(A1,A2,A3,A4)const volatile>();
}
template<class S,class R,class A1,class A2,class A3,class A4,class A5>
static cast_helper<S,R(T::*)(A1,A2,A3,A4,A5)const volatile>
stage1(R(S::*)(A1,A2,A3,A4,A5)const volatile)
{
    return cast_helper<S,R(T::*)(A1,A2,A3,A4,A5)const volatile>();
}
template<class S,class R,class A1,class A2,class A3,class A4,class A5,class A6>
static cast_helper<S,R(T::*)(A1,A2,A3,A4,A5,A6)const volatile>
stage1(R(S::*)(A1,A2,A3,A4,A5,A6)const volatile)
{
    return cast_helper<S,R(T::*)(A1,A2,A3,A4,A5,A6)const volatile>();
}
template<class S,class R,class A1,class A2,class A3,class A4,class A5,class A6,class A7>
static cast_helper<S,R(T::*)(A1,A2,A3,A4,A5,A6,A7)const volatile>
stage1(R(S::*)(A1,A2,A3,A4,A5,A6,A7)const volatile)
{
    return cast_helper<S,R(T::*)(A1,A2,A3,A4,A5,A6,A7)const volatile>();
}
template<class S,class R,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8>
static cast_helper<S,R(T::*)(A1,A2,A3,A4,A5,A6,A7,A8)const volatile>
stage1(R(S::*)(A1,A2,A3,A4,A5,A6,A7,A8)const volatile)
{
    return cast_helper<S,R(T::*)(A1,A2,A3,A4,A5,A6,A7,A8)const volatile>();
}
template<class S,class R,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8,class A9>
static cast_helper<S,R(T::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9)const volatile>
stage1(R(S::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9)const volatile)
{
    return cast_helper<S,R(T::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9)const volatile>();
}
template<class S,class R,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8,class A9,class A10>
static cast_helper<S,R(T::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10)const volatile>
stage1(R(S::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10)const volatile)
{
    return cast_helper<S,R(T::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10)const volatile>();
}
template<class S,class R,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8,class A9,class A10,class A11>
static cast_helper<S,R(T::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11)const volatile>
stage1(R(S::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11)const volatile)
{
    return cast_helper<S,R(T::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11)const volatile>();
}
template<class S,class R,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8,class A9,class A10,class A11,class A12>
static cast_helper<S,R(T::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12)const volatile>
stage1(R(S::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12)const volatile)
{
    return cast_helper<S,R(T::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12)const volatile>();
}
template<class S,class R,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8,class A9,class A10,class A11,class A12,class A13>
static cast_helper<S,R(T::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13)const volatile>
stage1(R(S::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13)const volatile)
{
    return cast_helper<S,R(T::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13)const volatile>();
}
template<class S,class R,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8,class A9,class A10,class A11,class A12,class A13,class A14>
static cast_helper<S,R(T::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13,A14)const volatile>
stage1(R(S::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13,A14)const volatile)
{
    return cast_helper<S,R(T::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13,A14)const volatile>();
}
template<class S,class R,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8,class A9,class A10,class A11,class A12,class A13,class A14,class A15>
static cast_helper<S,R(T::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13,A14,A15)const volatile>
stage1(R(S::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13,A14,A15)const volatile)
{
    return cast_helper<S,R(T::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13,A14,A15)const volatile>();
}
#endif // MEMBER_FUNCTION_CAST_DWA2002410_HPP
