///////////////////////////////////////////////////////////////////////////////
//
// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
//
///////////////////////////////////////////////////////////////////////////////
#if !defined(BOOST_PP_IS_ITERATING)

#ifndef TYPE_LIST_UTILS_JDG20020826_HPP
#define TYPE_LIST_UTILS_JDG20020826_HPP

# include <boost/mpl/at.hpp>
# include <boost/mpl/size.hpp>
//# include <boost/mpl/pop_front.hpp>
//# include <boost/mpl/pop_back.hpp>

# include <boost/preprocessor/enum_params.hpp>
# include <boost/preprocessor/enum_shifted_params.hpp>
# include <boost/preprocessor/cat.hpp>
# include <boost/preprocessor/iterate.hpp>
# include <boost/preprocessor/dec.hpp>

# include <boost/mpl/type_list.hpp>

namespace boost { namespace python { namespace detail {

# if (!defined(__EDG_VERSION__) || __EDG_VERSION__ > 245)                       \
    && (!defined(BOOST_INTEL_CXX_VERSION) || BOOST_INTEL_CXX_VERSION > 600)

    template <int N, class L>
    struct type_at : public boost::mpl::at<N, L> {};

    template <class L>
    struct type_list_size : public boost::mpl::size<L> {};

//    template <class L>
//    struct pop_front : public boost::mpl::pop_front<L> {};
//
//    template <class L>
//    struct pop_back : public boost::mpl::pop_back<L> {};

# else

    template <int N, class L>
    struct type_at {};

    template <class L>
    struct type_list_size {};

//    template <class L>
//    struct pop_front {};
//
//    template <class L>
//    struct pop_back {};

//    template <class L, class T>
//    struct push_back {};

# define BOOST_PP_ITERATION_PARAMS_1                                            \
    (3, (0, BOOST_PYTHON_MAX_ARITY, <boost/python/detail/type_list_utils.hpp>))
# include BOOST_PP_ITERATE()

# endif

}}} // namespace boost::python::detail

#endif // TYPE_LIST_UTILS_JDG20020826_HPP

#else // defined(BOOST_PP_IS_ITERATING)

# define N BOOST_PP_ITERATION()
# define MAX BOOST_PYTHON_MAX_ARITY

#  if (N < MAX-1)

    template <BOOST_PP_ENUM_PARAMS(MAX, class A)>
    struct type_at<N, boost::mpl::type_list<BOOST_PP_ENUM_PARAMS(MAX, A)> >
    {
        typedef BOOST_PP_CAT(A, N) type;
    };

//    template <BOOST_PP_ENUM_PARAMS(N, class A) BOOST_PP_COMMA_IF(N) class T>
//    struct push_back<boost::mpl::type_list<BOOST_PP_ENUM_PARAMS(N, A)>, T>
//    {
//        typedef boost::mpl::type_list<BOOST_PP_ENUM_PARAMS(N, A) BOOST_PP_COMMA_IF(N) T> sequence;
//    };

#  if (N > 0)

//    template <BOOST_PP_ENUM_PARAMS(N, class A)>
//    struct pop_front<boost::mpl::type_list<BOOST_PP_ENUM_PARAMS(N, A)> >
//    {
//        typedef boost::mpl::type_list<BOOST_PP_ENUM_SHIFTED_PARAMS(N, A)> sequence;
//    };
//
//    template <BOOST_PP_ENUM_PARAMS(N, class A)>
//    struct pop_back<boost::mpl::type_list<BOOST_PP_ENUM_PARAMS(N, A)> >
//    {
//        typedef boost::mpl::type_list<BOOST_PP_ENUM_PARAMS(BOOST_PP_DEC(N), A)> sequence;
//    };

#  endif
#  endif

    template <BOOST_PP_ENUM_PARAMS(N, class A)>
    struct type_list_size<boost::mpl::type_list<BOOST_PP_ENUM_PARAMS(N, A)> >
    {
        BOOST_STATIC_CONSTANT(long, value = N);
    };

# undef N
# undef MAX

#endif // !defined(BOOST_PP_IS_ITERATING)
