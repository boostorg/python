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
%}    static Init* create(Signature%x%{<%(A%n%:, %)>%})
        { return new Init%x<T%(, A%n%)>; }
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
            from_python(a%n, Type<A%n>())%)
            );
    }
    const char* description() const
        { return typeid(void (*)(%(A%n%:, %))).name(); }
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

