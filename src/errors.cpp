// Copyright David Abrahams 2001. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.

#ifndef BOOST_PYTHON_SOURCE
# define BOOST_PYTHON_SOURCE
#endif

#include <boost/python/errors.hpp>
#include <boost/cast.hpp>

namespace boost { namespace python {

// IMPORTANT: this function may only be called from within a catch block!
BOOST_PYTHON_DECL bool handle_exception_impl(function0<void> f)
{
    try
    {
        f();
        return false;
    }
    catch(const boost::python::error_already_set&)
    {
        // The python error reporting has already been handled.
    }
    catch(const std::bad_alloc&)
    {
        PyErr_NoMemory();
    }
    catch(const bad_numeric_cast& x)
    {
        PyErr_SetString(PyExc_OverflowError, x.what());
    }
    catch(const std::exception& x)
    {
        PyErr_SetString(PyExc_RuntimeError, x.what());
    }
    catch(...)
    {
        PyErr_SetString(PyExc_RuntimeError, "unidentifiable C++ exception");
    }
    return true;
}

void BOOST_PYTHON_DECL throw_argument_error()
{
    throw argument_error();
}

void BOOST_PYTHON_DECL throw_error_already_set()
{
    throw error_already_set();
}

namespace detail {

  BOOST_PYTHON_DECL void expect_complex(PyObject* p)
  {
      if (!PyComplex_Check(p))
      {
          PyErr_SetString(PyExc_TypeError, "expected a complex number");
          boost::python::throw_argument_error();
      }
  }

// needed by void_adaptor (see void_adaptor.hpp)
BOOST_PYTHON_DECL PyObject arbitrary_object = { 0 };


} // namespace boost::python::detail

}} // namespace boost::python


