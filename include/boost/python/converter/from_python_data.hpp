// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef FROM_PYTHON_AUX_DATA_DWA2002128_HPP
# define FROM_PYTHON_AUX_DATA_DWA2002128_HPP

# include <boost/python/detail/char_array.hpp>
# include <boost/mpl/select_type.hpp>
# include <boost/type_traits/same_traits.hpp>
# include <boost/type_traits/alignment_traits.hpp>
# include <boost/type_traits/transform_traits.hpp>
# include <boost/static_assert.hpp>
# include <boost/python/converter/from_python_stage1_data.hpp>
# include <boost/type_traits/composite_traits.hpp>
# include <boost/type_traits/cv_traits.hpp>
# include <boost/type_traits/ice.hpp>
# include <boost/python/detail/destroy.hpp>
# include <boost/preprocessor/list/for_each_i.hpp>
# include <boost/preprocessor/tuple/to_list.hpp>
# include <boost/preprocessor/cat.hpp>

namespace boost { namespace python { namespace converter { 

namespace detail
{
  template <class T> struct referent_alignment;
  template <class T> struct referent_size;
  
# ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
  
  template <class T>
  struct referent_alignment<T&>
  {
      BOOST_STATIC_CONSTANT(
          std::size_t, value = alignment_of<T>::value);
  };

  template <class T>
  struct referent_size<T&>
  {
      BOOST_STATIC_CONSTANT(
          std::size_t, value = sizeof(T));
  };

# else

  template <class U>
  struct alignment_chars
  {
      BOOST_STATIC_CONSTANT(
          std::size_T, n = alignment_of<U>::value);
      char elements[n + 1];
  };

  template <class T> struct referent_alignment
  {
      template <class U>
      static alignment_chars<U> helper(U&);
  
      static T t;
      
      BOOST_STATIC_CONSTANT(
          std::size_t, value = sizeof(helper(t).elements) - 1);
  };

  
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

# define BOOST_PYTHON_CHOOSE_LOWER_ALIGNMENT(R,P,I,T) \
        typename mpl::select_type< \
           alignment_of<T>::value <= target, T, char>::type BOOST_PP_CAT(t,I);

# define BOOST_PYTHON_CHOOSE_LOWER_SIZE(R,P,I,T) \
        typename mpl::select_type< \
           sizeof(T) <= target, T, char>::type BOOST_PP_CAT(t,I);
           
# define BOOST_PYTHON_CHOOSE_T(R,P,I,T) T BOOST_PP_CAT(t,I);
           
  template <std::size_t target>
  union lower_alignment
  {
      BOOST_PP_LIST_FOR_EACH_I(
          BOOST_PYTHON_CHOOSE_LOWER_ALIGNMENT
          , ignored, BOOST_PYTHON_ALIGNMENT_TYPES)
  };

  template <std::size_t target>
  union lower_size
  {
      BOOST_PP_LIST_FOR_EACH_I(
          BOOST_PYTHON_CHOOSE_LOWER_SIZE
          , ignored, BOOST_PYTHON_ALIGNMENT_TYPES)
  };

  union max_align
  {
      BOOST_PP_LIST_FOR_EACH_I(
          BOOST_PYTHON_CHOOSE_T
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
      typedef typename remove_cv<typename remove_reference<Reference>::type>::type referent;

      BOOST_STATIC_CONSTANT(std::size_t, target = referent_alignment<Reference>::value);
      typedef lower_alignment<target> t1;

      BOOST_STATIC_CONSTANT(bool, t1_aligned =
                            (alignment_of<t1>::value >= target)
                            & (alignment_of<t1>::value % target == 0));

      typedef lower_size<referent_size<Reference>::value> t2;

      BOOST_STATIC_CONSTANT(bool, t2_aligned =
                            (alignment_of<t2>::value >= target)
                            & (alignment_of<t2>::value % target == 0));


      typedef typename mpl::select_type<
          t1_aligned
          , t1
          , typename mpl::select_type< 
              t2_aligned
              , t2
              , max_align
          >::type
      >::type align_t;

      BOOST_STATIC_CONSTANT(std::size_t, found = alignment_of<align_t>::value);
    
      BOOST_STATIC_ASSERT(found >= target);
      BOOST_STATIC_ASSERT(found % target == 0);
    
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
        python::detail::destroy_reference<
            add_reference<
                add_cv<T>::type
            >::type
        >(storage.bytes);
}

}}} // namespace boost::python::converter

#endif // FROM_PYTHON_AUX_DATA_DWA2002128_HPP
