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
//  This file was generated for %d-argument constructors by gen_init_function.python

#ifndef INIT_FUNCTION_DWA052000_H_
# define INIT_FUNCTION_DWA052000_H_

# include "pyconfig.h"
# include "functions.h"
# include "signatures.h"
# include <typeinfo>

namespace python {

namespace detail {

  // parameter_traits - so far, this is a way to pass a const T& when we can be
  // sure T is not a reference type, and a raw T otherwise. This should be
  // rolled into boost::call_traits. Ordinarily, parameter_traits would be
  // written:
  //
  //    template <class T> struct parameter_traits
  //    {
  //        typedef const T& const_reference;
  //    };
  //
  //    template <class T> struct parameter_traits<T&>
  //    {
  //        typedef T& const_reference;
  //    };
  //
  //    template <> struct parameter_traits<void>
  //    {
  //        typedef void const_reference;
  //    };
  //
  // ...but since we can't partially specialize on reference types, we need this
  // long-winded but equivalent incantation.

  // const_ref_selector -- an implementation detail of parameter_traits (below). This uses
  // the usual "poor man's partial specialization" hack for MSVC. 
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
      typedef typename selector::template const_ref<T>::type const_reference;
  };
# ifdef BOOST_MSVC
#  pragma warning(pop)
# endif // BOOST_MSVC

  // Full spcialization for void
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

class extension_instance;
class instance_holder_base;

class init;
"""
        + gen_functions('template <class T%(, class A%n%)> struct init%x;\n', args)
        + """
template <class T>
struct init_function
{
""" + gen_functions("""%{
    template <%(class A%n%:, %)>
%}    static init* create(signature%x%{<%(A%n%:, %)>%}) {
        return new init%x<T%(,
                       detail::parameter_traits<A%n>::const_reference%)>;
    }
""", args)+"""};

class init : public function
{
private: // override function hook
    PyObject* do_call(PyObject* args, PyObject* keywords) const;
private:
    virtual instance_holder_base* create_holder(extension_instance* self, PyObject* tail_args, PyObject* keywords) const = 0;
    string description_as_string() const;
    string argument_types_as_string(tuple args) const;
};
""" + gen_functions("""

template <class T%(, class A%n%)>
struct init%x : init
{
    virtual instance_holder_base* create_holder(extension_instance* self, PyObject* args, PyObject* /*keywords*/) const
    {
        %(PyObject* a%n;
        %)if (!PyArg_ParseTuple(args, const_cast<char*>("%(O%)")%(, &a%n%)))
            throw argument_error();
        return new T(self%(,
            python::detail::reference_parameter<A%n>(from_python(a%n, type<A%n>()))%)
            );
    }
    
    PyObject* description() const
    { 
        return function_signature(get_python_type_name(python::type<T>())%(, 
                                  get_python_type_name(python::type<A%n>())%)); 
    }
    
    string function_name() const
    { 
        string result(get_python_type_name(python::type<T>()));
        result += ".__init__";
        return result; 
    }
};""", args) + """

}} // namespace python::detail

#endif // INIT_FUNCTION_DWA052000_H_
""")

if __name__ == '__main__':
    import sys

    if len(sys.argv) == 1:
        args = 5
    else:
        args = int(sys.argv[1])

    print gen_init_function(args)

