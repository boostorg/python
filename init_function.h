//  (C) Copyright David Abrahams 2000. Permission to copy, use, modify, sell and
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

class ExtensionInstance;
class InstanceHolderBase;

class Init;
template <class T> struct Init0;
template <class T, class A1> struct Init1;
template <class T, class A1, class A2> struct Init2;
template <class T, class A1, class A2, class A3> struct Init3;
template <class T, class A1, class A2, class A3, class A4> struct Init4;
template <class T, class A1, class A2, class A3, class A4, class A5> struct Init5;
template <class T, class A1, class A2, class A3, class A4, class A5, class A6> struct Init6;
template <class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7> struct Init7;
template <class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8> struct Init8;
template <class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9> struct Init9;
template <class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10> struct Init10;

template <class T>
struct InitFunction
{
    static Init* create(Signature0) {
        return new Init0<T>;
    }

    template <class A1>
    static Init* create(Signature1<A1>) {
        return new Init1<T,
                       detail::parameter_traits<A1>::const_reference>;
    }

    template <class A1, class A2>
    static Init* create(Signature2<A1, A2>) {
        return new Init2<T,
                       detail::parameter_traits<A1>::const_reference,
                       detail::parameter_traits<A2>::const_reference>;
    }

    template <class A1, class A2, class A3>
    static Init* create(Signature3<A1, A2, A3>) {
        return new Init3<T,
                       detail::parameter_traits<A1>::const_reference,
                       detail::parameter_traits<A2>::const_reference,
                       detail::parameter_traits<A3>::const_reference>;
    }

    template <class A1, class A2, class A3, class A4>
    static Init* create(Signature4<A1, A2, A3, A4>) {
        return new Init4<T,
                       detail::parameter_traits<A1>::const_reference,
                       detail::parameter_traits<A2>::const_reference,
                       detail::parameter_traits<A3>::const_reference,
                       detail::parameter_traits<A4>::const_reference>;
    }

    template <class A1, class A2, class A3, class A4, class A5>
    static Init* create(Signature5<A1, A2, A3, A4, A5>) {
        return new Init5<T,
                       detail::parameter_traits<A1>::const_reference,
                       detail::parameter_traits<A2>::const_reference,
                       detail::parameter_traits<A3>::const_reference,
                       detail::parameter_traits<A4>::const_reference,
                       detail::parameter_traits<A5>::const_reference>;
    }

    template <class A1, class A2, class A3, class A4, class A5, class A6>
    static Init* create(Signature6<A1, A2, A3, A4, A5, A6>) {
        return new Init6<T,
                       detail::parameter_traits<A1>::const_reference,
                       detail::parameter_traits<A2>::const_reference,
                       detail::parameter_traits<A3>::const_reference,
                       detail::parameter_traits<A4>::const_reference,
                       detail::parameter_traits<A5>::const_reference,
                       detail::parameter_traits<A6>::const_reference>;
    }

    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7>
    static Init* create(Signature7<A1, A2, A3, A4, A5, A6, A7>) {
        return new Init7<T,
                       detail::parameter_traits<A1>::const_reference,
                       detail::parameter_traits<A2>::const_reference,
                       detail::parameter_traits<A3>::const_reference,
                       detail::parameter_traits<A4>::const_reference,
                       detail::parameter_traits<A5>::const_reference,
                       detail::parameter_traits<A6>::const_reference,
                       detail::parameter_traits<A7>::const_reference>;
    }

    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
    static Init* create(Signature8<A1, A2, A3, A4, A5, A6, A7, A8>) {
        return new Init8<T,
                       detail::parameter_traits<A1>::const_reference,
                       detail::parameter_traits<A2>::const_reference,
                       detail::parameter_traits<A3>::const_reference,
                       detail::parameter_traits<A4>::const_reference,
                       detail::parameter_traits<A5>::const_reference,
                       detail::parameter_traits<A6>::const_reference,
                       detail::parameter_traits<A7>::const_reference,
                       detail::parameter_traits<A8>::const_reference>;
    }

    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
    static Init* create(Signature9<A1, A2, A3, A4, A5, A6, A7, A8, A9>) {
        return new Init9<T,
                       detail::parameter_traits<A1>::const_reference,
                       detail::parameter_traits<A2>::const_reference,
                       detail::parameter_traits<A3>::const_reference,
                       detail::parameter_traits<A4>::const_reference,
                       detail::parameter_traits<A5>::const_reference,
                       detail::parameter_traits<A6>::const_reference,
                       detail::parameter_traits<A7>::const_reference,
                       detail::parameter_traits<A8>::const_reference,
                       detail::parameter_traits<A9>::const_reference>;
    }

    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10>
    static Init* create(Signature10<A1, A2, A3, A4, A5, A6, A7, A8, A9, A10>) {
        return new Init10<T,
                       detail::parameter_traits<A1>::const_reference,
                       detail::parameter_traits<A2>::const_reference,
                       detail::parameter_traits<A3>::const_reference,
                       detail::parameter_traits<A4>::const_reference,
                       detail::parameter_traits<A5>::const_reference,
                       detail::parameter_traits<A6>::const_reference,
                       detail::parameter_traits<A7>::const_reference,
                       detail::parameter_traits<A8>::const_reference,
                       detail::parameter_traits<A9>::const_reference,
                       detail::parameter_traits<A10>::const_reference>;
    }
};

class Init : public Function
{
private: // override Function hook
    PyObject* do_call(PyObject* args, PyObject* keywords) const;
private:
    virtual InstanceHolderBase* create_holder(ExtensionInstance* self, PyObject* tail_args, PyObject* keywords) const = 0;
};


template <class T>
struct Init0 : Init
{
    virtual InstanceHolderBase* create_holder(ExtensionInstance* self, PyObject* args, PyObject* /*keywords*/) const
    {
        if (!PyArg_ParseTuple(args, const_cast<char*>("")))
            throw ArgumentError();
        return new T(self
            );
    }
    const char* description() const
        { return typeid(void (*)(T&)).name(); }
};

template <class T, class A1>
struct Init1 : Init
{
    virtual InstanceHolderBase* create_holder(ExtensionInstance* self, PyObject* args, PyObject* /*keywords*/) const
    {
        PyObject* a1;
        if (!PyArg_ParseTuple(args, const_cast<char*>("O"), &a1))
            throw ArgumentError();
        return new T(self,
            py::detail::reference_parameter<A1>(from_python(a1, Type<A1>()))
            );
    }
    const char* description() const
        { return typeid(void (*)(T&, A1)).name(); }
};

template <class T, class A1, class A2>
struct Init2 : Init
{
    virtual InstanceHolderBase* create_holder(ExtensionInstance* self, PyObject* args, PyObject* /*keywords*/) const
    {
        PyObject* a1;
        PyObject* a2;
        if (!PyArg_ParseTuple(args, const_cast<char*>("OO"), &a1, &a2))
            throw ArgumentError();
        return new T(self,
            py::detail::reference_parameter<A1>(from_python(a1, Type<A1>())),
            py::detail::reference_parameter<A2>(from_python(a2, Type<A2>()))
            );
    }
    const char* description() const
        { return typeid(void (*)(T&, A1, A2)).name(); }
};

template <class T, class A1, class A2, class A3>
struct Init3 : Init
{
    virtual InstanceHolderBase* create_holder(ExtensionInstance* self, PyObject* args, PyObject* /*keywords*/) const
    {
        PyObject* a1;
        PyObject* a2;
        PyObject* a3;
        if (!PyArg_ParseTuple(args, const_cast<char*>("OOO"), &a1, &a2, &a3))
            throw ArgumentError();
        return new T(self,
            py::detail::reference_parameter<A1>(from_python(a1, Type<A1>())),
            py::detail::reference_parameter<A2>(from_python(a2, Type<A2>())),
            py::detail::reference_parameter<A3>(from_python(a3, Type<A3>()))
            );
    }
    const char* description() const
        { return typeid(void (*)(T&, A1, A2, A3)).name(); }
};

template <class T, class A1, class A2, class A3, class A4>
struct Init4 : Init
{
    virtual InstanceHolderBase* create_holder(ExtensionInstance* self, PyObject* args, PyObject* /*keywords*/) const
    {
        PyObject* a1;
        PyObject* a2;
        PyObject* a3;
        PyObject* a4;
        if (!PyArg_ParseTuple(args, const_cast<char*>("OOOO"), &a1, &a2, &a3, &a4))
            throw ArgumentError();
        return new T(self,
            py::detail::reference_parameter<A1>(from_python(a1, Type<A1>())),
            py::detail::reference_parameter<A2>(from_python(a2, Type<A2>())),
            py::detail::reference_parameter<A3>(from_python(a3, Type<A3>())),
            py::detail::reference_parameter<A4>(from_python(a4, Type<A4>()))
            );
    }
    const char* description() const
        { return typeid(void (*)(T&, A1, A2, A3, A4)).name(); }
};

template <class T, class A1, class A2, class A3, class A4, class A5>
struct Init5 : Init
{
    virtual InstanceHolderBase* create_holder(ExtensionInstance* self, PyObject* args, PyObject* /*keywords*/) const
    {
        PyObject* a1;
        PyObject* a2;
        PyObject* a3;
        PyObject* a4;
        PyObject* a5;
        if (!PyArg_ParseTuple(args, const_cast<char*>("OOOOO"), &a1, &a2, &a3, &a4, &a5))
            throw ArgumentError();
        return new T(self,
            py::detail::reference_parameter<A1>(from_python(a1, Type<A1>())),
            py::detail::reference_parameter<A2>(from_python(a2, Type<A2>())),
            py::detail::reference_parameter<A3>(from_python(a3, Type<A3>())),
            py::detail::reference_parameter<A4>(from_python(a4, Type<A4>())),
            py::detail::reference_parameter<A5>(from_python(a5, Type<A5>()))
            );
    }
    const char* description() const
        { return typeid(void (*)(T&, A1, A2, A3, A4, A5)).name(); }
};

template <class T, class A1, class A2, class A3, class A4, class A5, class A6>
struct Init6 : Init
{
    virtual InstanceHolderBase* create_holder(ExtensionInstance* self, PyObject* args, PyObject* /*keywords*/) const
    {
        PyObject* a1;
        PyObject* a2;
        PyObject* a3;
        PyObject* a4;
        PyObject* a5;
        PyObject* a6;
        if (!PyArg_ParseTuple(args, const_cast<char*>("OOOOOO"), &a1, &a2, &a3, &a4, &a5, &a6))
            throw ArgumentError();
        return new T(self,
            py::detail::reference_parameter<A1>(from_python(a1, Type<A1>())),
            py::detail::reference_parameter<A2>(from_python(a2, Type<A2>())),
            py::detail::reference_parameter<A3>(from_python(a3, Type<A3>())),
            py::detail::reference_parameter<A4>(from_python(a4, Type<A4>())),
            py::detail::reference_parameter<A5>(from_python(a5, Type<A5>())),
            py::detail::reference_parameter<A6>(from_python(a6, Type<A6>()))
            );
    }
    const char* description() const
        { return typeid(void (*)(T&, A1, A2, A3, A4, A5, A6)).name(); }
};

template <class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7>
struct Init7 : Init
{
    virtual InstanceHolderBase* create_holder(ExtensionInstance* self, PyObject* args, PyObject* /*keywords*/) const
    {
        PyObject* a1;
        PyObject* a2;
        PyObject* a3;
        PyObject* a4;
        PyObject* a5;
        PyObject* a6;
        PyObject* a7;
        if (!PyArg_ParseTuple(args, const_cast<char*>("OOOOOOO"), &a1, &a2, &a3, &a4, &a5, &a6, &a7))
            throw ArgumentError();
        return new T(self,
            py::detail::reference_parameter<A1>(from_python(a1, Type<A1>())),
            py::detail::reference_parameter<A2>(from_python(a2, Type<A2>())),
            py::detail::reference_parameter<A3>(from_python(a3, Type<A3>())),
            py::detail::reference_parameter<A4>(from_python(a4, Type<A4>())),
            py::detail::reference_parameter<A5>(from_python(a5, Type<A5>())),
            py::detail::reference_parameter<A6>(from_python(a6, Type<A6>())),
            py::detail::reference_parameter<A7>(from_python(a7, Type<A7>()))
            );
    }
    const char* description() const
        { return typeid(void (*)(T&, A1, A2, A3, A4, A5, A6, A7)).name(); }
};

template <class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
struct Init8 : Init
{
    virtual InstanceHolderBase* create_holder(ExtensionInstance* self, PyObject* args, PyObject* /*keywords*/) const
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
            throw ArgumentError();
        return new T(self,
            py::detail::reference_parameter<A1>(from_python(a1, Type<A1>())),
            py::detail::reference_parameter<A2>(from_python(a2, Type<A2>())),
            py::detail::reference_parameter<A3>(from_python(a3, Type<A3>())),
            py::detail::reference_parameter<A4>(from_python(a4, Type<A4>())),
            py::detail::reference_parameter<A5>(from_python(a5, Type<A5>())),
            py::detail::reference_parameter<A6>(from_python(a6, Type<A6>())),
            py::detail::reference_parameter<A7>(from_python(a7, Type<A7>())),
            py::detail::reference_parameter<A8>(from_python(a8, Type<A8>()))
            );
    }
    const char* description() const
        { return typeid(void (*)(T&, A1, A2, A3, A4, A5, A6, A7, A8)).name(); }
};

template <class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
struct Init9 : Init
{
    virtual InstanceHolderBase* create_holder(ExtensionInstance* self, PyObject* args, PyObject* /*keywords*/) const
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
            throw ArgumentError();
        return new T(self,
            py::detail::reference_parameter<A1>(from_python(a1, Type<A1>())),
            py::detail::reference_parameter<A2>(from_python(a2, Type<A2>())),
            py::detail::reference_parameter<A3>(from_python(a3, Type<A3>())),
            py::detail::reference_parameter<A4>(from_python(a4, Type<A4>())),
            py::detail::reference_parameter<A5>(from_python(a5, Type<A5>())),
            py::detail::reference_parameter<A6>(from_python(a6, Type<A6>())),
            py::detail::reference_parameter<A7>(from_python(a7, Type<A7>())),
            py::detail::reference_parameter<A8>(from_python(a8, Type<A8>())),
            py::detail::reference_parameter<A9>(from_python(a9, Type<A9>()))
            );
    }
    const char* description() const
        { return typeid(void (*)(T&, A1, A2, A3, A4, A5, A6, A7, A8, A9)).name(); }
};

template <class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10>
struct Init10 : Init
{
    virtual InstanceHolderBase* create_holder(ExtensionInstance* self, PyObject* args, PyObject* /*keywords*/) const
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
            throw ArgumentError();
        return new T(self,
            py::detail::reference_parameter<A1>(from_python(a1, Type<A1>())),
            py::detail::reference_parameter<A2>(from_python(a2, Type<A2>())),
            py::detail::reference_parameter<A3>(from_python(a3, Type<A3>())),
            py::detail::reference_parameter<A4>(from_python(a4, Type<A4>())),
            py::detail::reference_parameter<A5>(from_python(a5, Type<A5>())),
            py::detail::reference_parameter<A6>(from_python(a6, Type<A6>())),
            py::detail::reference_parameter<A7>(from_python(a7, Type<A7>())),
            py::detail::reference_parameter<A8>(from_python(a8, Type<A8>())),
            py::detail::reference_parameter<A9>(from_python(a9, Type<A9>())),
            py::detail::reference_parameter<A10>(from_python(a10, Type<A10>()))
            );
    }
    const char* description() const
        { return typeid(void (*)(T&, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10)).name(); }
};

}} // namespace py::detail

#endif // INIT_FUNCTION_DWA052000_H_
