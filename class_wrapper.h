#ifndef CLASS_WRAPPER_DWA101000_H_
# define CLASS_WRAPPER_DWA101000_H_

#include "extclass.h"
#include "module.h"
#include "py.h"
#include "cast.h"

namespace py {

namespace detail {
struct EmptyBase {};
}

// Syntactic sugar to make wrapping classes more convenient
template <class T, class U = HeldInstance<T> >
class ClassWrapper
    : PyExtensionClassConverters<T, U> // Works around MSVC6.x/GCC2.95.2 bug described below
{
 public:
    ClassWrapper(Module& module, const char* name)
        : m_class(new ExtensionClass<T, U>(name))
    {
        module.add(Ptr(as_object(m_class.get()), Ptr::new_ref), name);
    }
    
    // define constructors
    template <class Signature>
    void def(const Signature& signature)
        { m_class->def(signature); }

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
    // member (pm) of the T instance
    template <class MemberType>
    void def_getter(MemberType T::*pm, const char* name)
        { m_class->def_getter(pm, name); }
    
    // Provide a function which implements assignment to x.<name>, writing to
    // the given member (pm) of the T instance
    template <class MemberType>
    void def_setter(MemberType T::*pm, const char* name)
        { m_class->def_getter(pm, name); }
    
    // Expose the given member (pm) of the T instance as a read-only attribute
    template <class MemberType>
    void def_readonly(MemberType T::*pm, const char* name)
        { m_class->def_readonly(pm, name); }
    
    // Expose the given member (pm) of the T instance as a read/write attribute
    template <class MemberType>
    void def_read_write(MemberType T::*pm, const char* name)
        { m_class->def_read_write(pm, name); }
        
    // declare the given class a base class of this one and register 
    // conversion functions
    template <class S, class V>
    void declare_base(ClassWrapper<S, V> const & base)
    {
        m_class->declare_base(base.get_extension_class());
    }

    // declare the given class a base class of this one and register 
    // upcast conversion function
    template <class S, class V>
    void declare_base(ClassWrapper<S, V> const & base, WithoutDowncast)
    {
        m_class->declare_base(base.get_extension_class(), without_downcast);
    }

    // declare the given class a base class of this one and register 
    // conversion functions
    template <class S, class V>
    void declare_base(ExtensionClass<S, V> * base)
    {
        m_class->declare_base(base);
    }
        
    // declare the given class a base class of this one and register 
    // upcast conversion function
    template <class S, class V>
    void declare_base(ExtensionClass<S, V> * base, WithoutDowncast)
    {
        m_class->declare_base(base, without_downcast);
    }
    
    // get the embedded ExtensioClass object
    ExtensionClass<T, U> * get_extension_class() const 
    {
        return m_class.get();
    }
    
 private:
    PyPtr<ExtensionClass<T, U> > m_class;
};

// The bug mentioned at the top of this file is that on certain compilers static
// global functions declared within the body of a class template will only be
// generated when the class template is constructed, and when (for some reason)
// the construction does not occur via a new-expression. Otherwise, we could
// rely on the initialization of the m_class data member to cause all of the
// to_/from_python functions to come into being.

}

#endif // CLASS_WRAPPER_DWA101000_H_
