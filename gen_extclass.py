from gen_function import *
import string

def gen_extclass(args):
    held_instance = """%{
    template <%(class A%n%:, %)>%}
    HeldInstance(PyObject* p%(, const A%n%& a%n%)) : T(%(a%n%:, %)), m_self(p) {}"""

    instance_value_holder = """%{
    template <%(class A%n%:, %)>%}
    InstanceValueHolder(ExtensionInstance* p%(, const A%n& a%n%)) :
        m_held(p%(, a%n%)) {}"""
    
    return (
"""//  (C) Copyright David Abrahams 2000. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
//  The author gratefully acknowleges the support of Dragon Systems, Inc., in
//  producing this work.
//
//  This file automatically generated for %d-argument constructors by
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
public:""" % args
        + gen_functions(held_instance, args)
        + """
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
"""
        + gen_functions(instance_value_holder, args)
        + """
private:
    Wrapper m_held;
};

#endif
""")

if __name__ == '__main__':
    import sys

    if len(sys.argv) == 1:
        args = 5
    else:
        args = int(sys.argv[1])

    print gen_extclass(args)
