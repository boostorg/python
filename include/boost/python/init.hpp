///////////////////////////////////////////////////////////////////////////////
//
// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
//
///////////////////////////////////////////////////////////////////////////////
#ifndef INIT_JDG20020820_HPP
#define INIT_JDG20020820_HPP

#include <boost/python/detail/type_list.hpp>
#include <boost/mpl/fold_backward.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/apply_if.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/push_front.hpp>
#include <boost/mpl/iterator_range.hpp>
#include <boost/mpl/logical/not.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/mpl/lambda.hpp>
#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/find_if.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/pop_front.hpp>

#include <boost/type_traits/is_same.hpp>

#include <boost/static_assert.hpp>
#include <boost/preprocessor/enum_params_with_a_default.hpp>
#include <boost/preprocessor/enum_params.hpp>
#include <boost/preprocessor/enum_params.hpp>
#include <boost/preprocessor/repeat.hpp>

///////////////////////////////////////////////////////////////////////////////
#define BOOST_PYTHON_TEMPLATE_TYPES_WITH_DEFAULT                                \
    BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(                                        \
        BOOST_PYTHON_MAX_ARITY,                                                 \
        class T,                                                                \
        mpl::void_)                                                             \

#define BOOST_PYTHON_TEMPLATE_TYPES                                             \
    BOOST_PP_ENUM_PARAMS(                                                       \
        BOOST_PYTHON_MAX_ARITY,                                                 \
        class T)                                                                \

#define BOOST_PYTHON_TEMPLATE_ARGS                                              \
    BOOST_PP_ENUM_PARAMS(                                                       \
        BOOST_PYTHON_MAX_ARITY,                                                 \
        T)                                                                      \

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace python {

template <BOOST_PYTHON_TEMPLATE_TYPES_WITH_DEFAULT>
struct init; // forward declaration

///////////////////////////////////////
template <BOOST_PYTHON_TEMPLATE_TYPES_WITH_DEFAULT>
struct optional; // forward declaration

namespace detail {

    ///////////////////////////////////////////////////////////////////////////
    //
    //  is_optional<T>::value
    //
    //      This metaprogram checks if T is an optional
    //
    ///////////////////////////////////////////////////////////////////////////
    #if defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

    template <class T>
    struct is_optional {

    private:

        template <BOOST_PYTHON_TEMPLATE_TYPES>
        static boost::type_traits::yes_type f(optional<BOOST_PYTHON_TEMPLATE_ARGS>);
        static boost::type_traits::no_type f(...);
        static T t();

    public:

        BOOST_STATIC_CONSTANT(
            bool, value =
                sizeof(f(t())) == sizeof(::boost::type_traits::yes_type));
        typedef mpl::bool_c<value> type;

        BOOST_MPL_AUX_LAMBDA_SUPPORT(1,is_optional,(T)) // needed for MSVC & Borland
    };

    ///////////////////////////////////////
    #else // defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

    template <class T>
    struct is_optional_impl {

        BOOST_STATIC_CONSTANT(bool, value = false);
    };

    template <BOOST_PYTHON_TEMPLATE_TYPES>
    struct is_optional_impl<optional<BOOST_PYTHON_TEMPLATE_ARGS> > {

        BOOST_STATIC_CONSTANT(bool, value = true);
    };

    template <class T>
    struct is_optional : is_optional_impl<T>
    {
        typedef mpl::bool_c<is_optional_impl<T>::value> type;
        BOOST_MPL_AUX_LAMBDA_SUPPORT(1,is_optional,(T)) // needed for MSVC & Borland
    };
    #endif // defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

} // namespace detail

template <class DerivedT>
struct init_base {

    DerivedT const& derived() const
    { return *static_cast<DerivedT const*>(this); }
};

template <class CallPoliciesT, class InitT>
struct init_with_call_policies
: public init_base<init_with_call_policies<CallPoliciesT, InitT> >
{
    BOOST_STATIC_CONSTANT(int, n_arguments = InitT::n_arguments);
    BOOST_STATIC_CONSTANT(int, n_defaults = InitT::n_defaults);

    typedef typename InitT::reversed_args reversed_args;

    init_with_call_policies(CallPoliciesT const& policies_, char const* doc_)
    : policies(policies_), doc(doc_) {}

    char const* doc_string() const
    { return doc; }

    CallPoliciesT
    call_policies() const
    { return policies; }

    CallPoliciesT policies;
    char const* doc;
};

template <BOOST_PYTHON_TEMPLATE_TYPES>
struct init : public init_base<init<BOOST_PYTHON_TEMPLATE_ARGS> >
{
    typedef init<BOOST_PYTHON_TEMPLATE_ARGS> self_t;

    init(char const* doc_ = 0)
    : doc(doc_) {}

    char const* doc_string() const
    { return doc; }

    default_call_policies
    call_policies() const
    { return default_call_policies(); }

    template <class CallPoliciesT>
    init_with_call_policies<CallPoliciesT, self_t>
    operator[](CallPoliciesT const& policies) const
    { return init_with_call_policies<CallPoliciesT, self_t>(policies, doc); }

    typedef detail::type_list<BOOST_PYTHON_TEMPLATE_ARGS> signature_;
    typedef typename mpl::end<signature_>::type finish;

    // Find the optional<> element, if any
    typedef typename mpl::find_if<
        signature_, detail::is_optional<mpl::_>
    >::type opt;


    // Check to make sure the optional<> element, if any, is the last one
    typedef typename mpl::apply_if<
        is_same<opt,finish>
        , mpl::identity<opt>
        , mpl::next<opt>
    >::type expected_finish;
    BOOST_STATIC_ASSERT((is_same<expected_finish, finish>::value));

    typedef typename mpl::apply_if<
        is_same<opt,finish>
        , mpl::list0<>
        , opt
    >::type optional_args;

    // Count the number of default args
    BOOST_STATIC_CONSTANT(int, n_defaults = mpl::size<optional_args>::value);

    typedef typename mpl::iterator_range<
        typename mpl::begin<signature_>::type
        , opt
    >::type required_args;

    // Build a reverse image of all the args, including optionals
    typedef typename mpl::fold<
        required_args
        , mpl::list0<>
        , mpl::push_front<mpl::_1, mpl::_2>
    >::type reversed_required;

    typedef typename mpl::fold<
        optional_args
        , reversed_required
        , mpl::push_front<mpl::_1, mpl::_2>
    >::type reversed_args;

    // Count the maximum number of arguments
    BOOST_STATIC_CONSTANT(int, n_arguments = mpl::size<reversed_args>::value);

    char const* doc;
};

template <> // specialization for zero args
struct init<> : public init_base<init<> >
{
    typedef init<> self_t;

    init(char const* doc_ = 0)
    : doc(doc_) {}

    char const* doc_string() const
    { return doc; }

    default_call_policies
    call_policies() const
    { return default_call_policies(); }

    template <class CallPoliciesT>
    init_with_call_policies<CallPoliciesT, self_t>
    operator[](CallPoliciesT const& policies) const
    { return init_with_call_policies<CallPoliciesT, self_t>(policies, doc); }

    BOOST_STATIC_CONSTANT(int, n_defaults = 0);
    BOOST_STATIC_CONSTANT(int, n_arguments = 0);

    typedef detail::type_list<> reversed_args;

    char const* doc;
};

///////////////////////////////////////////////////////////////////////////////
//
//  optional
//
//      optional<T0...TN>::type returns a typelist.
//
///////////////////////////////////////////////////////////////////////////////
template <BOOST_PYTHON_TEMPLATE_TYPES>
struct optional
    : detail::type_list<BOOST_PYTHON_TEMPLATE_ARGS>
{
};

namespace detail
{
  template <class ClassT, class CallPoliciesT, class ReversedArgs>
  void def_init_reversed(ClassT& cl, ReversedArgs const&, CallPoliciesT const& policies, char const* doc)
  {
      typedef typename mpl::fold<
          ReversedArgs
          , mpl::list0<>
          , mpl::push_front<mpl::_1,mpl::_2>
          >::type args;

      cl.def_init(args(), policies, doc);
  }

  ///////////////////////////////////////////////////////////////////////////////
  //
  //  define_class_init_helper<N>::apply
  //
  //      General case
  //
  //      Accepts a class_ and an arguments list. Defines a constructor
  //      for the class given the arguments and recursively calls
  //      define_class_init_helper<N-1>::apply with one less arguments (the
  //      rightmost argument is shaved off)
  //
  ///////////////////////////////////////////////////////////////////////////////
  template <int N>
  struct define_class_init_helper {

      template <class ClassT, class CallPoliciesT, class ReversedArgs>
      static void apply(ClassT& cl, CallPoliciesT const& policies, ReversedArgs const& args, char const* doc)
      {
          def_init_reversed(cl, args, policies, doc);

          typename mpl::pop_front<ReversedArgs>::type next;
          define_class_init_helper<N-1>::apply(cl, policies, next, doc);
      }
  };

  ///////////////////////////////////////////////////////////////////////////////
  //
  //  define_class_init_helper<0>::apply
  //
  //      Terminal case
  //
  //      Accepts a class_ and an arguments list. Defines a constructor
  //      for the class given the arguments.
  //
  ///////////////////////////////////////////////////////////////////////////////
  template <>
  struct define_class_init_helper<0> {

      template <class ClassT, class CallPoliciesT, class ReversedArgs>
      static void apply(ClassT& cl, CallPoliciesT const& policies, ReversedArgs const& args, char const* doc)
      {
          def_init_reversed(cl, args, policies, doc);
      }
  };
}

///////////////////////////////////////////////////////////////////////////////
//
//  define_init
//
//      Accepts a class_ and an init-list. Defines a set of constructors for
//      the class given the arguments. The init list (see init above) has
//      n_defaults (number of default arguments and n_arguments (number of
//      actual arguments). This function defines n_defaults + 1 constructors
//      for the class. Each constructor after the first has one less argument
//      to its right. Example:
//
//          init<int, default<char, long, double>
//
//      Defines:
//
//          __init__(int, char, long, double)
//          __init__(int, char, long)
//          __init__(int, char)
//          __init__(int)
//
///////////////////////////////////////////////////////////////////////////////
template <class ClassT, class InitT>
void
define_init(ClassT& cl, InitT const& i)
{
    typedef typename InitT::reversed_args reversed_args;
    detail::define_class_init_helper<InitT::n_defaults>::apply(
        cl, i.call_policies(), reversed_args(), i.doc_string());
}

}} // namespace boost::python

#undef BOOST_PYTHON_TEMPLATE_TYPES_WITH_DEFAULT
#undef BOOST_PYTHON_TEMPLATE_TYPES
#undef BOOST_PYTHON_TEMPLATE_ARGS
#undef BOOST_PYTHON_IS_OPTIONAL_VALUE
#undef BOOST_PYTHON_APPEND_TO_INIT

///////////////////////////////////////////////////////////////////////////////
#endif // INIT_JDG20020820_HPP








