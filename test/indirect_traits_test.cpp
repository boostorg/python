//#include <stdio.h>
#include <cassert>
#include <boost/python/detail/indirect_traits.hpp>

//#define print(expr) printf("%s ==> %s\n", #expr, expr)

int main()
{
using namespace boost::python::detail;

    assert(is_reference_to_pointer<int*&>::value);
    assert(is_reference_to_pointer<int* const&>::value);
    assert(is_reference_to_pointer<int*volatile&>::value);
    assert(is_reference_to_pointer<int*const volatile&>::value);
    
    assert(!is_reference_to_pointer<int const volatile>::value);
    assert(!is_reference_to_pointer<int>::value);
    assert(!is_reference_to_pointer<int*>::value);

    assert(!is_reference_to_const<int*&>::value);
    assert(is_reference_to_const<int* const&>::value);
    assert(!is_reference_to_const<int*volatile&>::value);
    assert(is_reference_to_const<int*const volatile&>::value);
    
    assert(!is_reference_to_const<int const volatile>::value);
    assert(!is_reference_to_const<int>::value);
    assert(!is_reference_to_const<int*>::value);

    assert(is_reference_to_non_const<int*&>::value);
    assert(!is_reference_to_non_const<int* const&>::value);
    assert(is_reference_to_non_const<int*volatile&>::value);
    assert(!is_reference_to_non_const<int*const volatile&>::value);
    
    assert(!is_reference_to_non_const<int const volatile>::value);
    assert(!is_reference_to_non_const<int>::value);
    assert(!is_reference_to_non_const<int*>::value);
    
    assert(!is_reference_to_volatile<int*&>::value);
    assert(!is_reference_to_volatile<int* const&>::value);
    assert(is_reference_to_volatile<int*volatile&>::value);
    assert(is_reference_to_volatile<int*const volatile&>::value);
    
    assert(!is_reference_to_volatile<int const volatile>::value);
    assert(!is_reference_to_volatile<int>::value);
    assert(!is_reference_to_volatile<int*>::value);
    
    return 0;
}
