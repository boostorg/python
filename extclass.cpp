//  (C) Copyright David Abrahams 2000. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
//  The author gratefully acknowleges the support of Dragon Systems, Inc., in
//  producing this work.

#include "extclass.h"
#include <cstring>
#include <boost/utility.hpp>

namespace py {
namespace detail {

  struct operator_dispatcher
      : public PyObject
#ifndef NDEBUG
        , boost::noncopyable
#endif
  {
      static PyTypeObject type_object;
      static PyNumberMethods number_methods;

      operator_dispatcher(const Ptr& o, const Ptr& s);
#ifndef NDEBUG
      ~operator_dispatcher();
#endif

      Ptr m_object;
      Ptr m_self;
  };

}}

PY_BEGIN_CONVERSION_NAMESPACE

inline PyObject* to_python(py::detail::operator_dispatcher* n) { return n; }

PY_END_CONVERSION_NAMESPACE


namespace py{ 

namespace detail {

  Tuple extension_class_coerce(Ptr l, Ptr r)
  {
      // Introduced sequence points for exception-safety.
      Ptr first(new operator_dispatcher(l, l));
      Ptr second;
      
      if(r->ob_type == &operator_dispatcher::type_object)
      {
           second = r;
      }
      else
      {
           second = Ptr(new operator_dispatcher(r, Ptr()));
      }
      return py::Tuple(first, second);
  }

  enum { unwrap_exception_code = -1000 };

  int unwrap_args(PyObject* left, PyObject* right, PyObject*& self, PyObject*& other)
  {
      if (left->ob_type != &operator_dispatcher::type_object ||
          right->ob_type != &operator_dispatcher::type_object)
      {
          String format("operator_dispatcher::unwrap_args(): internal error (%d, %d)");
          String message(format % Tuple(__FILE__, __LINE__));
          PyErr_SetObject(PyExc_RuntimeError, message.get());
          return unwrap_exception_code;
      }

      typedef PyPtr<operator_dispatcher> DPtr;
      DPtr lwrapper(static_cast<operator_dispatcher*>(left), DPtr::new_ref);
      DPtr rwrapper(static_cast<operator_dispatcher*>(right), DPtr::new_ref);
      
      if (lwrapper->m_self.get() != 0)
      {
          self = lwrapper->m_self.get();
          other = rwrapper->m_object.get();
          return 0;
      }
      else
      {
          self = rwrapper->m_self.get();
          other = lwrapper->m_object.get();
          return 1;
      }
  }

  int unwrap_pow_args(PyObject* left, PyObject* right, PyObject* m,
                                  PyObject*& self, PyObject*& first, PyObject*& second)
  {
      if (left->ob_type != &operator_dispatcher::type_object ||
          right->ob_type != &operator_dispatcher::type_object ||
          m->ob_type != &operator_dispatcher::type_object)
      {
          String format("operator_dispatcher::unwrap_pow_args(): internal error (%d, %d)");
          String message(format % Tuple(__FILE__, __LINE__));
          PyErr_SetObject(PyExc_RuntimeError, message.get());
          return unwrap_exception_code;
      }


      typedef PyPtr<operator_dispatcher> DPtr;
      DPtr lwrapper(static_cast<operator_dispatcher*>(left), DPtr::new_ref);
      DPtr rwrapper(static_cast<operator_dispatcher*>(right), DPtr::new_ref);
      DPtr mwrapper(static_cast<operator_dispatcher*>(m), DPtr::new_ref);
      
      if (lwrapper->m_self.get() != 0)
      {
          self = lwrapper->m_self.get();
          first = rwrapper->m_object.get();
          second = mwrapper->m_object.get();
          return 0;
      }
      else if (rwrapper->m_self.get() != 0)
      {
          self = rwrapper->m_self.get();
          first = lwrapper->m_object.get();
          second = mwrapper->m_object.get();
          return 1;
      }
      else
      {
          self = mwrapper->m_self.get();
          first = lwrapper->m_object.get();
          second = rwrapper->m_object.get();
          return 2;
      }
  }
} // namespace detail

ExtensionInstance* get_extension_instance(PyObject* p)
{
    // The object's type will just be some Class<ExtensionInstance> object,
    // but if its meta-type is right, then it is an ExtensionInstance.
    if (p->ob_type->ob_type != extension_meta_class())
    {
        PyErr_SetString(PyExc_TypeError, p->ob_type->tp_name);
        throw py::ArgumentError();
    }
    return static_cast<ExtensionInstance*>(p);
}

void
ExtensionInstance::add_implementation(std::auto_ptr<InstanceHolderBase> holder)
{
    for (WrappedObjects::const_iterator p = m_wrapped_objects.begin();
         p != m_wrapped_objects.end(); ++p)
    {
        if (typeid(*holder) == typeid(**p))
        {
            PyErr_SetString(PyExc_RuntimeError, "Base class already initialized");
            throw ErrorAlreadySet();
        }
    }
    m_wrapped_objects.push_back(holder.release());
}

ExtensionInstance::ExtensionInstance(PyTypeObject* class_)
    : Instance(class_)
{
}

ExtensionInstance::~ExtensionInstance()
{
    for (WrappedObjects::const_iterator p = m_wrapped_objects.begin(),
             finish = m_wrapped_objects.end();
         p != finish; ++p)
    {
        delete *p;
    }
}
    
MetaClass<ExtensionInstance>* extension_meta_class()
{
    static MetaClass<ExtensionInstance> result;
    return &result;
}

typedef Class<ExtensionInstance> ExtClass;

bool is_subclass(const ExtClass* derived,
                 const PyObject* possible_base)
{

    Tuple bases = derived->bases();
    
    for (std::size_t i = 0, size = bases.size(); i < size; ++i)
    {
        const PyObject* base = bases[i].get();
        
        if (base == possible_base)
            return true;
        
        if (base->ob_type == extension_meta_class())
        {
            const ExtClass* base_class = Downcast<const ExtClass>(base);
            if (is_subclass(base_class, possible_base))
                return true;
        }
    }
    return false;
}

// Return true iff instance is an instance of target_class
bool is_instance(ExtensionInstance* instance,
                 Class<ExtensionInstance>* target_class)
{
    if (instance->ob_type == target_class)
        return true;
    else
    {
        return is_subclass(
            Downcast<Class<ExtensionInstance> >(instance->ob_type).get(),
            as_object(target_class));
    }
}

void two_string_error(PyObject* exception_object, const char* format, const char* s1, const char* s2)
{
    char buffer[256];
    std::size_t format_length = PY_CSTD_::strlen(format);
    std::size_t length1 = PY_CSTD_::strlen(s1);
    std::size_t length2 = PY_CSTD_::strlen(s2);

    std::size_t additional_length = length1 + length2;
    if (additional_length + format_length > format_length - 1)
    {
        std::size_t difference = sizeof(buffer) - 1 - additional_length;
        length1 -= difference / 2;
        additional_length -= difference / 2;
    }
        
    sprintf(buffer, format, length1, s1, length2, s2);
                
    PyErr_SetString(exception_object, buffer);
    if (exception_object == PyExc_TypeError)
        throw ArgumentError();
    else
        throw ErrorAlreadySet();
}

// This is called when an attempt has been made to convert the given instance to
// a C++ type for which it doesn't have any instance data. In that case, either
// the instance was not derived from the target_class, or the appropriate
// __init__ function wasn't called to initialize the instance data of the target class.
void report_missing_instance_data(
    ExtensionInstance* instance,                // The object being converted
    Class<ExtensionInstance>* target_class,     // the extension class of the C++ type
    const std::type_info& target_typeid,        // The typeid of the C++ type
    bool target_is_ptr)
{
    char buffer[256];
    if (is_instance(instance, target_class))
    {
        if (target_is_ptr)
        {
            two_string_error(PyExc_RuntimeError,
                             "Object of extension class '%.*s' does not wrap <%.*s>.",
                             instance->ob_type->tp_name, target_typeid.name());
        }
        else
        {
            const char message[] = "__init__ function for extension class '%.*s' was never called.";
            sprintf(buffer, message, sizeof(buffer) - sizeof(message) - 1,
                    target_class->tp_name);
        }
        PyErr_SetString(PyExc_RuntimeError, buffer);
    }
    else if (target_class == 0)
    {
        const char message[] = "Cannot convert to <%.*s>; its Python class was never created or has been deleted.";
        sprintf(buffer, message, sizeof(buffer) - sizeof(message) - 1, target_typeid.name());
        PyErr_SetString(PyExc_RuntimeError, buffer);
    }
    else    
    {
        two_string_error(PyExc_TypeError, "extension class '%.*s' is not convertible into '%.*s'.",
                         instance->ob_type->tp_name, target_class->tp_name);
    }
}

void report_missing_instance_data(
    ExtensionInstance* instance,                // The object being converted
    Class<ExtensionInstance>* target_class,     // the extension class of the C++ type
    const std::type_info& target_typeid)        // The typeid of the C++ type
{
    report_missing_instance_data(instance, target_class, target_typeid, false);
}

void report_missing_ptr_data(
    ExtensionInstance* instance,                // The object being converted
    Class<ExtensionInstance>* target_class,     // the extension class of the C++ type
    const std::type_info& target_typeid)        // The typeid of the C++ type
{
    report_missing_instance_data(instance, target_class, target_typeid, true);
}

void report_missing_class_object(const std::type_info& info)
{
    char buffer[256];
    const char message[] = "Cannot convert <%.*s> to python; its Python class was never created or has been deleted.";
    sprintf(buffer, message, sizeof(buffer) - sizeof(message) - 1, info.name());
    PyErr_SetString(PyExc_RuntimeError, buffer);
    throw ErrorAlreadySet();
}

void report_released_smart_pointer(const std::type_info& info)
{
    char buffer[256];
    const char message[] = "Converting from python, pointer or smart pointer to <%.*s> is NULL.";
    sprintf(buffer, message, sizeof(buffer) - sizeof(message) - 1, info.name());
    PyErr_SetString(PyExc_RuntimeError, buffer);
    throw ArgumentError();
}

ReadOnlySetattrFunction::ReadOnlySetattrFunction(const char* name)
    : m_name(name)
{
}

PyObject* ReadOnlySetattrFunction::do_call(PyObject* /*args*/, PyObject* /*keywords*/) const
{
    PyErr_SetObject(PyExc_AttributeError, ("'" + m_name + "' attribute is read-only").get());
    return 0;
}

const char* ReadOnlySetattrFunction::description() const
{
    return "uncallable";
}

ExtensionClassBase::ExtensionClassBase(const char* name)
    : Class<ExtensionInstance>(
        extension_meta_class(), String(name), Tuple(), Dict())
{
}

//  This function is used in from_python() to convert wrapped classes that are 
//  related by inheritance. The problem is this: although C++ provides all necessary 
//  conversion operators, source and target of a conversion must be known at compile
//  time. However, in Python we want to convert classes at runtime. The solution is to
//  generate conversion functions at compile time, register them within the appropriate 
//  class objects and call them when a particular runtime conversion is required.

//  If functions for any possible conversion have to be stored, their number will grow 
//  qudratically. To reduce this number, we actually store only conversion functions
//  between adjacent levels in the inheritance tree. By traversing the tree recursively,
//  we can build any allowed conversion as a concatenation of simple conversions. This
//  traversal is done in the functions try_base_class_conversions() and 
//  try_derived_class_conversions(). If a particular conversion is impossible, all
//  conversion functions will return a NULL pointer.

//  The function extract_object_from_holder() attempts to actually extract the pointer 
//  to the contained object from an InstanceHolderBase (a wrapper class). A conversion
//  of the held object to 'T *' is allowed when the conversion 
//  'dynamic_cast<InstanceHolder<T> *>(an_instance_holder_base)' succeeds.
void* ExtensionClassBase::try_class_conversions(InstanceHolderBase* object) const
{
    void* result = try_derived_class_conversions(object);
    if (result) 
        return result;
        
    if (!object->held_by_value())
        return try_base_class_conversions(object);
    else
        return 0;
}

void* ExtensionClassBase::try_base_class_conversions(InstanceHolderBase* object) const
{
    for (std::size_t i = 0; i < base_classes().size(); ++i)
    {
        if (base_classes()[i].convert == 0) 
            continue;
        void* result1 = base_classes()[i].class_object->extract_object_from_holder(object);
        if (result1)
            return (*base_classes()[i].convert)(result1);
        
        void* result2 = base_classes()[i].class_object->try_base_class_conversions(object);
        if (result2)
            return (*base_classes()[i].convert)(result2);
    }
    return 0;
}

void* ExtensionClassBase::try_derived_class_conversions(InstanceHolderBase* object) const
{
    for (std::size_t i = 0; i < derived_classes().size(); ++i)
    {
        void* result1 = derived_classes()[i].class_object->extract_object_from_holder(object);
        if (result1) 
            return (*derived_classes()[i].convert)(result1);
        
        void* result2 = derived_classes()[i].class_object->try_derived_class_conversions(object);
        if (result2) 
            return (*derived_classes()[i].convert)(result2);
    }
    return 0;
}

void ExtensionClassBase::add_method(Function* method, const char* name)
{
    add_method(PyPtr<Function>(method), name);
}
    
void ExtensionClassBase::add_method(PyPtr<Function> method, const char* name)
{
    // Add the attribute to the computed target
    Function::add_to_namespace(method, name, this->dict().get());

    // If it is a special member function it should be enabled both here and there.
    detail::enable_named_method(this, name);
}

void ExtensionClassBase::add_constructor_object(Function* init_function)
{
    add_method(init_function, "__init__");
}

void ExtensionClassBase::add_setter_method(Function* setter_, const char* name)
{
    PyPtr<Function> setter(setter_);
    add_method(setter, (detail::setattr_string() + name + "__").c_str());
}

void ExtensionClassBase::add_getter_method(Function* getter_, const char* name)
{
    PyPtr<Function> getter(getter_);
    add_method(getter, (detail::getattr_string() + name + "__").c_str());
}

void ExtensionClassBase::set_attribute(const char* name, PyObject* x_)
{
    Ptr x(x_);
    set_attribute(name, x);
}

void ExtensionClassBase::set_attribute(const char* name, Ptr x)
{
    dict().set_item(String(name), x);
    if (PyCallable_Check(x.get()))
        detail::enable_named_method(this, name);
}

namespace detail
{

#ifndef NDEBUG
int total_Dispatchers = 0;
operator_dispatcher::~operator_dispatcher() 
{ 
    --total_Dispatchers; 
}
#endif

operator_dispatcher::operator_dispatcher(const Ptr& o, const Ptr& s)
    : m_object(o), m_self(s)
{
    ob_refcnt = 1;
    ob_type = &type_object;
#ifndef NDEBUG
    ++total_Dispatchers;
#endif
}

extern "C"
{

void operator_dispatcher_dealloc(PyObject* self) 
{ 
    delete static_cast<operator_dispatcher*>(self);
} 

int operator_dispatcher_coerce(PyObject** l, PyObject** r)
{
    Py_INCREF(*l);
    *r = new operator_dispatcher(Ptr(*r, Ptr::new_ref), Ptr());
    return 0;
}


#define PY_DEFINE_OPERATOR(id, symbol) \
    PyObject* operator_dispatcher_call_##id(PyObject* left, PyObject* right)                   \
    {                                                                                           \
        /* unwrap the arguments from their OperatorDispatcher */                                \
        PyObject* self;                                                                         \
        PyObject* other;                                                                        \
        int reverse = unwrap_args(left, right, self, other);                                    \
        if (reverse == unwrap_exception_code)                                                   \
            return 0;                                                                           \
                                                                                                \
        /* call the function */                                                                 \
        PyObject* result =                                                                      \
           PyEval_CallMethod(self,                                                              \
                             const_cast<char*>(reverse ? "__r" #id "__" : "__" #id "__"),       \
                             const_cast<char*>("(O)"),                                          \
                             other);                                                            \
        if (result == 0 && PyErr_GivenExceptionMatches(PyErr_Occurred(), PyExc_AttributeError)) \
        {                                                                                       \
            PyErr_Clear();                                                                      \
            PyErr_SetString(PyExc_TypeError, "bad operand type(s) for " #symbol);               \
        }                                                                                       \
        return result;                                                                          \
    }

PY_DEFINE_OPERATOR(add, +)
PY_DEFINE_OPERATOR(sub, -)
PY_DEFINE_OPERATOR(mul, *)
PY_DEFINE_OPERATOR(div, /)
PY_DEFINE_OPERATOR(mod, %)
PY_DEFINE_OPERATOR(divmod, divmod)
PY_DEFINE_OPERATOR(lshift, <<)
PY_DEFINE_OPERATOR(rshift, >>)
PY_DEFINE_OPERATOR(and, &)
PY_DEFINE_OPERATOR(xor, ^)
PY_DEFINE_OPERATOR(or, |)

/* coercion rules for heterogeneous pow():
    pow(Foo, int): left, right coerced; m: None => reverse = 0
    pow(int, Foo): left, right coerced; m: None => reverse = 1
    pow(Foo, int, int): left, right, m coerced => reverse = 0
    pow(int, Foo, int): left, right, m coerced => reverse = 1
    pow(int, int, Foo): left, right, m coerced => reverse = 2
    pow(Foo, Foo, int): left, right coerced; m coerced twice => reverse = 0
    pow(Foo, int, Foo): left, right, m coerced => reverse = 0
    pow(int, Foo, Foo): left, right, m coerced => reverse = 1 
*/
PyObject* operator_dispatcher_call_pow(PyObject* left, PyObject* right, PyObject* m)
{
    int reverse;
    PyObject* self;
    PyObject* first;
    PyObject* second;
    
    if (m->ob_type == Py_None->ob_type)
    {
        reverse = unwrap_args(left, right, self, first);
        second = m; 
    }
    else
    {
        reverse = unwrap_pow_args(left, right, m, self, first, second);
    }
    
    if (reverse == unwrap_exception_code) 
        return 0;                         
                                              
    // call the function
    PyObject* result = 
        PyEval_CallMethod(self,
                          const_cast<char*>((reverse == 0)
                                            ? "__pow__"
                                            : (reverse == 1)
                                              ? "__rpow__"
                                              : "__rrpow__"),
                          const_cast<char*>("(OO)"),
                          first, second);
    if (result == 0 && 
        (PyErr_GivenExceptionMatches(PyErr_Occurred(), PyExc_TypeError) ||
         PyErr_GivenExceptionMatches(PyErr_Occurred(), PyExc_AttributeError)))
    {
        PyErr_Clear();
        PyErr_SetString(PyExc_TypeError, "bad operand type(s) for pow()");
    }
    return result;
}

int operator_dispatcher_call_cmp(PyObject* left, PyObject* right)
{
    // unwrap the arguments from their OperatorDispatcher
    PyObject* self;
    PyObject* other;
    int reverse =  unwrap_args(left, right, self, other);
    if (reverse == unwrap_exception_code)
        return -1;
    
    // call the function
    PyObject* result = 
        PyEval_CallMethod(self,
                          const_cast<char*>(reverse ? "__rcmp__" : "__cmp__"),
                          const_cast<char*>("(O)"),
                          other);
    if (result == 0)
    {
        PyErr_Clear();
        PyErr_SetString(PyExc_TypeError, "bad operand type(s) for cmp() or <");
        return -1;
    }
    else
    {
        try
        {
            return PY_CONVERSION::from_python(result, Type<int>());
        }
        catch(...)
        {
            PyErr_Clear();
            PyErr_SetString(PyExc_TypeError, "cmp() didn't return int");
            return -1;
        }
    }
}

} // extern "C"
    
PyTypeObject operator_dispatcher::type_object = 
{ 
    PyObject_HEAD_INIT(&PyType_Type) 
    0, 
    const_cast<char*>("operator_dispatcher"), 
    sizeof(operator_dispatcher), 
    0, 
    &operator_dispatcher_dealloc, 
    0, 
    0, 
    0, 
    &operator_dispatcher_call_cmp, 
    0, 
    &operator_dispatcher::number_methods, 
    0, 
    0, 
    0, 
    0, 
    0, 
    0, 
    0, 
    0, 
    0, 
    0,
    0,
    0,
    0,
    0
}; 

PyNumberMethods operator_dispatcher::number_methods = 
{ 
    &operator_dispatcher_call_add, 
    &operator_dispatcher_call_sub, 
    &operator_dispatcher_call_mul, 
    &operator_dispatcher_call_div, 
    &operator_dispatcher_call_mod, 
    &operator_dispatcher_call_divmod, 
    &operator_dispatcher_call_pow, 
    0, 
    0, 
    0, 
    0, 
    0, 
    &operator_dispatcher_call_lshift, 
    &operator_dispatcher_call_rshift, 
    &operator_dispatcher_call_and, 
    &operator_dispatcher_call_xor, 
    &operator_dispatcher_call_or, 
    &operator_dispatcher_coerce,  
    0, 
    0, 
    0, 
    0, 
    0 
}; 

} // namespace detail

} // namespace py
