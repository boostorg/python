#include <boost/python.hpp>

using namespace boost::python;

struct X
{
    X( int value ) : m_value( value )
    { ++s_count; }
    
    X( const X &other ) : m_value( other.m_value )
    { ++s_count; }
    
    ~X() 
    { --s_count; }
        
    int get_value() const
    { return m_value; }
    
    void set_value(int new_value)
    { m_value = new_value; }
    
    static int get_instance_count()
    { return s_count; }
        
    int m_value;

    static int s_count;
};

int X::s_count = 0;

int get_X_instance_count()
{ return X::get_instance_count(); }



BOOST_PYTHON_MODULE(properties_ext)
{
    typedef return_value_policy<return_by_value> return_by_value_t;
    typedef return_internal_reference<> return_by_internal_reference_t;
    class_<X>("X", init<int>() )
        //defining read only property
        .add_property( "value_r", &X::get_value )
        //defining read \ write property 
        .add_property( "value_rw", &X::get_value, &X::set_value )
        //defining read \ write property using make_getter and make_setter
        .add_property( "value_direct", 
                        make_getter( &X::m_value, return_by_value_t() ),
                        make_setter( &X::m_value, return_by_internal_reference_t() ) )
        //defining read only property for static member
        .add_static_property( "instance_count", &X::get_instance_count )
        //defining read \ write property for static member using make_getter and make_setter
        .add_static_property( "instance_count_direct", 
                              make_getter( &X::s_count, return_by_value_t() ), 
                              make_setter( &X::s_count, return_by_internal_reference_t() ) )
        //defining class property using a global function
        .add_static_property( "instance_count_injected", &get_X_instance_count );
}

#include "module_tail.cpp"
