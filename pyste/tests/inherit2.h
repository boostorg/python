namespace inherit2 {

struct A
{
    int x;
    int getx() { return x; }
};

struct B : A
{
    int y;
    int gety() { return y; }
};

struct C : B
{
    int z;
    int getz() { return z; }
};

struct D : C
{
    int w;
    int getw() { return w; }
};

}
