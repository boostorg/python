//  (C) Copyright David Abrahams 2001,2002. Permission to copy, use, modify, sell
//  and distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
//  This work was funded in part by Lawrence Berkeley National Labs
//
//  This file generated for 5-argument member functions and 6-argument free
//  functions by gen_returning.py

#ifndef RETURNING_DWA20020228_HPP
# define RETURNING_DWA20020228_HPP

# include <boost/config.hpp>
# include <boost/python/converter/callback.hpp>
# include <boost/python/detail/none.hpp>
# include <boost/python/reference.hpp>

namespace boost { namespace python {

// Calling C++ from Python
template <class R>
struct returning
{
    static R call(char const* name, PyObject* self)
    {
        converter::callback_from_python<R> cr;
        return cr(PyEval_CallMethod(
                      self
                      , const_cast<char*>(name)
                      , const_cast<char*>("()")
                      ));
    }
    
    static R call(PyObject* self)
    {
        converter::callback_from_python<R> cr;
        return cr(PyEval_CallFunction(self, const_cast<char*>("()")
                      ));
    }

    template <class A1>
    static R call_method(PyObject* self, const char* name, A1 const& a1)
    {
        converter::callback_from_python<R> cr;
        return cr(PyEval_CallMethod(
                      self
                      , const_cast<char*>(name)
                      , const_cast<char*>("(O)")
                      , converter::callback_to_python<A1>(a1).get()
                      ));
    }

    template <class A1>
    static R call(PyObject* self, A1 const& a1)
    {
        converter::callback_from_python<R> cr;
        return cr(PyEval_CallFunction(
                      self
                      , const_cast<char*>("(O)")
                      , converter::callback_to_python<A1>(a1).get()
                      ));
    }

    template <class A1, class A2>
    static R call_method(PyObject* self, const char* name, A1 const& a1, A2 const& a2)
    {
        converter::callback_from_python<R> cr;
        return cr(PyEval_CallMethod(
                      self
                      , const_cast<char*>(name)
                      , const_cast<char*>("(O)")
                      , converter::callback_to_python<A1>(a1).get()
                      , converter::callback_to_python<A2>(a2).get()
                      ));
    }

    template <class A1, class A2>
    static R call(PyObject* self, A1 const& a1, A2 const& a2)
    {
        converter::callback_from_python<R> cr;
        return cr(PyEval_CallFunction(
                      self
                      , const_cast<char*>("(O)")
                      , converter::callback_to_python<A1>(a1).get()
                      , converter::callback_to_python<A2>(a2).get()
                      ));
    }

};
                           
template <>
struct returning<void>
{
    typedef void R;
    static R call(char const* name, PyObject* self)
    {
        ref x(PyEval_CallMethod(
                      self
                      , const_cast<char*>(name)
                      , const_cast<char*>("()")
                      ));
    }
    
    static R call(PyObject* self)
    {
        ref x(PyEval_CallFunction(self, const_cast<char*>("()")
                      ));
    }

    template <class A1>
    static R call_method(PyObject* self, const char* name, A1 const& a1)
    {
        ref x(PyEval_CallMethod(
                      self
                      , const_cast<char*>(name)
                      , const_cast<char*>("(O)")
                      , converter::callback_to_python<A1>(a1).get()
                      ));
    }

    template <class A1>
    static R call(PyObject* self, A1 const& a1)
    {
        ref x(PyEval_CallFunction(
                      self
                      , const_cast<char*>("(O)")
                      , converter::callback_to_python<A1>(a1).get()
                      ));
    }

    template <class A1, class A2>
    static R call_method(PyObject* self, const char* name, A1 const& a1, A2 const& a2)
    {
        ref x(PyEval_CallMethod(
                      self
                      , const_cast<char*>(name)
                      , const_cast<char*>("(O)")
                      , converter::callback_to_python<A1>(a1).get()
                      , converter::callback_to_python<A2>(a2).get()
                      ));
    }

    template <class A1, class A2>
    static R call(PyObject* self, A1 const& a1, A2 const& a2)
    {
        ref x(PyEval_CallFunction(
                      self
                      , const_cast<char*>("(O)")
                      , converter::callback_to_python<A1>(a1).get()
                      , converter::callback_to_python<A2>(a2).get()
                      ));
    }
};

}} // namespace boost::python

#endif // RETURNING_DWA20020228_HPP

