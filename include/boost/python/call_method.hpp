// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef CALL_METHOD_DWA2002411_HPP
# define CALL_METHOD_DWA2002411_HPP

# include <boost/python/converter/arg_to_python.hpp>
# include <boost/python/converter/return_from_python.hpp>
# include <boost/python/detail/preprocessor.hpp>
# include <boost/preprocessor/comma_if.hpp>
# include <boost/preprocessor/enum.hpp>
# include <boost/preprocessor/enum_params.hpp>
# include <boost/preprocessor/repeat.hpp>
# include <boost/preprocessor/cat.hpp>
# include <boost/python/detail/void_return.hpp>
# include <boost/type.hpp>

namespace boost { namespace python { 

# ifndef BOOST_PYTHON_GENERATE_CODE
#  include <boost/python/preprocessed/call_method.hpp>
# endif

# define BOOST_PYTHON_CALL_METHOD_FUNCTION(nargs,ignored)                       \
template <                                                                      \
    class R                                                                     \
    BOOST_PP_COMMA_IF(nargs) BOOST_PP_ENUM_PARAMS(nargs, class A)               \
    >                                                                           \
typename detail::returnable<R>::type                                            \
call_method(PyObject* self, char const* name                                    \
     BOOST_PP_COMMA_IF(nargs) BOOST_PYTHON_ENUM_PARAMS2(nargs, (A,const& a))    \
   , boost::type<R>* = 0                                                        \
    )                                                                           \
{                                                                               \
    converter::return_from_python<R> converter;                                 \
    return converter(                                                           \
        PyEval_CallMethod(                                                      \
            self                                                                \
            , const_cast<char*>(name)                                           \
            , const_cast<char*>(BOOST_PYTHON_ARG_STRING(nargs))                 \
            BOOST_PP_COMMA_IF(nargs)                                            \
            BOOST_PP_ENUM(nargs,BOOST_PYTHON_ARG_TO_PYTHON_GET,nil)             \
            ));                                                                 \
}

BOOST_PYTHON_REPEAT_ARITY_2ND(BOOST_PYTHON_CALL_METHOD_FUNCTION,data)

}} // namespace boost::python

#endif // CALL_METHOD_DWA2002411_HPP
