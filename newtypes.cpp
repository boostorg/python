//  (C) Copyright David Abrahams 2000. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
//  The author gratefully acknowleges the support of Dragon Systems, Inc., in
//  producing this work.

#include "newtypes.h"
#include "pyptr.h" // for handle_exception()
#include "module.h"
#include "none.h"
#include <cstring>
#include <vector>
#include <cstddef>
#include <stdexcept>
#include <boost/smart_ptr.hpp>
#include "objects.h"

namespace py {

namespace {

PyObject* call(PyObject* instance, PyObject* (TypeObjectBase::*f)(PyObject*) const)
{
    try
    {
        return (static_cast<TypeObjectBase*>(instance->ob_type)->*f)(instance);
    }
    catch(...)
    {
        handle_exception();
        return 0;
    }
}

// Naming this differently allows us to use it for functions returning long on
// compilers without partial ordering
template <class R>
R int_call(PyObject* instance, R (TypeObjectBase::*f)(PyObject*) const)
{
    try
    {
        return (static_cast<TypeObjectBase*>(instance->ob_type)->*f)(instance);
    }
    catch(...)
    {
        handle_exception();
        return -1;
    }
}

// Implemented in terms of int_call, above
int call(PyObject* instance, int (TypeObjectBase::*f)(PyObject*) const)
{
    return int_call(instance, f);
}

template <class A1>
PyObject* call(PyObject* instance, PyObject* (TypeObjectBase::*f)(PyObject*, A1) const, A1 a1)
{
    try
    {
        return (static_cast<TypeObjectBase*>(instance->ob_type)->*f)(instance, a1);
    }
    catch(...)
    {
        handle_exception();
        return 0;
    }
}

template <class A1>
int call(PyObject* instance, int (TypeObjectBase::*f)(PyObject*, A1) const, A1 a1)
{
    try
    {
        return (static_cast<TypeObjectBase*>(instance->ob_type)->*f)(instance, a1);
    }
    catch(...)
    {
        handle_exception();
        return -1;
    }
}

template <class A1, class A2>
PyObject* call(PyObject* instance, PyObject* (TypeObjectBase::*f)(PyObject*, A1, A2) const, A1 a1, A2 a2)
{
    try
    {
        return (static_cast<TypeObjectBase*>(instance->ob_type)->*f)(instance, a1, a2);
    }
    catch(...)
    {
        handle_exception();
        return 0;
    }
}
    
template <class A1, class A2>
int call(PyObject* instance, int (TypeObjectBase::*f)(PyObject*, A1, A2) const, A1 a1, A2 a2)
{
    try
    {
        return (static_cast<TypeObjectBase*>(instance->ob_type)->*f)(instance, a1, a2);
    }
    catch(...)
    {
        handle_exception();
        return -1;
    }
}
    
template <class A1, class A2, class A3>
int call(PyObject* instance, int (TypeObjectBase::*f)(PyObject*, A1, A2, A3) const, A1 a1, A2 a2, A3 a3)
{
    try
    {
        return (static_cast<TypeObjectBase*>(instance->ob_type)->*f)(instance, a1, a2, a3);
    }
    catch(...)
    {
        handle_exception();
        return -1;
    }
}

int call_length_function(PyObject* instance, int (TypeObjectBase::*f)(PyObject*) const)
{
    try
    {
        const int outcome =
            (static_cast<TypeObjectBase*>(instance->ob_type)->*f)(instance);
        
        if (outcome < 0)
        {
            PyErr_SetString(PyExc_ValueError, "__len__() should return >= 0");
            return -1;
        }
        return outcome;
    }
    catch(...)
    {
        handle_exception();
        return -1;
    }
}

}  // anonymous namespace

extern "C" {

static PyObject* do_instance_repr(PyObject* instance)
{
    return call(instance, &TypeObjectBase::instance_repr);
}

static int do_instance_compare(PyObject* instance, PyObject* other)
{
    return call(instance, &TypeObjectBase::instance_compare, other);
}

static PyObject* do_instance_str(PyObject* instance)
{
    return call(instance, &TypeObjectBase::instance_str);
}

static long do_instance_hash(PyObject* instance)
{
    return int_call(instance, &TypeObjectBase::instance_hash);
}
    
static PyObject* do_instance_call(PyObject* instance, PyObject* args, PyObject* keywords)
{
    return call(instance, &TypeObjectBase::instance_call, args, keywords);
}

static void do_instance_dealloc(PyObject* instance)
{
    try
    {
        static_cast<TypeObjectBase*>(instance->ob_type)
            ->instance_dealloc(instance);
    }
    catch(...)
    {
        assert(!"exception during destruction!");
        handle_exception();
    }
}

static PyObject* do_instance_getattr(PyObject* instance, char* name)
{
    const char* name_ = name;
    return call(instance, &TypeObjectBase::instance_getattr, name_);
}

static int do_instance_setattr(PyObject* instance, char* name, PyObject* value)
{
    const char* name_ = name;
    return call(instance, &TypeObjectBase::instance_setattr, name_, value);
}

static int do_instance_mp_length(PyObject* instance)
{
    return call_length_function(instance, &TypeObjectBase::instance_mapping_length);
}

static int do_instance_sq_length(PyObject* instance)
{
    return call_length_function(instance, &TypeObjectBase::instance_sequence_length);
}

static PyObject* do_instance_mp_subscript(PyObject* instance, PyObject* index)
{
    return call(instance, &TypeObjectBase::instance_mapping_subscript, index);
}

static PyObject* do_instance_sq_item(PyObject* instance, int index)
{
    try
    {
        const PyTypeObject* const type = instance->ob_type;
        
        // This is an extension to standard class behavior. If sequence_length
        // is implemented and n >= sequence_length(), raise an IndexError. That
        // keeps users from having to worry about raising it themselves
        if (type->tp_as_sequence != 0 && type->tp_as_sequence->sq_length != 0
            && index >= type->tp_as_sequence->sq_length(instance))
        {
            PyErr_SetString(PyExc_IndexError, type->tp_name);
            return 0;
        }
    
        return static_cast<TypeObjectBase*>(instance->ob_type)
            ->instance_sequence_item(instance, index);
    }
    catch(...)
    {
        handle_exception();
        return 0;
    }
}

static int do_instance_mp_ass_subscript(PyObject* instance, PyObject* index, PyObject* value)
{
    return call(instance, &TypeObjectBase::instance_mapping_ass_subscript, index, value);
}

static int do_instance_sq_ass_item(PyObject* instance, int index, PyObject* value)
{
    return call(instance, &TypeObjectBase::instance_sequence_ass_item, index, value);
}

static PyObject* do_instance_sq_concat(PyObject* instance, PyObject* other)
{
    return call(instance, &TypeObjectBase::instance_sequence_concat, other);
}

static PyObject* do_instance_sq_repeat(PyObject* instance, int n)
{
    return call(instance, &TypeObjectBase::instance_sequence_repeat, n);
}

static PyObject* do_instance_sq_slice(
    PyObject* instance, int start, int finish)
{
    return call(instance, &TypeObjectBase::instance_sequence_slice, start, finish);
}

static int do_instance_sq_ass_slice(
    PyObject* instance, int start, int finish, PyObject* value)
{
    return call(instance, &TypeObjectBase::instance_sequence_ass_slice, start, finish, value);
}

static PyObject* do_instance_nb_add(PyObject* instance, PyObject* other)
{
    return call(instance, &TypeObjectBase::instance_number_add, other);
}

static PyObject* do_instance_nb_subtract(PyObject* instance, PyObject* other)
{
    return call(instance, &TypeObjectBase::instance_number_subtract, other);
}

static PyObject* do_instance_nb_multiply(PyObject* instance, PyObject* other)
{
    return call(instance, &TypeObjectBase::instance_number_multiply, other);
}

static PyObject* do_instance_nb_divide(PyObject* instance, PyObject* other)
{
    return call(instance, &TypeObjectBase::instance_number_divide, other);
}

static PyObject* do_instance_nb_remainder(PyObject* instance, PyObject* other)
{
    return call(instance, &TypeObjectBase::instance_number_remainder, other);
}

static PyObject* do_instance_nb_divmod(PyObject* instance, PyObject* other)
{
    return call(instance, &TypeObjectBase::instance_number_divmod, other);
}

static PyObject* do_instance_nb_power(PyObject* instance, PyObject* exponent, PyObject* modulus)
{
    return call(instance, &TypeObjectBase::instance_number_power, exponent, modulus);
}

static PyObject* do_instance_nb_negative(PyObject* instance)
{
    return call(instance, &TypeObjectBase::instance_number_negative);
}

static PyObject* do_instance_nb_positive(PyObject* instance)
{
    return call(instance, &TypeObjectBase::instance_number_positive);
}

static PyObject* do_instance_nb_absolute(PyObject* instance)
{
    return call(instance, &TypeObjectBase::instance_number_absolute);
}

static int do_instance_nb_nonzero(PyObject* instance)
{
    return call(instance, &TypeObjectBase::instance_number_nonzero);
}

static PyObject* do_instance_nb_invert(PyObject* instance)
{
    return call(instance, &TypeObjectBase::instance_number_invert);
}

    
static PyObject* do_instance_nb_lshift(PyObject* instance, PyObject* other)
{
    return call(instance, &TypeObjectBase::instance_number_lshift, other);
}

static PyObject* do_instance_nb_rshift(PyObject* instance, PyObject* other)
{
    return call(instance, &TypeObjectBase::instance_number_rshift, other);
}

static PyObject* do_instance_nb_and(PyObject* instance, PyObject* other)
{
    return call(instance, &TypeObjectBase::instance_number_and, other);
}

static PyObject* do_instance_nb_xor(PyObject* instance, PyObject* other)
{
    return call(instance, &TypeObjectBase::instance_number_xor, other);
}

static PyObject* do_instance_nb_or(PyObject* instance, PyObject* other)
{
    return call(instance, &TypeObjectBase::instance_number_or, other);
}

static int do_instance_nb_coerce(PyObject**instance, PyObject**other)
{
    return call(*instance, &TypeObjectBase::instance_number_coerce, instance, other);
}
static PyObject* do_instance_nb_int(PyObject* instance)
{
    return call(instance, &TypeObjectBase::instance_number_int);
}

static PyObject* do_instance_nb_long(PyObject* instance)
{
    return call(instance, &TypeObjectBase::instance_number_long);
}

static PyObject* do_instance_nb_float(PyObject* instance)
{
    return call(instance, &TypeObjectBase::instance_number_float);
}

static PyObject* do_instance_nb_oct(PyObject* instance)
{
    return call(instance, &TypeObjectBase::instance_number_oct);
}

static PyObject* do_instance_nb_hex(PyObject* instance)
{
    return call(instance, &TypeObjectBase::instance_number_hex);
}

} // extern "C"

namespace
{

#define ENABLE_GENERAL_CAPABILITY(field) \
    case TypeObjectBase::field: \
        dest->tp_##field = &do_instance_##field; \
        break

bool add_capability_general(TypeObjectBase::Capability capability, PyTypeObject* dest)
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
    return true;
}

template <class T>
void create_method_table_if_null(T *& table)
{
    if(table == 0)
    {
        table = new T;
        memset(table, 0, sizeof(T));
    }
}

#define ENABLE_MAPPING_CAPABILITY(field) \
    case TypeObjectBase::mapping_##field: \
        create_method_table_if_null(dest); \
        dest->mp_##field = &do_instance_mp_##field; \
        break

bool add_capability_mapping(TypeObjectBase::Capability capability, PyMappingMethods*& dest)
{
    switch(capability)
    {
        ENABLE_MAPPING_CAPABILITY(length);
        ENABLE_MAPPING_CAPABILITY(subscript);
        ENABLE_MAPPING_CAPABILITY(ass_subscript);
        default:
            return false;
    }
    return true;
}

#define ENABLE_SEQUENCE_CAPABILITY(field) \
    case TypeObjectBase::sequence_##field: \
        create_method_table_if_null(dest); \
        dest->sq_##field = &do_instance_sq_##field; \
        break

bool add_capability_sequence(TypeObjectBase::Capability capability, PySequenceMethods*& dest)
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
    return true;
}

#define ENABLE_NUMBER_CAPABILITY(field) \
    case TypeObjectBase::number_##field: \
        create_method_table_if_null(dest); \
        dest->nb_##field = &do_instance_nb_##field; \
        break

bool add_capability_number(TypeObjectBase::Capability capability, PyNumberMethods*& dest)
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
    return true;
}

#define ENABLE_BUFFER_CAPABILITY(field) \
    case TypeObjectBase::buffer_##field: \
        create_method_table_if_null(dest); \
        dest->bf_##field = &do_instance_bf_##field; \
        break

bool add_capability_buffer(TypeObjectBase::Capability capability, PyBufferProcs*& dest)
{
    switch(capability)
    {
        // nothing defined yet
        
        default:
            return false;
    }
    return true;
}

} // anonymous namespace

namespace detail  {

  void add_capability(
      TypeObjectBase::Capability capability,
      PyTypeObject* dest_)
  {
    if(add_capability_general(capability, dest_))
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

void TypeObjectBase::enable(TypeObjectBase::Capability capability)
{
    detail::add_capability(capability, this);
}

TypeObjectBase::TypeObjectBase(PyTypeObject* t)
    : PythonType(t)
{
    this->tp_dealloc = do_instance_dealloc;
}

namespace {
  struct ErrorType {
      operator PyObject*() const { return 0; }
      operator int() const { return -1; }
  };

  ErrorType unimplemented(const char* name)
  {
      assert(!"Control should never reach here");
      String s("Unimplemented ");
      s += String(name);
      PyErr_SetObject(PyExc_RuntimeError, s.get());
      return ErrorType();
  }
}

PyObject* TypeObjectBase::instance_repr(PyObject*) const
{
    return unimplemented("instance_repr");
}

int TypeObjectBase::instance_compare(PyObject*, PyObject*) const
{
    return unimplemented("instance_compare");
}

PyObject* TypeObjectBase::instance_str(PyObject*) const
{
    return unimplemented("instance_str");
}

long TypeObjectBase::instance_hash(PyObject* /* instance */) const
{
    return unimplemented("instance_hash");
}

PyObject* TypeObjectBase::instance_call(PyObject* /*instance*/, PyObject* /*args*/, PyObject* /*kw*/) const
{
    return unimplemented("instance_call");
}

PyObject* TypeObjectBase::instance_getattr(PyObject* /*instance*/, const char* /*name*/) const
{
    return unimplemented("instance_getattr");
}

int TypeObjectBase::instance_setattr(PyObject* /*instance*/, const char* /*name*/, PyObject* /*value*/) const
{
    return unimplemented("instance_setattr");
}

int TypeObjectBase::instance_mapping_length(PyObject*) const
{
    return unimplemented("instance_mapping_length");
}

int TypeObjectBase::instance_sequence_length(PyObject*) const
{
    return unimplemented("instance_sequence_length");
}

PyObject* TypeObjectBase::instance_mapping_subscript(PyObject*, PyObject*) const
{
    return unimplemented("instance_mapping_subscript");
}

PyObject* TypeObjectBase::instance_sequence_item(PyObject*, int) const
{
    return unimplemented("instance_sequence_item");
}

int TypeObjectBase::instance_mapping_ass_subscript(PyObject*, PyObject*, PyObject*) const
{
    return unimplemented("instance_mapping_ass_subscript");
}

int TypeObjectBase::instance_sequence_ass_item(PyObject*, int, PyObject*) const
{
    return unimplemented("instance_sequence_ass_item");
}

PyObject* TypeObjectBase::instance_sequence_concat(PyObject*, PyObject*) const
{
    return unimplemented("instance_sequence_concat");
}

PyObject* TypeObjectBase::instance_sequence_repeat(PyObject*, int) const
{
    return unimplemented("instance_sequence_repeat");
}

PyObject* TypeObjectBase::instance_sequence_slice(PyObject*, int, int) const
{
    return unimplemented("instance_sequence_slice");
}

int TypeObjectBase::instance_sequence_ass_slice(PyObject*, int, int, PyObject*) const
{
    return unimplemented("instance_sequence_ass_slice");
}

PyObject* TypeObjectBase::instance_number_add(PyObject*, PyObject*) const
{
    return unimplemented("instance_number_add");
}

PyObject* TypeObjectBase::instance_number_subtract(PyObject*, PyObject*) const
{
    return unimplemented("instance_number_subtract");
}

PyObject* TypeObjectBase::instance_number_multiply(PyObject*, PyObject*) const
{
    return unimplemented("instance_number_multiply");
}

PyObject* TypeObjectBase::instance_number_divide(PyObject*, PyObject*) const
{
    return unimplemented("instance_number_divide");
}

PyObject* TypeObjectBase::instance_number_remainder(PyObject*, PyObject*) const
{
    return unimplemented("instance_number_remainder");
}

PyObject* TypeObjectBase::instance_number_divmod(PyObject*, PyObject*) const
{
    return unimplemented("instance_number_divmod");
}

PyObject* TypeObjectBase::instance_number_power(PyObject*, PyObject*, PyObject*) const
{
    return unimplemented("instance_number_divmod");
}

PyObject* TypeObjectBase::instance_number_negative(PyObject*) const
{
    return unimplemented("instance_number_negative");
}

PyObject* TypeObjectBase::instance_number_positive(PyObject*) const
{
    return unimplemented("instance_number_positive");
}

PyObject* TypeObjectBase::instance_number_absolute(PyObject*) const
{
    return unimplemented("instance_number_absolute");
}

int TypeObjectBase::instance_number_nonzero(PyObject*) const
{
    return unimplemented("instance_number_nonzero");
}

PyObject* TypeObjectBase::instance_number_invert(PyObject*) const
{
    return unimplemented("instance_number_invert");
}

PyObject* TypeObjectBase::instance_number_lshift(PyObject*, PyObject*) const
{
    return unimplemented("instance_number_lshift");
}

PyObject* TypeObjectBase::instance_number_rshift(PyObject*, PyObject*) const
{
    return unimplemented("instance_number_rshift");
}

PyObject* TypeObjectBase::instance_number_and(PyObject*, PyObject*) const
{
    return unimplemented("instance_number_and");
}

PyObject* TypeObjectBase::instance_number_xor(PyObject*, PyObject*) const
{
    return unimplemented("instance_number_xor");
}

PyObject* TypeObjectBase::instance_number_or(PyObject*, PyObject*) const
{
    return unimplemented("instance_number_or");
}

int TypeObjectBase::instance_number_coerce(PyObject*, PyObject**, PyObject**) const
{
    return unimplemented("instance_number_coerce");
}

PyObject* TypeObjectBase::instance_number_int(PyObject*) const
{
    return unimplemented("instance_number_int");
}

PyObject* TypeObjectBase::instance_number_long(PyObject*) const
{
    return unimplemented("instance_number_long");
}

PyObject* TypeObjectBase::instance_number_float(PyObject*) const
{
    return unimplemented("instance_number_float");
}

PyObject* TypeObjectBase::instance_number_oct(PyObject*) const
{
    return unimplemented("instance_number_oct");
}

PyObject* TypeObjectBase::instance_number_hex(PyObject*) const
{
    return unimplemented("instance_number_hex");
}

TypeObjectBase::~TypeObjectBase()
{
    delete tp_as_mapping;
    delete tp_as_sequence;
    delete tp_as_number;
    delete tp_as_buffer;
}

}
