#ifndef CLASS_WRAPPER_DWA101000_H_
# define CLASS_WRAPPER_DWA101000_H_

#include <boost/python/detail/extension_class.hpp>
#include <boost/python/operators.hpp>
#include <boost/python/module_builder.hpp>
#include <boost/python/conversions.hpp>
#include <boost/python/detail/cast.hpp>
#include <boost/python/reference.hpp>

namespace boost { namespace python {

// Syntactic sugar to make wrapping classes more convenient
template <class T, class U = detail::held_instance<T> >
class class_builder
    : python_extension_class_converters<T, U> // Works around MSVC6.x/GCC2.95.2 bug described below
{
 public:
    class_builder(module_builder& module, const char* name,
                  bool auto_pickle = false)
        : m_class(new detail::extension_class<T, U>(name))
    {
        module.add(ref(as_object(m_class.get()), ref::increment_count), name);
        if (auto_pickle) {
          add(ref(BOOST_PYTHON_CONVERSION::to_python(1)), "__auto_pickle__");
        }
    }
    
    ~class_builder()
    {}
    
    // define constructors
    template <class signature>
    void def(const signature& s)
        { m_class->def(s); }

    // export heterogeneous reverse-argument operators 
    // (type of lhs: 'left', of rhs: 'right')
    // usage:  foo_class.def(boost::python::operators<(boost::python::op_add | boost::python::op_sub), Foo>(),
    //                       boost::python::left_operand<int const &>());
    template <long which, class left, class right>
    void def(operators<which, right> o1, left_operand<left> o2)
        { m_class->def(o1, o2); }

    // export heterogeneous operators (type of lhs: 'left', of rhs: 'right')
    // usage:  foo_class.def(boost::python::operators<(boost::python::op_add | boost::python::op_sub), Foo>(),
    //                       boost::python::right_operand<int const &>());
    template <long which, class left, class right>
    void def(operators<which, left> o1, right_operand<right> o2)
        { m_class->def(o1, o2); }

    // define a function that passes Python arguments and keywords
    // to C++ verbatim (as a 'tuple const &' and 'dictionary const &' 
    // respectively). This is useful for manual argument passing.
    // It's also the only possibility to pass keyword arguments to C++.
    // Fn must have a signatur that is compatible to 
    //     PyObject * (*)(PyObject * aTuple, PyObject * aDictionary)
    template <class Fn>
    void def_raw(Fn fn, const char* name)
        { m_class->def_raw(fn, name); }

    // define member functions. In fact this works for free functions, too -
    // they act like static member functions, or if they start with the
    // appropriate self argument (as a pointer or reference), they can be used
    // just like ordinary member functions -- just like Python!
    template <class Fn>
    void def(Fn fn, const char* name)
        { m_class->def(fn, name); }

    // Define a virtual member function with a default implementation.
    // default_fn should be a function which provides the default implementation.
    // Be careful that default_fn does not in fact call fn virtually!
    template <class Fn, class DefaultFn>
    void def(Fn fn, const char* name, DefaultFn default_fn)
        { m_class->def(fn, name, default_fn); }

    // Provide a function which implements x.<name>, reading from the given
    // member (pm) of the T obj
    template <class MemberType>
    void def_getter(MemberType T::*pm, const char* name)
        { m_class->def_getter(pm, name); }
    
    // Provide a function which implements assignment to x.<name>, writing to
    // the given member (pm) of the T obj
    template <class MemberType>
    void def_setter(MemberType T::*pm, const char* name)
        { m_class->def_getter(pm, name); }
    
    // Expose the given member (pm) of the T obj as a read-only attribute
    template <class MemberType>
    void def_readonly(MemberType T::*pm, const char* name)
        { m_class->def_readonly(pm, name); }
    
    // Expose the given member (pm) of the T obj as a read/write attribute
    template <class MemberType>
    void def_read_write(MemberType T::*pm, const char* name)
        { m_class->def_read_write(pm, name); }
        
    // define the standard coercion needed for operator overloading
    void def_standard_coerce()
        { m_class->def_standard_coerce(); }
    
    // declare the given class a base class of this one and register 
    // conversion functions
    template <class S, class V>
    void declare_base(class_builder<S, V> const & base)
    {
        m_class->declare_base(base.get_extension_class());
    }

    // declare the given class a base class of this one and register 
    // upcast conversion function
    template <class S, class V>
    void declare_base(class_builder<S, V> const & base, without_downcast_t)
    {
        m_class->declare_base(base.get_extension_class(), without_downcast);
    }

    // get the embedded ExtensioClass object
    detail::extension_class<T, U> * get_extension_class() const 
    {
        return m_class.get();
    }

    // set an arbitrary attribute. Useful for non-function class data members,
    // e.g. enums
    void add(PyObject* x, const char* name)
        { m_class->set_attribute(name, x); }
    void add(ref x, const char* name)
        { m_class->set_attribute(name, x); }
 private:
    // declare the given class a base class of this one and register 
    // conversion functions
    template <class S, class V>
    void declare_base(detail::extension_class<S, V> * base)
    {
        m_class->declare_base(base);
    }
        
    // declare the given class a base class of this one and register 
    // upcast conversion function
    template <class S, class V>
    void declare_base(detail::extension_class<S, V> * base, without_downcast_t)
    {
        m_class->declare_base(base, without_downcast);
    }
    
    reference<detail::extension_class<T, U> > m_class;
};

// The bug mentioned at the top of this file is that on certain compilers static
// global functions declared within the body of a class template will only be
// generated when the class template is constructed, and when (for some reason)
// the construction does not occur via a new-expression. Otherwise, we could
// rely on the initialization of the m_class data member to cause all of the
// to_/from_python functions to come into being.

}} // namespace boost::python

#endif // CLASS_WRAPPER_DWA101000_H_
