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

#ifndef DEFAULTS_DEF_JDG20020811_HPP
#define DEFAULTS_DEF_JDG20020811_HPP

#include <boost/python/detail/defaults_gen.hpp>
#include <boost/type_traits.hpp>
#include <boost/mpl/int_t.hpp>
#include <boost/mpl/size.hpp>
#include <boost/static_assert.hpp>
#include <boost/preprocessor/iterate.hpp>

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
//      1. char const* name:    function name that will be visible to python
//      2. StubsT:              a function stubs struct (see defaults_gen.hpp)
//      3. HolderT& holder:     a python::class_ or python::module instance
//      4. int_t<N>:            the Nth overloaded function (StubsT::func_N)
//                                  (see defaults_gen.hpp)
//      5. char const* name:    doc string
//
///////////////////////////////////////////////////////////////////////////////
#define BOOST_PP_ITERATION_PARAMS_1                                             \
    (3, (0, BOOST_PYTHON_MAX_ARITY, <boost/python/detail/defaults_def.hpp>))

#include BOOST_PP_ITERATE()

///////////////////////////////////////////////////////////////////////////////
//
//  define_with_defaults_helper<N>
//
//  This helper template struct does the actual recursive definition.
//  There's a generic version define_with_defaults_helper<N> and a
//  terminal case define_with_defaults_helper<0>. The struct and its
//  specialization has a sole static member function def that expects:
//
//      1. char const* name:    function name that will be visible to python
//      2. StubsT:              a function stubs struct (see defaults_gen.hpp)
//      3. HolderT& holder:     a python::class_ or python::module instance
//      4. char const* name:    doc string
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
        def(char const* name, StubsT stubs, HolderT& holder, char const* doc)
        {
            //  define the NTH stub function of stubs
            define_stub_function(name, stubs, holder, boost::mpl::int_t<N>(), doc);
            //  call the next define_with_defaults_helper
            define_with_defaults_helper<N-1>::def(name, stubs, holder, doc);
        }
    };

///////////////////////////////////////
    template <>
    struct define_with_defaults_helper<0> {

        template <typename StubsT, typename HolderT>
        static void
        def(char const* name, StubsT stubs, HolderT& holder, char const* doc)
        {
            //  define the Oth stub function of stubs
            define_stub_function(name, stubs, holder, boost::mpl::int_t<0>(), doc);
            //  return
        }
    };

///////////////////////////////////////////////////////////////////////////////
//
//  define_with_defaults
//
//      1. char const* name:    function name that will be visible to python
//      2. StubsT:              a function stubs struct (see defaults_gen.hpp)
//      3. HolderT& holder:     a python::class_ or python::module instance
//      4. SigT sig:            Function signature typelist (see defaults_gen.hpp)
//      5. char const* name:    doc string
//
//  This is the main entry point. This function recursively defines all
//  stub functions of StubT (see defaults_gen.hpp) in HolderT holder which
//  can be either a python::class_ or a python::module. The sig argument
//  is a typelist that specifies the return type, the class (for member
//  functions, and the arguments. Here are some SigT examples:
//
//      int foo(int)        mpl::type_list<int, int>
//      void bar(int, int)  mpl::type_list<void, int, int>
//      void C::foo(int)    mpl::type_list<void, C, int>
//
///////////////////////////////////////////////////////////////////////////////
    template <typename StubsT, typename HolderT, typename SigT>
    inline void
    define_with_defaults(
        char const* name,
        StubsT,
        HolderT& holder,
        SigT sig,
        char const* doc)
    {
        typedef typename mpl::at<0, SigT>::type nth_type;
        typedef typename StubsT::v_type v_type;
        typedef typename StubsT::nv_type nv_type;
        
        typedef typename mpl::select_type<
            boost::is_same<void, nth_type>::value
            , v_type
            , nv_type
        >::type stubs_type;

        BOOST_STATIC_ASSERT(
            (stubs_type::max_args + 1) <= boost::mpl::size<SigT>::value);

        typedef typename stubs_type::template gen<SigT> gen_type;
        define_with_defaults_helper<stubs_type::n_funcs-1>::def
            (name, gen_type(), holder, doc);
    }

} // namespace detail

}} // namespace boost::python

///////////////////////////////////////////////////////////////////////////////
#endif // DEFAULTS_DEF_JDG20020811_HPP

#else // defined(BOOST_PP_IS_ITERATING)
// PP vertical iteration code

    template <typename StubsT, typename HolderT>
    inline void
    define_stub_function
    (
        char const* name,
        StubsT,
        HolderT& holder,
        boost::mpl::int_t<BOOST_PP_ITERATION()>,
        char const* doc
    )
    {
        holder.def(
            name,
            &StubsT::BOOST_PP_CAT(func_, BOOST_PP_ITERATION()),
            default_call_policies(),
            doc);
    }

#endif // !defined(BOOST_PP_IS_ITERATING)
