#include "numeric.h"
#include "py.h"
#include <stdexcept>

namespace py {

NumericDispatcher::FunctionRepository NumericDispatcher::add_functions;
NumericDispatcher::FunctionRepository NumericDispatcher::sub_functions;

PyTypeObject NumericDispatcher::type_object = 
{ 
    PyObject_HEAD_INIT(&PyType_Type) 
    0, 
    "NumericDispatcher", 
    sizeof(NumericDispatcher), 
    0, 
    (destructor)&NumericDispatcher::dealloc, 
    0, 
    0, 
    0, 
    0, 
    0, 
    &NumericDispatcher::number_methods, 
    0, 
    0, 
    0, 
    0, 
    0, 
    0, 
    0, 
    0, 
    0, 
    0 
}; 

PyNumberMethods NumericDispatcher::number_methods = 
{ 
    &NumericDispatcher::add, 
    &NumericDispatcher::sub, 
    0, 
    0, 
    0, 
    0, 
    0, 
    0, 
    0, 
    0, 
    0, 
    0, 
    0, 
    0, 
    0, 
    0, 
    0, 
    0,  
    0, 
    0, 
    0, 
    0, 
    0 
}; 

NumericDispatcher::NumericDispatcher(PyObject * o)
: object(o)
{
    ob_refcnt = 1;
    ob_type = &type_object;
}

void NumericDispatcher::dealloc(PyObject *self) 
{ 
    delete static_cast<NumericDispatcher *>(self);
} 

PyObject * NumericDispatcher::add(PyObject * l, PyObject * r)
{
    coerce(l,r);

    PyTypeObject * lt = l->ob_type;
    PyTypeObject * rt = r->ob_type;
         
    FunctionRepository::iterator f = add_functions.find(make_pair(lt, rt));

    if(f != add_functions.end())
    {
        PyObject * result = (*(*f).second)(l, r);
        Py_DECREF(l);
        Py_DECREF(r);
        return result;
    }
    else
    {
        Py_DECREF(l);
        Py_DECREF(r);
        PyErr_SetString(PyExc_TypeError, "incompatible arguments for +");        
        return 0;
    }
}

PyObject * NumericDispatcher::sub(PyObject * l, PyObject * r)
{
    coerce(l,r);

    PyTypeObject * lt = l->ob_type;
    PyTypeObject * rt = r->ob_type;
         
    FunctionRepository::iterator f = sub_functions.find(make_pair(lt, rt));

    if(f != sub_functions.end())
    {
        PyObject * result = (*(*f).second)(l, r);
        Py_DECREF(l);
        Py_DECREF(r);
        return result;
    }
    else
    {
        Py_DECREF(l);
        Py_DECREF(r);
        PyErr_SetString(PyExc_TypeError, "incompatible arguments for -");        
        return 0;
    }
}

// add appropriate ref counting here !!!
void NumericDispatcher::coerce(PyObject * & l, PyObject * & r)
{
    if(l->ob_type == &type_object)
    {
        if(r->ob_type != &type_object)
        {
            throw std::runtime_error("internal error");
        }
        
        NumericDispatcher * lwrapper = static_cast<NumericDispatcher *>(l);
        NumericDispatcher * rwrapper = static_cast<NumericDispatcher *>(r);
        l = lwrapper->object;
        r = rwrapper->object;
    }

    Py_INCREF(l);
    Py_INCREF(r);
    return;  
}

void NumericDispatcher::init_type_object()
{
}


void NumericDispatcher::free_type_object()
{
}

py::Tuple coerce_wrapped(PyObject * l, PyObject * r)
{
    return py::Tuple(new NumericDispatcher(l),
                     new NumericDispatcher(r));
}

bool operator<(TypePair const & l, TypePair const & r)
{
    return (l.first < r.first) ? 
                1 : 
                (r.first < l.first) ?
                    0 :
                    l.second < r.second;
}


}
