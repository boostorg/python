//Copyright David Abrahams 2002.Permission to copy,use,
//modify,sell and distribute this software is granted provided this
//copyright notice appears in all copies.This software is provided
//"as is" without express or implied warranty,and with no claim as
//to its suitability for any purpose.
#ifndef CALL_METHOD_PP_DWA2002411_HPP
# define CALL_METHOD_PP_DWA2002411_HPP

template<class R>typename 
converter::callback_from_python<R>::result_type 
call_method(PyObject*self,char const*name,boost::type<R>* =0)
{
 
    converter::callback_from_python<R>converter;
    return converter(
        PyEval_CallMethod(self,const_cast<char*>(name),const_cast<char*>("(" ")")));
}
template<class R,class A0>typename 
converter::callback_from_python<R>::result_type 
call_method(PyObject*self,char const*name,A0 const&a0,boost::type<R>* =0)
{
 
    converter::callback_from_python<R>converter;
    return converter(
        PyEval_CallMethod(self,const_cast<char*>(name),const_cast<char*>("(" "O" ")"),
                            converter::callback_to_python<A0>(a0).get()));
}
template<class R,class A0,class A1>typename 
converter::callback_from_python<R>::result_type 
call_method(PyObject*self,char const*name,A0 const&a0,A1 const&a1,boost::type<R>* =0)
{
 
    converter::callback_from_python<R>converter;
    return converter(
        PyEval_CallMethod(self,const_cast<char*>(name),const_cast<char*>("(" "O" "O" ")"),
                            converter::callback_to_python<A0>(a0).get(),
                            converter::callback_to_python<A1>(a1).get()));
}
template<class R,class A0,class A1,class A2>typename 
converter::callback_from_python<R>::result_type 
call_method(PyObject*self,char const*name,A0 const&a0,A1 const&a1,A2 const&a2,boost::type<R>* =0)
{
 
    converter::callback_from_python<R>converter;
    return converter(
        PyEval_CallMethod(self,const_cast<char*>(name),const_cast<char*>("(" "O" "O" "O" ")"),
                            converter::callback_to_python<A0>(a0).get(),
                            converter::callback_to_python<A1>(a1).get(),
                            converter::callback_to_python<A2>(a2).get()));
}
template<class R,class A0,class A1,class A2,class A3>typename 
converter::callback_from_python<R>::result_type 
call_method(PyObject*self,char const*name,A0 const&a0,A1 const&a1,A2 const&a2,A3 const&a3,boost::type<R>* =0)
{
 
    converter::callback_from_python<R>converter;
    return converter(
        PyEval_CallMethod(self,const_cast<char*>(name),const_cast<char*>("(" "O" "O" "O" "O" ")"),
                            converter::callback_to_python<A0>(a0).get(),
                            converter::callback_to_python<A1>(a1).get(),
                            converter::callback_to_python<A2>(a2).get(),
                            converter::callback_to_python<A3>(a3).get()));
}
template<class R,class A0,class A1,class A2,class A3,class A4>typename 
converter::callback_from_python<R>::result_type 
call_method(PyObject*self,char const*name,A0 const&a0,A1 const&a1,A2 const&a2,A3 const&a3,A4 const&a4,boost::type<R>* =0)
{
 
    converter::callback_from_python<R>converter;
    return converter(
        PyEval_CallMethod(self,const_cast<char*>(name),const_cast<char*>("(" "O" "O" "O" "O" "O" ")"),
                            converter::callback_to_python<A0>(a0).get(),
                            converter::callback_to_python<A1>(a1).get(),
                            converter::callback_to_python<A2>(a2).get(),
                            converter::callback_to_python<A3>(a3).get(),
                            converter::callback_to_python<A4>(a4).get()));
}
template<class R,class A0,class A1,class A2,class A3,class A4,class A5>typename 
converter::callback_from_python<R>::result_type 
call_method(PyObject*self,char const*name,A0 const&a0,A1 const&a1,A2 const&a2,A3 const&a3,A4 const&a4,A5 const&a5,boost::type<R>* =0)
{
 
    converter::callback_from_python<R>converter;
    return converter(
        PyEval_CallMethod(self,const_cast<char*>(name),const_cast<char*>("(" "O" "O" "O" "O" "O" "O" ")"),
                            converter::callback_to_python<A0>(a0).get(),
                            converter::callback_to_python<A1>(a1).get(),
                            converter::callback_to_python<A2>(a2).get(),
                            converter::callback_to_python<A3>(a3).get(),
                            converter::callback_to_python<A4>(a4).get(),
                            converter::callback_to_python<A5>(a5).get()));
}
template<class R,class A0,class A1,class A2,class A3,class A4,class A5,class A6>typename 
converter::callback_from_python<R>::result_type 
call_method(PyObject*self,char const*name,A0 const&a0,A1 const&a1,A2 const&a2,A3 const&a3,A4 const&a4,A5 const&a5,A6 const&a6,boost::type<R>* =0)
{
 
    converter::callback_from_python<R>converter;
    return converter(
        PyEval_CallMethod(self,const_cast<char*>(name),const_cast<char*>("(" "O" "O" "O" "O" "O" "O" "O" ")"),
                            converter::callback_to_python<A0>(a0).get(),
                            converter::callback_to_python<A1>(a1).get(),
                            converter::callback_to_python<A2>(a2).get(),
                            converter::callback_to_python<A3>(a3).get(),
                            converter::callback_to_python<A4>(a4).get(),
                            converter::callback_to_python<A5>(a5).get(),
                            converter::callback_to_python<A6>(a6).get()));
}
template<class R,class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7>typename 
converter::callback_from_python<R>::result_type 
call_method(PyObject*self,char const*name,A0 const&a0,A1 const&a1,A2 const&a2,A3 const&a3,A4 const&a4,A5 const&a5,A6 const&a6,A7 const&a7,boost::type<R>* =0)
{
 
    converter::callback_from_python<R>converter;
    return converter(
        PyEval_CallMethod(self,const_cast<char*>(name),const_cast<char*>("(" "O" "O" "O" "O" "O" "O" "O" "O" ")"),
                            converter::callback_to_python<A0>(a0).get(),
                            converter::callback_to_python<A1>(a1).get(),
                            converter::callback_to_python<A2>(a2).get(),
                            converter::callback_to_python<A3>(a3).get(),
                            converter::callback_to_python<A4>(a4).get(),
                            converter::callback_to_python<A5>(a5).get(),
                            converter::callback_to_python<A6>(a6).get(),
                            converter::callback_to_python<A7>(a7).get()));
}
template<class R,class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8>typename 
converter::callback_from_python<R>::result_type 
call_method(PyObject*self,char const*name,A0 const&a0,A1 const&a1,A2 const&a2,A3 const&a3,A4 const&a4,A5 const&a5,A6 const&a6,A7 const&a7,A8 const&a8,boost::type<R>* =0)
{
 
    converter::callback_from_python<R>converter;
    return converter(
        PyEval_CallMethod(self,const_cast<char*>(name),const_cast<char*>("(" "O" "O" "O" "O" "O" "O" "O" "O" "O" ")"),
                            converter::callback_to_python<A0>(a0).get(),
                            converter::callback_to_python<A1>(a1).get(),
                            converter::callback_to_python<A2>(a2).get(),
                            converter::callback_to_python<A3>(a3).get(),
                            converter::callback_to_python<A4>(a4).get(),
                            converter::callback_to_python<A5>(a5).get(),
                            converter::callback_to_python<A6>(a6).get(),
                            converter::callback_to_python<A7>(a7).get(),
                            converter::callback_to_python<A8>(a8).get()));
}
 
 
#endif//
CALL_METHOD_PP_DWA2002411_HPP
