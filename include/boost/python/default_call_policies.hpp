// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef DEFAULT_CALL_POLICIES_DWA2002131_HPP
# define DEFAULT_CALL_POLICIES_DWA2002131_HPP
# include <boost/python/detail/wrap_python.hpp>
# include <boost/mpl/select_type.hpp>

namespace boost { namespace python { 

template <class T> struct to_python;

namespace detail
{
// for "readable" error messages
  template <class T> struct specify_a_result_policy_to_wrap_functions_returning
# if defined(__GNUC__) && __GNUC__ >= 3 || defined(__EDG__)
  {}
# endif 
  ;
}

struct default_result_converter;

struct default_call_policies
{
    // Nothing to do
    static bool precall(PyObject*)
    {
        return true;
    }

    // Pass the result through
    static PyObject* postcall(PyObject*, PyObject* result)
    {
        return result;
    }

    typedef default_result_converter result_converter;
};

struct default_result_converter
{
    template <class R>
    struct apply
    {
        typedef typename mpl::select_type<
            is_reference<R>::value | is_pointer<R>::value
            , detail::specify_a_result_policy_to_wrap_functions_returning<R>
            , to_python<R>
        >::type type;
    };
};

// Exceptions for c strings an PyObject*s
template <>
struct default_result_converter::apply<char const*>
{
    typedef boost::python::to_python<char const*> type;
};

template <>
struct default_result_converter::apply<PyObject*>
{
    typedef boost::python::to_python<PyObject*> type;
};

}} // namespace boost::python

#endif // DEFAULT_CALL_POLICIES_DWA2002131_HPP
