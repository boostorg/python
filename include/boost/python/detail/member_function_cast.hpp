// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef MEMBER_FUNCTION_CAST_DWA2002311_HPP
# define MEMBER_FUNCTION_CAST_DWA2002311_HPP
# include <boost/mpl/select_if.hpp>
# include <boost/type_traits/composite_traits.hpp>
# include <boost/python/detail/preprocessor.hpp>
# include <boost/preprocessor/comma_if.hpp>
# include <boost/preprocessor/dec.hpp>
# include <boost/preprocessor/enum_shifted_params.hpp>

namespace boost { namespace python { namespace detail { 

template <class S, class FT>
struct cast_helper
{
    struct yes_helper
    {
        static FT stage3(FT x) { return x; }
    };

    struct no_helper
    {
        template <class T>
        static T stage3(T x) { return x; }
    };

    static yes_helper stage2(S*) { return yes_helper(); }
    static no_helper stage2(void*) { return no_helper(); }
};

struct non_member_function_cast_impl
{
    template <class T>
    static non_member_function_cast_impl stage1(T) { return non_member_function_cast_impl(); }

    template <class T>
    static non_member_function_cast_impl stage2(T) { return non_member_function_cast_impl(); }

    template <class T>
    T stage3(T x) { return x; }
};

template <class T>
struct member_function_cast_impl
{
# ifndef BOOST_NO_FUNCTION_TEMPLATE_ORDERING
    template <class U>
    static non_member_function_cast_impl stage1(U)
    {
        return non_member_function_cast_impl();
    }
# endif
    
// Member functions
# ifndef BOOST_PYTHON_GENERATE_CODE
#  include <boost/python/preprocessed/member_function_cast.hpp>
# endif

# define BOOST_PYTHON_MEMBER_FUNCTION_CAST_STAGE1(args, cv)                             \
template <                                                                              \
    class S                                                                             \
  , class R                                                                             \
    BOOST_PP_COMMA_IF(BOOST_PP_DEC(args)) BOOST_PP_ENUM_SHIFTED_PARAMS(args, class A)   \
  >                                                                                     \
static cast_helper<S,BOOST_PYTHON_FN(T::*,1,args)cv()>                                  \
stage1(BOOST_PYTHON_FN(S::*,1,args)cv())                                                \
{                                                                                       \
    return cast_helper<S,BOOST_PYTHON_FN(T::*,1,args)cv()>();                           \
} 

BOOST_PYTHON_REPEAT_MF_ALL_CV_2ND(BOOST_PYTHON_MEMBER_FUNCTION_CAST_STAGE1)
};


template <class T, class SF>
struct member_function_cast
# ifndef BOOST_NO_FUNCTION_TEMPLATE_ORDERING
    : member_function_cast_impl<T>
# else 
    : mpl::select_if_c<
        is_member_function_pointer<SF>::value
        , member_function_cast_impl<T>
        , non_member_function_cast_impl
    >::type
# endif 
{
};

}}} // namespace boost::python::detail

#endif // MEMBER_FUNCTION_CAST_DWA2002311_HPP
