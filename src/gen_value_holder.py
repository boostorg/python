#  Copyright David Abrahams 2002. Permission to copy, use, modify,
#  sell and distribute this software is granted provided this
#  copyright notice appears in all copies. This software is provided
#  "as is" without express or implied warranty, and with no claim as
#  to its suitability for any purpose.
#
#  This work was funded in part by Lawrence Livermore National Labs

from gen_function import *
import string

def _generate(member_function_args, free_function_args = None):
    return ('''// Copyright David Abrahams 2001. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef VALUE_HOLDER_DWA20011215_HPP
# define VALUE_HOLDER_DWA20011215_HPP

# include <boost/python/object/class.hpp>
# include <boost/python/converter/type_id.hpp>
# include <boost/python/object/inheritance.hpp>
# include <boost/ref.hpp>
# include <boost/function/function_base.hpp>

namespace boost { namespace python { namespace objects { 

template <class Held>
struct value_holder : instance_holder
{
    // Forward construction to the held object
'''
            +
            gen_functions(
