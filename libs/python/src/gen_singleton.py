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

# include <boost/python/detail/config.hpp>

namespace boost { namespace python { namespace detail {

struct empty {};
template <class Derived, class Base = empty>
struct singleton : Base
{
    typedef singleton singleton_base; // Convenience type for derived class constructors
    
    static Derived* instance();

    // Pass-through constructors
"""
        + gen_functions("""%{
    template <%(class A%n%:, %)>
%}    singleton(%(const A%n& a%n%:, %)) : Base(%(a%n%:, %)) {}
""", args)
        + """
};

template <class Derived, class Base>
Derived* singleton<Derived,Base>::instance()
{
    static Derived x;
    return &x;
}

}}} // namespace boost::python::detail

#endif
""")

if __name__ == '__main__':
    import sys

    if len(sys.argv) == 1:
        args = 5
    else:
        args = int(sys.argv[1])

    print gen_singleton(args)
