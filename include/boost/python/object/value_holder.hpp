// Copyright David Abrahams 2001. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef VALUE_HOLDER_DWA20011215_HPP
# define VALUE_HOLDER_DWA20011215_HPP

# include <boost/python/object/class.hpp>
# include <boost/python/converter/type_id.hpp>
# include <boost/python/object/inheritance.hpp>
# include <boost/ref.hpp>

namespace boost { namespace python { namespace objects { 

template <class Held>
struct value_holder : instance_holder
{
    // Forward construction to the held object
    value_holder(PyObject*)
        : m_held() {}
    
    template <class A1>
    value_holder(PyObject*, A1 a1)
        : m_held(
            (unwrap_reference<A1>::type&)(a1)
            )
    {}
    
    template <class A1, class A2>
    value_holder(PyObject*, A1 a1, A2 a2)
        : m_held(
            (unwrap_reference<A1>::type&)(a1)
            , (unwrap_reference<A2>::type&)(a2)
            )
    {}
    
    template <class A1, class A2, class A3>
    value_holder(PyObject*, A1 a1, A2 a2, A3 a3)
        : m_held(
            (unwrap_reference<A1>::type&)(a1)
            , (unwrap_reference<A2>::type&)(a2)
            , (unwrap_reference<A3>::type&)(a3)
            )
    {}
    
    template <class A1, class A2, class A3, class A4>
    value_holder(PyObject*, A1 a1, A2 a2, A3 a3, A4 a4)
        : m_held(
            (unwrap_reference<A1>::type&)(a1)
            , (unwrap_reference<A2>::type&)(a2)
            , (unwrap_reference<A3>::type&)(a3)
            , (unwrap_reference<A4>::type&)(a4)
            )
    {}
    
    template <class A1, class A2, class A3, class A4, class A5>
    value_holder(PyObject*, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5)
        : m_held(
            (unwrap_reference<A1>::type&)(a1)
            , (unwrap_reference<A2>::type&)(a2)
            , (unwrap_reference<A3>::type&)(a3)
            , (unwrap_reference<A4>::type&)(a4)
            , (unwrap_reference<A5>::type&)(a5)
            ) {}
    
    template <class A1, class A2, class A3, class A4, class A5, class A6>
    value_holder(PyObject*, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6)
        : m_held(
            (unwrap_reference<A1>::type&)(a1)
            , (unwrap_reference<A2>::type&)(a2)
            , (unwrap_reference<A3>::type&)(a3)
            , (unwrap_reference<A4>::type&)(a4)
            , (unwrap_reference<A5>::type&)(a5)
            , (unwrap_reference<A6>::type&)(a6)
            ) {}
    
    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7>
    value_holder(PyObject*, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7)
        : m_held(
            (unwrap_reference<A1>::type&)(a1)
            , (unwrap_reference<A2>::type&)(a2)
            , (unwrap_reference<A3>::type&)(a3)
            , (unwrap_reference<A4>::type&)(a4)
            , (unwrap_reference<A5>::type&)(a5)
            , (unwrap_reference<A6>::type&)(a6)
            , (unwrap_reference<A7>::type&)(a7)
            )
    {}
    
    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
    value_holder(PyObject*, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8)
        : m_held(
            (unwrap_reference<A1>::type&)(a1)
            , (unwrap_reference<A2>::type&)(a2)
            , (unwrap_reference<A3>::type&)(a3)
            , (unwrap_reference<A4>::type&)(a4)
            , (unwrap_reference<A5>::type&)(a5)
            , (unwrap_reference<A6>::type&)(a6)
            , (unwrap_reference<A7>::type&)(a7)
            , (unwrap_reference<A8>::type&)(a8)
            )
    {}
    
    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
    value_holder(PyObject*, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9)
        : m_held(
            (unwrap_reference<A1>::type&)(a1)
            , (unwrap_reference<A2>::type&)(a2)
            , (unwrap_reference<A3>::type&)(a3)
            , (unwrap_reference<A4>::type&)(a4)
            , (unwrap_reference<A5>::type&)(a5)
            , (unwrap_reference<A6>::type&)(a6)
            , (unwrap_reference<A7>::type&)(a7)
            , (unwrap_reference<A8>::type&)(a8)
            , (unwrap_reference<A9>::type&)(a9)
            )
    {}
    
    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10>
    value_holder(PyObject*, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10)
        : m_held(
            (unwrap_reference<A1>::type&)(a1)
            , (unwrap_reference<A2>::type&)(a2)
            , (unwrap_reference<A3>::type&)(a3)
            , (unwrap_reference<A4>::type&)(a4)
            , (unwrap_reference<A5>::type&)(a5)
            , (unwrap_reference<A6>::type&)(a6)
            , (unwrap_reference<A7>::type&)(a7)
            , (unwrap_reference<A8>::type&)(a8)
            , (unwrap_reference<A9>::type&)(a9)
            , (unwrap_reference<A10>::type&)(a10)
            )
    {}

 private: // required holder implementation
    void* holds(converter::type_id_t);

 private: // data members
    Held m_held;
};

// A generator metafunction which can be passed to make_holder
struct value_holder_generator
{
    template <class Held>
    struct apply
    {
        typedef value_holder<Held> type;
    };
};

template <class Held>
void* value_holder<Held>::holds(converter::type_id_t dst_t)
{
    converter::type_id_t src_t = converter::type_id<Held>();
    return src_t == dst_t ? &m_held
        : find_static_type(&m_held, src_t, dst_t);
}

}}} // namespace boost::python::objects

#endif // VALUE_HOLDER_DWA20011215_HPP
