//  (C) Copyright David Abrahams 2000. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
//  The author gratefully acknowleges the support of Dragon Systems, Inc., in
//  producing this work.
//
// Revision History:
// 05 Apr 01  added: from_python std::string type checking (rwgk)
// 12 Mar 01  Python 1.5.2 fixes (Ralf W. Grosse-Kunstleve)
// 11 Mar 01  std::string *MAY* include nulls (Alex Martelli)
// 04 Mar 01  std::complex<> fixes for MSVC (Dave Abrahams)
// 03 Mar 01  added: converters for [plain] char (Ralf W. Grosse-Kunstleve)

#define BOOST_PYTHON_SOURCE

#include <boost/python/conversions.hpp>
#include <boost/function.hpp>
#include <typeinfo>
#include <exception>
#include <boost/cast.hpp>

BOOST_PYTHON_BEGIN_CONVERSION_NAMESPACE

BOOST_PYTHON_DECL long from_python(PyObject* p, boost::python::type<long>)
{
    // Why am I clearing the error here before trying to convert? I know there's a reason...
    long result;
    {
        result = PyInt_AsLong(p);
        if (PyErr_Occurred())
            throw boost::python::argument_error();
    }
    return result;
}

BOOST_PYTHON_DECL double from_python(PyObject* p, boost::python::type<double>)
{
    double result;
    {
        result = PyFloat_AsDouble(p);
        if (PyErr_Occurred())
            throw boost::python::argument_error();
    }
    return result;
}

template <class T>
T integer_from_python(PyObject* p, boost::python::type<T>)
{
    const long long_result = from_python(p, boost::python::type<long>());

    try
    {
        return boost::numeric_cast<T>(long_result);
    }
    catch(const boost::bad_numeric_cast&)
    {
        char buffer[256];
        const char message[] = "%ld out of range for %s";
        sprintf(buffer, message, long_result, typeid(T).name());
        PyErr_SetString(PyExc_ValueError, buffer);
        throw boost::python::argument_error();
    }
#if defined(__MWERKS__) && __MWERKS__ <= 0x2407
    return 0; // Not smart enough to know that the catch clause always rethrows
#endif
}

template <class T>
PyObject* integer_to_python(T value)
{
    long value_as_long;

    try
    {
        value_as_long = boost::numeric_cast<long>(value);
    }
    catch(const boost::bad_numeric_cast&)
    {
        const char message[] = "value out of range for Python int";
        PyErr_SetString(PyExc_ValueError, message);
        throw boost::python::error_already_set();
    }
    
    return to_python(value_as_long);
}

BOOST_PYTHON_DECL int from_python(PyObject* p, boost::python::type<int> type)
{
    return integer_from_python(p, type);
}

BOOST_PYTHON_DECL PyObject* to_python(unsigned int i)
{
    return integer_to_python(i);
}

BOOST_PYTHON_DECL unsigned int from_python(PyObject* p, boost::python::type<unsigned int> type)
{
    return integer_from_python(p, type);
}

BOOST_PYTHON_DECL short from_python(PyObject* p, boost::python::type<short> type)
{
    return integer_from_python(p, type);
}

BOOST_PYTHON_DECL float from_python(PyObject* p, boost::python::type<float>)
{
    return static_cast<float>(from_python(p, boost::python::type<double>()));
}

BOOST_PYTHON_DECL PyObject* to_python(unsigned short i)
{
    return integer_to_python(i);
}

BOOST_PYTHON_DECL unsigned short from_python(PyObject* p, boost::python::type<unsigned short> type)
{
    return integer_from_python(p, type);
}

BOOST_PYTHON_DECL PyObject* to_python(char c)
{
    if (c == '\0') return PyString_FromString("");
    return PyString_FromStringAndSize(&c, 1);
}

BOOST_PYTHON_DECL char from_python(PyObject* p, boost::python::type<char>)
{
    int l = -1;
    if (PyString_Check(p)) l = PyString_Size(p);
    if (l < 0 || l > 1) {
        PyErr_SetString(PyExc_TypeError, "expected string of length 0 or 1");
        throw boost::python::argument_error();
    }
    if (l == 0) return '\0';
    return PyString_AsString(p)[0];
}

BOOST_PYTHON_DECL PyObject* to_python(unsigned char i)
{
    return integer_to_python(i);
}

BOOST_PYTHON_DECL unsigned char from_python(PyObject* p, boost::python::type<unsigned char> type)
{
    return integer_from_python(p, type);
}

BOOST_PYTHON_DECL PyObject* to_python(signed char i)
{
    return integer_to_python(i);
}

BOOST_PYTHON_DECL signed char from_python(PyObject* p, boost::python::type<signed char> type)
{
    return integer_from_python(p, type);
}

BOOST_PYTHON_DECL PyObject* to_python(unsigned long x)
{
    return integer_to_python(x);
}

BOOST_PYTHON_DECL unsigned long from_python(PyObject* p, boost::python::type<unsigned long> type)
{
    return integer_from_python(p, type);
}

BOOST_PYTHON_DECL void from_python(PyObject* p, boost::python::type<void>)
{
    if (p != Py_None) {
        PyErr_SetString(PyExc_TypeError, "expected argument of type None");
        throw boost::python::argument_error();
    }
}

BOOST_PYTHON_DECL const char* from_python(PyObject* p, boost::python::type<const char*>)
{
    const char* s = PyString_AsString(p);
    if (!s)
        throw boost::python::argument_error();
    return s;
}

BOOST_PYTHON_DECL PyObject* to_python(const std::string& s)
{
    return PyString_FromStringAndSize(s.data(), s.size());
}

BOOST_PYTHON_DECL std::string from_python(PyObject* p, boost::python::type<std::string>)
{
    if (! PyString_Check(p)) {
        PyErr_SetString(PyExc_TypeError, "expected a string");
        throw boost::python::argument_error();
    }
    return std::string(PyString_AsString(p), PyString_Size(p));
}

BOOST_PYTHON_DECL bool from_python(PyObject* p, boost::python::type<bool>)
{
    int value = from_python(p, boost::python::type<int>());
    if (value == 0)
        return false;
    return true;
}

#ifdef BOOST_MSVC6_OR_EARLIER
// An optimizer bug prevents these from being inlined.
BOOST_PYTHON_DECL PyObject* to_python(double d)
{
    return PyFloat_FromDouble(d);
}

BOOST_PYTHON_DECL PyObject* to_python(float f)
{
    return PyFloat_FromDouble(f);
}
#endif // BOOST_MSVC6_OR_EARLIER

BOOST_PYTHON_END_CONVERSION_NAMESPACE

