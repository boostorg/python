#include <string>

namespace basic {
    
struct C
{    
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
    static int static_value;
    static const int const_static_value;
    
    int value;
    const int const_value;
};

int C::static_value = 3;
const int C::const_static_value = 100;

int call_f(C& c)
{
    return c.f();
}

int call_f(C& c, int x)
{
    return c.f(x);
} 

int get_static()
{
    return C::static_value;
}

int get_value(C& c)
{
    return c.value;
}

}
