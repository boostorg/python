//  (C) Copyright David Abrahams 2001. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
//  This work was funded in part by Lawrence Berkeley National Labs
//
//  This file generated for 5-argument member functions and 6-argument free
//  functions by gen_arg_tuple_size.python

#ifndef ARG_TUPLE_SIZE_DWA20011201_HPP
# define ARG_TUPLE_SIZE_DWA20011201_HPP

# include <boost/config.hpp>
# include <boost/python/detail/char_array.hpp>
# include <boost/python/detail/preprocessor.hpp>
# include <boost/preprocessor/comma_if.hpp>
# include <boost/preprocessor/enum_params.hpp>
# include <boost/preprocessor/cat.hpp>

namespace boost { namespace python { namespace detail {

// Computes (at compile-time) the number of elements that a Python
// argument tuple must have in order to be passed to a wrapped C++
// (member) function of the given type.
template <class F> struct arg_tuple_size;

// Include the pre-expanded version of the code
# ifndef BOOST_PYTHON_GENERATE_CODE
#  include <boost/python/preprocessed/arg_tuple_size.hpp>
# endif 

# if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

// Specializations for function pointers
#  define BOOST_PYTHON_ARG_TUPLE_SIZE_PF(args, ignored)                                         \
template <class R BOOST_PP_COMMA_IF(args) BOOST_PP_ENUM_PARAMS(args, class A)>      \
struct arg_tuple_size<BOOST_PYTHON_FN(*,0,args)>                                                \
{                                                                                               \
    BOOST_STATIC_CONSTANT(std::size_t, value = args);                                           \
};

// Specializations for member function pointers
#  define BOOST_PYTHON_ARG_TUPLE_SIZE_PMF(args, cv)             \
template <class R, BOOST_PP_ENUM_PARAMS(args, class A)>         \
struct arg_tuple_size<BOOST_PYTHON_FN(A0::*,1,args) cv()>       \
{                                                               \
    BOOST_STATIC_CONSTANT(std::size_t, value = args);           \
};

# else

// We will use the "sizeof() trick" to work around the lack of
// partial specialization in MSVC6 and its broken-ness in borland.
// See http://opensource.adobe.com  or
// http://groups.yahoo.com/group/boost/message/5441 for
// more examples

// The following helper functions are never actually called, since
// they are only used within a sizeof() expression, but the type of
// their return value is used to discriminate between various free
// and member function pointers at compile-time.

#  define BOOST_PYTHON_ARG_TUPLE_SIZE_PF(args, ignored)                         \
template <class R BOOST_PP_COMMA_IF(args) BOOST_PP_ENUM_PARAMS(args, class A)>  \
char_array<args> arg_tuple_size_helper(BOOST_PYTHON_FN(*,0,args));

#  define BOOST_PYTHON_ARG_TUPLE_SIZE_PMF(args, cv)                             \
template <class R, BOOST_PP_ENUM_PARAMS(args, class A)>                         \
char_array<args> arg_tuple_size_helper(BOOST_PYTHON_FN(A0::*,1,args)cv());
    
# endif

BOOST_PYTHON_REPEAT_ARITY_2ND(BOOST_PYTHON_ARG_TUPLE_SIZE_PF, nil)
    
// Generate a series for each cv-qualification
BOOST_PYTHON_REPEAT_MF_CV_2ND(BOOST_PYTHON_ARG_TUPLE_SIZE_PMF)
    
# if defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION) || defined(__BORLANDC__)
template <class F>
struct arg_tuple_size
{
    // The sizeof() magic happens here
    BOOST_STATIC_CONSTANT(std::size_t, value
      = sizeof(arg_tuple_size_helper(F(0)).elements) - 1);
};
# endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
}}} // namespace boost::python::detail

#endif // ARG_TUPLE_SIZE_DWA20011201_HPP

