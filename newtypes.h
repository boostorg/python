//  (C) Copyright David Abrahams 2000. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
//  The author gratefully acknowleges the support of Dragon Systems, Inc., in
//  producing this work.

#ifndef TYPES_DWA051800_H_
# define TYPES_DWA051800_H_

//  Usage:
//  class X : public
//          py::Callable<
//          py::Getattrable <
//          py::Setattrable<PythonObject, X> > >
//  {
//  public:
//      Ptr call(args, kw);
//      Ptr getattr(args, kw);
//      Ptr setattr(args, kw);
//  };

# include "pyconfig.h"
# include "signatures.h" // really just for Type<>
# include "cast.h"
# include "base_object.h"
# include <typeinfo>
# include <vector>
# include <cassert>

namespace py {

class String;
class InstanceHolderBase;

class TypeObjectBase : public PythonType
{
 public:
    explicit TypeObjectBase(PyTypeObject* type_type);
    virtual ~TypeObjectBase();

 public:
    enum Capability
    {
        hash, call, str, getattr, setattr, compare, repr,
        mapping_length, mapping_subscript, mapping_ass_subscript,
        sequence_length, sequence_item, sequence_ass_item,
        sequence_concat, sequence_repeat, sequence_slice, sequence_ass_slice,

        number_add, number_subtract, number_multiply, number_divide,
        number_remainder, number_divmod, number_power, number_negative,
        number_positive, number_absolute, number_nonzero, number_invert,
        number_lshift, number_rshift, number_and, number_xor, number_or,
        number_coerce, number_int, number_long, number_float, number_oct,
        number_hex
    };
    
    void enable(Capability);
    
    //
    // Type behaviors
    //
 public: // Callbacks for basic type functionality.
    virtual PyObject* instance_repr(PyObject*) const;
    virtual int instance_compare(PyObject*, PyObject* other) const;
    virtual PyObject* instance_str(PyObject*) const;
    virtual long instance_hash(PyObject*) const;
    virtual PyObject* instance_call(PyObject* instance, PyObject* args, PyObject* kw) const;
    virtual PyObject* instance_getattr(PyObject* instance, const char* name) const;
    virtual int instance_setattr(PyObject* instance, const char* name, PyObject* value) const;

    // Dealloc is a special case, since every type needs a nonzero tp_dealloc slot.
    virtual void instance_dealloc(PyObject*) const = 0;

 public: // Callbacks for mapping methods
    virtual int instance_mapping_length(PyObject*) const;
    virtual PyObject* instance_mapping_subscript(PyObject*, PyObject*) const ;
    virtual int instance_mapping_ass_subscript(PyObject*, PyObject*, PyObject*) const;

 public: // Callbacks for sequence methods
    virtual int instance_sequence_length(PyObject* instance) const;
    virtual PyObject* instance_sequence_concat(PyObject* instance, PyObject* other) const;
    virtual PyObject* instance_sequence_repeat(PyObject* instance, int n) const;
    virtual PyObject* instance_sequence_item(PyObject* instance, int n) const;
    virtual PyObject* instance_sequence_slice(PyObject* instance, int start, int finish) const;
    virtual int instance_sequence_ass_item(PyObject* instance, int n, PyObject* value) const;
    virtual int instance_sequence_ass_slice(PyObject* instance, int start, int finish, PyObject* value) const;
    
 public: // Callbacks for number methods
    virtual PyObject* instance_number_add(PyObject*, PyObject*) const;
    virtual PyObject* instance_number_subtract(PyObject*, PyObject*) const;
    virtual PyObject* instance_number_multiply(PyObject*, PyObject*) const;
    virtual PyObject* instance_number_divide(PyObject*, PyObject*) const;
    virtual PyObject* instance_number_remainder(PyObject*, PyObject*) const;
    virtual PyObject* instance_number_divmod(PyObject*, PyObject*) const;
    virtual PyObject* instance_number_power(PyObject*, PyObject*, PyObject*) const;
    virtual PyObject* instance_number_negative(PyObject*) const;
    virtual PyObject* instance_number_positive(PyObject*) const;
    virtual PyObject* instance_number_absolute(PyObject*) const;
    virtual int instance_number_nonzero(PyObject*) const;
    virtual PyObject* instance_number_invert(PyObject*) const;
    virtual PyObject* instance_number_lshift(PyObject*, PyObject*) const;
    virtual PyObject* instance_number_rshift(PyObject*, PyObject*) const;
    virtual PyObject* instance_number_and(PyObject*, PyObject*) const;
    virtual PyObject* instance_number_xor(PyObject*, PyObject*) const;
    virtual PyObject* instance_number_or(PyObject*, PyObject*) const;
    virtual int instance_number_coerce(PyObject*, PyObject**, PyObject**) const;
    virtual PyObject* instance_number_int(PyObject*) const;
    virtual PyObject* instance_number_long(PyObject*) const;
    virtual PyObject* instance_number_float(PyObject*) const;
    virtual PyObject* instance_number_oct(PyObject*) const;
    virtual PyObject* instance_number_hex(PyObject*) const;
};

template <class T>
class TypeObject : public TypeObjectBase
{
 public:
    typedef T Instance;

    TypeObject(PyTypeObject* type_type, const char* name)
        : Base(type_type)
    {
        assert(name != 0);
        this->tp_name = const_cast<char*>(name);
    }

    TypeObject(PyTypeObject* type_type)
        : Base(type_type)
    {
        this->tp_name = const_cast<char*>(typeid(Instance).name());
    }

 private: // Overridable behaviors.
    // Called when the reference count goes to zero. The default implementation
    // is "delete p". If you have not allocated your object with operator new or
    // you have other constraints, you'll need to override this
    virtual void dealloc(T* p) const;
    
 private: // Implementation of TypeObjectBase hooks. Do not reimplement in derived classes.
    void instance_dealloc(PyObject*) const;
};

//
// Type objects
//
template <class Base>
class Callable : public Base
{
 public:
    typedef Callable Properties; // Convenience for derived class construction
    typedef typename Base::Instance Instance;
    Callable(PyTypeObject* type_type, const char* name);
    Callable(PyTypeObject* type_type);
 private:
    PyObject* instance_call(PyObject* instance, PyObject* args, PyObject* kw) const;
};

template <class Base>
class Getattrable : public Base
{
 public:
    typedef Getattrable Properties; // Convenience for derived class construction
    typedef typename Base::Instance Instance;
    Getattrable(PyTypeObject* type_type, const char* name);
    Getattrable(PyTypeObject* type_type);
 private:
    PyObject* instance_getattr(PyObject* instance, const char* name) const;
};

template <class Base>
class Setattrable : public Base
{
 public:
    typedef Setattrable Properties; // Convenience for derived class construction
    typedef typename Base::Instance Instance;
    Setattrable(PyTypeObject* type_type, const char* name);
    Setattrable(PyTypeObject* type_type);
 private:
    int instance_setattr(PyObject* instance, const char* name, PyObject* value) const;
};

//
// Member function definitions
//

// TypeObject<>
template <class T>
void TypeObject<T>::instance_dealloc(PyObject* instance) const
{
    this->dealloc(Downcast<Instance>(instance).get());
}

template <class T>
void TypeObject<T>::dealloc(T* instance) const
{
    delete instance;
}

// Callable
template <class Base>
Callable<Base>::Callable(PyTypeObject* type_type, const char* name)
    : Base(type_type, name)
{
    this->enable(call);
}
        
template <class Base>
Callable<Base>::Callable(PyTypeObject* type_type)
    : Base(type_type)
{
    this->enable(call);
}
        
template <class Base>
PyObject* Callable<Base>::instance_call(PyObject* instance, PyObject* args, PyObject* kw) const
{
    return Downcast<Instance>(instance)->call(args, kw);
}

// Getattrable
template <class Base>
Getattrable<Base>::Getattrable(PyTypeObject* type_type, const char* name)
    : Base(type_type, name)
{
    this->enable(getattr);
}
        
template <class Base>
Getattrable<Base>::Getattrable(PyTypeObject* type_type)
    : Base(type_type)
{
    this->enable(getattr);
}
        
template <class Base>
PyObject* Getattrable<Base>::instance_getattr(PyObject* instance, const char* name) const
{
    return Downcast<Instance>(instance)->getattr(name);
}

// Setattrable
template <class Base>
Setattrable<Base>::Setattrable(PyTypeObject* type_type, const char* name)
    : Base(type_type, name)
{
    this->enable(setattr);
}
        
template <class Base>
Setattrable<Base>::Setattrable(PyTypeObject* type_type)
    : Base(type_type)
{
    this->enable(setattr);
}
        
template <class Base>
int Setattrable<Base>::instance_setattr(PyObject* instance, const char* name, PyObject* value) const
{
    return Downcast<Instance>(instance)->setattr(name, value);
}

namespace detail {

  struct AllMethods {
      PyMappingMethods mapping;
      PySequenceMethods sequence;
      PyNumberMethods number;
      PyBufferProcs buffer;
  };

  typedef void (*Dispatch)();
  struct CapabilityEntry
  {
      std::size_t offset1;
      std::size_t offset2;
      Dispatch dispatch;
      std::size_t substructure_size;
      int allmethods_offset;
  };

  extern const CapabilityEntry capabilities[];
  extern const std::size_t num_capabilities;

  void add_capability(std::size_t index, PyTypeObject* dest, AllMethods&);

  class UniquePodSet
  {
      typedef std::pair<const char*, const char*> Holder;
      typedef std::vector<Holder> Storage;
   public:
      static UniquePodSet& instance();
      ~UniquePodSet();

      template <class T>
      T* get(const T& x)
      {
          char* base = const_cast<char*>(
              reinterpret_cast<const char*>(&x));
          return const_cast<T*>(
              static_cast<const T*>(
              get_element(base, sizeof(T))));
      }

      const void* get_element(const void* buffer, std::size_t size);

   private:
      struct Compare;

   private:
      UniquePodSet() {} // singleton

   private:
      Storage m_storage;
  };

# define PY_ARRAY_LENGTH(a) \
        (sizeof(::py::detail::countof_validate(a, &(a))) ? sizeof(a) / sizeof((a)[0]) : 0)

  template<typename T>
  inline void countof_validate(T* const, T* const*);

  template<typename T>
  inline int countof_validate(const void*, T);
}

}

#endif // TYPES_DWA051800_H_
