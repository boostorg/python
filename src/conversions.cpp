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

#include <boost/python/conversions.hpp>
#include <typeinfo>
#include <exception>
#ifndef BOOST_NO_LIMITS
# include <boost/cast.hpp>
#endif

namespace boost { namespace python {

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
    catch(const boost::python::error_already_set&)
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

namespace detail {

  void expect_complex(PyObject* p)
  {
      if (!PyComplex_Check(p))
      {
          PyErr_SetString(PyExc_TypeError, "expected a complex number");
          throw boost::python::argument_error();
      }
  }

} // namespace boost::python::detail

}} // namespace boost::python

BOOST_PYTHON_BEGIN_CONVERSION_NAMESPACE

long from_python(PyObject* p, boost::python::type<long>)
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

double from_python(PyObject* p, boost::python::type<double>)
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
        throw boost::python::argument_error();
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
        throw boost::python::error_already_set();
    }
    
    return to_python(value_as_long, boost::python::lookup_tag());
}

int from_python(PyObject* p, boost::python::type<int> type)
{
    return integer_from_python(p, type);
}

PyObject* to_python(unsigned int i, boost::python::lookup_tag)
{
    return integer_to_python(i);
}

unsigned int from_python(PyObject* p, boost::python::type<unsigned int> type)
{
    return integer_from_python(p, type);
}

short from_python(PyObject* p, boost::python::type<short> type)
{
    return integer_from_python(p, type);
}

float from_python(PyObject* p, boost::python::type<float>)
{
    return static_cast<float>(from_python(p, boost::python::type<double>()));
}

PyObject* to_python(unsigned short i, boost::python::lookup_tag)
{
    return integer_to_python(i);
}

unsigned short from_python(PyObject* p, boost::python::type<unsigned short> type)
{
    return integer_from_python(p, type);
}

PyObject* to_python(char c, boost::python::lookup_tag)
{
    if (c == '\0') return PyString_FromString("");
    return PyString_FromStringAndSize(&c, 1);
}

char from_python(PyObject* p, boost::python::type<char>)
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

PyObject* to_python(unsigned char i, boost::python::lookup_tag)
{
    return integer_to_python(i);
}

unsigned char from_python(PyObject* p, boost::python::type<unsigned char> type)
{
    return integer_from_python(p, type);
}

PyObject* to_python(signed char i, boost::python::lookup_tag)
{
    return integer_to_python(i);
}

signed char from_python(PyObject* p, boost::python::type<signed char> type)
{
    return integer_from_python(p, type);
}

PyObject* to_python(unsigned long x, boost::python::lookup_tag)
{
    return integer_to_python(x);
}

unsigned long from_python(PyObject* p, boost::python::type<unsigned long> type)
{
    return integer_from_python(p, type);
}

void from_python(PyObject* p, boost::python::type<void>)
{
    if (p != Py_None) {
        PyErr_SetString(PyExc_TypeError, "expected argument of type None");
        throw boost::python::argument_error();
    }
}

const char* from_python(PyObject* p, boost::python::type<const char*>)
{
    const char* s = PyString_AsString(p);
    if (!s)
        throw boost::python::argument_error();
    return s;
}

PyObject* to_python(const std::string& s, boost::python::lookup_tag)
{
    return PyString_FromStringAndSize(s.data(), s.size());
}

std::string from_python(PyObject* p, boost::python::type<std::string>)
{
    if (! PyString_Check(p)) {
        PyErr_SetString(PyExc_TypeError, "expected a string");
        throw boost::python::argument_error();
    }
    return std::string(PyString_AsString(p), PyString_Size(p));
}

bool from_python(PyObject* p, boost::python::type<bool>)
{
    int value = from_python(p, boost::python::type<int>());
    if (value == 0)
        return false;
    return true;
}

#ifdef BOOST_MSVC6_OR_EARLIER
// An optimizer bug prevents these from being inlined.
PyObject* to_python(double d, boost::python::lookup_tag)
{
    return PyFloat_FromDouble(d);
}

PyObject* to_python(float f, boost::python::lookup_tag)
{
    return PyFloat_FromDouble(f);
}
#endif // BOOST_MSVC6_OR_EARLIER

BOOST_PYTHON_END_CONVERSION_NAMESPACE

