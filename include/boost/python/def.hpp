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
# include <boost/python/detail/defaults_def.hpp>
# include <boost/python/scope.hpp>
# include <boost/python/signature.hpp>

namespace boost { namespace python {

namespace detail
{
  void BOOST_PYTHON_DECL scope_setattr_doc(char const* name, object const& obj, char const* doc);

  template <class Fn, class CallPolicyOrDoc>
  void
  dispatch_def(
      void const*,
      char const* name,
      Fn fn,
      CallPolicyOrDoc const& policy_or_doc,
      char const* doc)
  {
      typedef detail::def_helper<CallPolicyOrDoc> helper;

      detail::scope_setattr_doc(
          name, boost::python::make_function(fn, helper::get_policy(policy_or_doc)),
          helper::get_doc(policy_or_doc, doc));
  }

    template <class StubsT, class SigT, class CallPolicyOrDoc>
    void dispatch_def(
        detail::func_stubs_base const*,
        char const* name,
        SigT sig,
        StubsT const& stubs,
        CallPolicyOrDoc const& policy_or_doc,
        char const* doc = 0)
    {
        typedef detail::def_helper<CallPolicyOrDoc> helper;

        //  convert sig to a type_list (see detail::get_signature in signature.hpp)
        //  before calling detail::define_with_defaults.

        scope current;
        detail::define_with_defaults(
            name, stubs, helper::get_policy(policy_or_doc),
            current, detail::get_signature(sig),
            helper::get_doc(policy_or_doc, doc));
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
    //  arg1:   function    or  signature
    //  arg2:   policy      or  docstring   or  stubs

    detail::dispatch_def(&arg2, name, arg1, arg2, (char*)0);
}

template <class Arg1T, class Arg2T, class Arg3T>
void def(char const* name, Arg1T arg1, Arg2T const& arg2, Arg3T const& arg3)
{
    //  The arguments may be:
    //  arg1:   function    or  signature
    //  arg2:   policy      or  docstring   or  stubs
    //  arg3:   policy      or  docstring

    detail::dispatch_def(&arg2, name, arg1, arg2, arg3);
}

template <class Arg1T, class Arg2T, class Arg3T>
void def(char const* name, Arg1T arg1, Arg2T const& arg2, Arg3T const& arg3, char const* doc)
{
    //  The arguments are definitely:
    //  arg1:   signature
    //  arg2:   stubs
    //  arg3:   policy

    detail::dispatch_def(&arg2, name, arg1, arg2, arg3, doc);
}

}} // namespace boost::python

#endif // DEF_DWA200292_HPP
