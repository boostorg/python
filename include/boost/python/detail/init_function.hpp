//  (C) Copyright David Abrahams 2001. Permission to copy, use, modify, sell and
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

# include <boost/python/detail/config.hpp>
# include <boost/python/detail/functions.hpp>
# include <boost/python/detail/signatures.hpp>
# include <typeinfo>

namespace boost { namespace python {

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
      enum { is_ref = boost::is_reference<T>::value };
      typedef const_ref_selector<is_ref> selector;
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

  struct reference_parameter_base {};

  template <class T>
  class reference_parameter
      : public reference_parameter_base
  {
   public:
      typedef typename parameter_traits<T>::const_reference const_reference;
      reference_parameter(const_reference value)
          : value(value) {}
      operator const_reference() { return value; }
   private:
      const_reference value;
  };

# ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
  template <class T>
  struct unwrap_parameter
  {
      typedef typename boost::add_reference<T>::type type;
  };

  template <class T>
  struct unwrap_parameter<reference_parameter<T> >
  {
      typedef typename reference_parameter<T>::const_reference type;
  };
# else
  template <bool is_wrapped>
  struct unwrap_parameter_helper
  {
      template <class T>
      struct apply
      {
          typedef typename T::const_reference type;
      };
  };

  template <>
  struct unwrap_parameter_helper<false>
  {
      template <class T>
      struct apply
      {
          typedef typename add_reference<T>::type type;
      };
  };

  template <class T>
  struct unwrap_parameter
  {
      BOOST_STATIC_CONSTANT(
          bool, is_wrapped = (is_base_and_derived<T,reference_parameter_base>::value));
      
      typedef typename unwrap_parameter_helper<
          is_wrapped
      >::template apply<T>::type type;
  };
# endif 
  
class extension_instance;
class instance_holder_base;

class init;
template <class T> struct init0;
template <class T, class A1> struct init1;
template <class T, class A1, class A2> struct init2;
template <class T, class A1, class A2, class A3> struct init3;
template <class T, class A1, class A2, class A3, class A4> struct init4;
template <class T, class A1, class A2, class A3, class A4, class A5> struct init5;
template <class T, class A1, class A2, class A3, class A4, class A5, class A6> struct init6;
template <class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7> struct init7;
template <class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8> struct init8;
template <class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9> struct init9;
template <class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10> struct init10;

template <class T>
struct init_function
{
    static init* create(signature0) {
        return new init0<T>;
    }

    template <class A1>
    static init* create(signature1<A1>) {
        return new init1<T,
                       typename detail::parameter_traits<A1>::const_reference>;
    }

    template <class A1, class A2>
    static init* create(signature2<A1, A2>) {
        return new init2<T,
                       typename detail::parameter_traits<A1>::const_reference,
                       typename detail::parameter_traits<A2>::const_reference>;
    }

    template <class A1, class A2, class A3>
    static init* create(signature3<A1, A2, A3>) {
        return new init3<T,
                       typename detail::parameter_traits<A1>::const_reference,
                       typename detail::parameter_traits<A2>::const_reference,
                       typename detail::parameter_traits<A3>::const_reference>;
    }

    template <class A1, class A2, class A3, class A4>
    static init* create(signature4<A1, A2, A3, A4>) {
        return new init4<T,
                       typename detail::parameter_traits<A1>::const_reference,
                       typename detail::parameter_traits<A2>::const_reference,
                       typename detail::parameter_traits<A3>::const_reference,
                       typename detail::parameter_traits<A4>::const_reference>;
    }

    template <class A1, class A2, class A3, class A4, class A5>
    static init* create(signature5<A1, A2, A3, A4, A5>) {
        return new init5<T,
                       typename detail::parameter_traits<A1>::const_reference,
                       typename detail::parameter_traits<A2>::const_reference,
                       typename detail::parameter_traits<A3>::const_reference,
                       typename detail::parameter_traits<A4>::const_reference,
                       typename detail::parameter_traits<A5>::const_reference>;
    }

    template <class A1, class A2, class A3, class A4, class A5, class A6>
    static init* create(signature6<A1, A2, A3, A4, A5, A6>) {
        return new init6<T,
                       typename detail::parameter_traits<A1>::const_reference,
                       typename detail::parameter_traits<A2>::const_reference,
                       typename detail::parameter_traits<A3>::const_reference,
                       typename detail::parameter_traits<A4>::const_reference,
                       typename detail::parameter_traits<A5>::const_reference,
                       typename detail::parameter_traits<A6>::const_reference>;
    }

    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7>
    static init* create(signature7<A1, A2, A3, A4, A5, A6, A7>) {
        return new init7<T,
                       typename detail::parameter_traits<A1>::const_reference,
                       typename detail::parameter_traits<A2>::const_reference,
                       typename detail::parameter_traits<A3>::const_reference,
                       typename detail::parameter_traits<A4>::const_reference,
                       typename detail::parameter_traits<A5>::const_reference,
                       typename detail::parameter_traits<A6>::const_reference,
                       typename detail::parameter_traits<A7>::const_reference>;
    }

    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
    static init* create(signature8<A1, A2, A3, A4, A5, A6, A7, A8>) {
        return new init8<T,
                       typename detail::parameter_traits<A1>::const_reference,
                       typename detail::parameter_traits<A2>::const_reference,
                       typename detail::parameter_traits<A3>::const_reference,
                       typename detail::parameter_traits<A4>::const_reference,
                       typename detail::parameter_traits<A5>::const_reference,
                       typename detail::parameter_traits<A6>::const_reference,
                       typename detail::parameter_traits<A7>::const_reference,
                       typename detail::parameter_traits<A8>::const_reference>;
    }

    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
    static init* create(signature9<A1, A2, A3, A4, A5, A6, A7, A8, A9>) {
        return new init9<T,
                       typename detail::parameter_traits<A1>::const_reference,
                       typename detail::parameter_traits<A2>::const_reference,
                       typename detail::parameter_traits<A3>::const_reference,
                       typename detail::parameter_traits<A4>::const_reference,
                       typename detail::parameter_traits<A5>::const_reference,
                       typename detail::parameter_traits<A6>::const_reference,
                       typename detail::parameter_traits<A7>::const_reference,
                       typename detail::parameter_traits<A8>::const_reference,
                       typename detail::parameter_traits<A9>::const_reference>;
    }

    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10>
    static init* create(signature10<A1, A2, A3, A4, A5, A6, A7, A8, A9, A10>) {
        return new init10<T,
                       typename detail::parameter_traits<A1>::const_reference,
                       typename detail::parameter_traits<A2>::const_reference,
                       typename detail::parameter_traits<A3>::const_reference,
                       typename detail::parameter_traits<A4>::const_reference,
                       typename detail::parameter_traits<A5>::const_reference,
                       typename detail::parameter_traits<A6>::const_reference,
                       typename detail::parameter_traits<A7>::const_reference,
                       typename detail::parameter_traits<A8>::const_reference,
                       typename detail::parameter_traits<A9>::const_reference,
                       typename detail::parameter_traits<A10>::const_reference>;
    }
};

class BOOST_PYTHON_DECL init : public function
{
private: // override function hook
    PyObject* do_call(PyObject* args, PyObject* keywords) const;
private:
    virtual instance_holder_base* create_holder(extension_instance* self, PyObject* tail_args, PyObject* keywords) const = 0;
};


template <class T>
struct init0 : init
{
    virtual instance_holder_base* create_holder(extension_instance* self, PyObject* args, PyObject* /*keywords*/) const
    {
        if (!PyArg_ParseTuple(args, const_cast<char*>("")))
            throw argument_error();
        return new T(self
            );
    }
    const char* description() const
        { return typeid(void (*)(T&)).name(); }
};

template <class T, class A1>
struct init1 : init
{
    virtual instance_holder_base* create_holder(extension_instance* self, PyObject* args, PyObject* /*keywords*/) const
    {
        PyObject* a1;
        if (!PyArg_ParseTuple(args, const_cast<char*>("O"), &a1))
            throw argument_error();
        return new T(self,
            boost::python::detail::reference_parameter<A1>(from_python(a1, type<A1>()))
            );
    }
    const char* description() const
        { return typeid(void (*)(T&, A1)).name(); }
};

template <class T, class A1, class A2>
struct init2 : init
{
    virtual instance_holder_base* create_holder(extension_instance* self, PyObject* args, PyObject* /*keywords*/) const
    {
        PyObject* a1;
        PyObject* a2;
        if (!PyArg_ParseTuple(args, const_cast<char*>("OO"), &a1, &a2))
            throw argument_error();
        return new T(self,
            boost::python::detail::reference_parameter<A1>(from_python(a1, type<A1>())),
            boost::python::detail::reference_parameter<A2>(from_python(a2, type<A2>()))
            );
    }
    const char* description() const
        { return typeid(void (*)(T&, A1, A2)).name(); }
};

template <class T, class A1, class A2, class A3>
struct init3 : init
{
    virtual instance_holder_base* create_holder(extension_instance* self, PyObject* args, PyObject* /*keywords*/) const
    {
        PyObject* a1;
        PyObject* a2;
        PyObject* a3;
        if (!PyArg_ParseTuple(args, const_cast<char*>("OOO"), &a1, &a2, &a3))
            throw argument_error();
        return new T(self,
            boost::python::detail::reference_parameter<A1>(from_python(a1, type<A1>())),
            boost::python::detail::reference_parameter<A2>(from_python(a2, type<A2>())),
            boost::python::detail::reference_parameter<A3>(from_python(a3, type<A3>()))
            );
    }
    const char* description() const
        { return typeid(void (*)(T&, A1, A2, A3)).name(); }
};

template <class T, class A1, class A2, class A3, class A4>
struct init4 : init
{
    virtual instance_holder_base* create_holder(extension_instance* self, PyObject* args, PyObject* /*keywords*/) const
    {
        PyObject* a1;
        PyObject* a2;
        PyObject* a3;
        PyObject* a4;
        if (!PyArg_ParseTuple(args, const_cast<char*>("OOOO"), &a1, &a2, &a3, &a4))
            throw argument_error();
        return new T(self,
            boost::python::detail::reference_parameter<A1>(from_python(a1, type<A1>())),
            boost::python::detail::reference_parameter<A2>(from_python(a2, type<A2>())),
            boost::python::detail::reference_parameter<A3>(from_python(a3, type<A3>())),
            boost::python::detail::reference_parameter<A4>(from_python(a4, type<A4>()))
            );
    }
    const char* description() const
        { return typeid(void (*)(T&, A1, A2, A3, A4)).name(); }
};

template <class T, class A1, class A2, class A3, class A4, class A5>
struct init5 : init
{
    virtual instance_holder_base* create_holder(extension_instance* self, PyObject* args, PyObject* /*keywords*/) const
    {
        PyObject* a1;
        PyObject* a2;
        PyObject* a3;
        PyObject* a4;
        PyObject* a5;
        if (!PyArg_ParseTuple(args, const_cast<char*>("OOOOO"), &a1, &a2, &a3, &a4, &a5))
            throw argument_error();
        return new T(self,
            boost::python::detail::reference_parameter<A1>(from_python(a1, type<A1>())),
            boost::python::detail::reference_parameter<A2>(from_python(a2, type<A2>())),
            boost::python::detail::reference_parameter<A3>(from_python(a3, type<A3>())),
            boost::python::detail::reference_parameter<A4>(from_python(a4, type<A4>())),
            boost::python::detail::reference_parameter<A5>(from_python(a5, type<A5>()))
            );
    }
    const char* description() const
        { return typeid(void (*)(T&, A1, A2, A3, A4, A5)).name(); }
};

template <class T, class A1, class A2, class A3, class A4, class A5, class A6>
struct init6 : init
{
    virtual instance_holder_base* create_holder(extension_instance* self, PyObject* args, PyObject* /*keywords*/) const
    {
        PyObject* a1;
        PyObject* a2;
        PyObject* a3;
        PyObject* a4;
        PyObject* a5;
        PyObject* a6;
        if (!PyArg_ParseTuple(args, const_cast<char*>("OOOOOO"), &a1, &a2, &a3, &a4, &a5, &a6))
            throw argument_error();
        return new T(self,
            boost::python::detail::reference_parameter<A1>(from_python(a1, type<A1>())),
            boost::python::detail::reference_parameter<A2>(from_python(a2, type<A2>())),
            boost::python::detail::reference_parameter<A3>(from_python(a3, type<A3>())),
            boost::python::detail::reference_parameter<A4>(from_python(a4, type<A4>())),
            boost::python::detail::reference_parameter<A5>(from_python(a5, type<A5>())),
            boost::python::detail::reference_parameter<A6>(from_python(a6, type<A6>()))
            );
    }
    const char* description() const
        { return typeid(void (*)(T&, A1, A2, A3, A4, A5, A6)).name(); }
};

template <class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7>
struct init7 : init
{
    virtual instance_holder_base* create_holder(extension_instance* self, PyObject* args, PyObject* /*keywords*/) const
    {
        PyObject* a1;
        PyObject* a2;
        PyObject* a3;
        PyObject* a4;
        PyObject* a5;
        PyObject* a6;
        PyObject* a7;
        if (!PyArg_ParseTuple(args, const_cast<char*>("OOOOOOO"), &a1, &a2, &a3, &a4, &a5, &a6, &a7))
            throw argument_error();
        return new T(self,
            boost::python::detail::reference_parameter<A1>(from_python(a1, type<A1>())),
            boost::python::detail::reference_parameter<A2>(from_python(a2, type<A2>())),
            boost::python::detail::reference_parameter<A3>(from_python(a3, type<A3>())),
            boost::python::detail::reference_parameter<A4>(from_python(a4, type<A4>())),
            boost::python::detail::reference_parameter<A5>(from_python(a5, type<A5>())),
            boost::python::detail::reference_parameter<A6>(from_python(a6, type<A6>())),
            boost::python::detail::reference_parameter<A7>(from_python(a7, type<A7>()))
            );
    }
    const char* description() const
        { return typeid(void (*)(T&, A1, A2, A3, A4, A5, A6, A7)).name(); }
};

template <class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
struct init8 : init
{
    virtual instance_holder_base* create_holder(extension_instance* self, PyObject* args, PyObject* /*keywords*/) const
    {
        PyObject* a1;
        PyObject* a2;
        PyObject* a3;
        PyObject* a4;
        PyObject* a5;
        PyObject* a6;
        PyObject* a7;
        PyObject* a8;
        if (!PyArg_ParseTuple(args, const_cast<char*>("OOOOOOOO"), &a1, &a2, &a3, &a4, &a5, &a6, &a7, &a8))
            throw argument_error();
        return new T(self,
            boost::python::detail::reference_parameter<A1>(from_python(a1, type<A1>())),
            boost::python::detail::reference_parameter<A2>(from_python(a2, type<A2>())),
            boost::python::detail::reference_parameter<A3>(from_python(a3, type<A3>())),
            boost::python::detail::reference_parameter<A4>(from_python(a4, type<A4>())),
            boost::python::detail::reference_parameter<A5>(from_python(a5, type<A5>())),
            boost::python::detail::reference_parameter<A6>(from_python(a6, type<A6>())),
            boost::python::detail::reference_parameter<A7>(from_python(a7, type<A7>())),
            boost::python::detail::reference_parameter<A8>(from_python(a8, type<A8>()))
            );
    }
    const char* description() const
        { return typeid(void (*)(T&, A1, A2, A3, A4, A5, A6, A7, A8)).name(); }
};

template <class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
struct init9 : init
{
    virtual instance_holder_base* create_holder(extension_instance* self, PyObject* args, PyObject* /*keywords*/) const
    {
        PyObject* a1;
        PyObject* a2;
        PyObject* a3;
        PyObject* a4;
        PyObject* a5;
        PyObject* a6;
        PyObject* a7;
        PyObject* a8;
        PyObject* a9;
        if (!PyArg_ParseTuple(args, const_cast<char*>("OOOOOOOOO"), &a1, &a2, &a3, &a4, &a5, &a6, &a7, &a8, &a9))
            throw argument_error();
        return new T(self,
            boost::python::detail::reference_parameter<A1>(from_python(a1, type<A1>())),
            boost::python::detail::reference_parameter<A2>(from_python(a2, type<A2>())),
            boost::python::detail::reference_parameter<A3>(from_python(a3, type<A3>())),
            boost::python::detail::reference_parameter<A4>(from_python(a4, type<A4>())),
            boost::python::detail::reference_parameter<A5>(from_python(a5, type<A5>())),
            boost::python::detail::reference_parameter<A6>(from_python(a6, type<A6>())),
            boost::python::detail::reference_parameter<A7>(from_python(a7, type<A7>())),
            boost::python::detail::reference_parameter<A8>(from_python(a8, type<A8>())),
            boost::python::detail::reference_parameter<A9>(from_python(a9, type<A9>()))
            );
    }
    const char* description() const
        { return typeid(void (*)(T&, A1, A2, A3, A4, A5, A6, A7, A8, A9)).name(); }
};

template <class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10>
struct init10 : init
{
    virtual instance_holder_base* create_holder(extension_instance* self, PyObject* args, PyObject* /*keywords*/) const
    {
        PyObject* a1;
        PyObject* a2;
        PyObject* a3;
        PyObject* a4;
        PyObject* a5;
        PyObject* a6;
        PyObject* a7;
        PyObject* a8;
        PyObject* a9;
        PyObject* a10;
        if (!PyArg_ParseTuple(args, const_cast<char*>("OOOOOOOOOO"), &a1, &a2, &a3, &a4, &a5, &a6, &a7, &a8, &a9, &a10))
            throw argument_error();
        return new T(self,
            boost::python::detail::reference_parameter<A1>(from_python(a1, type<A1>())),
            boost::python::detail::reference_parameter<A2>(from_python(a2, type<A2>())),
            boost::python::detail::reference_parameter<A3>(from_python(a3, type<A3>())),
            boost::python::detail::reference_parameter<A4>(from_python(a4, type<A4>())),
            boost::python::detail::reference_parameter<A5>(from_python(a5, type<A5>())),
            boost::python::detail::reference_parameter<A6>(from_python(a6, type<A6>())),
            boost::python::detail::reference_parameter<A7>(from_python(a7, type<A7>())),
            boost::python::detail::reference_parameter<A8>(from_python(a8, type<A8>())),
            boost::python::detail::reference_parameter<A9>(from_python(a9, type<A9>())),
            boost::python::detail::reference_parameter<A10>(from_python(a10, type<A10>()))
            );
    }
    const char* description() const
        { return typeid(void (*)(T&, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10)).name(); }
};

}}} // namespace boost::python::detail

#endif // INIT_FUNCTION_DWA052000_H_
