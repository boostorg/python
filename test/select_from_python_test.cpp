#include <boost/python/converter/from_python.hpp>
//#include <cassert>
//#include <boost/type_traits.hpp>
#include <boost/python/converter/type_id.hpp>
#include <iostream>

int result;

#define ASSERT_SAME(T1,T2) \
       if (!is_same< T1, T2 >::value) { \
             std::cout << "*********************\n"; \
             std::cout << type_id< T1 >() << " != " << type_id< T2 >() << "\n"; \
             std::cout << "*********************\n"; \
             result = 1; \
       }

int main()
{
    using namespace boost::python::converter;
    using namespace boost;


    ASSERT_SAME(
        select_from_python<int>::type, rvalue_from_python<int>
        );
    
    ASSERT_SAME(
        select_from_python<int const>::type, rvalue_from_python<int const>
        );
    
    ASSERT_SAME(
        select_from_python<int volatile>::type, rvalue_from_python<int volatile>
        );

    ASSERT_SAME(
        select_from_python<int const volatile>::type, rvalue_from_python<int const volatile>
        );



    ASSERT_SAME(
        select_from_python<int*>::type, pointer_from_python<int*>
        );
    
    ASSERT_SAME(
        select_from_python<int const*>::type, pointer_from_python<int const*>
        );
    
    ASSERT_SAME(
        select_from_python<int volatile*>::type, pointer_from_python<int volatile*>
        );

    ASSERT_SAME(
        select_from_python<int const volatile*>::type, pointer_from_python<int const volatile*>
        );




    ASSERT_SAME(
        select_from_python<int&>::type, reference_from_python<int&>
        );
    
    ASSERT_SAME(
        select_from_python<int const&>::type, rvalue_from_python<int const&>
        );
    
    ASSERT_SAME(
        select_from_python<int volatile&>::type, reference_from_python<int volatile&>
        );

    ASSERT_SAME(
        select_from_python<int const volatile&>::type, reference_from_python<int const volatile&>
        );



    ASSERT_SAME(
        select_from_python<int*&>::type, reference_from_python<int*&>
        );
    
    ASSERT_SAME(
        select_from_python<int const*&>::type, reference_from_python<int const*&>
        );
    
    ASSERT_SAME(
        select_from_python<int volatile*&>::type, reference_from_python<int volatile*&>
        );

    ASSERT_SAME(
        select_from_python<int const volatile*&>::type, reference_from_python<int const volatile*&>
        );



    ASSERT_SAME(
        select_from_python<int* const&>::type, pointer_const_reference_from_python<int*const&>
        );
    
    ASSERT_SAME(
        select_from_python<int const* const&>::type, pointer_const_reference_from_python<int const*const&>
        );
    
    ASSERT_SAME(
        select_from_python<int volatile* const&>::type, pointer_const_reference_from_python<int volatile*const&>
        );

    ASSERT_SAME(
        select_from_python<int const volatile* const&>::type, pointer_const_reference_from_python<int const volatile*const&>
        );



    ASSERT_SAME(
        select_from_python<int*volatile&>::type, reference_from_python<int*volatile&>
        );
    
    ASSERT_SAME(
        select_from_python<int const*volatile&>::type, reference_from_python<int const*volatile&>
        );
    
    ASSERT_SAME(
        select_from_python<int volatile*volatile&>::type, reference_from_python<int volatile*volatile&>
        );

    ASSERT_SAME(
        select_from_python<int const volatile*volatile&>::type, reference_from_python<int const volatile*volatile&>
        );



    ASSERT_SAME(
        select_from_python<int*const volatile&>::type, reference_from_python<int*const volatile&>
        );
    
    ASSERT_SAME(
        select_from_python<int const*const volatile&>::type, reference_from_python<int const*const volatile&>
        );
    
    ASSERT_SAME(
        select_from_python<int volatile*const volatile&>::type, reference_from_python<int volatile*const volatile&>
        );

    ASSERT_SAME(
        select_from_python<int const volatile*const volatile&>::type, reference_from_python<int const volatile*const volatile&>
        );
    return result;
}
