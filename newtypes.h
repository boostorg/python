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
//          python::callable<
//          python::getattrable <
//          python::setattrable<python_object, X> > >
//  {
//  public:
//      ref call(args, kw);
//      ref getattr(args, kw);
//      ref setattr(args, kw);
//  };

# include "pyconfig.h"
# include "signatures.h" // really just for type<>
# include "cast.h"
# include "base_object.h"
# include <typeinfo>
# include <vector>
# include <cassert>

namespace python {

class string;

namespace detail {

class instance_holder_base;

class type_object_base : public python_type
{
 public:
    explicit type_object_base(PyTypeObject* type_type);
    virtual ~type_object_base();

 public:
    enum capability {
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
    
    void enable(capability);
    
    //
    // type behaviors
    //
 public: // Callbacks for basic type functionality.
    virtual PyObject* instance_repr(PyObject*) const;
    virtual int instance_compare(PyObject*, PyObject* other) const;
    virtual PyObject* instance_str(PyObject*) const;
    virtual long instance_hash(PyObject*) const;
    virtual PyObject* instance_call(PyObject* obj, PyObject* args, PyObject* kw) const;
    virtual PyObject* instance_getattr(PyObject* obj, const char* name) const;
    virtual int instance_setattr(PyObject* obj, const char* name, PyObject* value) const;

    // Dealloc is a special case, since every type needs a nonzero tp_dealloc slot.
    virtual void instance_dealloc(PyObject*) const = 0;

 public: // Callbacks for mapping methods
    virtual int instance_mapping_length(PyObject*) const;
    virtual PyObject* instance_mapping_subscript(PyObject*, PyObject*) const ;
    virtual int instance_mapping_ass_subscript(PyObject*, PyObject*, PyObject*) const;

 public: // Callbacks for sequence methods
    virtual int instance_sequence_length(PyObject* obj) const;
    virtual PyObject* instance_sequence_concat(PyObject* obj, PyObject* other) const;
    virtual PyObject* instance_sequence_repeat(PyObject* obj, int n) const;
    virtual PyObject* instance_sequence_item(PyObject* obj, int n) const;
    virtual PyObject* instance_sequence_slice(PyObject* obj, int start, int finish) const;
    virtual int instance_sequence_ass_item(PyObject* obj, int n, PyObject* value) const;
    virtual int instance_sequence_ass_slice(PyObject* obj, int start, int finish, PyObject* value) const;
    
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
class type_object : public type_object_base
{
 public:
    typedef T instance;

    type_object(PyTypeObject* type_type, const char* name)
        : type_object_base(type_type)
    {
        assert(name != 0);
        this->tp_name = const_cast<char*>(name);
    }

    type_object(PyTypeObject* type_type)
        : type_object_base(type_type)
    {
        this->tp_name = const_cast<char*>(typeid(instance).name());
    }

 private: // Overridable behaviors.
    // Called when the reference count goes to zero. The default implementation
    // is "delete p". If you have not allocated your object with operator new or
    // you have other constraints, you'll need to override this
    virtual void dealloc(T* p) const;
    
 private: // Implementation of type_object_base hooks. Do not reimplement in derived classes.
    void instance_dealloc(PyObject*) const;
};

//
// type objects
//
template <class Base>
class callable : public Base
{
 public:
    typedef callable properties; // Convenience for derived class construction
    typedef typename Base::instance instance;
    callable(PyTypeObject* type_type, const char* name);
    callable(PyTypeObject* type_type);
 private:
    PyObject* instance_call(PyObject* obj, PyObject* args, PyObject* kw) const;
};

template <class Base>
class getattrable : public Base
{
 public:
    typedef getattrable properties; // Convenience for derived class construction
    typedef typename Base::instance instance;
    getattrable(PyTypeObject* type_type, const char* name);
    getattrable(PyTypeObject* type_type);
 private:
    PyObject* instance_getattr(PyObject* obj, const char* name) const;
};

template <class Base>
class setattrable : public Base
{
 public:
    typedef setattrable properties; // Convenience for derived class construction
    typedef typename Base::instance instance;
    setattrable(PyTypeObject* type_type, const char* name);
    setattrable(PyTypeObject* type_type);
 private:
    int instance_setattr(PyObject* obj, const char* name, PyObject* value) const;
};

template <class Base>
class reprable : public Base
{
 public:
    typedef reprable properties; // Convenience for derived class construction
    typedef typename Base::instance instance;
    reprable(PyTypeObject* type_type, const char* name);
    reprable(PyTypeObject* type_type);
 private:
    PyObject* instance_repr(PyObject* obj) const;
};

//
// Member function definitions
//

// type_object<>
template <class T>
void type_object<T>::instance_dealloc(PyObject* obj) const
{
    this->dealloc(downcast<instance>(obj).get());
}

template <class T>
void type_object<T>::dealloc(T* obj) const
{
    delete obj;
}

// callable
template <class Base>
callable<Base>::callable(PyTypeObject* type_type, const char* name)
    : Base(type_type, name)
{
    this->enable(call);
}
        
template <class Base>
callable<Base>::callable(PyTypeObject* type_type)
    : Base(type_type)
{
    this->enable(call);
}
        
template <class Base>
PyObject* callable<Base>::instance_call(PyObject* obj, PyObject* args, PyObject* kw) const
{
    return downcast<instance>(obj)->call(args, kw);
}

// getattrable
template <class Base>
getattrable<Base>::getattrable(PyTypeObject* type_type, const char* name)
    : Base(type_type, name)
{
    this->enable(getattr);
}
        
template <class Base>
getattrable<Base>::getattrable(PyTypeObject* type_type)
    : Base(type_type)
{
    this->enable(getattr);
}
        
template <class Base>
PyObject* getattrable<Base>::instance_getattr(PyObject* obj, const char* name) const
{
    return downcast<instance>(obj)->getattr(name);
}

// setattrable
template <class Base>
setattrable<Base>::setattrable(PyTypeObject* type_type, const char* name)
    : Base(type_type, name)
{
    this->enable(setattr);
}
        
template <class Base>
setattrable<Base>::setattrable(PyTypeObject* type_type)
    : Base(type_type)
{
    this->enable(setattr);
}
        
template <class Base>
int setattrable<Base>::instance_setattr(PyObject* obj, const char* name, PyObject* value) const
{
    return downcast<instance>(obj)->setattr(name, value);
}

// reprable
template <class Base>
reprable<Base>::reprable(PyTypeObject* type_type, const char* name)
    : Base(type_type, name)
{
    this->enable(repr);
}
        
template <class Base>
reprable<Base>::reprable(PyTypeObject* type_type)
    : Base(type_type)
{
    this->enable(repr);
}
        
template <class Base>
PyObject* reprable<Base>::instance_repr(PyObject* obj) const
{
    return downcast<instance>(obj)->repr();
}

  class shared_pod_manager
  {
      typedef std::pair<char*, std::size_t> holder;
      typedef std::vector<holder> storage;
        
   public:
      static shared_pod_manager& obj();
      ~shared_pod_manager();

      template <class T>
      static void replace_if_equal(T*& t)
      {
          t = reinterpret_cast<T*>(obj().replace_if_equal(t, sizeof(T)));
      }

      template <class T>
      static void make_unique_copy(T*& t)
      {
          t = reinterpret_cast<T*>(obj().make_unique_copy(t, sizeof(T)));
      }

      template <class T>
      static void create(T*& t)
      {
          t = reinterpret_cast<T*>(obj().create(sizeof(T)));
      }

      template <class T>
      static void dispose(T* t)
      {
          obj().dec_ref(t, sizeof(T));
      }

   private:
      void* replace_if_equal(void* pod, std::size_t size);
      void* make_unique_copy(void* pod, std::size_t size);
      void* create(std::size_t size);
      void dec_ref(void* pod, std::size_t size);
      void erase_from_list(void* pod);
        
      struct compare;
      struct identical;

   private:
      shared_pod_manager() {} // instance

#ifdef TYPE_OBJECT_BASE_STANDALONE_TEST
   public:
#endif
      storage m_storage;
  };


  void add_capability(type_object_base::capability capability, 
                      PyTypeObject* dest);

// This macro gets the length of an array as a compile-time constant, and will
// fail to compile if the parameter is a pointer.
# define PY_ARRAY_LENGTH(a) \
        (sizeof(::python::detail::countof_validate(a, &(a))) ? sizeof(a) / sizeof((a)[0]) : 0)

  template<typename T>
  inline void countof_validate(T* const, T* const*);

  template<typename T>
  inline int countof_validate(const void*, T);

}} // namespace python::detail

#endif // TYPES_DWA051800_H_
