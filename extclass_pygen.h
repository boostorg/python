//  (C) Copyright David Abrahams 2000. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
//  The author gratefully acknowleges the support of Dragon Systems, Inc., in
//  producing this work.
//
//  This file automatically generated for 5-argument constructors by
//  gen_extclass.py

#ifndef EXTCLASS_PYGEN_DWA070900_H_
# define EXTCLASS_PYGEN_DWA070900_H_

    
// A simple wrapper over a T which allows us to use ExtensionClass<T> with a
// single template parameter only. See ExtensionClass<T>, above.
template <class T>
class HeldInstance : public T
{
    // There are no member functions: we want to avoid inadvertently overriding
    // any virtual functions in T.
public:
    HeldInstance(PyObject* p) : T(), m_self(p) {}
    template <class A1>
    HeldInstance(PyObject* p, const A1& a1) : T(a1), m_self(p) {}
    template <class A1, class A2>
    HeldInstance(PyObject* p, const A1& a1, const A2& a2) : T(a1, a2), m_self(p) {}
    template <class A1, class A2, class A3>
    HeldInstance(PyObject* p, const A1& a1, const A2& a2, const A3& a3) : T(a1, a2, a3), m_self(p) {}
    template <class A1, class A2, class A3, class A4>
    HeldInstance(PyObject* p, const A1& a1, const A2& a2, const A3& a3, const A4& a4) : T(a1, a2, a3, a4), m_self(p) {}
    template <class A1, class A2, class A3, class A4, class A5>
    HeldInstance(PyObject* p, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5) : T(a1, a2, a3, a4, a5), m_self(p) {}
protected:
    PyObject* m_self; // Not really needed; doesn't really hurt.
};

class InstanceHolderBase
{
public:
    virtual ~InstanceHolderBase() {}
};

template <class Held>
class InstanceHolder : public InstanceHolderBase
{
public:
    virtual Held *target() = 0;
};
    
template <class Held, class Wrapper>
class InstanceValueHolder : public InstanceHolder<Held>
{
public:
    Held* target() { return &m_held; }
    Wrapper* value_target() { return &m_held; }

    InstanceValueHolder(ExtensionInstance* p) :
        m_held(p) {}
    template <class A1>
    InstanceValueHolder(ExtensionInstance* p, const A1& a1) :
        m_held(p, a1) {}
    template <class A1, class A2>
    InstanceValueHolder(ExtensionInstance* p, const A1& a1, const A2& a2) :
        m_held(p, a1, a2) {}
    template <class A1, class A2, class A3>
    InstanceValueHolder(ExtensionInstance* p, const A1& a1, const A2& a2, const A3& a3) :
        m_held(p, a1, a2, a3) {}
    template <class A1, class A2, class A3, class A4>
    InstanceValueHolder(ExtensionInstance* p, const A1& a1, const A2& a2, const A3& a3, const A4& a4) :
        m_held(p, a1, a2, a3, a4) {}
    template <class A1, class A2, class A3, class A4, class A5>
    InstanceValueHolder(ExtensionInstance* p, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5) :
        m_held(p, a1, a2, a3, a4, a5) {}
private:
    Wrapper m_held;
};

#endif
