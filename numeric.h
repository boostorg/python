#ifndef PYCPP_NUMERIC_H
#define PYCPP_NUMERIC_H

#include <map>
#include <utility>
#include "py.h"
#include "extclass.h"

namespace py {

template <class T, class U>
struct NumericOperators
{
    static PyObject * add(PyObject * l, PyObject * r) 
    { 
        return to_python(from_python(l, py::Type<T const &>()) +
                         from_python(r, py::Type<U const &>())); 
    }
    static PyObject * subtract(PyObject * l, PyObject * r) 
    { 
        return to_python(from_python(l, py::Type<T const &>()) -
                         from_python(r, py::Type<U const &>())); 
    }
};

typedef std::pair<PyTypeObject *, PyTypeObject *> TypePair;

bool operator<(TypePair const & l, TypePair const & r);

struct NumericDispatcher
: public PyObject
{
    typedef PyObject * (*NumericFunction)(PyObject *, PyObject *);
    typedef std::map<TypePair, NumericFunction> FunctionRepository;
    
    static FunctionRepository add_functions;
    static FunctionRepository sub_functions;
    
    static PyTypeObject type_object;
    static PyNumberMethods number_methods;

    friend class Module;
    
    // store this function in NumericDispatcher's 'nb_add' slot
    static PyObject * add(PyObject * l, PyObject * r);
    static PyObject * sub(PyObject * l, PyObject * r);
    
    static void coerce(PyObject * & l, PyObject * & r);

    static void init_type_object();
    static void free_type_object();
    
    NumericDispatcher(PyObject * o);
    static void dealloc(PyObject *self);
    
    PyObject * object;
};

py::Tuple coerce_wrapped(PyObject * l, PyObject * r);

}

inline PyObject * to_python(py::NumericDispatcher * n) { return n; }



#endif /* PYCPP_NUMERIC_H */
