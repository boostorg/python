//  (C) Copyright David Abrahams 2000. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
//  The author gratefully acknowleges the support of Dragon Systems, Inc., in
//  producing this work.

#ifndef ERRORS_DWA052500_H_
# define ERRORS_DWA052500_H_

# include <boost/python/detail/config.hpp>
# include <boost/python/detail/wrap_python.hpp>
# include <boost/function.hpp>

namespace boost { namespace python {

struct error_already_set {};
struct argument_error : error_already_set {};

// Handles exceptions caught just before returning to Python code.
// Returns true iff an exception was caught.
BOOST_PYTHON_DECL bool handle_exception_impl(function0<void>);

template <class T>
bool handle_exception(T f)
{
    return handle_exception_impl(function0<void>(boost::ref(f)));
}

BOOST_PYTHON_DECL PyObject* expect_non_null(PyObject* x);

template <class T>
T* expect_non_null(T* x)
{
    return (T*)expect_non_null((PyObject*)x);
}

}} // namespace boost::python

#endif // ERRORS_DWA052500_H_
