// Copyright David Abrahams 2001. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef CLASS_DWA20011214_HPP
# define CLASS_DWA20011214_HPP

# include <boost/python/detail/wrap_python.hpp>
# include <boost/python/detail/config.hpp>
# include <boost/utility.hpp>
# include <boost/python/converter/type_id.hpp>
# include <boost/iterator_adaptors.hpp>

namespace boost { namespace python { namespace objects { 

template <class T> struct holder;

// Base class for all holders
struct BOOST_PYTHON_DECL instance_holder : noncopyable
{
 public:
    instance_holder();
    virtual ~instance_holder();
    
    // return the next holder in a chain
    instance_holder* next() const;

    virtual void* holds(converter::type_id_t) = 0;

    void install(PyObject* inst);
    
    struct iterator_policies : default_iterator_policies
    {
        template <class Iterator>
        void increment(Iterator& p)
        {
            p.base() = p.base()->next();
        }
    };
    
    typedef iterator_adaptor<
        instance_holder*
        , iterator_policies
        , value_type_is<noncopyable>
        , reference_is<instance_holder&>
        , pointer_is<instance_holder*>
        , iterator_category_is<std::input_iterator_tag> > iterator;
    
 private:
    instance_holder* m_next;
};

// Each extension instance will be one of these
struct instance
{
    PyObject_HEAD
    instance_holder* objects;
};

BOOST_PYTHON_DECL void* find_instance_impl(PyObject*, converter::type_id_t);

template <class T>
T* find_instance(PyObject* p, T* = 0)
{
    return static_cast<T*>(find_instance_impl(p, converter::type_id<T>()));
}

BOOST_PYTHON_DECL PyTypeObject* class_metatype();
BOOST_PYTHON_DECL PyTypeObject* class_type();

//
// implementation
//
inline instance_holder* instance_holder::next() const
{
    return m_next;
}

}}} // namespace boost::python::objects

#endif // CLASS_DWA20011214_HPP
