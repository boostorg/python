// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef BUILTIN_CONVERTERS_DWA2002124_HPP
# define BUILTIN_CONVERTERS_DWA2002124_HPP
# include <boost/python/detail/wrap_python.hpp>
# include <boost/python/detail/none.hpp>
# include <boost/python/reference.hpp>
# include <string>
# include <complex>

namespace boost { namespace python {

// Provide specializations of to_python_value
template <class T> struct to_python_value;

namespace detail
{
  struct builtin_to_python
  {
      static bool convertible() { return true; }
  };
}

namespace converter
{
  template <class T> struct callback_to_python;
  BOOST_PYTHON_DECL PyObject* do_call_to_python(char);
  BOOST_PYTHON_DECL PyObject* do_call_to_python(char const*);
  BOOST_PYTHON_DECL PyObject* do_call_to_python(PyObject*);
  BOOST_PYTHON_DECL PyObject* do_callback_to_python(PyObject*);
}

# define BOOST_PYTHON_CALL_TO_PYTHON_BY_VALUE(T, expr)   \
    template <> struct to_python_value<T&>          \
        : detail::builtin_to_python                 \
    {                                               \
        PyObject* operator()(T const& x) const      \
        {                                           \
            return (expr);                          \
        }                                           \
    };                                              \
    template <> struct to_python_value<T const&>    \
        : detail::builtin_to_python                 \
    {                                               \
        PyObject* operator()(T const& x) const      \
        {                                           \
            return (expr);                          \
        }                                           \
    };

# define BOOST_PYTHON_CALLBACK_TO_PYTHON_BY_VALUE(T, expr)   \
    namespace converter                             \
    {                                               \
      template <> struct callback_to_python< T >    \
      {                                             \
          callback_to_python(T const& x)            \
            : m_held(expr) {}                       \
          PyObject* get() const                     \
            { return m_held.get(); }                \
       private:                                     \
          ref m_held;                               \
      };                                            \
    } 

# define BOOST_PYTHON_TO_PYTHON_BY_VALUE(T, expr)   \
        BOOST_PYTHON_CALL_TO_PYTHON_BY_VALUE(T,expr) \
        BOOST_PYTHON_CALLBACK_TO_PYTHON_BY_VALUE(T,expr)

# define BOOST_PYTHON_TO_INT(T)                                         \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(signed T, PyInt_FromLong(x))        \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(unsigned T, PyInt_FromLong(x))

BOOST_PYTHON_TO_PYTHON_BY_VALUE(bool, PyInt_FromLong(x))
BOOST_PYTHON_TO_INT(char)
BOOST_PYTHON_TO_INT(short)
BOOST_PYTHON_TO_INT(int)
BOOST_PYTHON_TO_INT(long)
# undef BOOST_TO_PYTHON_INT

BOOST_PYTHON_TO_PYTHON_BY_VALUE(char, converter::do_call_to_python(x))
BOOST_PYTHON_TO_PYTHON_BY_VALUE(char const*, converter::do_call_to_python(x))
BOOST_PYTHON_TO_PYTHON_BY_VALUE(std::string, PyString_FromString(x.c_str()))
BOOST_PYTHON_TO_PYTHON_BY_VALUE(float, PyFloat_FromDouble(x))
BOOST_PYTHON_TO_PYTHON_BY_VALUE(double, PyFloat_FromDouble(x))
BOOST_PYTHON_TO_PYTHON_BY_VALUE(long double, PyFloat_FromDouble(x))
BOOST_PYTHON_CALL_TO_PYTHON_BY_VALUE(PyObject*, converter::do_call_to_python(x))
BOOST_PYTHON_CALLBACK_TO_PYTHON_BY_VALUE(PyObject*, converter::do_callback_to_python(x))
BOOST_PYTHON_TO_PYTHON_BY_VALUE(std::complex<float>, PyComplex_FromDoubles(x.real(), x.imag()))
BOOST_PYTHON_TO_PYTHON_BY_VALUE(std::complex<double>, PyComplex_FromDoubles(x.real(), x.imag()))
BOOST_PYTHON_TO_PYTHON_BY_VALUE(std::complex<long double>, PyComplex_FromDoubles(x.real(), x.imag()))

namespace converter
{ 

  void initialize_builtin_converters();

}

}} // namespace boost::python::converter

#endif // BUILTIN_CONVERTERS_DWA2002124_HPP
