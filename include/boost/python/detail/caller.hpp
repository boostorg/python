#if !defined(BOOST_PP_IS_ITERATING)

//  (C) Copyright David Abrahams 2000. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
//  The author gratefully acknowleges the support of Dragon Systems, Inc., in
//  producing this work.
//
//  This file generated for 10-argument member functions and 11-argument free
//  functions by gen_caller.python

# ifndef CALLER_DWA20011214_HPP
#  define CALLER_DWA20011214_HPP

#  include <boost/python/detail/wrap_python.hpp>
#  include <boost/python/detail/returning.hpp>
#  include <boost/python/detail/preprocessor.hpp>

#  include <boost/type_traits/composite_traits.hpp>
#  include <boost/type_traits/same_traits.hpp>

#  include <boost/preprocessor/comma_if.hpp>
#  include <boost/preprocessor/iterate.hpp>
#  include <boost/preprocessor/debug/line.hpp>
#  include <boost/preprocessor/repetition/enum_trailing_params.hpp>

namespace boost { namespace python
{
    template <class T> struct to_python;
}}

namespace boost { namespace python { namespace detail {

struct caller
{
    typedef PyObject* result_type;

    // function pointers
#  define BOOST_PP_ITERATION_PARAMS_1 \
    (4, (0, BOOST_PYTHON_MAX_ARITY, <boost/python/detail/caller.hpp>, BOOST_PYTHON_FUNCTION_POINTER))
#  include BOOST_PP_ITERATE()

    // pointers-to-members
#  define BOOST_PP_ITERATION_PARAMS_1 \
    (4, (0, 3, <boost/python/detail/caller.hpp>, BOOST_PYTHON_POINTER_TO_MEMBER))
#  include BOOST_PP_ITERATE()

};

}}} // namespace boost::python::detail

# endif // CALLER_DWA20011214_HPP

/* ---------- function pointers --------- */
#elif BOOST_PP_ITERATION_DEPTH() == 1 && BOOST_PP_ITERATION_FLAGS() == BOOST_PYTHON_FUNCTION_POINTER
# line BOOST_PP_LINE(__LINE__, detail/caller.hpp(function pointers))

# define N BOOST_PP_ITERATION()

template <
    class P, class R
    BOOST_PP_ENUM_TRAILING_PARAMS_Z(1, N, class A)
    >
PyObject* operator()(
    R (*pf)(BOOST_PP_ENUM_PARAMS_Z(1, N, A))
    , PyObject* args
    , PyObject* keywords
    , P const& policies) const
{
    return returning<R>::call(pf, args, keywords, &policies);
}

# undef N

/* ---------- pointers-to-members ---------- */
#elif BOOST_PP_ITERATION_DEPTH() == 1 && BOOST_PP_ITERATION_FLAGS() == BOOST_PYTHON_POINTER_TO_MEMBER
// outer over cv-qualifiers

# define BOOST_PP_ITERATION_PARAMS_2 (3, (0, BOOST_PYTHON_MAX_ARITY, <boost/python/detail/caller.hpp>))
# include BOOST_PP_ITERATE()

#elif BOOST_PP_ITERATION_DEPTH() == 2
// inner over arities

#define N BOOST_PP_ITERATION()
#define Q BOOST_PYTHON_CV_QUALIFIER(BOOST_PP_RELATIVE_ITERATION(1))

template <
    class P, class R, class T
    BOOST_PP_ENUM_TRAILING_PARAMS_Z(1, N, class A)
    >
PyObject* operator()(
    R (T::*pmf)(BOOST_PP_ENUM_PARAMS_Z(1, N, A)) Q
    , PyObject* args, PyObject* keywords
    , P const& policies
    ) const
{
    return returning<R>::call(pmf, args, keywords, &policies);
}

#undef N
#undef Q

#endif
