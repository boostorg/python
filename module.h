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
# include "objects.h"
# include "functions.h"

namespace python {

class module_builder
{
    typedef PyObject * (*raw_function_ptr)(python::tuple const &, python::dictionary const &);
    
 public:
    // Create a module. REQUIRES: only one module_builder is created per module.
    module_builder(const char* name);

    // Add elements to the module
    void add(detail::function* x, const char* name);
    void add(PyTypeObject* x, const char* name = 0);
    void add(ref x, const char*name);

    template <class Fn>
    void def_raw(Fn fn, const char* name)
    {
        add(detail::new_raw_arguments_function(fn), name);
    }
    
    template <class Fn>
    void def(Fn fn, const char* name)
    {
        add(detail::new_wrapped_function(fn), name);
    }

    static string name();
    
 private:
    PyObject* m_module;
    static PyMethodDef initial_methods[1];
};

}

#endif
