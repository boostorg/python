//  (C) Copyright David Abrahams 2000. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
//  The author gratefully acknowleges the support of Dragon Systems, Inc., in
//  producing this work.

#ifndef MODULE_DWA051000_H_
# define MODULE_DWA051000_H_

# include "pyconfig.h"
# include "pyptr.h"
# include "functions.h"
# include "numeric.h"

namespace py {

class ExtensionType;

class Module
{
public:
    Module(const char* name);

    void add(Function* x, const char* name);
    
    void add(PyTypeObject* x, const char* name = 0);
    
    void add(Ptr x, const char*name);

    template <class Fn>
    void def(Fn fn, const char* name)
    {
        add(new_wrapped_function(fn), name);
    }
    
    template <class T1, class U1, class T2, class U2>
    void
    def_numeric(ExtensionClass<T1,U1> * l, ExtensionClass<T2,U2> * r, 
                char const * name)
    {
        PyTypeObject * tl = l;
        PyTypeObject * tr = r;

        l->def(coerce_wrapped, "__coerce__");
        r->def(coerce_wrapped, "__coerce__");
        if(strcmp(name,"__add__") == 0)
        {
            NumericDispatcher::add_functions[std::make_pair(tl,tr)] = 
                                         NumericOperators<T1, T2>::add;
            l->def(py::NumericDispatcher::add, "__add__");
            r->def(py::NumericDispatcher::add, "__add__");
        }
        else if(strcmp(name,"__sub__") == 0)
        {
            NumericDispatcher::sub_functions[std::make_pair(tl,tr)] = 
                                         NumericOperators<T1, T2>::subtract;
            l->def(py::NumericDispatcher::sub, "__sub__");
            r->def(py::NumericDispatcher::sub, "__sub__");
        }
    }
    
    
    template <class T1, class U1>
    void
    def_numeric(ExtensionClass<T1,U1> * l, PyTypeObject * r, 
                char const * name)
    {
        PyTypeObject * tl = l;
        PyTypeObject * tr = r;

        l->def(coerce_wrapped, "__coerce__");
        if(strcmp(name,"__add__") == 0)
        {
            NumericDispatcher::add_functions[std::make_pair(tl,tr)] = 
                                         NumericOperators<T1, int>::add;
            l->def(py::NumericDispatcher::add, "__add__");
        }
        else if(strcmp(name,"__sub__") == 0)
        {
            NumericDispatcher::sub_functions[std::make_pair(tl,tr)] = 
                                         NumericOperators<T1, int>::subtract;
            l->def(py::NumericDispatcher::sub, "__sub__");
        }
    }
    
    
    template <class T2, class U2>
    void
    def_numeric(PyTypeObject * l, ExtensionClass<T2,U2> * r, 
                char const * name)
    {
        PyTypeObject * tl = l;
        PyTypeObject * tr = r;

        r->def(coerce_wrapped, "__coerce__");
        if(strcmp(name,"__add__") == 0)
        {
            NumericDispatcher::add_functions[std::make_pair(tl,tr)] = 
                                         NumericOperators<int, T2>::add;
            r->def(py::NumericDispatcher::add, "__add__");
        }
        else if(strcmp(name,"__sub__") == 0)
        {
            NumericDispatcher::sub_functions[std::make_pair(tl,tr)] = 
                                         NumericOperators<int, T2>::subtract;
            r->def(py::NumericDispatcher::sub, "__sub__");
        }
    }

 private:
    PyObject* m_module;
    static PyMethodDef initial_methods[1];
};

}

#endif
