// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef DEF_HELPER_DWA200287_HPP
# define DEF_HELPER_DWA200287_HPP

# include <boost/python/args.hpp>
# include <boost/type_traits/ice.hpp>
# include <boost/type_traits/same_traits.hpp>
# include <boost/python/detail/indirect_traits.hpp>
# include <boost/mpl/logical/not.hpp>
# include <boost/mpl/logical/and.hpp>
# include <boost/type_traits/add_reference.hpp>
# include <boost/mpl/lambda.hpp>
# include <boost/mpl/apply.hpp>
# include <boost/tuple/tuple.hpp>
# include <boost/python/detail/not_specified.hpp>

namespace boost { namespace python {

struct default_call_policies;

namespace detail
{
  template <class Tuple, class Predicate>
  struct tuple_extract;
  
  template <bool matched>
  struct tuple_extract_impl
  {
      template <class Tuple, class Predicate>
      struct apply
      {
          typedef typename Tuple::head_type result_type;
          
          static typename Tuple::head_type extract(Tuple const& x)
          {
              return x.get_head();
          }
      };
  };
  
  template <>
  struct tuple_extract_impl<false>
  {
      template <class Tuple, class Predicate>
      struct apply
          : tuple_extract<typename Tuple::tail_type, Predicate>
      {
          // All of this forwarding would be unneeded if tuples were
          // derived from their tails.
          typedef tuple_extract<typename Tuple::tail_type, Predicate> base;
          typedef typename base::result_type result_type;
          static result_type extract(Tuple const& x)
          {
              return base::extract(x.get_tail());
          }
      };
  };

  template <class Tuple, class Predicate>
  struct tuple_extract_base_select
  {
      typedef typename Tuple::head_type head_type;
      typedef typename mpl::apply1<Predicate,head_type>::type match_t;
      BOOST_STATIC_CONSTANT(bool, match = match_t::value);
      typedef typename tuple_extract_impl<match>::template apply<Tuple,Predicate> type;
  };
  
  template <class Tuple, class Predicate>
  struct tuple_extract
      : tuple_extract_base_select<
         Tuple
         , typename mpl::lambda<Predicate>::type
      >::type
  {
  };

  template <class Tuple>
  struct doc_extract
      : tuple_extract<
      Tuple,
      mpl::logical_not<
        is_reference_to_class<
          add_reference<mpl::_1>
        >
      > >
  {
  };
  
  template <class Tuple>
  struct keyword_extract
      : tuple_extract<Tuple, is_reference_to_keywords<add_reference<mpl::_1> > >
  {
  };

  template <class Tuple>
  struct policy_extract
      : tuple_extract<
          Tuple,
          mpl::logical_and<
             is_reference_to_class<add_reference<mpl::_> >
             , mpl::logical_not<is_reference_to_keywords<add_reference<mpl::_1> > >
          >
        >
  {
  };

# define BOOST_PYTHON_DEF_HELPER_TAIL default_call_policies, keywords<0>, char const*
  template <class T1, class T2 = not_specified, class T3 = not_specified>
  struct def_helper
  {
      typedef typename mpl::if_<
          is_same<T2, not_specified>
          , boost::tuples::tuple<T1 const&, BOOST_PYTHON_DEF_HELPER_TAIL>
          , typename mpl::if_<
                is_same<T3, not_specified>
                , boost::tuples::tuple<T1 const&, T2 const&, BOOST_PYTHON_DEF_HELPER_TAIL>
                , boost::tuples::tuple<T1 const&, T2 const&, T3 const&>
            >::type
         >::type all_t;

      def_helper(T1 const& a1) : m_all(a1) {}
      def_helper(T1 const& a1, T2 const& a2) : m_all(a1,a2) {}
      def_helper(T1 const& a1, T2 const& a2, T3 const& a3) : m_all(a1,a2,a3) {}

      char const* doc() const
      {
          return doc_extract<all_t>::extract(m_all);
      }
      
      typename keyword_extract<all_t>::result_type keywords() const
      {
          return keyword_extract<all_t>::extract(m_all);
      }
      
      typename policy_extract<all_t>::result_type policies() const
      {
          return policy_extract<all_t>::extract(m_all);
      }
      
      all_t m_all;
  };
# undef BOOST_PYTHON_DEF_HELPER_TAIL
}

}} // namespace boost::python::detail

#endif // DEF_HELPER_DWA200287_HPP
