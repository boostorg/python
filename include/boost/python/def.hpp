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
        CallPolicyOrDoc const& policy_or_doc)
    {
        typedef detail::def_helper<CallPolicyOrDoc> helper;

        detail::scope_setattr_doc(
            name, boost::python::make_function(fn, helper::get_policy(policy_or_doc)),
            helper::get_doc(policy_or_doc, 0));
    }

    template <class Fn, class CallPolicyOrDoc1, class CallPolicyOrDoc2>
    void dispatch_def(
        void const*,
        char const* name,
        Fn fn,
        CallPolicyOrDoc1 const& policy_or_doc1,
        CallPolicyOrDoc2 const& policy_or_doc2)
    {
        typedef detail::def_helper<CallPolicyOrDoc1> helper;

        detail::scope_setattr_doc(
            name, boost::python::make_function(
                fn, helper::get_policy(policy_or_doc1, policy_or_doc2)),
            helper::get_doc(policy_or_doc1, policy_or_doc2));
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
    //  The arguments are definitely:
    //      def(name, function, policy, doc_string) // TODO: exchange policy, doc_string position

    detail::dispatch_def(&arg2, name, arg1, arg2, arg3);
}

//template <class Arg1T, class Arg2T, class Arg3T>
//void def(char const* name, Arg1T arg1, Arg2T const& arg2, Arg3T const& arg3, char const* doc)
//{
//    //  The arguments are definitely:
//    //  arg1:   signature
//    //  arg2:   stubs
//    //  arg3:   policy
//
//    detail::dispatch_def(&arg2, name, arg1, arg2, arg3, doc);
//}

}} // namespace boost::python

#endif // DEF_DWA200292_HPP
