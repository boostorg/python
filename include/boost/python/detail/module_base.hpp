// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef MODULE_BASE_DWA2002227_HPP
# define MODULE_BASE_DWA2002227_HPP
# include <boost/python/detail/wrap_python.hpp>
# include <boost/python/handle.hpp>

namespace boost { namespace python { namespace detail { 

class BOOST_PYTHON_DECL module_base
{
 public:
    // Create a module. REQUIRES: only one module is created per module.
    module_base(const char* name);
    ~module_base();

    // Add elements to the module
    void setattr(const char* name, PyObject*);
    void setattr(const char* name, handle<> const&);
    void add(type_handle const&); // just use the type's name
    
    // Return a reference to the Python module object being built
    inline handle<> object() const;

 protected:
    void add_class(type_handle const& class_obj);

 private:
    handle<> m_module;
    static PyMethodDef initial_methods[1];
};

//
// inline implementations
//
inline handle<> module_base::object() const
{
    return m_module;
}

}}} // namespace boost::python::detail

#endif // MODULE_BASE_DWA2002227_HPP
