
namespace virtual2 {

struct A
{
    virtual int f() { return 0; }
    virtual int f1() { return 10; }
};

struct B: A
{
    virtual int f() { return 1; }
    virtual int f2() { return 20; }
};

int call_fs(A*a)
{
    int r = a->f1();
    B* b = dynamic_cast<B*>(a);
    return r + b->f2();
}
    
int call_f(A* a)
{
    return a->f();
}
}
