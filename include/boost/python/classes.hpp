//  (C) Copyright David Abrahams 2000. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
//  The author gratefully acknowleges the support of Dragon Systems, Inc., in
//  producing this work.

#ifndef SUBCLASS_DWA051500_H_
# define SUBCLASS_DWA051500_H_

# include <boost/python/detail/config.hpp>
# include <boost/python/detail/types.hpp>
# include <boost/python/objects.hpp>
# include <boost/python/detail/singleton.hpp>
# include <boost/utility.hpp>
# include <boost/python/conversions.hpp>
# include <boost/python/callback.hpp>

namespace boost { namespace python {

// A simple type which acts something like a built-in Python class obj.
class instance
    : public boost::python::detail::python_object
{
 public:
    instance(PyTypeObject* class_);
    ~instance();

    // Standard Python functions.
    PyObject* repr();
    int compare(PyObject*);
    PyObject* str();
    long hash();
    PyObject* call(PyObject* args, PyObject* keywords);
    PyObject* getattr(const char* name, bool use_special_function = true);
    int setattr(const char* name, PyObject* value);

    // Mapping methods
    int length();
    PyObject* get_subscript(PyObject* key);
    void set_subscript(PyObject* key, PyObject* value);

    // Sequence methods
    PyObject* get_slice(int start, int finish);
    void set_slice(int start, int finish, PyObject* value);

    // Number methods
    PyObject* add(PyObject* other);
    PyObject* subtract(PyObject* other);
    PyObject* multiply(PyObject* other);
    PyObject* divide(PyObject* other);
    PyObject* remainder(PyObject* other);
    PyObject* divmod(PyObject* other);
    PyObject* power(PyObject*, PyObject*);
    PyObject* negative();
    PyObject* positive();
    PyObject* absolute();
    int nonzero();
    PyObject* invert();
    PyObject* lshift(PyObject* other);
    PyObject* rshift(PyObject* other);
    PyObject* do_and(PyObject* other);
    PyObject* do_xor(PyObject* other);
    PyObject* do_or(PyObject* other);
    int coerce(PyObject**, PyObject**);
    PyObject* as_int();
    PyObject* as_long();
    PyObject* as_float();
    PyObject* oct();
    PyObject* hex();

 private: // noncopyable, without the size bloat
    instance(const instance&);
    void operator=(const instance&);

 private: // helper functions
    int setattr_dict(PyObject* value);
    
 private:
    dictionary m_name_space;
};

template <class T> class meta_class;

namespace detail {
  class class_base : public type_object_base
  {
   public:
      class_base(PyTypeObject* meta_class_obj, string name, tuple bases, const dictionary& name_space);
      tuple bases() const;
      string name() const;
      dictionary& dict();
      
      // Standard Python functions.
      PyObject* getattr(const char* name);
      int setattr(const char* name, PyObject* value);
      PyObject* repr() const;
      void add_base(ref base);

   protected:
      bool initialize_instance(instance* obj, PyObject* args, PyObject* keywords);

   private: // virtual functions
      // Subclasses should override this to delete the particular obj type
      virtual void delete_instance(PyObject*) const = 0;

   private: // boost::python::type_object_base required interface implementation
      void instance_dealloc(PyObject*) const; // subclasses should not override this
      
   private:
      string m_name;
      tuple m_bases;
      dictionary m_name_space;
  };

  void enable_named_method(class_base* type_obj, const char* name);
}

// A type which acts a lot like a built-in Python class. T is the obj type,
// so class_t<instance> is a very simple "class-alike".
template <class T>
class class_t
    : public boost::python::detail::class_base
{
 public:
    class_t(meta_class<T>* meta_class_obj, string name, tuple bases, const dictionary& name_space);
    
    // Standard Python functions.
    PyObject* call(PyObject* args, PyObject* keywords);
    
 private: // Implement mapping methods on instances
    PyObject* instance_repr(PyObject*) const;
    int instance_compare(PyObject*, PyObject* other) const;
    PyObject* instance_str(PyObject*) const;
    long instance_hash(PyObject*) const;
    int instance_mapping_length(PyObject*) const;
    PyObject* instance_mapping_subscript(PyObject*, PyObject*) const;
    int instance_mapping_ass_subscript(PyObject*, PyObject*, PyObject*) const;

 private: // Implement sequence methods on instances
    int instance_sequence_length(PyObject*) const;
    PyObject* instance_sequence_item(PyObject* obj, int n) const;
    int instance_sequence_ass_item(PyObject* obj, int n, PyObject* value) const;
    PyObject* instance_sequence_slice(PyObject*, int start, int finish) const;
    int instance_sequence_ass_slice(PyObject*, int start, int finish, PyObject* value) const;

 private: // Implement number methods on instances
    PyObject* instance_number_add(PyObject*, PyObject*) const;
    PyObject* instance_number_subtract(PyObject*, PyObject*) const;
    PyObject* instance_number_multiply(PyObject*, PyObject*) const;
    PyObject* instance_number_divide(PyObject*, PyObject*) const;
    PyObject* instance_number_remainder(PyObject*, PyObject*) const;
    PyObject* instance_number_divmod(PyObject*, PyObject*) const;
    PyObject* instance_number_power(PyObject*, PyObject*, PyObject*) const;
    PyObject* instance_number_negative(PyObject*) const;
    PyObject* instance_number_positive(PyObject*) const;
    PyObject* instance_number_absolute(PyObject*) const;
    int instance_number_nonzero(PyObject*) const;
    PyObject* instance_number_invert(PyObject*) const;
    PyObject* instance_number_lshift(PyObject*, PyObject*) const;
    PyObject* instance_number_rshift(PyObject*, PyObject*) const;
    PyObject* instance_number_and(PyObject*, PyObject*) const;
    PyObject* instance_number_xor(PyObject*, PyObject*) const;
    PyObject* instance_number_or(PyObject*, PyObject*) const;
    int instance_number_coerce(PyObject*, PyObject**, PyObject**) const;
    PyObject* instance_number_int(PyObject*) const;
    PyObject* instance_number_long(PyObject*) const;
    PyObject* instance_number_float(PyObject*) const;
    PyObject* instance_number_oct(PyObject*) const;
    PyObject* instance_number_hex(PyObject*) const;
    
 private: // Miscellaneous "special" methods
    PyObject* instance_call(PyObject* obj, PyObject* args, PyObject* keywords) const;
    PyObject* instance_getattr(PyObject* obj, const char* name) const;
    int instance_setattr(PyObject* obj, const char* name, PyObject* value) const;

 private: // Implementation of boost::python::detail::class_base required interface
    void delete_instance(PyObject*) const;
    
 private: // noncopyable, without the size bloat
    class_t(const class_t<T>&);
    void operator=(const class_t&);
};

// The type of a class_t<T> object.
template <class T>
class meta_class
    : public boost::python::detail::reprable<
                boost::python::detail::callable<
                   boost::python::detail::getattrable<
                      boost::python::detail::setattrable<
                         boost::python::detail::type_object<class_t<T> > > > > >,
      boost::noncopyable
{
 public:
    meta_class();

    // Standard Python functions.
    PyObject* call(PyObject* args, PyObject* keywords);
    
    struct type_object
        : boost::python::detail::singleton<type_object,
             boost::python::detail::callable<
                boost::python::detail::type_object<meta_class> > >
    {
        type_object() : singleton_base(&PyType_Type) {}
    };
};

//
// Member function implementations.
//
template <class T>
meta_class<T>::meta_class()
    : properties(type_object::instance())
{
} 

template <class T>
class_t<T>::class_t(meta_class<T>* meta_class_obj, string name, tuple bases, const dictionary& name_space)
    : boost::python::detail::class_base(meta_class_obj, name, bases, name_space)
{
}

template <class T>
void class_t<T>::delete_instance(PyObject* obj) const
{
    delete downcast<T>(obj);
}

template <class T>
PyObject* class_t<T>::call(PyObject* args, PyObject* keywords)
{
    reference<T> result(new T(this));
    if (!this->initialize_instance(result.get(), args, keywords))
        return 0;
    else
        return result.release();
}

template <class T>
PyObject* class_t<T>::instance_repr(PyObject* obj) const
{
    return downcast<T>(obj)->repr();
}

template <class T>
int class_t<T>::instance_compare(PyObject* obj, PyObject* other) const
{
    return downcast<T>(obj)->compare(other);
}

template <class T>
PyObject* class_t<T>::instance_str(PyObject* obj) const
{
    return downcast<T>(obj)->str();
}

template <class T>
long class_t<T>::instance_hash(PyObject* obj) const
{
    return downcast<T>(obj)->hash();
}

template <class T>
int class_t<T>::instance_mapping_length(PyObject* obj) const
{
    return downcast<T>(obj)->length();
}

template <class T>
int class_t<T>::instance_sequence_length(PyObject* obj) const
{
    return downcast<T>(obj)->length();
}

template <class T>
PyObject* class_t<T>::instance_mapping_subscript(PyObject* obj, PyObject* key) const
{
    return downcast<T>(obj)->get_subscript(key);
}

template <class T>
PyObject* class_t<T>::instance_sequence_item(PyObject* obj, int n) const
{
    ref key(to_python(n, lookup_tag()));
    return downcast<T>(obj)->get_subscript(key.get());
}

template <class T>
int class_t<T>::instance_sequence_ass_item(PyObject* obj, int n, PyObject* value) const
{
    ref key(to_python(n, lookup_tag()));
    downcast<T>(obj)->set_subscript(key.get(), value);
    return 0;
}

template <class T>
int class_t<T>::instance_mapping_ass_subscript(PyObject* obj, PyObject* key, PyObject* value) const
{
    downcast<T>(obj)->set_subscript(key, value);
    return 0;
}

void adjust_slice_indices(PyObject* obj, int& start, int& finish);

template <class T>
PyObject* class_t<T>::instance_sequence_slice(PyObject* obj, int start, int finish) const
{
    adjust_slice_indices(obj, start, finish);    
    return downcast<T>(obj)->get_slice(start, finish);
}

template <class T>
int class_t<T>::instance_sequence_ass_slice(PyObject* obj, int start, int finish, PyObject* value) const
{
    adjust_slice_indices(obj, start, finish);
    downcast<T>(obj)->set_slice(start, finish, value);
    return 0;
}

template <class T>
PyObject* class_t<T>::instance_call(PyObject* obj, PyObject* args, PyObject* keywords) const
{
    return downcast<T>(obj)->call(args, keywords);
}

template <class T>
PyObject* class_t<T>::instance_getattr(PyObject* obj, const char* name) const
{
    return downcast<T>(obj)->getattr(name);
}


template <class T>
int class_t<T>::instance_setattr(PyObject* obj, const char* name, PyObject* value) const
{
    return downcast<T>(obj)->setattr(name, value);
}

template <class T>
PyObject* class_t<T>::instance_number_add(PyObject* obj, PyObject* other) const
{
    return downcast<T>(obj)->add(other);
}

template <class T>
PyObject* class_t<T>::instance_number_subtract(PyObject* obj, PyObject* other) const
{
    return downcast<T>(obj)->subtract(other);
}

template <class T>
PyObject* class_t<T>::instance_number_multiply(PyObject* obj, PyObject* other) const
{
    return downcast<T>(obj)->multiply(other);
}

template <class T>
PyObject* class_t<T>::instance_number_divide(PyObject* obj, PyObject* other) const
{
    return downcast<T>(obj)->divide(other);
}

template <class T>
PyObject* class_t<T>::instance_number_remainder(PyObject* obj, PyObject* other) const
{
    return downcast<T>(obj)->remainder(other);
}

template <class T>
PyObject* class_t<T>::instance_number_divmod(PyObject* obj, PyObject* other) const
{
    return downcast<T>(obj)->divmod(other);
}

template <class T>
PyObject* class_t<T>::instance_number_power(PyObject* obj, PyObject* exponent, PyObject* modulus) const
{
    return downcast<T>(obj)->power(exponent, modulus);
}

template <class T>
PyObject* class_t<T>::instance_number_negative(PyObject* obj) const
{
    return downcast<T>(obj)->negative();
}

template <class T>
PyObject* class_t<T>::instance_number_positive(PyObject* obj) const
{
    return downcast<T>(obj)->positive();
}

template <class T>
PyObject* class_t<T>::instance_number_absolute(PyObject* obj) const
{
    return downcast<T>(obj)->absolute();
}

template <class T>
int class_t<T>::instance_number_nonzero(PyObject* obj) const
{
    return downcast<T>(obj)->nonzero();
}

template <class T>
PyObject* class_t<T>::instance_number_invert(PyObject* obj) const
{
    return downcast<T>(obj)->invert();
}

template <class T>
PyObject* class_t<T>::instance_number_lshift(PyObject* obj, PyObject* other) const
{
    return downcast<T>(obj)->lshift(other);
}

template <class T>
PyObject* class_t<T>::instance_number_rshift(PyObject* obj, PyObject* other) const
{
    return downcast<T>(obj)->rshift(other);
}

template <class T>
PyObject* class_t<T>::instance_number_and(PyObject* obj, PyObject* other) const
{
    return downcast<T>(obj)->do_and(other);
}

template <class T>
PyObject* class_t<T>::instance_number_xor(PyObject* obj, PyObject* other) const
{
    return downcast<T>(obj)->do_xor(other);
}

template <class T>
PyObject* class_t<T>::instance_number_or(PyObject* obj, PyObject* other) const
{
    return downcast<T>(obj)->do_or(other);
}

template <class T>
int class_t<T>::instance_number_coerce(PyObject* obj, PyObject** x, PyObject** y) const
{
    return downcast<T>(obj)->coerce(x, y);
}

template <class T>
PyObject* class_t<T>::instance_number_int(PyObject* obj) const
{
    return downcast<T>(obj)->as_int();
}

template <class T>
PyObject* class_t<T>::instance_number_long(PyObject* obj) const
{
    return downcast<T>(obj)->as_long();
}

template <class T>
PyObject* class_t<T>::instance_number_float(PyObject* obj) const
{
    return downcast<T>(obj)->as_float();
}

template <class T>
PyObject* class_t<T>::instance_number_oct(PyObject* obj) const
{
    return downcast<T>(obj)->oct();
}

template <class T>
PyObject* class_t<T>::instance_number_hex(PyObject* obj) const
{
    return downcast<T>(obj)->hex();
}

namespace detail {
  inline dictionary& class_base::dict()
  {
      return m_name_space;
  }

  inline tuple class_base::bases() const
  {
      return m_bases;
  }
}

template <class T>
PyObject* meta_class<T>::call(PyObject* args, PyObject* /*keywords*/)
{
    PyObject* name;
    PyObject* bases;
    PyObject* name_space;
    
    if (!PyArg_ParseTuple(args, const_cast<char*>("O!O!O!"),
                          &PyString_Type, &name,
                          &PyTuple_Type, &bases,
                          &PyDict_Type, &name_space))
    {
        return 0;
    }
    
    return as_object(
        new class_t<T>(this, string(ref(name, ref::increment_count)),
                  tuple(ref(bases, ref::increment_count)),
                  dictionary(ref(name_space, ref::increment_count)))
        );
}

namespace detail {
  const string& setattr_string();
  const string& getattr_string();
  const string& delattr_string();

  inline string class_base::name() const
  {
      return m_name;
  }
}


}} // namespace boost::python
#endif
