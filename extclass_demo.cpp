//  (C) Copyright David Abrahams 2000. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
//  The author gratefully acknowleges the support of Dragon Systems, Inc., in
//  producing this work.
#include "extclass_demo.h"
#include "class_wrapper.h"
#include <stdio.h> // used for portability on broken compilers

namespace extclass_demo {

FooCallback::FooCallback(PyObject* self, int x)
    : Foo(x), m_self(self)
{
}

int FooCallback::add_len(const char* x) const
{
    // Try to call the "add_len" method on the corresponding Python object.
    return py::Callback<int>::call_method(m_self, "add_len", x);
}

// A function which Python can call in case bar is not overridden from
// Python. In true Python style, we use a free function taking an initial self
// parameter. This function anywhere needn't be a static member of the callback
// class. The only reason to do it this way is that Foo::add_len is private, and
// FooCallback is already a friend of Foo.
int FooCallback::default_add_len(const Foo* self, const char* x)
{
    // Don't forget the Foo:: qualification, or you'll get an infinite
    // recursion!
    return self->Foo::add_len(x);
}
    
// Since Foo::pure() is pure virtual, we don't need a corresponding
// default_pure(). A failure to override it in Python will result in an
// exception at runtime when pure() is called.
const char* FooCallback::pure() const
{
    return py::Callback<const char*>::call_method(m_self, "pure");
}

// The initializer for ExtensionClass<Foo,FooCallback> is entirely optional. It
// only affects the way that instances of this class _print_ in Python. If you
// need an absolutely predictable name for the type, use the
// initializer. Otherwise, C++ will generate an implementation-dependent
// representation of the type name, usually something like "class
// extclass_demo::Foo". I've supplied it here in part so that I can write
// doctests that exactly anticipate the generated error messages.
Foo::PythonClass::PythonClass()
    : py::ExtensionClass<Foo,FooCallback>("Foo") // optional
{
    def(py::Constructor<int>());
    def(&Foo::mumble, "mumble");
    def(&Foo::set, "set");
    def(&Foo::call_pure, "call_pure");
    def(&Foo::call_add_len, "call_add_len");

    // This is the way we add a virtual function that has a default implementation.
    def(&Foo::add_len, "add_len", &FooCallback::default_add_len);
    
    // Since pure() is pure virtual, we are leaving it undefined.
}

BarPythonClass::BarPythonClass()
    : py::ExtensionClass<Bar>("Bar") // optional
{
    def(py::Constructor<int, int>());
    def(&Bar::first, "first");
    def(&Bar::second, "second");
    def(&Bar::pass_baz, "pass_baz");
}

BazPythonClass::BazPythonClass()
    : py::ExtensionClass<Baz>("Baz") // optional
{
    def(py::Constructor<py::Void>());
    def(&Baz::pass_bar, "pass_bar");
    def(&Baz::clone, "clone");
    def(&Baz::create_foo, "create_foo");
    def(&Baz::get_foo_value, "get_foo_value");
    def(&Baz::eat_baz, "eat_baz");
}

StringMapPythonClass::StringMapPythonClass()
    : py::ExtensionClass<StringMap >("StringMap")
{
    def(py::Constructor<py::Void>());
    def(&StringMap::size, "__len__");
    def(&get_item, "__getitem__");
    def(&set_item, "__setitem__");
    def(&del_item, "__delitem__");
}

int get_first(const IntPair& p)
{
    return p.first;
}

void set_first(IntPair& p, int value)
{
    p.first = -value;
}

void del_first(const IntPair&)
{
    PyErr_SetString(PyExc_AttributeError, "first can't be deleted!");
    throw py::ErrorAlreadySet();
}

IntPairPythonClass::IntPairPythonClass()
    : py::ExtensionClass<IntPair>("IntPair")
{
    def(py::Constructor<int, int>());
    def(&getattr, "__getattr__");
    def(&setattr, "__setattr__");
    def(&delattr, "__delattr__");
    def(&get_first, "__getattr__first__");
    def(&set_first, "__setattr__first__");
    def(&del_first, "__delattr__first__");
}

void IntPairPythonClass::setattr(IntPair& x, const std::string& name, int value)
{
    if (name == "second")
    {
        x.second = value;
    }
    else
    {
        PyErr_SetString(PyExc_AttributeError, name.c_str());
        throw py::ErrorAlreadySet();
    }
}

void IntPairPythonClass::delattr(IntPair&, const char*)
{
    PyErr_SetString(PyExc_AttributeError, "Attributes can't be deleted!");
    throw py::ErrorAlreadySet();
}

int IntPairPythonClass::getattr(const IntPair& p, const std::string& s)
{
    if (s == "second")
    {
        return p.second;
    }
    else
    {
        PyErr_SetString(PyExc_AttributeError, s.c_str());
        throw py::ErrorAlreadySet();
    }
#if defined(__MWERKS__) && __MWERKS__ <= 0x6000
    return 0;
#endif
}

namespace { namespace file_local {
void throw_key_error_if_end(const StringMap& m, StringMap::const_iterator p, std::size_t key)
{
    if (p == m.end())
    {
		PyErr_SetObject(PyExc_KeyError, py::converters::to_python(key));
        throw py::ErrorAlreadySet();
    }
}
}} // namespace <anonymous>::file_local

const std::string& StringMapPythonClass::get_item(const StringMap& m, std::size_t key)
{
    const StringMap::const_iterator p = m.find(key);
    file_local::throw_key_error_if_end(m, p, key);
    return p->second;
}

void StringMapPythonClass::set_item(StringMap& m, std::size_t key, const std::string& value)
{
    m[key] = value;
}

void StringMapPythonClass::del_item(StringMap& m, std::size_t key)
{
    const StringMap::iterator p = m.find(key);
    file_local::throw_key_error_if_end(m, p, key);
    m.erase(p);
}

//
// Show that polymorphism can work. a DerivedFromFoo object will be passed to
// Python in a smart pointer object.
//
class DerivedFromFoo : public Foo
{
public:
    DerivedFromFoo(int x) : Foo(x) {}
    
private:
    const char* pure() const
        { return "this was never pure!"; }
    
    int add_len(const char*) const
        { return 1000; }
};

//
// function implementations
//

IntPair make_pair(int x, int y)
{
    return std::make_pair(x, y);
}

const char* Foo::mumble()
{
    return "mumble";
}

void Foo::set(long x)
{
    m_x = x;
}

const char* Foo::call_pure()
{
    return this->pure();
}

int Foo::call_add_len(const char* s) const
{
    return this->add_len(s);
}

int Foo::add_len(const char* s) const         // sum the held value and the length of s
{
    return PY_CSTD_::strlen(s) + static_cast<int>(m_x);
}

boost::shared_ptr<Foo> Baz::create_foo()
{
    return boost::shared_ptr<Foo>(new DerivedFromFoo(0));
}

// We can accept smart pointer parameters
int Baz::get_foo_value(boost::shared_ptr<Foo> foo)
{
    return foo->call_add_len("");
}

// Show what happens in python when we take ownership from an auto_ptr
void Baz::eat_baz(std::auto_ptr<Baz> baz)
{
    baz->clone(); // just do something to show that it is valid.
}

Baz Bar::pass_baz(Baz b)
{
    return b;
}

std::string stringpair_repr(const StringPair& sp)
{
    return "('" + sp.first + "', '" + sp.second + "')";
}

int stringpair_compare(const StringPair& sp1, const StringPair& sp2)
{
    return sp1 < sp2 ? -1 : sp2 < sp1 ? 1 : 0;
}

py::String range_str(const Range& r)
{
    char buf[200];
    sprintf(buf, "(%d, %d)", r.m_start, r.m_finish);
    return py::String(buf);
}

int range_compare(const Range& r1, const Range& r2)
{
    int d = r1.m_start - r2.m_start;
    if (d == 0)
        d = r1.m_finish - r2.m_finish;
    return d;
}

long range_hash(const Range& r)
{
    return r.m_start * 123 + r.m_finish;
}

/************************************************************/
/*                                                          */
/*           some functions to test overloading             */
/*                                                          */
/************************************************************/

static std::string testVoid()
{
   return std::string("Hello world!");  
}

static int testInt(int i)
{
   return i;
}

static std::string testString(std::string i)
{
   return i;
}

static int test2(int i1, int i2)
{
    return i1+i2;
}

static int test3(int i1, int i2, int i3)
{
    return i1+i2+i3;
}

static int test4(int i1, int i2, int i3, int i4)
{
    return i1+i2+i3+i4;
}

static int test5(int i1, int i2, int i3, int i4, int i5)
{
    return i1+i2+i3+i4+i5;
}

/************************************************************/
/*                                                          */
/*               a class to test overloading                */
/*                                                          */
/************************************************************/

struct OverloadTest
{
    OverloadTest(): x_(1000) {}
    OverloadTest(int x): x_(x) {}
    OverloadTest(int x,int y): x_(x+y) { }
    OverloadTest(int x,int y,int z): x_(x+y+z) {}
    OverloadTest(int x,int y,int z, int a): x_(x+y+z+a) {}
    OverloadTest(int x,int y,int z, int a, int b): x_(x+y+z+a+b) {}
    
    int x() const { return x_; }
    void setX(int x) { x_ = x; }

    int p1(int x) { return x;  }
    int p2(int x, int y) { return x + y; }
    int p3(int x, int y, int z) { return x + y + z; }
    int p4(int x, int y, int z, int a) { return x + y + z + a; }
    int p5(int x, int y, int z, int a, int b) { return x + y + z + a + b; }
  private:
    int x_;
};

static int getX(OverloadTest * u)
{
    return u->x();
}

/************************************************************/
/*                                                          */
/*                       init the module                    */
/*                                                          */
/************************************************************/

void init_module(py::Module& m)
{
    m.add(new Foo::PythonClass);
    m.add(new BarPythonClass);
    m.add(new BazPythonClass);
    m.add(new StringMapPythonClass);
    m.add(new IntPairPythonClass);
    m.def(make_pair, "make_pair");
    m.add(new CompareIntPairPythonClass);

    py::ClassWrapper<StringPair> string_pair(m, "StringPair");
    string_pair.def(py::Constructor<std::string, std::string>());
    string_pair.def_readonly(&StringPair::first, "first");
    string_pair.def_read_write(&StringPair::second, "second");
    string_pair.def(&stringpair_repr, "__repr__");
    string_pair.def(&stringpair_compare, "__cmp__");
    m.def(first_string, "first_string");
    m.def(second_string, "second_string");

    py::ClassWrapper<Range> range(m, "Range");
    range.def(py::Constructor<int>());
    range.def(py::Constructor<int, int>());
    range.def((void (Range::*)(std::size_t))&Range::length, "__len__");
    range.def((std::size_t (Range::*)() const)&Range::length, "__len__");
    range.def(&Range::operator[], "__getitem__");
    range.def(&Range::slice, "__getslice__");
    range.def(&range_str, "__str__");
    range.def(&range_compare, "__cmp__");
    range.def(&range_hash, "__hash__");
    range.def_readonly(&Range::m_start, "start");
    range.def_readonly(&Range::m_finish, "finish");
    
    m.def(&testVoid, "overloaded");
    m.def(&testInt, "overloaded");
    m.def(&testString, "overloaded");
    m.def(&test2, "overloaded");
    m.def(&test3, "overloaded");
    m.def(&test4, "overloaded");
    m.def(&test5, "overloaded");

    py::ClassWrapper<OverloadTest> over(m, "OverloadTest");
    over.def(py::Constructor<>());
    over.def(py::Constructor<OverloadTest const &>());
    over.def(py::Constructor<int>());
    over.def(py::Constructor<int, int>());
    over.def(py::Constructor<int, int, int>());
    over.def(py::Constructor<int, int, int, int>());
    over.def(py::Constructor<int, int, int, int, int>());
    over.def(&getX, "getX");
    over.def(&OverloadTest::setX, "setX");
    over.def(&OverloadTest::x, "overloaded");
    over.def(&OverloadTest::p1, "overloaded");
    over.def(&OverloadTest::p2, "overloaded");
    over.def(&OverloadTest::p3, "overloaded");
    over.def(&OverloadTest::p4, "overloaded");
    over.def(&OverloadTest::p5, "overloaded");
    
}

void init_module()
{
    py::Module demo("demo");
    init_module(demo);

    // Just for giggles, add a raw metaclass.
    demo.add(new py::MetaClass<py::Instance>);
}

extern "C"
#ifdef _WIN32
__declspec(dllexport)
#endif
void initdemo()
{
    try {
        extclass_demo::init_module();
    }
    catch(...) {
        py::handle_exception();
    } // Need a way to report other errors here
}

CompareIntPairPythonClass::CompareIntPairPythonClass()
    : py::ExtensionClass<CompareIntPair>("CompareIntPair")
{
    def(py::Constructor<py::Void>());
    def(&CompareIntPair::operator(), "__call__");
}

} // namespace extclass_demo


#if defined(_WIN32)
# include <windows.h>
extern "C" BOOL WINAPI DllMain ( HINSTANCE hInst, DWORD wDataSeg, LPVOID lpvReserved );

# ifdef PY_COMPILER_IS_MSVC
extern "C" void structured_exception_translator(unsigned int, EXCEPTION_POINTERS*)
{
    throw;
}
# endif

BOOL WINAPI DllMain(
    HINSTANCE,  //hDllInst
    DWORD fdwReason,
    LPVOID  // lpvReserved
    )
{
# ifdef PY_COMPILER_IS_MSVC
    _set_se_translator(structured_exception_translator);
#endif
    return 1;
    (void)fdwReason; // warning suppression.
}
#endif // _WIN32
