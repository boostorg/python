// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef RESULT_DWA2002521_HPP
# define RESULT_DWA2002521_HPP

# include <boost/python/detail/preprocessor.hpp>
# include <boost/preprocessor/comma_if.hpp>
# include <boost/mpl/aux_/preprocessor.hpp>
# include <boost/preprocessor/comma_if.hpp>
# include <boost/mpl/select_type.hpp>
# include <boost/type.hpp>
# include <boost/type_traits/object_traits.hpp>

namespace boost { namespace python { namespace detail { 

// Defines a family of overloaded function which, given x, a function
// pointer, member [function] pointer, or an AdaptableFunction object,
// returns a pointer to type<R>*, where R is the result type of
// invoking the result of bind(x).
//
// In order to work around bugs in deficient compilers, if x might be
// an AdaptableFunction object, you must pass OL as a second argument
// to get this to work portably.

# ifndef BOOST_PYTHON_GENERATE_CODE
#  include <boost/python/preprocessed/result.hpp>
# endif 

#  define BOOST_PYTHON_FIRST_ARGUMENT_PF(args, ignored)                                         \
template <class R BOOST_PP_COMMA_IF(args) BOOST_MPL_TEMPLATE_PARAMETERS(0, args, class A)>      \
boost::type<R>* result(BOOST_PYTHON_FN(*,0,args), int = 0) { return 0; }

#  define BOOST_PYTHON_FIRST_ARGUMENT_PMF(args, cv)                                             \
template <class R, BOOST_MPL_TEMPLATE_PARAMETERS(0, args, class A)>                             \
boost::type<R>* result(BOOST_PYTHON_FN(A0::*,1,args)cv(), int = 0) { return 0; }

BOOST_PYTHON_REPEAT_ARITY_2ND(BOOST_PYTHON_FIRST_ARGUMENT_PF, nil)
BOOST_PYTHON_REPEAT_MF_CV_2ND(BOOST_PYTHON_FIRST_ARGUMENT_PMF)

template <class R, class T>
boost::type<R>* result(R (T::*), int = 0) { return 0; }

#  if (defined(BOOST_MSVC) && _MSC_FULL_VER <= 13102140)  \
   || (defined(__GNUC__) && __GNUC__ < 3)                 \
   || (defined(__MWERKS__) && __MWERKS__ < 0x3000)
// This code actually works on all implementations, but why use it when we don't have to?
template <class T>
struct get_result_type
{
    typedef boost::type<typename T::result_type> type;
};

struct void_type
{
    typedef void type;
};

template <class T>
struct result_result
{
    typedef typename mpl::select_type<
        is_class<T>::value
        , get_result_type<T>
        , void_type
        >::type t1;

    typedef typename t1::type* type;
};

template <class X>
typename result_result<X>::type
result(X const&, short) { return 0; }

#  else // Simpler code for more-capable compilers
template <class X>
boost::type<typename X::result_type>*
result(X const&, short = 0) { return 0; }

#  endif 

}}} // namespace boost::python::detail

#endif // RESULT_DWA2002521_HPP
