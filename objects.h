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
    explicit Tuple(std::size_t n = 0);
    explicit Tuple(Ptr p);

    template <class First, class Second>
    Tuple(const std::pair<First,Second>& x)
        : Object(Ptr(PyTuple_New(2)))
    {
        set_item(0, x.first);
        set_item(1, x.second);
    }
    
    template <class First, class Second>
    Tuple(const First& first, const Second& second)
        : Object(Ptr(PyTuple_New(2)))
    {
        set_item(0, first);
        set_item(1, second);
    }
    
    template <class First, class Second, class Third>
    Tuple(const First& first, const Second& second, const Third& third)
        : Object(Ptr(PyTuple_New(3)))
    {
        set_item(0, first);
        set_item(1, second);
        set_item(2, third);
    }
    
    template <class First, class Second, class Third, class Fourth>
    Tuple(const First& first, const Second& second, const Third& third, const Fourth& fourth)
        : Object(Ptr(PyTuple_New(4)))
    {
        set_item(0, first);
        set_item(1, second);
        set_item(2, third);
        set_item(3, fourth);
    }
    
    static PyTypeObject* type_object();
    static bool accepts(Ptr p);
    std::size_t size() const;
    Ptr operator[](std::size_t pos) const;

    template <class T>
    void set_item(std::size_t pos, const T& rhs)
    {
        this->set_item(pos, make_ptr(rhs));
    }
    
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

    template <class T>
    void set_item(std::size_t pos, const T& x)
        { this->set_item(pos, make_ptr(x)); }
    void set_item(std::size_t pos, const Ptr& );
    
//    void set_item(std::size_t pos, const Object& );

    template <class T>
    void insert(std::size_t index, const T& x)
        { this->insert(index, make_ptr(x)); }
    void insert(std::size_t index, const Ptr& item);

    template <class T>
    void push_back(const T& item)
        { this->push_back(make_ptr(item)); }
    void push_back(const Ptr& item);
    
    template <class T>
    void append(const T& item)
        { this->append(make_ptr(item)); }
    void append(const Ptr& item);
    
    List slice(int low, int high) const;
    SliceProxy slice(int low, int high);
    void sort();
    void reverse();
    Tuple as_tuple() const;
};

class String
    : public Object, public boost::multipliable2<String, unsigned int>
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

    String& operator*=(unsigned int repeat_count);
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
    template <class Key>
    Proxy operator[](const Key& key)
        { return this->operator[](make_ptr(key)); }
    Proxy operator[](Ptr key);
    
    template <class Key>
    Ptr operator[](const Key& key) const
        { return this->operator[](make_ptr(key)); }
    Ptr operator[](Ptr key) const;

    template <class Key>
    Ptr get_item(const Key& key) const
        { return this->get_item(make_ptr(key)); }
    Ptr get_item(const Ptr& key) const;
    
    template <class Key, class Default>
    Ptr get_item(const Key& key, const Default& default_) const
        { return this->get_item(make_ptr(key), make_ptr(default_)); }
    Ptr get_item(const Ptr& key, const Ptr& default_) const;
    
    template <class Key, class Value>
    void set_item(const Key& key, const Value& value)
        { this->set_item(make_ptr(key), make_ptr(value)); }
    void set_item(const Ptr& key, const Ptr& value);

    template <class Key>
    void erase(const Key& key)
        { this->erase(make_ptr(key)); }
    void erase(Ptr key);

//    Proxy operator[](const Object& key);
//    Ptr operator[](const Object& key) const;

//    Ptr get_item(const Object& key, Ptr default_ = Ptr()) const;
//    void set_item(const Object& key, const Ptr& value);
        
//    void erase(const Object& key);

    List items() const;
    List keys() const;
    List values() const;

    std::size_t size() const;
    // TODO: iterator support
};

struct Dict::Proxy
{
    template <class T>
    const Ptr& operator=(const T& rhs)
        { return (*this) = make_ptr(rhs); }
    const Ptr& operator=(const Ptr& rhs);

    operator Ptr() const;
 private:
    friend class Dict;
    Proxy(const Ptr& dict, const Ptr& key);

    // This is needed to work around the very strange MSVC error report that the
    // return type of the built-in operator= differs from that of the ones
    // defined above. Couldn't hurt to make these un-assignable anyway, though.
    const Ptr& operator=(const Proxy&); // Not actually implemented
 private:
    Ptr m_dict;
    Ptr m_key;
};

struct List::Proxy
{
    template <class T>
    const Ptr& operator=(const T& rhs)
        { return (*this) = make_ptr(rhs); }
    const Ptr& operator=(const Ptr& rhs);
    
    operator Ptr() const;
    
 private:
    friend class List;
    Proxy(const Ptr& list, std::size_t index);
    
    // This is needed to work around the very strange MSVC error report that the
    // return type of the built-in operator= differs from that of the ones
    // defined above. Couldn't hurt to make these un-assignable anyway, though.
    const Ptr& operator=(const Proxy&); // Not actually implemented
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

} // namespace py

PY_BEGIN_CONVERSION_NAMESPACE

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

PY_END_CONVERSION_NAMESPACE

#endif // OBJECTS_DWA051100_H_
