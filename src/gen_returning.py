#  (C) Copyright David Abrahams 2001,2002. Permission to copy, use, modify, sell and
#  distribute this software is granted provided this copyright notice appears
#  in all copies. This software is provided "as is" without express or implied
#  warranty, and with no claim as to its suitability for any purpose.
#
#  This work was funded in part by Lawrence Berkeley National Labs

from gen_function import *
import string

header = '''//  (C) Copyright David Abrahams 2001,2002. Permission to copy, use, modify, sell
//  and distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
//  This work was funded in part by Lawrence Berkeley National Labs
//
//  This file generated for %d-argument member functions and %d-argument free
//  functions by gen_returning.py
'''

body_sections = (
'''
#ifndef RETURNING_DWA20011201_HPP
# define RETURNING_DWA20011201_HPP

# include <boost/python/detail/wrap_python.hpp>
# include <boost/config.hpp>
# include <boost/python/detail/none.hpp>
# include <boost/python/from_python.hpp>

namespace boost { namespace python { namespace detail {

// Calling C++ from Python
template <class R>
struct returning
{
''',
'''
''',
'''    // Free functions
''',
'''};
                           
template <>
struct returning<void>
{
    typedef void R;
''',
'''
''',
'''
    // Free functions
''',
'''};

}}} // namespace boost::python::detail

#endif // RETURNING_DWA20011201_HPP
''')

#'

member_function = '''    template <class P, class A0%(, class A%+%)>
    static PyObject* call(R (A0::*pmf)(%(A%+%:, %))%1, PyObject* args_, PyObject*, P const& policies)
    {
        // check that each of the arguments is convertible
        from_python<A0%1*> c0(PyTuple_GET_ITEM(args_, 0));
        if (!c0.convertible()) return 0;
%(        from_python<A%+> c%+(PyTuple_GET_ITEM(args_, %+));
        if (!c%+.convertible()) return 0;
%)
%[r%:        // find the result converter
        typedef typename P::result_converter result_converter;
        typename eval<result_converter,R>::type cr;
        if (!cr.convertible()) return 0;
        
%]        if (!policies.precall(args_)) return 0;

        %[r%:PyObject* result = cr( %]((c0(PyTuple_GET_ITEM(args_, 0)))->*pmf)(
                %(c%+(PyTuple_GET_ITEM(args_, %+))%:
                , %))%[r%: )%];
        
        return policies.postcall(args_, %[r%:result%]%[v%:detail::none()%]);
    }
''' 
        
free_function = '''    template <class P%(, class A%n%%)>
    static PyObject* call(R (*pf)(%(A%n%:, %)), PyObject* args_, PyObject*, P const& policies)
    {%{
        // check that each of the arguments is convertible
%}%(        from_python<A%n> c%n(PyTuple_GET_ITEM(args_, %n));
        if (!c%n.convertible()) return 0;
%)
%[r%:        // find the result converter
        typedef typename P::result_converter result_converter;
        typename eval<result_converter,R>::type cr;
        if (!cr.convertible()) return 0;
        
%]%[not-void-and-0-arg%:        if (!policies.precall(args_)) return 0;
        
%]        %[r%:PyObject* result = cr( %](*pf)(
                %(c%n(PyTuple_GET_ITEM(args_, %n))%:
                , %))%[r%: )%];
                
        return policies.postcall(args_, %[r%:result%]%[v%:detail::none()%]);
    }
''' 

def _returns_value(key, n, args, value):
    if key != 'v':
        return value
    else:
        return ''

def _returns_void(key, n, args, value):
    if key == 'v' or key == 'not-void-and-0-arg' and n != 0:
        return value
    else:
        return ''

_cv_qualifiers = ('', ' const', ' volatile', ' const volatile')

_prefix = {
#     ' const': '''

# // missing cv-qualified -> cv-unqualified member pointer conversions
# # if defined(__MWERKS__) && __MWERKS__ <=0x2406 || defined(BOOST_MSVC) && BOOST_MSVC <= 1200 || defined(__BORLANDC__)
# ''',
             ' const volatile': '''
// missing const volatile type traits
#  ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
'''};
            
def gen_returning(member_function_args, free_function_args = None):
    if free_function_args is None:
        free_function_args = member_function_args + 1

    return_none = ''';
        return detail::none();'''
    
    return (header % (member_function_args, free_function_args)
            + body_sections[0]
            #
            # functions returning results
            #

            + reduce(lambda x,y: x+y
                   , map(lambda cv:
                         _prefix.get(cv,'') 
                         + gen_functions(member_function,
                                         member_function_args, cv,
                                         fill = _returns_value) + '\n'
        , _cv_qualifiers))
            + '''#  endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
            
'''
## endif // missing cv-qualified -> cv-unqualified member pointer conversions
#'''
            # free functions
            + gen_functions(free_function, free_function_args, fill = _returns_value)
            + body_sections[3]

            #
            # functions returning void
            #

            + reduce(lambda x,y: x+y
                   , map(lambda cv:
                         _prefix.get(cv,'')
                         + gen_functions(member_function,
                                         member_function_args, cv, fill =
                                         _returns_void) + '\n'
        , _cv_qualifiers))
            
            + '''#  endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
            
'''
## endif // missing cv-qualified -> cv-unqualified member pointer conversions
#'''
            # free functions
            + gen_functions(free_function, free_function_args, fill = _returns_void)
            + body_sections[6]
            )

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

    print gen_returning(member_function_args, free_function_args)


