//  (C) Copyright David Abrahams 2000. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
//  The author gratefully acknowleges the support of Dragon Systems, Inc., in
//  producing this work.

#ifndef OBJECTS_DWA051100_H_
# define OBJECTS_DWA051100_H_

# include "wrap_python.h"
# include "pyconfig.h"
# include "pyptr.h"
# include "boost/operators.hpp"
# include <utility>

namespace py {

class Object
{
 public:
    explicit Object(Ptr p);
    
    // Return a reference to the held object
    Ptr reference() const;

    // Return a raw pointer to the held object
    PyObject* get() const;
    
 private:
    Ptr m_p;
};

class Tuple : public Object
{
 public:
    Tuple(std::size_t n = 0);
    explicit Tuple(Ptr p);

    template <class First, class Second>
    Tuple(const std::pair<First,Second>& x)
        : Object(Ptr(PyTuple_New(2)))
    {
        set_item(0, Ptr(to_python(x.first)));
        set_item(1, Ptr(to_python(x.second)));
    }
    
    template <class First, class Second>
    Tuple(const First& first, const Second& second)
        : Object(Ptr(PyTuple_New(2)))
    {
        set_item(0, Ptr(to_python(first)));
        set_item(1, Ptr(to_python(second)));
    }
    
    template <class First, class Second, class Third>
    Tuple(const First& first, const Second& second, const Third& third)
        : Object(Ptr(PyTuple_New(3)))
    {
        set_item(0, Ptr(to_python(first)));
        set_item(1, Ptr(to_python(second)));
        set_item(2, Ptr(to_python(third)));
    }
    
    static PyTypeObject* type_object();
    static bool accepts(Ptr p);
    std::size_t size() const;
    Ptr operator[](std::size_t pos) const;

    void set_item(std::size_t pos, const Ptr& rhs);
    Tuple slice(int low, int high) const;

    friend Tuple operator+(const Tuple&, const Tuple&);
    Tuple& operator+=(const Tuple& rhs);
};

class List : public Object
{
    struct Proxy;
    struct SliceProxy;
 public:
    explicit List(Ptr p);
    explicit List(std::size_t sz = 0);
    static PyTypeObject* type_object();
    static bool accepts(Ptr p);
    std::size_t size();
    Ptr operator[](std::size_t pos) const;
    Proxy operator[](std::size_t pos);
    Ptr get_item(std::size_t pos) const;
    void set_item(std::size_t pos, Ptr);
    void set_item(std::size_t pos, Object);
    void insert(std::size_t index, Ptr item);
    void push_back(Ptr item);
    void append(Ptr item);
    List slice(int low, int high) const;
    SliceProxy slice(int low, int high);
    void sort();
    void reverse();
    Tuple as_tuple() const;
};

class String : public Object
{
 public:
    // Construct from an owned PyObject*.
    // Precondition: p must point to a python string.
    explicit String(Ptr p);
    explicit String(const char* s);
    String(const char* s, std::size_t length);
    String(const String& rhs);

    enum Interned { interned };
    String(const char* s, Interned);
#if 0
    String(const char* s, std::size_t length, Interned);
#endif
    
    // Get the type object for Strings
    static PyTypeObject* type_object();

    // Return true if the given object is a python String
    static bool accepts(Ptr o);

    // Return the length of the string.
    std::size_t size() const;

    // Returns a null-terminated representation of the contents of string.
    // The pointer refers to the internal buffer of string, not a copy.
    // The data must not be modified in any way. It must not be de-allocated. 
    const char* c_str() const;

    String& operator+=(const String& rhs);
    friend String operator+(String x, String y);
    String& operator+=(const char* rhs);
    friend String operator+(String x, const char* y);
    friend String operator+(const char* x, String y);

    void intern(); // UNTESTED!!

    friend String operator%(const String& format, const Tuple& args);
};

class Dict : public Object
{
 private:
    struct Proxy;
    
 public:
    explicit Dict(Ptr p);
    Dict();
    void clear();

    static PyTypeObject* type_object();
    static bool accepts(Ptr p);
    
 public:
    Proxy operator[](Ptr key);
    Ptr operator[](Ptr key) const;

    Ptr get_item(const Ptr& key, const Ptr& default_ = Ptr()) const;
    void set_item(const Ptr& key, const Ptr& value);
        
    void erase(Ptr key);

    Proxy operator[](const Object& key);
    Ptr operator[](const Object& key) const;

    Ptr get_item(const Object& key, Ptr default_ = Ptr()) const;
    void set_item(const Object& key, const Ptr& value);
        
    void erase(const Object& key);

    Ptr items() const;
    Ptr keys() const;
    Ptr values() const;

    std::size_t size() const;
    // TODO: iterator support
};

struct Dict::Proxy
{
    const Ptr& operator=(const Ptr& rhs);
    operator Ptr() const;
 private:
    friend class Dict;
    Proxy(const Ptr& dict, const Ptr& key);
 private:
    Ptr m_dict;
    Ptr m_key;
};

struct List::Proxy
{
    const Ptr& operator=(const Ptr& rhs);
    operator Ptr() const;
 private:
    friend class List;
    Proxy(const Ptr& list, std::size_t index);
 private:
    List m_list;
    std::size_t m_index;
};

struct List::SliceProxy
{
    const List& operator=(const List& rhs);
    operator Ptr() const;
    operator List() const;
    std::size_t size();
    Ptr operator[](std::size_t pos) const;
 private:
    friend class List;
    SliceProxy(const Ptr& list, int low, int high);
 private:
    Ptr m_list;
    int m_low, m_high;
};

#ifdef PY_NO_INLINE_FRIENDS_IN_NAMESPACE
} // Back to the global namespace for this GCC bug
#endif

PyObject* to_python(const py::Tuple&);
py::Tuple from_python(PyObject* p, py::Type<py::Tuple>);

inline py::Tuple from_python(PyObject* p, py::Type<const py::Tuple&>)
{
    return from_python(p, py::Type<py::Tuple>());
}

PyObject* to_python(const py::List&);
py::List from_python(PyObject* p, py::Type<py::List>);

inline py::List from_python(PyObject* p, py::Type<const py::List&>)
{
    return from_python(p, py::Type<py::List>());
}

PyObject* to_python(const py::String&);
py::String from_python(PyObject* p, py::Type<py::String>);

inline py::String from_python(PyObject* p, py::Type<const py::String&>)
{
    return from_python(p, py::Type<py::String>());
}

PyObject* to_python(const py::Dict&);
py::Dict from_python(PyObject* p, py::Type<py::Dict>);

inline py::Dict from_python(PyObject* p, py::Type<const py::Dict&>)
{
    return from_python(p, py::Type<py::Dict>());
}

#ifdef PY_NO_INLINE_FRIENDS_IN_NAMESPACE
namespace py {
#endif

}
#endif
