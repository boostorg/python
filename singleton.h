//  (C) Copyright David Abrahams 2000. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
//  The author gratefully acknowleges the support of Dragon Systems, Inc., in
//  producing this work.

#ifndef SINGLETON_DWA051900_H_
# define SINGLETON_DWA051900_H_

# include "pyconfig.h"

namespace py { namespace detail {

struct Empty {};
template <class Derived, class Base = Empty>
struct Singleton : Base
{
    typedef Singleton SingletonBase; // Convenience type for derived class constructors
    
    static Derived* singleton();

    // Pass-through constructors
    Singleton() : Base() {}

    template <class A1>
    Singleton(const A1& a1) : Base(a1) {}

    template <class A1, class A2>
    Singleton(const A1& a1, const A2& a2) : Base(a1, a2) {}

    template <class A1, class A2, class A3>
    Singleton(const A1& a1, const A2& a2, const A3& a3) : Base(a1, a2, a3) {}

    template <class A1, class A2, class A3, class A4>
    Singleton(const A1& a1, const A2& a2, const A3& a3, const A4& a4) : Base(a1, a2, a3, a4) {}

    template <class A1, class A2, class A3, class A4, class A5>
    Singleton(const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5) : Base(a1, a2, a3, a4, a5) {}

    template <class A1, class A2, class A3, class A4, class A5, class A6>
    Singleton(const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6) : Base(a1, a2, a3, a4, a5, a6) {}

    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7>
    Singleton(const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7) : Base(a1, a2, a3, a4, a5, a6, a7) {}

    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
    Singleton(const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8) : Base(a1, a2, a3, a4, a5, a6, a7, a8) {}

    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
    Singleton(const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9) : Base(a1, a2, a3, a4, a5, a6, a7, a8, a9) {}

    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10>
    Singleton(const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9, const A10& a10) : Base(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10) {}

};

template <class Derived, class Base>
Derived* Singleton<Derived,Base>::singleton()
{
    static Derived x;
    return &x;
}

}} // namespace py::detail

#endif
