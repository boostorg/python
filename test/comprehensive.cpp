//  (C) Copyright David Abrahams 2000. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
//  The author gratefully acknowleges the support of Dragon Systems, Inc., in
//  producing this work.

//  Revision History:
//  04 Mar 01  Changed name of extension module so it would work with DebugPython,
//             eliminated useless test that aggravated MSVC (David Abrahams)
#include "comprehensive.hpp"
#include <boost/python/class_builder.hpp>
#include <stdio.h> // used for portability on broken compilers
#include <math.h>  // for pow()
#include <boost/rational.hpp>

#if defined(__sgi) \
    && (   (defined(_COMPILER_VERSION) && _COMPILER_VERSION <= 730) \
        && !defined(__GNUC__))
inline double pow(int x, int y) { return pow(static_cast<double>(x), y); }
#endif

namespace bpl_test {

FooCallback::FooCallback(PyObject* self, int x)
    : Foo(x), m_self(self)
{
}

int FooCallback::add_len(const char* x) const
{
    // Try to call the "add_len" method on the corresponding Python object.
    return boost::python::callback<int>::call_method(m_self, "add_len", x);
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
std::string FooCallback::pure() const
{
    return boost::python::callback<std::string>::call_method(m_self, "pure");
}

Foo::PythonClass::PythonClass(boost::python::module_builder& m)
    : boost::python::class_builder<Foo,FooCallback>(m, "Foo")
{
    def(boost::python::constructor<int>());
    def(&Foo::mumble, "mumble");
    def(&Foo::set, "set");
    def(&Foo::call_pure, "call_pure");
    def(&Foo::call_add_len, "call_add_len");

    // This is the way we add a virtual function that has a default implementation.
    def(&Foo::add_len, "add_len", &FooCallback::default_add_len);
    
    // Since pure() is pure virtual, we are leaving it undefined.

    // And the nested classes.
    boost::python::class_builder<Foo::Foo_A> foo_a(*this, "Foo_A");
    foo_a.def(boost::python::constructor<>());
    foo_a.def(&Foo::Foo_A::mumble, "mumble");

    boost::python::class_builder<Foo::Foo_B> foo_b(get_extension_class(),
                                                   "Foo_B");
    foo_b.def(boost::python::constructor<>());
    foo_b.def(&Foo::Foo_B::mumble, "mumble");
}

BarPythonClass::BarPythonClass(boost::python::module_builder& m)
    : boost::python::class_builder<Bar>(m, "Bar")
{
    def(boost::python::constructor<int, int>());
    def(&Bar::first, "first");
    def(&Bar::second, "second");
    def(&Bar::pass_baz, "pass_baz");
}

BazPythonClass::BazPythonClass(boost::python::module_builder& m)
    : boost::python::class_builder<Baz>(m, "Baz") // optional
{
    def(boost::python::constructor<>());
    def(&Baz::pass_bar, "pass_bar");
    def(&Baz::clone, "clone");
    def(&Baz::create_foo, "create_foo");
    def(&Baz::get_foo_value, "get_foo_value");
    def(&Baz::eat_baz, "eat_baz");
}

StringMapPythonClass::StringMapPythonClass(boost::python::module_builder& m)
    : boost::python::class_builder<StringMap >(m, "StringMap")
{
    def(boost::python::constructor<>());
    // Some compilers make the target of this function
    // pointer the same type as the class in which it is defined (some
    // standard library class), instead of StringMap.
    def((std::size_t (StringMap::*)()const)&StringMap::size, "__len__");
    
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
    boost::python::throw_error_already_set();
}

IntPairPythonClass::IntPairPythonClass(boost::python::module_builder& m)
    : boost::python::class_builder<IntPair>(m, "IntPair")
{
    def(boost::python::constructor<int, int>());
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
        boost::python::throw_error_already_set();
    }
}

void IntPairPythonClass::delattr(IntPair&, const char*)
{
    PyErr_SetString(PyExc_AttributeError, "Attributes can't be deleted!");
    boost::python::throw_error_already_set();
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
        boost::python::throw_error_already_set();
    }
    return 0;
}

namespace { namespace file_local {
void throw_key_error_if_end(const StringMap& m, StringMap::const_iterator p, std::size_t key)
{
    if (p == m.end())
    {
        PyErr_SetObject(PyExc_KeyError, BOOST_PYTHON_CONVERSION::to_python(key));
        boost::python::throw_error_already_set();
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
    std::string pure() const
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

const char* Foo::Foo_A::mumble()
{
    return "mumble a";
}

const char* Foo::Foo_B::mumble()
{
    return "mumble b";
}

void Foo::set(long x)
{
    m_x = x;
}

std::string Foo::call_pure()
{
    return this->pure();
}

int Foo::call_add_len(const char* s) const
{
    return this->add_len(s);
}

int Foo::add_len(const char* s) const         // sum the held value and the length of s
{
    return BOOST_CSTD_::strlen(s) + static_cast<int>(m_x);
}

boost::shared_ptr<Foo> Baz::create_foo()
{
    return boost::shared_ptr<Foo>(new DerivedFromFoo(0));
}

// Used to check conversion to None
boost::shared_ptr<Foo> foo_factory(bool create)
{
    return boost::shared_ptr<Foo>(create ? new DerivedFromFoo(0) : 0);
}

// Used to check conversion from None
bool foo_ptr_is_null(Foo* p)
{
    return p == 0;
}

bool foo_shared_ptr_is_null(boost::shared_ptr<Foo> p)
{
    return p.get() == 0;
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

boost::python::string range_str(const Range& r)
{
    char buf[200];
    sprintf(buf, "(%d, %d)", r.m_start, r.m_finish);
    return boost::python::string(buf);
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

static int getX(OverloadTest* u)
{
    return u->x();
}


/************************************************************/
/*                                                          */
/*    classes to test base declarations and conversions     */
/*                                                          */
/************************************************************/

struct Dummy
{
    virtual ~Dummy() {}
    int dummy_;
};

struct Base
{
    virtual int x() const { return 999; };
    virtual ~Base() {}
};

// inherit Dummy so that the Base part of Concrete starts at an offset
// otherwise, typecast tests wouldn't be very meaningful
struct Derived1 : public Dummy, public Base
{
    Derived1(int x): x_(x) {}
    virtual int x() const { return x_; }
    
  private:
    int x_;
};

struct Derived2 : public Dummy, public Base
{
    Derived2(int x): x_(x) {}
    virtual int x() const { return x_; }
    
  private:
    int x_;
};

static int testUpcast(Base* b)
{
    return b->x();
}

static std::auto_ptr<Base> derived1Factory(int i)
{
    return std::auto_ptr<Base>(i < 0 ? 0 : new Derived1(i));
}

static std::auto_ptr<Base> derived2Factory(int i)
{
    return std::auto_ptr<Base>(new Derived2(i));
}

static int testDowncast1(Derived1* d)
{
    return d->x();
}

static int testDowncast2(Derived2* d)
{
    return d->x();
}

/************************************************************/
/*                                                          */
/*       test classes for interaction of overloading,       */
/*             base declarations,  and callbacks            */
/*                                                          */
/************************************************************/

struct CallbackTestBase
{
  virtual int testCallback(int i) { return callback(i); }
  virtual int callback(int i) = 0;
  virtual ~CallbackTestBase() {}
};

struct CallbackTest : public CallbackTestBase
{
  virtual int callback(int i) { return i + 1; }
  virtual std::string callbackString(std::string const & i) { return i + " 1"; }
};

struct CallbackTestCallback : public CallbackTest
{
  CallbackTestCallback(PyObject* self)
  : m_self(self)
  {}
  
  int callback(int x) 
  { 
    return boost::python::callback<int>::call_method(m_self, "callback", x); 
  }
  std::string callbackString(std::string const & x) 
  { 
    return boost::python::callback<std::string>::call_method(m_self, "callback", x); 
  }

  static int default_callback(CallbackTest* self, int x) 
  { 
    return self->CallbackTest::callback(x); 
  }
  static std::string default_callbackString(CallbackTest* self, std::string x) 
  { 
    return self->CallbackTest::callbackString(x); 
  }
  
  PyObject* m_self;
};

int testCallback(CallbackTestBase* b, int i)
{
    return b->testCallback(i);
}

/************************************************************/
/*                                                          */
/*       test classes for interaction of method lookup      */
/*               in the context of inheritance              */
/*                                                          */
/************************************************************/

struct A1 {
    virtual ~A1() {}
    virtual std::string overrideA1() const { return "A1::overrideA1"; }
    virtual std::string inheritA1() const { return "A1::inheritA1"; }
};

struct A2 {
    virtual ~A2() {}
    virtual std::string inheritA2() const { return "A2::inheritA2"; }
};

struct B1 : A1, A2 {
    std::string overrideA1() const { return "B1::overrideA1"; }
    virtual std::string overrideB1() const { return "B1::overrideB1"; }
};

struct B2 : A1, A2 {
    std::string overrideA1() const { return "B2::overrideA1"; }
    virtual std::string inheritB2() const { return "B2::inheritB2"; }
};

struct C : B1 {
    std::string overrideB1() const { return "C::overrideB1"; }
};

std::string call_overrideA1(const A1& a) { return a.overrideA1(); }
std::string call_overrideB1(const B1& b) { return b.overrideB1(); }
std::string call_inheritA1(const A1& a) { return a.inheritA1(); }

std::auto_ptr<A1> factoryA1asA1() { return std::auto_ptr<A1>(new A1); }
std::auto_ptr<A1> factoryB1asA1() { return std::auto_ptr<A1>(new B1); }
std::auto_ptr<A1> factoryB2asA1() { return std::auto_ptr<A1>(new B2); }
std::auto_ptr<A1> factoryCasA1() { return std::auto_ptr<A1>(new C); }
std::auto_ptr<A2> factoryA2asA2() { return std::auto_ptr<A2>(new A2); }
std::auto_ptr<A2> factoryB1asA2() { return std::auto_ptr<A2>(new B1); }
std::auto_ptr<B1> factoryB1asB1() { return std::auto_ptr<B1>(new B1); }
std::auto_ptr<B1> factoryCasB1() { return std::auto_ptr<B1>(new C); }

struct B_callback : B1 {
   B_callback(PyObject* self) : m_self(self) {}
   
   std::string overrideA1() const { return boost::python::callback<std::string>::call_method(m_self, "overrideA1"); }
   std::string overrideB1() const { return boost::python::callback<std::string>::call_method(m_self, "overrideB1"); }
   
   static std::string default_overrideA1(B1& x) { return x.B1::overrideA1(); }
   static std::string default_overrideB1(B1& x) { return x.B1::overrideB1(); }
   
   PyObject* m_self;
};

struct A_callback : A1 {
   A_callback(PyObject* self) : m_self(self) {}
   
   std::string overrideA1() const { return boost::python::callback<std::string>::call_method(m_self, "overrideA1"); }
   std::string inheritA1() const { return boost::python::callback<std::string>::call_method(m_self, "inheritA1"); }
   
   static std::string default_overrideA1(A1& x) { return x.A1::overrideA1(); }
   static std::string default_inheritA1(A1& x) { return x.A1::inheritA1(); }
   
   PyObject* m_self;
};

/************************************************************/
/*                                                          */
/*                         RawTest                          */
/*          (test passing of raw arguments to C++)          */
/*                                                          */
/************************************************************/

struct RawTest
{
    RawTest(int i) : i_(i) {}
    
    int i_;
};

PyObject* raw(boost::python::tuple const & args, boost::python::dictionary const & keywords);

int raw1(PyObject* args, PyObject* keywords)
{
    return PyTuple_Size(args) + PyDict_Size(keywords);
}

int raw2(boost::python::ref args, boost::python::ref keywords)
{
    return PyTuple_Size(args.get()) + PyDict_Size(keywords.get());
}



/************************************************************/
/*                                                          */
/*                           Ratio                          */
/*                                                          */
/************************************************************/

typedef boost::rational<int> Ratio;

boost::python::string ratio_str(const Ratio& r)
{
    char buf[200];
    
    if (r.denominator() == 1)
        sprintf(buf, "%d", r.numerator());
    else
        sprintf(buf, "%d/%d", r.numerator(), r.denominator());
    
    return boost::python::string(buf);
}

boost::python::string ratio_repr(const Ratio& r)
{
    char buf[200];
    sprintf(buf, "Rational(%d, %d)", r.numerator(), r.denominator());
    return boost::python::string(buf);
}

boost::python::tuple ratio_coerce(const Ratio& r1, int r2)
{
    return boost::python::tuple(r1, Ratio(r2));
}

// The most reliable way, across compilers, to grab the particular abs function
// we're interested in.
Ratio ratio_abs(const Ratio& r)
{
    return boost::abs(r);
}

// An experiment, to be integrated into the py_cpp library at some point.
template <class T>
struct StandardOps
{
    static T add(const T& x, const T& y) { return x + y; }
    static T sub(const T& x, const T& y) { return x - y; }
    static T mul(const T& x, const T& y) { return x * y; }
    static T div(const T& x, const T& y) { return x / y; }
    static T cmp(const T& x, const T& y) { return std::less<T>()(x, y) ? -1 : std::less<T>()(y, x) ? 1 : 0; }
};

// This helps us prove that we can now pass non-const reference parameters to constructors
struct Fubar {
    Fubar(Foo&) {}
    Fubar(int) {}
};

/************************************************************/
/*                                                          */
/*                          Int                             */
/*              this class tests operator export            */
/*                                                          */
/************************************************************/

#ifndef NDEBUG
int total_Ints = 0;
#endif

struct Int
{
    explicit Int(int i) : i_(i), j_(0) {
#ifndef NDEBUG
        ++total_Ints;
#endif
    }
    
#ifndef NDEBUG
    ~Int() { --total_Ints; }
    Int(const Int& rhs) : i_(rhs.i_), j_(rhs.j_) { ++total_Ints; }
#endif
    
    int i() const { return i_; }
    int j() const { return j_; }
    
    int i_;
    int j_;

    Int& operator +=(Int const& r) { ++j_; i_ += r.i_; return *this; }
    Int& operator -=(Int const& r) { ++j_; i_ -= r.i_; return *this; }
    Int& operator *=(Int const& r) { ++j_; i_ *= r.i_; return *this; }
    Int& operator /=(Int const& r) { ++j_; i_ /= r.i_; return *this; }
    Int& operator %=(Int const& r) { ++j_; i_ %= r.i_; return *this; }
    Int& ipow (Int const& r) { ++j_; 
                               int o=i_;
                               for (int k=1; k<r.i_; k++) i_ *= o;
                               return *this; }
    Int& operator <<=(Int const& r) { ++j_; i_ <<= r.i_; return *this; }
    Int& operator >>=(Int const& r) { ++j_; i_ >>= r.i_; return *this; }
    Int& operator &=(Int const& r) { ++j_; i_ &= r.i_; return *this; }
    Int& operator |=(Int const& r) { ++j_; i_ |= r.i_; return *this; }
    Int& operator ^=(Int const& r) { ++j_; i_ ^= r.i_; return *this; }
};

Int operator+(Int const & l, Int const & r) { return Int(l.i_ + r.i_); }
Int operator+(Int const & l, int const & r) { return Int(l.i_ + r); }
Int operator+(int const & l, Int const & r) { return Int(l + r.i_); }

Int operator-(Int const & l, Int const & r) { return Int(l.i_ - r.i_); }
Int operator-(Int const & l, int const & r) { return Int(l.i_ - r); }
Int operator-(int const & l, Int const & r) { return Int(l - r.i_); }
Int operator-(Int const & r) { return Int(- r.i_); }

Int mul(Int const & l, Int const & r) { return Int(l.i_ * r.i_); }
Int imul(Int const & l, int const & r) { return Int(l.i_ * r); }
Int rmul(Int const & r, int const & l) { return Int(l * r.i_); }

Int operator/(Int const & l, Int const & r) { return Int(l.i_ / r.i_); }

Int operator%(Int const & l, Int const & r) { return Int(l.i_ % r.i_); }

bool operator<(Int const & l, Int const & r) { return l.i_ < r.i_; }
bool operator<(Int const & l, int const & r) { return l.i_ < r; }
bool operator<(int const & l, Int const & r) { return l < r.i_; }

Int pow(Int const & l, Int const & r) { return Int(static_cast<int>(::pow(l.i_, r.i_))); }
Int powmod(Int const & l, Int const & r, Int const & m) { return Int((int)::pow(l.i_, r.i_) % m.i_); }
Int pow(Int const & l, int const & r) { return Int(static_cast<int>(::pow(l.i_, r))); }

std::ostream & operator<<(std::ostream & o, Int const & r) { return (o << r.i_); }

/************************************************************/
/*                                                          */
/* double tests from Mark Evans(<mark.evans@clarisay.com>)  */
/*                                                          */
/************************************************************/
double sizelist(boost::python::list list) { return list.size(); }
void vd_push_back(std::vector<double>& vd, const double& x)
{
    vd.push_back(x);
}

/************************************************************/
/*                                                          */
/*       What if I want to return a pointer?                */
/*                                                          */
/************************************************************/

//
// This example exposes the pointer by copying its referent
//
struct Record {
    Record(int x) : value(x){}
    int value;
};

const Record* get_record()
{
    static Record v(1234);
    return &v;
}

} // namespace bpl_test

namespace boost { namespace python {
  template class class_builder<bpl_test::Record>; // explicitly instantiate
}} // namespace boost::python

BOOST_PYTHON_BEGIN_CONVERSION_NAMESPACE
inline PyObject* to_python(const bpl_test::Record* p)
{
    return to_python(*p);
}
BOOST_PYTHON_END_CONVERSION_NAMESPACE

/************************************************************/
/*                                                          */
/*          Enums and non-method class attributes           */
/*                                                          */
/************************************************************/

namespace bpl_test {

struct EnumOwner
{
 public:
    enum enum_type { one = 1, two = 2, three = 3 };
    
    EnumOwner(enum_type a1, const enum_type& a2)
        : m_first(a1), m_second(a2) {}

    void set_first(const enum_type& x) { m_first = x; }
    void set_second(const enum_type& x) { m_second = x; }
    
    enum_type first() { return m_first; }
    enum_type second() { return m_second; }
 private:
    enum_type m_first, m_second;
};

}

namespace boost { namespace python {
  template class enum_as_int_converters<bpl_test::EnumOwner::enum_type>;
  using bpl_test::pow;
}} // namespace boost::python

// This is just a way of getting the converters instantiated
//struct EnumOwner_enum_type_Converters
//    : boost::python::py_enum_as_int_converters<EnumOwner::enum_type>
//{
//};

namespace bpl_test {

/************************************************************/
/*                                                          */
/*                       pickling support                   */
/*                                                          */
/************************************************************/
  class world
  {
    private:
      std::string country;
      int secret_number;
    public:
      world(const std::string& country) : secret_number(0) {
        this->country = country;
      }
      std::string greet() const { return "Hello from " + country + "!"; }
      std::string get_country() const { return country; }
      void set_secret_number(int number) { secret_number = number; }
      int get_secret_number() const { return secret_number; }
  };

  // Support for pickle.
  boost::python::tuple world_getinitargs(const world& w)
  {
      boost::python::tuple result(1);
      result.set_item(0, w.get_country());
      return result;
  }

  boost::python::tuple world_getstate(const world& w)
  {
      boost::python::tuple result(1);
      result.set_item(0, w.get_secret_number());
      return result;
  }

  void world_setstate(world& w, boost::python::tuple state)
  {
      if (state.size() != 1) {
          PyErr_SetString(PyExc_ValueError,
                          "Unexpected argument in call to __setstate__.");
          boost::python::throw_error_already_set();
      }
    
      const int number = BOOST_PYTHON_CONVERSION::from_python(state[0].get(), boost::python::type<int>());
      if (number != 42)
          w.set_secret_number(number);
  }

  // Test plain char converters.
  char get_plain_char() { return 'x'; }
  std::string use_plain_char(char c) { return std::string(3, c); }

  // This doesn't test anything but the compiler, since it has the same signature as the above.
  // Since MSVC is broken and gets the signature wrong, we'll skip it.
  std::string use_const_plain_char(
#if !defined(BOOST_MSVC) || BOOST_MSVC > 1300
      const 
#endif
      char c) { return std::string(5, c); }

  // Test std::complex<double> converters.
  std::complex<double> dpolar(double rho, double theta) {
    return std::polar(rho, theta);
  }
  double dreal(const std::complex<double>& c) { return c.real(); }
  double dimag(std::complex<double> c) { return c.imag(); }

  // Test std::complex<float> converters.
  std::complex<float> fpolar(float rho, float theta) {
    return std::polar(rho, theta);
  }
  double freal(const std::complex<float>& c) { return c.real(); }
  double fimag(std::complex<float> c) { return c.imag(); }

  // Wrappers for inplace operators.
  Int& int_iadd(Int& self, const Int& r) { self += r; return self; }
  Int& int_isub(Int& self, const Int& r) { self -= r; return self; }
  Int& int_imul(Int& self, const Int& r) { self *= r; return self; }
  Int& int_idiv(Int& self, const Int& r) { self /= r; return self; }
  Int& int_imod(Int& self, const Int& r) { self %= r; return self; }
  Int& int_ipow(Int& self, const Int& r) { self.ipow (r); return self; }
  Int& int_ilshift(Int& self, const Int& r) { self <<= r; return self; }
  Int& int_irshift(Int& self, const Int& r) { self >>= r; return self; }
  Int& int_iand(Int& self, const Int& r) { self &= r; return self; }
  Int& int_ior(Int& self, const Int& r) { self |= r; return self; }
  Int& int_ixor(Int& self, const Int& r) { self ^= r; return self; }

/************************************************************/
/*                                                          */
/*                       init the module                    */
/*                                                          */
/************************************************************/

void init_module(boost::python::module_builder& m)
{
    m.def(get_record, "get_record");
    boost::python::class_builder<Record> record_class(m, "Record");
    record_class.def_readonly(&Record::value, "value");
    
    m.def(sizelist, "sizelist");
    
    boost::python::class_builder<std::vector<double> >  vector_double(m, "vector_double");
    vector_double.def(boost::python::constructor<>());
    vector_double.def(vd_push_back, "push_back");
    
    boost::python::class_builder<Fubar> fubar(m, "Fubar");
    fubar.def(boost::python::constructor<Foo&>());
    fubar.def(boost::python::constructor<int>());

    Foo::PythonClass foo(m);
    BarPythonClass bar(m);
    BazPythonClass baz(m);
    StringMapPythonClass string_map(m);
    IntPairPythonClass int_pair(m);
    m.def(make_pair, "make_pair");
    CompareIntPairPythonClass compare_int_pair(m);

    boost::python::class_builder<StringPair> string_pair(m, "StringPair");
    string_pair.def(boost::python::constructor<std::string, std::string>());
    string_pair.def_readonly(&StringPair::first, "first");
    string_pair.def_read_write(&StringPair::second, "second");
    string_pair.def(&stringpair_repr, "__repr__");
    string_pair.def(&stringpair_compare, "__cmp__");
    m.def(first_string, "first_string");
    m.def(second_string, "second_string");

    // This shows the wrapping of a 3rd-party numeric type.
    boost::python::class_builder<boost::rational<int> > rational(m, "Rational");
    rational.def(boost::python::constructor<int, int>());
    rational.def(boost::python::constructor<int>());
    rational.def(boost::python::constructor<>());
    rational.def(StandardOps<Ratio>::add, "__add__");
    rational.def(StandardOps<Ratio>::sub, "__sub__");
    rational.def(StandardOps<Ratio>::mul, "__mul__");
    rational.def(StandardOps<Ratio>::div, "__div__");
    rational.def(StandardOps<Ratio>::cmp, "__cmp__");
    rational.def(ratio_coerce, "__coerce__");
    rational.def(ratio_str, "__str__");
    rational.def(ratio_repr, "__repr__");
    rational.def(ratio_abs, "__abs__");
    
    boost::python::class_builder<Range> range(m, "Range");
    range.def(boost::python::constructor<int>());
    range.def(boost::python::constructor<int, int>());
    range.def((std::size_t (Range::*)() const)&Range::length, "__len__");
    range.def((void (Range::*)(std::size_t))&Range::length, "__len__");
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

    boost::python::class_builder<OverloadTest> over(m, "OverloadTest");
    over.def(boost::python::constructor<>());
    over.def(boost::python::constructor<OverloadTest const &>());
    over.def(boost::python::constructor<int>());
    over.def(boost::python::constructor<int, int>());
    over.def(boost::python::constructor<int, int, int>());
    over.def(boost::python::constructor<int, int, int, int>());
    over.def(boost::python::constructor<int, int, int, int, int>());
    over.def(&getX, "getX");
    over.def(&OverloadTest::setX, "setX");
    over.def(&OverloadTest::x, "overloaded");
    over.def(&OverloadTest::p1, "overloaded");
    over.def(&OverloadTest::p2, "overloaded");
    over.def(&OverloadTest::p3, "overloaded");
    over.def(&OverloadTest::p4, "overloaded");
    over.def(&OverloadTest::p5, "overloaded");
    
    boost::python::class_builder<Base> base(m, "Base");
    base.def(&Base::x, "x");
    
    boost::python::class_builder<Derived1> derived1(m, "Derived1");    
    // this enables conversions between Base and Derived1
    // and makes wrapped methods of Base available 
    derived1.declare_base(base);
    derived1.def(boost::python::constructor<int>());

    boost::python::class_builder<Derived2> derived2(m, "Derived2");    
    // don't enable downcast from Base to Derived2 
    derived2.declare_base(base, boost::python::without_downcast);
    derived2.def(boost::python::constructor<int>());
    
    m.def(&testUpcast, "testUpcast");
    m.def(&derived1Factory, "derived1Factory");
    m.def(&derived2Factory, "derived2Factory");
    m.def(&testDowncast1, "testDowncast1");
    m.def(&testDowncast2, "testDowncast2");

    boost::python::class_builder<CallbackTestBase> callbackTestBase(m, "CallbackTestBase");
    callbackTestBase.def(&CallbackTestBase::testCallback, "testCallback");
    m.def(&testCallback, "testCallback");

    boost::python::class_builder<CallbackTest, CallbackTestCallback> callbackTest(m, "CallbackTest");
    callbackTest.def(boost::python::constructor<>());
    callbackTest.def(&CallbackTest::callback, "callback", 
                   &CallbackTestCallback::default_callback);
    callbackTest.def(&CallbackTest::callbackString, "callback", 
                   &CallbackTestCallback::default_callbackString);

    callbackTest.declare_base(callbackTestBase);     

    boost::python::class_builder<A1, A_callback> a1_class(m, "A1");
    a1_class.def(boost::python::constructor<>());
    a1_class.def(&A1::overrideA1, "overrideA1", &A_callback::default_overrideA1);
    a1_class.def(&A1::inheritA1, "inheritA1", &A_callback::default_inheritA1);

    boost::python::class_builder<A2> a2_class(m, "A2");
    a2_class.def(boost::python::constructor<>());
    a2_class.def(&A2::inheritA2, "inheritA2");

    boost::python::class_builder<B1, B_callback> b1_class(m, "B1");
    b1_class.declare_base(a1_class);  
    b1_class.declare_base(a2_class);  

    b1_class.def(boost::python::constructor<>());
    b1_class.def(&B1::overrideA1, "overrideA1", &B_callback::default_overrideA1); 
    b1_class.def(&B1::overrideB1, "overrideB1", &B_callback::default_overrideB1); 

    boost::python::class_builder<B2> b2_class(m, "B2");
    b2_class.declare_base(a1_class);  
    b2_class.declare_base(a2_class);  

    b2_class.def(boost::python::constructor<>());
    b2_class.def(&B2::overrideA1, "overrideA1"); 
    b2_class.def(&B2::inheritB2, "inheritB2"); 
    
    m.def(call_overrideA1, "call_overrideA1");    
    m.def(call_overrideB1, "call_overrideB1");    
    m.def(call_inheritA1, "call_inheritA1");    

    m.def(factoryA1asA1, "factoryA1asA1");    
    m.def(factoryB1asA1, "factoryB1asA1");    
    m.def(factoryB2asA1, "factoryB2asA1");    
    m.def(factoryCasA1, "factoryCasA1");    
    m.def(factoryA2asA2, "factoryA2asA2");    
    m.def(factoryB1asA2, "factoryB1asA2");    
    m.def(factoryB1asB1, "factoryB1asB1");    
    m.def(factoryCasB1, "factoryCasB1");    
    
    boost::python::class_builder<RawTest> rawtest_class(m, "RawTest");
    rawtest_class.def(boost::python::constructor<int>());
    rawtest_class.def_raw(&raw, "raw");
    
    m.def_raw(&raw, "raw");
    m.def_raw(&raw1, "raw1");
    m.def_raw(&raw2, "raw2");
    
    boost::python::class_builder<Int> int_class(m, "Int");
    int_class.def(boost::python::constructor<int>());
    int_class.def(&Int::i, "i");
    int_class.def(&Int::j, "j");

    // wrap homogeneous operators
    int_class.def(boost::python::operators<(boost::python::op_add | boost::python::op_sub | boost::python::op_neg | 
          boost::python::op_cmp | boost::python::op_str | boost::python::op_divmod | boost::python::op_pow )>());
    // export non-operator functions as homogeneous operators
    int_class.def(&mul, "__mul__");
    int_class.def(&powmod, "__pow__");

    // wrap heterogeneous operators (lhs: Int const &, rhs: int const &)
    int_class.def(boost::python::operators<(boost::python::op_add | boost::python::op_sub | boost::python::op_cmp | boost::python::op_pow)>(), 
                  boost::python::right_operand<int const & >());
    // export non-operator function as heterogeneous operator
    int_class.def(&imul, "__mul__");

    // wrap heterogeneous operators (lhs: int const &, rhs: Int const &)
    int_class.def(boost::python::operators<(boost::python::op_add | boost::python::op_sub | boost::python::op_cmp)>(), 
                  boost::python::left_operand<int const & >());
    // export non-operator function as heterogeneous reverse-argument operator
    int_class.def(&rmul, "__rmul__");

#if PYTHON_API_VERSION >= 1010
    // inplace operators.
    int_class.def(&int_iadd, "__iadd__");
    int_class.def(&int_isub, "__isub__");
    int_class.def(&int_imul, "__imul__");
    int_class.def(&int_idiv, "__idiv__");
    int_class.def(&int_imod, "__imod__");
    int_class.def(&int_ipow, "__ipow__");
    int_class.def(&int_ilshift, "__ilshift__");
    int_class.def(&int_irshift, "__irshift__");
    int_class.def(&int_iand, "__iand__");
    int_class.def(&int_ior, "__ior__");
    int_class.def(&int_ixor, "__ixor__");
#endif
    

    boost::python::class_builder<EnumOwner> enum_owner(m, "EnumOwner");
    enum_owner.def(boost::python::constructor<EnumOwner::enum_type, const EnumOwner::enum_type&>());
    enum_owner.def(&EnumOwner::set_first, "__setattr__first__");
    enum_owner.def(&EnumOwner::set_second, "__setattr__second__");
    enum_owner.def(&EnumOwner::first, "__getattr__first__");
    enum_owner.def(&EnumOwner::second, "__getattr__second__");
    enum_owner.add(PyInt_FromLong(EnumOwner::one), "one");
    enum_owner.add(PyInt_FromLong(EnumOwner::two), "two");
    enum_owner.add(PyInt_FromLong(EnumOwner::three), "three");

    // pickling support
    
    // Create the Python type object for our extension class.
    boost::python::class_builder<world> world_class(m, "world");

    // Add the __init__ function.
    world_class.def(boost::python::constructor<std::string>());
    // Add a regular member function.
    world_class.def(&world::greet, "greet");
    world_class.def(&world::get_secret_number, "get_secret_number");
    world_class.def(&world::set_secret_number, "set_secret_number");

    // Support for pickle.
    world_class.def(world_getinitargs, "__getinitargs__");
    world_class.def(world_getstate, "__getstate__");
    world_class.def(world_setstate, "__setstate__");

    // Test plain char converters.
    m.def(get_plain_char, "get_plain_char");
    m.def(use_plain_char, "use_plain_char");
    m.def(use_const_plain_char, "use_const_plain_char");

    // Test std::complex<double> converters.
    m.def(dpolar, "dpolar");
    m.def(dreal, "dreal");
    m.def(dimag, "dimag");

    // Test std::complex<float> converters.
    m.def(fpolar, "fpolar");
    m.def(freal, "freal");
    m.def(fimag, "fimag");

    // Test new null-pointer<->None conversions
    m.def(foo_factory, "foo_factory");
    m.def(foo_ptr_is_null, "foo_ptr_is_null");
    m.def(foo_shared_ptr_is_null, "foo_shared_ptr_is_null");
}

PyObject* raw(const boost::python::tuple& args, const boost::python::dictionary& keywords)
{
    if(args.size() != 2 || keywords.size() != 2)
    {
        PyErr_SetString(PyExc_TypeError, "wrong number of arguments");
        boost::python::throw_argument_error();
    }
    
    RawTest* first = BOOST_PYTHON_CONVERSION::from_python(args[0].get(), boost::python::type<RawTest*>());
    int second = BOOST_PYTHON_CONVERSION::from_python(args[1].get(), boost::python::type<int>());
    
    int third = BOOST_PYTHON_CONVERSION::from_python(keywords[boost::python::string("third")].get(), boost::python::type<int>());
    int fourth = BOOST_PYTHON_CONVERSION::from_python(keywords[boost::python::string("fourth")].get(), boost::python::type<int>());
    
    return BOOST_PYTHON_CONVERSION::to_python(first->i_ + second + third + fourth);
}

BOOST_PYTHON_MODULE(boost_python_test)
{
    boost::python::module_builder boost_python_test("boost_python_test");
    init_module(boost_python_test);

    // Just for giggles, add a raw metaclass.
    boost_python_test.add(new boost::python::meta_class<boost::python::instance>);
}

CompareIntPairPythonClass::CompareIntPairPythonClass(boost::python::module_builder& m)
    : boost::python::class_builder<CompareIntPair>(m, "CompareIntPair")
{
    def(boost::python::constructor<>());
    def(&CompareIntPair::operator(), "__call__");
}

} // namespace bpl_test


#if defined(_WIN32)
# ifdef __MWERKS__
#  pragma ANSI_strict off
# endif
# include <windows.h>
# ifdef __MWERKS__
#  pragma ANSI_strict reset
# endif
extern "C" BOOL WINAPI DllMain ( HINSTANCE hInst, DWORD wDataSeg, LPVOID lpvReserved );

# ifdef BOOST_MSVC
extern "C" void structured_exception_translator(unsigned int, EXCEPTION_POINTERS*)
#  if BOOST_MSVC > 1200
    throw(...)
#  endif 
{
    throw;
}
# endif

#ifndef NDEBUG
namespace boost { namespace python { namespace detail {
        extern int total_Dispatchers;
}}} // namespace boost::python::detail
#endif

BOOL WINAPI DllMain(
    HINSTANCE,  //hDllInst
    DWORD fdwReason,
    LPVOID  // lpvReserved
    )
{
# ifdef BOOST_MSVC
    _set_se_translator(structured_exception_translator);
#endif
    (void)fdwReason; // warning suppression.

#ifndef NDEBUG
    switch(fdwReason)
    {
    case DLL_PROCESS_DETACH:
        assert(bpl_test::total_Ints == 0);
    }
#endif
    
    return 1;
}
#endif // _WIN32
