//  (C) Copyright David Abrahams 2000. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
//  The author gratefully acknowleges the support of Dragon Systems, Inc., in
//  producing this work.

// TODO: Move inline implementations from objects.cpp here

#include "objects.h"
#include "none.h"

namespace py {

template <class T>
T object_from_python(PyObject* p, Type<T>)
{
    Ptr x(p);
    if (!T::accepts(x))
    {
        PyErr_SetString(PyExc_TypeError, p->ob_type->tp_name);
        throw ErrorAlreadySet();
    }
    return T(x);
}

inline PyObject* object_to_python(const Object& x)
{
    return x.reference().release();
}

Object::Object(Ptr p)
    : m_p(p) {}
    
// Return a reference to the held object
Ptr Object::reference() const
{
    return m_p;
}

// Return a raw pointer to the held object
PyObject* Object::get() const
{
    return m_p.get();
}

#ifdef PY_NO_INLINE_FRIENDS_IN_NAMESPACE
} // Back to the global namespace for this GCC bug
#endif

PyObject* to_python(const py::Tuple& x)
{
    return object_to_python(x);
}

py::Tuple from_python(PyObject* p, py::Type<py::Tuple> type)
{
    return py::object_from_python(p, type);
}

PyObject* to_python(const py::List& x)
{
    return object_to_python(x);
}

py::List from_python(PyObject* p, py::Type<py::List> type)
{
    return py::object_from_python(p, type);
}

PyObject* to_python(const py::Dict& x)
{
    return object_to_python(x);
}

py::Dict from_python(PyObject* p, py::Type<py::Dict> type)
{
    return py::object_from_python(p, type);
}

PyObject* to_python(const py::String& x)
{
    return object_to_python(x);
}

py::String from_python(PyObject* p, py::Type<py::String> type)
{
    return py::object_from_python(p, type);
}

#ifdef PY_NO_INLINE_FRIENDS_IN_NAMESPACE
namespace py {
#endif

Tuple::Tuple(std::size_t n)
    : Object(Ptr(PyTuple_New(n)))
{
    for (std::size_t i = 0; i < n; ++i)
        PyTuple_SET_ITEM(get(), i, none());
}
    
Tuple::Tuple(Ptr p)
    : Object(p)
{
    assert(accepts(p));
}

PyTypeObject* Tuple::type_object()
{
    return &PyTuple_Type;
}

bool Tuple::accepts(Ptr p)
{
    return PyTuple_Check(p.get());
}

std::size_t Tuple::size() const
{
    return PyTuple_Size(get());
}

Ptr Tuple::operator[](std::size_t pos) const
{
    return Ptr(PyTuple_GetItem(get(), static_cast<int>(pos)),
               Ptr::new_ref);
}

void Tuple::set_item(std::size_t pos, const Ptr& rhs)
{
    int failed = PyTuple_SetItem(
        get(), static_cast<int>(pos), Ptr(rhs).release()); // A reference is stolen here.
    (void)failed;
    assert(failed == 0);
}

Tuple Tuple::slice(int low, int high) const
{
    return Tuple(Ptr(PyTuple_GetSlice(get(), low, high)));
}

Tuple& Tuple::operator+=(const Tuple& rhs)
{
    return *this = *this + rhs;
}


// Construct from an owned PyObject*.
// Precondition: p must point to a python string.
String::String(Ptr p)
    : Object(p) { assert(accepts(p)); }
    
String::String(const char* s)
    : Object(Ptr(PyString_FromString(s))) {}

String::String(const char* s, std::size_t length)
    : Object(Ptr(PyString_FromStringAndSize(s, length))) {}

String::String(const char* s, Interned)
    : Object(Ptr(PyString_InternFromString(s))) {}

#if 0
String::String(const char* s, std::size_t length, Interned)
    : Object(Ptr(PyString_InternFromStringAndSize(s, length))) {}
#endif

String::String(const String& rhs)
    : Object(rhs.reference()) {}

// Get the type object for Strings
PyTypeObject* String::type_object()
{ return &PyString_Type; }

// Return true if the given object is a python String
bool String::accepts(Ptr o)
{ return PyString_Check(o.get()); }

// Return the length of the string.
std::size_t String::size() const
{
    int size = PyString_GET_SIZE(get());
    assert(size >= 0);
    return static_cast<std::size_t>(size);
}

// Returns a null-terminated representation of the contents of string.
// The pointer refers to the internal buffer of string, not a copy.
// The data must not be modified in any way. It must not be de-allocated. 
const char* String::c_str() const
{ return PyString_AS_STRING(get()); }

void String::intern()
{ // UNTESTED!!
    *this = String(Ptr(PyString_InternFromString(c_str()), Ptr::borrowed));
}

Dict::Dict(Ptr p)
    : Object(p) { assert(accepts(p)); }

Dict::Dict()
    : Object(Ptr(PyDict_New())) {}

PyTypeObject* Dict::type_object()
{ return &PyDict_Type; }

bool Dict::accepts(Ptr p)
{ return PyDict_Check(p.get()); }

void Dict::clear()
{ PyDict_Clear(get()); }

const Ptr& Dict::Proxy::operator=(const Ptr& rhs) {
    if (PyDict_SetItem(m_dict.get(), m_key.get(), rhs.get()) == -1)
        throw ErrorAlreadySet();
    return rhs;
}

Dict::Proxy::operator Ptr() const
{
    return Ptr(m_dict->ob_type->tp_as_mapping->mp_subscript(m_dict.get(), m_key.get()),
               Ptr::borrowed);
}

Dict::Proxy::Proxy(const Ptr& dict, const Ptr& key)
    : m_dict(dict), m_key(key) {}

Dict::Proxy Dict::operator[](Ptr key)
{ return Proxy(reference(), key); }
    
Ptr Dict::operator[](Ptr key) const {
    // An odd MSVC bug causes the ".operator Ptr()" to be needed
    return Proxy(reference(), key).operator Ptr();
}

    
Ptr Dict::get_item(const Ptr& key, const Ptr& default_ /* = Ptr() */)
{
    PyObject* value_or_null = PyDict_GetItem(get(), key.get());
    if (value_or_null == 0 && !PyErr_Occurred())
        return default_;
    else
        return Ptr(value_or_null, Ptr::borrowed); // Will throw if there was another error
}
        
void Dict::erase(Ptr key) {
    if (PyDict_DelItem(get(), key.get()) == -1)
        throw ErrorAlreadySet();
}

Ptr Dict::items() const { return Ptr(PyDict_Items(get())); }
Ptr Dict::keys() const { return Ptr(PyDict_Keys(get())); }
Ptr Dict::values() const { return Ptr(PyDict_Values(get())); }

std::size_t Dict::size() const { return static_cast<std::size_t>(PyDict_Size(get())); }

Dict::Proxy Dict::operator[](const Object& key)
{
    return this->operator[](key.reference());
}

Ptr Dict::operator[](const Object& key) const
{
    return this->operator[](key.reference());
}

Ptr Dict::get_item(const Object& key, Ptr default_)
{
    return this->get_item(key.reference(), default_);
}
        
void Dict::erase(const Object& key)
{
    this->erase(key.reference());
}


// TODO: iterator support

String operator+(String x, String y)
{
    PyObject* io_string = x.reference().release();
    PyString_Concat(&io_string, y.get());
    return String(Ptr(io_string));    
}

String& String::operator+=(const String& rhs)
{
    return *this = *this + rhs;
}

String& String::operator+=(const char* y)
{
    return *this += String(y);
}

String operator%(const String& format, const Tuple& args)
{
    return String(Ptr(PyString_Format(format.get(), args.reference().get())));
}

String operator+(String x, const char* y)
{
    return x + String(y);
}

String operator+(const char* x, String y)
{
    return String(x) + y;
}

Tuple operator+(const Tuple& x, const Tuple& y)
{
    Tuple result(x.size() + y.size());
    for (std::size_t xi = 0; xi < x.size(); ++xi)
        result.set_item(xi, x[xi]);
    for (std::size_t yi = 0; yi < y.size(); ++yi)
        result.set_item(yi + x.size(), y[yi]);
    return result;
}


List::List(Ptr p)
    : Object(p)
{
    assert(accepts(p));
}

List::List(std::size_t sz)
    : Object(Ptr(PyList_New(sz)))
{
}

PyTypeObject* List::type_object()
{
    return &PyList_Type;
}

bool List::accepts(Ptr p)
{
    return PyList_Check(p.get());
}

std::size_t List::size()
{
    return PyList_Size(get());
}

Ptr List::operator[](std::size_t pos) const
{
    return Ptr(PyList_GetItem(get(), pos), Ptr::borrowed);
}

List::Proxy List::operator[](std::size_t pos)
{
    return Proxy(reference(), pos);
}

void List::insert(std::size_t index, Ptr item)
{
    if (PyList_Insert(get(), index, item.get()) == -1)
        throw ErrorAlreadySet();
}

void List::push_back(Ptr item)
{
    if (PyList_Append(get(), item.get()) == -1)
        throw ErrorAlreadySet();
}

void List::append(Ptr item)
{
    this->push_back(item);
}

List List::slice(int low, int high) const
{
    return List(Ptr(PyList_GetSlice(get(), low, high)));
}

List::SliceProxy List::slice(int low, int high)
{
    return SliceProxy(reference(), low, high);
}

void List::sort()
{
    if (PyList_Sort(get()) == -1)
        throw ErrorAlreadySet();
}

void List::reverse()
{
    if (PyList_Reverse(get()) == -1)
        throw ErrorAlreadySet();
}

Tuple List::as_tuple() const
{
    return Tuple(Ptr(PyList_AsTuple(get())));
}

const Ptr& List::Proxy::operator=(const Ptr& rhs)
{
    int result = PyList_SetItem(m_list.get(), m_index, rhs.get());
    if (result == -1)
        throw ErrorAlreadySet();
    Py_INCREF(rhs.get());
    return rhs;
}

List::Proxy::operator Ptr() const
{
    return Ptr(PyList_GetItem(m_list.get(), m_index), Ptr::borrowed);
}

List::Proxy::Proxy(const Ptr& list, std::size_t index)
    : m_list(list), m_index(index)
{
}

const List& List::SliceProxy::operator=(const List& rhs)
{
    if (PyList_SetSlice(m_list.get(), m_low, m_high, rhs.get()) == -1)
        throw ErrorAlreadySet();
    return rhs;
}

List::SliceProxy::operator Ptr() const
{
    return Ptr(PyList_GetSlice(m_list.get(), m_low, m_high));
}

List::SliceProxy::operator List() const
{
    return List(this->operator Ptr());
}

std::size_t List::SliceProxy::size()
{
    return this->operator List().size();
}

Ptr List::SliceProxy::operator[](std::size_t pos) const
{
    return this->operator List()[pos].operator Ptr();
}

List::SliceProxy::SliceProxy(const Ptr& list, int low, int high)
    : m_list(list), m_low(low), m_high(high)
{
}

}
