#include <string>

namespace basic {
    
struct C
{    
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
};

int call_f(C& c)
{
    return c.f();
}

int call_f(C& c, int x)
{
    return c.f(x);
} 

}
