// Copyright David Abrahams 2001. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef CLASS_DWA20011214_HPP
# define CLASS_DWA20011214_HPP

# include <boost/python/detail/wrap_python.hpp>
# include <boost/python/export.hpp>
# include <boost/utility.hpp>
# include <boost/python/converter/type_id.hpp>

namespace boost { namespace python { namespace object { 

template <class T> struct holder;

// Base class for all holders
struct BOOST_PYTHON_EXPORT holder_base : noncopyable
{
 public:
    holder_base(converter::type_id_t id);
    virtual ~holder_base();
    virtual bool held_by_value() const = 0;
    
    holder_base* next() const;
    converter::type_id_t type() const;

    void install(PyObject* inst);
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

extern BOOST_PYTHON_EXPORT PyTypeObject class_metatype;
extern BOOST_PYTHON_EXPORT PyTypeObject class_type;

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

}}} // namespace boost::python::object

#endif // CLASS_DWA20011214_HPP
