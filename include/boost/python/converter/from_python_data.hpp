// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef FROM_PYTHON_AUX_DATA_DWA2002128_HPP
# define FROM_PYTHON_AUX_DATA_DWA2002128_HPP

# include <boost/python/detail/char_array.hpp>
# include <boost/mpl/select_if.hpp>
# include <boost/type_traits/same_traits.hpp>
# include <boost/type_traits/transform_traits.hpp>
# include <boost/static_assert.hpp>
# include <boost/python/converter/from_python_stage1_data.hpp>
# include <boost/type_traits/composite_traits.hpp>
# include <boost/type_traits/cv_traits.hpp>
# include <boost/python/detail/destroy.hpp>
# include <boost/preprocessor/list/for_each_i.hpp>
# include <boost/preprocessor/tuple/to_list.hpp>
# include <boost/preprocessor/cat.hpp>

namespace boost { namespace python { namespace converter { 

namespace detail
{
  template <class T> struct referent_size;
  
# ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
  
  template <class T>
  struct referent_size<T&>
  {
      BOOST_STATIC_CONSTANT(
          std::size_t, value = sizeof(T));
  };

# else

  template <class T> struct referent_size
  {
      static T f();
      BOOST_STATIC_CONSTANT(std::size_t, value = sizeof(f()));
  };
  
# endif
  struct alignment_dummy;
  typedef void (*function_ptr)();
  typedef int (alignment_dummy::*member_ptr);
  typedef int (alignment_dummy::*member_function_ptr)();

# define BOOST_PYTHON_ALIGNMENT_TYPES BOOST_PP_TUPLE_TO_LIST( \
        11, ( \
        char, short, int, long, float, double, long double \
        , void*, function_ptr, member_ptr, member_function_ptr))

# define BOOST_PYTHON_CHOOSE_LOWER_SIZE(R,P,I,T) \
        typename mpl::select_if_c< \
           sizeof(T) <= target, T, char>::type BOOST_PP_CAT(t,I);
           
# define BOOST_PYTHON_CHOOSE_T(R,P,I,T) T BOOST_PP_CAT(t,I);
           
  template <std::size_t target>
  union lower_size
  {
      BOOST_PP_LIST_FOR_EACH_I(
          BOOST_PYTHON_CHOOSE_LOWER_SIZE
          , ignored, BOOST_PYTHON_ALIGNMENT_TYPES)
  };

  template <class Align, std::size_t size>
  union aligned_storage
  {
      Align align;
      char bytes[size];
  };

  template <class Reference>
  struct referent_storage
  {
      typedef lower_size<referent_size<Reference>::value> align_t;
      typedef aligned_storage<align_t,referent_size<Reference>::value> type;
  };
}

template <class T>
struct rvalue_base_data
{
    rvalue_stage1_data stage1;
    
    typename detail::referent_storage<
        typename add_reference<T>::type
    >::type storage;
};

template <class T>
struct rvalue_data : rvalue_base_data<T>
{
    rvalue_data(rvalue_stage1_data const&);
    rvalue_data(void*);
    ~rvalue_data();
 private:
    typedef typename add_reference<typename add_cv<T>::type>::type ref_type;
};

//
// Implementataions
//
template <class T>
inline rvalue_data<T>::rvalue_data(rvalue_stage1_data const& stage1)
{
    this->stage1 = stage1;
}

template <class T>
inline rvalue_data<T>::rvalue_data(void* convertible)
{
    this->stage1.convertible = convertible;
}

template <class T>
inline rvalue_data<T>::~rvalue_data()
{
    if (this->stage1.convertible == this->storage.bytes)
        python::detail::destroy_reference<ref_type>(this->storage.bytes);
}

}}} // namespace boost::python::converter

#endif // FROM_PYTHON_AUX_DATA_DWA2002128_HPP
