//  (C) Copyright David Abrahams 2000. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
//  The author gratefully acknowleges the support of Dragon Systems, Inc., in
//  producing this work.

#include "py.h"
#include <boost/config.hpp>
#include <typeinfo>
#ifndef BOOST_NO_LIMITS
# include <boost/cast.hpp>
#endif

namespace py {

void expect_and_absorb_non_null(PyObject* p)
{
    Py_XDECREF(expect_non_null(p));
}

// IMPORTANT: this function may only be called from within a catch block!
void handle_exception()
{
    try {
        // re-toss the current exception so we can find out what type it is.
        // NOTE: a heinous bug in MSVC6 causes exception objects re-thrown in
        // this way to be double-destroyed. Thus, you must only use objects that
        // can tolerate double-destruction with that compiler. Metrowerks
        // Codewarrior doesn't suffer from this problem.
        throw;
    }
    catch(const py::ErrorAlreadySet&)
    {
        // The python error reporting has already been handled.
    }
    catch(const std::bad_alloc&)
    {
        PyErr_NoMemory();
    }
    catch(const std::exception& x)
    {
        PyErr_SetString(PyExc_RuntimeError, x.what());
    }
    catch(...)
    {
        PyErr_SetString(PyExc_RuntimeError, "unidentifiable C++ exception");
    }
}

#ifdef PY_NO_INLINE_FRIENDS_IN_NAMESPACE
}
#endif

long from_python(PyObject* p, py::Type<long>)
{
    // Why am I clearing the error here before trying to convert? I know there's a reason...
    long result;
    {
//        py::SuspendError suspended_error(py::SuspendError::discard_old_error);
        result = PyInt_AsLong(p);
        if (PyErr_Occurred())
            throw py::ArgumentError();
//        suspended_error.throw_if_error();
    }
    return result;
}

double from_python(PyObject* p, py::Type<double>)
{
    // Why am I clearing the error here before trying to convert? I know there's a reason...
    double result;
    {
//        py::SuspendError suspended_error(py::SuspendError::discard_old_error);
        result = PyFloat_AsDouble(p);
        if (PyErr_Occurred())
            throw py::ArgumentError();
//        suspended_error.throw_if_error();
    }
    return result;
}

template <class T>
T integer_from_python(PyObject* p, py::Type<T>)
{
    const long long_result = from_python(p, py::Type<long>());

#ifndef BOOST_NO_LIMITS
    try
    {
        return boost::numeric_cast<T>(long_result);
    }
    catch(const boost::bad_numeric_cast&)
#else
    if (static_cast<T>(long_result) == long_result)
    {
        return static_cast<T>(long_result);
    }
    else
#endif
    {
        char buffer[256];
        const char message[] = "%ld out of range for %s";
        sprintf(buffer, message, long_result, typeid(T).name());
        PyErr_SetString(PyExc_ValueError, buffer);
        throw py::ArgumentError();
    }
#if defined(__MWERKS__) && __MWERKS__ < 0x6000
    return 0; // Not smart enough to know that the catch clause always rethrows
#endif
}

template <class T>
PyObject* integer_to_python(T value)
{
    long value_as_long;

#ifndef BOOST_NO_LIMITS
    try
    {
        value_as_long = boost::numeric_cast<long>(value);
    }
    catch(const boost::bad_numeric_cast&)
#else
    value_as_long = static_cast<long>(value);
    if (value_as_long != value)
#endif
    {
        const char message[] = "value out of range for Python int";
        PyErr_SetString(PyExc_ValueError, message);
        throw py::ErrorAlreadySet();
    }
    
    return to_python(value_as_long);
}

int from_python(PyObject* p, py::Type<int> type)
{
    return integer_from_python(p, type);
}

PyObject* to_python(unsigned int i)
{
	return integer_to_python(i);
}

unsigned int from_python(PyObject* p, py::Type<unsigned int> type)
{
    return integer_from_python(p, type);
}

short from_python(PyObject* p, py::Type<short> type)
{
    return integer_from_python(p, type);
}

float from_python(PyObject* p, py::Type<float>)
{
    return static_cast<float>(from_python(p, py::Type<double>()));
}

PyObject* to_python(unsigned short i)
{
	return integer_to_python(i);
}

unsigned short from_python(PyObject* p, py::Type<unsigned short> type)
{
    return integer_from_python(p, type);
}

PyObject* to_python(unsigned long x)
{
    return integer_to_python(x);
}

unsigned long from_python(PyObject* p, py::Type<unsigned long> type)
{
    return integer_from_python(p, type);
}

void from_python(PyObject* p, py::Type<void>)
{
    if (p != Py_None) {
        PyErr_SetString(PyExc_TypeError, "expected argument of type None");
        throw py::ArgumentError();
    }
}

const char* from_python(PyObject* p, py::Type<const char*>)
{
    const char* s = PyString_AsString(p);
    if (!s) throw py::ArgumentError();
    return s;
}

PyObject* to_python(const std::string& s)
{
	return PyString_FromString(s.c_str());
}

std::string from_python(PyObject* p, py::Type<std::string>)
{
    return std::string(from_python(p, py::Type<const char*>()));
}

bool from_python(PyObject* p, py::Type<bool>)
{
    int value = from_python(p, py::Type<int>());
    if (value == 0)
        return false;
    return true;
}

#ifdef PY_NO_INLINE_FRIENDS_IN_NAMESPACE
namespace py {
#endif

}

