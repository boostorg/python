//  (C) Copyright David Abrahams 2000. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
//  The author gratefully acknowleges the support of Dragon Systems, Inc., in
//  producing this work.

// TODO: Move inline implementations from objects.cpp here

#include <boost/python/objects.hpp>
#include <boost/python/detail/none.hpp>

namespace boost { namespace python {

template <class T>
T object_from_python(PyObject* p, type<T>)
{
    ref x(p, ref::increment_count);
    if (!T::accepts(x))
    {
        PyErr_SetString(PyExc_TypeError, p->ob_type->tp_name);
        throw error_already_set();
    }
    return T(x);
}

inline PyObject* object_to_python(const object& x)
{
    return x.reference().release();
}

object::object(ref p)
    : m_p(p) {}
    
// Return a reference to the held object
ref object::reference() const
{
    return m_p;
}

// Return a raw pointer to the held object
PyObject* object::get() const
{
    return m_p.get();
}

}} // namespace boost::python

BOOST_PYTHON_BEGIN_CONVERSION_NAMESPACE

PyObject* to_python(const boost::python::tuple& x, boost::python::lookup_tag)
{
    return boost::python::object_to_python(x);
}

boost::python::tuple from_python(PyObject* p, boost::python::type<boost::python::tuple> type)
{
    return boost::python::object_from_python(p, type);
}

PyObject* to_python(const boost::python::list& x, boost::python::lookup_tag)
{
    return boost::python::object_to_python(x);
}

boost::python::list from_python(PyObject* p, boost::python::type<boost::python::list> type)
{
    return boost::python::object_from_python(p, type);
}

PyObject* to_python(const boost::python::dictionary& x, boost::python::lookup_tag)
{
    return boost::python::object_to_python(x);
}

boost::python::dictionary from_python(PyObject* p, boost::python::type<boost::python::dictionary> type)
{
    return boost::python::object_from_python(p, type);
}

PyObject* to_python(const boost::python::string& x, boost::python::lookup_tag)
{
    return boost::python::object_to_python(x);
}

boost::python::string from_python(PyObject* p, boost::python::type<boost::python::string> type)
{
    return boost::python::object_from_python(p, type);
}

BOOST_PYTHON_END_CONVERSION_NAMESPACE

namespace boost { namespace python {

tuple::tuple(std::size_t n)
    : object(ref(PyTuple_New(n)))
{
    for (std::size_t i = 0; i < n; ++i)
        PyTuple_SET_ITEM(get(), i, detail::none());
}
    
tuple::tuple(ref p)
    : object(p)
{
    assert(accepts(p));
    if (!accepts(p))
    {
        PyErr_SetString(PyExc_TypeError, p->ob_type->tp_name);
        throw error_already_set();
    }
}

PyTypeObject* tuple::type_obj()
{
    return &PyTuple_Type;
}

bool tuple::accepts(ref p)
{
    return PyTuple_Check(p.get());
}

std::size_t tuple::size() const
{
    return PyTuple_Size(get());
}

ref tuple::operator[](std::size_t pos) const
{
    return ref(PyTuple_GetItem(get(), static_cast<int>(pos)),
               ref::increment_count);
}

void tuple::set_item(std::size_t pos, const ref& rhs)
{
    int failed = PyTuple_SetItem(
        get(), static_cast<int>(pos), ref(rhs).release()); // A reference is stolen here.
    (void)failed;
    assert(failed == 0);
}

tuple tuple::slice(int low, int high) const
{
    return tuple(ref(PyTuple_GetSlice(get(), low, high)));
}

tuple& tuple::operator+=(const tuple& rhs)
{
    return *this = *this + rhs;
}


// Construct from an owned PyObject*.
// Precondition: p must point to a python string.
string::string(ref p)
    : object(p)
{
    assert(accepts(p));
    if (!accepts(p))
    {
        PyErr_SetString(PyExc_TypeError, p->ob_type->tp_name);
        throw error_already_set();
    }
}
    
string::string(const char* s)
    : object(ref(PyString_FromString(s))) {}

string::string(const char* s, std::size_t length)
    : object(ref(PyString_FromStringAndSize(s, length))) {}

string::string(const char* s, interned_t)
    : object(ref(PyString_InternFromString(s))) {}

#if 0
string::string(const char* s, std::size_t length, interned_t)
    : object(ref(PyString_InternFromStringAndSize(s, length))) {}
#endif

string::string(const string& rhs)
    : object(rhs.reference()) {}

// Get the type object for Strings
PyTypeObject* string::type_obj()
{ return &PyString_Type; }

// Return true if the given object is a python string
bool string::accepts(ref o)
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
    *this = string(ref(PyString_InternFromString(c_str()), ref::increment_count));
}

string& string::operator*=(unsigned int repeat_count)
{
    *this = string(ref(PySequence_Repeat(get(), repeat_count)));
    return *this;
}

dictionary::dictionary(ref p)
    : object(p)
{
    assert(accepts(p));
    if (!accepts(p))
    {
        PyErr_SetString(PyExc_TypeError, p->ob_type->tp_name);
        throw error_already_set();
    }
}

dictionary::dictionary()
    : object(ref(PyDict_New())) {}

PyTypeObject* dictionary::type_obj()
{ return &PyDict_Type; }

bool dictionary::accepts(ref p)
{ return PyDict_Check(p.get()); }

void dictionary::clear()
{ PyDict_Clear(get()); }

const ref& dictionary::proxy::operator=(const ref& rhs)
{
    if (PyDict_SetItem(m_dict.get(), m_key.get(), rhs.get()) == -1)
        throw error_already_set();
    return rhs;
}

dictionary::proxy::operator ref() const
{
    return ref(m_dict->ob_type->tp_as_mapping->mp_subscript(m_dict.get(), m_key.get()),
               ref::increment_count);
}

dictionary::proxy::proxy(const ref& dict, const ref& key)
    : m_dict(dict), m_key(key) {}

dictionary::proxy dictionary::operator[](ref key)
{ return proxy(reference(), key); }
    
ref dictionary::operator[](ref key) const {
    // An odd MSVC bug causes the ".operator Ptr()" to be needed
    return proxy(reference(), key).operator ref();
}

    
ref dictionary::get_item(const ref& key) const
{
    return get_item(key, ref());
}

ref dictionary::get_item(const ref& key, const ref& default_) const
{
    PyObject* value_or_null = PyDict_GetItem(get(), key.get());
    if (value_or_null == 0 && !PyErr_Occurred())
        return default_;
    else
        return ref(value_or_null, ref::increment_count); // Will throw if there was another error
}
        
void dictionary::set_item(const ref& key, const ref& value)
{
    if (PyDict_SetItem(get(), key.get(), value.get()) == -1)
        throw error_already_set();
}

void dictionary::erase(ref key) {
    if (PyDict_DelItem(get(), key.get()) == -1)
        throw error_already_set();
}

list dictionary::items() const { return list(ref(PyDict_Items(get()))); }
list dictionary::keys() const { return list(ref(PyDict_Keys(get()))); }
list dictionary::values() const { return list(ref(PyDict_Values(get()))); }

std::size_t dictionary::size() const { return static_cast<std::size_t>(PyDict_Size(get())); }

string operator+(string x, string y)
{
    PyObject* io_string = x.reference().release();
    PyString_Concat(&io_string, y.get());
    return string(ref(io_string));    
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
    return string(ref(PyString_Format(format.get(), args.reference().get())));
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


list::list(ref p)
    : object(p)
{
    assert(accepts(p));
    if (!accepts(p))
    {
        PyErr_SetString(PyExc_TypeError, p->ob_type->tp_name);
        throw error_already_set();
    }
}

list::list(std::size_t sz)
    : object(ref(PyList_New(sz)))
{
}

PyTypeObject* list::type_obj()
{
    return &PyList_Type;
}

bool list::accepts(ref p)
{
    return PyList_Check(p.get());
}

std::size_t list::size()
{
    return PyList_Size(get());
}

ref list::operator[](std::size_t pos) const
{
    return ref(PyList_GetItem(get(), pos), ref::increment_count);
}

list::proxy list::operator[](std::size_t pos)
{
    return proxy(reference(), pos);
}

void list::insert(std::size_t index, const ref& item)
{
    if (PyList_Insert(get(), index, item.get()) == -1)
        throw error_already_set();
}

void list::push_back(const ref& item)
{
    if (PyList_Append(get(), item.get()) == -1)
        throw error_already_set();
}

void list::append(const ref& item)
{
    this->push_back(item);
}

list list::slice(int low, int high) const
{
    return list(ref(PyList_GetSlice(get(), low, high)));
}

list::slice_proxy list::slice(int low, int high)
{
    return slice_proxy(reference(), low, high);
}

void list::sort()
{
    if (PyList_Sort(get()) == -1)
        throw error_already_set();
}

void list::reverse()
{
    if (PyList_Reverse(get()) == -1)
        throw error_already_set();
}

tuple list::as_tuple() const
{
    return tuple(ref(PyList_AsTuple(get())));
}

const ref& list::proxy::operator=(const ref& rhs)
{
    m_list.set_item(m_index, rhs);
    return rhs;
}

list::proxy::operator ref() const
{
    return ref(PyList_GetItem(m_list.get(), m_index), ref::increment_count);
}

ref list::get_item(std::size_t pos) const
{
    return ref(PyList_GetItem(this->get(), pos), ref::increment_count);
}

void list::set_item(std::size_t pos, const ref& rhs)
{
    int result = PyList_SetItem(this->get(), pos, rhs.get());
    if (result == -1)
        throw error_already_set();
    Py_INCREF(rhs.get());
}

list::proxy::proxy(const ref& list, std::size_t index)
    : m_list(list), m_index(index)
{
}

const list& list::slice_proxy::operator=(const list& rhs)
{
    if (PyList_SetSlice(m_list.get(), m_low, m_high, rhs.get()) == -1)
        throw error_already_set();
    return rhs;
}

list::slice_proxy::operator ref() const
{
    return ref(PyList_GetSlice(m_list.get(), m_low, m_high));
}

list::slice_proxy::operator list() const
{
    return list(this->operator ref());
}

std::size_t list::slice_proxy::size()
{
    return this->operator list().size();
}

ref list::slice_proxy::operator[](std::size_t pos) const
{
    return this->operator list()[pos].operator ref();
}

list::slice_proxy::slice_proxy(const ref& list, int low, int high)
    : m_list(list), m_low(low), m_high(high)
{
}

}} // namespace boost::python
