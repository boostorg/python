//  (C) Copyright David Abrahams 2001. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
//  The author gratefully acknowleges the support of Dragon Systems, Inc., in
//  producing this work.
//
//  This file automatically generated for 10-argument constructors by
//  gen_extclass.python

//  Revision History:
//  17 Apr 01  Comment added with reference to cross_module.hpp (R.W. Grosse-Kunstleve)
//  05 Mar 01  Fixed a bug which prevented auto_ptr values from being converted
//             to_python (Dave Abrahams)

#ifndef EXTENSION_CLASS_DWA052000_H_
# define EXTENSION_CLASS_DWA052000_H_

# include <boost/python/detail/config.hpp>
# include <boost/python/classes.hpp>
# include <vector>
# include <boost/python/detail/none.hpp>
# include <boost/python/objects.hpp>
# include <boost/python/detail/functions.hpp>
# include <memory>
# include <boost/python/detail/init_function.hpp>
# include <typeinfo>
# include <boost/shared_ptr.hpp>
# include <boost/type_traits.hpp>

namespace boost { namespace python {

// forward declarations
template <long which, class operand> struct operators;
template <class T> struct left_operand;
template <class T> struct right_operand;

enum without_downcast_t { without_downcast };

namespace detail
{

// forward declarations
  class extension_instance;
  class extension_class_base;
  template <class T> class instance_holder;
  template <class T, class U> class instance_value_holder;
  template <class ref, class T> class instance_ptr_holder;
  template <class Specified> struct operand_select;
  template <long> struct choose_op;
  template <long> struct choose_rop;
  template <long> struct choose_unary_op;
  template <long> struct define_operator;

  class BOOST_PYTHON_DECL extension_instance : public instance
  {
   public:
      extension_instance(PyTypeObject* class_);
      ~extension_instance();
    
      void add_implementation(std::auto_ptr<instance_holder_base> holder);

      typedef std::vector<instance_holder_base*> held_objects;
      const held_objects& wrapped_objects() const
      { return m_wrapped_objects; }
   private:
      held_objects m_wrapped_objects;
  };

} // namespace detail

# ifndef BOOST_PYTHON_NO_TEMPLATE_EXPORT
BOOST_PYTHON_EXPORT_TEMPLATE_CLASS class_t<detail::extension_instance>;
BOOST_PYTHON_EXPORT_TEMPLATE_CLASS meta_class<detail::extension_instance>;
# endif 

namespace detail {

BOOST_PYTHON_DECL meta_class<extension_instance>* extension_meta_class();
BOOST_PYTHON_DECL extension_instance* get_extension_instance(PyObject* p);
BOOST_PYTHON_DECL void report_missing_instance_data(extension_instance*, class_t<extension_instance>*, const std::type_info&);
BOOST_PYTHON_DECL void report_missing_ptr_data(extension_instance*, class_t<extension_instance>*, const std::type_info&);
BOOST_PYTHON_DECL void report_missing_class_object(const std::type_info&);
BOOST_PYTHON_DECL void report_released_smart_pointer(const std::type_info&);
    
template <class T>
T* check_non_null(T* p)
{
    if (p == 0)
        report_released_smart_pointer(typeid(T));
    return p;
}

template <class Held> class held_instance;

typedef void* (*conversion_function_ptr)(void*);

struct BOOST_PYTHON_DECL base_class_info
{
    base_class_info(extension_class_base* t, conversion_function_ptr f)
        :class_object(t), convert(f)
        {}
    
    extension_class_base* class_object;
    conversion_function_ptr convert;
};

typedef base_class_info derived_class_info;

struct add_operator_base;

class BOOST_PYTHON_DECL extension_class_base : public class_t<extension_instance>
{
 public:
    extension_class_base(const char* name);
    
 public:
    // the purpose of try_class_conversions() and its related functions 
    // is explained in extclass.cpp
    void* try_class_conversions(instance_holder_base*) const;
    void* try_base_class_conversions(instance_holder_base*) const;
    void* try_derived_class_conversions(instance_holder_base*) const;

    void set_attribute(const char* name, PyObject* x);
    void set_attribute(const char* name, ref x);
    
 private:
    virtual void* extract_object_from_holder(instance_holder_base* v) const = 0;
    virtual std::vector<base_class_info> const& base_classes() const = 0;
    virtual std::vector<derived_class_info> const& derived_classes() const = 0;

 protected:
    friend struct add_operator_base;
    void add_method(reference<function> method, const char* name);
    void add_method(function* method, const char* name);
    
    void add_constructor_object(function*);
    void add_setter_method(function*, const char* name);
    void add_getter_method(function*, const char* name);
};

template <class T>
class class_registry
{
 public:
    static extension_class_base* class_object()
        { return static_class_object; }

    // Register/unregister the Python class object corresponding to T
    static void register_class(extension_class_base*);
    static void unregister_class(extension_class_base*);

    // Establish C++ inheritance relationships
    static void register_base_class(base_class_info const&);
    static void register_derived_class(derived_class_info const&);

    // Query the C++ inheritance relationships
    static std::vector<base_class_info> const& base_classes();
    static std::vector<derived_class_info> const& derived_classes();
 private:
    static extension_class_base* static_class_object;
    static std::vector<base_class_info> static_base_class_info;
    static std::vector<derived_class_info> static_derived_class_info;
};

template <bool is_pointer>
struct is_null_helper
{
    template <class Ptr>
    static bool test(Ptr x) { return x == 0; }
};

template <>
struct is_null_helper<false>
{
    template <class Ptr>
    static bool test(const Ptr& x) { return x.get() == 0; }
};

template <class Ptr>
bool is_null(const Ptr& x)
{
    return is_null_helper<(is_pointer<Ptr>::value)>::test(x);
}

}}} // namespace boost::python::detail

BOOST_PYTHON_BEGIN_CONVERSION_NAMESPACE

// This class' only job is to define from_python and to_python converters for T
// and U. T is the class the user really intends to wrap. U is a class derived
// from T with some virtual function overriding boilerplate, or if there are no
// virtual functions, U = held_instance<T>.
//
// A look-alike of this class in root/boost/python/cross_module.hpp
// is used for the implementation of the cross-module support
// (export_converters and import_converters). If from_python
// and to_python converters are added or removed from the class
// below, the class python_import_extension_class_converters has
// to be modified accordingly.
//
template <class T, class U = boost::python::detail::held_instance<T> >
class python_extension_class_converters
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
    friend python_extension_class_converters py_extension_class_converters(boost::python::type<T>)
    { 
        return python_extension_class_converters();
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
        boost::python::reference<boost::python::detail::extension_instance> result(create_instance());
        result->add_implementation(
            std::auto_ptr<boost::python::detail::instance_holder_base>(
                new boost::python::detail::instance_value_holder<T,U>(result.get(), x)));
        return result.release();
    }

    friend
    T* non_null_from_python(PyObject* obj, boost::python::type<T*>)
    {
        // downcast to an extension_instance, then find the actual T
        boost::python::detail::extension_instance* self = boost::python::detail::get_extension_instance(obj);
        typedef std::vector<boost::python::detail::instance_holder_base*>::const_iterator iterator;
        for (iterator p = self->wrapped_objects().begin();
             p != self->wrapped_objects().end(); ++p)
        {
            boost::python::detail::instance_holder<T>* held = dynamic_cast<boost::python::detail::instance_holder<T>*>(*p);
            if (held != 0)
                return held->target();

            // see extclass.cpp for an explanation of try_class_conversions()
            void* target = boost::python::detail::class_registry<T>::class_object()->try_class_conversions(*p);
            if(target) 
                return static_cast<T*>(target);
        }
        boost::python::detail::report_missing_instance_data(self, boost::python::detail::class_registry<T>::class_object(), typeid(T));
        throw boost::python::argument_error();
#if defined(__MWERKS__) && __MWERKS__ <= 0x2406
        return 0;
#endif
    }

    // Convert to T*
    friend T* from_python(PyObject* obj, boost::python::type<T*>)
    {
        if (obj == Py_None)
            return 0;
        else
            return non_null_from_python(obj, boost::python::type<T*>());
    }

    // Extract from obj a mutable reference to the PtrType object which is holding a T.
    template <class PtrType>
    static PtrType& smart_ptr_reference(PyObject* obj, boost::python::type<PtrType>)
    {
        // downcast to an extension_instance, then find the actual T
        boost::python::detail::extension_instance* self = boost::python::detail::get_extension_instance(obj);
        typedef std::vector<boost::python::detail::instance_holder_base*>::const_iterator iterator;
        for (iterator p = self->wrapped_objects().begin();
             p != self->wrapped_objects().end(); ++p)
        {
            boost::python::detail::instance_ptr_holder<PtrType, T>* held =
                dynamic_cast<boost::python::detail::instance_ptr_holder<PtrType, T>*>(*p);
            if (held != 0)
                return held->ptr();
        }
        boost::python::detail::report_missing_ptr_data(self, boost::python::detail::class_registry<T>::class_object(), typeid(T));
        throw boost::python::argument_error();
#if defined(__MWERKS__) && __MWERKS__ <= 0x2406
        return *(PtrType*)0;
#endif
    }

    // Extract from obj a reference to the PtrType object which is holding a
    // T. If it weren't for auto_ptr, it would be a constant reference. Do not
    // modify the referent except by copying an auto_ptr! If obj is None, the
    // reference denotes a default-constructed PtrType
    template <class PtrType>
    static PtrType& smart_ptr_value(PyObject* obj, boost::python::type<PtrType>)
    {
        if (obj == Py_None)
        {
            static PtrType null_ptr;
            return null_ptr;
        }
        return smart_ptr_reference(obj, boost::python::type<PtrType>());
    }
        
    template <class PtrType>
    static PyObject* smart_ptr_to_python(PtrType x)
    {
        if (boost::python::detail::is_null(x))
        {
            return boost::python::detail::none();
        }
        
        boost::python::reference<boost::python::detail::extension_instance> result(create_instance());
        result->add_implementation(
            std::auto_ptr<boost::python::detail::instance_holder_base>(
                new boost::python::detail::instance_ptr_holder<PtrType,T>(x)));
        return result.release();
    }

    static boost::python::reference<boost::python::detail::extension_instance> create_instance()
    {
        PyTypeObject* class_object = boost::python::detail::class_registry<T>::class_object();
        if (class_object == 0)
            boost::python::detail::report_missing_class_object(typeid(T));
            
        return boost::python::reference<boost::python::detail::extension_instance>(
            new boost::python::detail::extension_instance(class_object));
    }

    // Convert to const T*
    friend const T* from_python(PyObject* p, boost::python::type<const T*>)
        { return from_python(p, boost::python::type<T*>()); }

    // Convert to const T* const&
    friend const T* from_python(PyObject* p, boost::python::type<const T*const&>)
         { return from_python(p, boost::python::type<const T*>()); }
  
    // Convert to T* const&
    friend T* from_python(PyObject* p, boost::python::type<T* const&>)
         { return from_python(p, boost::python::type<T*>()); }
 
    // Convert to T&
    friend T& from_python(PyObject* p, boost::python::type<T&>)
        { return *boost::python::detail::check_non_null(non_null_from_python(p, boost::python::type<T*>())); }

    // Convert to const T&
    friend const T& from_python(PyObject* p, boost::python::type<const T&>)
        { return from_python(p, boost::python::type<T&>()); }

    // Convert to T
    friend const T& from_python(PyObject* p, boost::python::type<T>)
        { return from_python(p, boost::python::type<T&>()); }

    friend std::auto_ptr<T>& from_python(PyObject* p, boost::python::type<std::auto_ptr<T>&>)
        { return smart_ptr_reference(p, boost::python::type<std::auto_ptr<T> >()); }
    
    friend std::auto_ptr<T> from_python(PyObject* p, boost::python::type<std::auto_ptr<T> >)
        { return smart_ptr_value(p, boost::python::type<std::auto_ptr<T> >()); }
    
    friend const std::auto_ptr<T>& from_python(PyObject* p, boost::python::type<const std::auto_ptr<T>&>)
        { return smart_ptr_value(p, boost::python::type<std::auto_ptr<T> >()); }

    friend PyObject* to_python(std::auto_ptr<T> x)
        { return smart_ptr_to_python(x); }

    friend boost::shared_ptr<T>& from_python(PyObject* p, boost::python::type<boost::shared_ptr<T>&>)
        { return smart_ptr_reference(p, boost::python::type<boost::shared_ptr<T> >()); }
    
    friend const boost::shared_ptr<T>& from_python(PyObject* p, boost::python::type<boost::shared_ptr<T> >)
        { return smart_ptr_value(p, boost::python::type<boost::shared_ptr<T> >()); }
    
    friend const boost::shared_ptr<T>& from_python(PyObject* p, boost::python::type<const boost::shared_ptr<T>&>)
        { return smart_ptr_value(p, boost::python::type<boost::shared_ptr<T> >()); }

    friend PyObject* to_python(boost::shared_ptr<T> x)
        { return smart_ptr_to_python(x); }
};

// Convert T to_python, instantiated on demand and only if there isn't a
// non-template overload for this function. This version is the one invoked when
// T is a wrapped class. See the first 2 functions declared in
// python_extension_class_converters above for more info.
template <class T>
PyObject* to_python(const T& x)
{
    return py_extension_class_converters(boost::python::type<T>()).to_python(x);
}

BOOST_PYTHON_END_CONVERSION_NAMESPACE

namespace boost { namespace python {

BOOST_PYTHON_IMPORT_CONVERSION(python_extension_class_converters);

namespace detail {

template <class T> class instance_holder;

class BOOST_PYTHON_DECL read_only_setattr_function : public function
{
 public:
    read_only_setattr_function(const char* name);
    PyObject* do_call(PyObject* args, PyObject* keywords) const;
    const char* description() const;
 private:
    string m_name;
};

  template <class From, class To>
  struct define_conversion
  {
      static void* upcast_ptr(void* v)
      {
          return static_cast<To*>(static_cast<From*>(v));
      }

      static void* downcast_ptr(void* v)
      {
          return dynamic_cast<To*>(static_cast<From*>(v));
      }
  };

// An easy way to make an extension base class which wraps T. Note that Python
// subclasses of this class will simply be class_t<extension_instance> objects.
//
// U should be a class derived from T which overrides virtual functions with
// boilerplate code to call back into Python. See extclass_demo.h for examples.
// 
// U is optional, but you won't be able to override any member functions in
// Python which are called from C++ if you don't supply it. If you just want to
// be able to use T in python without overriding member functions, you can omit
// U.
template <class T, class U = held_instance<T> >
class extension_class
    : public python_extension_class_converters<T, U>, // This generates the to_python/from_python functions
      public extension_class_base
{
 public:
    typedef T wrapped_type;
    typedef U callback_type;
    
    // Construct with a name that comes from typeid(T).name(). The name only
    // affects the objects of this class are represented through repr()
    extension_class();
    
    // Construct with the given name. The name only affects the objects of this
    // class are represented through repr()
    extension_class(const char* name);
    
    ~extension_class();

    // define constructors
    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10>
    inline void def(constructor<A1, A2, A3, A4, A5, A6, A7, A8, A9, A10>)
    // The following incantation builds a signature1, signature2,... object. It
    // should _all_ get optimized away.
    { add_constructor(
        prepend(type<A1>::id(),
        prepend(type<A2>::id(),
        prepend(type<A3>::id(),
        prepend(type<A4>::id(),
        prepend(type<A5>::id(),
        prepend(type<A6>::id(),
        prepend(type<A7>::id(),
        prepend(type<A8>::id(),
        prepend(type<A9>::id(),
        prepend(type<A10>::id(),
                signature0())))))))))));
    }


    // export homogeneous operators (type of both lhs and rhs is 'operator')
    // usage:  foo_class.def(boost::python::operators<(boost::python::op_add | boost::python::op_sub), Foo>());
    
    // export homogeneous operators (type of both lhs and rhs is 'T const&')
    // usage:  foo_class.def(boost::python::operators<(boost::python::op_add | boost::python::op_sub)>());
    template <long which, class Operand>
    inline void def(operators<which,Operand>)
    {
        typedef typename operand_select<Operand>::template wrapped<T>::type true_operand;
        def_operators(operators<which,true_operand>());
    }

    // export heterogeneous operators (type of lhs: 'left', of rhs: 'right')
    // usage:  foo_class.def(boost::python::operators<(boost::python::op_add | boost::python::op_sub), Foo>(),
    //                       boost::python::right_operand<int const&>());

    // export heterogeneous operators (type of lhs: 'T const&', of rhs: 'right')
    // usage:  foo_class.def(boost::python::operators<(boost::python::op_add | boost::python::op_sub)>(),
    //                       boost::python::right_operand<int const&>());
    template <long which, class Left, class Right>
    inline void def(operators<which,Left>, right_operand<Right> r)
    {
        typedef typename operand_select<Left>::template wrapped<T>::type true_left;
        def_operators(operators<which,true_left>(), r);
    }

    // export heterogeneous reverse-argument operators 
    // (type of lhs: 'left', of rhs: 'right')
    // usage:  foo_class.def(boost::python::operators<(boost::python::op_add | boost::python::op_sub), Foo>(),
    //                       boost::python::left_operand<int const&>());
    
    // export heterogeneous reverse-argument operators 
    // (type of lhs: 'left', of rhs: 'T const&')
    // usage:  foo_class.def(boost::python::operators<(boost::python::op_add | boost::python::op_sub)>(),
    //                       boost::python::left_operand<int const&>());
    template <long which, class Left, class Right>
    inline void def(operators<which,Right>, left_operand<Left> l)
    {
        typedef typename operand_select<Right>::template wrapped<T>::type true_right;
        def_operators(operators<which,true_right>(), l);
    }

    // define a function that passes Python arguments and keywords
    // to C++ verbatim (as a 'tuple const&' and 'dictionary const&' 
    // respectively). This is useful for manual argument passing.
    // It's also the only possibility to pass keyword arguments to C++.
    // Fn must have a signatur that is compatible to 
    //     PyObject* (*)(PyObject* aTuple, PyObject* aDictionary)
    template <class Fn>
    inline void def_raw(Fn fn, const char* name)
    {
        this->add_method(new_raw_arguments_function(fn), name);
    }

    // define member functions. In fact this works for free functions, too -
    // they act like static member functions, or if they start with the
    // appropriate self argument (as a pointer), they can be used just like
    // ordinary member functions -- just like Python!
    template <class Fn>
    inline void def(Fn fn, const char* name)
    {
        this->add_method(new_wrapped_function(fn), name);
    }

    // Define a virtual member function with a default implementation.
    // default_fn should be a function which provides the default implementation.
    // Be careful that default_fn does not in fact call fn virtually!
    template <class Fn, class DefaultFn>
    inline void def(Fn fn, const char* name, DefaultFn default_fn)
    {
        this->add_method(new_virtual_function(type<T>(), fn, default_fn), name);
    }

    // Provide a function which implements x.<name>, reading from the given
    // member (pm) of the T obj
    template <class MemberType>
    inline void def_getter(MemberType T::*pm, const char* name)
    {
        this->add_getter_method(new getter_function<T, MemberType>(pm), name);
    }
    
    // Provide a function which implements assignment to x.<name>, writing to
    // the given member (pm) of the T obj
    template <class MemberType>
    inline void def_setter(MemberType T::*pm, const char* name)
    {
        this->add_setter_method(new setter_function<T, MemberType>(pm), name);
    }
    
    // Expose the given member (pm) of the T obj as a read-only attribute
    template <class MemberType>
    inline void def_readonly(MemberType T::*pm, const char* name)
    {
        this->add_setter_method(new read_only_setattr_function(name), name);
        this->def_getter(pm, name);
    }
    
    // Expose the given member (pm) of the T obj as a read/write attribute
    template <class MemberType>
    inline void def_read_write(MemberType T::*pm, const char* name)
    {
        this->def_getter(pm, name);
        this->def_setter(pm, name);
    }
    
    // define the standard coercion needed for operator overloading
    void def_standard_coerce();

    // declare the given class a base class of this one and register 
    // up and down conversion functions
    template <class S, class V>
    void declare_base(extension_class<S, V>* base)
    {
        // see extclass.cpp for an explanation of why we need to register
        // conversion functions
        base_class_info baseInfo(base, 
                            &define_conversion<S, T>::downcast_ptr);
        class_registry<T>::register_base_class(baseInfo);
        add_base(ref(as_object(base), ref::increment_count));
        
        derived_class_info derivedInfo(this, 
                            &define_conversion<T, S>::upcast_ptr);
        class_registry<S>::register_derived_class(derivedInfo);
    }
        
    // declare the given class a base class of this one and register 
    // only up conversion function
    template <class S, class V>
    void declare_base(extension_class<S, V>* base, without_downcast_t)
    {
        // see extclass.cpp for an explanation of why we need to register
        // conversion functions
        base_class_info baseInfo(base, 0);
        class_registry<T>::register_base_class(baseInfo);
        add_base(ref(as_object(base), ref::increment_count));
        
        derived_class_info derivedInfo(this, 
                           &define_conversion<T, S>::upcast_ptr);
        class_registry<S>::register_derived_class(derivedInfo);
    }
    
 private: // types
    typedef instance_value_holder<T,U> holder;

 private: // extension_class_base virtual function implementations
    std::vector<base_class_info> const& base_classes() const;
    std::vector<derived_class_info> const& derived_classes() const;
    void* extract_object_from_holder(instance_holder_base* v) const;

 private: // Utility functions
    template <long which, class Operand>
    inline void def_operators(operators<which,Operand>)
    {
        def_standard_coerce();

        // for some strange reason, this prevents MSVC from having an
        // "unrecoverable block scoping error"!
        typedef choose_op<(which & op_add)> choose_add;

        choose_op<(which & op_add)>::template args<Operand>::add(this);
        choose_op<(which & op_sub)>::template args<Operand>::add(this);
        choose_op<(which & op_mul)>::template args<Operand>::add(this);
        choose_op<(which & op_div)>::template args<Operand>::add(this);
        choose_op<(which & op_mod)>::template args<Operand>::add(this);
        choose_op<(which & op_divmod)>::template args<Operand>::add(this);
        choose_op<(which & op_pow)>::template args<Operand>::add(this);
        choose_op<(which & op_lshift)>::template args<Operand>::add(this);
        choose_op<(which & op_rshift)>::template args<Operand>::add(this);
        choose_op<(which & op_and)>::template args<Operand>::add(this);
        choose_op<(which & op_xor)>::template args<Operand>::add(this);
        choose_op<(which & op_or)>::template args<Operand>::add(this);
        choose_op<(which & op_gt)>::template args<Operand>::add(this);
        choose_op<(which & op_ge)>::template args<Operand>::add(this);
        choose_op<(which & op_lt)>::template args<Operand>::add(this);
        choose_op<(which & op_le)>::template args<Operand>::add(this);
        choose_op<(which & op_eq)>::template args<Operand>::add(this);
        choose_op<(which & op_ne)>::template args<Operand>::add(this);
        choose_unary_op<(which & op_neg)>::template args<Operand>::add(this);
        choose_unary_op<(which & op_pos)>::template args<Operand>::add(this);
        choose_unary_op<(which & op_abs)>::template args<Operand>::add(this);
        choose_unary_op<(which & op_invert)>::template args<Operand>::add(this);
        choose_unary_op<(which & op_int)>::template args<Operand>::add(this);
        choose_unary_op<(which & op_long)>::template args<Operand>::add(this);
        choose_unary_op<(which & op_float)>::template args<Operand>::add(this);
        choose_op<(which & op_cmp)>::template args<Operand>::add(this);
        choose_unary_op<(which & op_str)>::template args<Operand>::add(this);
    }

    template <long which, class Left, class Right>
    inline void def_operators(operators<which,Left>, right_operand<Right>)
    {
        def_standard_coerce();
        
        choose_op<(which & op_add)>::template args<Left,Right>::add(this);
        choose_op<(which & op_sub)>::template args<Left,Right>::add(this);
        choose_op<(which & op_mul)>::template args<Left,Right>::add(this);
        choose_op<(which & op_div)>::template args<Left,Right>::add(this);
        choose_op<(which & op_mod)>::template args<Left,Right>::add(this);
        choose_op<(which & op_divmod)>::template args<Left,Right>::add(this);
        choose_op<(which & op_pow)>::template args<Left,Right>::add(this);
        choose_op<(which & op_lshift)>::template args<Left,Right>::add(this);
        choose_op<(which & op_rshift)>::template args<Left,Right>::add(this);
        choose_op<(which & op_and)>::template args<Left,Right>::add(this);
        choose_op<(which & op_xor)>::template args<Left,Right>::add(this);
        choose_op<(which & op_or)>::template args<Left,Right>::add(this);
        choose_op<(which & op_cmp)>::template args<Left,Right>::add(this);
        choose_op<(which & op_gt)>::template args<Left,Right>::add(this);
        choose_op<(which & op_ge)>::template args<Left,Right>::add(this);
        choose_op<(which & op_lt)>::template args<Left,Right>::add(this);
        choose_op<(which & op_le)>::template args<Left,Right>::add(this);
        choose_op<(which & op_eq)>::template args<Left,Right>::add(this);
        choose_op<(which & op_ne)>::template args<Left,Right>::add(this);
    }
    
    template <long which, class Left, class Right>
    inline void def_operators(operators<which,Right>, left_operand<Left>)
    {
        def_standard_coerce();
        
        choose_rop<(which & op_add)>::template args<Left,Right>::add(this);
        choose_rop<(which & op_sub)>::template args<Left,Right>::add(this);
        choose_rop<(which & op_mul)>::template args<Left,Right>::add(this);
        choose_rop<(which & op_div)>::template args<Left,Right>::add(this);
        choose_rop<(which & op_mod)>::template args<Left,Right>::add(this);
        choose_rop<(which & op_divmod)>::template args<Left,Right>::add(this);
        choose_rop<(which & op_pow)>::template args<Left,Right>::add(this);
        choose_rop<(which & op_lshift)>::template args<Left,Right>::add(this);
        choose_rop<(which & op_rshift)>::template args<Left,Right>::add(this);
        choose_rop<(which & op_and)>::template args<Left,Right>::add(this);
        choose_rop<(which & op_xor)>::template args<Left,Right>::add(this);
        choose_rop<(which & op_or)>::template args<Left,Right>::add(this);
        choose_rop<(which & op_cmp)>::template args<Left,Right>::add(this);
    }
    
    template <class signature>
    void add_constructor(signature sig)
    {
        this->add_constructor_object(init_function<holder>::create(sig));
    }
};

// A simple wrapper over a T which allows us to use extension_class<T> with a
// single template parameter only. See extension_class<T>, above.
template <class Held>
class held_instance : public Held
{
    // There are no member functions: we want to avoid inadvertently overriding
    // any virtual functions in Held.
public:
    held_instance(PyObject*) : Held() {}
    template <class A1>
    held_instance(PyObject*, A1 a1) : Held(
        typename unwrap_parameter<A1>::type(a1)) {}
    template <class A1, class A2>
    held_instance(PyObject*, A1 a1, A2 a2) : Held(
        typename unwrap_parameter<A1>::type(a1)
        , typename unwrap_parameter<A2>::type(a2)) {}
    template <class A1, class A2, class A3>
    held_instance(PyObject*, A1 a1, A2 a2, A3 a3) : Held(
        typename unwrap_parameter<A1>::type(a1)
        , typename unwrap_parameter<A2>::type(a2)
        , typename unwrap_parameter<A3>::type(a3)) {}
    template <class A1, class A2, class A3, class A4>
    held_instance(PyObject*, A1 a1, A2 a2, A3 a3, A4 a4) : Held(
        typename unwrap_parameter<A1>::type(a1)
        , typename unwrap_parameter<A2>::type(a2)
        , typename unwrap_parameter<A3>::type(a3)
        , typename unwrap_parameter<A4>::type(a4)) {}
    template <class A1, class A2, class A3, class A4, class A5>
    held_instance(PyObject*, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) : Held(
        typename unwrap_parameter<A1>::type(a1)
        , typename unwrap_parameter<A2>::type(a2)
        , typename unwrap_parameter<A3>::type(a3)
        , typename unwrap_parameter<A4>::type(a4)
        , typename unwrap_parameter<A5>::type(a5)) {}
    template <class A1, class A2, class A3, class A4, class A5, class A6>
    held_instance(PyObject*, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6) : Held(
        typename unwrap_parameter<A1>::type(a1)
        , typename unwrap_parameter<A2>::type(a2)
        , typename unwrap_parameter<A3>::type(a3)
        , typename unwrap_parameter<A4>::type(a4)
        , typename unwrap_parameter<A5>::type(a5)
        , typename unwrap_parameter<A6>::type(a6)) {}
    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7>
    held_instance(PyObject*, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) : Held(
        typename unwrap_parameter<A1>::type(a1)
        , typename unwrap_parameter<A2>::type(a2)
        , typename unwrap_parameter<A3>::type(a3)
        , typename unwrap_parameter<A4>::type(a4)
        , typename unwrap_parameter<A5>::type(a5)
        , typename unwrap_parameter<A6>::type(a6)
        , typename unwrap_parameter<A7>::type(a7)) {}
    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
    held_instance(PyObject*, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8) : Held(
        typename unwrap_parameter<A1>::type(a1)
        , typename unwrap_parameter<A2>::type(a2)
        , typename unwrap_parameter<A3>::type(a3)
        , typename unwrap_parameter<A4>::type(a4)
        , typename unwrap_parameter<A5>::type(a5)
        , typename unwrap_parameter<A6>::type(a6)
        , typename unwrap_parameter<A7>::type(a7)
        , typename unwrap_parameter<A8>::type(a8)) {}
    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
    held_instance(PyObject*, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9) : Held(
        typename unwrap_parameter<A1>::type(a1)
        , typename unwrap_parameter<A2>::type(a2)
        , typename unwrap_parameter<A3>::type(a3)
        , typename unwrap_parameter<A4>::type(a4)
        , typename unwrap_parameter<A5>::type(a5)
        , typename unwrap_parameter<A6>::type(a6)
        , typename unwrap_parameter<A7>::type(a7)
        , typename unwrap_parameter<A8>::type(a8)
        , typename unwrap_parameter<A9>::type(a9)) {}
    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10>
    held_instance(PyObject*, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10) : Held(
        typename unwrap_parameter<A1>::type(a1)
        , typename unwrap_parameter<A2>::type(a2)
        , typename unwrap_parameter<A3>::type(a3)
        , typename unwrap_parameter<A4>::type(a4)
        , typename unwrap_parameter<A5>::type(a5)
        , typename unwrap_parameter<A6>::type(a6)
        , typename unwrap_parameter<A7>::type(a7)
        , typename unwrap_parameter<A8>::type(a8)
        , typename unwrap_parameter<A9>::type(a9)
        , typename unwrap_parameter<A10>::type(a10)) {}
};

// Abstract base class for all obj holders. Base for template class
// instance_holder<>, below.
class BOOST_PYTHON_DECL instance_holder_base
{
public:
    virtual ~instance_holder_base() {}
    virtual bool held_by_value() = 0;
};

// Abstract base class which holds a Held, somehow. Provides a uniform way to
// get a pointer to the held object
template <class Held>
class instance_holder : public instance_holder_base
{
public:
    virtual Held*target() = 0;
};

// Concrete class which holds a Held by way of a wrapper class Wrapper. If Held
// can be constructed with arguments (A1...An), Wrapper must have a
// corresponding constructor for arguments (PyObject*, A1...An). Wrapper is
// neccessary to implement virtual function callbacks (there must be a
// back-pointer to the actual Python object so that we can call any
// overrides). held_instance (above) is used as a default Wrapper class when
// there are no virtual functions.
template <class Held, class Wrapper>
class instance_value_holder : public instance_holder<Held>
{
public:
    Held* target() { return &m_held; }
    Wrapper* value_target() { return &m_held; }

    instance_value_holder(extension_instance* p) :
        m_held(p) {}
    template <class A1>
    instance_value_holder(extension_instance* p, A1 a1) :
        m_held(p, a1) {}
    template <class A1, class A2>
    instance_value_holder(extension_instance* p, A1 a1, A2 a2) :
        m_held(p, a1, a2) {}
    template <class A1, class A2, class A3>
    instance_value_holder(extension_instance* p, A1 a1, A2 a2, A3 a3) :
        m_held(p, a1, a2, a3) {}
    template <class A1, class A2, class A3, class A4>
    instance_value_holder(extension_instance* p, A1 a1, A2 a2, A3 a3, A4 a4) :
        m_held(p, a1, a2, a3, a4) {}
    template <class A1, class A2, class A3, class A4, class A5>
    instance_value_holder(extension_instance* p, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) :
        m_held(p, a1, a2, a3, a4, a5) {}
    template <class A1, class A2, class A3, class A4, class A5, class A6>
    instance_value_holder(extension_instance* p, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6) :
        m_held(p, a1, a2, a3, a4, a5, a6) {}
    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7>
    instance_value_holder(extension_instance* p, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) :
        m_held(p, a1, a2, a3, a4, a5, a6, a7) {}
    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
    instance_value_holder(extension_instance* p, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8) :
        m_held(p, a1, a2, a3, a4, a5, a6, a7, a8) {}
    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
    instance_value_holder(extension_instance* p, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9) :
        m_held(p, a1, a2, a3, a4, a5, a6, a7, a8, a9) {}
    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10>
    instance_value_holder(extension_instance* p, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10) :
        m_held(p, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10) {}

 public: // implementation of instance_holder_base required interface
    bool held_by_value() { return true; }

 private:
    Wrapper m_held;
};

// Concrete class which holds a HeldType by way of a (possibly smart) pointer
// PtrType. By default, these are only generated for PtrType ==
// std::auto_ptr<HeldType> and PtrType == boost::shared_ptr<HeldType>.
template <class PtrType, class HeldType>
class instance_ptr_holder : public instance_holder<HeldType>
{
 public:
    HeldType* target() { return &*m_ptr; }
    PtrType& ptr() { return m_ptr; }

    instance_ptr_holder(PtrType ptr) : m_ptr(ptr) {}
    
 public: // implementation of instance_holder_base required interface
    bool held_by_value() { return false; }
 private:
    PtrType m_ptr;
};

//
// Template function implementations
//

template <class T, class U>
extension_class<T, U>::extension_class()
    : extension_class_base(typeid(T).name())
{
    class_registry<T>::register_class(this);
}

template <class T, class U>
extension_class<T, U>::extension_class(const char* name)
    : extension_class_base(name)
{
    class_registry<T>::register_class(this);
}

template <class T, class U>
void extension_class<T, U>::def_standard_coerce()
{
    ref coerce_fct = dict().get_item(string("__coerce__"));
    
    if(coerce_fct.get() == 0) // not yet defined
        this->def(&standard_coerce, "__coerce__");
}

template <class T, class U>
inline
std::vector<base_class_info> const& 
extension_class<T, U>::base_classes() const
{
    return class_registry<T>::base_classes();
}

template <class T, class U>
inline
std::vector<derived_class_info> const& 
extension_class<T, U>::derived_classes() const
{
    return class_registry<T>::derived_classes();
}
       
template <class T, class U>
void* extension_class<T, U>::extract_object_from_holder(instance_holder_base* v) const
{
    instance_holder<T>* held = dynamic_cast<instance_holder<T>*>(v);
    if(held)
        return held->target();
    return 0;
}

template <class T, class U>
extension_class<T, U>::~extension_class()
{
    class_registry<T>::unregister_class(this);
}

template <class T>
inline void class_registry<T>::register_class(extension_class_base* p)
{
    // You're not expected to create more than one of these!
    assert(static_class_object == 0);
    static_class_object = p;
}

template <class T>
inline void class_registry<T>::unregister_class(extension_class_base* p)
{
    // The user should be destroying the same object they created.
    assert(static_class_object == p);
    (void)p; // unused in shipping version
    static_class_object = 0;
}

template <class T>
void class_registry<T>::register_base_class(base_class_info const& i)
{
    static_base_class_info.push_back(i);
}

template <class T>
void class_registry<T>::register_derived_class(derived_class_info const& i)
{
    static_derived_class_info.push_back(i);
}

template <class T>
std::vector<base_class_info> const& class_registry<T>::base_classes()
{
    return static_base_class_info;
}

template <class T>
std::vector<derived_class_info> const& class_registry<T>::derived_classes()
{
    return static_derived_class_info;
}

//
// Static data member declaration.
//
template <class T>
extension_class_base* class_registry<T>::static_class_object;
template <class T>
std::vector<base_class_info> class_registry<T>::static_base_class_info;
template <class T>
std::vector<derived_class_info> class_registry<T>::static_derived_class_info;

}}} // namespace boost::python::detail

#endif // EXTENSION_CLASS_DWA052000_H_
