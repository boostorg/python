//  (C) Copyright David Abrahams 2000. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
//  The author gratefully acknowleges the support of Dragon Systems, Inc., in
//  producing this work.

#ifndef EXTCLASS_DEMO_DWA052200_H_
# define EXTCLASS_DEMO_DWA052200_H_
//
// Example code demonstrating extension class usage
//

# include <boost/python/class_builder.hpp>
# include <boost/python/callback.hpp>
# include <boost/utility.hpp>
# include <cstring>
# include <iostream>
# include <cstddef>
# include <string>
# include <map>

namespace extclass_demo {

//
// example: Foo, Bar, and Baz are C++ classes we want to wrap.
//

class Foo                // prohibit copying, proving that it doesn't choke 
    : boost::noncopyable // our generation of to_python().
{
 public: // constructor/destructor
    Foo(int x) : m_x(x) {}
    virtual ~Foo() {}
    
 public: // non-virtual functions
    const char* mumble(); // mumble something
    void set(long x);     // change the held value

    // These two call virtual functions
    std::string call_pure();                    // call a pure virtual fuction
    int call_add_len(const char* s) const;      // virtual function with a default implementation

 private:
    // by default, sum the held value and the length of s
    virtual int add_len(const char* s) const;
    
    // Derived classes can do whatever they want here, but they must do something!
    virtual std::string pure() const = 0;     

 public: // friend declarations
    // If you have private virtual functions such as add_len which you want to
    // override in Python and have default implementations, they must be
    // accessible by the thing making the def() call on the extension_class (in
    // this case, the nested PythonClass itself), and by the C++ derived class
    // which is used to cause the Python callbacks (in this case,
    // FooCallback). See the definition of FooCallback::add_len()
    struct PythonClass;
    friend struct PythonClass;
    friend class FooCallback; 
    
 private:
    int m_x; // the held value
};

//
// Bar and Baz have mutually-recursive type conversion dependencies (see
// pass_xxx functions). I've done this to prove that it doesn't cause a
// problem for Python class definitions, which happen later.
//
// Bar and Baz functions are only virtual to increase the likelihood of a crash
// if I inadvertently use a pointer to garbage memory (a likely thing to test
// for considering the amount of type casting needed to translate to and from
// Python).
struct Baz;
struct Bar
{
    Bar(int x, int y) : m_first(x), m_second(y) {}
    virtual int first() const { return m_first; }
    virtual int second() const { return m_second; }
    virtual Baz pass_baz(Baz x);

    int m_first, m_second;
};

struct Baz
{
    virtual Bar pass_bar(const Bar& x) { return x; }

    // We can return smart pointers
    virtual std::auto_ptr<Baz> clone() { return std::auto_ptr<Baz>(new Baz(*this)); }

    // This illustrates creating a polymorphic derived class of Foo
    virtual boost::shared_ptr<Foo> create_foo();

    // We can accept smart pointer parameters
    virtual int get_foo_value(boost::shared_ptr<Foo>);

    // Show what happens in python when we take ownership from an auto_ptr
    virtual void eat_baz(std::auto_ptr<Baz>);
};

typedef std::map<std::size_t, std::string> StringMap;
typedef std::pair<int, int> IntPair;

IntPair make_pair(int, int);

typedef std::less<IntPair> CompareIntPair;
typedef std::pair<std::string, std::string> StringPair;

inline std::string first_string(const StringPair& x)
{
    return x.first;
}

inline std::string second_string(const StringPair& x)
{
    return x.second;
}

struct Range
{
    Range(int x)
        : m_start(x), m_finish(x) {}
    
    Range(int start, int finish)
        : m_start(start), m_finish(finish) {}
    
    std::size_t length() const
        { return m_finish < m_start ? 0 : m_finish - m_start; }

    void length(std::size_t new_length)
        { m_finish = m_start + new_length; }

    int operator[](std::size_t n)
        { return m_start + n; }

    Range slice(std::size_t start, std::size_t end)
    {
        if (start > length())
            start = length();
        if (end > length())
            end = length();
        return Range(m_start + start, m_start + end);
    }

    int m_start, m_finish;
};

////////////////////////////////////////////////////////////////////////
//                                                                    //
// Begin wrapping code. Usually this would live in a separate header. //
//                                                                    //
////////////////////////////////////////////////////////////////////////

// Since Foo has virtual functions which we want overriden in Python, we must
// derive FooCallback.
class FooCallback : public Foo
{
 public:
    // Note the additional constructor parameter "self", which is needed to
    // allow function overriding from Python.
    FooCallback(PyObject* self, int x);

    friend struct PythonClass; // give it access to the functions below
    
 private:  // implementations of Foo virtual functions that are overridable in python.    
    int add_len(const char* x) const;

    // A function which Python can call in case bar is not overridden from
    // Python. In true Python style, we use a free function taking an initial
    // self parameter. You can put this function anywhere; it needn't be a
    // static member of the wrapping class.
    static int default_add_len(const Foo* self, const char* x);
    
    // Since Foo::pure() is pure virtual, we don't need a corresponding
    // default_pure(). A failure to override it in Python will result in an
    // exception at runtime when pure() is called.
    std::string pure() const;

 private: // Required boilerplate if functions will be overridden
    PyObject* m_self; // No, we don't want a boost::python::ref here, or we'd get an ownership cycle.
};

// Define the Python base class
struct Foo::PythonClass : boost::python::class_builder<Foo, FooCallback> { PythonClass(boost::python::module_builder&); };

// No virtual functions on Bar or Baz which are actually supposed to behave
// virtually from C++, so we'll rely on the library to define a wrapper for
// us. Even so, Python class_t types for each type we're wrapping should be
// _defined_ here in a header where they can be seen by other extension class
// definitions, since it is the definition of the boost::python::class_builder<> that
// causes to_python/from_python conversion functions to be generated.
struct BarPythonClass : boost::python::class_builder<Bar> { BarPythonClass(boost::python::module_builder&); };
struct BazPythonClass : boost::python::class_builder<Baz> { BazPythonClass(boost::python::module_builder&); };

struct StringMapPythonClass
    : boost::python::class_builder<StringMap>
{
    StringMapPythonClass(boost::python::module_builder&);
    
    // These static functions implement the right argument protocols for
    // implementing the Python "special member functions" for mapping on
    // StringMap. Could just as easily be global functions.
    static const std::string& get_item(const StringMap& m, std::size_t key);
    static void set_item(StringMap& m, std::size_t key, const std::string& value);
    static void del_item(StringMap& m, std::size_t key);
};

struct IntPairPythonClass
    : boost::python::class_builder<IntPair>
{
    IntPairPythonClass(boost::python::module_builder&);
    
    // The following could just as well be a free function; it implements the
    // getattr functionality for IntPair.
    static int getattr(const IntPair&, const std::string& s);
    static void setattr(IntPair&, const std::string& name, int value);
    static void delattr(IntPair&, const char* name);
};

struct CompareIntPairPythonClass
    : boost::python::class_builder<CompareIntPair>
{
    CompareIntPairPythonClass(boost::python::module_builder&);
};

} // namespace extclass_demo

#endif // EXTCLASS_DEMO_DWA052200_H_
