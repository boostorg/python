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

///////////////////////////////////////////////////////////////////////////////
    template <int N>
    struct define_with_defaults_helper {

        template <typename StubsT, typename HolderT>
        static void
        def(char const* name, StubsT stubs, HolderT& holder)
        {
            define_stub_function(name, stubs, holder, boost::mpl::int_t<N>());
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
            define_stub_function(name, stubs, holder, boost::mpl::int_t<0>());
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


