// Copyright David Abrahams 2001. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef POINTER_HOLDER_DWA20011215_HPP
# define POINTER_HOLDER_DWA20011215_HPP

# include <boost/python/object/class.hpp>
# include <boost/python/converter/type_id.hpp>
# include <boost/python/object/inheritance.hpp>
# include <boost/python/object/find_instance.hpp>
# include <boost/ref.hpp>
# include <boost/type.hpp>
# include <boost/mpl/select_type.hpp>
# include <boost/mpl/apply.hpp>

namespace boost { namespace python { namespace objects { 

template <class Pointer, class Value>
struct pointer_holder : instance_holder
{
    pointer_holder(Pointer);
    
    // Forward construction to the held object
    pointer_holder(PyObject*)
        : m_p(new Value) {}

    
    template <class A1>
    pointer_holder(PyObject*, A1 a1)
        : m_p(new Value(
            (typename unwrap_reference<A1>::type&)(a1)
                  ))
    {}
    
    template <class A1, class A2>
    pointer_holder(PyObject*, A1 a1, A2 a2)
        : m_p(new Value(
            (typename unwrap_reference<A1>::type&)(a1)
            , (typename unwrap_reference<A2>::type&)(a2)
            ))
    {}
    
    template <class A1, class A2, class A3>
    pointer_holder(PyObject*, A1 a1, A2 a2, A3 a3)
        : m_p(new Value(
            (typename unwrap_reference<A1>::type&)(a1)
            , (typename unwrap_reference<A2>::type&)(a2)
            , (typename unwrap_reference<A3>::type&)(a3)
            ))
    {}
    
    template <class A1, class A2, class A3, class A4>
    pointer_holder(PyObject*, A1 a1, A2 a2, A3 a3, A4 a4)
        : m_p(new Value(
            (typename unwrap_reference<A1>::type&)(a1)
            , (typename unwrap_reference<A2>::type&)(a2)
            , (typename unwrap_reference<A3>::type&)(a3)
            , (typename unwrap_reference<A4>::type&)(a4)
            ))
    {}
    
    template <class A1, class A2, class A3, class A4, class A5>
    pointer_holder(PyObject*, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5)
        : m_p(new Value(
            (typename unwrap_reference<A1>::type&)(a1)
            , (typename unwrap_reference<A2>::type&)(a2)
            , (typename unwrap_reference<A3>::type&)(a3)
            , (typename unwrap_reference<A4>::type&)(a4)
            , (typename unwrap_reference<A5>::type&)(a5)
            )) {}
    
    template <class A1, class A2, class A3, class A4, class A5, class A6>
    pointer_holder(PyObject*, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6)
        : m_p(new Value(
            (typename unwrap_reference<A1>::type&)(a1)
            , (typename unwrap_reference<A2>::type&)(a2)
            , (typename unwrap_reference<A3>::type&)(a3)
            , (typename unwrap_reference<A4>::type&)(a4)
            , (typename unwrap_reference<A5>::type&)(a5)
            , (typename unwrap_reference<A6>::type&)(a6)
            )) {}
    
    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7>
    pointer_holder(PyObject*, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7)
        : m_p(new Value(
            (typename unwrap_reference<A1>::type&)(a1)
            , (typename unwrap_reference<A2>::type&)(a2)
            , (typename unwrap_reference<A3>::type&)(a3)
            , (typename unwrap_reference<A4>::type&)(a4)
            , (typename unwrap_reference<A5>::type&)(a5)
            , (typename unwrap_reference<A6>::type&)(a6)
            , (typename unwrap_reference<A7>::type&)(a7)
            ))
    {}
    
    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
    pointer_holder(PyObject*, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8)
        : m_p(new Value(
            (typename unwrap_reference<A1>::type&)(a1)
            , (typename unwrap_reference<A2>::type&)(a2)
            , (typename unwrap_reference<A3>::type&)(a3)
            , (typename unwrap_reference<A4>::type&)(a4)
            , (typename unwrap_reference<A5>::type&)(a5)
            , (typename unwrap_reference<A6>::type&)(a6)
            , (typename unwrap_reference<A7>::type&)(a7)
            , (typename unwrap_reference<A8>::type&)(a8)
            ))
    {}
    
    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
    pointer_holder(PyObject*, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9)
        : m_p(new Value(
            (typename unwrap_reference<A1>::type&)(a1)
            , (typename unwrap_reference<A2>::type&)(a2)
            , (typename unwrap_reference<A3>::type&)(a3)
            , (typename unwrap_reference<A4>::type&)(a4)
            , (typename unwrap_reference<A5>::type&)(a5)
            , (typename unwrap_reference<A6>::type&)(a6)
            , (typename unwrap_reference<A7>::type&)(a7)
            , (typename unwrap_reference<A8>::type&)(a8)
            , (typename unwrap_reference<A9>::type&)(a9)
            ))
    {}
    
    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10>
    pointer_holder(PyObject*, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10)
        : m_p(new Value(
            (typename unwrap_reference<A1>::type&)(a1)
            , (typename unwrap_reference<A2>::type&)(a2)
            , (typename unwrap_reference<A3>::type&)(a3)
            , (typename unwrap_reference<A4>::type&)(a4)
            , (typename unwrap_reference<A5>::type&)(a5)
            , (typename unwrap_reference<A6>::type&)(a6)
            , (typename unwrap_reference<A7>::type&)(a7)
            , (typename unwrap_reference<A8>::type&)(a8)
            , (typename unwrap_reference<A9>::type&)(a9)
            , (typename unwrap_reference<A10>::type&)(a10)
            ))
    {}

 private: // required holder implementation
    void* holds(converter::undecorated_type_id_t);

 private: // data members
    Pointer m_p;
};

template <class Pointer, class Value, class BackReferenceType>
struct pointer_holder_back_reference : instance_holder
{
    pointer_holder_back_reference(Pointer);
    
    // Forward construction to the held object
    pointer_holder_back_reference(PyObject* p)
        : m_p(new BackReferenceType(p)) {
        (void)instance_finder<BackReferenceType>::registration;
    }


    
    template <class A1>
    pointer_holder_back_reference(PyObject* p, A1 a1)
        : m_p(new BackReferenceType(p
            , (typename unwrap_reference<A1>::type&)(a1)
                  ))
    {
        (void)instance_finder<BackReferenceType>::registration;
    }

    
    template <class A1, class A2>
    pointer_holder_back_reference(PyObject* p, A1 a1, A2 a2)
        : m_p(new BackReferenceType(p
            , (typename unwrap_reference<A1>::type&)(a1)
            , (typename unwrap_reference<A2>::type&)(a2)
            ))
    {
        (void)instance_finder<BackReferenceType>::registration;
    }

    
    template <class A1, class A2, class A3>
    pointer_holder_back_reference(PyObject* p, A1 a1, A2 a2, A3 a3)
        : m_p(new BackReferenceType(p
            , (typename unwrap_reference<A1>::type&)(a1)
            , (typename unwrap_reference<A2>::type&)(a2)
            , (typename unwrap_reference<A3>::type&)(a3)
            ))
    {
        (void)instance_finder<BackReferenceType>::registration;
    }

    
    template <class A1, class A2, class A3, class A4>
    pointer_holder_back_reference(PyObject* p, A1 a1, A2 a2, A3 a3, A4 a4)
        : m_p(new BackReferenceType(p
            , (typename unwrap_reference<A1>::type&)(a1)
            , (typename unwrap_reference<A2>::type&)(a2)
            , (typename unwrap_reference<A3>::type&)(a3)
            , (typename unwrap_reference<A4>::type&)(a4)
            ))
    {
        (void)instance_finder<BackReferenceType>::registration;
    }

    
    template <class A1, class A2, class A3, class A4, class A5>
    pointer_holder_back_reference(PyObject* p, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5)
        : m_p(new BackReferenceType(p
            , (typename unwrap_reference<A1>::type&)(a1)
            , (typename unwrap_reference<A2>::type&)(a2)
            , (typename unwrap_reference<A3>::type&)(a3)
            , (typename unwrap_reference<A4>::type&)(a4)
            , (typename unwrap_reference<A5>::type&)(a5)
            )) {
        (void)instance_finder<BackReferenceType>::registration;
    }

    
    template <class A1, class A2, class A3, class A4, class A5, class A6>
    pointer_holder_back_reference(PyObject* p, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6)
        : m_p(new BackReferenceType(p
            , (typename unwrap_reference<A1>::type&)(a1)
            , (typename unwrap_reference<A2>::type&)(a2)
            , (typename unwrap_reference<A3>::type&)(a3)
            , (typename unwrap_reference<A4>::type&)(a4)
            , (typename unwrap_reference<A5>::type&)(a5)
            , (typename unwrap_reference<A6>::type&)(a6)
            )) {
        (void)instance_finder<BackReferenceType>::registration;
    }

    
    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7>
    pointer_holder_back_reference(PyObject* p, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7)
        : m_p(new BackReferenceType(p
            , (typename unwrap_reference<A1>::type&)(a1)
            , (typename unwrap_reference<A2>::type&)(a2)
            , (typename unwrap_reference<A3>::type&)(a3)
            , (typename unwrap_reference<A4>::type&)(a4)
            , (typename unwrap_reference<A5>::type&)(a5)
            , (typename unwrap_reference<A6>::type&)(a6)
            , (typename unwrap_reference<A7>::type&)(a7)
            ))
    {
        (void)instance_finder<BackReferenceType>::registration;
    }

    
    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
    pointer_holder_back_reference(PyObject* p, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8)
        : m_p(new BackReferenceType(p
            , (typename unwrap_reference<A1>::type&)(a1)
            , (typename unwrap_reference<A2>::type&)(a2)
            , (typename unwrap_reference<A3>::type&)(a3)
            , (typename unwrap_reference<A4>::type&)(a4)
            , (typename unwrap_reference<A5>::type&)(a5)
            , (typename unwrap_reference<A6>::type&)(a6)
            , (typename unwrap_reference<A7>::type&)(a7)
            , (typename unwrap_reference<A8>::type&)(a8)
            ))
    {
        (void)instance_finder<BackReferenceType>::registration;
    }

    
    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
    pointer_holder_back_reference(PyObject* p, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9)
        : m_p(new BackReferenceType(p
            , (typename unwrap_reference<A1>::type&)(a1)
            , (typename unwrap_reference<A2>::type&)(a2)
            , (typename unwrap_reference<A3>::type&)(a3)
            , (typename unwrap_reference<A4>::type&)(a4)
            , (typename unwrap_reference<A5>::type&)(a5)
            , (typename unwrap_reference<A6>::type&)(a6)
            , (typename unwrap_reference<A7>::type&)(a7)
            , (typename unwrap_reference<A8>::type&)(a8)
            , (typename unwrap_reference<A9>::type&)(a9)
            ))
    {
        (void)instance_finder<BackReferenceType>::registration;
    }

    
    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10>
    pointer_holder_back_reference(PyObject* p, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10)
        : m_p(new BackReferenceType(p
            , (typename unwrap_reference<A1>::type&)(a1)
            , (typename unwrap_reference<A2>::type&)(a2)
            , (typename unwrap_reference<A3>::type&)(a3)
            , (typename unwrap_reference<A4>::type&)(a4)
            , (typename unwrap_reference<A5>::type&)(a5)
            , (typename unwrap_reference<A6>::type&)(a6)
            , (typename unwrap_reference<A7>::type&)(a7)
            , (typename unwrap_reference<A8>::type&)(a8)
            , (typename unwrap_reference<A9>::type&)(a9)
            , (typename unwrap_reference<A10>::type&)(a10)
            ))
    {
        (void)instance_finder<BackReferenceType>::registration;
    }


 private: // required holder implementation
    void* holds(converter::undecorated_type_id_t);

 private: // data members
    Pointer m_p;
};

}}} // namespace boost::python::objects

// back to namespace boost for this forward declaration
namespace boost
{
  template <class T> class shared_ptr;
}

namespace boost { namespace python { namespace objects {

struct shared_ptr_generator
{
    template <class T>
    struct apply
    {
        typedef boost::shared_ptr<T> type;
    };
};

struct no_back_reference;

// Workaround lack of partial specialization
namespace detail
{
  template <class BackReferenceType, class PointerGenerator>
  struct pointer_holder_back_reference_generator
  {
      template <class Held>
      struct apply
      {
          typedef typename mpl::apply1<
              PointerGenerator,BackReferenceType
              >::type pointer;
              
          typedef pointer_holder_back_reference<pointer,Held,BackReferenceType> type;
      };
  };

  template <class PointerGenerator>
  struct plain_pointer_holder_generator
  {
      template <class Held>
      struct apply
      {
          typedef typename mpl::apply1<
              PointerGenerator,Held
              >::type pointer;
              
          typedef pointer_holder<pointer, Held> type;
      };
  };
}

// A generator metafunction which can be passed to make_holder
// PointerGenerator should be another generator metafunction which
// makes the appropriate (smart) pointer type to hold the argument to
// pointer_holder_generator.
template <class PointerGenerator, class BackReferenceType = no_back_reference>
struct pointer_holder_generator
    : mpl::select_type<
          is_same<BackReferenceType,no_back_reference>::value
          , detail::plain_pointer_holder_generator<
                PointerGenerator>
          , detail::pointer_holder_back_reference_generator<
                BackReferenceType,PointerGenerator>
      >::type
{
};

template <class Pointer, class Value>
pointer_holder<Pointer,Value>::pointer_holder(Pointer p)
    : m_p(p)
{
}

template <class Pointer, class Value>
void* pointer_holder<Pointer, Value>::holds(converter::undecorated_type_id_t dst_t)
{
    if (dst_t == converter::undecorated_type_id<Pointer>())
        return &this->m_p;

    converter::type_id_t src_t = converter::undecorated_type_id<Value>();
    return src_t == dst_t ? &*this->m_p
        : find_dynamic_type(&*this->m_p, src_t, dst_t);
}

}}} // namespace boost::python::objects

#endif // POINTER_HOLDER_DWA20011215_HPP
