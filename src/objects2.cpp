//  (C) Copyright David Abrahams 2000. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
//  The author gratefully acknowleges the support of Dragon Systems, Inc., in
//  producing this work.

// TODO: Move inline implementations from objects.cpp here

#ifndef BOOST_PYTHON_SOURCE
# define BOOST_PYTHON_SOURCE
#endif 

#include <boost/python/objects.hpp>
#include <boost/python/detail/none.hpp>

namespace boost { namespace python {

objects_base::objects_base(handle<> const& p)
    : m_p(borrowed(p.get())) // Do the null check here
{}
    
// Return a reference to the held object
handle<> objects_base::reference() const
{
    return m_p;
}

// Return a raw pointer to the held object
PyObject* objects_base::get() const
{
    return m_p.get();
}

}} // namespace boost::python

namespace boost { namespace python {

tuple_base::tuple_base(std::size_t n)
    : objects_base(handle<>(PyTuple_New(n)))
{
    for (std::size_t i = 0; i < n; ++i)
        PyTuple_SET_ITEM(get(), i, detail::none());
}
    
tuple_base::tuple_base(handle<> p)
    : objects_base(p)
{
    assert(accepts(p));
    if (!accepts(p))
    {
        PyErr_SetString(PyExc_TypeError, p->ob_type->tp_name);
        throw_error_already_set();
    }
}

PyTypeObject* tuple_base::type_obj()
{
    return &PyTuple_Type;
}

bool tuple_base::accepts(handle<> p)
{
    return PyTuple_Check(p.get());
}

std::size_t tuple_base::size() const
{
    return PyTuple_Size(get());
}

handle<> tuple_base::operator[](std::size_t pos) const
{
    return handle<>(borrowed(PyTuple_GetItem(get(), static_cast<int>(pos))));
}

void tuple_base::set_item(std::size_t pos, const handle<>& rhs)
{
    int failed = PyTuple_SetItem(
        get()
        , static_cast<int>(pos)
        , incref(expect_non_null(rhs.get()))
        ); 
    (void)failed;
    assert(failed == 0);
}

tuple tuple_base::slice(int low, int high) const
{
    return tuple(handle<>(PyTuple_GetSlice(get(), low, high)));
}

BOOST_PYTHON_DECL tuple& operator+=(tuple& self, const tuple& rhs)
{
    return self = self + rhs;
}


// Construct from an owned PyObject*.
// Precondition: p must point to a python string.
string::string(handle<> p)
    : objects_base(p)
{
    assert(accepts(p));
    if (!accepts(p))
    {
        PyErr_SetString(PyExc_TypeError, p->ob_type->tp_name);
        throw_error_already_set();
    }
}
    
string::string(const char* s)
    : objects_base(handle<>(PyString_FromString(s))) {}

string::string(const char* s, std::size_t length)
    : objects_base(handle<>(PyString_FromStringAndSize(s, length))) {}

string::string(const char* s, interned_t)
    : objects_base(handle<>(PyString_InternFromString(s))) {}

string::string(const string& rhs)
    : objects_base(rhs.reference()) {}

// Get the type object for Strings
PyTypeObject* string::type_obj()
{ return &PyString_Type; }

// Return true if the given object is a python string
bool string::accepts(handle<> o)
{ return PyString_Check(o.get()); }

// Return the length of the string.
std::size_t string::size() const
{
    int size = PyString_GET_SIZE(get());
    assert(size >= 0);
    return static_cast<std::size_t>(size);
}

// Returns a null-terminated representation of the contents of string.
// The pointer refers to the internal buffer of string, not a copy.
// The data must not be modified in any way. It must not be de-allocated. 
const char* string::c_str() const
{ return PyString_AS_STRING(get()); }

void string::intern()
{ // UNTESTED!!
    *this = string(handle<>(borrowed(PyString_InternFromString(c_str()))));
}

string& string::operator*=(unsigned int repeat_count)
{
    *this = string(handle<>(PySequence_Repeat(get(), repeat_count)));
    return *this;
}

dictionary_base::dictionary_base(handle<> p)
    : objects_base(p)
{
    assert(accepts(p));
    if (!accepts(p))
    {
        PyErr_SetString(PyExc_TypeError, p->ob_type->tp_name);
        throw_error_already_set();
    }
}

dictionary_base::dictionary_base()
    : objects_base(handle<>(PyDict_New())) {}

PyTypeObject* dictionary_base::type_obj()
{ return &PyDict_Type; }

bool dictionary_base::accepts(handle<> p)
{ return PyDict_Check(p.get()); }

void dictionary_base::clear()
{ PyDict_Clear(get()); }

const handle<>& dictionary_proxy::operator=(const handle<>& rhs)
{
    if (PyDict_SetItem(m_dict.get(), m_key.get(), rhs.get()) == -1)
        throw_error_already_set();
    return rhs;
}

dictionary_proxy::operator handle<>() const
{
    return handle<>( 
        m_dict->ob_type->tp_as_mapping->mp_subscript(m_dict.get(), m_key.get()));
}

dictionary_proxy::dictionary_proxy(const handle<>& dict, const handle<>& key)
    : m_dict(dict), m_key(key) {}

dictionary_proxy dictionary_base::operator[](handle<> key)
{ return proxy(reference(), key); }
    
handle<> dictionary_base::operator[](handle<> key) const {
    // An odd MSVC bug causes the ".operator Ptr()" to be needed
    return proxy(reference(), key).operator handle<>();
}

    
handle<> dictionary_base::get_item(const handle<>& key) const
{
    return get_item(key, handle<>());
}

handle<> dictionary_base::get_item(const handle<>& key, const handle<>& default_) const
{
    PyObject* value_or_null = PyDict_GetItem(get(), key.get());
    if (value_or_null == 0 && !PyErr_Occurred())
        return default_;
    else
        return handle<>(borrowed(value_or_null)); // Will throw if there was another error
}
        
void dictionary_base::set_item(const handle<>& key, const handle<>& value)
{
    if (PyDict_SetItem(get(), key.get(), value.get()) == -1)
        throw_error_already_set();
}

void dictionary_base::erase(handle<> key) {
    if (PyDict_DelItem(get(), key.get()) == -1)
        throw_error_already_set();
}

list dictionary_base::items() const { return list(handle<>(PyDict_Items(get()))); }
list dictionary_base::keys() const { return list(handle<>(PyDict_Keys(get()))); }
list dictionary_base::values() const { return list(handle<>(PyDict_Values(get()))); }

std::size_t dictionary_base::size() const { return static_cast<std::size_t>(PyDict_Size(get())); }

string operator+(string x, string y)
{
    PyObject* io_string = incref(x.get());
    PyString_Concat(&io_string, y.get());
    return string(handle<>(io_string));
}

string& string::operator+=(const string& rhs)
{
    return *this = *this + rhs;
}

string& string::operator+=(const char* y)
{
    return *this += string(y);
}

string operator%(const string& format, const tuple& args)
{
    return string(handle<>(PyString_Format(format.get(), args.reference().get())));
}

string operator+(string x, const char* y)
{
    return x + string(y);
}

string operator+(const char* x, string y)
{
    return string(x) + y;
}

tuple operator+(const tuple& x, const tuple& y)
{
    tuple result(x.size() + y.size());
    for (std::size_t xi = 0; xi < x.size(); ++xi)
        result.set_item(xi, x[xi]);
    for (std::size_t yi = 0; yi < y.size(); ++yi)
        result.set_item(yi + x.size(), y[yi]);
    return result;
}


list_base::list_base(handle<> p)
    : objects_base(p)
{
    assert(accepts(p));
    if (!accepts(p))
    {
        PyErr_SetString(PyExc_TypeError, p->ob_type->tp_name);
        throw_error_already_set();
    }
}

list_base::list_base(std::size_t sz)
    : objects_base(handle<>(PyList_New(sz)))
{
}

PyTypeObject* list_base::type_obj()
{
    return &PyList_Type;
}

bool list_base::accepts(handle<> p)
{
    return PyList_Check(p.get());
}

std::size_t list_base::size() const
{
    return PyList_Size(get());
}

handle<> list_base::operator[](std::size_t pos) const
{
    return handle<>(borrowed(PyList_GetItem(get(), pos)));
}

list_proxy list_base::operator[](std::size_t pos)
{
    return proxy(reference(), pos);
}

void list_base::insert(std::size_t index, const handle<>& item)
{
    if (PyList_Insert(get(), index, item.get()) == -1)
        throw_error_already_set();
}

void list_base::push_back(const handle<>& item)
{
    if (PyList_Append(get(), item.get()) == -1)
        throw_error_already_set();
}

void list_base::append(const handle<>& item)
{
    this->push_back(item);
}

list list_base::slice(int low, int high) const
{
    return list(handle<>(PyList_GetSlice(get(), low, high)));
}

list_slice_proxy list_base::slice(int low, int high)
{
    return list_slice_proxy(reference(), low, high);
}

void list_base::sort()
{
    if (PyList_Sort(get()) == -1)
        throw_error_already_set();
}

void list_base::reverse()
{
    if (PyList_Reverse(get()) == -1)
        throw_error_already_set();
}

tuple list_base::as_tuple() const
{
    return tuple(handle<>(PyList_AsTuple(get())));
}

const handle<>& list_proxy::operator=(const handle<>& rhs)
{
    m_list.set_item(m_index, rhs);
    return rhs;
}

list_proxy::operator handle<>() const
{
    return handle<>(borrowed(PyList_GetItem(m_list.get(), m_index)));
}

handle<> list_base::get_item(std::size_t pos) const
{
    return handle<>(borrowed(PyList_GetItem(this->get(), pos)));
}

void list_base::set_item(std::size_t pos, const handle<>& rhs)
{
    int result = PyList_SetItem(this->get(), pos, rhs.get());
    if (result == -1)
        throw_error_already_set();
    Py_INCREF(rhs.get());
}

list_proxy::list_proxy(const handle<>& list, std::size_t index)
    : m_list(list), m_index(index)
{
}

const list& list_slice_proxy::operator=(const list& rhs)
{
    if (PyList_SetSlice(m_list.get(), m_low, m_high, rhs.get()) == -1)
        throw_error_already_set();
    return rhs;
}

list_slice_proxy::operator handle<>() const
{
    return handle<>(PyList_GetSlice(m_list.get(), m_low, m_high));
}

list_slice_proxy::operator list() const
{
    return list(this->operator handle<>());
}

std::size_t list_slice_proxy::size() const
{
    return this->operator list().size();
}

handle<> list_slice_proxy::operator[](std::size_t pos) const
{
    return this->operator list()[pos].operator handle<>();
}

list_slice_proxy::list_slice_proxy(const handle<>& list, int low, int high)
    : m_list(list), m_low(low), m_high(high)
{
}

}} // namespace boost::python
