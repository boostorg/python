//  (C) Copyright David Abrahams 2002. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
//  This work was funded in part by Lawrence Berkeley and Lawrence
//  Livermore National Labs
//
//  This file generated for 5-argument member functions and 6-argument free
//  functions by gen_signature.py

#ifndef SIGNATURE_DWA2002128_HPP
# define SIGNATURE_DWA2002128_HPP

# include <boost/mpl/type_list.hpp>

namespace boost { namespace python { namespace detail {

template <class R>
mpl::type_list<R>
signature(R (*)())
{
    return mpl::type_list<R>();
}

template <class R, class A0>
mpl::type_list<R,A0>
signature(R (*)(A0))
{
    return mpl::type_list<R,A0>();
}

template <class R, class A0, class A1>
mpl::type_list<R,A0,A1>
signature(R (*)(A0, A1))
{
    return mpl::type_list<R,A0,A1>();
}

template <class R, class A0, class A1, class A2>
mpl::type_list<R,A0,A1,A2>
signature(R (*)(A0, A1, A2))
{
    return mpl::type_list<R,A0,A1,A2>();
}

template <class R, class A0, class A1, class A2, class A3>
mpl::type_list<R,A0,A1,A2,A3>
signature(R (*)(A0, A1, A2, A3))
{
    return mpl::type_list<R,A0,A1,A2,A3>();
}

template <class R, class A0, class A1, class A2, class A3, class A4>
mpl::type_list<R,A0,A1,A2,A3,A4>
signature(R (*)(A0, A1, A2, A3, A4))
{
    return mpl::type_list<R,A0,A1,A2,A3,A4>();
}

template <class R, class A0, class A1, class A2, class A3, class A4, class A5>
mpl::type_list<R,A0,A1,A2,A3,A4,A5>
signature(R (*)(A0, A1, A2, A3, A4, A5))
{
    return mpl::type_list<R,A0,A1,A2,A3,A4,A5>();
}
template <class R, class A0>
mpl::type_list<R,A0&> signature(R (A0::*)())
{
    return mpl::type_list<R,A0&>();
}

template <class R, class A0, class A1>
mpl::type_list<R,A0&,A1> signature(R (A0::*)(A1))
{
    return mpl::type_list<R,A0&,A1>();
}

template <class R, class A0, class A1, class A2>
mpl::type_list<R,A0&,A1,A2> signature(R (A0::*)(A1, A2))
{
    return mpl::type_list<R,A0&,A1,A2>();
}

template <class R, class A0, class A1, class A2, class A3>
mpl::type_list<R,A0&,A1,A2,A3> signature(R (A0::*)(A1, A2, A3))
{
    return mpl::type_list<R,A0&,A1,A2,A3>();
}

template <class R, class A0, class A1, class A2, class A3, class A4>
mpl::type_list<R,A0&,A1,A2,A3,A4> signature(R (A0::*)(A1, A2, A3, A4))
{
    return mpl::type_list<R,A0&,A1,A2,A3,A4>();
}

template <class R, class A0, class A1, class A2, class A3, class A4, class A5>
mpl::type_list<R,A0&,A1,A2,A3,A4,A5> signature(R (A0::*)(A1, A2, A3, A4, A5))
{
    return mpl::type_list<R,A0&,A1,A2,A3,A4,A5>();
}


template <class R, class A0>
mpl::type_list<R,A0 const&> signature(R (A0::*)() const)
{
    return mpl::type_list<R,A0 const&>();
}

template <class R, class A0, class A1>
mpl::type_list<R,A0 const&,A1> signature(R (A0::*)(A1) const)
{
    return mpl::type_list<R,A0 const&,A1>();
}

template <class R, class A0, class A1, class A2>
mpl::type_list<R,A0 const&,A1,A2> signature(R (A0::*)(A1, A2) const)
{
    return mpl::type_list<R,A0 const&,A1,A2>();
}

template <class R, class A0, class A1, class A2, class A3>
mpl::type_list<R,A0 const&,A1,A2,A3> signature(R (A0::*)(A1, A2, A3) const)
{
    return mpl::type_list<R,A0 const&,A1,A2,A3>();
}

template <class R, class A0, class A1, class A2, class A3, class A4>
mpl::type_list<R,A0 const&,A1,A2,A3,A4> signature(R (A0::*)(A1, A2, A3, A4) const)
{
    return mpl::type_list<R,A0 const&,A1,A2,A3,A4>();
}

template <class R, class A0, class A1, class A2, class A3, class A4, class A5>
mpl::type_list<R,A0 const&,A1,A2,A3,A4,A5> signature(R (A0::*)(A1, A2, A3, A4, A5) const)
{
    return mpl::type_list<R,A0 const&,A1,A2,A3,A4,A5>();
}


template <class R, class A0>
mpl::type_list<R,A0 volatile&> signature(R (A0::*)() volatile)
{
    return mpl::type_list<R,A0 volatile&>();
}

template <class R, class A0, class A1>
mpl::type_list<R,A0 volatile&,A1> signature(R (A0::*)(A1) volatile)
{
    return mpl::type_list<R,A0 volatile&,A1>();
}

template <class R, class A0, class A1, class A2>
mpl::type_list<R,A0 volatile&,A1,A2> signature(R (A0::*)(A1, A2) volatile)
{
    return mpl::type_list<R,A0 volatile&,A1,A2>();
}

template <class R, class A0, class A1, class A2, class A3>
mpl::type_list<R,A0 volatile&,A1,A2,A3> signature(R (A0::*)(A1, A2, A3) volatile)
{
    return mpl::type_list<R,A0 volatile&,A1,A2,A3>();
}

template <class R, class A0, class A1, class A2, class A3, class A4>
mpl::type_list<R,A0 volatile&,A1,A2,A3,A4> signature(R (A0::*)(A1, A2, A3, A4) volatile)
{
    return mpl::type_list<R,A0 volatile&,A1,A2,A3,A4>();
}

template <class R, class A0, class A1, class A2, class A3, class A4, class A5>
mpl::type_list<R,A0 volatile&,A1,A2,A3,A4,A5> signature(R (A0::*)(A1, A2, A3, A4, A5) volatile)
{
    return mpl::type_list<R,A0 volatile&,A1,A2,A3,A4,A5>();
}


template <class R, class A0>
mpl::type_list<R,A0 const volatile&> signature(R (A0::*)() const volatile)
{
    return mpl::type_list<R,A0 const volatile&>();
}

template <class R, class A0, class A1>
mpl::type_list<R,A0 const volatile&,A1> signature(R (A0::*)(A1) const volatile)
{
    return mpl::type_list<R,A0 const volatile&,A1>();
}

template <class R, class A0, class A1, class A2>
mpl::type_list<R,A0 const volatile&,A1,A2> signature(R (A0::*)(A1, A2) const volatile)
{
    return mpl::type_list<R,A0 const volatile&,A1,A2>();
}

template <class R, class A0, class A1, class A2, class A3>
mpl::type_list<R,A0 const volatile&,A1,A2,A3> signature(R (A0::*)(A1, A2, A3) const volatile)
{
    return mpl::type_list<R,A0 const volatile&,A1,A2,A3>();
}

template <class R, class A0, class A1, class A2, class A3, class A4>
mpl::type_list<R,A0 const volatile&,A1,A2,A3,A4> signature(R (A0::*)(A1, A2, A3, A4) const volatile)
{
    return mpl::type_list<R,A0 const volatile&,A1,A2,A3,A4>();
}

template <class R, class A0, class A1, class A2, class A3, class A4, class A5>
mpl::type_list<R,A0 const volatile&,A1,A2,A3,A4,A5> signature(R (A0::*)(A1, A2, A3, A4, A5) const volatile)
{
    return mpl::type_list<R,A0 const volatile&,A1,A2,A3,A4,A5>();
}

}}} // namespace boost::python::detail

#endif // SIGNATURE_DWA2002128_HPP

