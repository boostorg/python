#if !defined(BOOST_PP_IS_ITERATING)

// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef ARGS_DWA2002323_HPP
# define ARGS_DWA2002323_HPP
#  include <boost/config.hpp>

#  include <boost/python/detail/preprocessor.hpp>

#  include <boost/mpl/type_list.hpp>

#  include <boost/preprocessor/cat.hpp>
#  include <boost/preprocessor/iterate.hpp>

#  if !defined(__EDG_VERSION__) || __EDG_VERSION__ > 245

namespace boost { namespace python {

// A type list for specifying arguments
template < BOOST_PYTHON_ENUM_WITH_DEFAULT(BOOST_PYTHON_MAX_ARITY, typename A, boost::mpl::null_argument) >
struct args : boost::mpl::type_list< BOOST_PYTHON_UNARY_ENUM(BOOST_PYTHON_MAX_ARITY, A) >::type
{};

}} // namespace boost::python

#  else // slow template instantiators need this other version with
        // explicit specializations of mpl::size<> and
        // mpl::at<>. Eventually, however, inheritance from mpl::list
        // *should* be eliminated and the two versions unified, just in
        // order to get true arity independence

namespace boost { namespace python {

template < BOOST_PYTHON_ENUM_WITH_DEFAULT(BOOST_PYTHON_MAX_ARITY, typename A, boost::mpl::null_argument) >
struct args
{};

}} // namespace boost::python

namespace boost { namespace mpl {

template <class T> struct size;
template <long N, class Seq> struct at;

#  define BOOST_PP_ITERATION_PARAMS_1 4, (0, BOOST_PYTHON_MAX_ARITY, <boost/python/args.hpp>, 1)
#  include BOOST_PP_ITERATE()

#  define BOOST_PP_ITERATION_PARAMS_1 4, (0, BOOST_PYTHON_MAX_ARITY - 1, <boost/python/args.hpp>, 2)
#  include BOOST_PP_ITERATE()


}} // namespace boost::mpl

# endif // __EDG_VERSION__

# endif // ARGS_DWA2002323_HPP

/* ---------- size ---------- */
#elif BOOST_PP_ITERATION_DEPTH() == 1 && BOOST_PP_ITERATION_FLAGS() == 1
# line BOOST_PP_LINE(__LINE__, args.hpp(size))

# define N BOOST_PP_ITERATION()

template <BOOST_PYTHON_UNARY_ENUM(N, class A)>
struct size<boost::python::args<BOOST_PYTHON_UNARY_ENUM(N, A)> >
{
    BOOST_STATIC_CONSTANT(long, value = N);
};

# undef N

/* ---------- at ---------- */
#elif BOOST_PP_ITERATION_DEPTH() == 1 && BOOST_PP_ITERATION_FLAGS() == 2
# line BOOST_PP_LINE(__LINE__, args.hpp(at))

# define N BOOST_PP_ITERATION()

template <BOOST_PYTHON_UNARY_ENUM(BOOST_PYTHON_MAX_ARITY, class A)>
struct at<N, boost::python::args<BOOST_PYTHON_UNARY_ENUM(BOOST_PYTHON_MAX_ARITY, A)> >
{
    typedef BOOST_PP_CAT(A, N) type;
};

# undef N

#endif
