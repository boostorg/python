from gen_function import *
import string

def gen_extclass(args):
    return (
"""//  (C) Copyright David Abrahams 2000. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
//  The author gratefully acknowleges the support of Dragon Systems, Inc., in
//  producing this work.
//
//  This file automatically generated for %d-argument constructors by
//  gen_extclass.py

#ifndef EXTENSION_CLASS_DWA052000_H_
# define EXTENSION_CLASS_DWA052000_H_

# include "pyconfig.h"
# include "subclass.h"
# include <vector>
# include "none.h"
# include "objects.h"
# include "functions.h"
# include <memory>
# include "init_function.h"
# include <typeinfo>
# include <boost/smart_ptr.hpp>

namespace py {

// forward declarations
class ExtensionInstance;
class ExtensionClassBase;
template <class T> class InstanceHolder;
template <class T, class U> class InstanceValueHolder;
template <class Ptr, class T> class InstancePtrHolder;

MetaClass<ExtensionInstance>* extension_meta_class();
ExtensionInstance* get_extension_instance(PyObject* p);
void report_missing_instance_data(ExtensionInstance*, Class<ExtensionInstance>*, const std::type_info&);
void report_missing_ptr_data(ExtensionInstance*, Class<ExtensionInstance>*, const std::type_info&);
void report_missing_class_object(const std::type_info&);
void report_released_smart_pointer(const std::type_info&);
    
template <class T, class U>
struct ExtensionClassFromPython
{
};

template <class T>
T* check_non_null(T* p)
{
    if (p == 0)
        report_released_smart_pointer(typeid(T));
    return p;
}

template <class T> class HeldInstance;

namespace detail {
  typedef void* (*ConversionFunction)(void*);

  struct BaseClassInfo
  {
      BaseClassInfo(ExtensionClassBase* t, ConversionFunction f)
          :class_object(t), convert(f)
          {}
    
      ExtensionClassBase* class_object;
      ConversionFunction convert;
  };

  typedef BaseClassInfo DerivedClassInfo;
}

class ExtensionClassBase : public Class<ExtensionInstance>
{
 public:
    ExtensionClassBase(const char* name);
    
 public:
    // the purpose of try_class_conversions() and its related functions 
    // is explained in extclass.cpp
    void* try_class_conversions(InstanceHolderBase*) const;
    void* try_base_class_conversions(InstanceHolderBase*) const;
    void* try_derived_class_conversions(InstanceHolderBase*) const;

    void set_attribute(const char* name, PyObject* x_);
    void set_attribute(const char* name, Ptr x);
    
 private:
    virtual void* extract_object_from_holder(InstanceHolderBase* v) const = 0;
    virtual std::vector<py::detail::BaseClassInfo> const& base_classes() const = 0;
    virtual std::vector<py::detail::DerivedClassInfo> const& derived_classes() const = 0;

 protected:
    void add_method(PyPtr<Function> method, const char* name);
    void add_method(Function* method, const char* name);
    
    void add_constructor_object(Function*);
    void add_setter_method(Function*, const char* name);
    void add_getter_method(Function*, const char* name);
};

template <class T>
class ClassRegistry
{
 public:
    static ExtensionClassBase* class_object()
        { return static_class_object; }

    // Register/unregister the Python class object corresponding to T
    static void register_class(ExtensionClassBase*);
    static void unregister_class(ExtensionClassBase*);

    // Establish C++ inheritance relationships
    static void register_base_class(py::detail::BaseClassInfo const&);
    static void register_derived_class(py::detail::DerivedClassInfo const&);

    // Query the C++ inheritance relationships
    static std::vector<py::detail::BaseClassInfo> const& base_classes();
    static std::vector<py::detail::DerivedClassInfo> const& derived_classes();
 private:
    static ExtensionClassBase* static_class_object;
    static std::vector<py::detail::BaseClassInfo> static_base_class_info;
    static std::vector<py::detail::DerivedClassInfo> static_derived_class_info;
};

#ifdef PY_NO_INLINE_FRIENDS_IN_NAMESPACE // back to global namespace for this GCC bug
}
#endif

// This class' only job is to define from_python and to_python converters for T
// and U. T is the class the user really intends to wrap. U is a class derived
// from T with some virtual function overriding boilerplate, or if there are no
// virtual functions, U = HeldInstance<T>.
template <class T, class U = py::HeldInstance<T> >
class PyExtensionClassConverters
{
 public:
    // Get an object which can be used to convert T to/from python. This is used
    // as a kind of concept check by the global template
    //
    //     from_python(PyObject*,  py::Type<const T&>)
    //
    // below this class, to prevent the confusing messages that would otherwise
    // pop up. Now, if T hasn't been wrapped as an extension class, the user
    // will see an error message about the lack of an eligible
    // py_extension_class_converters() function.
    friend PyExtensionClassConverters py_extension_class_converters(py::Type<T>)
    { 
        return PyExtensionClassConverters();
    }

    // This is a member function because in a conforming implementation, friend
    // funcitons defined inline in the class body are all instantiated as soon
    // as the enclosing class is instantiated. If T is not copyable, that causes
    // a compiler error. Instead, we access this function through the global
    // template 
    //
    //     from_python(PyObject*,  py::Type<const T&>)
    //
    // defined below this class. Since template functions are instantiated only
    // on demand, errors will be avoided unless T is noncopyable and the user
    // writes code which causes us to try to copy a T.
    PyObject* to_python(const T& x) const
    {
        py::PyPtr<py::ExtensionInstance> result(create_instance());
        result->add_implementation(
            std::auto_ptr<py::InstanceHolderBase>(
                new py::InstanceValueHolder<T,U>(result.get(), x)));
        return result.release();
    }
    
    // Convert to T*
    friend T* from_python(PyObject* obj, py::Type<T*>)
    {
        // Downcast to an ExtensionInstance, then find the actual T
        py::ExtensionInstance* self = py::get_extension_instance(obj);
        typedef std::vector<py::InstanceHolderBase*>::const_iterator Iterator;
        for (Iterator p = self->wrapped_objects().begin();
             p != self->wrapped_objects().end(); ++p)
        {
            py::InstanceHolder<T>* held = dynamic_cast<py::InstanceHolder<T>*>(*p);
            if (held != 0)
                return held->target();

            // see extclass.cpp for an explanation of try_class_conversions()
            void * target = py::ClassRegistry<T>::class_object()->try_class_conversions(*p);
            if(target) 
                return static_cast<T *>(target);
        }
        py::report_missing_instance_data(self, py::ClassRegistry<T>::class_object(), typeid(T));
        throw py::ArgumentError();
    }

    // Convert to PtrType, where PtrType can be dereferenced to obtain a T.
    template <class PtrType>
    static PtrType& ptr_from_python(PyObject* obj, py::Type<PtrType>)
    {
        // Downcast to an ExtensionInstance, then find the actual T
        py::ExtensionInstance* self = py::get_extension_instance(obj);
        typedef std::vector<py::InstanceHolderBase*>::const_iterator Iterator;
        for (Iterator p = self->wrapped_objects().begin();
             p != self->wrapped_objects().end(); ++p)
        {
            py::InstancePtrHolder<PtrType, T>* held =
                dynamic_cast<py::InstancePtrHolder<PtrType, T>*>(*p);
            if (held != 0)
                return held->ptr();
        }
        py::report_missing_ptr_data(self, py::ClassRegistry<T>::class_object(), typeid(T));
        throw py::ArgumentError();
    }

    template <class PtrType>
    static PyObject* ptr_to_python(PtrType x)
    {
        py::PyPtr<py::ExtensionInstance> result(create_instance());
        result->add_implementation(
            std::auto_ptr<py::InstanceHolderBase>(
                new py::InstancePtrHolder<PtrType,T>(x)));
        return result.release();
    }

    static py::PyPtr<py::ExtensionInstance> create_instance()
    {
        PyTypeObject* class_object = py::ClassRegistry<T>::class_object();
        if (class_object == 0)
            py::report_missing_class_object(typeid(T));
            
        return py::PyPtr<py::ExtensionInstance>(
            new py::ExtensionInstance(class_object));
    }

    // Convert to const T*
    friend const T* from_python(PyObject* p, py::Type<const T*>)
        { return from_python(p, py::Type<T*>()); }

    // Convert to T&
    friend T& from_python(PyObject* p, py::Type<T&>)
        { return *py::check_non_null(from_python(p, py::Type<T*>())); }

    // Convert to const T&
    friend const T& from_python(PyObject* p, py::Type<const T&>)
        { return from_python(p, py::Type<T&>()); }

    // Convert to T
    friend const T& from_python(PyObject* p, py::Type<T>)
        { return from_python(p, py::Type<T&>()); }

    friend std::auto_ptr<T>& from_python(PyObject* p, py::Type<std::auto_ptr<T>&>)
        { return ptr_from_python(p, py::Type<std::auto_ptr<T> >()); }
    
    friend std::auto_ptr<T>& from_python(PyObject* p, py::Type<std::auto_ptr<T> >)
        { return ptr_from_python(p, py::Type<std::auto_ptr<T> >()); }
    
    friend const std::auto_ptr<T>& from_python(PyObject* p, py::Type<const std::auto_ptr<T>&>)
        { return ptr_from_python(p, py::Type<std::auto_ptr<T> >()); }

    friend PyObject* to_python(std::auto_ptr<T> x)
        { return ptr_to_python(x); }

    friend boost::shared_ptr<T>& from_python(PyObject* p, py::Type<boost::shared_ptr<T>&>)
        { return ptr_from_python(p, py::Type<boost::shared_ptr<T> >()); }
    
    friend boost::shared_ptr<T>& from_python(PyObject* p, py::Type<boost::shared_ptr<T> >)
        { return ptr_from_python(p, py::Type<boost::shared_ptr<T> >()); }
    
    friend const boost::shared_ptr<T>& from_python(PyObject* p, py::Type<const boost::shared_ptr<T>&>)
        { return ptr_from_python(p, py::Type<boost::shared_ptr<T> >()); }

    friend PyObject* to_python(boost::shared_ptr<T> x)
        { return ptr_to_python(x); }
};

// Convert T to_python, instantiated on demand and only if there isn't a
// non-template overload for this function. This version is the one invoked when
// T is a wrapped class. See the first 2 functions declared in
// PyExtensionClassConverters above for more info.
template <class T>
PyObject* to_python(const T& x)
{
    return py_extension_class_converters(py::Type<T>()).to_python(x);
}

#ifdef PY_NO_INLINE_FRIENDS_IN_NAMESPACE // back from global namespace for this GCC bug
namespace py {
using ::PyExtensionClassConverters;
#endif

template <class T> class InstanceHolder;

class ReadOnlySetattrFunction : public Function
{
 public:
    ReadOnlySetattrFunction(const char* name);
    PyObject* do_call(PyObject* args, PyObject* keywords) const;
    const char* description() const;
 private:
    String m_name;
};

namespace detail
{

  template <class From, class To>
  struct DefineConversion
  {
      static void * upcast_ptr(void * v)
      {
          return static_cast<To *>(static_cast<From *>(v));
      }

      static void * downcast_ptr(void * v)
      {
          return dynamic_cast<To *>(static_cast<From *>(v));
      }
  };

}

enum WithoutDowncast { without_downcast };

// An easy way to make an extension base class which wraps T. Note that Python
// subclasses of this class will simply be Class<ExtensionInstance> objects.
//
// U should be a class derived from T which overrides virtual functions with
// boilerplate code to call back into Python. See extclass_demo.h for examples.
// 
// U is optional, but you won't be able to override any member functions in
// Python which are called from C++ if you don't supply it. If you just want to
// be able to use T in python without overriding member functions, you can omit
// U.
template <class T, class U = HeldInstance<T> >
class ExtensionClass
    : public PyExtensionClassConverters<T, U>, // This generates the to_python/from_python functions
      public ExtensionClassBase
{
 public:
    typedef T WrappedType;
    typedef U CallbackType;
    
    // Construct with a name that comes from typeid(T).name(). The name only
    // affects the objects of this class are represented through repr()
    ExtensionClass();
    
    // Construct with the given name. The name only affects the objects of this
    // class are represented through repr()
    ExtensionClass(const char* name);
    
    ~ExtensionClass();

    // define constructors
""" % args
        + gen_function(
"""    template <%(class A%n%:, %)>
    void def(Constructor<%(A%n%:, %)>)
    // The following incantation builds a Signature1, Signature2,... object. It
    // should _all_ get optimized away.
    { add_constructor(
        %(prepend(Type<A%n>::Id(),
        %)        Signature0()%()%));
    }
""", args)
        +
"""
    // define member functions. In fact this works for free functions, too -
    // they act like static member functions, or if they start with the
    // appropriate self argument (as a pointer), they can be used just like
    // ordinary member functions -- just like Python!
    template <class Fn>
    void def(Fn fn, const char* name)
    {
        this->add_method(new_wrapped_function(fn), name);
    }

    // Define a virtual member function with a default implementation.
    // default_fn should be a function which provides the default implementation.
    // Be careful that default_fn does not in fact call fn virtually!
    template <class Fn, class DefaultFn>
    void def(Fn fn, const char* name, DefaultFn default_fn)
    {
        this->add_method(py::detail::new_virtual_function(Type<T>(), fn, default_fn), name);
    }

    // Provide a function which implements x.<name>, reading from the given
    // member (pm) of the T instance
    template <class MemberType>
    void def_getter(MemberType T::*pm, const char* name)
    {
        this->add_getter_method(new GetterFunction<T, MemberType>(pm), name);
    }
    
    // Provide a function which implements assignment to x.<name>, writing to
    // the given member (pm) of the T instance
    template <class MemberType>
    void def_setter(MemberType T::*pm, const char* name)
    {
        this->add_setter_method(new SetterFunction<T, MemberType>(pm), name);
    }
    
    // Expose the given member (pm) of the T instance as a read-only attribute
    template <class MemberType>
    void def_readonly(MemberType T::*pm, const char* name)
    {
        this->add_setter_method(new ReadOnlySetattrFunction(name), name);
        this->def_getter(pm, name);
    }
    
    // Expose the given member (pm) of the T instance as a read/write attribute
    template <class MemberType>
    void def_read_write(MemberType T::*pm, const char* name)
    {
        this->def_getter(pm, name);
        this->def_setter(pm, name);
    }
        
    // declare the given class a base class of this one and register 
    // up and down conversion functions
    template <class S, class V>
    void declare_base(ExtensionClass<S, V> * base)
    {
        // see extclass.cpp for an explanation of why we need to register
        // conversion functions
        detail::BaseClassInfo baseInfo(base, 
                            &detail::DefineConversion<S, T>::downcast_ptr);
        ClassRegistry<T>::register_base_class(baseInfo);
        add_base(Ptr(as_object(base), Ptr::new_ref));
        
        detail::DerivedClassInfo derivedInfo(this, 
                            &detail::DefineConversion<T, S>::upcast_ptr);
        ClassRegistry<S>::register_derived_class(derivedInfo);
    }
        
    // declare the given class a base class of this one and register 
    // only up conversion function
    template <class S, class V>
    void declare_base(ExtensionClass<S, V> * base, WithoutDowncast)
    {
        // see extclass.cpp for an explanation of why we need to register
        // conversion functions
        detail::BaseClassInfo baseInfo(base, 0);
        ClassRegistry<T>::register_base_class(baseInfo);
        add_base(Ptr(as_object(base), Ptr::new_ref));
        
        detail::DerivedClassInfo derivedInfo(this, 
                           &detail::DefineConversion<T, S>::upcast_ptr);
        ClassRegistry<S>::register_derived_class(derivedInfo);
    }
    
 private: // types
    typedef InstanceValueHolder<T,U> Holder;

 private: // ExtensionClassBase virtual function implementations
    std::vector<detail::BaseClassInfo> const& base_classes() const;
    std::vector<detail::DerivedClassInfo> const& derived_classes() const;
    void* extract_object_from_holder(InstanceHolderBase* v) const;

 private: // Utility functions
    template <class Signature>
    void add_constructor(Signature sig)
    {
        this->add_constructor_object(InitFunction<Holder>::create(sig));
    }
};

// A simple wrapper over a T which allows us to use ExtensionClass<T> with a
// single template parameter only. See ExtensionClass<T>, above.
template <class T>
class HeldInstance : public T
{
    // There are no member functions: we want to avoid inadvertently overriding
    // any virtual functions in T.
public:"""
        + gen_functions("""%{
    template <%(class A%n%:, %)>%}
    HeldInstance(PyObject*%(, A%n% a%n%)) : T(%(a%n%:, %)) {}""", args)
        + """
};

// Abstract base class for all instance holders. Base for template class
// InstanceHolder<>, below.
class InstanceHolderBase
{
public:
    virtual ~InstanceHolderBase() {}
    virtual bool held_by_value() = 0;
};

// Abstract base class which holds a Held, somehow. Provides a uniform way to
// get a pointer to the held object
template <class Held>
class InstanceHolder : public InstanceHolderBase
{
public:
    virtual Held *target() = 0;
};

// Concrete class which holds a Held by way of a wrapper class Wrapper. If Held
// can be constructed with arguments (A1...An), Wrapper must have a
// corresponding constructor for arguments (PyObject*, A1...An). Wrapper is
// neccessary to implement virtual function callbacks (there must be a
// back-pointer to the actual Python object so that we can call any
// overrides). HeldInstance (above) is used as a default Wrapper class when
// there are no virtual functions.
template <class Held, class Wrapper>
class InstanceValueHolder : public InstanceHolder<Held>
{
public:
    Held* target() { return &m_held; }
    Wrapper* value_target() { return &m_held; }
"""
        + gen_functions("""%{
    template <%(class A%n%:, %)>%}
    InstanceValueHolder(ExtensionInstance* p%(, A%n a%n%)) :
        m_held(p%(, a%n%)) {}""", args)
        + """

 public: // implementation of InstanceHolderBase required interface
    bool held_by_value() { return true; }

 private:
    Wrapper m_held;
};

// Concrete class which holds a HeldType by way of a (possibly smart) pointer
// PtrType. By default, these are only generated for PtrType ==
// std::auto_ptr<HeldType> and PtrType == boost::shared_ptr<HeldType>.
template <class PtrType, class HeldType>
class InstancePtrHolder : public InstanceHolder<HeldType>
{
 public:
    HeldType* target() { return &*m_ptr; }
    PtrType& ptr() { return m_ptr; }

    InstancePtrHolder(PtrType ptr) : m_ptr(ptr) {}
    
 public: // implementation of InstanceHolderBase required interface
    bool held_by_value() { return false; }
 private:
    PtrType m_ptr;
};

class ExtensionInstance : public Instance
{
 public:
    ExtensionInstance(PyTypeObject* class_);
    ~ExtensionInstance();
    
    void add_implementation(std::auto_ptr<InstanceHolderBase> holder);

    typedef std::vector<InstanceHolderBase*> WrappedObjects;
    const WrappedObjects& wrapped_objects() const
        { return m_wrapped_objects; }
 private:
    WrappedObjects m_wrapped_objects;
};

//
// Template function implementations
//

template <class T, class U>
ExtensionClass<T, U>::ExtensionClass()
    : ExtensionClassBase(typeid(T).name())
{
    ClassRegistry<T>::register_class(this);
}

template <class T, class U>
ExtensionClass<T, U>::ExtensionClass(const char* name)
    : ExtensionClassBase(name)
{
    ClassRegistry<T>::register_class(this);
}

template <class T, class U>
inline
std::vector<detail::BaseClassInfo> const & 
ExtensionClass<T, U>::base_classes() const
{
    return ClassRegistry<T>::base_classes();
}

template <class T, class U>
inline
std::vector<detail::DerivedClassInfo> const & 
ExtensionClass<T, U>::derived_classes() const
{
    return ClassRegistry<T>::derived_classes();
}
       
template <class T, class U>
void* ExtensionClass<T, U>::extract_object_from_holder(InstanceHolderBase* v) const
{
    py::InstanceHolder<T>* held = dynamic_cast<py::InstanceHolder<T>*>(v);
    if(held)
        return held->target();
    return 0;
}

template <class T, class U>
ExtensionClass<T, U>::~ExtensionClass()
{
    ClassRegistry<T>::unregister_class(this);
}

template <class T>
inline void ClassRegistry<T>::register_class(ExtensionClassBase* p)
{
    // You're not expected to create more than one of these!
    assert(static_class_object == 0);
    static_class_object = p;
}

template <class T>
inline void ClassRegistry<T>::unregister_class(ExtensionClassBase* p)
{
    // The user should be destroying the same object they created.
    assert(static_class_object == p);
    (void)p; // unused in shipping version
    static_class_object = 0;
}

template <class T>
void ClassRegistry<T>::register_base_class(py::detail::BaseClassInfo const & i)
{
    static_base_class_info.push_back(i);
}

template <class T>
void ClassRegistry<T>::register_derived_class(py::detail::DerivedClassInfo const & i)
{
    static_derived_class_info.push_back(i);
}

template <class T>
std::vector<py::detail::BaseClassInfo> const& ClassRegistry<T>::base_classes()
{
    return static_base_class_info;
}

template <class T>
std::vector<py::detail::DerivedClassInfo> const& ClassRegistry<T>::derived_classes()
{
    return static_derived_class_info;
}

//
// Static data member declaration.
//
template <class T>
ExtensionClassBase* ClassRegistry<T>::static_class_object;
template <class T>
std::vector<py::detail::BaseClassInfo> ClassRegistry<T>::static_base_class_info;
template <class T>
std::vector<py::detail::DerivedClassInfo> ClassRegistry<T>::static_derived_class_info;

} // namespace py

#endif // EXTENSION_CLASS_DWA052000_H_
""")

if __name__ == '__main__':
    import sys

    if len(sys.argv) == 1:
        args = 5
    else:
        args = int(sys.argv[1])

    print gen_extclass(args)
