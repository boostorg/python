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

class ExtensionInstance;
class InstanceHolderBase;

class Init;
template <class T> struct Init0;
template <class T, class A1> struct Init1;
template <class T, class A1, class A2> struct Init2;
template <class T, class A1, class A2, class A3> struct Init3;
template <class T, class A1, class A2, class A3, class A4> struct Init4;
template <class T, class A1, class A2, class A3, class A4, class A5> struct Init5;

template <class T>
struct InitFunction
{
    static Init* create(Signature0)
        { return new Init0<T>; }

    template <class A1>
    static Init* create(Signature1<A1>)
        { return new Init1<T, A1>; }

    template <class A1, class A2>
    static Init* create(Signature2<A1, A2>)
        { return new Init2<T, A1, A2>; }

    template <class A1, class A2, class A3>
    static Init* create(Signature3<A1, A2, A3>)
        { return new Init3<T, A1, A2, A3>; }

    template <class A1, class A2, class A3, class A4>
    static Init* create(Signature4<A1, A2, A3, A4>)
        { return new Init4<T, A1, A2, A3, A4>; }

    template <class A1, class A2, class A3, class A4, class A5>
    static Init* create(Signature5<A1, A2, A3, A4, A5>)
        { return new Init5<T, A1, A2, A3, A4, A5>; }
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
        { return typeid(void (*)()).name(); }
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
            from_python(a1, Type<A1>())
            );
    }
    const char* description() const
        { return typeid(void (*)(A1)).name(); }
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
            from_python(a1, Type<A1>()),
            from_python(a2, Type<A2>())
            );
    }
    const char* description() const
        { return typeid(void (*)(A1, A2)).name(); }
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
            from_python(a1, Type<A1>()),
            from_python(a2, Type<A2>()),
            from_python(a3, Type<A3>())
            );
    }
    const char* description() const
        { return typeid(void (*)(A1, A2, A3)).name(); }
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
            from_python(a1, Type<A1>()),
            from_python(a2, Type<A2>()),
            from_python(a3, Type<A3>()),
            from_python(a4, Type<A4>())
            );
    }
    const char* description() const
        { return typeid(void (*)(A1, A2, A3, A4)).name(); }
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
            from_python(a1, Type<A1>()),
            from_python(a2, Type<A2>()),
            from_python(a3, Type<A3>()),
            from_python(a4, Type<A4>()),
            from_python(a5, Type<A5>())
            );
    }
    const char* description() const
        { return typeid(void (*)(A1, A2, A3, A4, A5)).name(); }
};

}

#endif // INIT_FUNCTION_DWA052000_H_
