from gen_function import *
import string

def gen_singleton(args):
    return (
"""//  (C) Copyright David Abrahams 2000. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
//  The author gratefully acknowleges the support of Dragon Systems, Inc., in
//  producing this work.

#ifndef SINGLETON_DWA051900_H_
# define SINGLETON_DWA051900_H_

# include "pyconfig.h"

namespace py { namespace detail {

struct Empty {};
template <class Derived, class Base = Empty>
struct Singleton : Base
{
    typedef Singleton SingletonBase; // Convenience type for derived class constructors
    
    static Derived* singleton();

    // Pass-through constructors
"""
        + gen_functions("""%{
    template <%(class A%n%:, %)>
%}    Singleton(%(const A%n& a%n%:, %)) : Base(%(a%n%:, %)) {}
""", args)
        + """
};

template <class Derived, class Base>
Derived* Singleton<Derived,Base>::singleton()
{
    static Derived x;
    return &x;
}

}} // namespace py::detail

#endif
""")

if __name__ == '__main__':
    import sys

    if len(sys.argv) == 1:
        args = 5
    else:
        args = int(sys.argv[1])

    print gen_singleton(args)
