///////////////////////////////////////////////////////////////////////////////
//
// Copyright David Abrahams 2002, Joel de Guzman, 2002. Permission to copy,
// use, modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided "as is"
// without express or implied warranty, and with no claim as to its
// suitability for any purpose.
//
///////////////////////////////////////////////////////////////////////////////
#if !defined(BOOST_PP_IS_ITERATING)

# ifndef SIGNATURE_JDG20020813_HPP
#  define SIGNATURE_JDG20020813_HPP

#  include <boost/python/detail/preprocessor.hpp>
#  include <boost/preprocessor/repeat.hpp>
#  include <boost/preprocessor/enum.hpp>
#  include <boost/preprocessor/enum_params.hpp>
#  include <boost/preprocessor/empty.hpp>
#  include <boost/preprocessor/arithmetic/sub.hpp>
#  include <boost/preprocessor/iterate.hpp>
#  include <boost/python/detail/type_list.hpp>

#  include <boost/preprocessor/debug/line.hpp>
#  include <boost/preprocessor/arithmetic/sub.hpp>
#  include <boost/preprocessor/arithmetic/inc.hpp>
#  include <boost/preprocessor/repetition/enum_trailing_params.hpp>

# define BOOST_PYTHON_FUNCTION_SIGNATURE_LIST(n)        \
   BOOST_PP_CAT(mpl::list, BOOST_PP_INC(n))

# define BOOST_PYTHON_MEMBER_FUNCTION_SIGNATURE_LIST(n)         \
   BOOST_PP_CAT(mpl::list, BOOST_PP_INC(BOOST_PP_INC(n)))


///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace python { namespace detail {

///////////////////////////////////////////////////////////////////////////////
//
//  The following macros generate expansions for:
//
//      template <class RT, class T0... class TN>
//      inline mpl::list<RT, T0...TN>
//      get_signature(RT(*)(T0...TN))
//      {
//          return mpl::list<RT, T0...TN>();
//      }
//
//      template <class RT, class ClassT, class T0... class TN>
//      inline mpl::list<RT, ClassT, T0...TN>
//      get_signature(RT(ClassT::*)(T0...TN)))
//      {
//          return mpl::list<RT, ClassT, T0...TN>();
//      }
//
//      template <class RT, class ClassT, class T0... class TN>
//      inline mpl::list<RT, ClassT, T0...TN>
//      get_signature(RT(ClassT::*)(T0...TN) const))
//      {
//          return mpl::list<RT, ClassT const, T0...TN>();
//      }
//
//  These functions extract the return type, class (for member functions)
//  and arguments of the input signature and stuffs them in an mpl::list.
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
#  define BOOST_PP_ITERATION_PARAMS_1                                   \
    (3, (0, BOOST_PYTHON_MAX_ARITY-1, <boost/python/signature.hpp>))

#  include BOOST_PP_ITERATE()

}

}} // namespace boost::python


# undef BOOST_PYTHON_FUNCTION_SIGNATURE_LIST
# undef BOOST_PYTHON_MEMBER_FUNCTION_SIGNATURE_LIST

///////////////////////////////////////////////////////////////////////////////
# endif // SIGNATURE_JDG20020813_HPP

#else // defined(BOOST_PP_IS_ITERATING)

# define N BOOST_PP_ITERATION()

# define BOOST_PYTHON_SIGNATURE_PARAMS BOOST_PP_ENUM_TRAILING_PARAMS_Z(1, N, class T)
# define BOOST_PYTHON_SIGNATURE_TYPES BOOST_PP_ENUM_PARAMS_Z(1, N, T)
# define BOOST_PYTHON_TRAILING_SIGNATURE_TYPES BOOST_PP_COMMA_IF(N) BOOST_PYTHON_SIGNATURE_TYPES

template <
    class RT BOOST_PYTHON_SIGNATURE_PARAMS>
inline BOOST_PYTHON_FUNCTION_SIGNATURE_LIST(N)<
    RT BOOST_PYTHON_TRAILING_SIGNATURE_TYPES>
get_signature(RT(*)(BOOST_PYTHON_SIGNATURE_TYPES))
{
    return BOOST_PYTHON_FUNCTION_SIGNATURE_LIST(N)<
            RT BOOST_PYTHON_TRAILING_SIGNATURE_TYPES
        >();
}

///////////////////////////////////////////////////////////////////////////////
#if N <= (BOOST_PYTHON_MAX_ARITY - 2)

template <
    class RT, class ClassT BOOST_PYTHON_SIGNATURE_PARAMS>
inline BOOST_PYTHON_MEMBER_FUNCTION_SIGNATURE_LIST(N)<
    RT, ClassT BOOST_PYTHON_TRAILING_SIGNATURE_TYPES >
get_signature(RT(ClassT::*)(BOOST_PYTHON_SIGNATURE_TYPES))
{
    return BOOST_PYTHON_MEMBER_FUNCTION_SIGNATURE_LIST(N)<
        RT, ClassT BOOST_PYTHON_TRAILING_SIGNATURE_TYPES>();
}

///////////////////////////////////////
template <
    class RT, class ClassT BOOST_PYTHON_SIGNATURE_PARAMS>
inline BOOST_PYTHON_MEMBER_FUNCTION_SIGNATURE_LIST(N)<
    RT, ClassT const BOOST_PYTHON_TRAILING_SIGNATURE_TYPES>
get_signature(RT(ClassT::*)(BOOST_PYTHON_SIGNATURE_TYPES) const)
{
    return BOOST_PYTHON_MEMBER_FUNCTION_SIGNATURE_LIST(N)<
        RT, ClassT const BOOST_PYTHON_TRAILING_SIGNATURE_TYPES>();
}

#endif // N < (BOOST_PYTHON_MAX_ARITY - 2)

# undef BOOST_PYTHON_SIGNATURE_PARAMS
# undef BOOST_PYTHON_SIGNATURE_TYPES
# undef BOOST_PYTHON_TRAILING_SIGNATURE_TYPES

#endif // !defined(BOOST_PP_IS_ITERATING)
