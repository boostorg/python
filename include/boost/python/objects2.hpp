//  (C) Copyright David Abrahams 2002. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.

#ifndef OBJECTS_DWA20020611_H
# define OBJECTS_DWA20020611_H

# include <boost/python/detail/wrap_python.hpp>
# include <boost/python/detail/config.hpp>
# include <boost/python/handle.hpp>
# include "boost/operators.hpp"
# include <utility>

namespace boost { namespace python {

class list;

class BOOST_PYTHON_DECL objects_base
{
 public:
    explicit objects_base(handle<> const& p);
    
    // Return a reference to the held object
    handle<> reference() const;

    // Return a raw pointer to the held object
    PyObject* get() const;
    
 private:
    handle<> m_p;
};

class tuple;

class BOOST_PYTHON_DECL tuple_base : public objects_base
{
 public:
    explicit tuple_base(std::size_t n = 0);
    explicit tuple_base(handle<> p);

    static PyTypeObject* type_obj();
    static bool accepts(handle<> p);
    std::size_t size() const;
    handle<> operator[](std::size_t pos) const;

    void set_item(std::size_t pos, const handle<>& rhs);
    
    tuple slice(int low, int high) const;

    friend BOOST_PYTHON_DECL tuple operator+(const tuple&, const tuple&);
    friend BOOST_PYTHON_DECL tuple& operator+=(tuple&, const tuple&);
};

class  tuple : public tuple_base
{
 public:
    explicit tuple(std::size_t n = 0) : tuple_base(n) {}
    explicit tuple(handle<> p) : tuple_base(p) {}

    template <class First, class Second>
    tuple(const std::pair<First,Second>& x)
        : tuple_base(handle<>(PyTuple_New(2)))
    {
        set_item(0, x.first);
        set_item(1, x.second);
    }
    
    template <class First, class Second>
    tuple(const First& first, const Second& second)
        : tuple_base(handle<>(PyTuple_New(2)))
    {
        set_item(0, first);
        set_item(1, second);
    }
    
    template <class First, class Second, class Third>
    tuple(const First& first, const Second& second, const Third& third)
        : tuple_base(handle<>(PyTuple_New(3)))
    {
        set_item(0, first);
        set_item(1, second);
        set_item(2, third);
    }
    
    template <class First, class Second, class Third, class Fourth>
    tuple(const First& first, const Second& second, const Third& third, const Fourth& fourth)
        : tuple_base(handle<>(PyTuple_New(4)))
    {
        set_item(0, first);
        set_item(1, second);
        set_item(2, third);
        set_item(3, fourth);
    }

    void set_item(std::size_t pos, const handle<>& rhs)
    {
        tuple_base::set_item(pos, rhs);
    }
};

class BOOST_PYTHON_DECL string
    : public objects_base, public boost::multipliable2<string, unsigned int>
{
 public:
    // Construct from an owned PyObject*.
    // Precondition: p must point to a python string.
    explicit string(handle<> p);
    explicit string(const char* s);
    string(const char* s, std::size_t length);
    string(const string& rhs);

    enum interned_t { interned };
    string(const char* s, interned_t);
    
    // Get the type object for Strings
    static PyTypeObject* type_obj();

    // Return true if the given object is a python string
    static bool accepts(handle<> o);

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

class dictionary;

struct BOOST_PYTHON_DECL dictionary_proxy;

class BOOST_PYTHON_DECL dictionary_base : public objects_base
{
 protected:
    typedef dictionary_proxy proxy;
    
 public:
    explicit dictionary_base(handle<> p);
    dictionary_base();
    void clear();

    static PyTypeObject* type_obj();
    static bool accepts(handle<> p);
    
 public:
    proxy operator[](handle<> key);
    handle<> operator[](handle<> key) const;
    handle<> get_item(const handle<>& key) const;
    handle<> get_item(const handle<>& key, const handle<>& default_) const;
    
    void set_item(const handle<>& key, const handle<>& value);

    void erase(handle<> key);

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

struct BOOST_PYTHON_DECL dictionary_proxy
{
    template <class T>
    const handle<>& operator=(const T& rhs)
        { return (*this) = make_ref(rhs); }
    const handle<>& operator=(const handle<>& rhs);

    operator handle<>() const;
 private:
    friend class dictionary_base;
    dictionary_proxy(const handle<>& dict, const handle<>& key);

    // This is needed to work around the very strange MSVC error report that the
    // return type of the built-in operator= differs from that of the ones
    // defined above. Couldn't hurt to make these un-assignable anyway, though.
    const handle<>& operator=(const dictionary_proxy&); // Not actually implemented
 private:
    handle<> m_dict;
    handle<> m_key;
};

class dictionary : public dictionary_base
{
    typedef dictionary_proxy proxy;
 public:
    explicit dictionary(handle<> p) : dictionary_base(p) {}
    dictionary() : dictionary_base() {}
    
    template <class Key>
    proxy operator[](const Key& key)
        { return this->operator[](make_ref(key)); }
    proxy operator[](handle<> key)
    { return dictionary_base::operator[](key); }
    
    template <class Key>
    handle<> operator[](const Key& key) const
        { return this->operator[](make_ref(key)); }
    handle<> operator[](handle<> key) const
    { return dictionary_base::operator[](key); }

    template <class Key>
    handle<> get_item(const Key& key) const
        { return this->get_item(make_ref(key)); }
    handle<> get_item(const handle<>& key) const
    { return dictionary_base::get_item(key); }
    
    template <class Key, class Default>
    handle<> get_item(const Key& key, const Default& default_) const
        { return this->get_item(make_ref(key), make_ref(default_)); }
    handle<> get_item(const handle<>& key, const handle<>& default_) const
    { return dictionary_base::get_item(key, default_); }
    
    template <class Key, class Value>
    void set_item(const Key& key, const Value& value)
        { this->set_item(make_ref(key), make_ref(value)); }
    void set_item(const handle<>& key, const handle<>& value)
    { dictionary_base::set_item(key, value); }

    template <class Key>
    void erase(const Key& key)
        { this->erase(make_ref(key)); }
    void erase(handle<> key)
    { dictionary_base::erase(key); }
};

}} // namespace boost::python

#endif // OBJECTS_DWA20020611_H
