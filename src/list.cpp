// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#include <boost/python/list.hpp>

namespace boost { namespace python { 

detail::new_non_null_reference list::call(object const& arg_)
{
    return (detail::new_non_null_reference)
        (expect_non_null)(
            PyObject_CallFunction(
                (PyObject*)&PyList_Type, "(O)", 
                arg_.ptr()));
}

list::list()
    : object(detail::new_reference(PyList_New(0)))
{}

list::list(object_cref sequence)
    : object(list::call(sequence))
{}

void list::append(object_cref x)
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

long list::count(object_cref value) const
{
    object result_obj(this->attr("count")(value));
    long result = PyInt_AsLong(result_obj.ptr());
    if (result == -1)
        throw_error_already_set();
    return result;
}

void list::extend(object_cref sequence)
{
    this->attr("extend")(sequence);
}

long list::index(object_cref value) const
{
    object result_obj(this->attr("index")(value));
    long result = PyInt_AsLong(result_obj.ptr());
    if (result == -1)
        throw_error_already_set();
    return result;
}

void list::insert(int index, object_cref item)
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

void list::insert(object const& index, object_cref x)
{
    long index_ = PyInt_AsLong(index.ptr());
    if (index_ == -1 && PyErr_Occurred())
        throw_error_already_set();
    this->insert(index_, x);
}

object list::pop()
{
    return this->attr("pop")();
}

object list::pop(long index)
{
    return this->pop(object(index));
}

object list::pop(object const& index)
{
    return this->attr("pop")(index);
}

void list::remove(object_cref value)
{
    this->attr("remove")(value);
}
    
void list::reverse()
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

void list::sort()
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

void list::sort(object_cref cmpfunc)
{
    this->attr("sort")(cmpfunc);
}

}} // namespace boost::python
