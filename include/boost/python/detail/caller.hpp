// Copyright David Abrahams 2001. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef CALLER_DWA20011214_HPP
# define CALLER_DWA20011214_HPP

# include <boost/python/detail/wrap_python.hpp>
# include <boost/python/detail/returning.hpp>
# include <boost/mpl/select_if.hpp>
# include <boost/type_traits/composite_traits.hpp>
# include <boost/type_traits/same_traits.hpp>
# include <boost/python/detail/preprocessor.hpp>
# include <boost/preprocessor/comma_if.hpp>
# include <boost/preprocessor/enum_params.hpp>

namespace boost { namespace python
{
  template <class T> struct to_python;
}}

namespace boost { namespace python { namespace detail {

struct caller
{
    typedef PyObject* result_type;
    
# ifndef BOOST_PYTHON_GENERATE_CODE
#  include <boost/python/preprocessed/caller.hpp>
# endif

# define BOOST_PYTHON_CALLER_PF(args_, ignored)                         \
template <                                                              \
    class P                                                             \
  , class R                                                             \
    BOOST_PP_COMMA_IF(args_) BOOST_PP_ENUM_PARAMS(args_, class A)       \
  >                                                                     \
PyObject* operator()(                                                   \
    BOOST_PYTHON_FN(*f,0,args_)                                         \
  , PyObject* args, PyObject* keywords                                  \
  , P const& policies                                                   \
  ) const                                                               \
{                                                                       \
    return returning<R>::call(f, args, keywords,&policies);             \
}

BOOST_PYTHON_REPEAT_ARITY_2ND(BOOST_PYTHON_CALLER_PF, nil)

// Member functions
# define BOOST_PYTHON_CALLER_PMF(args_, cv)                             \
template <class P, class R, BOOST_PP_ENUM_PARAMS(args_, class A)>       \
PyObject* operator()(                                                   \
    BOOST_PYTHON_FN(A0::*f,1,args_)cv()                                 \
  , PyObject* args, PyObject* keywords                                  \
  , P const& policies                                                   \
  ) const                                                               \
{                                                                       \
    return returning<R>::call(f, args, keywords,&policies);             \
}

BOOST_PYTHON_REPEAT_MF_ALL_CV_2ND(BOOST_PYTHON_CALLER_PMF)
    
};

}}} // namespace boost::python::detail

#endif // CALLER_DWA20011214_HPP
