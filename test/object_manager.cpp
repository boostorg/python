// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#include <boost/python/converter/object_manager.hpp>
#include <boost/python/borrowed.hpp>
#include <boost/static_assert.hpp>
#include "test_class.hpp"

using namespace boost::python;
using namespace boost::python::converter;

template <class T> struct undefined;

int main()
{
    BOOST_STATIC_ASSERT(is_object_manager<handle<> >::value);
    BOOST_STATIC_ASSERT(!is_object_manager<int>::value);
    BOOST_STATIC_ASSERT(!is_object_manager<test_class<> >::value);
    
    BOOST_STATIC_ASSERT(is_reference_to_object_manager<handle<>&>::value);
    BOOST_STATIC_ASSERT(is_reference_to_object_manager<handle<> const&>::value);
    BOOST_STATIC_ASSERT(is_reference_to_object_manager<handle<> volatile&>::value);
    BOOST_STATIC_ASSERT(is_reference_to_object_manager<handle<> const volatile&>::value);

//    undefined<is_reference_to_object_manager<handle<> >::t1> x1;
//    undefined<is_reference_to_object_manager<handle<> >::t2> x2;
    
    BOOST_STATIC_ASSERT(!is_reference_to_object_manager<handle<> >::value);
    BOOST_STATIC_ASSERT(!is_reference_to_object_manager<test_class<> >::value);
    BOOST_STATIC_ASSERT(!is_reference_to_object_manager<test_class<>&>::value);
    BOOST_STATIC_ASSERT(!is_reference_to_object_manager<test_class<>const&>::value);
    
    return 0;
}

