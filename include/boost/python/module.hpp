// Copyright David Abrahams 2001. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef MODULE_DWA2001128_HPP
# define MODULE_DWA2001128_HPP

# include <boost/python/errors.hpp>
# include <boost/python/detail/config.hpp>
# include <boost/python/make_function.hpp>
# include <boost/python/objects.hpp>
# include <boost/python/class_fwd.hpp>
# include <boost/python/detail/module_base.hpp>
# include <boost/python/detail/module_init.hpp>

namespace boost { namespace python {

class module : public detail::module_base
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
        this->add_class(c.object());
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
