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
# include <boost/python/class_fwd.hpp>

namespace boost { namespace python {

class BOOST_PYTHON_DECL module_base
{
 public:
    // Create a module. REQUIRES: only one module is created per module.
    module_base(const char* name);
    ~module_base();

    // Add elements to the module
    void setattr(const char* name, PyObject*);
    void setattr(const char* name, ref const&);
    void add(PyTypeObject* x); // just use the type's name
    void add_type(ref);
    
    // Return a reference to the Python module object being built
    ref object() const;

 private:
    ref m_module;
    static PyMethodDef initial_methods[1];
};

class module : public module_base
{
 public:
    module(const char* name)
        : module_base(name) {}

    // Add elements to the module
    module& setattr(const char* name, PyObject*);
    module& setattr(const char* name, PyTypeObject*);
    module& setattr(const char* name, ref const&);
    module& add(PyTypeObject* x); // just use the type's name
    
    template <class T, class Bases, class HolderGenerator>
    module& add(class_<T,Bases,HolderGenerator> const& c)
    {
        Py_INCREF(c.object());
        this->add_type(c.object());
        return *this;
    }
    
    template <class Fn>
    module& def(char const* name, Fn fn)
    {
        this->setattr(name, boost::python::make_function(fn));
        return *this;
    }

    
    template <class Fn, class ResultHandler>
    module& def(char const* name, Fn fn, ResultHandler handler)
    {
        this->setattr(name, boost::python::make_function(fn, handler));
        return *this;
    }
};

//
// inline implementations
//
inline ref module_base::object() const
{
    return m_module;
}

inline module& module::setattr(const char* name, PyObject* x)
{
    this->module_base::setattr(name, x);
    return *this;
}

inline module& module::setattr(const char* name, PyTypeObject* x)
{
    this->module_base::setattr(name, (PyObject*)x);
    return *this;
}

inline module& module::setattr(const char* name, ref const& x)
{
    this->module_base::setattr(name, x);
    return *this;
}

inline module& module::add(PyTypeObject* x)
{
    this->module_base::add(x);
    return *this;
}

}} // namespace boost::python

#endif // MODULE_DWA20011221_HPP
