// Copyright David Abrahams 2001. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef POINTER_HOLDER_DWA20011215_HPP
# define POINTER_HOLDER_DWA20011215_HPP

# include <boost/python/object/class.hpp>
# include <boost/python/type_id.hpp>
# include <boost/python/object/inheritance.hpp>
# include <boost/python/object/find_instance.hpp>
# include <boost/python/object/forward.hpp>
# include <boost/type.hpp>
# include <boost/mpl/select_type.hpp>
# include <boost/mpl/apply.hpp>
# include <boost/python/pointee.hpp>
# include <boost/python/detail/preprocessor.hpp>
# include <boost/preprocessor/enum_params.hpp>

namespace boost { namespace python { namespace objects { 

template <class Pointer, class Value>
struct pointer_holder : instance_holder
{
    pointer_holder(Pointer);

    // Forward construction to the held object
# ifndef BOOST_PYTHON_GENERATE_CODE
#  include <boost/python/preprocessed/pointer_holder.hpp>
# endif 


# define BOOST_PYTHON_CONSTRUCT_POINTER_HOLDER(nargs, ignored)          \
    BOOST_PP_EXPR_IF(nargs, template <)                                 \
        BOOST_PP_ENUM_PARAMS(nargs, class A)                            \
    BOOST_PP_EXPR_IF(nargs, >)                                          \
    pointer_holder(PyObject*                                            \
                   BOOST_PP_COMMA_IF(nargs)                             \
                   BOOST_PYTHON_ENUM_PARAMS2(nargs, (A,a)))             \
        : m_p(new Value(                                                \
                  BOOST_PP_ENUM(nargs, BOOST_PYTHON_UNFORWARD, nil)     \
            ))                                                          \
    {}

    BOOST_PYTHON_REPEAT_ARITY_2ND(BOOST_PYTHON_CONSTRUCT_POINTER_HOLDER,nil)
        
 private: // required holder implementation
    void* holds(type_info);

 private: // data members
    Pointer m_p;
};

template <class Pointer, class Value>
struct pointer_holder_back_reference : instance_holder
{
 private:
    typedef typename python::pointee<Pointer>::type held_type;
 public:
    
    pointer_holder_back_reference(Pointer);
    
    // Forward construction to the held object
# ifndef BOOST_PYTHON_GENERATE_CODE
#  include <boost/python/preprocessed/ptr_holder_back_reference.hpp>
# endif
    
# define BOOST_PYTHON_CONSTRUCT_POINTER_HOLDER_BACK_REFERENCE(nargs, ignored)   \
    BOOST_PP_EXPR_IF(nargs, template <)                                         \
        BOOST_PP_ENUM_PARAMS(nargs, class A)                                    \
    BOOST_PP_EXPR_IF(nargs, >)                                                  \
    pointer_holder_back_reference(PyObject* p                                   \
                   BOOST_PP_COMMA_IF(nargs)                                     \
                   BOOST_PYTHON_ENUM_PARAMS2(nargs, (A,a)))                     \
        : m_p(new held_type(                                                    \
                    p BOOST_PP_COMMA_IF(nargs)                                  \
                    BOOST_PP_ENUM(nargs, BOOST_PYTHON_UNFORWARD, nil)           \
            ))                                                                  \
    {                                                                           \
        void const* x = &instance_finder<held_type>::registration; (void)x;     \
    }

    BOOST_PYTHON_REPEAT_ARITY_2ND(BOOST_PYTHON_CONSTRUCT_POINTER_HOLDER_BACK_REFERENCE,nil)

 private: // required holder implementation
    void* holds(type_info);

 private: // data members
    Pointer m_p;
};

template <class Pointer, class Value>
inline pointer_holder<Pointer,Value>::pointer_holder(Pointer p)
    : m_p(p)
{
}

template <class Pointer, class Value>
inline pointer_holder_back_reference<Pointer,Value>::pointer_holder_back_reference(Pointer p)
    : m_p(p)
{
}

template <class Pointer, class Value>
void* pointer_holder<Pointer, Value>::holds(type_info dst_t)
{
    if (dst_t == python::type_id<Pointer>())
        return &this->m_p;

    type_info src_t = python::type_id<Value>();
    return src_t == dst_t ? &*this->m_p
        : find_dynamic_type(&*this->m_p, src_t, dst_t);
}

template <class Pointer, class Value>
void* pointer_holder_back_reference<Pointer, Value>::holds(type_info dst_t)
{
    if (dst_t == python::type_id<Pointer>())
        return &this->m_p;

    if (dst_t == python::type_id<held_type>())
        return &*this->m_p;

    type_info src_t = python::type_id<Value>();
    Value* p = &*this->m_p;
    return src_t == dst_t ? p : find_dynamic_type(p, src_t, dst_t);
}

}}} // namespace boost::python::objects

#endif // POINTER_HOLDER_DWA20011215_HPP
