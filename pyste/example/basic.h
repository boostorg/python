#ifndef BASIC_H
#define BASIC_H


#include <string>

namespace basic {
    
struct C
{    
    // test virtuallity
    C(): value(1), const_value(0) {}
    virtual int f(int x = 10)
    {
        return x*2;
    }    
    
    int foo(int x=1){
        return x+1;
    }

    const std::string& name() { return _name; }
    void set_name(const std::string& name) { _name = name; }
    std::string _name;

    // test data members
    static int static_value;
    static const int const_static_value;
    
    int value;
    const int const_value;

    // test static functions
    static int mul(int x=2, int y=3) { return x*y; }
};

inline int call_f(C& c)
{
    return c.f();
}

inline int call_f(C& c, int x)
{
    return c.f(x);
} 

inline int get_static()
{
    return C::static_value;
}

inline int get_value(C& c)
{
    return c.value;
}

}

#endif
