// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef CALL_PP_DWA2002411_HPP
# define CALL_PP_DWA2002411_HPP

call(PyObject*self)
    :m_result(
        PyEval_CallFunction(self,const_cast<char*>("(" ")")))
{
 
}
template<class A0>
call(PyObject*self,A0 const&a0)
    :m_result(
        PyEval_CallFunction(self,const_cast<char*>("(" "O" ")"),
                            converter::callback_to_python<A0>(a0).get()))
{
 
}
template<class A0,class A1>
call(PyObject*self,A0 const&a0,A1 const&a1)
    :m_result(
        PyEval_CallFunction(self,const_cast<char*>("(" "O" "O" ")"),
                            converter::callback_to_python<A0>(a0).get(),
                            converter::callback_to_python<A1>(a1).get()))
{
 
}
template<class A0,class A1,class A2>
call(PyObject*self,A0 const&a0,A1 const&a1,A2 const&a2)
    :m_result(
        PyEval_CallFunction(self,const_cast<char*>("(" "O" "O" "O" ")"),
                            converter::callback_to_python<A0>(a0).get(),
                            converter::callback_to_python<A1>(a1).get(),
                            converter::callback_to_python<A2>(a2).get()))
{
 
}
template<class A0,class A1,class A2,class A3>
call(PyObject*self,A0 const&a0,A1 const&a1,A2 const&a2,A3 const&a3)
    :m_result(
        PyEval_CallFunction(self,const_cast<char*>("(" "O" "O" "O" "O" ")"),
                            converter::callback_to_python<A0>(a0).get(),
                            converter::callback_to_python<A1>(a1).get(),
                            converter::callback_to_python<A2>(a2).get(),
                            converter::callback_to_python<A3>(a3).get()))
{
 
}
template<class A0,class A1,class A2,class A3,class A4>
call(PyObject*self,A0 const&a0,A1 const&a1,A2 const&a2,A3 const&a3,A4 const&a4)
    :m_result(
        PyEval_CallFunction(self,const_cast<char*>("(" "O" "O" "O" "O" "O" ")"),
                            converter::callback_to_python<A0>(a0).get(),
                            converter::callback_to_python<A1>(a1).get(),
                            converter::callback_to_python<A2>(a2).get(),
                            converter::callback_to_python<A3>(a3).get(),
                            converter::callback_to_python<A4>(a4).get()))
{
 
}
template<class A0,class A1,class A2,class A3,class A4,class A5>
call(PyObject*self,A0 const&a0,A1 const&a1,A2 const&a2,A3 const&a3,A4 const&a4,A5 const&a5)
    :m_result(
        PyEval_CallFunction(self,const_cast<char*>("(" "O" "O" "O" "O" "O" "O" ")"),
                            converter::callback_to_python<A0>(a0).get(),
                            converter::callback_to_python<A1>(a1).get(),
                            converter::callback_to_python<A2>(a2).get(),
                            converter::callback_to_python<A3>(a3).get(),
                            converter::callback_to_python<A4>(a4).get(),
                            converter::callback_to_python<A5>(a5).get()))
{
 
}
template<class A0,class A1,class A2,class A3,class A4,class A5,class A6>
call(PyObject*self,A0 const&a0,A1 const&a1,A2 const&a2,A3 const&a3,A4 const&a4,A5 const&a5,A6 const&a6)
    :m_result(
        PyEval_CallFunction(self,const_cast<char*>("(" "O" "O" "O" "O" "O" "O" "O" ")"),
                            converter::callback_to_python<A0>(a0).get(),
                            converter::callback_to_python<A1>(a1).get(),
                            converter::callback_to_python<A2>(a2).get(),
                            converter::callback_to_python<A3>(a3).get(),
                            converter::callback_to_python<A4>(a4).get(),
                            converter::callback_to_python<A5>(a5).get(),
                            converter::callback_to_python<A6>(a6).get()))
{
 
}
template<class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7>
call(PyObject*self,A0 const&a0,A1 const&a1,A2 const&a2,A3 const&a3,A4 const&a4,A5 const&a5,A6 const&a6,A7 const&a7)
    :m_result(
        PyEval_CallFunction(self,const_cast<char*>("(" "O" "O" "O" "O" "O" "O" "O" "O" ")"),
                            converter::callback_to_python<A0>(a0).get(),
                            converter::callback_to_python<A1>(a1).get(),
                            converter::callback_to_python<A2>(a2).get(),
                            converter::callback_to_python<A3>(a3).get(),
                            converter::callback_to_python<A4>(a4).get(),
                            converter::callback_to_python<A5>(a5).get(),
                            converter::callback_to_python<A6>(a6).get(),
                            converter::callback_to_python<A7>(a7).get()))
{
 
}
template<class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8>
call(PyObject*self,A0 const&a0,A1 const&a1,A2 const&a2,A3 const&a3,A4 const&a4,A5 const&a5,A6 const&a6,A7 const&a7,A8 const&a8)
    :m_result(
        PyEval_CallFunction(self,const_cast<char*>("(" "O" "O" "O" "O" "O" "O" "O" "O" "O" ")"),
                            converter::callback_to_python<A0>(a0).get(),
                            converter::callback_to_python<A1>(a1).get(),
                            converter::callback_to_python<A2>(a2).get(),
                            converter::callback_to_python<A3>(a3).get(),
                            converter::callback_to_python<A4>(a4).get(),
                            converter::callback_to_python<A5>(a5).get(),
                            converter::callback_to_python<A6>(a6).get(),
                            converter::callback_to_python<A7>(a7).get(),
                            converter::callback_to_python<A8>(a8).get()
            ))
{

} 

#endif // CALL_PP_DWA2002411_HPP
