#  (C) Copyright David Abrahams 2001. Permission to copy, use, modify, sell and
#  distribute this software is granted provided this copyright notice appears
#  in all copies. This software is provided "as is" without express or implied
#  warranty, and with no claim as to its suitability for any purpose.
#
#  This work was funded in part by Lawrence Berkeley National Labs

from gen_function import *
import string

header = '''//  (C) Copyright David Abrahams 2001. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
//  This work was funded in part by Lawrence Berkeley National Labs
//
//  This file generated for %d-argument member functions and %d-argument free
//  functions by gen_arg_tuple_size.python
'''

_cv_qualifiers = ('', ' const', ' volatile', ' const volatile')

def gen_arg_tuple_size(member_function_args, free_function_args = None):
    if free_function_args is None:
        free_function_args = member_function_args + 1

    return_none = ''';
        return detail::none();'''
    
    return (header % (member_function_args, free_function_args)
            + '''
#ifndef ARG_TUPLE_SIZE_DWA20011201_HPP
# define ARG_TUPLE_SIZE_DWA20011201_HPP

namespace boost { namespace python { namespace detail {

// Computes (at compile-time) the number of elements that a Python
// argument tuple must have in order to be passed to a wrapped C++
// (member) function of the given type.
template <class F> struct arg_tuple_size;

# if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION) && !defined(__BORLANDC__)

'''
            + gen_functions(
'''template <class R%(, class A%+%)>
struct arg_tuple_size<R (*)(%(A%+%:, %))>
{
    BOOST_STATIC_CONSTANT(std::size_t, value = %n);
};

''', free_function_args)

            + '\n'
            + gen_functions(
'''template <class R, class A0%(, class A%+%)>
struct arg_tuple_size<R (A0::*)(%(A%+%:, %))%1>
{
    BOOST_STATIC_CONSTANT(std::size_t, value = %+);
};

''', member_function_args, '')
            +
'''# else

// We will use the "sizeof() trick" to work around the lack of
// partial specialization in MSVC6 and its broken-ness in borland.
// See http://opensource.adobe.com  or
// http://groups.yahoo.com/group/boost/message/5441 for
// more examples

// This little package is used to transmit the number of arguments
// from the helper functions below to the sizeof() expression below.
// Because we can never have an array of fewer than 1 element, we
// add 1 to n and then subtract 1 from the result of sizeof() below.
template <int n>
struct char_array
{
    char elements[n+1];
};

// The following helper functions are never actually called, since
// they are only used within a sizeof() expression, but the type of
// their return value is used to discriminate between various free
// and member function pointers at compile-time.

'''
            + gen_functions(
'''template <class R%(, class A%+%)>
char_array<%n> arg_tuple_size_helper(R (*)(%(A%+%:, %)));

''', free_function_args)
            
            + reduce(lambda x,y: x+'\n'+y
                   , map(
        lambda cv: gen_functions(
'''template <class R, class A0%(, class A%+%)>
char_array<%+> arg_tuple_size_helper(R (A0::*)(%(A%+%:, %))%1);

''', member_function_args, cv)
        , _cv_qualifiers))
            + '''
template <class F>
struct arg_tuple_size
{
    // The sizeof() magic happens here
    BOOST_STATIC_CONSTANT(std::size_t, value
      = sizeof(arg_tuple_size_helper(F(0)).elements) - 1);
};
# endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
}}} // namespace boost::python::detail

#endif // ARG_TUPLE_SIZE_DWA20011201_HPP
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


