
struct Color
{
    Color(int r_ = 0, int g_ = 0, int b_ = 0):
        r(r_), g(g_), b(b_)
    {}        
    Color( const Color &c):
        r(c.r), g(c.g), b(c.b)
    {}
    int r;
    int g;
    int b;
};

const Color black = Color(0, 0, 0);
const Color red = Color(255, 0, 0);
const Color green = Color(0, 255, 0);
const Color blue = Color(0, 0, 255);
Color in_use = black;
