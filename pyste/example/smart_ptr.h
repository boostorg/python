#include <memory>
#include <boost/shared_ptr.hpp>

namespace smart_ptr {
    
struct C
{
    int value;
};

struct D
{
    boost::shared_ptr<C> Get() { return ptr; }
    void Set( boost::shared_ptr<C> c ) { ptr = c; }
private:    
    boost::shared_ptr<C> ptr;
};

std::auto_ptr<D> New() { return std::auto_ptr<D>( new D() ); }
}
