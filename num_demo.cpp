#include "numeric.h"
#include "class_wrapper.h"

struct Int
{
    Int(int i) : i_(i) {}
    
    Int operator+(int const & r) const { return Int(i_ + r); }
    Int operator-(int const & r) const { return Int(i_ - r); }
    Int operator+(Int const & r) const { return Int(i_ + r.i_); }
    Int operator-(Int const & r) const { return Int(i_ - r.i_); }
    
    int i() const { return i_; }
    
    int i_;
};

Int operator+(int const & i, Int const & j) { return Int(i+j.i()); }
Int operator-(int const & i, Int const & j) { return Int(i-j.i()); }

ostream & operator<<(ostream & o, Int const & i)
{
    o << i.i();
    return o;
}

extern "C"
void initnum()
{
    try 
    {
        py::Module num("num");
        py::ClassWrapper<Int> int_class(num, "Int");
        int_class.def(py::Constructor<int>());
        int_class.def(py::Constructor<Int>());
        int_class.def(py::coerce_wrapped, "__coerce__");
        int_class.def(&Int::i, "i");
        
        num.def_numeric(int_class.get_extension_class(),
                        int_class.get_extension_class(), "__add__");
        num.def_numeric(int_class.get_extension_class(),
                        int_class.get_extension_class(), "__sub__");
        num.def_numeric(int_class.get_extension_class(), &PyInt_Type, "__add__");
        num.def_numeric(&PyInt_Type, int_class.get_extension_class(), "__add__");
        
    }
    catch(...) 
    {
        py::handle_exception();
    } // Need a way to report other errors here
}

