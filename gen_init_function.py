from gen_function import *
import string

def gen_init_function(args):

    return (
"""//  (C) Copyright David Abrahams 2000. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
//  The author gratefully acknowleges the support of Dragon Systems, Inc., in
//  producing this work.
//
//  This file was generated for %d-argument constructors by gen_init_function.py

#ifndef INIT_FUNCTION_DWA052000_H_
# define INIT_FUNCTION_DWA052000_H_

# include "pyconfig.h"
# include "functions.h"
# include "signatures.h"
# include <typeinfo>

namespace py {

namespace detail {

#ifdef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

  // parameter_traits - so far, this is a way to pass a const T& when we can be
  // sure T is not a reference type, and a raw T otherwise. This should be
  // rolled into boost::call_traits.
  template <bool is_ref>
  struct const_ref_selector
  {
      template <class T>
      struct const_ref
      {
          typedef const T& type;
      };
  };

  template <>
  struct const_ref_selector<true>
  {
      template <class T>
      struct const_ref
      {
          typedef T type;
      };
  };

# ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable: 4181)
# endif // BOOST_MSVC
  template <class T>
  struct parameter_traits
  {
   private:
      typedef const_ref_selector<boost::is_reference<T>::value> selector;
   public:
      typedef typename selector::const_ref<T>::type const_reference;
  };
# ifdef BOOST_MSVC
#  pragma warning(pop)
# endif // BOOST_MSVC

#else
  template <class T>
  struct parameter_traits
  {
      typedef const T& const_reference;
  };

  template <class T>
  struct parameter_traits<T&>
  {
      typedef T& const_reference;
  };
#endif

  template <>
  struct parameter_traits<void>
  {
      typedef void const_reference;
  };

  template <class T>
  class reference_parameter
  {
      typedef typename parameter_traits<T>::const_reference const_reference;
   public:
      reference_parameter(const_reference value)
          : value(value) {}
      operator const_reference() { return value; }
   private:
      const_reference value;
  };
}

class ExtensionInstance;
class InstanceHolderBase;

class Init;
"""
        + gen_functions('template <class T%(, class A%n%)> struct Init%x;\n', args)
        + """
template <class T>
struct InitFunction
{
""" + gen_functions("""%{
    template <%(class A%n%:, %)>
%}    static Init* create(Signature%x%{<%(A%n%:, %)>%}) {
        return new Init%x<T%(,
                       detail::parameter_traits<A%n>::const_reference%)>;
    }
""", args)+"""};

class Init : public Function
{
private: // override Function hook
    PyObject* do_call(PyObject* args, PyObject* keywords) const;
private:
    virtual InstanceHolderBase* create_holder(ExtensionInstance* self, PyObject* tail_args, PyObject* keywords) const = 0;
};
""" + gen_functions("""

template <class T%(, class A%n%)>
struct Init%x : Init
{
    virtual InstanceHolderBase* create_holder(ExtensionInstance* self, PyObject* args, PyObject* /*keywords*/) const
    {
        %(PyObject* a%n;
        %)if (!PyArg_ParseTuple(args, const_cast<char*>("%(O%)")%(, &a%n%)))
            throw ArgumentError();
        return new T(self%(,
            py::detail::reference_parameter<A%n>(from_python(a%n, Type<A%n>()))%)
            );
    }
    const char* description() const
        { return typeid(void (*)(T&%(, A%n%%))).name(); }
};""", args) + """

}

#endif // INIT_FUNCTION_DWA052000_H_
""")

if __name__ == '__main__':
    import sys

    if len(sys.argv) == 1:
        args = 5
    else:
        args = int(sys.argv[1])

    print gen_init_function(args)

