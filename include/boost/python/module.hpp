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
# include <boost/python/detail/module_info.hpp>

namespace boost { namespace python {

class module : public detail::module_base
{
 public:
    typedef detail::module_base base;

     module(const char* name = "")
        : base(name) {}

    // Add elements to the module
    module& setattr(const char* name, PyObject*);
    module& setattr(const char* name, PyTypeObject*);
    module& setattr(const char* name, handle<> const&);
    module& add(PyTypeObject* x); // just use the type's name
    
    template <class T1, class T2 , class T3, class T4>
    module& add(class_<T1,T2,T3,T4> const& c)
    {
        // redundant
        // this->add_class(c.object());
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

    static module get_prior_module()
    {
        return module(module_base::get_prior_module());
    }

 private:
    module(handle<> const& m) : base(m) {}
};

//
// inline implementations
//
inline module& module::setattr(const char* name, PyObject* x)
{
    this->base::setattr(name, x);
    return *this;
}

inline module& module::setattr(const char* name, PyTypeObject* x)
{
    this->base::setattr(name, (PyObject*)x);
    return *this;
}

inline module& module::setattr(const char* name, handle<> const& x)
{
    this->base::setattr(name, x);
    return *this;
}

inline module& module::add(PyTypeObject* x)
{
    this->base::add(handle<>(borrowed(x)));
    return *this;
}

template <class Fn>
inline void def(char const* name, Fn fn)
{
    module::get_prior_module().def(name, fn);
}


template <class Fn, class ResultHandler>
inline void def(char const* name, Fn fn, ResultHandler handler)
{
    module::get_prior_module().def(name, fn, handler);
}

}} // namespace boost::python

#endif // MODULE_DWA20011221_HPP
