
namespace virtual2 {

struct A
{
    virtual int f1() { return 10; }
};

struct B: A
{
    virtual int f2() { return 20; }
};

int call(A*a)
{
    int r = a->f1();
    B* b = dynamic_cast<B*>(a);
    return r + b->f2();
}
    
}
