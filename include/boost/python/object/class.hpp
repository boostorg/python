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
struct BOOST_PYTHON_DECL holder_base : noncopyable
{
 public:
    holder_base(converter::type_id_t id);
    virtual ~holder_base();
    virtual bool held_by_value() const = 0;
    
    holder_base* next() const;
    converter::type_id_t type() const;

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
        holder_base*
        , iterator_policies
        , value_type_is<noncopyable>
        , reference_is<holder_base&>
        , pointer_is<holder_base*>
        , iterator_category_is<std::input_iterator_tag> > iterator;
    
 private:
    converter::type_id_t m_type;
    holder_base* m_next;
};

// Abstract base class which holds a Held, somehow. Provides a uniform
// way to get a pointer to the held object
template <class Held>
struct holder : holder_base
{
    typedef Held held_type;
    holder();
    virtual Held* target() = 0;
};

// Each extension instance will be one of these
struct instance
{
    PyObject_HEAD
    holder_base* objects;
};

BOOST_PYTHON_DECL holder_base* find_holder_impl(PyObject*, converter::type_id_t);

template <class T>
holder<T>* find_holder(PyObject* p, T* = 0)
{
    return static_cast<holder<T>*>(find_holder_impl(p, converter::type_id<T>()));
}

BOOST_PYTHON_DECL PyTypeObject* class_metatype();
BOOST_PYTHON_DECL PyTypeObject* class_type();

//
// implementation
//
inline holder_base* holder_base::next() const
{
    return m_next;
}

inline converter::type_id_t holder_base::type() const
{
    return m_type;
}

template <class Held>
holder<Held>::holder()
    : holder_base(converter::type_id<Held>())
{
}

}}} // namespace boost::python::objects

#endif // CLASS_DWA20011214_HPP
