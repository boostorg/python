// Copyright David Abrahams 2001. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef MAKE_HOLDER_DWA20011215_HPP
# define MAKE_HOLDER_DWA20011215_HPP

# include <boost/mpl/at.hpp>
# include <boost/python/object/forward.hpp>
# include <boost/python/object/class.hpp>
# include <boost/python/detail/wrap_python.hpp>
# include <boost/python/detail/preprocessor.hpp>
# include <boost/preprocessor/repeat.hpp>
# include <boost/preprocessor/enum.hpp>

namespace boost { namespace python { namespace objects { 

template <int nargs> struct make_holder;

# ifndef BOOST_PYTHON_GENERATE_CODE
#  include <boost/python/preprocessed/make_holder.hpp>
# endif


# define BOOST_PYTHON_FORWARD_ARG(index, ignored)                                       \
    typedef typename mpl::at_c<index,ArgList>::type BOOST_PP_CAT(t,index);              \
    typedef typename forward<BOOST_PP_CAT(t,index)>::type BOOST_PP_CAT(f,index);

# define BOOST_PYTHON_DO_FORWARD_ARG(index, ignored)    \
    BOOST_PP_CAT(f,index)(BOOST_PP_CAT(a, index))

# define BOOST_PYTHON_MAKE_HOLDER(nargs,ignored)                                \
template <>                                                                     \
struct make_holder<nargs>                                                       \
{                                                                               \
    template <class Holder, class ArgList>                                      \
    struct apply                                                                \
    {                                                                           \
        BOOST_PP_REPEAT(nargs, BOOST_PYTHON_FORWARD_ARG, nil)                   \
                                                                                \
        static void execute(                                                    \
            PyObject* p                                                         \
            BOOST_PP_COMMA_IF(nargs) BOOST_PYTHON_ENUM_PARAMS2(nargs, (t,a)) )  \
        {                                                                       \
            (new Holder(                                                        \
                p                                                               \
                BOOST_PP_COMMA_IF(nargs) BOOST_PP_ENUM(                         \
                    nargs,BOOST_PYTHON_DO_FORWARD_ARG,nil)))->install(p);       \
        }                                                                       \
    };                                                                          \
};

BOOST_PYTHON_REPEAT_ARITY_2ND(BOOST_PYTHON_MAKE_HOLDER,nil)

}}} // namespace boost::python::objects

#endif // MAKE_HOLDER_DWA20011215_HPP
