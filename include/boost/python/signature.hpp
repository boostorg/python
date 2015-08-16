///////////////////////////////////////////////////////////////////////////////
//
// Copyright David Abrahams 2002, Joel de Guzman, 2002.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////
# ifndef SIGNATURE_JDG20020813_HPP
#  define SIGNATURE_JDG20020813_HPP

# include <boost/python/detail/prefix.hpp>

# include <boost/mpl/if.hpp>
# include <boost/type_traits/is_convertible.hpp>
# include <boost/type_traits/is_class.hpp>
# include <boost/type_traits/conditional.hpp>
# include <boost/type_traits/decay.hpp>
# include <boost/function_types/result_type.hpp>
# include <boost/function_types/parameter_types.hpp>
# include <boost/function_types/components.hpp>
# include <boost/function_types/is_function_pointer.hpp>
# include <boost/mpl/vector.hpp>
# include <boost/mpl/insert_range.hpp>
# include <boost/mpl/copy.hpp>
# include <boost/mpl/joint_view.hpp>
# include <boost/mpl/transform.hpp>
# include <boost/type_traits/remove_cv.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace python { namespace detail {

// A metafunction returning C1 if C1 is derived from C2, and C2
// otherwise
template <class C1, class C2>
struct most_derived
{
    typedef typename mpl::if_<
        is_convertible<C1*,C2*>
      , C1
      , C2
    >::type type;
};

//  The following macros generate expansions for::
//
//      template <class RT, class T0... class TN>
//      inline mpl::vector<RT, T0...TN>
//      get_signature(RT(BOOST_PYTHON_FN_CC *)(T0...TN), void* = 0)
//      {
//          return mpl::list<RT, T0...TN>();
//      }
//
//    where BOOST_PYTHON_FN_CC is a calling convention keyword, can be
//
//        empty, for default calling convention
//        __cdecl (if BOOST_PYTHON_ENABLE_CDECL is defined)
//        __stdcall (if BOOST_PYTHON_ENABLE_STDCALL is defined)
//        __fastcall (if BOOST_PYTHON_ENABLE_FASTCALL is defined)
//
//   And, for an appropriate assortment of cv-qualifications::
//
//      template <class RT, class ClassT, class T0... class TN>
//      inline mpl::vector<RT, ClassT&, T0...TN>
//      get_signature(RT(BOOST_PYTHON_FN_CC ClassT::*)(T0...TN) cv))
//      {
//          return mpl::list<RT, ClassT&, T0...TN>();
//      }
//
//      template <class Target, class RT, class ClassT, class T0... class TN>
//      inline mpl::vector<
//          RT
//        , typename most_derived<Target, ClassT>::type&
//        , T0...TN
//      >
//      get_signature(RT(BOOST_PYTHON_FN_CC ClassT::*)(T0...TN) cv), Target*)
//      {
//          return mpl::list<RT, ClassT&, T0...TN>();
//      }
//
//  There are two forms for invoking get_signature::
//
//      get_signature(f)
//
//  and ::
//
//      get_signature(f,(Target*)0)
//
//  These functions extract the return type, class (for member
//  functions) and arguments of the input signature and stuff them in
//  an mpl type sequence (the calling convention is dropped).
//  Note that cv-qualification is dropped from
//  the "hidden this" argument of member functions; that is a
//  necessary sacrifice to ensure that an lvalue from_python converter
//  is used.  A pointer is not used so that None will be rejected for
//  overload resolution.
//
//  The second form of get_signature essentially downcasts the "hidden
//  this" argument of member functions to Target, because the function
//  may actually be a member of a base class which is not wrapped, and
//  in that case conversion from python would fail.
//
// @group {

template<typename T>
struct is_callable_detect {
private:
    typedef char(&yes)[1];
    typedef char(&no)[2];

    struct Fallback { void operator()(); };
    struct Derived : T, Fallback { };

    template<typename U, U> struct Check;

    template<typename>
    static yes test(...);

    template<typename C>
    static no test(Check<void (Fallback::*)(), &C::operator()>*);

public:
    static const bool value = sizeof(test<Derived>(0)) == sizeof(yes);
};

template<typename T>
struct is_callable
    : conditional<
        is_class<T>::value,
        is_callable_detect<T>,
        false_type
    >::type
{ };

template<class CallableT, class Target, class Enable = void>
struct get_signature_helper;


template<class CallableT, class Target>
struct get_signature_helper<CallableT, Target, typename enable_if_c<is_function<CallableT>::value>::type>{
    typedef typename function_types::components<CallableT>::types components;

    inline static components signature(CallableT, Target * = 0){ return components(); }
};


#if (__cplusplus > 199711L) && !defined(BOOST_NO_CXX11_LAMBDAS)
template<class CallableT, class Target>
struct get_signature_helper<CallableT, Target, typename enable_if_c<is_callable<CallableT>::value>::type>{
    typedef decltype(&CallableT::operator()) operator_type;
    typedef typename function_types::components<operator_type>::types components;

    inline static components signature(CallableT, Target * = 0){ return components(); }
};
#endif

template<class CallableT, class Target>
struct get_signature_helper<CallableT, Target, typename enable_if_c<function_types::is_function_pointer<CallableT>::value>::type>{
    typedef typename function_types::components<typename decay<CallableT>::type>::types components;

    inline static components signature(CallableT, Target * = 0){ return components(); }
};

template<class CallableT, class Target>
struct get_signature_helper<CallableT, Target, typename enable_if_c<is_member_function_pointer<CallableT>::value>::type>{
    typedef typename function_types::components<CallableT>::types base_components;
    typedef typename mpl::at_c<base_components, 0>::type return_type;
    typedef typename decay<typename
        remove_cv<
            typename mpl::at_c<base_components, 1>::type
        >::type
    >::type class_type;

    typedef typename mpl::advance_c<typename mpl::begin<base_components>::type,  2>::type param_types_begin;
    typedef typename mpl::end<base_components>::type param_types_end;
    typedef mpl::iterator_range<param_types_begin, param_types_end> param_types;

    typedef typename mpl::if_c<is_same<Target, void>::value,
        class_type,
        typename most_derived<Target, class_type>::type
    >::type target_type;

    typedef mpl::vector<return_type, target_type&> result_and_class_type;
    typedef mpl::joint_view<result_and_class_type, param_types> types_view;

    typedef typename mpl::reverse_copy<types_view, mpl::front_inserter< mpl::vector0<> > >::type target_components;
    typedef target_components components;

    inline static components signature(CallableT, Target * = 0){ return components();}
};

template<class CallableT, class Target = void>
inline typename get_signature_helper<CallableT, Target>::components get_signature(CallableT c, Target *p = 0){
    return get_signature_helper<CallableT, Target>::signature(boost::forward<CallableT>(c), p);
}

}}} // namespace boost::python::detail


# endif // SIGNATURE_JDG20020813_HPP
