// Copyright David Abrahams 2001. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef VALUE_HOLDER_DWA20011215_HPP
# define VALUE_HOLDER_DWA20011215_HPP

# include <boost/python/object/value_holder_fwd.hpp>
# include <boost/python/object/class.hpp>
# include <boost/python/type_id.hpp>
# include <boost/python/object/inheritance.hpp>
# include <boost/python/object/find_instance.hpp>
# include <boost/python/object/forward.hpp>
# include <boost/python/detail/preprocessor.hpp>
# include <boost/preprocessor/enum_params.hpp>

namespace boost { namespace python { namespace objects { 

template <class Held>
struct value_holder : instance_holder
{
    // Forward construction to the held object
# ifndef BOOST_PYTHON_GENERATE_CODE
#  include <boost/python/preprocessed/value_holder.hpp>
# endif 

# define BOOST_PYTHON_CONSTRUCT_VALUE_HOLDER(nargs, ignored)  \
    BOOST_PP_EXPR_IF(nargs, template <)                         \
        BOOST_PP_ENUM_PARAMS(nargs, class A)                    \
    BOOST_PP_EXPR_IF(nargs, >)                                  \
    value_holder(PyObject*                                      \
                   BOOST_PP_COMMA_IF(nargs)                     \
                   BOOST_PYTHON_ENUM_PARAMS2(nargs, (A,a)))     \
        : m_held(                                               \
            BOOST_PP_ENUM(nargs, BOOST_PYTHON_UNFORWARD, nil)   \
            )                                                   \
    {}

    BOOST_PYTHON_REPEAT_ARITY_2ND(BOOST_PYTHON_CONSTRUCT_VALUE_HOLDER,nil)

 private: // required holder implementation
    void* holds(type_info);

 private: // data members
    Held m_held;
};

template <class Held, class BackReferenceType>
struct value_holder_back_reference : instance_holder
{
    // Forward construction to the held object
# ifndef BOOST_PYTHON_GENERATE_CODE
#  include <boost/python/preprocessed/value_holder_back_reference.hpp>
# endif
    
# define BOOST_PYTHON_CONSTRUCT_VALUE_HOLDER_BACK_REFERENCE(nargs, ignored)             \
    BOOST_PP_EXPR_IF(nargs, template <)                                                 \
        BOOST_PP_ENUM_PARAMS(nargs, class A)                                            \
    BOOST_PP_EXPR_IF(nargs, >)                                                          \
    value_holder_back_reference(PyObject* p                                             \
                   BOOST_PP_COMMA_IF(nargs)                                             \
                   BOOST_PYTHON_ENUM_PARAMS2(nargs, (A,a)))                             \
        : m_held(                                                                       \
            p BOOST_PP_COMMA_IF(nargs)                                                  \
            BOOST_PP_ENUM(nargs, BOOST_PYTHON_UNFORWARD, nil)                           \
            )                                                                           \
    {                                                                                   \
        void const* x = &instance_finder<BackReferenceType>::registration; (void)x;     \
    }

    BOOST_PYTHON_REPEAT_ARITY_2ND(BOOST_PYTHON_CONSTRUCT_VALUE_HOLDER_BACK_REFERENCE,nil)
    
 private: // required holder implementation
    void* holds(type_info);

 private: // data members
    BackReferenceType m_held;
};

template <class Held>
void* value_holder<Held>::holds(type_info dst_t)
{
    type_info src_t = python::type_id<Held>();
    return src_t == dst_t ? &m_held
        : find_static_type(&m_held, src_t, dst_t);
}

template <class Held, class BackReferenceType>
void* value_holder_back_reference<Held,BackReferenceType>::holds(
    type_info dst_t)
{
    type_info src_t = python::type_id<Held>();
    if (src_t == dst_t)
    {
        Held* x = &m_held;
        return x;
    }

    src_t = python::type_id<BackReferenceType>();
    return src_t == dst_t
        ? &m_held
        :  find_static_type(&m_held, src_t, dst_t);
}

}}} // namespace boost::python::objects

#endif // VALUE_HOLDER_DWA20011215_HPP
