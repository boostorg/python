//  (C) Copyright David Abrahams 2000. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
//  The author gratefully acknowleges the support of Dragon Systems, Inc., in
//  producing this work.

#include "py.h"
#include <typeinfo>
#ifndef BOOST_NO_LIMITS
# include <boost/cast.hpp>
#endif

namespace py {

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

} // namespace py

PY_BEGIN_CONVERSION_NAMESPACE

long from_python(PyObject* p, py::Type<long>)
{
    // Why am I clearing the error here before trying to convert? I know there's a reason...
    long result;
    {
        result = PyInt_AsLong(p);
        if (PyErr_Occurred())
            throw py::ArgumentError();
    }
    return result;
}

double from_python(PyObject* p, py::Type<double>)
{
    double result;
    {
        result = PyFloat_AsDouble(p);
        if (PyErr_Occurred())
            throw py::ArgumentError();
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
#if defined(__MWERKS__) && __MWERKS__ <= 0x2400
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

PyObject* to_python(unsigned char i)
{
	return integer_to_python(i);
}

unsigned char from_python(PyObject* p, py::Type<unsigned char> type)
{
    return integer_from_python(p, type);
}

PyObject* to_python(signed char i)
{
	return integer_to_python(i);
}

signed char from_python(PyObject* p, py::Type<signed char> type)
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
    if (!s)
        throw py::ArgumentError();
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

#ifdef PY_MSVC6_OR_EARLIER
// An optimizer bug prevents these from being inlined.
PyObject* to_python(double d)
{
    return PyFloat_FromDouble(d);
}

PyObject* to_python(float f)
{
    return PyFloat_FromDouble(f);
}
#endif // PY_MSVC6_OR_EARLIER

PY_END_CONVERSION_NAMESPACE

