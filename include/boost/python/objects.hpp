//  (C) Copyright David Abrahams 2000. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
//  The author gratefully acknowleges the support of Dragon Systems, Inc., in
//  producing this work.

#ifndef OBJECTS_DWA051100_H_
# define OBJECTS_DWA051100_H_

# include <boost/python/detail/wrap_python.hpp>
# include <boost/python/detail/config.hpp>
# include <boost/python/reference.hpp>
# include "boost/operators.hpp"
# include <utility>

namespace boost { namespace python {

class object
{
 public:
    explicit object(ref p);
    
    // Return a reference to the held object
    ref reference() const;

    // Return a raw pointer to the held object
    PyObject* get() const;
    
 private:
    ref m_p;
};

class tuple : public object
{
 public:
    explicit tuple(std::size_t n = 0);
    explicit tuple(ref p);

    template <class First, class Second>
    tuple(const std::pair<First,Second>& x)
        : object(ref(PyTuple_New(2)))
    {
        set_item(0, x.first);
        set_item(1, x.second);
    }
    
    template <class First, class Second>
    tuple(const First& first, const Second& second)
        : object(ref(PyTuple_New(2)))
    {
        set_item(0, first);
        set_item(1, second);
    }
    
    template <class First, class Second, class Third>
    tuple(const First& first, const Second& second, const Third& third)
        : object(ref(PyTuple_New(3)))
    {
        set_item(0, first);
        set_item(1, second);
        set_item(2, third);
    }
    
    template <class First, class Second, class Third, class Fourth>
    tuple(const First& first, const Second& second, const Third& third, const Fourth& fourth)
        : object(ref(PyTuple_New(4)))
    {
        set_item(0, first);
        set_item(1, second);
        set_item(2, third);
        set_item(3, fourth);
    }
    
    static PyTypeObject* type_obj();
    static bool accepts(ref p);
    std::size_t size() const;
    ref operator[](std::size_t pos) const;

    template <class T>
    void set_item(std::size_t pos, const T& rhs)
    {
        this->set_item(pos, make_ref(rhs));
    }
    
    void set_item(std::size_t pos, const ref& rhs);
    
    tuple slice(int low, int high) const;

    friend tuple operator+(const tuple&, const tuple&);
    tuple& operator+=(const tuple& rhs);
};

class list : public object
{
    struct proxy;
    struct slice_proxy;
 public:
    explicit list(ref p);
    explicit list(std::size_t sz = 0);
    static PyTypeObject* type_obj();
    static bool accepts(ref p);
    std::size_t size();
    ref operator[](std::size_t pos) const;
    proxy operator[](std::size_t pos);
    ref get_item(std::size_t pos) const;

    template <class T>
    void set_item(std::size_t pos, const T& x)
        { this->set_item(pos, make_ref(x)); }
    void set_item(std::size_t pos, const ref& );
    
//    void set_item(std::size_t pos, const object& );

    template <class T>
    void insert(std::size_t index, const T& x)
        { this->insert(index, make_ref(x)); }
    void insert(std::size_t index, const ref& item);

    template <class T>
    void push_back(const T& item)
        { this->push_back(make_ref(item)); }
    void push_back(const ref& item);
    
    template <class T>
    void append(const T& item)
        { this->append(make_ref(item)); }
    void append(const ref& item);
    
    list slice(int low, int high) const;
    slice_proxy slice(int low, int high);
    void sort();
    void reverse();
    tuple as_tuple() const;
};

class string
    : public object, public boost::multipliable2<string, unsigned int>
{
 public:
    // Construct from an owned PyObject*.
    // Precondition: p must point to a python string.
    explicit string(ref p);
    explicit string(const char* s);
    string(const char* s, std::size_t length);
    string(const string& rhs);

    enum interned_t { interned };
    string(const char* s, interned_t);
    
    // Get the type object for Strings
    static PyTypeObject* type_obj();

    // Return true if the given object is a python string
    static bool accepts(ref o);

    // Return the length of the string.
    std::size_t size() const;

    // Returns a null-terminated representation of the contents of string.
    // The pointer refers to the internal buffer of string, not a copy.
    // The data must not be modified in any way. It must not be de-allocated. 
    const char* c_str() const;

    string& operator*=(unsigned int repeat_count);
    string& operator+=(const string& rhs);
    friend string operator+(string x, string y);
    string& operator+=(const char* rhs);
    friend string operator+(string x, const char* y);
    friend string operator+(const char* x, string y);

    void intern();

    friend string operator%(const string& format, const tuple& args);
};

class dictionary : public object
{
 private:
    struct proxy;
    
 public:
    explicit dictionary(ref p);
    dictionary();
    void clear();

    static PyTypeObject* type_obj();
    static bool accepts(ref p);
    
 public:
    template <class Key>
    proxy operator[](const Key& key)
        { return this->operator[](make_ref(key)); }
    proxy operator[](ref key);
    
    template <class Key>
    ref operator[](const Key& key) const
        { return this->operator[](make_ref(key)); }
    ref operator[](ref key) const;

    template <class Key>
    ref get_item(const Key& key) const
        { return this->get_item(make_ref(key)); }
    ref get_item(const ref& key) const;
    
    template <class Key, class Default>
    ref get_item(const Key& key, const Default& default_) const
        { return this->get_item(make_ref(key), make_ref(default_)); }
    ref get_item(const ref& key, const ref& default_) const;
    
    template <class Key, class Value>
    void set_item(const Key& key, const Value& value)
        { this->set_item(make_ref(key), make_ref(value)); }
    void set_item(const ref& key, const ref& value);

    template <class Key>
    void erase(const Key& key)
        { this->erase(make_ref(key)); }
    void erase(ref key);

//    proxy operator[](const object& key);
//    ref operator[](const object& key) const;

//    ref get_item(const object& key, ref default_ = ref()) const;
//    void set_item(const object& key, const ref& value);
        
//    void erase(const object& key);

    list items() const;
    list keys() const;
    list values() const;

    std::size_t size() const;
    // TODO: iterator support
};

struct dictionary::proxy
{
    template <class T>
    const ref& operator=(const T& rhs)
        { return (*this) = make_ref(rhs); }
    const ref& operator=(const ref& rhs);

    operator ref() const;
 private:
    friend class dictionary;
    proxy(const ref& dict, const ref& key);

    // This is needed to work around the very strange MSVC error report that the
    // return type of the built-in operator= differs from that of the ones
    // defined above. Couldn't hurt to make these un-assignable anyway, though.
    const ref& operator=(const proxy&); // Not actually implemented
 private:
    ref m_dict;
    ref m_key;
};

struct list::proxy
{
    template <class T>
    const ref& operator=(const T& rhs)
        { return (*this) = make_ref(rhs); }
    const ref& operator=(const ref& rhs);
    
    operator ref() const;
    
 private:
    friend class list;
    proxy(const ref& list, std::size_t index);
    
    // This is needed to work around the very strange MSVC error report that the
    // return type of the built-in operator= differs from that of the ones
    // defined above. Couldn't hurt to make these un-assignable anyway, though.
    const ref& operator=(const proxy&); // Not actually implemented
 private:
    list m_list;
    std::size_t m_index;
};

struct list::slice_proxy
{
    const list& operator=(const list& rhs);
    operator ref() const;
    operator list() const;
    std::size_t size();
    ref operator[](std::size_t pos) const;
 private:
    friend class list;
    slice_proxy(const ref& list, int low, int high);
 private:
    ref m_list;
    int m_low, m_high;
};

}} // namespace boost::python

BOOST_PYTHON_BEGIN_CONVERSION_NAMESPACE

PyObject* to_python(const boost::python::tuple&, boost::python::lookup_tag);
boost::python::tuple from_python(PyObject* p, boost::python::type<boost::python::tuple>);

inline boost::python::tuple from_python(PyObject* p, boost::python::type<const boost::python::tuple&>)
{
    return from_python(p, boost::python::type<boost::python::tuple>());
}

PyObject* to_python(const boost::python::list&, boost::python::lookup_tag);
boost::python::list from_python(PyObject* p, boost::python::type<boost::python::list>);

inline boost::python::list from_python(PyObject* p, boost::python::type<const boost::python::list&>)
{
    return from_python(p, boost::python::type<boost::python::list>());
}

PyObject* to_python(const boost::python::string&, boost::python::lookup_tag);
boost::python::string from_python(PyObject* p, boost::python::type<boost::python::string>);

inline boost::python::string from_python(PyObject* p, boost::python::type<const boost::python::string&>)
{
    return from_python(p, boost::python::type<boost::python::string>());
}

PyObject* to_python(const boost::python::dictionary&, boost::python::lookup_tag);
boost::python::dictionary from_python(PyObject* p, boost::python::type<boost::python::dictionary>);

inline boost::python::dictionary from_python(PyObject* p, boost::python::type<const boost::python::dictionary&>)
{
    return from_python(p, boost::python::type<boost::python::dictionary>());
}

BOOST_PYTHON_END_CONVERSION_NAMESPACE

#endif // OBJECTS_DWA051100_H_
