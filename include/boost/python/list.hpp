// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef LIST_DWA2002627_HPP
# define LIST_DWA2002627_HPP

# include <boost/python/object.hpp>
# include <boost/python/converter/pytype_extract_object_manager.hpp>

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
    BOOST_PYTHON_FORWARD_OBJECT_CONSTRUCTORS(list)
    
 private:
    static BOOST_PYTHON_DECL detail::new_non_null_reference call(object const&);
};

//
// Converter Specializations
//
namespace converter
{
  template <>
  struct extract_object_manager<list>
      : pytype_extract_object_manager<&PyList_Type,list>
  {
  };
}

}} // namespace boost::python

#endif // LIST_DWA2002627_HPP
