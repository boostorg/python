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
# include <boost/python/detail/none.hpp>
# include <boost/python/from_python.hpp>
# include <boost/python/to_python.hpp>

namespace boost { namespace python
{
  template <class T> struct to_python;
}} // namespace boost::python

namespace boost { namespace python { namespace detail {

// Calling C++ from Python
template <class R>
struct returning
{
    template <class P, class A0>
    static PyObject* call(R (A0::*pmf)(), PyObject* args, PyObject*, P const& policies)
    {
        // check that each of the arguments is convertible
        from_python<A0&> c0(PyTuple_GET_ITEM(args, 0));
        if (!c0.convertible()) return 0;

        // find the result converter
        typedef typename P::result_converter result_converter;
        typename eval<result_converter,R>::type cr;
        if (!cr.convertible()) return 0;
        
        if (!policies.precall(args)) return 0;
        
        PyObject* result = cr( ((c0(PyTuple_GET_ITEM(args, 0))).*pmf)() );
        
        if (!result) return 0;
        return policies.postcall(args, result);
    }
    template <class P, class A0, class A1>
    static PyObject* call(R (A0::*pmf)(A1), PyObject* args, PyObject*, P const& policies)
    {
        // check that each of the arguments is convertible
        from_python<A0&> c0(PyTuple_GET_ITEM(args, 0));
        if (!c0.convertible()) return 0;
        from_python<A1> c1(PyTuple_GET_ITEM(args, 1));
        if (!c1.convertible()) return 0;

        // find the result converter
        typedef typename P::result_converter result_converter;
        typename eval<result_converter,R>::type cr;
        if (!cr.convertible()) return 0;
        
        if (!policies.precall(args)) return 0;
        
        PyObject* result = cr( ((c0(PyTuple_GET_ITEM(args, 0))).*pmf)(c1(PyTuple_GET_ITEM(args, 1))) );
        
        if (!result) return 0;
        return policies.postcall(args, result);
    }
    template <class P, class A0, class A1, class A2>
    static PyObject* call(R (A0::*pmf)(A1, A2), PyObject* args, PyObject*, P const& policies)
    {
        // check that each of the arguments is convertible
        from_python<A0&> c0(PyTuple_GET_ITEM(args, 0));
        if (!c0.convertible()) return 0;
        from_python<A1> c1(PyTuple_GET_ITEM(args, 1));
        if (!c1.convertible()) return 0;
        from_python<A2> c2(PyTuple_GET_ITEM(args, 2));
        if (!c2.convertible()) return 0;

        // find the result converter
        typedef typename P::result_converter result_converter;
        typename eval<result_converter,R>::type cr;
        if (!cr.convertible()) return 0;
        
        if (!policies.precall(args)) return 0;
        
        PyObject* result = cr( ((c0(PyTuple_GET_ITEM(args, 0))).*pmf)(c1(PyTuple_GET_ITEM(args, 1)), c2(PyTuple_GET_ITEM(args, 2))) );
        
        if (!result) return 0;
        return policies.postcall(args, result);
    }
    template <class P, class A0, class A1, class A2, class A3>
    static PyObject* call(R (A0::*pmf)(A1, A2, A3), PyObject* args, PyObject*, P const& policies)
    {
        // check that each of the arguments is convertible
        from_python<A0&> c0(PyTuple_GET_ITEM(args, 0));
        if (!c0.convertible()) return 0;
        from_python<A1> c1(PyTuple_GET_ITEM(args, 1));
        if (!c1.convertible()) return 0;
        from_python<A2> c2(PyTuple_GET_ITEM(args, 2));
        if (!c2.convertible()) return 0;
        from_python<A3> c3(PyTuple_GET_ITEM(args, 3));
        if (!c3.convertible()) return 0;

        // find the result converter
        typedef typename P::result_converter result_converter;
        typename eval<result_converter,R>::type cr;
        if (!cr.convertible()) return 0;
        
        if (!policies.precall(args)) return 0;
        
        PyObject* result = cr( ((c0(PyTuple_GET_ITEM(args, 0))).*pmf)(c1(PyTuple_GET_ITEM(args, 1)), c2(PyTuple_GET_ITEM(args, 2)), c3(PyTuple_GET_ITEM(args, 3))) );
        
        if (!result) return 0;
        return policies.postcall(args, result);
    }
    template <class P, class A0, class A1, class A2, class A3, class A4>
    static PyObject* call(R (A0::*pmf)(A1, A2, A3, A4), PyObject* args, PyObject*, P const& policies)
    {
        // check that each of the arguments is convertible
        from_python<A0&> c0(PyTuple_GET_ITEM(args, 0));
        if (!c0.convertible()) return 0;
        from_python<A1> c1(PyTuple_GET_ITEM(args, 1));
        if (!c1.convertible()) return 0;
        from_python<A2> c2(PyTuple_GET_ITEM(args, 2));
        if (!c2.convertible()) return 0;
        from_python<A3> c3(PyTuple_GET_ITEM(args, 3));
        if (!c3.convertible()) return 0;
        from_python<A4> c4(PyTuple_GET_ITEM(args, 4));
        if (!c4.convertible()) return 0;

        // find the result converter
        typedef typename P::result_converter result_converter;
        typename eval<result_converter,R>::type cr;
        if (!cr.convertible()) return 0;
        
        if (!policies.precall(args)) return 0;
        
        PyObject* result = cr( ((c0(PyTuple_GET_ITEM(args, 0))).*pmf)(c1(PyTuple_GET_ITEM(args, 1)), c2(PyTuple_GET_ITEM(args, 2)), c3(PyTuple_GET_ITEM(args, 3)), c4(PyTuple_GET_ITEM(args, 4))) );
        
        if (!result) return 0;
        return policies.postcall(args, result);
    }
    template <class P, class A0, class A1, class A2, class A3, class A4, class A5>
    static PyObject* call(R (A0::*pmf)(A1, A2, A3, A4, A5), PyObject* args, PyObject*, P const& policies)
    {
        // check that each of the arguments is convertible
        from_python<A0&> c0(PyTuple_GET_ITEM(args, 0));
        if (!c0.convertible()) return 0;
        from_python<A1> c1(PyTuple_GET_ITEM(args, 1));
        if (!c1.convertible()) return 0;
        from_python<A2> c2(PyTuple_GET_ITEM(args, 2));
        if (!c2.convertible()) return 0;
        from_python<A3> c3(PyTuple_GET_ITEM(args, 3));
        if (!c3.convertible()) return 0;
        from_python<A4> c4(PyTuple_GET_ITEM(args, 4));
        if (!c4.convertible()) return 0;
        from_python<A5> c5(PyTuple_GET_ITEM(args, 5));
        if (!c5.convertible()) return 0;

        // find the result converter
        typedef typename P::result_converter result_converter;
        typename eval<result_converter,R>::type cr;
        if (!cr.convertible()) return 0;
        
        if (!policies.precall(args)) return 0;
        
        PyObject* result = cr( ((c0(PyTuple_GET_ITEM(args, 0))).*pmf)(c1(PyTuple_GET_ITEM(args, 1)), c2(PyTuple_GET_ITEM(args, 2)), c3(PyTuple_GET_ITEM(args, 3)), c4(PyTuple_GET_ITEM(args, 4)), c5(PyTuple_GET_ITEM(args, 5))) );
        
        if (!result) return 0;
        return policies.postcall(args, result);
    }

    template <class P, class A0>
    static PyObject* call(R (A0::*pmf)() const, PyObject* args, PyObject*, P const& policies)
    {
        // check that each of the arguments is convertible
        from_python<A0 const&> c0(PyTuple_GET_ITEM(args, 0));
        if (!c0.convertible()) return 0;

        // find the result converter
        typedef typename P::result_converter result_converter;
        typename eval<result_converter,R>::type cr;
        if (!cr.convertible()) return 0;
        
        if (!policies.precall(args)) return 0;
        
        PyObject* result = cr( ((c0(PyTuple_GET_ITEM(args, 0))).*pmf)() );
        
        if (!result) return 0;
        return policies.postcall(args, result);
    }
    template <class P, class A0, class A1>
    static PyObject* call(R (A0::*pmf)(A1) const, PyObject* args, PyObject*, P const& policies)
    {
        // check that each of the arguments is convertible
        from_python<A0 const&> c0(PyTuple_GET_ITEM(args, 0));
        if (!c0.convertible()) return 0;
        from_python<A1> c1(PyTuple_GET_ITEM(args, 1));
        if (!c1.convertible()) return 0;

        // find the result converter
        typedef typename P::result_converter result_converter;
        typename eval<result_converter,R>::type cr;
        if (!cr.convertible()) return 0;
        
        if (!policies.precall(args)) return 0;
        
        PyObject* result = cr( ((c0(PyTuple_GET_ITEM(args, 0))).*pmf)(c1(PyTuple_GET_ITEM(args, 1))) );
        
        if (!result) return 0;
        return policies.postcall(args, result);
    }
    template <class P, class A0, class A1, class A2>
    static PyObject* call(R (A0::*pmf)(A1, A2) const, PyObject* args, PyObject*, P const& policies)
    {
        // check that each of the arguments is convertible
        from_python<A0 const&> c0(PyTuple_GET_ITEM(args, 0));
        if (!c0.convertible()) return 0;
        from_python<A1> c1(PyTuple_GET_ITEM(args, 1));
        if (!c1.convertible()) return 0;
        from_python<A2> c2(PyTuple_GET_ITEM(args, 2));
        if (!c2.convertible()) return 0;

        // find the result converter
        typedef typename P::result_converter result_converter;
        typename eval<result_converter,R>::type cr;
        if (!cr.convertible()) return 0;
        
        if (!policies.precall(args)) return 0;
        
        PyObject* result = cr( ((c0(PyTuple_GET_ITEM(args, 0))).*pmf)(c1(PyTuple_GET_ITEM(args, 1)), c2(PyTuple_GET_ITEM(args, 2))) );
        
        if (!result) return 0;
        return policies.postcall(args, result);
    }
    template <class P, class A0, class A1, class A2, class A3>
    static PyObject* call(R (A0::*pmf)(A1, A2, A3) const, PyObject* args, PyObject*, P const& policies)
    {
        // check that each of the arguments is convertible
        from_python<A0 const&> c0(PyTuple_GET_ITEM(args, 0));
        if (!c0.convertible()) return 0;
        from_python<A1> c1(PyTuple_GET_ITEM(args, 1));
        if (!c1.convertible()) return 0;
        from_python<A2> c2(PyTuple_GET_ITEM(args, 2));
        if (!c2.convertible()) return 0;
        from_python<A3> c3(PyTuple_GET_ITEM(args, 3));
        if (!c3.convertible()) return 0;

        // find the result converter
        typedef typename P::result_converter result_converter;
        typename eval<result_converter,R>::type cr;
        if (!cr.convertible()) return 0;
        
        if (!policies.precall(args)) return 0;
        
        PyObject* result = cr( ((c0(PyTuple_GET_ITEM(args, 0))).*pmf)(c1(PyTuple_GET_ITEM(args, 1)), c2(PyTuple_GET_ITEM(args, 2)), c3(PyTuple_GET_ITEM(args, 3))) );
        
        if (!result) return 0;
        return policies.postcall(args, result);
    }
    template <class P, class A0, class A1, class A2, class A3, class A4>
    static PyObject* call(R (A0::*pmf)(A1, A2, A3, A4) const, PyObject* args, PyObject*, P const& policies)
    {
        // check that each of the arguments is convertible
        from_python<A0 const&> c0(PyTuple_GET_ITEM(args, 0));
        if (!c0.convertible()) return 0;
        from_python<A1> c1(PyTuple_GET_ITEM(args, 1));
        if (!c1.convertible()) return 0;
        from_python<A2> c2(PyTuple_GET_ITEM(args, 2));
        if (!c2.convertible()) return 0;
        from_python<A3> c3(PyTuple_GET_ITEM(args, 3));
        if (!c3.convertible()) return 0;
        from_python<A4> c4(PyTuple_GET_ITEM(args, 4));
        if (!c4.convertible()) return 0;

        // find the result converter
        typedef typename P::result_converter result_converter;
        typename eval<result_converter,R>::type cr;
        if (!cr.convertible()) return 0;
        
        if (!policies.precall(args)) return 0;
        
        PyObject* result = cr( ((c0(PyTuple_GET_ITEM(args, 0))).*pmf)(c1(PyTuple_GET_ITEM(args, 1)), c2(PyTuple_GET_ITEM(args, 2)), c3(PyTuple_GET_ITEM(args, 3)), c4(PyTuple_GET_ITEM(args, 4))) );
        
        if (!result) return 0;
        return policies.postcall(args, result);
    }
    template <class P, class A0, class A1, class A2, class A3, class A4, class A5>
    static PyObject* call(R (A0::*pmf)(A1, A2, A3, A4, A5) const, PyObject* args, PyObject*, P const& policies)
    {
        // check that each of the arguments is convertible
        from_python<A0 const&> c0(PyTuple_GET_ITEM(args, 0));
        if (!c0.convertible()) return 0;
        from_python<A1> c1(PyTuple_GET_ITEM(args, 1));
        if (!c1.convertible()) return 0;
        from_python<A2> c2(PyTuple_GET_ITEM(args, 2));
        if (!c2.convertible()) return 0;
        from_python<A3> c3(PyTuple_GET_ITEM(args, 3));
        if (!c3.convertible()) return 0;
        from_python<A4> c4(PyTuple_GET_ITEM(args, 4));
        if (!c4.convertible()) return 0;
        from_python<A5> c5(PyTuple_GET_ITEM(args, 5));
        if (!c5.convertible()) return 0;

        // find the result converter
        typedef typename P::result_converter result_converter;
        typename eval<result_converter,R>::type cr;
        if (!cr.convertible()) return 0;
        
        if (!policies.precall(args)) return 0;
        
        PyObject* result = cr( ((c0(PyTuple_GET_ITEM(args, 0))).*pmf)(c1(PyTuple_GET_ITEM(args, 1)), c2(PyTuple_GET_ITEM(args, 2)), c3(PyTuple_GET_ITEM(args, 3)), c4(PyTuple_GET_ITEM(args, 4)), c5(PyTuple_GET_ITEM(args, 5))) );
        
        if (!result) return 0;
        return policies.postcall(args, result);
    }

    template <class P, class A0>
    static PyObject* call(R (A0::*pmf)() volatile, PyObject* args, PyObject*, P const& policies)
    {
        // check that each of the arguments is convertible
        from_python<A0 volatile&> c0(PyTuple_GET_ITEM(args, 0));
        if (!c0.convertible()) return 0;

        // find the result converter
        typedef typename P::result_converter result_converter;
        typename eval<result_converter,R>::type cr;
        if (!cr.convertible()) return 0;
        
        if (!policies.precall(args)) return 0;
        
        PyObject* result = cr( ((c0(PyTuple_GET_ITEM(args, 0))).*pmf)() );
        
        if (!result) return 0;
        return policies.postcall(args, result);
    }
    template <class P, class A0, class A1>
    static PyObject* call(R (A0::*pmf)(A1) volatile, PyObject* args, PyObject*, P const& policies)
    {
        // check that each of the arguments is convertible
        from_python<A0 volatile&> c0(PyTuple_GET_ITEM(args, 0));
        if (!c0.convertible()) return 0;
        from_python<A1> c1(PyTuple_GET_ITEM(args, 1));
        if (!c1.convertible()) return 0;

        // find the result converter
        typedef typename P::result_converter result_converter;
        typename eval<result_converter,R>::type cr;
        if (!cr.convertible()) return 0;
        
        if (!policies.precall(args)) return 0;
        
        PyObject* result = cr( ((c0(PyTuple_GET_ITEM(args, 0))).*pmf)(c1(PyTuple_GET_ITEM(args, 1))) );
        
        if (!result) return 0;
        return policies.postcall(args, result);
    }
    template <class P, class A0, class A1, class A2>
    static PyObject* call(R (A0::*pmf)(A1, A2) volatile, PyObject* args, PyObject*, P const& policies)
    {
        // check that each of the arguments is convertible
        from_python<A0 volatile&> c0(PyTuple_GET_ITEM(args, 0));
        if (!c0.convertible()) return 0;
        from_python<A1> c1(PyTuple_GET_ITEM(args, 1));
        if (!c1.convertible()) return 0;
        from_python<A2> c2(PyTuple_GET_ITEM(args, 2));
        if (!c2.convertible()) return 0;

        // find the result converter
        typedef typename P::result_converter result_converter;
        typename eval<result_converter,R>::type cr;
        if (!cr.convertible()) return 0;
        
        if (!policies.precall(args)) return 0;
        
        PyObject* result = cr( ((c0(PyTuple_GET_ITEM(args, 0))).*pmf)(c1(PyTuple_GET_ITEM(args, 1)), c2(PyTuple_GET_ITEM(args, 2))) );
        
        if (!result) return 0;
        return policies.postcall(args, result);
    }
    template <class P, class A0, class A1, class A2, class A3>
    static PyObject* call(R (A0::*pmf)(A1, A2, A3) volatile, PyObject* args, PyObject*, P const& policies)
    {
        // check that each of the arguments is convertible
        from_python<A0 volatile&> c0(PyTuple_GET_ITEM(args, 0));
        if (!c0.convertible()) return 0;
        from_python<A1> c1(PyTuple_GET_ITEM(args, 1));
        if (!c1.convertible()) return 0;
        from_python<A2> c2(PyTuple_GET_ITEM(args, 2));
        if (!c2.convertible()) return 0;
        from_python<A3> c3(PyTuple_GET_ITEM(args, 3));
        if (!c3.convertible()) return 0;

        // find the result converter
        typedef typename P::result_converter result_converter;
        typename eval<result_converter,R>::type cr;
        if (!cr.convertible()) return 0;
        
        if (!policies.precall(args)) return 0;
        
        PyObject* result = cr( ((c0(PyTuple_GET_ITEM(args, 0))).*pmf)(c1(PyTuple_GET_ITEM(args, 1)), c2(PyTuple_GET_ITEM(args, 2)), c3(PyTuple_GET_ITEM(args, 3))) );
        
        if (!result) return 0;
        return policies.postcall(args, result);
    }
    template <class P, class A0, class A1, class A2, class A3, class A4>
    static PyObject* call(R (A0::*pmf)(A1, A2, A3, A4) volatile, PyObject* args, PyObject*, P const& policies)
    {
        // check that each of the arguments is convertible
        from_python<A0 volatile&> c0(PyTuple_GET_ITEM(args, 0));
        if (!c0.convertible()) return 0;
        from_python<A1> c1(PyTuple_GET_ITEM(args, 1));
        if (!c1.convertible()) return 0;
        from_python<A2> c2(PyTuple_GET_ITEM(args, 2));
        if (!c2.convertible()) return 0;
        from_python<A3> c3(PyTuple_GET_ITEM(args, 3));
        if (!c3.convertible()) return 0;
        from_python<A4> c4(PyTuple_GET_ITEM(args, 4));
        if (!c4.convertible()) return 0;

        // find the result converter
        typedef typename P::result_converter result_converter;
        typename eval<result_converter,R>::type cr;
        if (!cr.convertible()) return 0;
        
        if (!policies.precall(args)) return 0;
        
        PyObject* result = cr( ((c0(PyTuple_GET_ITEM(args, 0))).*pmf)(c1(PyTuple_GET_ITEM(args, 1)), c2(PyTuple_GET_ITEM(args, 2)), c3(PyTuple_GET_ITEM(args, 3)), c4(PyTuple_GET_ITEM(args, 4))) );
        
        if (!result) return 0;
        return policies.postcall(args, result);
    }
    template <class P, class A0, class A1, class A2, class A3, class A4, class A5>
    static PyObject* call(R (A0::*pmf)(A1, A2, A3, A4, A5) volatile, PyObject* args, PyObject*, P const& policies)
    {
        // check that each of the arguments is convertible
        from_python<A0 volatile&> c0(PyTuple_GET_ITEM(args, 0));
        if (!c0.convertible()) return 0;
        from_python<A1> c1(PyTuple_GET_ITEM(args, 1));
        if (!c1.convertible()) return 0;
        from_python<A2> c2(PyTuple_GET_ITEM(args, 2));
        if (!c2.convertible()) return 0;
        from_python<A3> c3(PyTuple_GET_ITEM(args, 3));
        if (!c3.convertible()) return 0;
        from_python<A4> c4(PyTuple_GET_ITEM(args, 4));
        if (!c4.convertible()) return 0;
        from_python<A5> c5(PyTuple_GET_ITEM(args, 5));
        if (!c5.convertible()) return 0;

        // find the result converter
        typedef typename P::result_converter result_converter;
        typename eval<result_converter,R>::type cr;
        if (!cr.convertible()) return 0;
        
        if (!policies.precall(args)) return 0;
        
        PyObject* result = cr( ((c0(PyTuple_GET_ITEM(args, 0))).*pmf)(c1(PyTuple_GET_ITEM(args, 1)), c2(PyTuple_GET_ITEM(args, 2)), c3(PyTuple_GET_ITEM(args, 3)), c4(PyTuple_GET_ITEM(args, 4)), c5(PyTuple_GET_ITEM(args, 5))) );
        
        if (!result) return 0;
        return policies.postcall(args, result);
    }


// missing const volatile type traits
#  ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    template <class P, class A0>
    static PyObject* call(R (A0::*pmf)() const volatile, PyObject* args, PyObject*, P const& policies)
    {
        // check that each of the arguments is convertible
        from_python<A0 const volatile&> c0(PyTuple_GET_ITEM(args, 0));
        if (!c0.convertible()) return 0;

        // find the result converter
        typedef typename P::result_converter result_converter;
        typename eval<result_converter,R>::type cr;
        if (!cr.convertible()) return 0;
        
        if (!policies.precall(args)) return 0;
        
        PyObject* result = cr( ((c0(PyTuple_GET_ITEM(args, 0))).*pmf)() );
        
        if (!result) return 0;
        return policies.postcall(args, result);
    }
    template <class P, class A0, class A1>
    static PyObject* call(R (A0::*pmf)(A1) const volatile, PyObject* args, PyObject*, P const& policies)
    {
        // check that each of the arguments is convertible
        from_python<A0 const volatile&> c0(PyTuple_GET_ITEM(args, 0));
        if (!c0.convertible()) return 0;
        from_python<A1> c1(PyTuple_GET_ITEM(args, 1));
        if (!c1.convertible()) return 0;

        // find the result converter
        typedef typename P::result_converter result_converter;
        typename eval<result_converter,R>::type cr;
        if (!cr.convertible()) return 0;
        
        if (!policies.precall(args)) return 0;
        
        PyObject* result = cr( ((c0(PyTuple_GET_ITEM(args, 0))).*pmf)(c1(PyTuple_GET_ITEM(args, 1))) );
        
        if (!result) return 0;
        return policies.postcall(args, result);
    }
    template <class P, class A0, class A1, class A2>
    static PyObject* call(R (A0::*pmf)(A1, A2) const volatile, PyObject* args, PyObject*, P const& policies)
    {
        // check that each of the arguments is convertible
        from_python<A0 const volatile&> c0(PyTuple_GET_ITEM(args, 0));
        if (!c0.convertible()) return 0;
        from_python<A1> c1(PyTuple_GET_ITEM(args, 1));
        if (!c1.convertible()) return 0;
        from_python<A2> c2(PyTuple_GET_ITEM(args, 2));
        if (!c2.convertible()) return 0;

        // find the result converter
        typedef typename P::result_converter result_converter;
        typename eval<result_converter,R>::type cr;
        if (!cr.convertible()) return 0;
        
        if (!policies.precall(args)) return 0;
        
        PyObject* result = cr( ((c0(PyTuple_GET_ITEM(args, 0))).*pmf)(c1(PyTuple_GET_ITEM(args, 1)), c2(PyTuple_GET_ITEM(args, 2))) );
        
        if (!result) return 0;
        return policies.postcall(args, result);
    }
    template <class P, class A0, class A1, class A2, class A3>
    static PyObject* call(R (A0::*pmf)(A1, A2, A3) const volatile, PyObject* args, PyObject*, P const& policies)
    {
        // check that each of the arguments is convertible
        from_python<A0 const volatile&> c0(PyTuple_GET_ITEM(args, 0));
        if (!c0.convertible()) return 0;
        from_python<A1> c1(PyTuple_GET_ITEM(args, 1));
        if (!c1.convertible()) return 0;
        from_python<A2> c2(PyTuple_GET_ITEM(args, 2));
        if (!c2.convertible()) return 0;
        from_python<A3> c3(PyTuple_GET_ITEM(args, 3));
        if (!c3.convertible()) return 0;

        // find the result converter
        typedef typename P::result_converter result_converter;
        typename eval<result_converter,R>::type cr;
        if (!cr.convertible()) return 0;
        
        if (!policies.precall(args)) return 0;
        
        PyObject* result = cr( ((c0(PyTuple_GET_ITEM(args, 0))).*pmf)(c1(PyTuple_GET_ITEM(args, 1)), c2(PyTuple_GET_ITEM(args, 2)), c3(PyTuple_GET_ITEM(args, 3))) );
        
        if (!result) return 0;
        return policies.postcall(args, result);
    }
    template <class P, class A0, class A1, class A2, class A3, class A4>
    static PyObject* call(R (A0::*pmf)(A1, A2, A3, A4) const volatile, PyObject* args, PyObject*, P const& policies)
    {
        // check that each of the arguments is convertible
        from_python<A0 const volatile&> c0(PyTuple_GET_ITEM(args, 0));
        if (!c0.convertible()) return 0;
        from_python<A1> c1(PyTuple_GET_ITEM(args, 1));
        if (!c1.convertible()) return 0;
        from_python<A2> c2(PyTuple_GET_ITEM(args, 2));
        if (!c2.convertible()) return 0;
        from_python<A3> c3(PyTuple_GET_ITEM(args, 3));
        if (!c3.convertible()) return 0;
        from_python<A4> c4(PyTuple_GET_ITEM(args, 4));
        if (!c4.convertible()) return 0;

        // find the result converter
        typedef typename P::result_converter result_converter;
        typename eval<result_converter,R>::type cr;
        if (!cr.convertible()) return 0;
        
        if (!policies.precall(args)) return 0;
        
        PyObject* result = cr( ((c0(PyTuple_GET_ITEM(args, 0))).*pmf)(c1(PyTuple_GET_ITEM(args, 1)), c2(PyTuple_GET_ITEM(args, 2)), c3(PyTuple_GET_ITEM(args, 3)), c4(PyTuple_GET_ITEM(args, 4))) );
        
        if (!result) return 0;
        return policies.postcall(args, result);
    }
    template <class P, class A0, class A1, class A2, class A3, class A4, class A5>
    static PyObject* call(R (A0::*pmf)(A1, A2, A3, A4, A5) const volatile, PyObject* args, PyObject*, P const& policies)
    {
        // check that each of the arguments is convertible
        from_python<A0 const volatile&> c0(PyTuple_GET_ITEM(args, 0));
        if (!c0.convertible()) return 0;
        from_python<A1> c1(PyTuple_GET_ITEM(args, 1));
        if (!c1.convertible()) return 0;
        from_python<A2> c2(PyTuple_GET_ITEM(args, 2));
        if (!c2.convertible()) return 0;
        from_python<A3> c3(PyTuple_GET_ITEM(args, 3));
        if (!c3.convertible()) return 0;
        from_python<A4> c4(PyTuple_GET_ITEM(args, 4));
        if (!c4.convertible()) return 0;
        from_python<A5> c5(PyTuple_GET_ITEM(args, 5));
        if (!c5.convertible()) return 0;

        // find the result converter
        typedef typename P::result_converter result_converter;
        typename eval<result_converter,R>::type cr;
        if (!cr.convertible()) return 0;
        
        if (!policies.precall(args)) return 0;
        
        PyObject* result = cr( ((c0(PyTuple_GET_ITEM(args, 0))).*pmf)(c1(PyTuple_GET_ITEM(args, 1)), c2(PyTuple_GET_ITEM(args, 2)), c3(PyTuple_GET_ITEM(args, 3)), c4(PyTuple_GET_ITEM(args, 4)), c5(PyTuple_GET_ITEM(args, 5))) );
        
        if (!result) return 0;
        return policies.postcall(args, result);
    }

#  endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

  
    template <class P>
    static PyObject* call(R (*pf)(), PyObject* args, PyObject*, P const& policies)
    {
        // find the result converter
        typedef typename P::result_converter result_converter;
        typename eval<result_converter,R>::type c0;
        if (!c0.convertible()) return 0;
        
        if (!policies.precall(args)) return 0;
        
        PyObject* result = c0( (*pf)() );
        
        if (!result) return 0;
        return policies.postcall(args, result);
    }
  
    template <class P, class A0>
    static PyObject* call(R (*pf)(A0), PyObject* args, PyObject*, P const& policies)
    {
        // check that each of the arguments is convertible
        from_python<A0> c0(PyTuple_GET_ITEM(args, 0));
        if (!c0.convertible()) return 0;

        // find the result converter
        typedef typename P::result_converter result_converter;
        typename eval<result_converter,R>::type c1;
        if (!c1.convertible()) return 0;
        
        if (!policies.precall(args)) return 0;
        
        PyObject* result = c1( (*pf)(c0(PyTuple_GET_ITEM(args, 0))) );
        
        if (!result) return 0;
        return policies.postcall(args, result);
    }
    template <class P, class A0, class A1>
    static PyObject* call(R (*pf)(A0, A1), PyObject* args, PyObject*, P const& policies)
    {
        // check that each of the arguments is convertible
        from_python<A0> c0(PyTuple_GET_ITEM(args, 0));
        if (!c0.convertible()) return 0;
        from_python<A1> c1(PyTuple_GET_ITEM(args, 1));
        if (!c1.convertible()) return 0;

        // find the result converter
        typedef typename P::result_converter result_converter;
        typename eval<result_converter,R>::type c2;
        if (!c2.convertible()) return 0;
        
        if (!policies.precall(args)) return 0;
        
        PyObject* result = c2( (*pf)(c0(PyTuple_GET_ITEM(args, 0)), c1(PyTuple_GET_ITEM(args, 1))) );
        
        if (!result) return 0;
        return policies.postcall(args, result);
    }
    template <class P, class A0, class A1, class A2>
    static PyObject* call(R (*pf)(A0, A1, A2), PyObject* args, PyObject*, P const& policies)
    {
        // check that each of the arguments is convertible
        from_python<A0> c0(PyTuple_GET_ITEM(args, 0));
        if (!c0.convertible()) return 0;
        from_python<A1> c1(PyTuple_GET_ITEM(args, 1));
        if (!c1.convertible()) return 0;
        from_python<A2> c2(PyTuple_GET_ITEM(args, 2));
        if (!c2.convertible()) return 0;

        // find the result converter
        typedef typename P::result_converter result_converter;
        typename eval<result_converter,R>::type c3;
        if (!c3.convertible()) return 0;
        
        if (!policies.precall(args)) return 0;
        
        PyObject* result = c3( (*pf)(c0(PyTuple_GET_ITEM(args, 0)), c1(PyTuple_GET_ITEM(args, 1)), c2(PyTuple_GET_ITEM(args, 2))) );
        
        if (!result) return 0;
        return policies.postcall(args, result);
    }
    template <class P, class A0, class A1, class A2, class A3>
    static PyObject* call(R (*pf)(A0, A1, A2, A3), PyObject* args, PyObject*, P const& policies)
    {
        // check that each of the arguments is convertible
        from_python<A0> c0(PyTuple_GET_ITEM(args, 0));
        if (!c0.convertible()) return 0;
        from_python<A1> c1(PyTuple_GET_ITEM(args, 1));
        if (!c1.convertible()) return 0;
        from_python<A2> c2(PyTuple_GET_ITEM(args, 2));
        if (!c2.convertible()) return 0;
        from_python<A3> c3(PyTuple_GET_ITEM(args, 3));
        if (!c3.convertible()) return 0;

        // find the result converter
        typedef typename P::result_converter result_converter;
        typename eval<result_converter,R>::type c4;
        if (!c4.convertible()) return 0;
        
        if (!policies.precall(args)) return 0;
        
        PyObject* result = c4( (*pf)(c0(PyTuple_GET_ITEM(args, 0)), c1(PyTuple_GET_ITEM(args, 1)), c2(PyTuple_GET_ITEM(args, 2)), c3(PyTuple_GET_ITEM(args, 3))) );
        
        if (!result) return 0;
        return policies.postcall(args, result);
    }
    template <class P, class A0, class A1, class A2, class A3, class A4>
    static PyObject* call(R (*pf)(A0, A1, A2, A3, A4), PyObject* args, PyObject*, P const& policies)
    {
        // check that each of the arguments is convertible
        from_python<A0> c0(PyTuple_GET_ITEM(args, 0));
        if (!c0.convertible()) return 0;
        from_python<A1> c1(PyTuple_GET_ITEM(args, 1));
        if (!c1.convertible()) return 0;
        from_python<A2> c2(PyTuple_GET_ITEM(args, 2));
        if (!c2.convertible()) return 0;
        from_python<A3> c3(PyTuple_GET_ITEM(args, 3));
        if (!c3.convertible()) return 0;
        from_python<A4> c4(PyTuple_GET_ITEM(args, 4));
        if (!c4.convertible()) return 0;

        // find the result converter
        typedef typename P::result_converter result_converter;
        typename eval<result_converter,R>::type c5;
        if (!c5.convertible()) return 0;
        
        if (!policies.precall(args)) return 0;
        
        PyObject* result = c5( (*pf)(c0(PyTuple_GET_ITEM(args, 0)), c1(PyTuple_GET_ITEM(args, 1)), c2(PyTuple_GET_ITEM(args, 2)), c3(PyTuple_GET_ITEM(args, 3)), c4(PyTuple_GET_ITEM(args, 4))) );
        
        if (!result) return 0;
        return policies.postcall(args, result);
    }
    template <class P, class A0, class A1, class A2, class A3, class A4, class A5>
    static PyObject* call(R (*pf)(A0, A1, A2, A3, A4, A5), PyObject* args, PyObject*, P const& policies)
    {
        // check that each of the arguments is convertible
        from_python<A0> c0(PyTuple_GET_ITEM(args, 0));
        if (!c0.convertible()) return 0;
        from_python<A1> c1(PyTuple_GET_ITEM(args, 1));
        if (!c1.convertible()) return 0;
        from_python<A2> c2(PyTuple_GET_ITEM(args, 2));
        if (!c2.convertible()) return 0;
        from_python<A3> c3(PyTuple_GET_ITEM(args, 3));
        if (!c3.convertible()) return 0;
        from_python<A4> c4(PyTuple_GET_ITEM(args, 4));
        if (!c4.convertible()) return 0;
        from_python<A5> c5(PyTuple_GET_ITEM(args, 5));
        if (!c5.convertible()) return 0;

        // find the result converter
        typedef typename P::result_converter result_converter;
        typename eval<result_converter,R>::type c6;
        if (!c6.convertible()) return 0;
        
        if (!policies.precall(args)) return 0;
        
        PyObject* result = c6( (*pf)(c0(PyTuple_GET_ITEM(args, 0)), c1(PyTuple_GET_ITEM(args, 1)), c2(PyTuple_GET_ITEM(args, 2)), c3(PyTuple_GET_ITEM(args, 3)), c4(PyTuple_GET_ITEM(args, 4)), c5(PyTuple_GET_ITEM(args, 5))) );
        
        if (!result) return 0;
        return policies.postcall(args, result);
    }
};
                           
template <>
struct returning<void>
{
    typedef void R;
    template <class P, class A0>
    static PyObject* call(R (A0::*pmf)(), PyObject* args, PyObject*, P const& policies)
    {
        // check that each of the arguments is convertible
        from_python<A0&> c0(PyTuple_GET_ITEM(args, 0));
        if (!c0.convertible()) return 0;
        
        if (!policies.precall(args)) return 0;
        
        ((c0(PyTuple_GET_ITEM(args, 0))).*pmf)();
        
        return policies.postcall(args, detail::none());
    }
    template <class P, class A0, class A1>
    static PyObject* call(R (A0::*pmf)(A1), PyObject* args, PyObject*, P const& policies)
    {
        // check that each of the arguments is convertible
        from_python<A0&> c0(PyTuple_GET_ITEM(args, 0));
        if (!c0.convertible()) return 0;
        from_python<A1> c1(PyTuple_GET_ITEM(args, 1));
        if (!c1.convertible()) return 0;
        
        if (!policies.precall(args)) return 0;
        
        ((c0(PyTuple_GET_ITEM(args, 0))).*pmf)(c1(PyTuple_GET_ITEM(args, 1)));
        
        return policies.postcall(args, detail::none());
    }
    template <class P, class A0, class A1, class A2>
    static PyObject* call(R (A0::*pmf)(A1, A2), PyObject* args, PyObject*, P const& policies)
    {
        // check that each of the arguments is convertible
        from_python<A0&> c0(PyTuple_GET_ITEM(args, 0));
        if (!c0.convertible()) return 0;
        from_python<A1> c1(PyTuple_GET_ITEM(args, 1));
        if (!c1.convertible()) return 0;
        from_python<A2> c2(PyTuple_GET_ITEM(args, 2));
        if (!c2.convertible()) return 0;
        
        if (!policies.precall(args)) return 0;
        
        ((c0(PyTuple_GET_ITEM(args, 0))).*pmf)(c1(PyTuple_GET_ITEM(args, 1)), c2(PyTuple_GET_ITEM(args, 2)));
        
        return policies.postcall(args, detail::none());
    }
    template <class P, class A0, class A1, class A2, class A3>
    static PyObject* call(R (A0::*pmf)(A1, A2, A3), PyObject* args, PyObject*, P const& policies)
    {
        // check that each of the arguments is convertible
        from_python<A0&> c0(PyTuple_GET_ITEM(args, 0));
        if (!c0.convertible()) return 0;
        from_python<A1> c1(PyTuple_GET_ITEM(args, 1));
        if (!c1.convertible()) return 0;
        from_python<A2> c2(PyTuple_GET_ITEM(args, 2));
        if (!c2.convertible()) return 0;
        from_python<A3> c3(PyTuple_GET_ITEM(args, 3));
        if (!c3.convertible()) return 0;
        
        if (!policies.precall(args)) return 0;
        
        ((c0(PyTuple_GET_ITEM(args, 0))).*pmf)(c1(PyTuple_GET_ITEM(args, 1)), c2(PyTuple_GET_ITEM(args, 2)), c3(PyTuple_GET_ITEM(args, 3)));
        
        return policies.postcall(args, detail::none());
    }
    template <class P, class A0, class A1, class A2, class A3, class A4>
    static PyObject* call(R (A0::*pmf)(A1, A2, A3, A4), PyObject* args, PyObject*, P const& policies)
    {
        // check that each of the arguments is convertible
        from_python<A0&> c0(PyTuple_GET_ITEM(args, 0));
        if (!c0.convertible()) return 0;
        from_python<A1> c1(PyTuple_GET_ITEM(args, 1));
        if (!c1.convertible()) return 0;
        from_python<A2> c2(PyTuple_GET_ITEM(args, 2));
        if (!c2.convertible()) return 0;
        from_python<A3> c3(PyTuple_GET_ITEM(args, 3));
        if (!c3.convertible()) return 0;
        from_python<A4> c4(PyTuple_GET_ITEM(args, 4));
        if (!c4.convertible()) return 0;
        
        if (!policies.precall(args)) return 0;
        
        ((c0(PyTuple_GET_ITEM(args, 0))).*pmf)(c1(PyTuple_GET_ITEM(args, 1)), c2(PyTuple_GET_ITEM(args, 2)), c3(PyTuple_GET_ITEM(args, 3)), c4(PyTuple_GET_ITEM(args, 4)));
        
        return policies.postcall(args, detail::none());
    }
    template <class P, class A0, class A1, class A2, class A3, class A4, class A5>
    static PyObject* call(R (A0::*pmf)(A1, A2, A3, A4, A5), PyObject* args, PyObject*, P const& policies)
    {
        // check that each of the arguments is convertible
        from_python<A0&> c0(PyTuple_GET_ITEM(args, 0));
        if (!c0.convertible()) return 0;
        from_python<A1> c1(PyTuple_GET_ITEM(args, 1));
        if (!c1.convertible()) return 0;
        from_python<A2> c2(PyTuple_GET_ITEM(args, 2));
        if (!c2.convertible()) return 0;
        from_python<A3> c3(PyTuple_GET_ITEM(args, 3));
        if (!c3.convertible()) return 0;
        from_python<A4> c4(PyTuple_GET_ITEM(args, 4));
        if (!c4.convertible()) return 0;
        from_python<A5> c5(PyTuple_GET_ITEM(args, 5));
        if (!c5.convertible()) return 0;
        
        if (!policies.precall(args)) return 0;
        
        ((c0(PyTuple_GET_ITEM(args, 0))).*pmf)(c1(PyTuple_GET_ITEM(args, 1)), c2(PyTuple_GET_ITEM(args, 2)), c3(PyTuple_GET_ITEM(args, 3)), c4(PyTuple_GET_ITEM(args, 4)), c5(PyTuple_GET_ITEM(args, 5)));
        
        return policies.postcall(args, detail::none());
    }

    template <class P, class A0>
    static PyObject* call(R (A0::*pmf)() const, PyObject* args, PyObject*, P const& policies)
    {
        // check that each of the arguments is convertible
        from_python<A0 const&> c0(PyTuple_GET_ITEM(args, 0));
        if (!c0.convertible()) return 0;
        
        if (!policies.precall(args)) return 0;
        
        ((c0(PyTuple_GET_ITEM(args, 0))).*pmf)();
        
        return policies.postcall(args, detail::none());
    }
    template <class P, class A0, class A1>
    static PyObject* call(R (A0::*pmf)(A1) const, PyObject* args, PyObject*, P const& policies)
    {
        // check that each of the arguments is convertible
        from_python<A0 const&> c0(PyTuple_GET_ITEM(args, 0));
        if (!c0.convertible()) return 0;
        from_python<A1> c1(PyTuple_GET_ITEM(args, 1));
        if (!c1.convertible()) return 0;
        
        if (!policies.precall(args)) return 0;
        
        ((c0(PyTuple_GET_ITEM(args, 0))).*pmf)(c1(PyTuple_GET_ITEM(args, 1)));
        
        return policies.postcall(args, detail::none());
    }
    template <class P, class A0, class A1, class A2>
    static PyObject* call(R (A0::*pmf)(A1, A2) const, PyObject* args, PyObject*, P const& policies)
    {
        // check that each of the arguments is convertible
        from_python<A0 const&> c0(PyTuple_GET_ITEM(args, 0));
        if (!c0.convertible()) return 0;
        from_python<A1> c1(PyTuple_GET_ITEM(args, 1));
        if (!c1.convertible()) return 0;
        from_python<A2> c2(PyTuple_GET_ITEM(args, 2));
        if (!c2.convertible()) return 0;
        
        if (!policies.precall(args)) return 0;
        
        ((c0(PyTuple_GET_ITEM(args, 0))).*pmf)(c1(PyTuple_GET_ITEM(args, 1)), c2(PyTuple_GET_ITEM(args, 2)));
        
        return policies.postcall(args, detail::none());
    }
    template <class P, class A0, class A1, class A2, class A3>
    static PyObject* call(R (A0::*pmf)(A1, A2, A3) const, PyObject* args, PyObject*, P const& policies)
    {
        // check that each of the arguments is convertible
        from_python<A0 const&> c0(PyTuple_GET_ITEM(args, 0));
        if (!c0.convertible()) return 0;
        from_python<A1> c1(PyTuple_GET_ITEM(args, 1));
        if (!c1.convertible()) return 0;
        from_python<A2> c2(PyTuple_GET_ITEM(args, 2));
        if (!c2.convertible()) return 0;
        from_python<A3> c3(PyTuple_GET_ITEM(args, 3));
        if (!c3.convertible()) return 0;
        
        if (!policies.precall(args)) return 0;
        
        ((c0(PyTuple_GET_ITEM(args, 0))).*pmf)(c1(PyTuple_GET_ITEM(args, 1)), c2(PyTuple_GET_ITEM(args, 2)), c3(PyTuple_GET_ITEM(args, 3)));
        
        return policies.postcall(args, detail::none());
    }
    template <class P, class A0, class A1, class A2, class A3, class A4>
    static PyObject* call(R (A0::*pmf)(A1, A2, A3, A4) const, PyObject* args, PyObject*, P const& policies)
    {
        // check that each of the arguments is convertible
        from_python<A0 const&> c0(PyTuple_GET_ITEM(args, 0));
        if (!c0.convertible()) return 0;
        from_python<A1> c1(PyTuple_GET_ITEM(args, 1));
        if (!c1.convertible()) return 0;
        from_python<A2> c2(PyTuple_GET_ITEM(args, 2));
        if (!c2.convertible()) return 0;
        from_python<A3> c3(PyTuple_GET_ITEM(args, 3));
        if (!c3.convertible()) return 0;
        from_python<A4> c4(PyTuple_GET_ITEM(args, 4));
        if (!c4.convertible()) return 0;
        
        if (!policies.precall(args)) return 0;
        
        ((c0(PyTuple_GET_ITEM(args, 0))).*pmf)(c1(PyTuple_GET_ITEM(args, 1)), c2(PyTuple_GET_ITEM(args, 2)), c3(PyTuple_GET_ITEM(args, 3)), c4(PyTuple_GET_ITEM(args, 4)));
        
        return policies.postcall(args, detail::none());
    }
    template <class P, class A0, class A1, class A2, class A3, class A4, class A5>
    static PyObject* call(R (A0::*pmf)(A1, A2, A3, A4, A5) const, PyObject* args, PyObject*, P const& policies)
    {
        // check that each of the arguments is convertible
        from_python<A0 const&> c0(PyTuple_GET_ITEM(args, 0));
        if (!c0.convertible()) return 0;
        from_python<A1> c1(PyTuple_GET_ITEM(args, 1));
        if (!c1.convertible()) return 0;
        from_python<A2> c2(PyTuple_GET_ITEM(args, 2));
        if (!c2.convertible()) return 0;
        from_python<A3> c3(PyTuple_GET_ITEM(args, 3));
        if (!c3.convertible()) return 0;
        from_python<A4> c4(PyTuple_GET_ITEM(args, 4));
        if (!c4.convertible()) return 0;
        from_python<A5> c5(PyTuple_GET_ITEM(args, 5));
        if (!c5.convertible()) return 0;
        
        if (!policies.precall(args)) return 0;
        
        ((c0(PyTuple_GET_ITEM(args, 0))).*pmf)(c1(PyTuple_GET_ITEM(args, 1)), c2(PyTuple_GET_ITEM(args, 2)), c3(PyTuple_GET_ITEM(args, 3)), c4(PyTuple_GET_ITEM(args, 4)), c5(PyTuple_GET_ITEM(args, 5)));
        
        return policies.postcall(args, detail::none());
    }

    template <class P, class A0>
    static PyObject* call(R (A0::*pmf)() volatile, PyObject* args, PyObject*, P const& policies)
    {
        // check that each of the arguments is convertible
        from_python<A0 volatile&> c0(PyTuple_GET_ITEM(args, 0));
        if (!c0.convertible()) return 0;
        
        if (!policies.precall(args)) return 0;
        
        ((c0(PyTuple_GET_ITEM(args, 0))).*pmf)();
        
        return policies.postcall(args, detail::none());
    }
    template <class P, class A0, class A1>
    static PyObject* call(R (A0::*pmf)(A1) volatile, PyObject* args, PyObject*, P const& policies)
    {
        // check that each of the arguments is convertible
        from_python<A0 volatile&> c0(PyTuple_GET_ITEM(args, 0));
        if (!c0.convertible()) return 0;
        from_python<A1> c1(PyTuple_GET_ITEM(args, 1));
        if (!c1.convertible()) return 0;
        
        if (!policies.precall(args)) return 0;
        
        ((c0(PyTuple_GET_ITEM(args, 0))).*pmf)(c1(PyTuple_GET_ITEM(args, 1)));
        
        return policies.postcall(args, detail::none());
    }
    template <class P, class A0, class A1, class A2>
    static PyObject* call(R (A0::*pmf)(A1, A2) volatile, PyObject* args, PyObject*, P const& policies)
    {
        // check that each of the arguments is convertible
        from_python<A0 volatile&> c0(PyTuple_GET_ITEM(args, 0));
        if (!c0.convertible()) return 0;
        from_python<A1> c1(PyTuple_GET_ITEM(args, 1));
        if (!c1.convertible()) return 0;
        from_python<A2> c2(PyTuple_GET_ITEM(args, 2));
        if (!c2.convertible()) return 0;
        
        if (!policies.precall(args)) return 0;
        
        ((c0(PyTuple_GET_ITEM(args, 0))).*pmf)(c1(PyTuple_GET_ITEM(args, 1)), c2(PyTuple_GET_ITEM(args, 2)));
        
        return policies.postcall(args, detail::none());
    }
    template <class P, class A0, class A1, class A2, class A3>
    static PyObject* call(R (A0::*pmf)(A1, A2, A3) volatile, PyObject* args, PyObject*, P const& policies)
    {
        // check that each of the arguments is convertible
        from_python<A0 volatile&> c0(PyTuple_GET_ITEM(args, 0));
        if (!c0.convertible()) return 0;
        from_python<A1> c1(PyTuple_GET_ITEM(args, 1));
        if (!c1.convertible()) return 0;
        from_python<A2> c2(PyTuple_GET_ITEM(args, 2));
        if (!c2.convertible()) return 0;
        from_python<A3> c3(PyTuple_GET_ITEM(args, 3));
        if (!c3.convertible()) return 0;
        
        if (!policies.precall(args)) return 0;
        
        ((c0(PyTuple_GET_ITEM(args, 0))).*pmf)(c1(PyTuple_GET_ITEM(args, 1)), c2(PyTuple_GET_ITEM(args, 2)), c3(PyTuple_GET_ITEM(args, 3)));
        
        return policies.postcall(args, detail::none());
    }
    template <class P, class A0, class A1, class A2, class A3, class A4>
    static PyObject* call(R (A0::*pmf)(A1, A2, A3, A4) volatile, PyObject* args, PyObject*, P const& policies)
    {
        // check that each of the arguments is convertible
        from_python<A0 volatile&> c0(PyTuple_GET_ITEM(args, 0));
        if (!c0.convertible()) return 0;
        from_python<A1> c1(PyTuple_GET_ITEM(args, 1));
        if (!c1.convertible()) return 0;
        from_python<A2> c2(PyTuple_GET_ITEM(args, 2));
        if (!c2.convertible()) return 0;
        from_python<A3> c3(PyTuple_GET_ITEM(args, 3));
        if (!c3.convertible()) return 0;
        from_python<A4> c4(PyTuple_GET_ITEM(args, 4));
        if (!c4.convertible()) return 0;
        
        if (!policies.precall(args)) return 0;
        
        ((c0(PyTuple_GET_ITEM(args, 0))).*pmf)(c1(PyTuple_GET_ITEM(args, 1)), c2(PyTuple_GET_ITEM(args, 2)), c3(PyTuple_GET_ITEM(args, 3)), c4(PyTuple_GET_ITEM(args, 4)));
        
        return policies.postcall(args, detail::none());
    }
    template <class P, class A0, class A1, class A2, class A3, class A4, class A5>
    static PyObject* call(R (A0::*pmf)(A1, A2, A3, A4, A5) volatile, PyObject* args, PyObject*, P const& policies)
    {
        // check that each of the arguments is convertible
        from_python<A0 volatile&> c0(PyTuple_GET_ITEM(args, 0));
        if (!c0.convertible()) return 0;
        from_python<A1> c1(PyTuple_GET_ITEM(args, 1));
        if (!c1.convertible()) return 0;
        from_python<A2> c2(PyTuple_GET_ITEM(args, 2));
        if (!c2.convertible()) return 0;
        from_python<A3> c3(PyTuple_GET_ITEM(args, 3));
        if (!c3.convertible()) return 0;
        from_python<A4> c4(PyTuple_GET_ITEM(args, 4));
        if (!c4.convertible()) return 0;
        from_python<A5> c5(PyTuple_GET_ITEM(args, 5));
        if (!c5.convertible()) return 0;
        
        if (!policies.precall(args)) return 0;
        
        ((c0(PyTuple_GET_ITEM(args, 0))).*pmf)(c1(PyTuple_GET_ITEM(args, 1)), c2(PyTuple_GET_ITEM(args, 2)), c3(PyTuple_GET_ITEM(args, 3)), c4(PyTuple_GET_ITEM(args, 4)), c5(PyTuple_GET_ITEM(args, 5)));
        
        return policies.postcall(args, detail::none());
    }


// missing const volatile type traits
#  ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    template <class P, class A0>
    static PyObject* call(R (A0::*pmf)() const volatile, PyObject* args, PyObject*, P const& policies)
    {
        // check that each of the arguments is convertible
        from_python<A0 const volatile&> c0(PyTuple_GET_ITEM(args, 0));
        if (!c0.convertible()) return 0;
        
        if (!policies.precall(args)) return 0;
        
        ((c0(PyTuple_GET_ITEM(args, 0))).*pmf)();
        
        return policies.postcall(args, detail::none());
    }
    template <class P, class A0, class A1>
    static PyObject* call(R (A0::*pmf)(A1) const volatile, PyObject* args, PyObject*, P const& policies)
    {
        // check that each of the arguments is convertible
        from_python<A0 const volatile&> c0(PyTuple_GET_ITEM(args, 0));
        if (!c0.convertible()) return 0;
        from_python<A1> c1(PyTuple_GET_ITEM(args, 1));
        if (!c1.convertible()) return 0;
        
        if (!policies.precall(args)) return 0;
        
        ((c0(PyTuple_GET_ITEM(args, 0))).*pmf)(c1(PyTuple_GET_ITEM(args, 1)));
        
        return policies.postcall(args, detail::none());
    }
    template <class P, class A0, class A1, class A2>
    static PyObject* call(R (A0::*pmf)(A1, A2) const volatile, PyObject* args, PyObject*, P const& policies)
    {
        // check that each of the arguments is convertible
        from_python<A0 const volatile&> c0(PyTuple_GET_ITEM(args, 0));
        if (!c0.convertible()) return 0;
        from_python<A1> c1(PyTuple_GET_ITEM(args, 1));
        if (!c1.convertible()) return 0;
        from_python<A2> c2(PyTuple_GET_ITEM(args, 2));
        if (!c2.convertible()) return 0;
        
        if (!policies.precall(args)) return 0;
        
        ((c0(PyTuple_GET_ITEM(args, 0))).*pmf)(c1(PyTuple_GET_ITEM(args, 1)), c2(PyTuple_GET_ITEM(args, 2)));
        
        return policies.postcall(args, detail::none());
    }
    template <class P, class A0, class A1, class A2, class A3>
    static PyObject* call(R (A0::*pmf)(A1, A2, A3) const volatile, PyObject* args, PyObject*, P const& policies)
    {
        // check that each of the arguments is convertible
        from_python<A0 const volatile&> c0(PyTuple_GET_ITEM(args, 0));
        if (!c0.convertible()) return 0;
        from_python<A1> c1(PyTuple_GET_ITEM(args, 1));
        if (!c1.convertible()) return 0;
        from_python<A2> c2(PyTuple_GET_ITEM(args, 2));
        if (!c2.convertible()) return 0;
        from_python<A3> c3(PyTuple_GET_ITEM(args, 3));
        if (!c3.convertible()) return 0;
        
        if (!policies.precall(args)) return 0;
        
        ((c0(PyTuple_GET_ITEM(args, 0))).*pmf)(c1(PyTuple_GET_ITEM(args, 1)), c2(PyTuple_GET_ITEM(args, 2)), c3(PyTuple_GET_ITEM(args, 3)));
        
        return policies.postcall(args, detail::none());
    }
    template <class P, class A0, class A1, class A2, class A3, class A4>
    static PyObject* call(R (A0::*pmf)(A1, A2, A3, A4) const volatile, PyObject* args, PyObject*, P const& policies)
    {
        // check that each of the arguments is convertible
        from_python<A0 const volatile&> c0(PyTuple_GET_ITEM(args, 0));
        if (!c0.convertible()) return 0;
        from_python<A1> c1(PyTuple_GET_ITEM(args, 1));
        if (!c1.convertible()) return 0;
        from_python<A2> c2(PyTuple_GET_ITEM(args, 2));
        if (!c2.convertible()) return 0;
        from_python<A3> c3(PyTuple_GET_ITEM(args, 3));
        if (!c3.convertible()) return 0;
        from_python<A4> c4(PyTuple_GET_ITEM(args, 4));
        if (!c4.convertible()) return 0;
        
        if (!policies.precall(args)) return 0;
        
        ((c0(PyTuple_GET_ITEM(args, 0))).*pmf)(c1(PyTuple_GET_ITEM(args, 1)), c2(PyTuple_GET_ITEM(args, 2)), c3(PyTuple_GET_ITEM(args, 3)), c4(PyTuple_GET_ITEM(args, 4)));
        
        return policies.postcall(args, detail::none());
    }
    template <class P, class A0, class A1, class A2, class A3, class A4, class A5>
    static PyObject* call(R (A0::*pmf)(A1, A2, A3, A4, A5) const volatile, PyObject* args, PyObject*, P const& policies)
    {
        // check that each of the arguments is convertible
        from_python<A0 const volatile&> c0(PyTuple_GET_ITEM(args, 0));
        if (!c0.convertible()) return 0;
        from_python<A1> c1(PyTuple_GET_ITEM(args, 1));
        if (!c1.convertible()) return 0;
        from_python<A2> c2(PyTuple_GET_ITEM(args, 2));
        if (!c2.convertible()) return 0;
        from_python<A3> c3(PyTuple_GET_ITEM(args, 3));
        if (!c3.convertible()) return 0;
        from_python<A4> c4(PyTuple_GET_ITEM(args, 4));
        if (!c4.convertible()) return 0;
        from_python<A5> c5(PyTuple_GET_ITEM(args, 5));
        if (!c5.convertible()) return 0;
        
        if (!policies.precall(args)) return 0;
        
        ((c0(PyTuple_GET_ITEM(args, 0))).*pmf)(c1(PyTuple_GET_ITEM(args, 1)), c2(PyTuple_GET_ITEM(args, 2)), c3(PyTuple_GET_ITEM(args, 3)), c4(PyTuple_GET_ITEM(args, 4)), c5(PyTuple_GET_ITEM(args, 5)));
        
        return policies.postcall(args, detail::none());
    }

#  endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

    template <class P>
    static PyObject* call(R (*pf)(), PyObject*, PyObject*, P const& policies)
    {
        (*pf)();
        
        return policies.postcall(args, detail::none());
    }
    template <class P, class A0>
    static PyObject* call(R (*pf)(A0), PyObject* args, PyObject*, P const& policies)
    {
        // check that each of the arguments is convertible
        from_python<A0> c0(PyTuple_GET_ITEM(args, 0));
        if (!c0.convertible()) return 0;
        
        if (!policies.precall(args)) return 0;
        
        (*pf)(c0(PyTuple_GET_ITEM(args, 0)));
        
        return policies.postcall(args, detail::none());
    }
    template <class P, class A0, class A1>
    static PyObject* call(R (*pf)(A0, A1), PyObject* args, PyObject*, P const& policies)
    {
        // check that each of the arguments is convertible
        from_python<A0> c0(PyTuple_GET_ITEM(args, 0));
        if (!c0.convertible()) return 0;
        from_python<A1> c1(PyTuple_GET_ITEM(args, 1));
        if (!c1.convertible()) return 0;
        
        if (!policies.precall(args)) return 0;
        
        (*pf)(c0(PyTuple_GET_ITEM(args, 0)), c1(PyTuple_GET_ITEM(args, 1)));
        
        return policies.postcall(args, detail::none());
    }
    template <class P, class A0, class A1, class A2>
    static PyObject* call(R (*pf)(A0, A1, A2), PyObject* args, PyObject*, P const& policies)
    {
        // check that each of the arguments is convertible
        from_python<A0> c0(PyTuple_GET_ITEM(args, 0));
        if (!c0.convertible()) return 0;
        from_python<A1> c1(PyTuple_GET_ITEM(args, 1));
        if (!c1.convertible()) return 0;
        from_python<A2> c2(PyTuple_GET_ITEM(args, 2));
        if (!c2.convertible()) return 0;
        
        if (!policies.precall(args)) return 0;
        
        (*pf)(c0(PyTuple_GET_ITEM(args, 0)), c1(PyTuple_GET_ITEM(args, 1)), c2(PyTuple_GET_ITEM(args, 2)));
        
        return policies.postcall(args, detail::none());
    }
    template <class P, class A0, class A1, class A2, class A3>
    static PyObject* call(R (*pf)(A0, A1, A2, A3), PyObject* args, PyObject*, P const& policies)
    {
        // check that each of the arguments is convertible
        from_python<A0> c0(PyTuple_GET_ITEM(args, 0));
        if (!c0.convertible()) return 0;
        from_python<A1> c1(PyTuple_GET_ITEM(args, 1));
        if (!c1.convertible()) return 0;
        from_python<A2> c2(PyTuple_GET_ITEM(args, 2));
        if (!c2.convertible()) return 0;
        from_python<A3> c3(PyTuple_GET_ITEM(args, 3));
        if (!c3.convertible()) return 0;
        
        if (!policies.precall(args)) return 0;
        
        (*pf)(c0(PyTuple_GET_ITEM(args, 0)), c1(PyTuple_GET_ITEM(args, 1)), c2(PyTuple_GET_ITEM(args, 2)), c3(PyTuple_GET_ITEM(args, 3)));
        
        return policies.postcall(args, detail::none());
    }
    template <class P, class A0, class A1, class A2, class A3, class A4>
    static PyObject* call(R (*pf)(A0, A1, A2, A3, A4), PyObject* args, PyObject*, P const& policies)
    {
        // check that each of the arguments is convertible
        from_python<A0> c0(PyTuple_GET_ITEM(args, 0));
        if (!c0.convertible()) return 0;
        from_python<A1> c1(PyTuple_GET_ITEM(args, 1));
        if (!c1.convertible()) return 0;
        from_python<A2> c2(PyTuple_GET_ITEM(args, 2));
        if (!c2.convertible()) return 0;
        from_python<A3> c3(PyTuple_GET_ITEM(args, 3));
        if (!c3.convertible()) return 0;
        from_python<A4> c4(PyTuple_GET_ITEM(args, 4));
        if (!c4.convertible()) return 0;
        
        if (!policies.precall(args)) return 0;
        
        (*pf)(c0(PyTuple_GET_ITEM(args, 0)), c1(PyTuple_GET_ITEM(args, 1)), c2(PyTuple_GET_ITEM(args, 2)), c3(PyTuple_GET_ITEM(args, 3)), c4(PyTuple_GET_ITEM(args, 4)));
        
        return policies.postcall(args, detail::none());
    }
    template <class P, class A0, class A1, class A2, class A3, class A4, class A5>
    static PyObject* call(R (*pf)(A0, A1, A2, A3, A4, A5), PyObject* args, PyObject*, P const& policies)
    {
        // check that each of the arguments is convertible
        from_python<A0> c0(PyTuple_GET_ITEM(args, 0));
        if (!c0.convertible()) return 0;
        from_python<A1> c1(PyTuple_GET_ITEM(args, 1));
        if (!c1.convertible()) return 0;
        from_python<A2> c2(PyTuple_GET_ITEM(args, 2));
        if (!c2.convertible()) return 0;
        from_python<A3> c3(PyTuple_GET_ITEM(args, 3));
        if (!c3.convertible()) return 0;
        from_python<A4> c4(PyTuple_GET_ITEM(args, 4));
        if (!c4.convertible()) return 0;
        from_python<A5> c5(PyTuple_GET_ITEM(args, 5));
        if (!c5.convertible()) return 0;
        
        if (!policies.precall(args)) return 0;
        
        (*pf)(c0(PyTuple_GET_ITEM(args, 0)), c1(PyTuple_GET_ITEM(args, 1)), c2(PyTuple_GET_ITEM(args, 2)), c3(PyTuple_GET_ITEM(args, 3)), c4(PyTuple_GET_ITEM(args, 4)), c5(PyTuple_GET_ITEM(args, 5)));
        
        return policies.postcall(args, detail::none());
    }
};

}}} // namespace boost::python::detail

#endif // RETURNING_DWA20011201_HPP

