//  (C) Copyright David Abrahams 2000. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
//  The author gratefully acknowleges the support of Dragon Systems, Inc., in
//  producing this work.
//
// Revision History:
// 04 Mar 01  Use PyObject_INIT() instead of trying to hand-initialize (David Abrahams)

#include <boost/python/detail/extension_class.hpp>
#include <cstring>
#include <boost/utility.hpp>

namespace boost { namespace python {
namespace detail {

  struct operator_dispatcher
      : public PyObject
  {
      static PyTypeObject type_obj;
      static PyNumberMethods number_methods;

      static operator_dispatcher* create(const ref& o, const ref& s);     
      
      ref m_object;
      ref m_self;

      // data members for allocation/deallocation optimization
      operator_dispatcher* m_free_list_link;
      static operator_dispatcher* free_list;

  private: 
      // only accessible through create()
      operator_dispatcher(const ref& o, const ref& s);
  };
  
  operator_dispatcher* operator_dispatcher::free_list = 0;

}}} // namespace boost::python::detail

BOOST_PYTHON_BEGIN_CONVERSION_NAMESPACE

inline PyObject* to_python(boost::python::semantics, boost::python::detail::operator_dispatcher* n) { return n; }

BOOST_PYTHON_END_CONVERSION_NAMESPACE


namespace boost { namespace python { 

tuple standard_coerce(ref l, ref r)
{
    // Introduced sequence points for exception-safety.
    ref first(detail::operator_dispatcher::create(l, l));
    
    ref second(r->ob_type == &detail::operator_dispatcher::type_obj
               ? r
               : ref(detail::operator_dispatcher::create(r, ref())));

    return tuple(first, second);
}

namespace detail {

  enum { unwrap_exception_code = -1000 };

  int unwrap_args(PyObject* left, PyObject* right, PyObject*& self, PyObject*& other)
  {
      if (left->ob_type != &operator_dispatcher::type_obj ||
          right->ob_type != &operator_dispatcher::type_obj)
      {
          PyErr_SetString(PyExc_RuntimeError, "operator_dispatcher::unwrap_args(): expecting operator_dispatcher arguments only!");
          return unwrap_exception_code;
      }

      typedef reference<operator_dispatcher> DPtr;
      DPtr lwrapper(static_cast<operator_dispatcher*>(left), DPtr::increment_count);
      DPtr rwrapper(static_cast<operator_dispatcher*>(right), DPtr::increment_count);
      
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
      if (left->ob_type != &operator_dispatcher::type_obj ||
          right->ob_type != &operator_dispatcher::type_obj ||
          m->ob_type != &operator_dispatcher::type_obj)
      {
          PyErr_SetString(PyExc_RuntimeError, "operator_dispatcher::unwrap_pow_args(): expecting operator_dispatcher arguments only!");
          return unwrap_exception_code;
      }
      
      typedef reference<operator_dispatcher> DPtr;
      DPtr lwrapper(static_cast<operator_dispatcher*>(left), DPtr::increment_count);
      DPtr rwrapper(static_cast<operator_dispatcher*>(right), DPtr::increment_count);
      DPtr mwrapper(static_cast<operator_dispatcher*>(m), DPtr::increment_count);
      
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

extension_instance* get_extension_instance(PyObject* p)
{
    // The object's type will just be some class_t<extension_instance> object,
    // but if its meta-type is right, then it is an extension_instance.
    if (p->ob_type->ob_type != extension_meta_class())
    {
        PyErr_SetString(PyExc_TypeError, p->ob_type->tp_name);
        throw boost::python::argument_error();
    }
    return static_cast<extension_instance*>(p);
}

void
extension_instance::add_implementation(std::auto_ptr<instance_holder_base> holder)
{
    for (held_objects::const_iterator p = m_wrapped_objects.begin();
         p != m_wrapped_objects.end(); ++p)
    {
        if (typeid(*holder) == typeid(**p))
        {
            PyErr_SetString(PyExc_RuntimeError, "Base class already initialized");
            throw error_already_set();
        }
    }
    m_wrapped_objects.push_back(holder.release());
}

extension_instance::extension_instance(PyTypeObject* class_)
    : instance(class_)
{
}

extension_instance::~extension_instance()
{
    for (held_objects::const_iterator p = m_wrapped_objects.begin(),
             finish = m_wrapped_objects.end();
         p != finish; ++p)
    {
        delete *p;
    }
}
    
meta_class<extension_instance>* extension_meta_class()
{
    static meta_class<extension_instance> result;
    return &result;
}

typedef class_t<extension_instance> extension_class_t;

bool is_subclass(const extension_class_t* derived,
                 const PyObject* possible_base)
{

    tuple bases = derived->bases();
    
    for (std::size_t i = 0, size = bases.size(); i < size; ++i)
    {
        const PyObject* base = bases[i].get();
        
        if (base == possible_base)
            return true;
        
        if (base->ob_type == extension_meta_class())
        {
            const extension_class_t* base_class = downcast<const extension_class_t>(base);
            if (is_subclass(base_class, possible_base))
                return true;
        }
    }
    return false;
}

// Return true iff obj is an obj of target_class
bool is_instance(extension_instance* obj,
                 class_t<extension_instance>* target_class)
{
    if (obj->ob_type == target_class)
        return true;
    else
    {
        return is_subclass(
            downcast<class_t<extension_instance> >(obj->ob_type).get(),
            as_object(target_class));
    }
}

void two_string_error(PyObject* exception_object, const char* format, const char* s1, const char* s2)
{
    char buffer[256];
    std::size_t format_length = BOOST_CSTD_::strlen(format);
    std::size_t length1 = BOOST_CSTD_::strlen(s1);
    std::size_t length2 = BOOST_CSTD_::strlen(s2);

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
        throw argument_error();
    else
        throw error_already_set();
}

// This is called when an attempt has been made to convert the given obj to
// a C++ type for which it doesn't have any obj data. In that case, either
// the obj was not derived from the target_class, or the appropriate
// __init__ function wasn't called to initialize the obj data of the target class.
void report_missing_instance_data(
    extension_instance* obj,                // The object being converted
    class_t<extension_instance>* target_class,     // the extension class of the C++ type
    const std::type_info& target_typeid,        // The typeid of the C++ type
    bool target_is_ptr)
{
    char buffer[256];
    if (is_instance(obj, target_class))
    {
        if (target_is_ptr)
        {
            two_string_error(PyExc_RuntimeError,
                             "Object of extension class '%.*s' does not wrap <%.*s>.",
                             obj->ob_type->tp_name, target_typeid.name());
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
                         obj->ob_type->tp_name, target_class->tp_name);
    }
}

void report_missing_instance_data(
    extension_instance* obj,                // The object being converted
    class_t<extension_instance>* target_class,     // the extension class of the C++ type
    const std::type_info& target_typeid)        // The typeid of the C++ type
{
    report_missing_instance_data(obj, target_class, target_typeid, false);
}

void report_missing_ptr_data(
    extension_instance* obj,                // The object being converted
    class_t<extension_instance>* target_class,     // the extension class of the C++ type
    const std::type_info& target_typeid)        // The typeid of the C++ type
{
    report_missing_instance_data(obj, target_class, target_typeid, true);
}

void report_missing_class_object(const std::type_info& info)
{
    char buffer[256];
    const char message[] = "Cannot convert <%.*s> to python; its Python class was never created or has been deleted.";
    sprintf(buffer, message, sizeof(buffer) - sizeof(message) - 1, info.name());
    PyErr_SetString(PyExc_RuntimeError, buffer);
    throw error_already_set();
}

void report_released_smart_pointer(const std::type_info& info)
{
    char buffer[256];
    const char message[] = "Converting from python, pointer or smart pointer to <%.*s> is NULL.";
    sprintf(buffer, message, sizeof(buffer) - sizeof(message) - 1, info.name());
    PyErr_SetString(PyExc_RuntimeError, buffer);
    throw argument_error();
}

read_only_setattr_function::read_only_setattr_function(const char* name)
    : m_name(name)
{
}

PyObject* read_only_setattr_function::do_call(PyObject* /*args*/, PyObject* /*keywords*/) const
{
    PyErr_SetObject(PyExc_AttributeError, ("'" + m_name + "' attribute is read-only").get());
    return 0;
}

const char* read_only_setattr_function::description() const
{
    return "uncallable";
}

extension_class_base::extension_class_base(const char* name)
    : class_t<extension_instance>(
        extension_meta_class(), string(name), tuple(), dictionary())
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
//  to the contained object from an instance_holder_base (a wrapper class). A conversion
//  of the held object to 'T *' is allowed when the conversion 
//  'dynamic_cast<instance_holder<T> *>(an_instance_holder_base)' succeeds.
void* extension_class_base::try_class_conversions(instance_holder_base* object) const
{
    void* result = try_derived_class_conversions(object);
    if (result) 
        return result;
        
    if (!object->held_by_value())
        return try_base_class_conversions(object);
    else
        return 0;
}

void* extension_class_base::try_base_class_conversions(instance_holder_base* object) const
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

void* extension_class_base::try_derived_class_conversions(instance_holder_base* object) const
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

void extension_class_base::add_method(function* method, const char* name)
{
    add_method(reference<function>(method), name);
}
    
void extension_class_base::add_method(reference<function> method, const char* name)
{
    // Add the attribute to the computed target
    function::add_to_namespace(method, name, this->dict().get());

    // If it is a special member function it should be enabled both here and there.
    detail::enable_named_method(this, name);
}

void extension_class_base::add_constructor_object(function* init_fn)
{
    add_method(init_fn, "__init__");
}

void extension_class_base::add_setter_method(function* setter_, const char* name)
{
    reference<function> setter(setter_);
    add_method(setter, (detail::setattr_string() + name + "__").c_str());
}

void extension_class_base::add_getter_method(function* getter_, const char* name)
{
    reference<function> getter(getter_);
    add_method(getter, (detail::getattr_string() + name + "__").c_str());
}

void extension_class_base::set_attribute(const char* name, PyObject* x_)
{
    ref x(x_);
    set_attribute(name, x);
}

void extension_class_base::set_attribute(const char* name, ref x)
{
    dict().set_item(string(name), x);
    if (PyCallable_Check(x.get()))
        detail::enable_named_method(this, name);
}

operator_dispatcher::operator_dispatcher(const ref& o, const ref& s)
    : m_object(o), m_self(s), m_free_list_link(0)

{
    PyObject* self = this;
    PyObject_INIT(self, &type_obj);
}

operator_dispatcher* 
operator_dispatcher::create(const ref& object, const ref& self)
{
    operator_dispatcher* const result = free_list;
    if (result == 0)
        return new operator_dispatcher(object, self);
    
    free_list = result->m_free_list_link;
    result->m_object = object;
    result->m_self = self;

    PyObject* result_as_pyobject = result;
    PyObject_INIT(result_as_pyobject, &type_obj);
    return result;
}

extern "C"
{

void operator_dispatcher_dealloc(PyObject* self) 
{ 
    operator_dispatcher* obj = static_cast<operator_dispatcher*>(self);
    obj->m_free_list_link = operator_dispatcher::free_list;
    operator_dispatcher::free_list = obj;
    obj->m_object.reset();
    obj->m_self.reset();
} 

int operator_dispatcher_coerce(PyObject** l, PyObject** r)
{
    Py_INCREF(*l);
    try
    {
        *r = operator_dispatcher::create(ref(*r, ref::increment_count), ref());
    }
    catch(...)
    {
        handle_exception();
        return -1;
    }
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
            return BOOST_PYTHON_CONVERSION::from_python(result, type<int>());
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
    
PyTypeObject operator_dispatcher::type_obj = 
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

}} // namespace boost::python
