// Copyright David Abrahams 2001. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef CLASS_DWA20011214_HPP
# define CLASS_DWA20011214_HPP

# include <boost/python/module.hpp>
# include <boost/python/detail/wrap_python.hpp>
# include <boost/python/detail/config.hpp>
# include <boost/utility.hpp>
# include <boost/python/converter/type_id.hpp>
# include <boost/python/reference.hpp>
# include <boost/iterator_adaptors.hpp>
# include <cstddef>

namespace boost { namespace python {

class module;

namespace objects { 

template <class T> struct holder;

// To identify a class, we don't need cv/reference decorations
typedef converter::undecorated_type_id_t class_id;

struct BOOST_PYTHON_DECL class_base : private noncopyable
{
    // constructor
    class_base(
        char const* name              // The name of the class
        
        , std::size_t num_types         // A list of class_ids. The first is the type
        , class_id const*const types    // this is wrapping. The rest are the types of
                                        // any bases.
        );

    // Retrieve the underlying object
    ref object() const { return m_object; }
 private:
    ref m_object;
};

// Base class for all holders
struct BOOST_PYTHON_DECL instance_holder : private noncopyable
{
 public:
    instance_holder();
    virtual ~instance_holder();
    
    // return the next holder in a chain
    instance_holder* next() const;

    virtual void* holds(converter::undecorated_type_id_t) = 0;

    void install(PyObject* inst) throw();
    
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

// Given an undecorated type_id, find the instance data which
// corresponds to it, or return 0 in case no such type is held.
BOOST_PYTHON_DECL void* find_instance_impl(PyObject*, converter::undecorated_type_id_t);

// This produces a function with the right signature for use in from_python conversions
template <class T>
struct instance_finder
{
    static inline void* execute(PyObject* p)
    {
        return find_instance_impl(p, converter::undecorated_type_id<T>());
    }
};

BOOST_PYTHON_DECL ref class_metatype();
BOOST_PYTHON_DECL ref class_type();

//
// implementation
//
inline instance_holder* instance_holder::next() const
{
    return m_next;
}

}}} // namespace boost::python::objects

#endif // CLASS_DWA20011214_HPP
