// Copyright David Abrahams 2001. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef MODULE_DWA2001128_HPP
# define MODULE_DWA2001128_HPP

# include <boost/python/errors.hpp>
# include <boost/python/detail/config.hpp>
# include <boost/python/reference.hpp>
# include <boost/python/make_function.hpp>
# include <boost/python/objects.hpp>
# include <boost/python/detail/wrap_python.hpp>

namespace boost { namespace python {

class BOOST_PYTHON_DECL module_base
{
 public:
    // Create a module. REQUIRES: only one module is created per module.
    module_base(const char* name);
    ~module_base();

    // Add elements to the module
    void add(PyObject* x, const char* name);
    void add(PyTypeObject* x, const char* name = 0);
    void add(ref const& x, const char*name);

    // Return true iff a module is currently being built.
    static bool initializing();
    
    // Return the name of the module currently being built.
    // REQUIRES: initializing() == true
    static string name();

    // Return a pointer to the Python module object being built
    ref module() const;

 private:
    ref m_module;
    static PyMethodDef initial_methods[1];
};

class module : public module_base
{
 public:
    module(const char* name)
        : module_base(name) {}

# if 0
    template <class Fn>
    void def_raw(Fn fn, const char* name)
    {
        add(detail::new_raw_arguments_function(fn), name);
    }
# endif 
    template <class Fn>
    void def(Fn fn, const char* name)
    {
        this->add(boost::python::make_function(fn), name);
    }
};

//
// inline implementations
//
inline ref module_base::module() const
{
    return m_module;
}

}} // namespace boost::python

#endif // MODULE_DWA20011221_HPP
