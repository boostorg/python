//  (C) Copyright David Abrahams 2000. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
//  The author gratefully acknowleges the support of Dragon Systems, Inc., in
//  producing this work.

#ifndef FUNCTIONS_DWA051400_H_
# define FUNCTIONS_DWA051400_H_

# include <boost/python/detail/config.hpp>
# include <boost/python/detail/wrap_python.hpp>
# include <boost/python/reference.hpp>
# include <boost/python/detail/signatures.hpp>
# include <boost/python/caller.hpp>
# include <boost/call_traits.hpp>
# include <boost/python/objects.hpp>
# include <boost/python/detail/base_object.hpp>
# include <typeinfo>
# include <vector>

namespace boost { namespace python { namespace detail {

// forward declaration
class extension_instance;


// function --
//      the common base class for all overloadable function and method objects
//      supplied by the library.
class BOOST_PYTHON_DECL function : public python_object
{
 public:
    function();
    // function objects are reasonably rare, so we guess we can afford a virtual table.
    // This cuts down on the number of distinct type objects which need to be defined.
    virtual ~function() {}

    PyObject* call(PyObject* args, PyObject* keywords) const;
    static void add_to_namespace(reference<function> f, const char* name, PyObject* dict);
    
 private:
    virtual PyObject* do_call(PyObject* args, PyObject* keywords) const = 0;
    virtual const char* description() const = 0;
 private:
    struct type_object;
 private:
    reference<function> m_overloads; // A linked list of the function overloads
};

// wrapped_function_pointer<> --
//      A single function or member function pointer wrapped and presented to
//      Python as a callable object.
//
//   Template parameters:
//      R - the return type of the function pointer
//      F - the complete type of the wrapped function pointer
template <class R, class F>
struct wrapped_function_pointer : function
{
    typedef F ptr_fun; // pointer-to--function or pointer-to-member-function
    
    wrapped_function_pointer(ptr_fun pf)
        : m_pf(pf) {}

 private:
    PyObject* do_call(PyObject* args, PyObject* keywords) const
        {
            // This is where the boundary between the uniform Python function
            // interface and the statically-checked C++ function interface is
            // crossed.
            return caller<R>::call(m_pf, args, keywords);
        }
    
    const char* description() const
        { return typeid(F).name(); }
    
 private:
    const ptr_fun m_pf;
};

// raw_arguments_function
//      A function that passes the Python argument tuple and keyword dictionary 
//      verbatim to C++ (useful for customized argument parsing and variable
//      argument lists)
template <class Ret, class Args, class Keywords>
struct raw_arguments_function : function
{
    typedef Ret (*ptr_fun)(Args, Keywords); 
    
    raw_arguments_function(ptr_fun pf)
        : m_pf(pf) {}

 private:
    PyObject* do_call(PyObject* args, PyObject* keywords) const
    { 
        ref dict(keywords ? 
                 ref(keywords, ref::increment_count) :
                 ref(PyDict_New()));
            
        return to_python(
            (*m_pf)(from_python(args, boost::python::type<Args>()),
                    from_python(dict.get(), boost::python::type<Keywords>()))); 
    }
    
    const char* description() const
        { return typeid(ptr_fun).name(); }
    
 private:
    const ptr_fun m_pf;
};

// virtual_function<> --
//      A virtual function with a default implementation wrapped and presented
//      to Python as a callable object.
//
//   Template parameters:
//      T - the type of the target class
//      R - the return type of the function pointer
//      V - the virtual function pointer being wrapped
//          (should be of the form R(T::*)(<args>), or R (*)(T, <args>))
//      D - a function which takes a T&, const T&, T*, or const T* first
//          parameter and calls T::f on it /non-virtually/, where V
//          approximates &T::f.
template <class T, class R, class V, class D>
class virtual_function : public function
{
 public:
    virtual_function(V virtual_function_ptr, D default_implementation)
        : m_virtual_function_ptr(virtual_function_ptr),
          m_default_implementation(default_implementation)
        {}

 private:
    PyObject* do_call(PyObject* args, PyObject* keywords) const;
    
    const char* description() const
        { return typeid(V).name(); }
    
 private:
    const V m_virtual_function_ptr;
    const D m_default_implementation;
};

// A helper function for new_member_function(), below.  Implements the core
// functionality once the return type has already been deduced. R is expected to
// be type<X>, where X is the actual return type of pmf.
template <class F, class R>
function* new_wrapped_function_aux(R, F pmf)
{
    // We can't just use "typename R::Type" below because MSVC (incorrectly) pukes.
    typedef typename R::type return_type;
    return new wrapped_function_pointer<return_type, F>(pmf);
}

// Create and return a new member function object wrapping the given
// pointer-to-member function
template <class F>
inline function* new_wrapped_function(F pmf)
{
    // Deduce the return type and pass it off to the helper function above
    return new_wrapped_function_aux(return_value(pmf), pmf);
}

template <class R, class Args, class keywords>
function* new_raw_arguments_function(R (*pmf)(Args, keywords))
{
    return new raw_arguments_function<R, Args, keywords>(pmf);
}


// A helper function for new_virtual_function(), below.  Implements the core
// functionality once the return type has already been deduced. R is expected to
// be type<X>, where X is the actual return type of V.
template <class T, class R, class V, class D>
inline function* new_virtual_function_aux(
    type<T>, R, V virtual_function_ptr, D default_implementation
    )
{
    // We can't just use "typename R::Type" below because MSVC (incorrectly) pukes.
    typedef typename R::type return_type;
    return new virtual_function<T, return_type, V, D>(
        virtual_function_ptr, default_implementation);
}

// Create and return a new virtual_function object wrapping the given
// virtual_function_ptr and default_implementation
template <class T, class V, class D>
inline function* new_virtual_function(
    type<T>, V virtual_function_ptr, D default_implementation
    )
{
    // Deduce the return type and pass it off to the helper function above
    return new_virtual_function_aux(
        type<T>(), return_value(virtual_function_ptr),
        virtual_function_ptr, default_implementation);
}

// A function with a bundled "bound target" object. This is what is produced by
// the expression a.b where a is an instance or extension_instance object and b
// is a callable object not found in the obj namespace but on its class or
// a base class.
class BOOST_PYTHON_DECL bound_function : public python_object
{
 public:
    static bound_function* create(const ref& target, const ref& fn);
    
    bound_function(const ref& target, const ref& fn);
    PyObject* call(PyObject*args, PyObject* keywords) const;
    PyObject* getattr(const char* name) const;
    
 private:
    struct type_object;
    friend struct type_object;
    
    ref m_target;
    ref m_unbound_function;
    
 private: // data members for allocation/deallocation optimization
    bound_function* m_free_list_link;

    static bound_function* free_list;
};

// Special functions designed to access data members of a wrapped C++ object.
template <class ClassType, class MemberType>
class getter_function : public function
{
 public:
    typedef MemberType ClassType::* pointer_to_member;
    
    getter_function(pointer_to_member pm)
        : m_pm(pm) {}

 private:
    PyObject* do_call(PyObject* args, PyObject* keywords) const;
    
    const char* description() const
        { return typeid(MemberType (*)(const ClassType&)).name(); }
 private:
    pointer_to_member m_pm;
};

template <class ClassType, class MemberType>
class setter_function : public function
{
 public:
    typedef MemberType ClassType::* pointer_to_member;
    
    setter_function(pointer_to_member pm)
        : m_pm(pm) {}

 private:
    PyObject* do_call(PyObject* args, PyObject* keywords) const;
    
    const char* description() const
        { return typeid(void (*)(const ClassType&, const MemberType&)).name(); }
 private:
    pointer_to_member m_pm;
};

template <class ClassType, class MemberType>
PyObject* getter_function<ClassType, MemberType>::do_call(
    PyObject* args, PyObject* /* keywords */) const
{
    PyObject* self;
    if (!PyArg_ParseTuple(args, const_cast<char*>("O"), &self))
        return 0;

    return to_python(
        from_python(self, type<const ClassType*>())->*m_pm);
}

template <class ClassType, class MemberType>
PyObject* setter_function<ClassType, MemberType>::do_call(
    PyObject* args, PyObject* /* keywords */) const
{
    PyObject* self;
    PyObject* value;
    if (!PyArg_ParseTuple(args, const_cast<char*>("OO"), &self, &value))
        return 0;
    
    typedef typename boost::call_traits<MemberType>::const_reference extract_type;
    from_python(self, type<ClassType*>())->*m_pm
        = from_python(value, type<extract_type>());
    
    return none();
}

template <class T, class R, class V, class D>
PyObject* virtual_function<T,R,V,D>::do_call(PyObject* args, PyObject* keywords) const
{
    // If the target object is held by pointer, we must call through the virtual
    // function pointer to the most-derived override.
    PyObject* target = PyTuple_GetItem(args, 0);
    if (target != 0)
    {
        extension_instance* self = get_extension_instance(target);
        if (self->wrapped_objects().size() == 1
            && !self->wrapped_objects()[0]->held_by_value())
        {
            return caller<R>::call(m_virtual_function_ptr, args, keywords);
        }
    }
    return caller<R>::call(m_default_implementation, args, keywords);
}
    
}}} // namespace boost::python::detail

#endif // FUNCTIONS_DWA051400_H_
