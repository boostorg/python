// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef CALL_DWA2002411_HPP
# define CALL_DWA2002411_HPP

# include <boost/python/converter/callback.hpp>
# include <boost/python/detail/preprocessor.hpp>
# include <boost/preprocessor/comma_if.hpp>
# include <boost/preprocessor/enum.hpp>
# include <boost/preprocessor/enum_params.hpp>
# include <boost/preprocessor/repeat.hpp>
# include <boost/preprocessor/cat.hpp>
# include <boost/type.hpp>

namespace boost { namespace python { 

# ifndef BOOST_PYTHON_GENERATE_CODE
#  include <boost/python/preprocessed/call.hpp>
# endif

# define BOOST_PYTHON_CALL_FUNCTION(nargs,ignored)                              \
template <                                                                      \
    class R                                                                     \
    BOOST_PP_COMMA_IF(nargs) BOOST_PP_ENUM_PARAMS(nargs, class A)               \
    >                                                                           \
typename converter::callback_from_python<R>::result_type                        \
call(PyObject* callable                                                         \
     BOOST_PP_COMMA_IF(nargs) BOOST_PYTHON_ENUM_PARAMS2(nargs, (A,const& a))    \
   , boost::type<R>* = 0                                                        \
    )                                                                           \
{                                                                               \
    converter::callback_from_python<R> converter;                               \
    return converter(                                                           \
        PyEval_CallFunction(                                                    \
            callable                                                            \
            , const_cast<char*>(BOOST_PYTHON_ARG_STRING(nargs))                 \
            BOOST_PP_COMMA_IF(nargs)                                            \
            BOOST_PP_ENUM(nargs,BOOST_PYTHON_CALLBACK_TO_PYTHON_GET,nil)        \
            ));                                                                 \
}

BOOST_PYTHON_REPEAT_ARITY_2ND(BOOST_PYTHON_CALL_FUNCTION,data)

}} // namespace boost::python

#endif // CALL_DWA2002411_HPP
