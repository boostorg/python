// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef LIST_DWA2002627_HPP
# define LIST_DWA2002627_HPP

# include <boost/python/object.hpp>
# include <boost/python/converter/pytype_object_mgr_traits.hpp>

namespace boost { namespace python { 

class BOOST_PYTHON_DECL list : public object
{
 public:
    list(); // new list
    explicit list(object_cref sequence); // new list initialized from sequence's items

    template <class T>
    explicit list(T const& sequence)
        : object(list::call(object(sequence)))
    {
    }

     void append(object_cref); // append object to end

    template <class T>
    void append(T const& x)
    {
        this->append(object(x));
    }

    long count(object_cref value) const; // return number of occurrences of value

    template <class T>
    long count(T const& value) const
    {
        return this->count(object(value));
    }
    
    void extend(object_cref sequence); // extend list by appending sequence elements
    
    template <class T>
    void extend(T const& x)
    {
        this->extend(object(x));
    }

    long index(object_cref value) const; // return index of first occurrence of value

    template <class T>
    long index(T const& x) const
    {
        return this->index(object(x));
    }
    
    void insert(int index, object_cref); // insert object before index
    void insert(object const& index, object_cref);

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
    
    object pop(); // remove and return item at index (default last)
    object pop(long index);
    object pop(object const& index);

    void remove(object_cref value); // remove first occurrence of value
    
    template <class T>
    void remove(T const& value)
    {
        this->remove(object(value));
    }
    
    void reverse(); // reverse *IN PLACE*

    void sort(); //  sort *IN PLACE*; if given, cmpfunc(x, y) -> -1, 0, 1
    void sort(object_cref cmpfunc);

    template <class T>
    void sort(T const& value)
    {
        this->sort(object(value));
    }
    
 public: // implementation detail -- for internal use only
    BOOST_PYTHON_FORWARD_OBJECT_CONSTRUCTORS(list)
    
 private:
    static detail::new_non_null_reference call(object const&);
};

//
// Converter Specializations
//
namespace converter
{
  template <>
  struct object_manager_traits<list>
      : pytype_object_manager_traits<&PyList_Type,list>
  {
  };
}

}} // namespace boost::python

#endif // LIST_DWA2002627_HPP
