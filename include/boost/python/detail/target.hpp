// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef TARGET_DWA2002521_HPP
# define TARGET_DWA2002521_HPP

# include <boost/python/detail/preprocessor.hpp>
# include <boost/preprocessor/comma_if.hpp>
# include <boost/mpl/aux_/preprocessor.hpp>
# include <boost/preprocessor/comma_if.hpp>
# include <boost/preprocessor/if.hpp>
# include <boost/type.hpp>

namespace boost { namespace python { namespace detail { 

# ifndef BOOST_PYTHON_GENERATE_CODE
#  include <boost/python/preprocessed/target.hpp>
# endif 

#  define BOOST_PYTHON_FIRST_ARGUMENT_PF(args, ignored)                                         \
template <class R BOOST_PP_COMMA_IF(args) BOOST_MPL_TEMPLATE_PARAMETERS(0, args, class A)>      \
boost::type<BOOST_PP_IF(args, A0, void)>* target(BOOST_PYTHON_FN(*,0,args)) { return 0; }

#  define BOOST_PYTHON_FIRST_ARGUMENT_PMF(args, cv)                                     \
template <class R, BOOST_MPL_TEMPLATE_PARAMETERS(0, args, class A)>                     \
boost::type<A0 cv()*>* target(BOOST_PYTHON_FN(A0::*,1,args)cv()) { return 0; }

BOOST_PYTHON_REPEAT_ARITY_2ND(BOOST_PYTHON_FIRST_ARGUMENT_PF, nil)
BOOST_PYTHON_REPEAT_MF_CV_2ND(BOOST_PYTHON_FIRST_ARGUMENT_PMF)

template <class R, class T>
boost::type<T*>* target(R (T::*)) { return 0; }

}}} // namespace boost::python::detail

#endif // TARGET_DWA2002521_HPP
