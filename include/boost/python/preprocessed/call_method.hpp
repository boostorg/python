//Copyright David Abrahams 2002.Permission to copy,use,
//modify,sell and distribute this software is granted provided this
//copyright notice appears in all copies.This software is provided
//"as is" without express or implied warranty,and with no claim as
//to its suitability for any purpose.
#ifndef CALL_METHOD_PP_DWA2002411_HPP
# define CALL_METHOD_PP_DWA2002411_HPP

// emacs commands used to pre-clean preprocessor output:
// (replace-regexp ", *converter" "\n, converter")
// (replace-string "PyEval_CallMethod(" "\nPyEval_CallMethod(\n")

template<class R>
typename detail::returnable<R>::type
call_method(PyObject*self,char const*name,boost::type<R>* =0)
{
    converter::return_from_python<R>converter;
    return converter(
        PyEval_CallMethod(
            self,const_cast<char*>(name),const_cast<char*>("(" ")")));
}
template<class R,class A0>
typename detail::returnable<R>::type
call_method(PyObject*self,char const*name,A0 const&a0,boost::type<R>* =0)
{
    converter::return_from_python<R>converter;
    return converter(
        PyEval_CallMethod(
            self,const_cast<char*>(name),const_cast<char*>("(" "O" ")")
            ,converter::arg_to_python<A0>(a0).get()));
}
template<class R,class A0,class A1>
typename detail::returnable<R>::type
call_method(PyObject*self,char const*name,A0 const&a0,A1 const&a1,boost::type<R>* =0)
{
    converter::return_from_python<R>converter;
    return converter(
        PyEval_CallMethod(
            self,const_cast<char*>(name),const_cast<char*>("(" "O" "O" ")")
            ,converter::arg_to_python<A0>(a0).get()
            ,converter::arg_to_python<A1>(a1).get()));
}
template<class R,class A0,class A1,class A2>
typename detail::returnable<R>::type
call_method(PyObject*self,char const*name,A0 const&a0,A1 const&a1,A2 const&a2,boost::type<R>* =0)
{
    converter::return_from_python<R>converter;
    return converter(
        PyEval_CallMethod(
            self,const_cast<char*>(name),const_cast<char*>("(" "O" "O" "O" ")")
            ,converter::arg_to_python<A0>(a0).get()
            ,converter::arg_to_python<A1>(a1).get()
            ,converter::arg_to_python<A2>(a2).get()));
}
template<class R,class A0,class A1,class A2,class A3>
typename detail::returnable<R>::type
call_method(PyObject*self,char const*name,A0 const&a0,A1 const&a1,A2 const&a2,A3 const&a3,boost::type<R>* =0)
{
    converter::return_from_python<R>converter;
    return converter(
        PyEval_CallMethod(
            self,const_cast<char*>(name),const_cast<char*>("(" "O" "O" "O" "O" ")")
            ,converter::arg_to_python<A0>(a0).get()
            ,converter::arg_to_python<A1>(a1).get()
            ,converter::arg_to_python<A2>(a2).get()
            ,converter::arg_to_python<A3>(a3).get()));
}
template<class R,class A0,class A1,class A2,class A3,class A4>
typename detail::returnable<R>::type
call_method(PyObject*self,char const*name,A0 const&a0,A1 const&a1,A2 const&a2,A3 const&a3,A4 const&a4,boost::type<R>* =0)
{
    converter::return_from_python<R>converter;
    return converter(
        PyEval_CallMethod(
            self,const_cast<char*>(name),const_cast<char*>("(" "O" "O" "O" "O" "O" ")")
            ,converter::arg_to_python<A0>(a0).get()
            ,converter::arg_to_python<A1>(a1).get()
            ,converter::arg_to_python<A2>(a2).get()
            ,converter::arg_to_python<A3>(a3).get()
            ,converter::arg_to_python<A4>(a4).get()));
}
template<class R,class A0,class A1,class A2,class A3,class A4,class A5>
typename detail::returnable<R>::type
call_method(PyObject*self,char const*name,A0 const&a0,A1 const&a1,A2 const&a2,A3 const&a3,A4 const&a4,A5 const&a5,boost::type<R>* =0)
{
    converter::return_from_python<R>converter;
    return converter(
        PyEval_CallMethod(
            self,const_cast<char*>(name),const_cast<char*>("(" "O" "O" "O" "O" "O" "O" ")")
            ,converter::arg_to_python<A0>(a0).get()
            ,converter::arg_to_python<A1>(a1).get()
            ,converter::arg_to_python<A2>(a2).get()
            ,converter::arg_to_python<A3>(a3).get()
            ,converter::arg_to_python<A4>(a4).get()
            ,converter::arg_to_python<A5>(a5).get()));
}
template<class R,class A0,class A1,class A2,class A3,class A4,class A5,class A6>
typename detail::returnable<R>::type
call_method(PyObject*self,char const*name,A0 const&a0,A1 const&a1,A2 const&a2,A3 const&a3,A4 const&a4,A5 const&a5,A6 const&a6,boost::type<R>* =0)
{
    converter::return_from_python<R>converter;
    return converter(
        PyEval_CallMethod(
            self,const_cast<char*>(name),const_cast<char*>("(" "O" "O" "O" "O" "O" "O" "O" ")")
            ,converter::arg_to_python<A0>(a0).get()
            ,converter::arg_to_python<A1>(a1).get()
            ,converter::arg_to_python<A2>(a2).get()
            ,converter::arg_to_python<A3>(a3).get()
            ,converter::arg_to_python<A4>(a4).get()
            ,converter::arg_to_python<A5>(a5).get()
            ,converter::arg_to_python<A6>(a6).get()));
}
template<class R,class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7>
typename detail::returnable<R>::type
call_method(PyObject*self,char const*name,A0 const&a0,A1 const&a1,A2 const&a2,A3 const&a3,A4 const&a4,A5 const&a5,A6 const&a6,A7 const&a7,boost::type<R>* =0)
{
    converter::return_from_python<R>converter;
    return converter(
        PyEval_CallMethod(
            self,const_cast<char*>(name),const_cast<char*>("(" "O" "O" "O" "O" "O" "O" "O" "O" ")")
            ,converter::arg_to_python<A0>(a0).get()
            ,converter::arg_to_python<A1>(a1).get()
            ,converter::arg_to_python<A2>(a2).get()
            ,converter::arg_to_python<A3>(a3).get()
            ,converter::arg_to_python<A4>(a4).get()
            ,converter::arg_to_python<A5>(a5).get()
            ,converter::arg_to_python<A6>(a6).get()
            ,converter::arg_to_python<A7>(a7).get()));
}
template<class R,class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8>
typename detail::returnable<R>::type
call_method(PyObject*self,char const*name,A0 const&a0,A1 const&a1,A2 const&a2,A3 const&a3,A4 const&a4,A5 const&a5,A6 const&a6,A7 const&a7,A8 const&a8,boost::type<R>* =0)
{
    converter::return_from_python<R>converter;
    return converter(
        PyEval_CallMethod(
            self,const_cast<char*>(name),const_cast<char*>("(" "O" "O" "O" "O" "O" "O" "O" "O" "O" ")")
            ,converter::arg_to_python<A0>(a0).get()
            ,converter::arg_to_python<A1>(a1).get()
            ,converter::arg_to_python<A2>(a2).get()
            ,converter::arg_to_python<A3>(a3).get()
            ,converter::arg_to_python<A4>(a4).get()
            ,converter::arg_to_python<A5>(a5).get()
            ,converter::arg_to_python<A6>(a6).get()
            ,converter::arg_to_python<A7>(a7).get()
            ,converter::arg_to_python<A8>(a8).get()));
}
template<class R,class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8,class A9>
typename detail::returnable<R>::type
call_method(PyObject*self,char const*name,A0 const&a0,A1 const&a1,A2 const&a2,A3 const&a3,A4 const&a4,A5 const&a5,A6 const&a6,A7 const&a7,A8 const&a8,A9 const&a9,boost::type<R>* =0)
{
    converter::return_from_python<R>converter;
    return converter(
        PyEval_CallMethod(
            self,const_cast<char*>(name),const_cast<char*>("(" "O" "O" "O" "O" "O" "O" "O" "O" "O" "O" ")")
            ,converter::arg_to_python<A0>(a0).get()
            ,converter::arg_to_python<A1>(a1).get()
            ,converter::arg_to_python<A2>(a2).get()
            ,converter::arg_to_python<A3>(a3).get()
            ,converter::arg_to_python<A4>(a4).get()
            ,converter::arg_to_python<A5>(a5).get()
            ,converter::arg_to_python<A6>(a6).get()
            ,converter::arg_to_python<A7>(a7).get()
            ,converter::arg_to_python<A8>(a8).get()
            ,converter::arg_to_python<A9>(a9).get()));
}
template<class R,class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8,class A9,class A10>
typename detail::returnable<R>::type
call_method(PyObject*self,char const*name,A0 const&a0,A1 const&a1,A2 const&a2,A3 const&a3,A4 const&a4,A5 const&a5,A6 const&a6,A7 const&a7,A8 const&a8,A9 const&a9,A10 const&a10,boost::type<R>* =0)
{
    converter::return_from_python<R>converter;
    return converter(
        PyEval_CallMethod(
            self,const_cast<char*>(name),const_cast<char*>("(" "O" "O" "O" "O" "O" "O" "O" "O" "O" "O" "O" ")")
            ,converter::arg_to_python<A0>(a0).get()
            ,converter::arg_to_python<A1>(a1).get()
            ,converter::arg_to_python<A2>(a2).get()
            ,converter::arg_to_python<A3>(a3).get()
            ,converter::arg_to_python<A4>(a4).get()
            ,converter::arg_to_python<A5>(a5).get()
            ,converter::arg_to_python<A6>(a6).get()
            ,converter::arg_to_python<A7>(a7).get()
            ,converter::arg_to_python<A8>(a8).get()
            ,converter::arg_to_python<A9>(a9).get()
            ,converter::arg_to_python<A10>(a10).get()));
}
template<class R,class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8,class A9,class A10,class A11>
typename detail::returnable<R>::type
call_method(PyObject*self,char const*name,A0 const&a0,A1 const&a1,A2 const&a2,A3 const&a3,A4 const&a4,A5 const&a5,A6 const&a6,A7 const&a7,A8 const&a8,A9 const&a9,A10 const&a10,A11 const&a11,boost::type<R>* =0)
{
    converter::return_from_python<R>converter;
    return converter(
        PyEval_CallMethod(
            self,const_cast<char*>(name),const_cast<char*>("(" "O" "O" "O" "O" "O" "O" "O" "O" "O" "O" "O" "O" ")")
            ,converter::arg_to_python<A0>(a0).get()
            ,converter::arg_to_python<A1>(a1).get()
            ,converter::arg_to_python<A2>(a2).get()
            ,converter::arg_to_python<A3>(a3).get()
            ,converter::arg_to_python<A4>(a4).get()
            ,converter::arg_to_python<A5>(a5).get()
            ,converter::arg_to_python<A6>(a6).get()
            ,converter::arg_to_python<A7>(a7).get()
            ,converter::arg_to_python<A8>(a8).get()
            ,converter::arg_to_python<A9>(a9).get()
            ,converter::arg_to_python<A10>(a10).get()
            ,converter::arg_to_python<A11>(a11).get()));
}
template<class R,class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8,class A9,class A10,class A11,class A12>
typename detail::returnable<R>::type
call_method(PyObject*self,char const*name,A0 const&a0,A1 const&a1,A2 const&a2,A3 const&a3,A4 const&a4,A5 const&a5,A6 const&a6,A7 const&a7,A8 const&a8,A9 const&a9,A10 const&a10,A11 const&a11,A12 const&a12,boost::type<R>* =0)
{
    converter::return_from_python<R>converter;
    return converter(
        PyEval_CallMethod(
            self,const_cast<char*>(name),const_cast<char*>("(" "O" "O" "O" "O" "O" "O" "O" "O" "O" "O" "O" "O" "O" ")")
            ,converter::arg_to_python<A0>(a0).get()
            ,converter::arg_to_python<A1>(a1).get()
            ,converter::arg_to_python<A2>(a2).get()
            ,converter::arg_to_python<A3>(a3).get()
            ,converter::arg_to_python<A4>(a4).get()
            ,converter::arg_to_python<A5>(a5).get()
            ,converter::arg_to_python<A6>(a6).get()
            ,converter::arg_to_python<A7>(a7).get()
            ,converter::arg_to_python<A8>(a8).get()
            ,converter::arg_to_python<A9>(a9).get()
            ,converter::arg_to_python<A10>(a10).get()
            ,converter::arg_to_python<A11>(a11).get()
            ,converter::arg_to_python<A12>(a12).get()));
}
template<class R,class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8,class A9,class A10,class A11,class A12,class A13>
typename detail::returnable<R>::type
call_method(PyObject*self,char const*name,A0 const&a0,A1 const&a1,A2 const&a2,A3 const&a3,A4 const&a4,A5 const&a5,A6 const&a6,A7 const&a7,A8 const&a8,A9 const&a9,A10 const&a10,A11 const&a11,A12 const&a12,A13 const&a13,boost::type<R>* =0)
{
    converter::return_from_python<R>converter;
    return converter(
        PyEval_CallMethod(
            self,const_cast<char*>(name),const_cast<char*>("(" "O" "O" "O" "O" "O" "O" "O" "O" "O" "O" "O" "O" "O" "O" ")")
            ,converter::arg_to_python<A0>(a0).get()
            ,converter::arg_to_python<A1>(a1).get()
            ,converter::arg_to_python<A2>(a2).get()
            ,converter::arg_to_python<A3>(a3).get()
            ,converter::arg_to_python<A4>(a4).get()
            ,converter::arg_to_python<A5>(a5).get()
            ,converter::arg_to_python<A6>(a6).get()
            ,converter::arg_to_python<A7>(a7).get()
            ,converter::arg_to_python<A8>(a8).get()
            ,converter::arg_to_python<A9>(a9).get()
            ,converter::arg_to_python<A10>(a10).get()
            ,converter::arg_to_python<A11>(a11).get()
            ,converter::arg_to_python<A12>(a12).get()
            ,converter::arg_to_python<A13>(a13).get()));
}
template<class R,class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8,class A9,class A10,class A11,class A12,class A13,class A14>
typename detail::returnable<R>::type
call_method(PyObject*self,char const*name,A0 const&a0,A1 const&a1,A2 const&a2,A3 const&a3,A4 const&a4,A5 const&a5,A6 const&a6,A7 const&a7,A8 const&a8,A9 const&a9,A10 const&a10,A11 const&a11,A12 const&a12,A13 const&a13,A14 const&a14,boost::type<R>* =0)
{
    converter::return_from_python<R>converter;
    return converter(
        PyEval_CallMethod(
            self,const_cast<char*>(name),const_cast<char*>("(" "O" "O" "O" "O" "O" "O" "O" "O" "O" "O" "O" "O" "O" "O" "O" ")")
            ,converter::arg_to_python<A0>(a0).get()
            ,converter::arg_to_python<A1>(a1).get()
            ,converter::arg_to_python<A2>(a2).get()
            ,converter::arg_to_python<A3>(a3).get()
            ,converter::arg_to_python<A4>(a4).get()
            ,converter::arg_to_python<A5>(a5).get()
            ,converter::arg_to_python<A6>(a6).get()
            ,converter::arg_to_python<A7>(a7).get()
            ,converter::arg_to_python<A8>(a8).get()
            ,converter::arg_to_python<A9>(a9).get()
            ,converter::arg_to_python<A10>(a10).get()
            ,converter::arg_to_python<A11>(a11).get()
            ,converter::arg_to_python<A12>(a12).get()
            ,converter::arg_to_python<A13>(a13).get()
            ,converter::arg_to_python<A14>(a14).get()));
}
#endif// CALL_METHOD_PP_DWA2002411_HPP
