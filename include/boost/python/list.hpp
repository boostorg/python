// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef LIST_DWA2002627_HPP
# define LIST_DWA2002627_HPP

# include <boost/python/object.hpp>
# include <boost/python/converter/pytype_arg_from_python.hpp>
# include <boost/python/converter/pytype_result_from_python.hpp>

namespace boost { namespace python { 

class list : public object
{
 public:
    BOOST_PYTHON_DECL list(); // new list
    explicit BOOST_PYTHON_DECL list(object_cref sequence); // new list initialized from sequence's items

    template <class T>
    explicit list(T const& sequence)
        : object(list::call(object(sequence)))
    {
    }

    BOOST_PYTHON_DECL void append(object_cref); // append object to end

    template <class T>
    void append(T const& x)
    {
        this->append(object(x));
    }

    BOOST_PYTHON_DECL long count(object_cref value) const; // return number of occurrences of value

    template <class T>
    long count(T const& value) const
    {
        return this->count(object(value));
    }
    
    BOOST_PYTHON_DECL void extend(object_cref sequence); // extend list by appending sequence elements
    
    template <class T>
    void extend(T const& x)
    {
        this->extend(object(x));
    }

    BOOST_PYTHON_DECL long index(object_cref value) const; // return index of first occurrence of value

    template <class T>
    long index(T const& x) const
    {
        return this->index(object(x));
    }
    
    BOOST_PYTHON_DECL void insert(int index, object_cref); // insert object before index
    BOOST_PYTHON_DECL void insert(object const& index, object_cref);

    template <class T>
    void insert(int index, T const& x) // insert object before index
    {
        this->insert(index, object(x));
    }
    
    template <class T>
    void insert(object const& index, T const& x) // insert object before index
    {
        this->insert(index, object(x));
    }
    
    BOOST_PYTHON_DECL object pop(); // remove and return item at index (default last)
    BOOST_PYTHON_DECL object pop(long index);
    BOOST_PYTHON_DECL object pop(object const& index);

    BOOST_PYTHON_DECL void remove(object_cref value); // remove first occurrence of value
    
    template <class T>
    void remove(T const& value)
    {
        this->remove(object(value));
    }
    
    BOOST_PYTHON_DECL void reverse(); // reverse *IN PLACE*

    BOOST_PYTHON_DECL void sort(); //  sort *IN PLACE*; if given, cmpfunc(x, y) -> -1, 0, 1
    BOOST_PYTHON_DECL void sort(object_cref cmpfunc);

    template <class T>
    void sort(T const& value)
    {
        this->sort(object(value));
    }
    
 public: // implementation detail -- for internal use only
    inline explicit list(detail::borrowed_reference);
    inline explicit list(detail::new_reference);
    
 private:
    static BOOST_PYTHON_DECL detail::new_reference call(object const&);
};

//
// Converter Specializations
//
template <class T> struct arg_from_python;

template <>
struct arg_from_python<list>
    : converter::pytype_wrapper_value_arg_from_python<list, &PyList_Type>
{
    typedef converter::pytype_wrapper_value_arg_from_python<list, &PyList_Type> base;
    typedef list result_type;
    
    arg_from_python(PyObject* p) : base(p) {}
};

template <>
struct arg_from_python<list const&>
    : arg_from_python<list>
{
    arg_from_python(PyObject* p)
        : arg_from_python<list>(p) {}
};

template <>
struct arg_from_python<list&>
    : converter::pytype_wrapper_ref_arg_from_python<list, &PyList_Type>
{
    typedef converter::pytype_wrapper_ref_arg_from_python<list, &PyList_Type> base;
    typedef list result_type;
    
    arg_from_python(PyObject* p)
        : base(p) {}
};

namespace converter
{
  template <class T> struct is_object_manager;

  template <>
  struct is_object_manager<list>
  {
      BOOST_STATIC_CONSTANT(bool, value = true);
  };

  template <class T> struct return_from_python;
  template <>
  struct return_from_python<list>
  {
      typedef list result_type;
      
      result_type operator()(PyObject* x) const
      {
          return list((pytype_result_from_python)(&PyList_Type, x));
      }
  };
}

//
// list implementation
//
inline list::list(detail::borrowed_reference p)
    : object(p)
{}

inline list::list(detail::new_reference p)
    : object(p)
{}

}} // namespace boost::python

#endif // LIST_DWA2002627_HPP
