// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef DEF_DWA200292_HPP
# define DEF_DWA200292_HPP

# include <boost/python/object_fwd.hpp>
# include <boost/python/make_function.hpp>
# include <boost/python/detail/def_helper.hpp>
# include <boost/python/detail/overloads_fwd.hpp>
# include <boost/python/scope.hpp>
# include <boost/python/signature.hpp>
# include <boost/python/detail/scope.hpp>

namespace boost { namespace python {

namespace detail
{
  template <class Fn, class A1>
  void
  dispatch_def(
      void const*,
      char const* name,
      Fn fn,
      A1 const& a1)
  {
      def_helper<A1> helper(a1);
      
      detail::scope_setattr_doc(
          name, boost::python::make_function(
              fn
              , helper.policies()
              , helper.keywords())
          , helper.doc()
          );
    }

    template <class Fn, class A1, class A2>
    void dispatch_def(
        void const*,
        char const* name,
        Fn fn,
        A1 const& a1,
        A2 const& a2)
    {
        def_helper<A1,A2> helper(a1,a2);

        detail::scope_setattr_doc(
            name, python::make_function(
                fn
                , helper.policies()
                , helper.keywords())
            , helper.doc()
            );
    }

    template <class StubsT, class SigT>
    void dispatch_def(
        detail::overloads_base const*,
        char const* name,
        SigT sig,
        StubsT const& stubs)
    {
        //  convert sig to a type_list (see detail::get_signature in signature.hpp)
        //  before calling detail::define_with_defaults.

        scope current;
        detail::define_with_defaults(
            name, stubs, current, detail::get_signature(sig));
    }
}

template <class Fn>
void def(char const* name, Fn fn)
{
    detail::scope_setattr_doc(name, boost::python::make_function(fn), 0);
}

template <class Arg1T, class Arg2T>
void def(char const* name, Arg1T arg1, Arg2T const& arg2)
{
    //  The arguments may be:
    //      def(name, function)
    //      def(name, function, policy)
    //      def(name, function, doc_string)
    //      def(name, signature, stubs)

    detail::dispatch_def(&arg2, name, arg1, arg2);
}

template <class Arg1T, class Arg2T, class Arg3T>
void def(char const* name, Arg1T arg1, Arg2T const& arg2, Arg3T const& arg3)
{
    detail::dispatch_def(&arg2, name, arg1, arg2, arg3);
}

template <class F, class A1, class A2, class A3>
void def(char const* name, F f, A1 const& a1, A2 const& a2, A3 const& a3)
{
    detail::def_helper<A1,A2,A3> helper(a1,a2,a3);

    detail::scope_setattr_doc(
        name, python::make_function(
            f
            , helper.policies()
            , helper.keywords())
        , helper.doc()
        );
}

}} // namespace boost::python

#endif // DEF_DWA200292_HPP
