// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef PREPROCESSOR_DWA200247_HPP
# define PREPROCESSOR_DWA200247_HPP

# include <boost/config.hpp>
# include <boost/preprocessor/tuple/to_list.hpp>
# include <boost/preprocessor/repeat_from_to_2nd.hpp>
# include <boost/preprocessor/inc.hpp>
# include <boost/preprocessor/empty.hpp>

namespace boost { namespace python { namespace detail { 

# define BOOST_PYTHON_CONST() const
# define BOOST_PYTHON_VOLATILE() volatile
# define BOOST_PYTHON_CONST_VOLATILE() const volatile

# if !defined(__MWERKS__) || __MWERKS__ > 0x2407
#  define BOOST_PYTHON_MEMBER_FUNCTION_CV \
     BOOST_PP_TUPLE_TO_LIST(4, (BOOST_PP_EMPTY \
                                 , BOOST_PYTHON_CONST \
                                 , BOOST_PYTHON_VOLATILE \
                                 , BOOST_PYTHON_CONST_VOLATILE))
# else
#  define BOOST_PYTHON_MEMBER_FUNCTION_CV \
     BOOST_PP_TUPLE_TO_LIST(1, (BOOST_PP_EMPTY))
# endif 

#ifndef BOOST_PYTHON_DEBUGGABLE_ARITY
# define BOOST_PYTHON_DEBUGGABLE_ARITY 10
#endif 

#ifndef BOOST_PYTHON_MAX_ARITY
# if !defined(__EDG_VERSION__) || __EDG_VERSION__ > 245
// Generate at least two more arguments just to test the syntax
#  define BOOST_PYTHON_MAX_ARITY 12
# else
// Current EDG compilers have a really slow preprocessor which makes
// it important not to generate new functions with it unless
// absolutely neccessary
#  define BOOST_PYTHON_MAX_ARITY BOOST_PYTHON_DEBUGGABLE_ARITY
# endif 
#endif 

#ifdef BOOST_PYTHON_GENERATE_CODE
# undef BOOST_STATIC_CONSTANT
# define BOOST_PYTHON_ARITY_START 0
# define BOOST_PYTHON_ARITY_FINISH BOOST_PYTHON_DEBUGGABLE_ARITY
# define BOOST_PYTHON_MF_ARITY_START 1
# define BOOST_PYTHON_MF_ARITY_FINISH BOOST_PP_INC(BOOST_PYTHON_DEBUGGABLE_ARITY)
#else
# define BOOST_PYTHON_ARITY_START BOOST_PYTHON_DEBUGGABLE_ARITY
# define BOOST_PYTHON_ARITY_FINISH BOOST_PYTHON_MAX_ARITY
# define BOOST_PYTHON_MF_ARITY_START BOOST_PP_INC(BOOST_PYTHON_DEBUGGABLE_ARITY)
# define BOOST_PYTHON_MF_ARITY_FINISH BOOST_PP_INC(BOOST_PYTHON_MAX_ARITY)
#endif 

# define BOOST_PYTHON_PF(Count)         R(*)(BOOST_MPL_TEMPLATE_PARAMETERS(0,Count,A))
# define BOOST_PYTHON_PMF(Count, cv)    R(A0::*)(BOOST_MPL_TEMPLATE_PARAMETERS(1,Count,A))cv()

# define BOOST_PYTHON_REPEAT_ARITY_2ND(function,data) \
    BOOST_PP_REPEAT_FROM_TO_2ND(BOOST_PYTHON_ARITY_START, BOOST_PYTHON_ARITY_FINISH, function, data)

# define BOOST_PYTHON_REPEAT_MF_ARITY_2ND(function,data) \
    BOOST_PP_REPEAT_FROM_TO_2ND(BOOST_PYTHON_MF_ARITY_START, BOOST_PYTHON_MF_ARITY_FINISH, function, data)


}}} // namespace boost::python::detail

#endif // PREPROCESSOR_DWA200247_HPP
