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
# include <boost/type.hpp>

// Keep these for the metaprogram which EDG is choking on.
# if !defined(__EDG__) || (__EDG_VERSION__ > 245)
#  include <boost/mpl/type_list.hpp>
#  include <boost/mpl/for_each.hpp>
#  include <boost/type_traits/alignment_traits.hpp>
#  include <boost/type_traits/composite_traits.hpp>
# endif 

namespace boost { namespace python { namespace converter { 

// A POD which is layout-compatible with the real intermediate data
// for all from_python conversions. There may be additional storage if
// we are converting a reference type.
struct from_python_data
{
    void* stage1;
};

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
      static T t;
      BOOST_STATIC_CONSTANT(std::size_t, value = sizeof(t));
  };
  
# endif

  struct unknown_alignment
  {
      void* p;
  };
  
// EDG is too slow to handle this metaprogram :(  
#if !defined(__EDG__) || (__EDG_VERSION__ > 245)
  struct alignment_dummy;

  template <std::size_t target_alignment>
  struct best_alignment_type
  {
      template <class T1, class T2>
      struct apply
      {
          BOOST_STATIC_CONSTANT(
              std::size_t, align1 = alignment_of<T1>::value);
          
          BOOST_STATIC_CONSTANT(
              std::size_t, align2 = alignment_of<T2>::value);
          
          BOOST_STATIC_CONSTANT(
              bool, aligned2 = (
                  (align2 >= target_alignment)
                  & (align2 % target_alignment == 0))
              );
          
          BOOST_STATIC_CONSTANT(
              bool, choose_t2 = (
                  aligned2 && (
                      is_same<T1,unknown_alignment>::value
                      | (align2 < alignment_of<T1>::value)
                      | (sizeof(T2) < sizeof(T1)))
                  ));
          
          typedef mpl::select_type<choose_t2, T2, T1>::type type;
      };
  };

  typedef mpl::type_list<
      char,short,int,long,float,double,long double
      ,void*
      ,void(*)()
      ,void (alignment_dummy::*)()
      , char (alignment_dummy::*)
  >
  align_types;
#endif // EDG is too slow
  
  template <class Align, std::size_t size>
  struct aligned_storage
  {
      typedef Align align_t;
      union 
      {
          Align align;
          char bytes[size
                     // this is just a STATIC_ASSERT. For some reason
                     // MSVC was barfing on the boost one.
              - (is_same<align_t,unknown_alignment>::value ? size : 0)];
      };
  };

  template <class Reference>
  struct referent_storage
  {
// EDG is too slow to handle this metaprogram :(  
#if !defined(__EDG__) || (__EDG_VERSION__ > 245)
      typedef mpl::for_each<
          align_types
          , unknown_alignment
          , best_alignment_type<referent_alignment<Reference>::value>
      > loop;
      typedef typename loop::state align_t;
#else
      // The Python source makes the assumption that double has
      // maximal alignment anyway
      typedef double align_t;
#endif 

      typedef aligned_storage<align_t,referent_size<Reference>::value> type;
  };

  template <class T>
  struct intermediate_data : from_python_data
  {
      typename referent_storage<T>::type stage2;
  };

  template <>
  struct intermediate_data<void> : from_python_data
  {
  };

}

// -------------------------------------------------------------------------
// Auxiliary POD storage where the convertible and/or convert functions of a
// from_python object may place arbitrary data.
//
// Always starts with a void*
//
// For references, we produce additional aligned storage sufficient to
// store the referent

template <class T>
struct from_python_intermediate_data
{
    typedef typename mpl::select_type<
        is_reference<T>::value, T, void>::type just_reference_t;

    typedef detail::intermediate_data<just_reference_t> type;
};

template <class T>
void* get_storage(from_python_data& x, boost::type<T>* = 0)
{
    typedef typename from_python_intermediate_data<T>::type layout;
    return static_cast<layout*>(&x)->stage2.bytes;
}

}}} // namespace boost::python::converter

#endif // FROM_PYTHON_AUX_DATA_DWA2002128_HPP
