// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef PREPROCESSOR_DWA200247_HPP
# define PREPROCESSOR_DWA200247_HPP

# include <boost/config.hpp>
# include <boost/preprocessor/tuple/to_list.hpp>
# include <boost/preprocessor/tuple/elem.hpp>
# include <boost/preprocessor/list/for_each.hpp>
# include <boost/preprocessor/repeat_from_to_2nd.hpp>
# include <boost/preprocessor/inc.hpp>
# include <boost/preprocessor/empty.hpp>
# include <boost/preprocessor/enum.hpp>
# include <boost/preprocessor/expr_if.hpp>

namespace boost { namespace python { namespace detail { 

# define BOOST_PYTHON_CONST() const
# define BOOST_PYTHON_VOLATILE() volatile
# define BOOST_PYTHON_CONST_VOLATILE() const volatile

#  define BOOST_PYTHON_ALL_CV                                           \
     BOOST_PP_TUPLE_TO_LIST(4, (BOOST_PP_EMPTY                          \
                                 , BOOST_PYTHON_CONST                   \
                                 , BOOST_PYTHON_VOLATILE                \
                                 , BOOST_PYTHON_CONST_VOLATILE))

# if !defined(__MWERKS__) || __MWERKS__ > 0x2407
#  define BOOST_PYTHON_MEMBER_FUNCTION_CV BOOST_PYTHON_ALL_CV
# else
#  define BOOST_PYTHON_MEMBER_FUNCTION_CV BOOST_PP_TUPLE_TO_LIST(1, (BOOST_PP_EMPTY))
# endif 

#ifndef BOOST_PYTHON_DEBUGGABLE_ARITY
# define BOOST_PYTHON_DEBUGGABLE_ARITY 15
#endif 

#ifndef BOOST_PYTHON_MAX_ARITY
# if !defined(__EDG_VERSION__) || __EDG_VERSION__ > 245
// Generate at least two more arguments just to test the syntax
#  define BOOST_PYTHON_MAX_ARITY 17
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
# define BOOST_PYTHON_ARITY_FINISH BOOST_PP_INC(BOOST_PYTHON_DEBUGGABLE_ARITY)
# define BOOST_PYTHON_MF_ARITY_START 1
# define BOOST_PYTHON_MF_ARITY_FINISH BOOST_PP_INC(BOOST_PP_INC(BOOST_PYTHON_DEBUGGABLE_ARITY))
#else
# define BOOST_PYTHON_ARITY_START BOOST_PP_INC(BOOST_PYTHON_DEBUGGABLE_ARITY)
# define BOOST_PYTHON_ARITY_FINISH BOOST_PP_INC(BOOST_PYTHON_MAX_ARITY)
# define BOOST_PYTHON_MF_ARITY_START BOOST_PP_INC(BOOST_PP_INC(BOOST_PYTHON_DEBUGGABLE_ARITY))
# define BOOST_PYTHON_MF_ARITY_FINISH BOOST_PP_INC(BOOST_PP_INC(BOOST_PYTHON_MAX_ARITY))
#endif 

#if BOOST_PYTHON_MAX_ARITY > BOOST_PYTHON_DEBUGGABLE_ARITY

# define BOOST_PYTHON_FN(inner,start,count) \
    R(inner)(BOOST_MPL_TEMPLATE_PARAMETERS(start,count,A))

# define BOOST_PYTHON_REPEAT_ARITY_2ND(function,data)           \
    BOOST_PP_REPEAT_FROM_TO_2ND(                                \
        BOOST_PYTHON_ARITY_START, BOOST_PYTHON_ARITY_FINISH     \
        , function, data)

# define BOOST_PYTHON_REPEAT_MF_ARITY_2ND(function,data)                \
    BOOST_PP_REPEAT_FROM_TO_2ND(                                        \
        BOOST_PYTHON_MF_ARITY_START, BOOST_PYTHON_MF_ARITY_FINISH       \
        , function, data)

#  define BOOST_PYTHON_REPEAT_PMF_CV(index, function, cv) \
   BOOST_PYTHON_REPEAT_MF_ARITY_2ND(function,cv) 

# define BOOST_PYTHON_REPEAT_MF_CV_2ND(function) \
   BOOST_PP_LIST_FOR_EACH(BOOST_PYTHON_REPEAT_PMF_CV,function,BOOST_PYTHON_MEMBER_FUNCTION_CV) 

# define BOOST_PYTHON_REPEAT_MF_ALL_CV_2ND(function) \
   BOOST_PP_LIST_FOR_EACH(BOOST_PYTHON_REPEAT_PMF_CV,function,BOOST_PYTHON_ALL_CV)

#define BOOST_PYTHON_NUMBER_PAIR(Index, Pair)           \
  BOOST_PP_CAT(BOOST_PP_TUPLE_ELEM(2,0,Pair),Index)     \
  BOOST_PP_CAT(BOOST_PP_TUPLE_ELEM(2,1,Pair),Index)

#define BOOST_PYTHON_ENUM_PARAMS2(N, Pair) BOOST_PP_ENUM(N, BOOST_PYTHON_NUMBER_PAIR, Pair)

# define BOOST_PYTHON_PROJECT_1ST(a1,a2) a1
# define BOOST_PYTHON_PROJECT_2ND(a1,a2) a2
#else

# define BOOST_PYTHON_REPEAT_ARITY_2ND(function,data)
# define BOOST_PYTHON_REPEAT_MF_ARITY_2ND(function,data) 
# define BOOST_PYTHON_REPEAT_MF_ALL_CV_2ND(function)
# define BOOST_PYTHON_REPEAT_MF_CV_2ND(function)
# define BOOST_PYTHON_REPEAT_PMF_CV(index, function, cv)

#endif

}}} // namespace boost::python::detail

#endif // PREPROCESSOR_DWA200247_HPP
