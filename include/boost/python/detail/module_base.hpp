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

class module_info;

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
    static module_info* get_module_info();
    static void set_module_info(module_info& mi);
    static handle<> get_prior_module();
    static void set_prior_module(handle<> const& m);
    static void add(type_handle const& class_obj, handle<> const& context);
    
    // Return a reference to the Python module object being built
    inline handle<> object() const;

 protected:
    module_base(handle<> const &m) : m_module(m) {}
    void add_class(type_handle const& class_obj);
    void add_class(type_handle const& class_obj, handle<> const& context);

 private:
    static module_info*& get_module_info_ref();
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

inline void module_base::add(type_handle const& class_obj, handle<> const& context)
{
    module_base mb(get_prior_module());
    mb.add_class(class_obj, context);
}

}}} // namespace boost::python::detail

#endif // MODULE_BASE_DWA2002227_HPP
