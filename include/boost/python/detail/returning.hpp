//  (C) Copyright David Abrahams 2001. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
//  This work was funded in part by Lawrence Berkeley National Labs
//
//  This file generated for 5-argument member functions and 6-argument free
//  functions by gen_returning.py

#ifndef RETURNING_DWA20011201_HPP
# define RETURNING_DWA20011201_HPP

//# include <boost/python/detail/config.hpp>
# include <boost/python/detail/wrap_python.hpp>
# include <boost/config.hpp>
# include <boost/python/convert.hpp>
# include <boost/python/detail/none.hpp>

namespace boost { namespace python { namespace detail {

// Calling C++ from Python
template <class R>
struct returning
{
    template <class A0>
    static PyObject* call(R (A0::*pmf)(), PyObject* args, PyObject* /* keywords */ )
    {
        // check that each of the arguments is convertible
        unwrap<A0&> c0(PyTuple_GET_ITEM(args, 0));

        // find the result converter
        wrap_more<R> r(c0);
        if (!c0) return 0;
        return r( ((*c0).*pmf)() );
    };
    template <class A0, class A1>
    static PyObject* call(R (A0::*pmf)(A1), PyObject* args, PyObject* /* keywords */ )
    {
        // check that each of the arguments is convertible
        unwrap<A0&> c0(PyTuple_GET_ITEM(args, 0));
        unwrap_more<A1> c1(PyTuple_GET_ITEM(args, 1), c0);

        // find the result converter
        wrap_more<R> r(c1);
        if (!c0) return 0;
        return r( ((*c0).*pmf)(*c1) );
    };
    template <class A0, class A1, class A2>
    static PyObject* call(R (A0::*pmf)(A1, A2), PyObject* args, PyObject* /* keywords */ )
    {
        // check that each of the arguments is convertible
        unwrap<A0&> c0(PyTuple_GET_ITEM(args, 0));
        unwrap_more<A1> c1(PyTuple_GET_ITEM(args, 1), c0);
        unwrap_more<A2> c2(PyTuple_GET_ITEM(args, 2), c1);

        // find the result converter
        wrap_more<R> r(c2);
        if (!c0) return 0;
        return r( ((*c0).*pmf)(*c1, *c2) );
    };
    template <class A0, class A1, class A2, class A3>
    static PyObject* call(R (A0::*pmf)(A1, A2, A3), PyObject* args, PyObject* /* keywords */ )
    {
        // check that each of the arguments is convertible
        unwrap<A0&> c0(PyTuple_GET_ITEM(args, 0));
        unwrap_more<A1> c1(PyTuple_GET_ITEM(args, 1), c0);
        unwrap_more<A2> c2(PyTuple_GET_ITEM(args, 2), c1);
        unwrap_more<A3> c3(PyTuple_GET_ITEM(args, 3), c2);

        // find the result converter
        wrap_more<R> r(c3);
        if (!c0) return 0;
        return r( ((*c0).*pmf)(*c1, *c2, *c3) );
    };
    template <class A0, class A1, class A2, class A3, class A4>
    static PyObject* call(R (A0::*pmf)(A1, A2, A3, A4), PyObject* args, PyObject* /* keywords */ )
    {
        // check that each of the arguments is convertible
        unwrap<A0&> c0(PyTuple_GET_ITEM(args, 0));
        unwrap_more<A1> c1(PyTuple_GET_ITEM(args, 1), c0);
        unwrap_more<A2> c2(PyTuple_GET_ITEM(args, 2), c1);
        unwrap_more<A3> c3(PyTuple_GET_ITEM(args, 3), c2);
        unwrap_more<A4> c4(PyTuple_GET_ITEM(args, 4), c3);

        // find the result converter
        wrap_more<R> r(c4);
        if (!c0) return 0;
        return r( ((*c0).*pmf)(*c1, *c2, *c3, *c4) );
    };
    template <class A0, class A1, class A2, class A3, class A4, class A5>
    static PyObject* call(R (A0::*pmf)(A1, A2, A3, A4, A5), PyObject* args, PyObject* /* keywords */ )
    {
        // check that each of the arguments is convertible
        unwrap<A0&> c0(PyTuple_GET_ITEM(args, 0));
        unwrap_more<A1> c1(PyTuple_GET_ITEM(args, 1), c0);
        unwrap_more<A2> c2(PyTuple_GET_ITEM(args, 2), c1);
        unwrap_more<A3> c3(PyTuple_GET_ITEM(args, 3), c2);
        unwrap_more<A4> c4(PyTuple_GET_ITEM(args, 4), c3);
        unwrap_more<A5> c5(PyTuple_GET_ITEM(args, 5), c4);

        // find the result converter
        wrap_more<R> r(c5);
        if (!c0) return 0;
        return r( ((*c0).*pmf)(*c1, *c2, *c3, *c4, *c5) );
    };

    template <class A0>
    static PyObject* call(R (A0::*pmf)() const, PyObject* args, PyObject* /* keywords */ )
    {
        // check that each of the arguments is convertible
        unwrap<A0 const&> c0(PyTuple_GET_ITEM(args, 0));

        // find the result converter
        wrap_more<R> r(c0);
        if (!c0) return 0;
        return r( ((*c0).*pmf)() );
    };
    template <class A0, class A1>
    static PyObject* call(R (A0::*pmf)(A1) const, PyObject* args, PyObject* /* keywords */ )
    {
        // check that each of the arguments is convertible
        unwrap<A0 const&> c0(PyTuple_GET_ITEM(args, 0));
        unwrap_more<A1> c1(PyTuple_GET_ITEM(args, 1), c0);

        // find the result converter
        wrap_more<R> r(c1);
        if (!c0) return 0;
        return r( ((*c0).*pmf)(*c1) );
    };
    template <class A0, class A1, class A2>
    static PyObject* call(R (A0::*pmf)(A1, A2) const, PyObject* args, PyObject* /* keywords */ )
    {
        // check that each of the arguments is convertible
        unwrap<A0 const&> c0(PyTuple_GET_ITEM(args, 0));
        unwrap_more<A1> c1(PyTuple_GET_ITEM(args, 1), c0);
        unwrap_more<A2> c2(PyTuple_GET_ITEM(args, 2), c1);

        // find the result converter
        wrap_more<R> r(c2);
        if (!c0) return 0;
        return r( ((*c0).*pmf)(*c1, *c2) );
    };
    template <class A0, class A1, class A2, class A3>
    static PyObject* call(R (A0::*pmf)(A1, A2, A3) const, PyObject* args, PyObject* /* keywords */ )
    {
        // check that each of the arguments is convertible
        unwrap<A0 const&> c0(PyTuple_GET_ITEM(args, 0));
        unwrap_more<A1> c1(PyTuple_GET_ITEM(args, 1), c0);
        unwrap_more<A2> c2(PyTuple_GET_ITEM(args, 2), c1);
        unwrap_more<A3> c3(PyTuple_GET_ITEM(args, 3), c2);

        // find the result converter
        wrap_more<R> r(c3);
        if (!c0) return 0;
        return r( ((*c0).*pmf)(*c1, *c2, *c3) );
    };
    template <class A0, class A1, class A2, class A3, class A4>
    static PyObject* call(R (A0::*pmf)(A1, A2, A3, A4) const, PyObject* args, PyObject* /* keywords */ )
    {
        // check that each of the arguments is convertible
        unwrap<A0 const&> c0(PyTuple_GET_ITEM(args, 0));
        unwrap_more<A1> c1(PyTuple_GET_ITEM(args, 1), c0);
        unwrap_more<A2> c2(PyTuple_GET_ITEM(args, 2), c1);
        unwrap_more<A3> c3(PyTuple_GET_ITEM(args, 3), c2);
        unwrap_more<A4> c4(PyTuple_GET_ITEM(args, 4), c3);

        // find the result converter
        wrap_more<R> r(c4);
        if (!c0) return 0;
        return r( ((*c0).*pmf)(*c1, *c2, *c3, *c4) );
    };
    template <class A0, class A1, class A2, class A3, class A4, class A5>
    static PyObject* call(R (A0::*pmf)(A1, A2, A3, A4, A5) const, PyObject* args, PyObject* /* keywords */ )
    {
        // check that each of the arguments is convertible
        unwrap<A0 const&> c0(PyTuple_GET_ITEM(args, 0));
        unwrap_more<A1> c1(PyTuple_GET_ITEM(args, 1), c0);
        unwrap_more<A2> c2(PyTuple_GET_ITEM(args, 2), c1);
        unwrap_more<A3> c3(PyTuple_GET_ITEM(args, 3), c2);
        unwrap_more<A4> c4(PyTuple_GET_ITEM(args, 4), c3);
        unwrap_more<A5> c5(PyTuple_GET_ITEM(args, 5), c4);

        // find the result converter
        wrap_more<R> r(c5);
        if (!c0) return 0;
        return r( ((*c0).*pmf)(*c1, *c2, *c3, *c4, *c5) );
    };

    template <class A0>
    static PyObject* call(R (A0::*pmf)() volatile, PyObject* args, PyObject* /* keywords */ )
    {
        // check that each of the arguments is convertible
        unwrap<A0 volatile&> c0(PyTuple_GET_ITEM(args, 0));

        // find the result converter
        wrap_more<R> r(c0);
        if (!c0) return 0;
        return r( ((*c0).*pmf)() );
    };
    template <class A0, class A1>
    static PyObject* call(R (A0::*pmf)(A1) volatile, PyObject* args, PyObject* /* keywords */ )
    {
        // check that each of the arguments is convertible
        unwrap<A0 volatile&> c0(PyTuple_GET_ITEM(args, 0));
        unwrap_more<A1> c1(PyTuple_GET_ITEM(args, 1), c0);

        // find the result converter
        wrap_more<R> r(c1);
        if (!c0) return 0;
        return r( ((*c0).*pmf)(*c1) );
    };
    template <class A0, class A1, class A2>
    static PyObject* call(R (A0::*pmf)(A1, A2) volatile, PyObject* args, PyObject* /* keywords */ )
    {
        // check that each of the arguments is convertible
        unwrap<A0 volatile&> c0(PyTuple_GET_ITEM(args, 0));
        unwrap_more<A1> c1(PyTuple_GET_ITEM(args, 1), c0);
        unwrap_more<A2> c2(PyTuple_GET_ITEM(args, 2), c1);

        // find the result converter
        wrap_more<R> r(c2);
        if (!c0) return 0;
        return r( ((*c0).*pmf)(*c1, *c2) );
    };
    template <class A0, class A1, class A2, class A3>
    static PyObject* call(R (A0::*pmf)(A1, A2, A3) volatile, PyObject* args, PyObject* /* keywords */ )
    {
        // check that each of the arguments is convertible
        unwrap<A0 volatile&> c0(PyTuple_GET_ITEM(args, 0));
        unwrap_more<A1> c1(PyTuple_GET_ITEM(args, 1), c0);
        unwrap_more<A2> c2(PyTuple_GET_ITEM(args, 2), c1);
        unwrap_more<A3> c3(PyTuple_GET_ITEM(args, 3), c2);

        // find the result converter
        wrap_more<R> r(c3);
        if (!c0) return 0;
        return r( ((*c0).*pmf)(*c1, *c2, *c3) );
    };
    template <class A0, class A1, class A2, class A3, class A4>
    static PyObject* call(R (A0::*pmf)(A1, A2, A3, A4) volatile, PyObject* args, PyObject* /* keywords */ )
    {
        // check that each of the arguments is convertible
        unwrap<A0 volatile&> c0(PyTuple_GET_ITEM(args, 0));
        unwrap_more<A1> c1(PyTuple_GET_ITEM(args, 1), c0);
        unwrap_more<A2> c2(PyTuple_GET_ITEM(args, 2), c1);
        unwrap_more<A3> c3(PyTuple_GET_ITEM(args, 3), c2);
        unwrap_more<A4> c4(PyTuple_GET_ITEM(args, 4), c3);

        // find the result converter
        wrap_more<R> r(c4);
        if (!c0) return 0;
        return r( ((*c0).*pmf)(*c1, *c2, *c3, *c4) );
    };
    template <class A0, class A1, class A2, class A3, class A4, class A5>
    static PyObject* call(R (A0::*pmf)(A1, A2, A3, A4, A5) volatile, PyObject* args, PyObject* /* keywords */ )
    {
        // check that each of the arguments is convertible
        unwrap<A0 volatile&> c0(PyTuple_GET_ITEM(args, 0));
        unwrap_more<A1> c1(PyTuple_GET_ITEM(args, 1), c0);
        unwrap_more<A2> c2(PyTuple_GET_ITEM(args, 2), c1);
        unwrap_more<A3> c3(PyTuple_GET_ITEM(args, 3), c2);
        unwrap_more<A4> c4(PyTuple_GET_ITEM(args, 4), c3);
        unwrap_more<A5> c5(PyTuple_GET_ITEM(args, 5), c4);

        // find the result converter
        wrap_more<R> r(c5);
        if (!c0) return 0;
        return r( ((*c0).*pmf)(*c1, *c2, *c3, *c4, *c5) );
    };


// missing const volatile type traits
#  ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    template <class A0>
    static PyObject* call(R (A0::*pmf)() const volatile, PyObject* args, PyObject* /* keywords */ )
    {
        // check that each of the arguments is convertible
        unwrap<A0 const volatile&> c0(PyTuple_GET_ITEM(args, 0));

        // find the result converter
        wrap_more<R> r(c0);
        if (!c0) return 0;
        return r( ((*c0).*pmf)() );
    };
    template <class A0, class A1>
    static PyObject* call(R (A0::*pmf)(A1) const volatile, PyObject* args, PyObject* /* keywords */ )
    {
        // check that each of the arguments is convertible
        unwrap<A0 const volatile&> c0(PyTuple_GET_ITEM(args, 0));
        unwrap_more<A1> c1(PyTuple_GET_ITEM(args, 1), c0);

        // find the result converter
        wrap_more<R> r(c1);
        if (!c0) return 0;
        return r( ((*c0).*pmf)(*c1) );
    };
    template <class A0, class A1, class A2>
    static PyObject* call(R (A0::*pmf)(A1, A2) const volatile, PyObject* args, PyObject* /* keywords */ )
    {
        // check that each of the arguments is convertible
        unwrap<A0 const volatile&> c0(PyTuple_GET_ITEM(args, 0));
        unwrap_more<A1> c1(PyTuple_GET_ITEM(args, 1), c0);
        unwrap_more<A2> c2(PyTuple_GET_ITEM(args, 2), c1);

        // find the result converter
        wrap_more<R> r(c2);
        if (!c0) return 0;
        return r( ((*c0).*pmf)(*c1, *c2) );
    };
    template <class A0, class A1, class A2, class A3>
    static PyObject* call(R (A0::*pmf)(A1, A2, A3) const volatile, PyObject* args, PyObject* /* keywords */ )
    {
        // check that each of the arguments is convertible
        unwrap<A0 const volatile&> c0(PyTuple_GET_ITEM(args, 0));
        unwrap_more<A1> c1(PyTuple_GET_ITEM(args, 1), c0);
        unwrap_more<A2> c2(PyTuple_GET_ITEM(args, 2), c1);
        unwrap_more<A3> c3(PyTuple_GET_ITEM(args, 3), c2);

        // find the result converter
        wrap_more<R> r(c3);
        if (!c0) return 0;
        return r( ((*c0).*pmf)(*c1, *c2, *c3) );
    };
    template <class A0, class A1, class A2, class A3, class A4>
    static PyObject* call(R (A0::*pmf)(A1, A2, A3, A4) const volatile, PyObject* args, PyObject* /* keywords */ )
    {
        // check that each of the arguments is convertible
        unwrap<A0 const volatile&> c0(PyTuple_GET_ITEM(args, 0));
        unwrap_more<A1> c1(PyTuple_GET_ITEM(args, 1), c0);
        unwrap_more<A2> c2(PyTuple_GET_ITEM(args, 2), c1);
        unwrap_more<A3> c3(PyTuple_GET_ITEM(args, 3), c2);
        unwrap_more<A4> c4(PyTuple_GET_ITEM(args, 4), c3);

        // find the result converter
        wrap_more<R> r(c4);
        if (!c0) return 0;
        return r( ((*c0).*pmf)(*c1, *c2, *c3, *c4) );
    };
    template <class A0, class A1, class A2, class A3, class A4, class A5>
    static PyObject* call(R (A0::*pmf)(A1, A2, A3, A4, A5) const volatile, PyObject* args, PyObject* /* keywords */ )
    {
        // check that each of the arguments is convertible
        unwrap<A0 const volatile&> c0(PyTuple_GET_ITEM(args, 0));
        unwrap_more<A1> c1(PyTuple_GET_ITEM(args, 1), c0);
        unwrap_more<A2> c2(PyTuple_GET_ITEM(args, 2), c1);
        unwrap_more<A3> c3(PyTuple_GET_ITEM(args, 3), c2);
        unwrap_more<A4> c4(PyTuple_GET_ITEM(args, 4), c3);
        unwrap_more<A5> c5(PyTuple_GET_ITEM(args, 5), c4);

        // find the result converter
        wrap_more<R> r(c5);
        if (!c0) return 0;
        return r( ((*c0).*pmf)(*c1, *c2, *c3, *c4, *c5) );
    };

#  endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
            
    static PyObject* call(R (*pf)(), PyObject*, PyObject* /* keywords */ )
    {
        // find the result converter
        wrap<R> r;
        return r( (*pf)() );
    };
    template <class A0>
    static PyObject* call(R (*pf)(A0), PyObject* args, PyObject* /* keywords */ )
    {
        // check that each of the arguments is convertible
        unwrap<A0> c0(PyTuple_GET_ITEM(args, 0));

        // find the result converter
        wrap_more<R> r(c0);
        if (!c0) return 0;
        return r( (*pf)(*c0) );
    };
    template <class A0, class A1>
    static PyObject* call(R (*pf)(A0, A1), PyObject* args, PyObject* /* keywords */ )
    {
        // check that each of the arguments is convertible
        unwrap<A0> c0(PyTuple_GET_ITEM(args, 0));
        unwrap_more<A1> c1(PyTuple_GET_ITEM(args, 1), c0);

        // find the result converter
        wrap_more<R> r(c1);
        if (!c0) return 0;
        return r( (*pf)(*c0, *c1) );
    };
    template <class A0, class A1, class A2>
    static PyObject* call(R (*pf)(A0, A1, A2), PyObject* args, PyObject* /* keywords */ )
    {
        // check that each of the arguments is convertible
        unwrap<A0> c0(PyTuple_GET_ITEM(args, 0));
        unwrap_more<A1> c1(PyTuple_GET_ITEM(args, 1), c0);
        unwrap_more<A2> c2(PyTuple_GET_ITEM(args, 2), c1);

        // find the result converter
        wrap_more<R> r(c2);
        if (!c0) return 0;
        return r( (*pf)(*c0, *c1, *c2) );
    };
    template <class A0, class A1, class A2, class A3>
    static PyObject* call(R (*pf)(A0, A1, A2, A3), PyObject* args, PyObject* /* keywords */ )
    {
        // check that each of the arguments is convertible
        unwrap<A0> c0(PyTuple_GET_ITEM(args, 0));
        unwrap_more<A1> c1(PyTuple_GET_ITEM(args, 1), c0);
        unwrap_more<A2> c2(PyTuple_GET_ITEM(args, 2), c1);
        unwrap_more<A3> c3(PyTuple_GET_ITEM(args, 3), c2);

        // find the result converter
        wrap_more<R> r(c3);
        if (!c0) return 0;
        return r( (*pf)(*c0, *c1, *c2, *c3) );
    };
    template <class A0, class A1, class A2, class A3, class A4>
    static PyObject* call(R (*pf)(A0, A1, A2, A3, A4), PyObject* args, PyObject* /* keywords */ )
    {
        // check that each of the arguments is convertible
        unwrap<A0> c0(PyTuple_GET_ITEM(args, 0));
        unwrap_more<A1> c1(PyTuple_GET_ITEM(args, 1), c0);
        unwrap_more<A2> c2(PyTuple_GET_ITEM(args, 2), c1);
        unwrap_more<A3> c3(PyTuple_GET_ITEM(args, 3), c2);
        unwrap_more<A4> c4(PyTuple_GET_ITEM(args, 4), c3);

        // find the result converter
        wrap_more<R> r(c4);
        if (!c0) return 0;
        return r( (*pf)(*c0, *c1, *c2, *c3, *c4) );
    };
    template <class A0, class A1, class A2, class A3, class A4, class A5>
    static PyObject* call(R (*pf)(A0, A1, A2, A3, A4, A5), PyObject* args, PyObject* /* keywords */ )
    {
        // check that each of the arguments is convertible
        unwrap<A0> c0(PyTuple_GET_ITEM(args, 0));
        unwrap_more<A1> c1(PyTuple_GET_ITEM(args, 1), c0);
        unwrap_more<A2> c2(PyTuple_GET_ITEM(args, 2), c1);
        unwrap_more<A3> c3(PyTuple_GET_ITEM(args, 3), c2);
        unwrap_more<A4> c4(PyTuple_GET_ITEM(args, 4), c3);
        unwrap_more<A5> c5(PyTuple_GET_ITEM(args, 5), c4);

        // find the result converter
        wrap_more<R> r(c5);
        if (!c0) return 0;
        return r( (*pf)(*c0, *c1, *c2, *c3, *c4, *c5) );
    };
};
                           
template <>
struct returning<void>
{
    typedef void R;
    template <class A0>
    static PyObject* call(R (A0::*pmf)(), PyObject* args, PyObject* /* keywords */ )
    {
        // check that each of the arguments is convertible
        unwrap<A0&> c0(PyTuple_GET_ITEM(args, 0));

        if (!c0) return 0;
        ((*c0).*pmf)();
        return detail::none();
    };
    template <class A0, class A1>
    static PyObject* call(R (A0::*pmf)(A1), PyObject* args, PyObject* /* keywords */ )
    {
        // check that each of the arguments is convertible
        unwrap<A0&> c0(PyTuple_GET_ITEM(args, 0));
        unwrap_more<A1> c1(PyTuple_GET_ITEM(args, 1), c0);

        if (!c0) return 0;
        ((*c0).*pmf)(*c1);
        return detail::none();
    };
    template <class A0, class A1, class A2>
    static PyObject* call(R (A0::*pmf)(A1, A2), PyObject* args, PyObject* /* keywords */ )
    {
        // check that each of the arguments is convertible
        unwrap<A0&> c0(PyTuple_GET_ITEM(args, 0));
        unwrap_more<A1> c1(PyTuple_GET_ITEM(args, 1), c0);
        unwrap_more<A2> c2(PyTuple_GET_ITEM(args, 2), c1);

        if (!c0) return 0;
        ((*c0).*pmf)(*c1, *c2);
        return detail::none();
    };
    template <class A0, class A1, class A2, class A3>
    static PyObject* call(R (A0::*pmf)(A1, A2, A3), PyObject* args, PyObject* /* keywords */ )
    {
        // check that each of the arguments is convertible
        unwrap<A0&> c0(PyTuple_GET_ITEM(args, 0));
        unwrap_more<A1> c1(PyTuple_GET_ITEM(args, 1), c0);
        unwrap_more<A2> c2(PyTuple_GET_ITEM(args, 2), c1);
        unwrap_more<A3> c3(PyTuple_GET_ITEM(args, 3), c2);

        if (!c0) return 0;
        ((*c0).*pmf)(*c1, *c2, *c3);
        return detail::none();
    };
    template <class A0, class A1, class A2, class A3, class A4>
    static PyObject* call(R (A0::*pmf)(A1, A2, A3, A4), PyObject* args, PyObject* /* keywords */ )
    {
        // check that each of the arguments is convertible
        unwrap<A0&> c0(PyTuple_GET_ITEM(args, 0));
        unwrap_more<A1> c1(PyTuple_GET_ITEM(args, 1), c0);
        unwrap_more<A2> c2(PyTuple_GET_ITEM(args, 2), c1);
        unwrap_more<A3> c3(PyTuple_GET_ITEM(args, 3), c2);
        unwrap_more<A4> c4(PyTuple_GET_ITEM(args, 4), c3);

        if (!c0) return 0;
        ((*c0).*pmf)(*c1, *c2, *c3, *c4);
        return detail::none();
    };
    template <class A0, class A1, class A2, class A3, class A4, class A5>
    static PyObject* call(R (A0::*pmf)(A1, A2, A3, A4, A5), PyObject* args, PyObject* /* keywords */ )
    {
        // check that each of the arguments is convertible
        unwrap<A0&> c0(PyTuple_GET_ITEM(args, 0));
        unwrap_more<A1> c1(PyTuple_GET_ITEM(args, 1), c0);
        unwrap_more<A2> c2(PyTuple_GET_ITEM(args, 2), c1);
        unwrap_more<A3> c3(PyTuple_GET_ITEM(args, 3), c2);
        unwrap_more<A4> c4(PyTuple_GET_ITEM(args, 4), c3);
        unwrap_more<A5> c5(PyTuple_GET_ITEM(args, 5), c4);

        if (!c0) return 0;
        ((*c0).*pmf)(*c1, *c2, *c3, *c4, *c5);
        return detail::none();
    };

    template <class A0>
    static PyObject* call(R (A0::*pmf)() const, PyObject* args, PyObject* /* keywords */ )
    {
        // check that each of the arguments is convertible
        unwrap<A0 const&> c0(PyTuple_GET_ITEM(args, 0));

        if (!c0) return 0;
        ((*c0).*pmf)();
        return detail::none();
    };
    template <class A0, class A1>
    static PyObject* call(R (A0::*pmf)(A1) const, PyObject* args, PyObject* /* keywords */ )
    {
        // check that each of the arguments is convertible
        unwrap<A0 const&> c0(PyTuple_GET_ITEM(args, 0));
        unwrap_more<A1> c1(PyTuple_GET_ITEM(args, 1), c0);

        if (!c0) return 0;
        ((*c0).*pmf)(*c1);
        return detail::none();
    };
    template <class A0, class A1, class A2>
    static PyObject* call(R (A0::*pmf)(A1, A2) const, PyObject* args, PyObject* /* keywords */ )
    {
        // check that each of the arguments is convertible
        unwrap<A0 const&> c0(PyTuple_GET_ITEM(args, 0));
        unwrap_more<A1> c1(PyTuple_GET_ITEM(args, 1), c0);
        unwrap_more<A2> c2(PyTuple_GET_ITEM(args, 2), c1);

        if (!c0) return 0;
        ((*c0).*pmf)(*c1, *c2);
        return detail::none();
    };
    template <class A0, class A1, class A2, class A3>
    static PyObject* call(R (A0::*pmf)(A1, A2, A3) const, PyObject* args, PyObject* /* keywords */ )
    {
        // check that each of the arguments is convertible
        unwrap<A0 const&> c0(PyTuple_GET_ITEM(args, 0));
        unwrap_more<A1> c1(PyTuple_GET_ITEM(args, 1), c0);
        unwrap_more<A2> c2(PyTuple_GET_ITEM(args, 2), c1);
        unwrap_more<A3> c3(PyTuple_GET_ITEM(args, 3), c2);

        if (!c0) return 0;
        ((*c0).*pmf)(*c1, *c2, *c3);
        return detail::none();
    };
    template <class A0, class A1, class A2, class A3, class A4>
    static PyObject* call(R (A0::*pmf)(A1, A2, A3, A4) const, PyObject* args, PyObject* /* keywords */ )
    {
        // check that each of the arguments is convertible
        unwrap<A0 const&> c0(PyTuple_GET_ITEM(args, 0));
        unwrap_more<A1> c1(PyTuple_GET_ITEM(args, 1), c0);
        unwrap_more<A2> c2(PyTuple_GET_ITEM(args, 2), c1);
        unwrap_more<A3> c3(PyTuple_GET_ITEM(args, 3), c2);
        unwrap_more<A4> c4(PyTuple_GET_ITEM(args, 4), c3);

        if (!c0) return 0;
        ((*c0).*pmf)(*c1, *c2, *c3, *c4);
        return detail::none();
    };
    template <class A0, class A1, class A2, class A3, class A4, class A5>
    static PyObject* call(R (A0::*pmf)(A1, A2, A3, A4, A5) const, PyObject* args, PyObject* /* keywords */ )
    {
        // check that each of the arguments is convertible
        unwrap<A0 const&> c0(PyTuple_GET_ITEM(args, 0));
        unwrap_more<A1> c1(PyTuple_GET_ITEM(args, 1), c0);
        unwrap_more<A2> c2(PyTuple_GET_ITEM(args, 2), c1);
        unwrap_more<A3> c3(PyTuple_GET_ITEM(args, 3), c2);
        unwrap_more<A4> c4(PyTuple_GET_ITEM(args, 4), c3);
        unwrap_more<A5> c5(PyTuple_GET_ITEM(args, 5), c4);

        if (!c0) return 0;
        ((*c0).*pmf)(*c1, *c2, *c3, *c4, *c5);
        return detail::none();
    };

    template <class A0>
    static PyObject* call(R (A0::*pmf)() volatile, PyObject* args, PyObject* /* keywords */ )
    {
        // check that each of the arguments is convertible
        unwrap<A0 volatile&> c0(PyTuple_GET_ITEM(args, 0));

        if (!c0) return 0;
        ((*c0).*pmf)();
        return detail::none();
    };
    template <class A0, class A1>
    static PyObject* call(R (A0::*pmf)(A1) volatile, PyObject* args, PyObject* /* keywords */ )
    {
        // check that each of the arguments is convertible
        unwrap<A0 volatile&> c0(PyTuple_GET_ITEM(args, 0));
        unwrap_more<A1> c1(PyTuple_GET_ITEM(args, 1), c0);

        if (!c0) return 0;
        ((*c0).*pmf)(*c1);
        return detail::none();
    };
    template <class A0, class A1, class A2>
    static PyObject* call(R (A0::*pmf)(A1, A2) volatile, PyObject* args, PyObject* /* keywords */ )
    {
        // check that each of the arguments is convertible
        unwrap<A0 volatile&> c0(PyTuple_GET_ITEM(args, 0));
        unwrap_more<A1> c1(PyTuple_GET_ITEM(args, 1), c0);
        unwrap_more<A2> c2(PyTuple_GET_ITEM(args, 2), c1);

        if (!c0) return 0;
        ((*c0).*pmf)(*c1, *c2);
        return detail::none();
    };
    template <class A0, class A1, class A2, class A3>
    static PyObject* call(R (A0::*pmf)(A1, A2, A3) volatile, PyObject* args, PyObject* /* keywords */ )
    {
        // check that each of the arguments is convertible
        unwrap<A0 volatile&> c0(PyTuple_GET_ITEM(args, 0));
        unwrap_more<A1> c1(PyTuple_GET_ITEM(args, 1), c0);
        unwrap_more<A2> c2(PyTuple_GET_ITEM(args, 2), c1);
        unwrap_more<A3> c3(PyTuple_GET_ITEM(args, 3), c2);

        if (!c0) return 0;
        ((*c0).*pmf)(*c1, *c2, *c3);
        return detail::none();
    };
    template <class A0, class A1, class A2, class A3, class A4>
    static PyObject* call(R (A0::*pmf)(A1, A2, A3, A4) volatile, PyObject* args, PyObject* /* keywords */ )
    {
        // check that each of the arguments is convertible
        unwrap<A0 volatile&> c0(PyTuple_GET_ITEM(args, 0));
        unwrap_more<A1> c1(PyTuple_GET_ITEM(args, 1), c0);
        unwrap_more<A2> c2(PyTuple_GET_ITEM(args, 2), c1);
        unwrap_more<A3> c3(PyTuple_GET_ITEM(args, 3), c2);
        unwrap_more<A4> c4(PyTuple_GET_ITEM(args, 4), c3);

        if (!c0) return 0;
        ((*c0).*pmf)(*c1, *c2, *c3, *c4);
        return detail::none();
    };
    template <class A0, class A1, class A2, class A3, class A4, class A5>
    static PyObject* call(R (A0::*pmf)(A1, A2, A3, A4, A5) volatile, PyObject* args, PyObject* /* keywords */ )
    {
        // check that each of the arguments is convertible
        unwrap<A0 volatile&> c0(PyTuple_GET_ITEM(args, 0));
        unwrap_more<A1> c1(PyTuple_GET_ITEM(args, 1), c0);
        unwrap_more<A2> c2(PyTuple_GET_ITEM(args, 2), c1);
        unwrap_more<A3> c3(PyTuple_GET_ITEM(args, 3), c2);
        unwrap_more<A4> c4(PyTuple_GET_ITEM(args, 4), c3);
        unwrap_more<A5> c5(PyTuple_GET_ITEM(args, 5), c4);

        if (!c0) return 0;
        ((*c0).*pmf)(*c1, *c2, *c3, *c4, *c5);
        return detail::none();
    };


// missing const volatile type traits
#  ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    template <class A0>
    static PyObject* call(R (A0::*pmf)() const volatile, PyObject* args, PyObject* /* keywords */ )
    {
        // check that each of the arguments is convertible
        unwrap<A0 const volatile&> c0(PyTuple_GET_ITEM(args, 0));

        if (!c0) return 0;
        ((*c0).*pmf)();
        return detail::none();
    };
    template <class A0, class A1>
    static PyObject* call(R (A0::*pmf)(A1) const volatile, PyObject* args, PyObject* /* keywords */ )
    {
        // check that each of the arguments is convertible
        unwrap<A0 const volatile&> c0(PyTuple_GET_ITEM(args, 0));
        unwrap_more<A1> c1(PyTuple_GET_ITEM(args, 1), c0);

        if (!c0) return 0;
        ((*c0).*pmf)(*c1);
        return detail::none();
    };
    template <class A0, class A1, class A2>
    static PyObject* call(R (A0::*pmf)(A1, A2) const volatile, PyObject* args, PyObject* /* keywords */ )
    {
        // check that each of the arguments is convertible
        unwrap<A0 const volatile&> c0(PyTuple_GET_ITEM(args, 0));
        unwrap_more<A1> c1(PyTuple_GET_ITEM(args, 1), c0);
        unwrap_more<A2> c2(PyTuple_GET_ITEM(args, 2), c1);

        if (!c0) return 0;
        ((*c0).*pmf)(*c1, *c2);
        return detail::none();
    };
    template <class A0, class A1, class A2, class A3>
    static PyObject* call(R (A0::*pmf)(A1, A2, A3) const volatile, PyObject* args, PyObject* /* keywords */ )
    {
        // check that each of the arguments is convertible
        unwrap<A0 const volatile&> c0(PyTuple_GET_ITEM(args, 0));
        unwrap_more<A1> c1(PyTuple_GET_ITEM(args, 1), c0);
        unwrap_more<A2> c2(PyTuple_GET_ITEM(args, 2), c1);
        unwrap_more<A3> c3(PyTuple_GET_ITEM(args, 3), c2);

        if (!c0) return 0;
        ((*c0).*pmf)(*c1, *c2, *c3);
        return detail::none();
    };
    template <class A0, class A1, class A2, class A3, class A4>
    static PyObject* call(R (A0::*pmf)(A1, A2, A3, A4) const volatile, PyObject* args, PyObject* /* keywords */ )
    {
        // check that each of the arguments is convertible
        unwrap<A0 const volatile&> c0(PyTuple_GET_ITEM(args, 0));
        unwrap_more<A1> c1(PyTuple_GET_ITEM(args, 1), c0);
        unwrap_more<A2> c2(PyTuple_GET_ITEM(args, 2), c1);
        unwrap_more<A3> c3(PyTuple_GET_ITEM(args, 3), c2);
        unwrap_more<A4> c4(PyTuple_GET_ITEM(args, 4), c3);

        if (!c0) return 0;
        ((*c0).*pmf)(*c1, *c2, *c3, *c4);
        return detail::none();
    };
    template <class A0, class A1, class A2, class A3, class A4, class A5>
    static PyObject* call(R (A0::*pmf)(A1, A2, A3, A4, A5) const volatile, PyObject* args, PyObject* /* keywords */ )
    {
        // check that each of the arguments is convertible
        unwrap<A0 const volatile&> c0(PyTuple_GET_ITEM(args, 0));
        unwrap_more<A1> c1(PyTuple_GET_ITEM(args, 1), c0);
        unwrap_more<A2> c2(PyTuple_GET_ITEM(args, 2), c1);
        unwrap_more<A3> c3(PyTuple_GET_ITEM(args, 3), c2);
        unwrap_more<A4> c4(PyTuple_GET_ITEM(args, 4), c3);
        unwrap_more<A5> c5(PyTuple_GET_ITEM(args, 5), c4);

        if (!c0) return 0;
        ((*c0).*pmf)(*c1, *c2, *c3, *c4, *c5);
        return detail::none();
    };

#  endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
            
    static PyObject* call(R (*pf)(), PyObject*, PyObject* /* keywords */ )
    {
        (*pf)();
        return detail::none();
    };
    template <class A0>
    static PyObject* call(R (*pf)(A0), PyObject* args, PyObject* /* keywords */ )
    {
        // check that each of the arguments is convertible
        unwrap<A0> c0(PyTuple_GET_ITEM(args, 0));

        if (!c0) return 0;
        (*pf)(*c0);
        return detail::none();
    };
    template <class A0, class A1>
    static PyObject* call(R (*pf)(A0, A1), PyObject* args, PyObject* /* keywords */ )
    {
        // check that each of the arguments is convertible
        unwrap<A0> c0(PyTuple_GET_ITEM(args, 0));
        unwrap_more<A1> c1(PyTuple_GET_ITEM(args, 1), c0);

        if (!c0) return 0;
        (*pf)(*c0, *c1);
        return detail::none();
    };
    template <class A0, class A1, class A2>
    static PyObject* call(R (*pf)(A0, A1, A2), PyObject* args, PyObject* /* keywords */ )
    {
        // check that each of the arguments is convertible
        unwrap<A0> c0(PyTuple_GET_ITEM(args, 0));
        unwrap_more<A1> c1(PyTuple_GET_ITEM(args, 1), c0);
        unwrap_more<A2> c2(PyTuple_GET_ITEM(args, 2), c1);

        if (!c0) return 0;
        (*pf)(*c0, *c1, *c2);
        return detail::none();
    };
    template <class A0, class A1, class A2, class A3>
    static PyObject* call(R (*pf)(A0, A1, A2, A3), PyObject* args, PyObject* /* keywords */ )
    {
        // check that each of the arguments is convertible
        unwrap<A0> c0(PyTuple_GET_ITEM(args, 0));
        unwrap_more<A1> c1(PyTuple_GET_ITEM(args, 1), c0);
        unwrap_more<A2> c2(PyTuple_GET_ITEM(args, 2), c1);
        unwrap_more<A3> c3(PyTuple_GET_ITEM(args, 3), c2);

        if (!c0) return 0;
        (*pf)(*c0, *c1, *c2, *c3);
        return detail::none();
    };
    template <class A0, class A1, class A2, class A3, class A4>
    static PyObject* call(R (*pf)(A0, A1, A2, A3, A4), PyObject* args, PyObject* /* keywords */ )
    {
        // check that each of the arguments is convertible
        unwrap<A0> c0(PyTuple_GET_ITEM(args, 0));
        unwrap_more<A1> c1(PyTuple_GET_ITEM(args, 1), c0);
        unwrap_more<A2> c2(PyTuple_GET_ITEM(args, 2), c1);
        unwrap_more<A3> c3(PyTuple_GET_ITEM(args, 3), c2);
        unwrap_more<A4> c4(PyTuple_GET_ITEM(args, 4), c3);

        if (!c0) return 0;
        (*pf)(*c0, *c1, *c2, *c3, *c4);
        return detail::none();
    };
    template <class A0, class A1, class A2, class A3, class A4, class A5>
    static PyObject* call(R (*pf)(A0, A1, A2, A3, A4, A5), PyObject* args, PyObject* /* keywords */ )
    {
        // check that each of the arguments is convertible
        unwrap<A0> c0(PyTuple_GET_ITEM(args, 0));
        unwrap_more<A1> c1(PyTuple_GET_ITEM(args, 1), c0);
        unwrap_more<A2> c2(PyTuple_GET_ITEM(args, 2), c1);
        unwrap_more<A3> c3(PyTuple_GET_ITEM(args, 3), c2);
        unwrap_more<A4> c4(PyTuple_GET_ITEM(args, 4), c3);
        unwrap_more<A5> c5(PyTuple_GET_ITEM(args, 5), c4);

        if (!c0) return 0;
        (*pf)(*c0, *c1, *c2, *c3, *c4, *c5);
        return detail::none();
    };
};

}}} // namespace boost::python::detail

#endif // RETURNING_DWA20011201_HPP

