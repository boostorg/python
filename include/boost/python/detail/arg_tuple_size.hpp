#if !defined(BOOST_PP_IS_ITERATING)

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
# include <boost/preprocessor/iterate.hpp>
# include <boost/preprocessor/debug/line.hpp>
# include <boost/preprocessor/enum_params.hpp>
# include <boost/preprocessor/repetition/enum_trailing_params.hpp>

namespace boost { namespace python { namespace detail {

// Computes (at compile-time) the number of elements that a Python
// argument tuple must have in order to be passed to a wrapped C++
// (member) function of the given type.
template <class F> struct arg_tuple_size;

// We will use the "sizeof() trick" to work around the lack of
// partial specialization in MSVC6 and its broken-ness in borland.
// See http://opensource.adobe.com  or
// http://groups.yahoo.com/group/boost/message/5441 for
// more examples

// The following helper functions are never actually called, since
// they are only used within a sizeof() expression, but the type of
// their return value is used to discriminate between various free
// and member function pointers at compile-time.

// Specializations for function pointers
# define BOOST_PP_ITERATION_PARAMS_1 \
     (4, (0, BOOST_PYTHON_MAX_ARITY, <boost/python/detail/arg_tuple_size.hpp>, BOOST_PYTHON_FUNCTION_POINTER))
# include BOOST_PP_ITERATE()

// Specializations for member function pointers
# define BOOST_PP_ITERATION_PARAMS_1 \
    (4, (0, BOOST_PYTHON_CV_COUNT - 1, <boost/python/detail/arg_tuple_size.hpp>, BOOST_PYTHON_POINTER_TO_MEMBER))
# include BOOST_PP_ITERATE()

# if defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

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

// --------------- function pointers --------------- //
#elif BOOST_PP_ITERATION_DEPTH() == 1 && BOOST_PP_ITERATION_FLAGS() == BOOST_PYTHON_FUNCTION_POINTER
# line BOOST_PP_LINE(__LINE__, arg_tuple_size.hpp(function pointers))

# define N BOOST_PP_ITERATION()

# if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template <class R BOOST_PP_ENUM_TRAILING_PARAMS_Z(1, N, class A)>
struct arg_tuple_size<R (*)(BOOST_PP_ENUM_PARAMS_Z(1, N, A))>
{
    BOOST_STATIC_CONSTANT(std::size_t, value = N);
};

# else

template<class R BOOST_PP_ENUM_TRAILING_PARAMS_Z(1, N, class A)>
char_array<N> arg_tuple_size_helper(
        R (*)(BOOST_PP_ENUM_PARAMS_Z(1, N, A)));

# endif // !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

# undef N

// --------------- pointers-to-members --------------- //
#elif BOOST_PP_ITERATION_DEPTH() == 1 && BOOST_PP_ITERATION_FLAGS() == BOOST_PYTHON_POINTER_TO_MEMBER
// Outer iteration over cv-qualifications

# define BOOST_PP_ITERATION_PARAMS_2 \
    (3, (0, BOOST_PYTHON_MAX_ARITY, <boost/python/detail/arg_tuple_size.hpp>))
# include BOOST_PP_ITERATE()

#elif BOOST_PP_ITERATION_DEPTH() == 2 && BOOST_PP_RELATIVE_FLAGS(1) == BOOST_PYTHON_POINTER_TO_MEMBER
# line BOOST_PP_LINE(__LINE__, arg_tuple_size.hpp(pointers-to-members))
// Inner iteration over arities
    
# define N BOOST_PP_ITERATION()
# define Q BOOST_PYTHON_CV_QUALIFIER(BOOST_PP_RELATIVE_ITERATION(1))

# if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template <class R, class T BOOST_PP_ENUM_TRAILING_PARAMS_Z(1, N, class A)>
struct arg_tuple_size<R (T::*)(BOOST_PP_ENUM_PARAMS_Z(1, N, A)) Q>
{
    BOOST_STATIC_CONSTANT(std::size_t, value = N + 1U);
};

# else

template <class R, class T BOOST_PP_ENUM_TRAILING_PARAMS_Z(1, N, class A)>
char_array<N + 1> arg_tuple_size_helper(
    R (T::*)(BOOST_PP_ENUM_PARAMS_Z(1, N, A)) Q);

# endif // !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

# undef Q
# undef N

#endif // !defined(BOOST_PP_IS_ITERATING)
