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
      char const* name,
      Fn fn,
      CallPolicyOrDoc const& policy_or_doc,
      char const* doc,
      void const*)
  {
      typedef detail::def_helper<CallPolicyOrDoc> helper;

      detail::scope_setattr_doc(
          name, boost::python::make_function(fn, helper::get_policy(policy_or_doc)),
          helper::get_doc(policy_or_doc, doc));
  }

  template <typename StubsT, typename SigT>
  void
  dispatch_def(
      char const* name,
      SigT sig,
      StubsT const& stubs,
      char const* doc,
      detail::func_stubs_base const*)
  {
      //  convert sig to a type_list (see detail::get_signature in signature.hpp)
      //  before calling detail::define_with_defaults.
      scope current;
      detail::define_with_defaults(name, stubs, current, detail::get_signature(sig), doc);
  }
}

template <class Fn>
void def(char const* name, Fn fn)
{
    detail::scope_setattr_doc(name, boost::python::make_function(fn), 0);
}

template <class Arg1T, class Arg2T>
void def(char const* name, Arg1T arg1, Arg2T const& arg2, char const* doc = 0)
{
    detail::dispatch_def(name, arg1, arg2, doc, &arg2);
}


}} // namespace boost::python

#endif // DEF_DWA200292_HPP
