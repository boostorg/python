// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef CALLER_DWA2002410_HPP
# define CALLER_DWA2002410_HPP

template<class P,class R>
PyObject*operator()(R(*f)(),PyObject*args,PyObject*keywords,P const&policies)const 
{
    return returning<R>::call(f,args,keywords,&policies);
}
template<class P,class R,class A0>
PyObject*operator()(R(*f)(A0),PyObject*args,PyObject*keywords,P const&policies)const 
{
    return returning<R>::call(f,args,keywords,&policies);
}
template<class P,class R,class A0,class A1>
PyObject*operator()(R(*f)(A0,A1),PyObject*args,PyObject*keywords,P const&policies)const 
{
    return returning<R>::call(f,args,keywords,&policies);
}
template<class P,class R,class A0,class A1,class A2>
PyObject*operator()(R(*f)(A0,A1,A2),PyObject*args,PyObject*keywords,P const&policies)const 
{
    return returning<R>::call(f,args,keywords,&policies);
}
template<class P,class R,class A0,class A1,class A2,class A3>
PyObject*operator()(R(*f)(A0,A1,A2,A3),PyObject*args,PyObject*keywords,P const&policies)const 
{
    return returning<R>::call(f,args,keywords,&policies);
}
template<class P,class R,class A0,class A1,class A2,class A3,class A4>
PyObject*operator()(R(*f)(A0,A1,A2,A3,A4),PyObject*args,PyObject*keywords,P const&policies)const 
{
    return returning<R>::call(f,args,keywords,&policies);
}
template<class P,class R,class A0,class A1,class A2,class A3,class A4,class A5>
PyObject*operator()(R(*f)(A0,A1,A2,A3,A4,A5),PyObject*args,PyObject*keywords,P const&policies)const 
{
    return returning<R>::call(f,args,keywords,&policies);
}
template<class P,class R,class A0,class A1,class A2,class A3,class A4,class A5,class A6>
PyObject*operator()(R(*f)(A0,A1,A2,A3,A4,A5,A6),PyObject*args,PyObject*keywords,P const&policies)const 
{
    return returning<R>::call(f,args,keywords,&policies);
}
template<class P,class R,class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7>
PyObject*operator()(R(*f)(A0,A1,A2,A3,A4,A5,A6,A7),PyObject*args,PyObject*keywords,P const&policies)const 
{
    return returning<R>::call(f,args,keywords,&policies);
}
template<class P,class R,class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8>
PyObject*operator()(R(*f)(A0,A1,A2,A3,A4,A5,A6,A7,A8),PyObject*args,PyObject*keywords,P const&policies)const 
{
    return returning<R>::call(f,args,keywords,&policies);
}
template<class P,class R,class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8,class A9>
PyObject*operator()(R(*f)(A0,A1,A2,A3,A4,A5,A6,A7,A8,A9),PyObject*args,PyObject*keywords,P const&policies)const 
{
    return returning<R>::call(f,args,keywords,&policies);
}
template<class P,class R,class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8,class A9,class A10>
PyObject*operator()(R(*f)(A0,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10),PyObject*args,PyObject*keywords,P const&policies)const 
{
    return returning<R>::call(f,args,keywords,&policies);
}
template<class P,class R,class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8,class A9,class A10,class A11>
PyObject*operator()(R(*f)(A0,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11),PyObject*args,PyObject*keywords,P const&policies)const 
{
    return returning<R>::call(f,args,keywords,&policies);
}
template<class P,class R,class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8,class A9,class A10,class A11,class A12>
PyObject*operator()(R(*f)(A0,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12),PyObject*args,PyObject*keywords,P const&policies)const 
{
    return returning<R>::call(f,args,keywords,&policies);
}
template<class P,class R,class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8,class A9,class A10,class A11,class A12,class A13>
PyObject*operator()(R(*f)(A0,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13),PyObject*args,PyObject*keywords,P const&policies)const 
{
    return returning<R>::call(f,args,keywords,&policies);
}
template<class P,class R,class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8,class A9,class A10,class A11,class A12,class A13,class A14>
PyObject*operator()(R(*f)(A0,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13,A14),PyObject*args,PyObject*keywords,P const&policies)const 
{
    return returning<R>::call(f,args,keywords,&policies);
}
 
 


template<class P,class R,class A0>
PyObject*operator()(R(A0::*f)(),PyObject*args,PyObject*keywords,P const&policies)const 
{
    return returning<R>::call(f,args,keywords,&policies);
}
template<class P,class R,class A0,class A1>
PyObject*operator()(R(A0::*f)(A1),PyObject*args,PyObject*keywords,P const&policies)const 
{
    return returning<R>::call(f,args,keywords,&policies);
}
template<class P,class R,class A0,class A1,class A2>
PyObject*operator()(R(A0::*f)(A1,A2),PyObject*args,PyObject*keywords,P const&policies)const 
{
    return returning<R>::call(f,args,keywords,&policies);
}
template<class P,class R,class A0,class A1,class A2,class A3>
PyObject*operator()(R(A0::*f)(A1,A2,A3),PyObject*args,PyObject*keywords,P const&policies)const 
{
    return returning<R>::call(f,args,keywords,&policies);
}
template<class P,class R,class A0,class A1,class A2,class A3,class A4>
PyObject*operator()(R(A0::*f)(A1,A2,A3,A4),PyObject*args,PyObject*keywords,P const&policies)const 
{
    return returning<R>::call(f,args,keywords,&policies);
}
template<class P,class R,class A0,class A1,class A2,class A3,class A4,class A5>
PyObject*operator()(R(A0::*f)(A1,A2,A3,A4,A5),PyObject*args,PyObject*keywords,P const&policies)const 
{
    return returning<R>::call(f,args,keywords,&policies);
}
template<class P,class R,class A0,class A1,class A2,class A3,class A4,class A5,class A6>
PyObject*operator()(R(A0::*f)(A1,A2,A3,A4,A5,A6),PyObject*args,PyObject*keywords,P const&policies)const 
{
    return returning<R>::call(f,args,keywords,&policies);
}
template<class P,class R,class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7>
PyObject*operator()(R(A0::*f)(A1,A2,A3,A4,A5,A6,A7),PyObject*args,PyObject*keywords,P const&policies)const 
{
    return returning<R>::call(f,args,keywords,&policies);
}
template<class P,class R,class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8>
PyObject*operator()(R(A0::*f)(A1,A2,A3,A4,A5,A6,A7,A8),PyObject*args,PyObject*keywords,P const&policies)const 
{
    return returning<R>::call(f,args,keywords,&policies);
}
template<class P,class R,class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8,class A9>
PyObject*operator()(R(A0::*f)(A1,A2,A3,A4,A5,A6,A7,A8,A9),PyObject*args,PyObject*keywords,P const&policies)const 
{
    return returning<R>::call(f,args,keywords,&policies);
}
template<class P,class R,class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8,class A9,class A10>
PyObject*operator()(R(A0::*f)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10),PyObject*args,PyObject*keywords,P const&policies)const 
{
    return returning<R>::call(f,args,keywords,&policies);
}
template<class P,class R,class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8,class A9,class A10,class A11>
PyObject*operator()(R(A0::*f)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11),PyObject*args,PyObject*keywords,P const&policies)const 
{
    return returning<R>::call(f,args,keywords,&policies);
}
template<class P,class R,class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8,class A9,class A10,class A11,class A12>
PyObject*operator()(R(A0::*f)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12),PyObject*args,PyObject*keywords,P const&policies)const 
{
    return returning<R>::call(f,args,keywords,&policies);
}
template<class P,class R,class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8,class A9,class A10,class A11,class A12,class A13>
PyObject*operator()(R(A0::*f)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13),PyObject*args,PyObject*keywords,P const&policies)const 
{
    return returning<R>::call(f,args,keywords,&policies);
}
template<class P,class R,class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8,class A9,class A10,class A11,class A12,class A13,class A14>
PyObject*operator()(R(A0::*f)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13,A14),PyObject*args,PyObject*keywords,P const&policies)const 
{
    return returning<R>::call(f,args,keywords,&policies);
}
template<class P,class R,class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8,class A9,class A10,class A11,class A12,class A13,class A14,class A15>
PyObject*operator()(R(A0::*f)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13,A14,A15),PyObject*args,PyObject*keywords,P const&policies)const 
{
    return returning<R>::call(f,args,keywords,&policies);
}
template<class P,class R,class A0>
PyObject*operator()(R(A0::*f)()const,PyObject*args,PyObject*keywords,P const&policies)const 
{
    return returning<R>::call(f,args,keywords,&policies);
}
template<class P,class R,class A0,class A1>
PyObject*operator()(R(A0::*f)(A1)const,PyObject*args,PyObject*keywords,P const&policies)const 
{
    return returning<R>::call(f,args,keywords,&policies);
}
template<class P,class R,class A0,class A1,class A2>
PyObject*operator()(R(A0::*f)(A1,A2)const,PyObject*args,PyObject*keywords,P const&policies)const 
{
    return returning<R>::call(f,args,keywords,&policies);
}
template<class P,class R,class A0,class A1,class A2,class A3>
PyObject*operator()(R(A0::*f)(A1,A2,A3)const,PyObject*args,PyObject*keywords,P const&policies)const 
{
    return returning<R>::call(f,args,keywords,&policies);
}
template<class P,class R,class A0,class A1,class A2,class A3,class A4>
PyObject*operator()(R(A0::*f)(A1,A2,A3,A4)const,PyObject*args,PyObject*keywords,P const&policies)const 
{
    return returning<R>::call(f,args,keywords,&policies);
}
template<class P,class R,class A0,class A1,class A2,class A3,class A4,class A5>
PyObject*operator()(R(A0::*f)(A1,A2,A3,A4,A5)const,PyObject*args,PyObject*keywords,P const&policies)const 
{
    return returning<R>::call(f,args,keywords,&policies);
}
template<class P,class R,class A0,class A1,class A2,class A3,class A4,class A5,class A6>
PyObject*operator()(R(A0::*f)(A1,A2,A3,A4,A5,A6)const,PyObject*args,PyObject*keywords,P const&policies)const 
{
    return returning<R>::call(f,args,keywords,&policies);
}
template<class P,class R,class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7>
PyObject*operator()(R(A0::*f)(A1,A2,A3,A4,A5,A6,A7)const,PyObject*args,PyObject*keywords,P const&policies)const 
{
    return returning<R>::call(f,args,keywords,&policies);
}
template<class P,class R,class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8>
PyObject*operator()(R(A0::*f)(A1,A2,A3,A4,A5,A6,A7,A8)const,PyObject*args,PyObject*keywords,P const&policies)const 
{
    return returning<R>::call(f,args,keywords,&policies);
}
template<class P,class R,class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8,class A9>
PyObject*operator()(R(A0::*f)(A1,A2,A3,A4,A5,A6,A7,A8,A9)const,PyObject*args,PyObject*keywords,P const&policies)const 
{
    return returning<R>::call(f,args,keywords,&policies);
}
template<class P,class R,class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8,class A9,class A10>
PyObject*operator()(R(A0::*f)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10)const,PyObject*args,PyObject*keywords,P const&policies)const 
{
    return returning<R>::call(f,args,keywords,&policies);
}
template<class P,class R,class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8,class A9,class A10,class A11>
PyObject*operator()(R(A0::*f)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11)const,PyObject*args,PyObject*keywords,P const&policies)const 
{
    return returning<R>::call(f,args,keywords,&policies);
}
template<class P,class R,class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8,class A9,class A10,class A11,class A12>
PyObject*operator()(R(A0::*f)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12)const,PyObject*args,PyObject*keywords,P const&policies)const 
{
    return returning<R>::call(f,args,keywords,&policies);
}
template<class P,class R,class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8,class A9,class A10,class A11,class A12,class A13>
PyObject*operator()(R(A0::*f)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13)const,PyObject*args,PyObject*keywords,P const&policies)const 
{
    return returning<R>::call(f,args,keywords,&policies);
}
template<class P,class R,class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8,class A9,class A10,class A11,class A12,class A13,class A14>
PyObject*operator()(R(A0::*f)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13,A14)const,PyObject*args,PyObject*keywords,P const&policies)const 
{
    return returning<R>::call(f,args,keywords,&policies);
}
template<class P,class R,class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8,class A9,class A10,class A11,class A12,class A13,class A14,class A15>
PyObject*operator()(R(A0::*f)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13,A14,A15)const,PyObject*args,PyObject*keywords,P const&policies)const 
{
    return returning<R>::call(f,args,keywords,&policies);
}
template<class P,class R,class A0>
PyObject*operator()(R(A0::*f)()volatile,PyObject*args,PyObject*keywords,P const&policies)const 
{
    return returning<R>::call(f,args,keywords,&policies);
}
template<class P,class R,class A0,class A1>
PyObject*operator()(R(A0::*f)(A1)volatile,PyObject*args,PyObject*keywords,P const&policies)const 
{
    return returning<R>::call(f,args,keywords,&policies);
}
template<class P,class R,class A0,class A1,class A2>
PyObject*operator()(R(A0::*f)(A1,A2)volatile,PyObject*args,PyObject*keywords,P const&policies)const 
{
    return returning<R>::call(f,args,keywords,&policies);
}
template<class P,class R,class A0,class A1,class A2,class A3>
PyObject*operator()(R(A0::*f)(A1,A2,A3)volatile,PyObject*args,PyObject*keywords,P const&policies)const 
{
    return returning<R>::call(f,args,keywords,&policies);
}
template<class P,class R,class A0,class A1,class A2,class A3,class A4>
PyObject*operator()(R(A0::*f)(A1,A2,A3,A4)volatile,PyObject*args,PyObject*keywords,P const&policies)const 
{
    return returning<R>::call(f,args,keywords,&policies);
}
template<class P,class R,class A0,class A1,class A2,class A3,class A4,class A5>
PyObject*operator()(R(A0::*f)(A1,A2,A3,A4,A5)volatile,PyObject*args,PyObject*keywords,P const&policies)const 
{
    return returning<R>::call(f,args,keywords,&policies);
}
template<class P,class R,class A0,class A1,class A2,class A3,class A4,class A5,class A6>
PyObject*operator()(R(A0::*f)(A1,A2,A3,A4,A5,A6)volatile,PyObject*args,PyObject*keywords,P const&policies)const 
{
    return returning<R>::call(f,args,keywords,&policies);
}
template<class P,class R,class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7>
PyObject*operator()(R(A0::*f)(A1,A2,A3,A4,A5,A6,A7)volatile,PyObject*args,PyObject*keywords,P const&policies)const 
{
    return returning<R>::call(f,args,keywords,&policies);
}
template<class P,class R,class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8>
PyObject*operator()(R(A0::*f)(A1,A2,A3,A4,A5,A6,A7,A8)volatile,PyObject*args,PyObject*keywords,P const&policies)const 
{
    return returning<R>::call(f,args,keywords,&policies);
}
template<class P,class R,class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8,class A9>
PyObject*operator()(R(A0::*f)(A1,A2,A3,A4,A5,A6,A7,A8,A9)volatile,PyObject*args,PyObject*keywords,P const&policies)const 
{
    return returning<R>::call(f,args,keywords,&policies);
}
template<class P,class R,class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8,class A9,class A10>
PyObject*operator()(R(A0::*f)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10)volatile,PyObject*args,PyObject*keywords,P const&policies)const 
{
    return returning<R>::call(f,args,keywords,&policies);
}
template<class P,class R,class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8,class A9,class A10,class A11>
PyObject*operator()(R(A0::*f)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11)volatile,PyObject*args,PyObject*keywords,P const&policies)const 
{
    return returning<R>::call(f,args,keywords,&policies);
}
template<class P,class R,class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8,class A9,class A10,class A11,class A12>
PyObject*operator()(R(A0::*f)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12)volatile,PyObject*args,PyObject*keywords,P const&policies)const 
{
    return returning<R>::call(f,args,keywords,&policies);
}
template<class P,class R,class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8,class A9,class A10,class A11,class A12,class A13>
PyObject*operator()(R(A0::*f)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13)volatile,PyObject*args,PyObject*keywords,P const&policies)const 
{
    return returning<R>::call(f,args,keywords,&policies);
}
template<class P,class R,class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8,class A9,class A10,class A11,class A12,class A13,class A14>
PyObject*operator()(R(A0::*f)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13,A14)volatile,PyObject*args,PyObject*keywords,P const&policies)const 
{
    return returning<R>::call(f,args,keywords,&policies);
}
template<class P,class R,class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8,class A9,class A10,class A11,class A12,class A13,class A14,class A15>
PyObject*operator()(R(A0::*f)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13,A14,A15)volatile,PyObject*args,PyObject*keywords,P const&policies)const 
{
    return returning<R>::call(f,args,keywords,&policies);
}
template<class P,class R,class A0>
PyObject*operator()(R(A0::*f)()const volatile,PyObject*args,PyObject*keywords,P const&policies)const 
{
    return returning<R>::call(f,args,keywords,&policies);
}
template<class P,class R,class A0,class A1>
PyObject*operator()(R(A0::*f)(A1)const volatile,PyObject*args,PyObject*keywords,P const&policies)const 
{
    return returning<R>::call(f,args,keywords,&policies);
}
template<class P,class R,class A0,class A1,class A2>
PyObject*operator()(R(A0::*f)(A1,A2)const volatile,PyObject*args,PyObject*keywords,P const&policies)const 
{
    return returning<R>::call(f,args,keywords,&policies);
}
template<class P,class R,class A0,class A1,class A2,class A3>
PyObject*operator()(R(A0::*f)(A1,A2,A3)const volatile,PyObject*args,PyObject*keywords,P const&policies)const 
{
    return returning<R>::call(f,args,keywords,&policies);
}
template<class P,class R,class A0,class A1,class A2,class A3,class A4>
PyObject*operator()(R(A0::*f)(A1,A2,A3,A4)const volatile,PyObject*args,PyObject*keywords,P const&policies)const 
{
    return returning<R>::call(f,args,keywords,&policies);
}
template<class P,class R,class A0,class A1,class A2,class A3,class A4,class A5>
PyObject*operator()(R(A0::*f)(A1,A2,A3,A4,A5)const volatile,PyObject*args,PyObject*keywords,P const&policies)const 
{
    return returning<R>::call(f,args,keywords,&policies);
}
template<class P,class R,class A0,class A1,class A2,class A3,class A4,class A5,class A6>
PyObject*operator()(R(A0::*f)(A1,A2,A3,A4,A5,A6)const volatile,PyObject*args,PyObject*keywords,P const&policies)const 
{
    return returning<R>::call(f,args,keywords,&policies);
}
template<class P,class R,class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7>
PyObject*operator()(R(A0::*f)(A1,A2,A3,A4,A5,A6,A7)const volatile,PyObject*args,PyObject*keywords,P const&policies)const 
{
    return returning<R>::call(f,args,keywords,&policies);
}
template<class P,class R,class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8>
PyObject*operator()(R(A0::*f)(A1,A2,A3,A4,A5,A6,A7,A8)const volatile,PyObject*args,PyObject*keywords,P const&policies)const 
{
    return returning<R>::call(f,args,keywords,&policies);
}
template<class P,class R,class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8,class A9>
PyObject*operator()(R(A0::*f)(A1,A2,A3,A4,A5,A6,A7,A8,A9)const volatile,PyObject*args,PyObject*keywords,P const&policies)const 
{
    return returning<R>::call(f,args,keywords,&policies);
}
template<class P,class R,class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8,class A9,class A10>
PyObject*operator()(R(A0::*f)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10)const volatile,PyObject*args,PyObject*keywords,P const&policies)const 
{
    return returning<R>::call(f,args,keywords,&policies);
}
template<class P,class R,class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8,class A9,class A10,class A11>
PyObject*operator()(R(A0::*f)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11)const volatile,PyObject*args,PyObject*keywords,P const&policies)const 
{
    return returning<R>::call(f,args,keywords,&policies);
}
template<class P,class R,class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8,class A9,class A10,class A11,class A12>
PyObject*operator()(R(A0::*f)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12)const volatile,PyObject*args,PyObject*keywords,P const&policies)const 
{
    return returning<R>::call(f,args,keywords,&policies);
}
template<class P,class R,class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8,class A9,class A10,class A11,class A12,class A13>
PyObject*operator()(R(A0::*f)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13)const volatile,PyObject*args,PyObject*keywords,P const&policies)const 
{
    return returning<R>::call(f,args,keywords,&policies);
}
template<class P,class R,class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8,class A9,class A10,class A11,class A12,class A13,class A14>
PyObject*operator()(R(A0::*f)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13,A14)const volatile,PyObject*args,PyObject*keywords,P const&policies)const 
{
    return returning<R>::call(f,args,keywords,&policies);
}
template<class P,class R,class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8,class A9,class A10,class A11,class A12,class A13,class A14,class A15>
PyObject*operator()(R(A0::*f)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13,A14,A15)const volatile,PyObject*args,PyObject*keywords,P const&policies)const 
{
    return returning<R>::call(f,args,keywords,&policies);
}
#endif // CALLER_DWA2002410_HPP
