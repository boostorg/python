#  (C) Copyright David Abrahams 2001. Permission to copy, use, modify, sell and
#  distribute this software is granted provided this copyright notice appears
#  in all copies. This software is provided "as is" without express or implied
#  warranty, and with no claim as to its suitability for any purpose.
#
#  This work was funded in part by Lawrence Berkeley National Labs

from gen_function import *
import string

header = '''//  (C) Copyright David Abrahams 2002. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
//  This work was funded in part by Lawrence Berkeley and Lawrence
//  Livermore National Labs
//
//  This file generated for %d-argument member functions and %d-argument free
//  functions by gen_signature.py
'''

_cv_qualifiers = ('', ' const', ' volatile', ' const volatile')

_suffix = {
    '': '''
// Metrowerks thinks this creates ambiguities
# if !defined(__MWERKS__) || __MWERKS__ > 0x2406
''', ' const volatile': '''
# endif // __MWERKS__
'''
    };

def gen_arg_tuple_size(member_function_args, free_function_args = None):
    if free_function_args is None:
        free_function_args = member_function_args + 1

    return_none = ''';
        return detail::none();'''
    
    return (header % (member_function_args, free_function_args)
            + '''
#ifndef SIGNATURE_DWA2002128_HPP
# define SIGNATURE_DWA2002128_HPP

# include <boost/mpl/type_list.hpp>

namespace boost { namespace python { namespace detail {
'''

            + gen_functions('''
template <class R%(, class A%n%)>
mpl::type_list<R%(,A%n%)>
signature(R (*)(%(A%n%:, %)))
{
    return mpl::type_list<R%(,A%n%)>()
}
''', free_function_args)
            
            + reduce(lambda x,y: x+'\n'+y
                   , map(
        lambda cv: gen_functions(
'''template <class R, class A0%(, class A%+%)>
mpl::type_list<R%,A0%1&%(,A%+%)> signature(R (A0::*)(%(A%+%:, %))%1)
{
    return mpl::type_list<R%,A0%1&%(,A%+%)>();
}

''', member_function_args, cv)
        , _cv_qualifiers)) + '''}}} // namespace boost::python::detail

#endif // SIGNATURE_DWA2002128_HPP
''')
            
if __name__ == '__main__':
    import sys

    if len(sys.argv) == 1:
        member_function_args = 5
        free_function_args = 6
    else:
        member_function_args = int(sys.argv[1])
        if len(sys.argv) > 2:
            free_function_args = int(sys.argv[2])
        else:
            free_function_args = member_function_args

    print gen_arg_tuple_size(member_function_args, free_function_args)


