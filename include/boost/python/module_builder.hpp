//  (C) Copyright David Abrahams 2000. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
//  The author gratefully acknowleges the support of Dragon Systems, Inc., in
//  producing this work.

#ifndef MODULE_DWA051000_H_
# define MODULE_DWA051000_H_

# include <boost/python/detail/config.hpp>
# include <boost/python/reference.hpp>
# include <boost/python/objects.hpp>
# include <boost/python/detail/functions.hpp>
# include <boost/python/detail/module_init.hpp>

namespace boost { namespace python {

class BOOST_PYTHON_DECL module_builder_base
{
 public:
    // Create a module. REQUIRES: only one module_builder is created per module.
    module_builder_base(const char* name);
    ~module_builder_base();

    // Add elements to the module
    void add(detail::function* x, const char* name);
    void add(PyTypeObject* x, const char* name = 0);
    void add(ref x, const char*name);

    // Return true iff a module is currently being built.
    static bool initializing();
    
    // Return the name of the module currently being built.
    // REQUIRES: initializing() == true
    static string name();

    // Return a pointer to the Python module object being built
    PyObject* module() const;

 private:
    PyObject* m_module;
    static PyMethodDef initial_methods[1];
};

class module_builder : public module_builder_base
{
 public:
    module_builder(const char* name)
        : module_builder_base(name) {}

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
};

//
// inline implementations
//
inline PyObject* module_builder_base::module() const
{
    return m_module;
}

}} // namespace boost::python

#endif
