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

#include <boost/mpl/type_list.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/mpl/select_type.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/pop_front.hpp>
#include <boost/mpl/pop_back.hpp>

#include <boost/static_assert.hpp>
#include <boost/preprocessor/enum_params_with_a_default.hpp>
#include <boost/preprocessor/enum_params.hpp>
#include <boost/preprocessor/repeat.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/inc.hpp>
#include <boost/preprocessor/dec.hpp>

///////////////////////////////////////////////////////////////////////////////
#define BOOST_PYTHON_TEMPLATE_TYPES_WITH_DEFAULT                                \
    BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT                                         \
    (                                                                           \
        BOOST_PYTHON_MAX_ARITY,                                                 \
        class T,                                                                \
        boost::mpl::null_argument                                               \
    )                                                                           \

#define BOOST_PYTHON_TEMPLATE_TYPES                                             \
    BOOST_PP_ENUM_PARAMS                                                        \
    (                                                                           \
        BOOST_PYTHON_MAX_ARITY,                                                 \
        class T                                                                 \
    )                                                                           \

#define BOOST_PYTHON_TEMPLATE_ARGS                                              \
    BOOST_PP_ENUM_PARAMS                                                        \
    (                                                                           \
        BOOST_PYTHON_MAX_ARITY,                                                 \
        T                                                                       \
    )                                                                           \

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
    //  is_nil<T>::value
    //
    //      This metaprogram checks if T is nil
    //
    ///////////////////////////////////////////////////////////////////////////
    template <class T>
    struct is_nil : public boost::is_same<T, boost::mpl::null_argument> {};

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
    };

    ///////////////////////////////////////
    #else // defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

    template <class T>
    struct is_optional {

        BOOST_STATIC_CONSTANT(bool, value = false);
    };

    template <BOOST_PYTHON_TEMPLATE_TYPES>
    struct is_optional<optional<BOOST_PYTHON_TEMPLATE_ARGS> > {

        BOOST_STATIC_CONSTANT(bool, value = true);
    };

    #endif // defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

    ///////////////////////////////////////////////////////////////////////////
    //
    //  append_to_init<ListT, T> [ and helpers ]
    //
    //      A metaprogram appends T to the initializer type list
    //
    ///////////////////////////////////////////////////////////////////////////
    struct append_to_init_helper1 {

        //  Case 1: default case, just push T to the back of ListT

        template <class ListT, class T>
        struct apply {

            typedef typename boost::mpl::push_back<ListT, T>::sequence sequence;
        };
    };

    struct append_to_init_helper2 {

        template <class ListT, class T>
        struct apply {

        //  Case 2: optional case, T is an optional, append all
        //          the contents of the optional T into back of ListT

            typedef typename boost::mpl::for_each
            <
                typename T::sequence,
                ListT,
                boost::mpl::push_back<boost::mpl::_1, boost::mpl::_2>
            >::state sequence;
        };
    };

    struct append_to_init_helper3 {

        //  Case 3: nil case, we found a nil, do nothing

        template <class ListT, class T>
        struct apply {

            typedef ListT sequence;
        };
    };

    template <class ListT, class T>
    struct append_to_init {

        typedef typename boost::mpl::select_type
        <
            is_optional<T>::value,              // if
            append_to_init_helper2,             // then
            typename boost::mpl::select_type    // else
            <
                is_nil<T>::value,               // if
                append_to_init_helper3,         // then
                append_to_init_helper1          // else
            >::type
        >::type helper;

        typedef typename helper::template apply<ListT, T>::sequence sequence;
    };

    ///////////////////////////////////////////////////////////////////////////
    //
    //  check_init_params [ and helpers ]
    //
    //      Check the init template parameters. Detect illegal
    //      arguments such as:
    //
    //      init<int, optional<char, long>, int> // BAD trailing int
    //      init<optional<char, long>, optional<char> > // BAD optional used twice
    //
    ///////////////////////////////////////////////////////////////////////////
    template <int N>
    struct check_init_params_helper {

        template <class ListT>
        struct apply {

        //  case where size of sequence is not zero

            typedef typename boost::mpl::pop_front<ListT>::sequence rest;

            enum {

                //  if first is optional then there must be no more
                //  elements to its right. if not then recurse and check
                //  the rest of the type list

                first_is_optional =
                    is_optional<typename boost::mpl::at<0, ListT>::type>::value,
                size_of_rest = boost::mpl::size<rest>::value,
                rest_is_nil = (size_of_rest == 0),
                is_ok = first_is_optional ? rest_is_nil :
                    check_init_params_helper<size_of_rest>
                        ::template apply<rest>::is_ok
            };
        };
    };

    template <>
    struct check_init_params_helper<0> {

        //  case where size of sequence is zero

        template <class ListT>
        struct apply {

            enum { is_ok = true };
        };
    };

    struct init_base {};

    template <BOOST_PYTHON_TEMPLATE_TYPES>
    struct check_init_params : init_base {

        typedef boost::mpl::type_list<BOOST_PYTHON_TEMPLATE_ARGS> params;

        BOOST_STATIC_ASSERT
        (
            check_init_params_helper<boost::mpl::size<params>::value>
                ::template apply<params>::is_ok
        );
    };

    ///////////////////////////////////////////////////////////////////////////
    //
    //  count_optional_types [ and helpers ]
    //
    //      count_optional_types<T0..TN>::value computes the number of
    //      optional types (see init and optional below). For example:
    //
    //      init<int, string, optional<char, long, double> >::value == 3
    //
    ///////////////////////////////////////////////////////////////////////////
    template <class T>
    struct count_optionals1 {

        BOOST_STATIC_CONSTANT(int, value = 0);
    };

    template <class T>
    struct count_optionals2 {

        BOOST_STATIC_CONSTANT(
            int, value = boost::mpl::size<typename T::sequence>::value);
    };

    template <class T>
    struct count_optionals
    :   boost::mpl::select_type
        <
            is_optional<T>::value,  //  if
            count_optionals2<T>,    //  then
            count_optionals1<T>     //  else
        >::type
    {
    };

    template <BOOST_PYTHON_TEMPLATE_TYPES>
    struct count_optional_types {

        BOOST_STATIC_CONSTANT(int, value =
            count_optionals<T0>::value +
            count_optionals<T1>::value +
            count_optionals<T2>::value
        );
    };

} // namespace detail

///////////////////////////////////////////////////////////////////////////////
//
//  init
//
//      init<T0...TN>::sequence returns a typelist. One of T0..TN
//      mat be an optional<...> see below. There should be only one
//      optional in the input types and an optional should be the
//      last in the list.
//
///////////////////////////////////////////////////////////////////////////////
#define BOOST_PYTHON_APPEND_TO_INIT(INDEX, D)                                   \
    typedef typename detail::append_to_init                                     \
    <                                                                           \
        BOOST_PP_CAT(l, INDEX),                                                 \
        BOOST_PP_CAT(T, BOOST_PP_INC(INDEX))                                    \
    >::sequence BOOST_PP_CAT(l, BOOST_PP_INC(INDEX));                           \


template <BOOST_PYTHON_TEMPLATE_TYPES>
struct init : detail::check_init_params<BOOST_PYTHON_TEMPLATE_ARGS>
{
    typedef boost::mpl::type_list<T0> l0;
    BOOST_PP_REPEAT
        (BOOST_PP_DEC(BOOST_PYTHON_MAX_ARITY), BOOST_PYTHON_APPEND_TO_INIT, 0)

    typedef BOOST_PP_CAT(l, BOOST_PP_DEC(BOOST_PYTHON_MAX_ARITY)) sequence;

    BOOST_STATIC_CONSTANT(int, n_arguments = boost::mpl::size<sequence>::value);

    BOOST_STATIC_CONSTANT(int, n_defaults =
        (detail::count_optional_types<BOOST_PYTHON_TEMPLATE_ARGS>::value)
    );
};

///////////////////////////////////////////////////////////////////////////////
//
//  optional
//
//      optional<T0...TN>::sequence returns a typelist.
//
///////////////////////////////////////////////////////////////////////////////
template <BOOST_PYTHON_TEMPLATE_TYPES>
struct optional {

    typedef boost::mpl::type_list<BOOST_PYTHON_TEMPLATE_ARGS> sequence;
};

namespace detail {

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

        template <class ClassT, class CallPoliciesT, class ArgsT>
        static void apply(ClassT& cl, CallPoliciesT const& policies, ArgsT const& args, char const* doc)
        {
            cl.def_init(args, policies, doc);
            typename boost::mpl::pop_back<ArgsT>::sequence next;
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

        template <class ClassT, class CallPoliciesT, class ArgsT>
        static void apply(ClassT& cl, CallPoliciesT const& policies, ArgsT const& args, char const* doc)
        {
            cl.def_init(args, policies, doc);
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
template <class ClassT, class CallPoliciesT, class InitT>
void
define_init(ClassT& cl, InitT const& i, CallPoliciesT const& policies, char const* doc)
{
    enum { n_defaults_plus_1 = InitT::n_defaults + 1 };
    typedef typename InitT::sequence args_t;
    detail::define_class_init_helper<n_defaults_plus_1>::apply(cl, policies, args_t(), doc);
}

}} // namespace boost::python

#undef BOOST_PYTHON_TEMPLATE_TYPES_WITH_DEFAULT
#undef BOOST_PYTHON_TEMPLATE_TYPES
#undef BOOST_PYTHON_TEMPLATE_ARGS
#undef BOOST_PYTHON_IS_OPTIONAL_VALUE
#undef BOOST_PYTHON_APPEND_TO_INIT

///////////////////////////////////////////////////////////////////////////////
#endif // INIT_JDG20020820_HPP








