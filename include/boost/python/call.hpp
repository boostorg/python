// Copyright David Abrahams 2001. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
//
//  This work was funded in part by Lawrence Berkeley National Labs
//
//  This file generated for 5-argument member functions and 6-argument free
//  functions by gen_call.py

#ifndef CALL_DWA20011214_HPP
# define CALL_DWA20011214_HPP

# include <boost/python/detail/returning.hpp>

namespace boost { namespace python { 

template <class R>
inline PyObject* call(R (*f)(), PyObject* args, PyObject* keywords)
{
    return detail::returning<R>::call(f, args, keywords);
}

template <class R, class A0>
inline PyObject* call(R (*f)(A0), PyObject* args, PyObject* keywords)
{
    return detail::returning<R>::call(f, args, keywords);
}

template <class R, class A0, class A1>
inline PyObject* call(R (*f)(A0, A1), PyObject* args, PyObject* keywords)
{
    return detail::returning<R>::call(f, args, keywords);
}

template <class R, class A0, class A1, class A2>
inline PyObject* call(R (*f)(A0, A1, A2), PyObject* args, PyObject* keywords)
{
    return detail::returning<R>::call(f, args, keywords);
}

template <class R, class A0, class A1, class A2, class A3>
inline PyObject* call(R (*f)(A0, A1, A2, A3), PyObject* args, PyObject* keywords)
{
    return detail::returning<R>::call(f, args, keywords);
}

template <class R, class A0, class A1, class A2, class A3, class A4>
inline PyObject* call(R (*f)(A0, A1, A2, A3, A4), PyObject* args, PyObject* keywords)
{
    return detail::returning<R>::call(f, args, keywords);
}

template <class R, class A0, class A1, class A2, class A3, class A4, class A5>
inline PyObject* call(R (*f)(A0, A1, A2, A3, A4, A5), PyObject* args, PyObject* keywords)
{
    return detail::returning<R>::call(f, args, keywords);
}

// Member functions
template <class R, class A0>
inline PyObject* call(R (A0::*f)(), PyObject* args, PyObject* keywords)
{
    return detail::returning<R>::call(f, args, keywords);
}

template <class R, class A0, class A1>
inline PyObject* call(R (A0::*f)(A1), PyObject* args, PyObject* keywords)
{
    return detail::returning<R>::call(f, args, keywords);
}

template <class R, class A0, class A1, class A2>
inline PyObject* call(R (A0::*f)(A1, A2), PyObject* args, PyObject* keywords)
{
    return detail::returning<R>::call(f, args, keywords);
}

template <class R, class A0, class A1, class A2, class A3>
inline PyObject* call(R (A0::*f)(A1, A2, A3), PyObject* args, PyObject* keywords)
{
    return detail::returning<R>::call(f, args, keywords);
}

template <class R, class A0, class A1, class A2, class A3, class A4>
inline PyObject* call(R (A0::*f)(A1, A2, A3, A4), PyObject* args, PyObject* keywords)
{
    return detail::returning<R>::call(f, args, keywords);
}

template <class R, class A0, class A1, class A2, class A3, class A4, class A5>
inline PyObject* call(R (A0::*f)(A1, A2, A3, A4, A5), PyObject* args, PyObject* keywords)
{
    return detail::returning<R>::call(f, args, keywords);
}

template <class R, class A0>
inline PyObject* call(R (A0::*f)() const, PyObject* args, PyObject* keywords)
{
    return detail::returning<R>::call(f, args, keywords);
}

template <class R, class A0, class A1>
inline PyObject* call(R (A0::*f)(A1) const, PyObject* args, PyObject* keywords)
{
    return detail::returning<R>::call(f, args, keywords);
}

template <class R, class A0, class A1, class A2>
inline PyObject* call(R (A0::*f)(A1, A2) const, PyObject* args, PyObject* keywords)
{
    return detail::returning<R>::call(f, args, keywords);
}

template <class R, class A0, class A1, class A2, class A3>
inline PyObject* call(R (A0::*f)(A1, A2, A3) const, PyObject* args, PyObject* keywords)
{
    return detail::returning<R>::call(f, args, keywords);
}

template <class R, class A0, class A1, class A2, class A3, class A4>
inline PyObject* call(R (A0::*f)(A1, A2, A3, A4) const, PyObject* args, PyObject* keywords)
{
    return detail::returning<R>::call(f, args, keywords);
}

template <class R, class A0, class A1, class A2, class A3, class A4, class A5>
inline PyObject* call(R (A0::*f)(A1, A2, A3, A4, A5) const, PyObject* args, PyObject* keywords)
{
    return detail::returning<R>::call(f, args, keywords);
}

template <class R, class A0>
inline PyObject* call(R (A0::*f)() volatile, PyObject* args, PyObject* keywords)
{
    return detail::returning<R>::call(f, args, keywords);
}

template <class R, class A0, class A1>
inline PyObject* call(R (A0::*f)(A1) volatile, PyObject* args, PyObject* keywords)
{
    return detail::returning<R>::call(f, args, keywords);
}

template <class R, class A0, class A1, class A2>
inline PyObject* call(R (A0::*f)(A1, A2) volatile, PyObject* args, PyObject* keywords)
{
    return detail::returning<R>::call(f, args, keywords);
}

template <class R, class A0, class A1, class A2, class A3>
inline PyObject* call(R (A0::*f)(A1, A2, A3) volatile, PyObject* args, PyObject* keywords)
{
    return detail::returning<R>::call(f, args, keywords);
}

template <class R, class A0, class A1, class A2, class A3, class A4>
inline PyObject* call(R (A0::*f)(A1, A2, A3, A4) volatile, PyObject* args, PyObject* keywords)
{
    return detail::returning<R>::call(f, args, keywords);
}

template <class R, class A0, class A1, class A2, class A3, class A4, class A5>
inline PyObject* call(R (A0::*f)(A1, A2, A3, A4, A5) volatile, PyObject* args, PyObject* keywords)
{
    return detail::returning<R>::call(f, args, keywords);
}

template <class R, class A0>
inline PyObject* call(R (A0::*f)() const volatile, PyObject* args, PyObject* keywords)
{
    return detail::returning<R>::call(f, args, keywords);
}

template <class R, class A0, class A1>
inline PyObject* call(R (A0::*f)(A1) const volatile, PyObject* args, PyObject* keywords)
{
    return detail::returning<R>::call(f, args, keywords);
}

template <class R, class A0, class A1, class A2>
inline PyObject* call(R (A0::*f)(A1, A2) const volatile, PyObject* args, PyObject* keywords)
{
    return detail::returning<R>::call(f, args, keywords);
}

template <class R, class A0, class A1, class A2, class A3>
inline PyObject* call(R (A0::*f)(A1, A2, A3) const volatile, PyObject* args, PyObject* keywords)
{
    return detail::returning<R>::call(f, args, keywords);
}

template <class R, class A0, class A1, class A2, class A3, class A4>
inline PyObject* call(R (A0::*f)(A1, A2, A3, A4) const volatile, PyObject* args, PyObject* keywords)
{
    return detail::returning<R>::call(f, args, keywords);
}

template <class R, class A0, class A1, class A2, class A3, class A4, class A5>
inline PyObject* call(R (A0::*f)(A1, A2, A3, A4, A5) const volatile, PyObject* args, PyObject* keywords)
{
    return detail::returning<R>::call(f, args, keywords);
}


}} // namespace boost::python

#endif // CALL_DWA20011214_HPP

