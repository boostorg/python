// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#include <boost/python/list.hpp>

namespace boost { namespace python { 

BOOST_PYTHON_DECL detail::new_reference list::call(object const& arg)
{
    return (detail::new_reference)PyObject_CallFunction(
        (PyObject*)&PyList_Type, "(O)", 
        arg.ptr());
}

BOOST_PYTHON_DECL list::list()
    : object(detail::new_reference(PyList_New(0)))
{}

BOOST_PYTHON_DECL list::list(object_cref sequence)
    : object(list::call(sequence))
{}

BOOST_PYTHON_DECL void list::append(object_cref x)
{
    if (PyList_CheckExact(this->ptr()))
    {
        if (PyList_Append(this->ptr(), x.ptr()) == -1)
            throw_error_already_set();
    }
    else
    {
        this->attr("append")(x);
    }
}

BOOST_PYTHON_DECL long list::count(object_cref value) const
{
    object result_obj(this->attr("count")(value));
    long result = PyInt_AsLong(result_obj.ptr());
    if (result == -1)
        throw_error_already_set();
    return result;
}

BOOST_PYTHON_DECL void list::extend(object_cref sequence)
{
    this->attr("extend")(sequence);
}

BOOST_PYTHON_DECL long list::index(object_cref value) const
{
    object result_obj(this->attr("index")(value));
    long result = PyInt_AsLong(result_obj.ptr());
    if (result == -1)
        throw_error_already_set();
    return result;
}

BOOST_PYTHON_DECL void list::insert(int index, object_cref item)
{
    if (PyList_CheckExact(this->ptr()))
    {
        if (PyList_Insert(this->ptr(), index, item.ptr()) == -1)
            throw_error_already_set();
    }
    else
    {
        this->attr("insert")(index, item);
    }
}

BOOST_PYTHON_DECL void list::insert(object const& index, object_cref x)
{
    long index_ = PyInt_AsLong(index.ptr());
    if (index_ == -1 && PyErr_Occurred())
        throw_error_already_set();
    this->insert(index_, x);
}

BOOST_PYTHON_DECL object list::pop()
{
    return this->attr("pop")();
}

BOOST_PYTHON_DECL object list::pop(long index)
{
    return this->pop(object(index));
}

BOOST_PYTHON_DECL object list::pop(object const& index)
{
    return this->attr("pop")(index);
}

BOOST_PYTHON_DECL void list::remove(object_cref value)
{
    this->attr("remove")(value);
}
    
BOOST_PYTHON_DECL void list::reverse()
{
    if (PyList_CheckExact(this->ptr()))
    {
        if (PyList_Reverse(this->ptr()) == -1)
            throw_error_already_set();
    }
    else
    {
        this->attr("reverse")();
    }
}

BOOST_PYTHON_DECL void list::sort()
{
    if (PyList_CheckExact(this->ptr()))
    {
        if (PyList_Sort(this->ptr()) == -1)
            throw_error_already_set();
    }
    else
    {
        this->attr("sort")();
    }
}

BOOST_PYTHON_DECL void list::sort(object_cref cmpfunc)
{
    this->attr("sort")(cmpfunc);
}

}} // namespace boost::python
