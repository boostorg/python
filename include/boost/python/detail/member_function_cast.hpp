// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef MEMBER_FUNCTION_CAST_DWA2002311_HPP
# define MEMBER_FUNCTION_CAST_DWA2002311_HPP
# include <boost/mpl/select_type.hpp>
# include <boost/type_traits/composite_traits.hpp>

namespace boost { namespace python { namespace detail { 

template <class S, class FT>
struct cast_helper
{
    struct yes_helper
    {
        static FT stage3(FT x) { return x; }
    };

    struct no_helper
    {
        template <class T>
        static T stage3(T x) { return x; }
    };

    static yes_helper stage2(S*) { return yes_helper(); }
    static no_helper stage2(void*) { return no_helper(); }
};

struct non_member_function_cast_impl
{
    template <class T>
    static non_member_function_cast_impl stage1(T) { return non_member_function_cast_impl(); }

    template <class T>
    static non_member_function_cast_impl stage2(T) { return non_member_function_cast_impl(); }

    template <class T>
    T stage3(T x) { return x; }
};

template <class T>
struct member_function_cast_impl
{
    template <class S, class R>
    static cast_helper<S,R(T::*)()> stage1(R (S::*)())
    {
        return cast_helper<S,R(T::*)()>();
    }

    template <class S, class R, class A0>
    static cast_helper<S,R(T::*)(A0)> stage1(R (S::*)(A0))
    {
        return cast_helper<S,R(T::*)(A0)>();
    }

    template <class S, class R, class A0, class A1>
    static cast_helper<S,R(T::*)(A0,A1) > stage1(R (S::*)(A0,A1))
    {
        return cast_helper<R(S::*)(A0,A1),R(T::*)(A0,A1) >();
    }

    template <class S, class R, class A0, class A1,class A2>
    static cast_helper<S,R(T::*)(A0,A1,A2) > stage1(R (S::*)(A0,A1,A2))
    {
        return cast_helper<R(S::*)(A0,A1,A2),R(T::*)(A0,A1,A2) >();
    }

    template <class S, class R, class A0, class A1, class A2, class A3>
    static cast_helper<S,R(T::*)(A0,A1,A2,A3)> stage1(R (S::*)(A0,A1,A2,A3))
    {
        return cast_helper<S,R(T::*)(A0,A1,A2,A3)>();
    }

    template <class S, class R, class A0, class A1, class A2, class A3, class A4>
    static cast_helper<S,R(T::*)(A0,A1,A2,A3,A4)> stage1(R (S::*)(A0,A1,A2,A3,A4))
    {
        return cast_helper<S,R(T::*)(A0,A1,A2,A3,A4)>();
    }

    template <class S, class R, class A0, class A1, class A2, class A3, class A4, class A5>
    static cast_helper<S,R(T::*)(A0,A1,A2,A3,A4,A5)> stage1(R (S::*)(A0,A1,A2,A3,A4,A5))
    {
        return cast_helper<S,R(T::*)(A0,A1,A2,A3,A4,A5)>();
    }

# if 1
    template <class S, class R>
    static cast_helper<S,R(T::*)()const> stage1(R (S::*)()const)
    {
        return cast_helper<S,R(T::*)()const>();
    }

    template <class S, class R, class A0>
    static cast_helper<S,R(T::*)(A0)const> stage1(R (S::*)(A0)const)
    {
        return cast_helper<S,R(T::*)(A0)const>();
    }

    template <class S, class R, class A0, class A1>
    static cast_helper<S,R(T::*)(A0,A1)const> stage1(R (S::*)(A0,A1)const)
    {
        return cast_helper<S,R(T::*)(A0,A1)const>();
    }

    template <class S, class R, class A0, class A1,class A2>
    static cast_helper<S,R(T::*)(A0,A1,A2)const> stage1(R (S::*)(A0,A1,A2)const)
    {
        return cast_helper<S,R(T::*)(A0,A1,A2)const>();
    }

    template <class S, class R, class A0, class A1, class A2, class A3>
    static cast_helper<S,R(T::*)(A0,A1,A2,A3)const> stage1(R (S::*)(A0,A1,A2,A3)const)
    {
        return cast_helper<S,R(T::*)(A0,A1,A2,A3)const>();
    }

    template <class S, class R, class A0, class A1, class A2, class A3, class A4>
    static cast_helper<S,R(T::*)(A0,A1,A2,A3,A4)const> stage1(R (S::*)(A0,A1,A2,A3,A4)const)
    {
        return cast_helper<S,R(T::*)(A0,A1,A2,A3,A4)const>();
    }

    template <class S, class R, class A0, class A1, class A2, class A3, class A4, class A5>
    static cast_helper<S,R(T::*)(A0,A1,A2,A3,A4,A5)const> stage1(R (S::*)(A0,A1,A2,A3,A4,A5)const)
    {
        return cast_helper<S,R(T::*)(A0,A1,A2,A3,A4,A5)const>();
    }

    template <class S, class R>
    static cast_helper<S,R(T::*)()volatile> stage1(R (S::*)()volatile)
    {
        return cast_helper<S,R(T::*)()volatile>();
    }

    template <class S, class R, class A0>
    static cast_helper<S,R(T::*)(A0)volatile> stage1(R (S::*)(A0)volatile)
    {
        return cast_helper<S,R(T::*)(A0)volatile>();
    }

    template <class S, class R, class A0, class A1>
    static cast_helper<S,R(T::*)(A0,A1)volatile> stage1(R (S::*)(A0,A1)volatile)
    {
        return cast_helper<S,R(T::*)(A0,A1)volatile>();
    }

    template <class S, class R, class A0, class A1,class A2>
    static cast_helper<S,R(T::*)(A0,A1,A2)volatile> stage1(R (S::*)(A0,A1,A2)volatile)
    {
        return cast_helper<S,R(T::*)(A0,A1,A2)volatile>();
    }

    template <class S, class R, class A0, class A1, class A2, class A3>
    static cast_helper<S,R(T::*)(A0,A1,A2,A3)volatile> stage1(R (S::*)(A0,A1,A2,A3)volatile)
    {
        return cast_helper<S,R(T::*)(A0,A1,A2,A3)volatile>();
    }

    template <class S, class R, class A0, class A1, class A2, class A3, class A4>
    static cast_helper<S,R(T::*)(A0,A1,A2,A3,A4)volatile> stage1(R (S::*)(A0,A1,A2,A3,A4)volatile)
    {
        return cast_helper<S,R(T::*)(A0,A1,A2,A3,A4)volatile>();
    }

    template <class S, class R, class A0, class A1, class A2, class A3, class A4, class A5>
    static cast_helper<S,R(T::*)(A0,A1,A2,A3,A4,A5)volatile> stage1(R (S::*)(A0,A1,A2,A3,A4,A5)volatile)
    {
        return cast_helper<S,R(T::*)(A0,A1,A2,A3,A4,A5)volatile>();
    }

// # ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    template <class S, class R>
    static cast_helper<S,R(T::*)()const volatile> stage1(R (S::*)()const volatile)
    {
        return cast_helper<S,R(T::*)()const volatile>();
    }

    template <class S, class R, class A0>
    static cast_helper<S,R(T::*)(A0)const volatile> stage1(R (S::*)(A0)const volatile)
    {
        return cast_helper<S,R(T::*)(A0)const volatile>();
    }

    template <class S, class R, class A0, class A1>
    static cast_helper<S,R(T::*)(A0,A1)const volatile> stage1(R (S::*)(A0,A1)const volatile)
    {
        return cast_helper<S,R(T::*)(A0,A1)const volatile>();
    }

    template <class S, class R, class A0, class A1,class A2>
    static cast_helper<S,R(T::*)(A0,A1,A2)const volatile> stage1(R (S::*)(A0,A1,A2)const volatile)
    {
        return cast_helper<S,R(T::*)(A0,A1,A2)const volatile>();
    }

    template <class S, class R, class A0, class A1, class A2, class A3>
    static cast_helper<S,R(T::*)(A0,A1,A2,A3)const volatile> stage1(R (S::*)(A0,A1,A2,A3)const volatile)
    {
        return cast_helper<S,R(T::*)(A0,A1,A2,A3)const volatile>();
    }

    template <class S, class R, class A0, class A1, class A2, class A3, class A4>
    static cast_helper<S,R(T::*)(A0,A1,A2,A3,A4)const volatile> stage1(R (S::*)(A0,A1,A2,A3,A4)const volatile)
    {
        return cast_helper<S,R(T::*)(A0,A1,A2,A3,A4)const volatile>();
    }

    template <class S, class R, class A0, class A1, class A2, class A3, class A4, class A5>
    static cast_helper<S,R(T::*)(A0,A1,A2,A3,A4,A5)const volatile> stage1(R (S::*)(A0,A1,A2,A3,A4,A5)const volatile)
    {
        return cast_helper<S,R(T::*)(A0,A1,A2,A3,A4,A5)const volatile>();
    }
# endif 
};


template <class T, class SF>
struct member_function_cast
    : mpl::select_type<
        is_member_function_pointer<SF>::value
        , member_function_cast_impl<T>
        , non_member_function_cast_impl
    >::type
{
};

}}} // namespace boost::python::detail

#endif // MEMBER_FUNCTION_CAST_DWA2002311_HPP
