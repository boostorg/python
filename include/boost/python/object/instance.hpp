// Copyright David Abrahams 2002.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#ifndef INSTANCE_DWA200295_HPP
# define INSTANCE_DWA200295_HPP

# include <boost/python/detail/prefix.hpp>
# include <boost/type_traits/alignment_traits.hpp>
# include <boost/align.hpp>
# include <boost/python/detail/alignment_of.hpp>
# include <boost/type_traits/aligned_storage.hpp>
# include <cstddef>

namespace boost { namespace python
{
  struct BOOST_PYTHON_DECL_FORWARD instance_holder;

    //allow users to override the alignment through partial template specialization/SFINAE
    template<typename T, class Enable = void>
    struct alignment_of : public ::boost::alignment::alignment_of<T>{
    };

}} // namespace boost::python

namespace boost { namespace python { namespace objects { 

// Each extension instance will be one of these
template <class Data = char>
struct instance
{
    PyObject_VAR_HEAD
    PyObject* dict;
    PyObject* weakrefs; 
    instance_holder* objects;


    //compatability union
    union aligned_storage_t{
      typedef typename ::boost::aligned_storage< sizeof(Data), detail::alignment_of<Data>::value>::type type;
      type storage;
      char bytes[sizeof(type)];

      void * address() const{
          return storage.address();
      }
    };

    BOOST_ALIGNMENT(::boost::python::detail::alignment_of<Data>::value+0) aligned_storage_t storage;
};

template <class Data>
struct additional_instance_size
{
    typedef instance<Data> instance_data;
    typedef instance<char> instance_char;
    BOOST_STATIC_CONSTANT(
        std::size_t, value = sizeof(instance_data)
                           - BOOST_PYTHON_OFFSETOF(instance_char,storage) + detail::alignment_of<Data>::value);
};

}}} // namespace boost::python::object

#endif // INSTANCE_DWA200295_HPP
