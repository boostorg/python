//  (C) Copyright David Abrahams 2000. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
//  The author gratefully acknowleges the support of Dragon Systems, Inc., in
//  producing this work.

#include <boost/python/detail/types.hpp>
#include <boost/python/reference.hpp> // for handle_exception()
#include <boost/python/conversions.hpp>
#include <boost/python/module_builder.hpp>
#include <boost/python/detail/none.hpp>
#include <boost/python/detail/void_adaptor.hpp>
#include <cstring>
#include <vector>
#include <cstddef>
#include <stdexcept>
#include <boost/smart_ptr.hpp>
#include <boost/python/objects.hpp>
#include <boost/type_traits/alignment_traits.hpp>
#include <boost/bind.hpp>

namespace boost { namespace python {

namespace {

  using detail::type_object_base;

  // Define a family of forwarding functions that can be called from a
  // PyTypeObject's slots. These functions dispatch through a (virtual) member
  // function pointer in the type_object_base, and handle exceptions in a
  // uniform way, preventing us from having to rewrite the dispatching code over
  // and over.


  // Given a function object f with signature
  //
  //    PyObject* f(PyTypeObject*,PyObject*)
  //
  // calls f inside of handle_exception, and returns the result. If an exception
  // is thrown by f, returns 0.
  template <class F>
  PyObject* obj_call(PyObject* obj, F const& f)
  {
      return handle_exception(
          boost::bind<PyObject*>(f, static_cast<type_object_base*>(obj->ob_type), obj));
  }


  // int_converter<T>/value_holder<T>
  //
  // A simple function object which converts its argument to a PyObject*. We
  // need this because handle_exception needs to return a PyObject*, even if the
  // function being called is supposed to return int. It has two parts...

  // holds the value actually returned by the underlying function
  template <class T>
  struct value_holder : PyObject
  {
      value_holder() : is_set(false), value(-1) {}

      // Tricky constructor allows us to grab the result even if rhs == 0.
      explicit value_holder(value_holder const* rhs)
          : is_set(rhs ? rhs->is_set : false), value(rhs ? rhs->value : -1) {}

      // true if the function object was ever called (false if an exception occurred)
      bool is_set;

      // The returned value
      T value;
  };

  // The function object
  template <class R>
  struct int_converter
  {
      typedef PyObject* result_type;
      
      PyObject* operator()(R const& x)
      {
          m_holder.is_set = true;
          m_holder.value = x;
          return &m_holder; // returns
      }

      value_holder<R> m_holder;
  };

  // Call the given int-returning function object inside of handle_exception,
  // returning a value_holder. F is a function object with "signature"
  //
  //     R F(PyTypeObject*, PyObject*)
  //
  // where R is an integer type.
  template <class R, class F>
  value_holder<R> int_call_holder(PyObject* obj, F f)
  {
      return value_holder<R>(
          
          // The int_converter object containing the value_holder is valid
          // through the life of the full-expression, so we can construct from
          // the pointer
          static_cast<value_holder<R>*>(
              handle_exception(

                  boost::bind<PyObject*>(
                      // Add an int_converter back-end to f
                      int_converter<R>()
                      // Bind the object's type and the object itself into f
                      , boost::bind<R>(f, static_cast<type_object_base*>(obj->ob_type), obj)
                      )
                  
                  )
              )
          );
  }

  // Just like int_call_holder (above), but returns the integer directly. If F
  // throws an exception, returns -1
  template <class R, class F>
  R int_call(PyObject* obj, F f)
  {
      value_holder<R> const v(int_call_holder<R>(obj, f));
      return v.value;
  }

  // Implemented in terms of obj_call, above
  PyObject* call(PyObject* obj, PyObject* (type_object_base::*f)(PyObject*) const)
  {
      return obj_call(obj, bind(f, _1, _2));
  }

  // Implemented in terms of int_call, above
  int call(PyObject* obj, int (type_object_base::*f)(PyObject*) const)
  {
      return int_call<int>(obj, bind(f, _1, _2));
  }

  template <class A1>
  PyObject* call(PyObject* obj, PyObject* (type_object_base::*f)(PyObject*, A1) const, A1 a1)
  {
      return obj_call(obj, bind(f, _1, _2, a1));
  }

  template <class A1>
  int call(PyObject* obj, int (type_object_base::*f)(PyObject*, A1) const, A1 a1)
  {
      return int_call<int>(obj, bind(f, _1, _2, a1));
  }

  template <class A1, class A2>
  PyObject* call(PyObject* obj, PyObject* (type_object_base::*f)(PyObject*, A1, A2) const, A1 a1, A2 a2)
  {
      return obj_call(obj, bind(f, _1, _2, a1, a2));
  }

  template <class A1, class A2>
  int call(PyObject* obj, int (type_object_base::*f)(PyObject*, A1, A2) const, A1 a1, A2 a2)
  {
      return int_call<int>(obj, bind(f, _1, _2, a1, a2));
  }

  template <class A1, class A2, class A3>
  int call(PyObject* obj, int (type_object_base::*f)(PyObject*, A1, A2, A3) const, A1 a1, A2 a2, A3 a3)
  {
      return int_call<int>(obj, bind(f, _1, _2, a1, a2, a3));
  }

  int call_length_function(PyObject* obj, int (type_object_base::*f)(PyObject*) const)
  {
      value_holder<int> const r(int_call_holder<int>(obj, bind(f, _1, _2)));
      
      if (!r.is_set)
      {
          return -1;
      }
      
      const int outcome = r.value;
      if (outcome >= 0)
          return outcome;

      PyErr_SetString(PyExc_ValueError, "__len__() should return >= 0");
      return -1;
  }
}  // anonymous namespace

namespace detail {
  // needed by void_adaptor (see void_adaptor.hpp)
  PyObject arbitrary_object;
}

extern "C" {

//
// These functions actually go into the type object's slots, and dispatch to the
// "call" wrappers defined above.
//
static PyObject* do_instance_repr(PyObject* obj)
{
    return call(obj, &type_object_base::instance_repr);
}

static PyObject* do_instance_richcompare(PyObject* obj, PyObject* other, int d)
{
#if PYTHON_API_VERSION >= 1010
    switch(d)
    {
        case Py_LT: 
          return call(obj, &type_object_base::instance_lt, other);
        case Py_LE: 
          return call(obj, &type_object_base::instance_le, other);
        case Py_EQ: 
          return call(obj, &type_object_base::instance_eq, other);
        case Py_NE: 
          return call(obj, &type_object_base::instance_ne, other);
        case Py_GT: 
          return call(obj, &type_object_base::instance_gt, other);
        case Py_GE: 
          return call(obj, &type_object_base::instance_ge, other);
    }
#endif
    return 0;
}

static int do_instance_compare(PyObject* obj, PyObject* other)
{
    return call(obj, &type_object_base::instance_compare, other);
}

static PyObject* do_instance_str(PyObject* obj)
{
    return call(obj, &type_object_base::instance_str);
}

static long do_instance_hash(PyObject* obj)
{
    return int_call<long>(obj, bind(&type_object_base::instance_hash, _1, _2));
}
    
static PyObject* do_instance_call(PyObject* obj, PyObject* args, PyObject* keywords)
{
    return call(obj, &type_object_base::instance_call, args, keywords);
}

static void do_instance_dealloc(PyObject* obj)
{
    PyObject* success = handle_exception(
        // translate the void return value of instance_dealloc into a PyObject*
        // that can indicate no error.
        detail::make_void_adaptor(
            bind(&type_object_base::instance_dealloc
                       , static_cast<type_object_base*>(obj->ob_type)
                       , obj)));
    if (!success)
    {
        assert(!"exception during destruction!");
    }
}

static PyObject* do_instance_getattr(PyObject* obj, char* name)
{
    const char* name_ = name;
    return call(obj, &type_object_base::instance_getattr, name_);
}

static int do_instance_setattr(PyObject* obj, char* name, PyObject* value)
{
    const char* name_ = name;
    return call(obj, &type_object_base::instance_setattr, name_, value);
}

static int do_instance_mp_length(PyObject* obj)
{
    return call_length_function(obj, &type_object_base::instance_mapping_length);
}

static int do_instance_sq_length(PyObject* obj)
{
    return call_length_function(obj, &type_object_base::instance_sequence_length);
}

static PyObject* do_instance_mp_subscript(PyObject* obj, PyObject* index)
{
    return call(obj, &type_object_base::instance_mapping_subscript, index);
}

static PyObject* do_instance_sq_item(PyObject* obj, int index)
{
    // This is an extension to standard class behavior. If sequence_length
    // is implemented and n >= sequence_length(), raise an IndexError. That
    // keeps users from having to worry about raising it themselves
    const PyTypeObject* const type = obj->ob_type;
    if (type->tp_as_sequence != 0 && type->tp_as_sequence->sq_length != 0
        && index >= type->tp_as_sequence->sq_length(obj))
    {
        PyErr_SetString(PyExc_IndexError, type->tp_name);
        return 0;
    }

    return handle_exception(
        bind(&type_object_base::instance_sequence_item
             , static_cast<type_object_base*>(obj->ob_type)
             , obj
             , index));
}

static int do_instance_mp_ass_subscript(PyObject* obj, PyObject* index, PyObject* value)
{
    return call(obj, &type_object_base::instance_mapping_ass_subscript, index, value);
}

static int do_instance_sq_ass_item(PyObject* obj, int index, PyObject* value)
{
    return call(obj, &type_object_base::instance_sequence_ass_item, index, value);
}

static PyObject* do_instance_sq_concat(PyObject* obj, PyObject* other)
{
    return call(obj, &type_object_base::instance_sequence_concat, other);
}

static PyObject* do_instance_sq_repeat(PyObject* obj, int n)
{
    return call(obj, &type_object_base::instance_sequence_repeat, n);
}

static PyObject* do_instance_sq_slice(
    PyObject* obj, int start, int finish)
{
    return call(obj, &type_object_base::instance_sequence_slice, start, finish);
}

static int do_instance_sq_ass_slice(
    PyObject* obj, int start, int finish, PyObject* value)
{
    return call(obj, &type_object_base::instance_sequence_ass_slice, start, finish, value);
}

static PyObject* do_instance_nb_add(PyObject* obj, PyObject* other)
{
    return call(obj, &type_object_base::instance_number_add, other);
}

static PyObject* do_instance_nb_subtract(PyObject* obj, PyObject* other)
{
    return call(obj, &type_object_base::instance_number_subtract, other);
}

static PyObject* do_instance_nb_multiply(PyObject* obj, PyObject* other)
{
    return call(obj, &type_object_base::instance_number_multiply, other);
}

static PyObject* do_instance_nb_divide(PyObject* obj, PyObject* other)
{
    return call(obj, &type_object_base::instance_number_divide, other);
}

static PyObject* do_instance_nb_remainder(PyObject* obj, PyObject* other)
{
    return call(obj, &type_object_base::instance_number_remainder, other);
}

static PyObject* do_instance_nb_divmod(PyObject* obj, PyObject* other)
{
    return call(obj, &type_object_base::instance_number_divmod, other);
}

static PyObject* do_instance_nb_power(PyObject* obj, PyObject* exponent, PyObject* modulus)
{
    return call(obj, &type_object_base::instance_number_power, exponent, modulus);
}

static PyObject* do_instance_nb_negative(PyObject* obj)
{
    return call(obj, &type_object_base::instance_number_negative);
}

static PyObject* do_instance_nb_positive(PyObject* obj)
{
    return call(obj, &type_object_base::instance_number_positive);
}

static PyObject* do_instance_nb_absolute(PyObject* obj)
{
    return call(obj, &type_object_base::instance_number_absolute);
}

static int do_instance_nb_nonzero(PyObject* obj)
{
    return call(obj, &type_object_base::instance_number_nonzero);
}

static PyObject* do_instance_nb_invert(PyObject* obj)
{
    return call(obj, &type_object_base::instance_number_invert);
}

    
static PyObject* do_instance_nb_lshift(PyObject* obj, PyObject* other)
{
    return call(obj, &type_object_base::instance_number_lshift, other);
}

static PyObject* do_instance_nb_rshift(PyObject* obj, PyObject* other)
{
    return call(obj, &type_object_base::instance_number_rshift, other);
}

static PyObject* do_instance_nb_and(PyObject* obj, PyObject* other)
{
    return call(obj, &type_object_base::instance_number_and, other);
}

static PyObject* do_instance_nb_xor(PyObject* obj, PyObject* other)
{
    return call(obj, &type_object_base::instance_number_xor, other);
}

static PyObject* do_instance_nb_or(PyObject* obj, PyObject* other)
{
    return call(obj, &type_object_base::instance_number_or, other);
}

static int do_instance_nb_coerce(PyObject**obj, PyObject**other)
{
    // no call() overload for this oddball function, so we'll do it manually
    return int_call<int>(
        *obj, bind(
            &type_object_base::instance_number_coerce, _1, _2, obj, other));
}
static PyObject* do_instance_nb_int(PyObject* obj)
{
    return call(obj, &type_object_base::instance_number_int);
}

static PyObject* do_instance_nb_long(PyObject* obj)
{
    return call(obj, &type_object_base::instance_number_long);
}

static PyObject* do_instance_nb_float(PyObject* obj)
{
    return call(obj, &type_object_base::instance_number_float);
}

static PyObject* do_instance_nb_oct(PyObject* obj)
{
    return call(obj, &type_object_base::instance_number_oct);
}

static PyObject* do_instance_nb_hex(PyObject* obj)
{
    return call(obj, &type_object_base::instance_number_hex);
}

static PyObject* do_instance_nb_inplace_add(PyObject* obj, PyObject* other)
{
    return call(obj, &type_object_base::instance_number_inplace_add, other);
}

static PyObject* do_instance_nb_inplace_subtract(PyObject* obj, PyObject* other)
{
    return call(obj, &type_object_base::instance_number_inplace_subtract, other);
}

static PyObject* do_instance_nb_inplace_multiply(PyObject* obj, PyObject* other)
{
    return call(obj, &type_object_base::instance_number_inplace_multiply, other);
}

static PyObject* do_instance_nb_inplace_divide(PyObject* obj, PyObject* other)
{
    return call(obj, &type_object_base::instance_number_inplace_divide, other);
}

static PyObject* do_instance_nb_inplace_remainder(PyObject* obj, PyObject* other)
{
    return call(obj, &type_object_base::instance_number_inplace_remainder, other);
}

static PyObject* do_instance_nb_inplace_power(PyObject* obj, PyObject* exponent, PyObject* modulus)
{
    return call(obj, &type_object_base::instance_number_inplace_power, exponent, modulus);
}

static PyObject* do_instance_nb_inplace_lshift(PyObject* obj, PyObject* other)
{
    return call(obj, &type_object_base::instance_number_inplace_lshift, other);
}

static PyObject* do_instance_nb_inplace_rshift(PyObject* obj, PyObject* other)
{
    return call(obj, &type_object_base::instance_number_inplace_rshift, other);
}

static PyObject* do_instance_nb_inplace_and(PyObject* obj, PyObject* other)
{
    return call(obj, &type_object_base::instance_number_inplace_and, other);
}

static PyObject* do_instance_nb_inplace_or(PyObject* obj, PyObject* other)
{
    return call(obj, &type_object_base::instance_number_inplace_or, other);
}

static PyObject* do_instance_nb_inplace_xor(PyObject* obj, PyObject* other)
{
    return call(obj, &type_object_base::instance_number_inplace_xor, other);
}

} // extern "C"

namespace
{

#define ENABLE_GENERAL_CAPABILITY(field) \
    case type_object_base::field: \
        dest->tp_##field = &do_instance_##field; \
        return true

bool add_capability_general(type_object_base::capability capability, PyTypeObject* dest)
{
    assert(dest != 0);

    switch(capability)
    {
        ENABLE_GENERAL_CAPABILITY(hash);
        ENABLE_GENERAL_CAPABILITY(call);
        ENABLE_GENERAL_CAPABILITY(str);
        ENABLE_GENERAL_CAPABILITY(getattr);
        ENABLE_GENERAL_CAPABILITY(setattr);
        ENABLE_GENERAL_CAPABILITY(compare);
        ENABLE_GENERAL_CAPABILITY(repr);
        default:
            return false;
    }
}


template <class T>
void create_method_table_if_null(T*& table)
{
    if(table == 0)
    {
        detail::shared_pod_manager::create(table);
    }
    else
    {
        detail::shared_pod_manager::make_unique_copy(table);
    }
}

bool add_capability_richcompare(type_object_base::capability capability, PyTypeObject* dest)
{
    assert(dest != 0);
    if (capability == type_object_base::richcompare) {
#if PYTHON_API_VERSION >= 1010
      dest->tp_richcompare = &do_instance_richcompare;
      dest->tp_flags |= Py_TPFLAGS_HAVE_RICHCOMPARE;
#endif
      return true;
    }
    
    return false;
}

#define ENABLE_INPLACE_CAPABILITY(field) \
    case type_object_base::number_##field: \
        create_method_table_if_null(dest->tp_as_number); \
        dest->tp_as_number->nb_##field = &do_instance_nb_##field; \
        detail::shared_pod_manager::replace_if_equal(dest->tp_as_number); \
        dest->tp_flags |= Py_TPFLAGS_HAVE_INPLACEOPS; \
        return true

bool add_capability_inplace(type_object_base::capability capability, PyTypeObject* dest)
{
    assert(dest != 0);
    switch (capability)
    {
#if PYTHON_API_VERSION >= 1010
        ENABLE_INPLACE_CAPABILITY (inplace_add);
        ENABLE_INPLACE_CAPABILITY (inplace_subtract);
        ENABLE_INPLACE_CAPABILITY (inplace_multiply);
        ENABLE_INPLACE_CAPABILITY (inplace_divide);
        ENABLE_INPLACE_CAPABILITY (inplace_remainder);
        ENABLE_INPLACE_CAPABILITY (inplace_power);
        ENABLE_INPLACE_CAPABILITY (inplace_lshift);
        ENABLE_INPLACE_CAPABILITY (inplace_rshift);
        ENABLE_INPLACE_CAPABILITY (inplace_and);
        ENABLE_INPLACE_CAPABILITY (inplace_or);
        ENABLE_INPLACE_CAPABILITY (inplace_xor);
#endif
        default:
            return false;
    }
}

#define ENABLE_MAPPING_CAPABILITY(field) \
    case type_object_base::mapping_##field: \
        create_method_table_if_null(dest); \
        dest->mp_##field = &do_instance_mp_##field; \
        detail::shared_pod_manager::replace_if_equal(dest); \
        return true

bool add_capability_mapping(type_object_base::capability capability, PyMappingMethods*& dest)
{
    switch(capability)
    {
        ENABLE_MAPPING_CAPABILITY(length);
        ENABLE_MAPPING_CAPABILITY(subscript);
        ENABLE_MAPPING_CAPABILITY(ass_subscript);
        default:
            return false;
    }
}

#define ENABLE_SEQUENCE_CAPABILITY(field) \
    case type_object_base::sequence_##field: \
        create_method_table_if_null(dest); \
        dest->sq_##field = &do_instance_sq_##field; \
        detail::shared_pod_manager::replace_if_equal(dest); \
        return true

bool add_capability_sequence(type_object_base::capability capability, PySequenceMethods*& dest)
{
    switch(capability)
    {
        ENABLE_SEQUENCE_CAPABILITY(length);
        ENABLE_SEQUENCE_CAPABILITY(item);
        ENABLE_SEQUENCE_CAPABILITY(ass_item);
        ENABLE_SEQUENCE_CAPABILITY(concat);
        ENABLE_SEQUENCE_CAPABILITY(repeat);
        ENABLE_SEQUENCE_CAPABILITY(slice);
        ENABLE_SEQUENCE_CAPABILITY(ass_slice);
        default:
            return false;
    }
}

#define ENABLE_NUMBER_CAPABILITY(field) \
    case type_object_base::number_##field: \
        create_method_table_if_null(dest); \
        dest->nb_##field = &do_instance_nb_##field; \
        detail::shared_pod_manager::replace_if_equal(dest); \
        return true

bool add_capability_number(type_object_base::capability capability, PyNumberMethods*& dest)
{
    switch(capability)
    {
        ENABLE_NUMBER_CAPABILITY(add);
        ENABLE_NUMBER_CAPABILITY(subtract);
        ENABLE_NUMBER_CAPABILITY(multiply);
        ENABLE_NUMBER_CAPABILITY(divide);
        ENABLE_NUMBER_CAPABILITY(remainder);
        ENABLE_NUMBER_CAPABILITY(divmod);
        ENABLE_NUMBER_CAPABILITY(power);
        ENABLE_NUMBER_CAPABILITY(negative);
        ENABLE_NUMBER_CAPABILITY(positive);
        ENABLE_NUMBER_CAPABILITY(absolute);
        ENABLE_NUMBER_CAPABILITY(nonzero);
        ENABLE_NUMBER_CAPABILITY(invert);
        ENABLE_NUMBER_CAPABILITY(lshift);
        ENABLE_NUMBER_CAPABILITY(rshift);
        ENABLE_NUMBER_CAPABILITY(and);
        ENABLE_NUMBER_CAPABILITY(xor);
        ENABLE_NUMBER_CAPABILITY(or);
        ENABLE_NUMBER_CAPABILITY(coerce);
        ENABLE_NUMBER_CAPABILITY(int);
        ENABLE_NUMBER_CAPABILITY(long);
        ENABLE_NUMBER_CAPABILITY(float);
        ENABLE_NUMBER_CAPABILITY(oct);
        ENABLE_NUMBER_CAPABILITY(hex);
        default:
            return false;
    }
}

#define ENABLE_BUFFER_CAPABILITY(field) \
    case type_object_base::buffer_##field: \
        create_method_table_if_null(dest); \
        dest->bf_##field = &do_instance_bf_##field; \
        detail::shared_pod_manager::replace_if_equal(dest); \
        return true

bool add_capability_buffer(type_object_base::capability capability, PyBufferProcs*& dest)
{
    (void)dest; // suppress unused argument warning
    (void)capability; // likwise
#if 0
    switch(capability)
    {
        // nothing defined yet
        default:
            return false;
    }
#endif
    return false;
}

} // anonymous namespace

namespace detail  {

  void add_capability(
      type_object_base::capability capability,
      PyTypeObject* dest_)
  {
    if(add_capability_general(capability, dest_))
        return;
    if(add_capability_richcompare(capability, dest_))
        return;
    if(add_capability_inplace(capability, dest_))
        return;
    if(add_capability_mapping(capability, dest_->tp_as_mapping))
        return;
    if(add_capability_sequence(capability, dest_->tp_as_sequence))
        return;
    if(add_capability_number(capability, dest_->tp_as_number))
        return;
    if(add_capability_buffer(capability, dest_->tp_as_buffer))
        return;

    // no one recognized the capability
    throw std::runtime_error("py::detail::add_capability(): unknown capability");
  }
} // namespace detail

type_object_base::~type_object_base()
{
    detail::shared_pod_manager::dispose(tp_as_mapping);
    detail::shared_pod_manager::dispose(tp_as_sequence);
    detail::shared_pod_manager::dispose(tp_as_number);
    detail::shared_pod_manager::dispose(tp_as_buffer);
}

void type_object_base::enable(type_object_base::capability capability)
{
    detail::add_capability(capability, this);
}

type_object_base::type_object_base(PyTypeObject* t)
    : python_type(t)
{
    this->tp_dealloc = do_instance_dealloc;
}

namespace
{
  typedef long pod_refcount;

  inline pod_refcount pod_refcount_offset(std::size_t size)
  {
      const std::size_t alignment = boost::alignment_of<pod_refcount>::value;
      return (size + alignment - 1) / alignment * alignment;
  }

  inline pod_refcount* counted_pod_refcount(char* pod, std::size_t size)
  {
      if(pod == 0)
          return 0;
      
      return reinterpret_cast<pod_refcount*>(pod + pod_refcount_offset(size));
  }

  #ifdef TYPE_OBJECT_BASE_STANDALONE_TEST
  int pod_instance_counter = 0;
  #endif

  inline pod_refcount counted_pod_getref(char* pod, std::size_t size)
  {
      pod_refcount* ref_count = counted_pod_refcount(pod, size);
      return ref_count == 0 ? -1 : *ref_count;
  }

  inline pod_refcount counted_pod_decref(char* pod, std::size_t size)
  {
      pod_refcount* const ref_count = counted_pod_refcount(pod, size);
      if (ref_count == 0)
          return -1;
      --(*ref_count);
      if (*ref_count <= 0)
      {
  #ifdef TYPE_OBJECT_BASE_STANDALONE_TEST
          --pod_instance_counter;
  #endif
          ::operator delete(pod);
          return 0;
      }
      return *ref_count;
  }

  pod_refcount counted_pod_incref(char* pod, std::size_t size)
  {
      pod_refcount* ref_count = counted_pod_refcount(pod, size);
      return ref_count == 0 ? -1 : ++(*ref_count);
  }

} // anonymous namespace

namespace detail
{
  struct shared_pod_manager::compare
  {
      bool operator()(const std::pair<char*, std::size_t>& x1,
                      const std::pair<char*, std::size_t>& x2) const
      {
          const std::size_t n1 = x1.second;
          const std::size_t n2 = x2.second;
          return n1 < n2 || n1 == n2 && BOOST_CSTD_::memcmp(x1.first, x2.first, n1) < 0;
      }
  };

  struct shared_pod_manager::identical
  {
      identical(char* p) : pod(p) {}

      bool operator()(const std::pair<char*, std::size_t>& x) const
      {
          return pod == x.first;
      }

      char* pod;
  };

  shared_pod_manager& shared_pod_manager::obj()
  {
      static shared_pod_manager spm;
      return spm;
  }

  shared_pod_manager::~shared_pod_manager()
  {
  }

  void* shared_pod_manager::replace_if_equal(void* pod, std::size_t size)
  {
      if(pod == 0)
          return 0;

      const holder element(static_cast<char*>(pod), size);

      const storage::iterator found
          = std::lower_bound(m_storage.begin(), m_storage.end(), element, compare());

      if (found != m_storage.end() && pod == found->first)
      {
          // pod already in list => do nothing
          return pod;
      }
      else if (found != m_storage.end() && !compare()(element, *found))
      {
          // equal element in list => replace
          void* replacement = found->first;
          counted_pod_incref(found->first, size);   
          dec_ref(element.first, size); // invalidates iterator 'found'
          return replacement;
      }
      else
      {
          // new element => insert
          m_storage.insert(found, element);
          return pod;
      }
  }

  void* shared_pod_manager::make_unique_copy(void* pod, std::size_t size)
  {
      if(pod == 0)
          return 0;
      if(counted_pod_getref(static_cast<char*>(pod), size) == 1)
      {
          erase_from_list(pod);
          return pod;
      }
      else
      {
          void* copy = create(size);
          memmove(copy, pod, size);
          dec_ref(pod, size);
          return copy;
      }
  }

  void* shared_pod_manager::create(std::size_t size)
  {
      std::size_t total_size = pod_refcount_offset(size) + sizeof(pod_refcount);
      char* pod = static_cast<char*>(::operator new(total_size));
  #ifdef TYPE_OBJECT_BASE_STANDALONE_TEST
      ++pod_instance_counter;
  #endif
      memset(pod, 0, total_size);

      *counted_pod_refcount(pod, size) = 1;

      return pod;
  }

  void shared_pod_manager::dec_ref(void* pod, std::size_t size)
  {
      if(pod == 0)
          return;

      int ref_count = counted_pod_decref(static_cast<char*>(pod), size);
      
      if(ref_count <= 0) 
          erase_from_list(pod);
  }

  void shared_pod_manager::erase_from_list(void* pod)
  {
      if(pod == 0)
          return;

      const storage::iterator found =
          std::find_if(m_storage.begin(), m_storage.end(), 
          identical(static_cast<char*>(pod)));

      if(found != m_storage.end())
      {
          m_storage.erase(found);
      }
  }
} // namespace detail

namespace {
  struct error_type {
      operator PyObject*() const { return 0; }
      operator int() const { return -1; }
  };

  error_type unimplemented(const char* name)
  {
      assert(!"Control should never reach here");
      string s("Unimplemented ");
      s += string(name);
      PyErr_SetObject(PyExc_RuntimeError, s.get());
      return error_type();
  }
}

PyObject* type_object_base::instance_repr(PyObject*) const
{
    return unimplemented("instance_repr");
}

int type_object_base::instance_compare(PyObject*, PyObject*) const
{
    return unimplemented("instance_compare");
}

PyObject* type_object_base::instance_str(PyObject*) const
{
    return unimplemented("instance_str");
}

long type_object_base::instance_hash(PyObject* /* obj */) const
{
    return unimplemented("instance_hash");
}

PyObject* type_object_base::instance_call(PyObject* /*obj*/, PyObject* /*args*/, PyObject* /*kw*/) const
{
    return unimplemented("instance_call");
}

PyObject* type_object_base::instance_getattr(PyObject* /*obj*/, const char* /*name*/) const
{
    return unimplemented("instance_getattr");
}

int type_object_base::instance_setattr(PyObject* /*obj*/, const char* /*name*/, PyObject* /*value*/) const
{
    return unimplemented("instance_setattr");
}

int type_object_base::instance_mapping_length(PyObject*) const
{
    return unimplemented("instance_mapping_length");
}

int type_object_base::instance_sequence_length(PyObject*) const
{
    return unimplemented("instance_sequence_length");
}

PyObject* type_object_base::instance_mapping_subscript(PyObject*, PyObject*) const
{
    return unimplemented("instance_mapping_subscript");
}

PyObject* type_object_base::instance_sequence_item(PyObject*, int) const
{
    return unimplemented("instance_sequence_item");
}

int type_object_base::instance_mapping_ass_subscript(PyObject*, PyObject*, PyObject*) const
{
    return unimplemented("instance_mapping_ass_subscript");
}

int type_object_base::instance_sequence_ass_item(PyObject*, int, PyObject*) const
{
    return unimplemented("instance_sequence_ass_item");
}

PyObject* type_object_base::instance_sequence_concat(PyObject*, PyObject*) const
{
    return unimplemented("instance_sequence_concat");
}

PyObject* type_object_base::instance_sequence_repeat(PyObject*, int) const
{
    return unimplemented("instance_sequence_repeat");
}

PyObject* type_object_base::instance_sequence_slice(PyObject*, int, int) const
{
    return unimplemented("instance_sequence_slice");
}

int type_object_base::instance_sequence_ass_slice(PyObject*, int, int, PyObject*) const
{
    return unimplemented("instance_sequence_ass_slice");
}

PyObject* type_object_base::instance_number_add(PyObject*, PyObject*) const
{
    return unimplemented("instance_number_add");
}

PyObject* type_object_base::instance_number_subtract(PyObject*, PyObject*) const
{
    return unimplemented("instance_number_subtract");
}

PyObject* type_object_base::instance_number_multiply(PyObject*, PyObject*) const
{
    return unimplemented("instance_number_multiply");
}

PyObject* type_object_base::instance_number_divide(PyObject*, PyObject*) const
{
    return unimplemented("instance_number_divide");
}

PyObject* type_object_base::instance_number_remainder(PyObject*, PyObject*) const
{
    return unimplemented("instance_number_remainder");
}

PyObject* type_object_base::instance_number_divmod(PyObject*, PyObject*) const
{
    return unimplemented("instance_number_divmod");
}

PyObject* type_object_base::instance_number_power(PyObject*, PyObject*, PyObject*) const
{
    return unimplemented("instance_number_power");
}

PyObject* type_object_base::instance_number_negative(PyObject*) const
{
    return unimplemented("instance_number_negative");
}

PyObject* type_object_base::instance_number_positive(PyObject*) const
{
    return unimplemented("instance_number_positive");
}

PyObject* type_object_base::instance_number_absolute(PyObject*) const
{
    return unimplemented("instance_number_absolute");
}

int type_object_base::instance_number_nonzero(PyObject*) const
{
    return unimplemented("instance_number_nonzero");
}

PyObject* type_object_base::instance_number_invert(PyObject*) const
{
    return unimplemented("instance_number_invert");
}

PyObject* type_object_base::instance_number_lshift(PyObject*, PyObject*) const
{
    return unimplemented("instance_number_lshift");
}

PyObject* type_object_base::instance_number_rshift(PyObject*, PyObject*) const
{
    return unimplemented("instance_number_rshift");
}

PyObject* type_object_base::instance_number_and(PyObject*, PyObject*) const
{
    return unimplemented("instance_number_and");
}

PyObject* type_object_base::instance_number_xor(PyObject*, PyObject*) const
{
    return unimplemented("instance_number_xor");
}

PyObject* type_object_base::instance_number_or(PyObject*, PyObject*) const
{
    return unimplemented("instance_number_or");
}

int type_object_base::instance_number_coerce(PyObject*, PyObject**, PyObject**) const
{
    return unimplemented("instance_number_coerce");
}

PyObject* type_object_base::instance_number_int(PyObject*) const
{
    return unimplemented("instance_number_int");
}

PyObject* type_object_base::instance_number_long(PyObject*) const
{
    return unimplemented("instance_number_long");
}

PyObject* type_object_base::instance_number_float(PyObject*) const
{
    return unimplemented("instance_number_float");
}

PyObject* type_object_base::instance_number_oct(PyObject*) const
{
    return unimplemented("instance_number_oct");
}

PyObject* type_object_base::instance_number_hex(PyObject*) const
{
    return unimplemented("instance_number_hex");
}

PyObject* type_object_base::instance_number_inplace_add(PyObject*, PyObject*) const
{
    return unimplemented("instance_number_inplace_add");
}

PyObject* type_object_base::instance_number_inplace_subtract(PyObject*, PyObject*) const
{
    return unimplemented("instance_number_inplace_subtract");
}

PyObject* type_object_base::instance_number_inplace_multiply(PyObject*, PyObject*) const
{
    return unimplemented("instance_number_inplace_multiply");
}

PyObject* type_object_base::instance_number_inplace_divide(PyObject*, PyObject*) const
{
    return unimplemented("instance_number_inplace_divide");
}

PyObject* type_object_base::instance_number_inplace_remainder(PyObject*, PyObject*) const
{
    return unimplemented("instance_number_inplace_remainder");
}

PyObject* type_object_base::instance_number_inplace_power(PyObject*, PyObject*, PyObject*) const
{
    return unimplemented("instance_number_inplace_power");
}

PyObject* type_object_base::instance_number_inplace_lshift(PyObject*, PyObject*) const
{
    return unimplemented("instance_number_inplace_lshift");
}

PyObject* type_object_base::instance_number_inplace_rshift(PyObject*, PyObject*) const
{
    return unimplemented("instance_number_inplace_rshift");
}

PyObject* type_object_base::instance_number_inplace_and(PyObject*, PyObject*) const
{
    return unimplemented("instance_number_inplace_and");
}

PyObject* type_object_base::instance_number_inplace_or(PyObject*, PyObject*) const
{
    return unimplemented("instance_number_inplace_or");
}

PyObject* type_object_base::instance_number_inplace_xor(PyObject*, PyObject*) const
{
    return unimplemented("instance_number_inplace_xor");
}

PyObject* type_object_base::instance_lt(PyObject*, PyObject*) const
{
    return unimplemented("instance_lt");
}

PyObject* type_object_base::instance_le(PyObject*, PyObject*) const
{
    return unimplemented("instance_le");
}

PyObject* type_object_base::instance_eq(PyObject*, PyObject*) const
{
    return unimplemented("instance_eq");
}

PyObject* type_object_base::instance_ne(PyObject*, PyObject*) const
{
    return unimplemented("instance_ne");
}

PyObject* type_object_base::instance_gt(PyObject*, PyObject*) const
{
    return unimplemented("instance_gt");
}

PyObject* type_object_base::instance_ge(PyObject*, PyObject*) const
{
    return unimplemented("instance_ge");
}

}} // namespace boost::python

#ifdef TYPE_OBJECT_BASE_STANDALONE_TEST

struct TestTypeObject : boost::python::type_object_base
{
    TestTypeObject()
    : boost::python::type_object_base(Py_None->ob_type->ob_type)
    {}
    
    void instance_dealloc(PyObject*) const {}
};

struct POD1
{
    unsigned char data;
};

int main()
{
    boost::python::type_object_base *o1, *o2, *o3;
    
//    POD1 * pod1;
//    boost::python::detail::shared_pod_manager::create(pod1);
    
    o1 = new TestTypeObject;
    o2 = new TestTypeObject;
    o3 = new TestTypeObject;
    
    assert(boost::python::pod_instance_counter == 0);
    
    o1->enable(boost::python::type_object_base::number_add);
    o1->enable(boost::python::type_object_base::compare);

    o2->enable(boost::python::type_object_base::number_add);
    o2->enable(boost::python::type_object_base::mapping_length);
    
    o3->enable(boost::python::type_object_base::number_add);
    o3->enable(boost::python::type_object_base::sequence_length);

    assert(boost::python::pod_instance_counter == 3);
    assert(o1->tp_as_number && !o1->tp_as_mapping && !o1->tp_as_sequence);
    assert(o2->tp_as_number && o2->tp_as_mapping && !o2->tp_as_sequence);
    assert(o3->tp_as_number && !o3->tp_as_mapping && o3->tp_as_sequence);
    assert(o1->tp_as_number == o2->tp_as_number);
    assert(o1->tp_as_number == o3->tp_as_number);
    assert((void*)o2->tp_as_number != o2->tp_as_mapping);
    assert((void*)o2->tp_as_mapping != o3->tp_as_sequence);
    
    o1->enable(boost::python::type_object_base::number_subtract);
    
    assert(boost::python::pod_instance_counter == 4);
    assert(o1->tp_as_number != o2->tp_as_number);
    assert(o2->tp_as_number == o3->tp_as_number);
    
    o3->enable(boost::python::type_object_base::mapping_subscript);

    assert(boost::python::pod_instance_counter == 5);
    assert(o3->tp_as_number && o3->tp_as_mapping && o3->tp_as_sequence);
    assert(o2->tp_as_mapping != o3->tp_as_mapping);
    
    o2->enable(boost::python::type_object_base::mapping_subscript);
    o3->enable(boost::python::type_object_base::mapping_length);

    assert(boost::python::pod_instance_counter == 4);
    assert(o2->tp_as_number && o2->tp_as_mapping && !o2->tp_as_sequence);
    assert(o3->tp_as_number && o3->tp_as_mapping && o3->tp_as_sequence);
    assert(o2->tp_as_mapping == o3->tp_as_mapping);
    
    boost::python::type_object_base *o4 = new TestTypeObject;

    assert(boost::python::pod_instance_counter == 4);

    o4->enable(boost::python::type_object_base::number_add);

    assert(boost::python::pod_instance_counter == 4);
    assert(o4->tp_as_number && !o4->tp_as_mapping && !o4->tp_as_sequence);
    assert(o4->tp_as_number == o3->tp_as_number);
    
    delete o3;

    assert(boost::python::pod_instance_counter == 3);
    assert(o1->tp_as_number && !o1->tp_as_mapping && !o1->tp_as_sequence);
    assert(o2->tp_as_number && o2->tp_as_mapping && !o2->tp_as_sequence);
    assert(o4->tp_as_number && !o4->tp_as_mapping && !o4->tp_as_sequence);
    assert(o4->tp_as_number == o2->tp_as_number);
    
    o3 =  new TestTypeObject;
    
    assert(boost::python::pod_instance_counter == 3);

    o3->enable(boost::python::type_object_base::number_add);
    o3->enable(boost::python::type_object_base::sequence_length);

    assert(boost::python::pod_instance_counter == 4);
    assert(o3->tp_as_number && !o3->tp_as_mapping && o3->tp_as_sequence);
    assert(o1->tp_as_number != o3->tp_as_number);
    assert(o2->tp_as_number == o3->tp_as_number);
    
    delete o1;
    
    assert(boost::python::pod_instance_counter == 3);
    
    delete o4;
    
    assert(boost::python::pod_instance_counter == 3);
    
    delete o3;
    
    assert(boost::python::pod_instance_counter == 2);
    
    delete o2;
    
    assert(boost::python::pod_instance_counter == 0);
    
    assert(boost::python::detail::shared_pod_manager::obj().m_storage.size() == 0);
}

#endif
