namespace virtual_ {
    
struct C
{
public:
    virtual int f()
    {
        return f_abs();
    }

    virtual void bar(int) {}
    virtual void bar(char*) {}

    const char* get_name()
    {
        return name();
    }

protected:    
    virtual int f_abs() = 0;

private:    
    virtual const char* name() { return "C"; }
};

inline int call_f(C& c) { return c.f(); }

}
