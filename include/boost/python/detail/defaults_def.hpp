///////////////////////////////////////////////////////////////////////////////
//
// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
//
///////////////////////////////////////////////////////////////////////////////
#ifndef DEFAULTS_DEF_JDG20020811_HPP
#define DEFAULTS_DEF_JDG20020811_HPP

#include <boost/python/detail/defaults_gen.hpp>
#include <boost/type_traits.hpp>
#include <boost/mpl/int_t.hpp>
#include <boost/mpl/size.hpp>
#include <boost/static_assert.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace python {

namespace detail {

///////////////////////////////////////////////////////////////////////////////
//
//  This Boost PP code generates expansions for
//
//      template <typename StubsT, typename HolderT>
//      inline void
//      define_stub_function(
//          char const* name, StubsT s, HolderT& holder, boost::mpl::int_t<N>)
//      {
//          holder.def(name, &StubsT::func_N);
//      }
//
//  where N runs from 0 to BOOST_PYTHON_MAX_ARITY
//
//  The set of overloaded functions (define_stub_function) expects:
//
//      1. char const* name:    a python function name
//      2. StubsT:              a function stubs struct (see defaults_gen.hpp)
//      3. HolderT& holder:     a python::class_ or python::module instance
//      4. int_t<N>:            the Nth overloaded function (StubsT::func_N)
//                                  (see defaults_gen.hpp)
//
///////////////////////////////////////////////////////////////////////////////
#define BPL_IMPL_STUB_FUNC_DEF(INDEX, DATA)                                     \
                                                                                \
    template <typename StubsT, typename HolderT>                                \
    inline void                                                                 \
    define_stub_function                                                        \
    (                                                                           \
        char const* name,                                                       \
        StubsT,                                                                 \
        HolderT& holder,                                                        \
        boost::mpl::int_t<INDEX>                                                \
    )                                                                           \
    {                                                                           \
        holder.def(name, &StubsT::BOOST_PP_CAT(func_, INDEX));                  \
    }                                                                           \

BOOST_PP_REPEAT(BOOST_PYTHON_MAX_ARITY, BPL_IMPL_STUB_FUNC_DEF, BOOST_PP_EMPTY)

#undef BPL_IMPL_STUB_FUNC_DEF
///////////////////////////////////////////////////////////////////////////////
//
//  define_with_defaults_helper<N>
//
//  This helper template struct does the actual recursive definition
//  There's a generic version define_with_defaults_helper<N> and a
//  terminal case define_with_defaults_helper<0>. The struct and its
//  specialization has a sole static member function def that expect:
//
//      1. char const* name:    a python function name
//      2. StubsT:              a function stubs struct (see defaults_gen.hpp)
//      3. HolderT& holder:     a python::class_ or python::module instance
//
//  The def static member function calls a corresponding
//  define_stub_function<N>. The general case recursively calls
//  define_with_defaults_helper<N-1>::def until it reaches the
//  terminal case case define_with_defaults_helper<0>.
//
///////////////////////////////////////////////////////////////////////////////
    template <int N>
    struct define_with_defaults_helper {

        template <typename StubsT, typename HolderT>
        static void
        def(char const* name, StubsT stubs, HolderT& holder)
        {
            //  define the NTH stub function of stubs
            define_stub_function(name, stubs, holder, boost::mpl::int_t<N>());
            //  call the next define_with_defaults_helper
            define_with_defaults_helper<N-1>::def(name, stubs, holder);
        }
    };

///////////////////////////////////////
    template <>
    struct define_with_defaults_helper<0> {

        template <typename StubsT, typename HolderT>
        static void
        def(char const* name, StubsT stubs, HolderT& holder)
        {
            //  define the Oth stub function of stubs
            define_stub_function(name, stubs, holder, boost::mpl::int_t<0>());
            //  return
        }
    };

///////////////////////////////////////////////////////////////////////////////
    template <typename StubsT, typename HolderT, typename SigT>
    inline void
    define_with_defaults(StubsT, HolderT& holder, SigT sig)
    {
        typedef typename mpl::select_type
        <
            boost::is_same<void, typename mpl::at<0, SigT>::type>::value,
            typename StubsT::v_type,
            typename StubsT::nv_type
        >
        ::type stubs_type;

        BOOST_STATIC_ASSERT(
            (stubs_type::max_args + 1) == boost::mpl::size<SigT>::value);

        typedef stubs_type::template gen<SigT> gen_type;
        define_with_defaults_helper<stubs_type::n_funcs-1>::def
            (stubs_type::name(), gen_type(), holder);
    }

} // namespace detail

}} // namespace boost::python

///////////////////////////////////////////////////////////////////////////////
#endif // DEFAULTS_DEF_JDG20020811_HPP


