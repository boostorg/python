// Copyright Sander Kersten
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#ifndef TUPLE_CONVERTER_SPK20162802_HPP
# define TUPLE_CONVERTER_SPK20162802_HPP

# include <boost/tuple/tuple.hpp>
# include <boost/python/tuple.hpp>
# include <boost/python/extract.hpp>
# include <boost/python/to_python_converter.hpp>


namespace boost { namespace python {

namespace detail
{
  void tuple_to_python_(PyObject*, tuples::null_type, int) {}

  template <class H, class T>
  void tuple_to_python_(PyObject* obj, tuples::cons<H,T> const& x, int N)
  {
    PyTuple_SET_ITEM(obj, N, incref(python::object(x.get_head()).ptr()));
    tuple_to_python_(obj, x.get_tail(), N+1);
  }
  
  template <class H, class T>
  PyObject* tuple_to_python(tuples::cons<H,T> const& x)
  {
    PyObject *obj = PyTuple_New(tuples::length<tuples::cons<H,T> >::value);
    tuple_to_python_(obj, x, 0);
    return obj;
  }
}

template <class T>
struct tuple_to_python_converter
{
  static PyObject* convert(T const& x)
  {
    return detail::tuple_to_python(x);
  }
};
 
namespace detail
{
  template <int N, int Max, typename Tuple>
  struct types_the_same;

  template <int N, typename Cons>
  struct types_the_same<N, N, Cons>
  {
    static bool same(PyObject*) { return false; }
  };

  template <int N>
  struct types_the_same<N, N, boost::tuples::null_type>
  {
    static bool same(PyObject*) { return true; }
  };

  template <int N, int Max, typename T, typename Tail>
  struct types_the_same<N, Max, tuples::cons<T, Tail> >
  {
    static bool same(PyObject* tuple)
    {
      if (extract<T>(PyTuple_GetItem(tuple, N)).check())
        return types_the_same<N+1, Max, Tail>::same(tuple);
      else
        return false;
    }
  };
  
  void assign_tuple(const tuples::null_type&, PyObject*, int) {}

  template <typename H, typename T>
  void assign_tuple(tuples::cons<H, T>& x, PyObject* tuple, int N = 0)
  {
    x.get_head() = extract<H>(PyTuple_GetItem(tuple, N));
    assign_tuple(x.get_tail(), tuple, N+1);
  }
}
 
template <typename Tuple>
struct tuple_from_python_converter
{
  tuple_from_python_converter()
  {
    boost::python::converter::registry::push_back(
      &convertible,
      &construct,
      type_id<Tuple>());
  }

  static void* convertible(PyObject* obj)
  {
    if (!PyTuple_Check(obj)) {
      return 0;
    }
    if (PyTuple_Size(obj) != tuples::length<Tuple>::value) {
      return 0;
    }
    if (!detail::types_the_same<
             0
           , tuples::length<Tuple>::value
           , typename Tuple::inherited>::same(obj)) {
      return 0;
    }
    return obj;
  }

  static void construct(
    PyObject* obj,
    converter::rvalue_from_python_stage1_data* data)
  {
    void* storage = (
        (converter::rvalue_from_python_storage<Tuple>*)
        data)->storage.bytes;

    Tuple *tuple = new (storage) Tuple();

    detail::assign_tuple(*tuple, obj);

    data->convertible = storage;
  }
};

template <typename Tuple>
void tuple_converter(const Tuple* = NULL)
{
  to_python_converter<Tuple, tuple_to_python_converter<Tuple> >();
  tuple_from_python_converter<Tuple>();
}

}} // namespace boost::python

#endif // TUPLE_CONVERTER_SPK20162802_HPP
