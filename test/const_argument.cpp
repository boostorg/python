/* Copyright 2004 Jonathan Brandmeyer 
 * Use, modification and distribution are subject to the
 * Boost Software License, Version 1.0. (See accompanying file
 * LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 * The purpose of this test is to determine if a function can be called from
 * Python with a const value type as an argument, and whether or not the 
 * presence of a prototype without the cv-qualifier will work around the
 * compiler's bug.
 */
#include <boost/python.hpp>
using namespace boost::python;

bool accept_const_arg_noproto( const object) 
{
    return true; 
}

bool accept_const_arg_with_proto( object);
bool accept_const_arg_with_proto( const object) 
{
    return true; 
}

BOOST_PYTHON_MODULE( const_argument_ext)
{
    def( "accept_const_arg_noproto", accept_const_arg_noproto);
    def( "accept_const_arg_with_proto", accept_const_arg_with_proto);
}

