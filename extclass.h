//  (C) Copyright David Abrahams 2000. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
//  The author gratefully acknowleges the support of Dragon Systems, Inc., in
//  producing this work.
//
//  This file automatically generated for 5-argument constructors by
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

    void set_attribute(const char* name, PyObject* x);
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

namespace detail
{
    struct operator_dispatcher
    : public PyObject
    {
        static PyTypeObject type_object;
        static PyNumberMethods number_methods;

        operator_dispatcher(PyObject * o, PyObject * s);
        static void dealloc(PyObject *self);
        static int coerce(PyObject ** l, PyObject ** r);
        static PyObject * call_add(PyObject *, PyObject *);
        static PyObject * call_sub(PyObject *, PyObject *);
        static PyObject * call_mul(PyObject *, PyObject *);
        static PyObject * call_div(PyObject *, PyObject *);
        static PyObject * call_mod(PyObject *, PyObject *);
        static PyObject * call_divmod(PyObject *, PyObject *);
        static PyObject * call_lshift(PyObject *, PyObject *);
        static PyObject * call_rshift(PyObject *, PyObject *);
        static PyObject * call_and(PyObject *, PyObject *);
        static PyObject * call_xor(PyObject *, PyObject *);
        static PyObject * call_or(PyObject *, PyObject *);
        static PyObject * call_pow(PyObject *, PyObject *, PyObject *);
        static int call_cmp(PyObject *, PyObject *);

        static bool unwrap_args(PyObject *  left, PyObject * right, 
                                PyObject * & self, PyObject * & other);
        static int unwrap_pow_args(PyObject *, PyObject *, PyObject *,
                                    PyObject * &, PyObject * &, PyObject * &);

        PyObject * object;
        PyObject * self;
    };
}

}

PY_BEGIN_CONVERSION_NAMESPACE

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
    //     PyObject* to_python(const T& x)
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
    //     PyObject* to_python(const T& x)
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

    // Convert to const T* const&
    friend const T* from_python(PyObject* p, py::Type<const T *const&>)
         { return from_python(p, py::Type<const T*>()); }
  
    // Convert to T* const&
    friend T* from_python(PyObject* p, py::Type<T* const&>)
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

inline PyObject * to_python(py::detail::operator_dispatcher * n) { return n; }


PY_END_CONVERSION_NAMESPACE

namespace py {

PY_IMPORT_CONVERSION(PyExtensionClassConverters);

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

enum operator_id
{ 
    op_add = 0x1, 
    op_sub = 0x2, 
    op_mul = 0x4, 
    op_div = 0x8, 
    op_mod = 0x10, 
    op_divmod =0x20, 
    op_pow = 0x40, 
    op_lshift = 0x80, 
    op_rshift = 0x100, 
    op_and = 0x200, 
    op_xor = 0x400, 
    op_or = 0x800, 
    op_neg = 0x1000, 
    op_pos = 0x2000, 
    op_abs = 0x4000, 
    op_invert = 0x8000, 
    op_int = 0x10000, 
    op_long = 0x20000, 
    op_float = 0x40000, 
    op_str = 0x80000,
    op_cmp = 0x100000 
};

namespace detail
{

    struct auto_operand {};

    template <int i>
    struct define_operator;

}

template <int which, class operand = py::detail::auto_operand>
struct operators {};

template <class T>
struct left_operand {};

template <class T>
struct right_operand {};

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
    template <class A1, class A2, class A3, class A4, class A5>
    void def(Constructor<A1, A2, A3, A4, A5>)
    // The following incantation builds a Signature1, Signature2,... object. It
    // should _all_ get optimized away.
    { add_constructor(
        prepend(Type<A1>::Id(),
        prepend(Type<A2>::Id(),
        prepend(Type<A3>::Id(),
        prepend(Type<A4>::Id(),
        prepend(Type<A5>::Id(),
                Signature0()))))));
    }


    // export homogeneous operators (type of both lhs and rhs is 'operator')
    // usage:  foo_class.def(py::operators<(py::op_add | py::op_sub), Foo>());
    template <int which, class operand>
    void def(operators<which, operand>)
    {
        register_coerce();
        
        if(which & py::op_add)
            add_method(new typename detail::define_operator<(which & py::op_add)>::
                operator_function<operand>(),
                detail::define_operator<(which & py::op_add)>::name());
                
        if(which & py::op_sub)
            add_method(new typename detail::define_operator<(which & py::op_sub)>::
                operator_function<operand>(),
                detail::define_operator<(which & py::op_sub)>::name());
                
        if(which & py::op_mul)
            add_method(new typename detail::define_operator<(which & py::op_mul)>::
                operator_function<operand>(),
                detail::define_operator<(which & py::op_mul)>::name());
                
        if(which & py::op_div)
            add_method(new typename detail::define_operator<(which & py::op_div)>::
                operator_function<operand>(),
                detail::define_operator<(which & py::op_div)>::name());
                
        if(which & py::op_mod)
            add_method(new typename detail::define_operator<(which & py::op_mod)>::
                operator_function<operand>(),
                detail::define_operator<(which & py::op_mod)>::name());
                
        if(which & py::op_divmod)
            add_method(new typename detail::define_operator<(which & py::op_divmod)>::
                operator_function<operand>(),
                detail::define_operator<(which & py::op_divmod)>::name());
                
        if(which & py::op_pow)
            add_method(new typename detail::define_operator<(which & py::op_pow)>::
                operator_function<operand>(),
                detail::define_operator<(which & py::op_pow)>::name());
                
        if(which & py::op_lshift)
            add_method(new typename detail::define_operator<(which & py::op_lshift)>::
                operator_function<operand>(),
                detail::define_operator<(which & py::op_lshift)>::name());
                
        if(which & py::op_rshift)
            add_method(new typename detail::define_operator<(which & py::op_rshift)>::
                operator_function<operand>(),
                detail::define_operator<(which & py::op_rshift)>::name());
                
        if(which & py::op_and)
            add_method(new typename detail::define_operator<(which & py::op_and)>::
                operator_function<operand>(),
                detail::define_operator<(which & py::op_and)>::name());
                
        if(which & py::op_xor)
            add_method(new typename detail::define_operator<(which & py::op_xor)>::
                operator_function<operand>(),
                detail::define_operator<(which & py::op_xor)>::name());
                
        if(which & py::op_or)
            add_method(new typename detail::define_operator<(which & py::op_or)>::
                operator_function<operand>(),
                detail::define_operator<(which & py::op_or)>::name());
                
        if(which & py::op_neg)
            add_method(new typename detail::define_operator<(which & py::op_neg)>::
                operator_function<operand>(),
                detail::define_operator<(which & py::op_neg)>::name());
                
        if(which & py::op_pos)
            add_method(new typename detail::define_operator<(which & py::op_pos)>::
                operator_function<operand>(),
                detail::define_operator<(which & py::op_pos)>::name());
                
        if(which & py::op_abs)
            add_method(new typename detail::define_operator<(which & py::op_abs)>::
                operator_function<operand>(),
                detail::define_operator<(which & py::op_abs)>::name());
                
        if(which & py::op_invert)
            add_method(new typename detail::define_operator<(which & py::op_invert)>::
                operator_function<operand>(),
                detail::define_operator<(which & py::op_invert)>::name());
                
        if(which & py::op_int)
            add_method(new typename detail::define_operator<(which & py::op_int)>::
                operator_function<operand>(),
                detail::define_operator<(which & py::op_int)>::name());
                
        if(which & py::op_long)
            add_method(new typename detail::define_operator<(which & py::op_long)>::
                operator_function<operand>(),
                detail::define_operator<(which & py::op_long)>::name());
                
        if(which & py::op_float)
            add_method(new typename detail::define_operator<(which & py::op_float)>::
                operator_function<operand>(),
                detail::define_operator<(which & py::op_float)>::name());
                
        if(which & py::op_cmp)
            add_method(new typename detail::define_operator<(which & py::op_cmp)>::
                operator_function<operand>(),
                detail::define_operator<(which & py::op_cmp)>::name());
                
        if(which & py::op_str)
            add_method(new typename detail::define_operator<(which & py::op_str)>::
                operator_function<operand>(),
                detail::define_operator<(which & py::op_str)>::name());
                
    }

    // export homogeneous operators (type of both lhs and rhs is 'T const &')
    // usage:  foo_class.def(py::operators<(py::op_add | py::op_sub)>());
    template <int which>
    void def(operators<which, py::detail::auto_operand>)
    {
        def(operators<which, T const &>());
    }   

    // export heterogeneous operators (type of lhs: 'left', of rhs: 'right')
    // usage:  foo_class.def(py::operators<(py::op_add | py::op_sub), Foo>(),
    //                       py::right_operand<int const &>());
    template <int which, class left, class right>
    void def(operators<which, left>, right_operand<right>)
    {
        register_coerce();
        
        if(which & py::op_add)
            add_method(new typename detail::define_operator<(which & py::op_add)>::
                operator_function<left, right>(),
                detail::define_operator<(which & py::op_add)>::name());
                
        if(which & py::op_sub)
            add_method(new typename detail::define_operator<(which & py::op_sub)>::
                operator_function<left, right>(),
                detail::define_operator<(which & py::op_sub)>::name());
                
        if(which & py::op_mul)
            add_method(new typename detail::define_operator<(which & py::op_mul)>::
                operator_function<left, right>(),
                detail::define_operator<(which & py::op_mul)>::name());
                
        if(which & py::op_div)
            add_method(new typename detail::define_operator<(which & py::op_div)>::
                operator_function<left, right>(),
                detail::define_operator<(which & py::op_div)>::name());
                
        if(which & py::op_mod)
            add_method(new typename detail::define_operator<(which & py::op_mod)>::
                operator_function<left, right>(),
                detail::define_operator<(which & py::op_mod)>::name());
                
        if(which & py::op_divmod)
            add_method(new typename detail::define_operator<(which & py::op_divmod)>::
                operator_function<left, right>(),
                detail::define_operator<(which & py::op_divmod)>::name());
                
        if(which & py::op_pow)
            add_method(new typename detail::define_operator<(which & py::op_pow)>::
                operator_function<left, right>(),
                detail::define_operator<(which & py::op_pow)>::name());
                
        if(which & py::op_lshift)
            add_method(new typename detail::define_operator<(which & py::op_lshift)>::
                operator_function<left, right>(),
                detail::define_operator<(which & py::op_lshift)>::name());
                
        if(which & py::op_rshift)
            add_method(new typename detail::define_operator<(which & py::op_rshift)>::
                operator_function<left, right>(),
                detail::define_operator<(which & py::op_rshift)>::name());
                
        if(which & py::op_and)
            add_method(new typename detail::define_operator<(which & py::op_and)>::
                operator_function<left, right>(),
                detail::define_operator<(which & py::op_and)>::name());
                
        if(which & py::op_xor)
            add_method(new typename detail::define_operator<(which & py::op_xor)>::
                operator_function<left, right>(),
                detail::define_operator<(which & py::op_xor)>::name());
                
        if(which & py::op_or)
            add_method(new typename detail::define_operator<(which & py::op_or)>::
                operator_function<left, right>(),
                detail::define_operator<(which & py::op_or)>::name());
                
        if(which & py::op_cmp)
            add_method(new typename detail::define_operator<(which & py::op_cmp)>::
                operator_function<left, right>(),
                detail::define_operator<(which & py::op_cmp)>::name());
                
    }
    
    // export heterogeneous operators (type of lhs: 'T const &', of rhs: 'right')
    // usage:  foo_class.def(py::operators<(py::op_add | py::op_sub)>(),
    //                       py::right_operand<int const &>());
    template <int which, class right>
    void def(operators<which, py::detail::auto_operand>, right_operand<right> r)
    {
        def(operators<which, T const &>(), r);
    }

    // export heterogeneous reverse-argument operators 
    // (type of lhs: 'left', of rhs: 'right')
    // usage:  foo_class.def(py::operators<(py::op_add | py::op_sub), Foo>(),
    //                       py::left_operand<int const &>());
    template <int which, class left, class right>
    void def(operators<which, right>, left_operand<left>)
    {
        register_coerce();
        
        if(which & py::op_add)
            add_method(new typename detail::define_operator<(which & py::op_add)>::
                roperator_function<right, left>(),
                detail::define_operator<(which & py::op_add)>::rname());
                
        if(which & py::op_sub)
            add_method(new typename detail::define_operator<(which & py::op_sub)>::
                roperator_function<right, left>(),
                detail::define_operator<(which & py::op_sub)>::rname());
                
        if(which & py::op_mul)
            add_method(new typename detail::define_operator<(which & py::op_mul)>::
                roperator_function<right, left>(),
                detail::define_operator<(which & py::op_mul)>::rname());
                
        if(which & py::op_div)
            add_method(new typename detail::define_operator<(which & py::op_div)>::
                roperator_function<right, left>(),
                detail::define_operator<(which & py::op_div)>::rname());
                
        if(which & py::op_mod)
            add_method(new typename detail::define_operator<(which & py::op_mod)>::
                roperator_function<right, left>(),
                detail::define_operator<(which & py::op_mod)>::rname());
                
        if(which & py::op_divmod)
            add_method(new typename detail::define_operator<(which & py::op_divmod)>::
                roperator_function<right, left>(),
                detail::define_operator<(which & py::op_divmod)>::rname());
                
        if(which & py::op_pow)
            add_method(new typename detail::define_operator<(which & py::op_pow)>::
                roperator_function<right, left>(),
                detail::define_operator<(which & py::op_pow)>::rname());
                
        if(which & py::op_lshift)
            add_method(new typename detail::define_operator<(which & py::op_lshift)>::
                roperator_function<right, left>(),
                detail::define_operator<(which & py::op_lshift)>::rname());
                
        if(which & py::op_rshift)
            add_method(new typename detail::define_operator<(which & py::op_rshift)>::
                roperator_function<right, left>(),
                detail::define_operator<(which & py::op_rshift)>::rname());
                
        if(which & py::op_and)
            add_method(new typename detail::define_operator<(which & py::op_and)>::
                roperator_function<right, left>(),
                detail::define_operator<(which & py::op_and)>::rname());
                
        if(which & py::op_xor)
            add_method(new typename detail::define_operator<(which & py::op_xor)>::
                roperator_function<right, left>(),
                detail::define_operator<(which & py::op_xor)>::rname());
                
        if(which & py::op_or)
            add_method(new typename detail::define_operator<(which & py::op_or)>::
                roperator_function<right, left>(),
                detail::define_operator<(which & py::op_or)>::rname());
                
        if(which & py::op_cmp)
            add_method(new typename detail::define_operator<(which & py::op_cmp)>::
                roperator_function<right, left>(),
                detail::define_operator<(which & py::op_cmp)>::rname());
                
    }
    
    // export heterogeneous reverse-argument operators 
    // (type of lhs: 'left', of rhs: 'T const &')
    // usage:  foo_class.def(py::operators<(py::op_add | py::op_sub)>(),
    //                       py::left_operand<int const &>());
    template <int which, class left>
    void def(operators<which, py::detail::auto_operand>, left_operand<left> l)
    {
        def(operators<which, T const &>(), l);
    }

    // define a function that passes Python arguments and keywords
    // to C++ verbatim (as a 'Tuple const &' and 'Dict const &' 
    // respectively). This is useful for manual argument passing.
    // It's also the only possibility to pass keyword arguments to C++.
    // Fn must have a signatur that is compatible to 
    //     PyObject * (*)(PyObject * aTuple, PyObject * aDictionary)
    template <class Fn>
    void def_raw(Fn fn, const char* name)
    {
        this->add_method(py::detail::new_raw_arguments_function(fn), name);
    }

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
    
    void register_coerce();
};

// A simple wrapper over a T which allows us to use ExtensionClass<T> with a
// single template parameter only. See ExtensionClass<T>, above.
template <class T>
class HeldInstance : public T
{
    // There are no member functions: we want to avoid inadvertently overriding
    // any virtual functions in T.
public:
    HeldInstance(PyObject*) : T() {}
    template <class A1>
    HeldInstance(PyObject*, A1 a1) : T(a1) {}
    template <class A1, class A2>
    HeldInstance(PyObject*, A1 a1, A2 a2) : T(a1, a2) {}
    template <class A1, class A2, class A3>
    HeldInstance(PyObject*, A1 a1, A2 a2, A3 a3) : T(a1, a2, a3) {}
    template <class A1, class A2, class A3, class A4>
    HeldInstance(PyObject*, A1 a1, A2 a2, A3 a3, A4 a4) : T(a1, a2, a3, a4) {}
    template <class A1, class A2, class A3, class A4, class A5>
    HeldInstance(PyObject*, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) : T(a1, a2, a3, a4, a5) {}
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

    InstanceValueHolder(ExtensionInstance* p) :
        m_held(p) {}
    template <class A1>
    InstanceValueHolder(ExtensionInstance* p, A1 a1) :
        m_held(p, a1) {}
    template <class A1, class A2>
    InstanceValueHolder(ExtensionInstance* p, A1 a1, A2 a2) :
        m_held(p, a1, a2) {}
    template <class A1, class A2, class A3>
    InstanceValueHolder(ExtensionInstance* p, A1 a1, A2 a2, A3 a3) :
        m_held(p, a1, a2, a3) {}
    template <class A1, class A2, class A3, class A4>
    InstanceValueHolder(ExtensionInstance* p, A1 a1, A2 a2, A3 a3, A4 a4) :
        m_held(p, a1, a2, a3, a4) {}
    template <class A1, class A2, class A3, class A4, class A5>
    InstanceValueHolder(ExtensionInstance* p, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) :
        m_held(p, a1, a2, a3, a4, a5) {}

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

namespace detail
{
    Tuple extension_class_coerce(PyObject * l, PyObject * r);
}

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
void ExtensionClass<T, U>::register_coerce()
{
    Ptr coerce_fct = dict().get_item(String("__coerce__"));
    
    if(coerce_fct.get() == 0) // not yet defined
        this->def(&py::detail::extension_class_coerce, "__coerce__");
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

