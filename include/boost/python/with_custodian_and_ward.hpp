// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef WITH_CUSTODIAN_AND_WARD_DWA2002131_HPP
# define WITH_CUSTODIAN_AND_WARD_DWA2002131_HPP

# include <boost/python/default_call_policies.hpp>
# include <boost/python/object/life_support.hpp>

namespace boost { namespace python { 

enum custodial_timing { pre_call, post_call };
                        
template <std::size_t custodian, std::size_t ward, class Base = default_call_policies>
struct with_custodian_and_ward : Base
{
    static bool precall(PyObject* args);
};

template <std::size_t custodian, std::size_t ward, class Base = default_call_policies>
struct with_custodian_and_ward_postcall : Base
{
    static PyObject* postcall(PyObject* args, PyObject* result);
};

//
// implementations
//
template <std::size_t custodian, std::size_t ward, class Base>
bool with_custodian_and_ward<custodian,ward,Base>::precall(PyObject* args_)
{
    BOOST_STATIC_ASSERT(custodian != ward);
    BOOST_STATIC_ASSERT(custodian > 0);
    BOOST_STATIC_ASSERT(ward > 0);
    
    PyObject* patient = PyTuple_GetItem(args_, ward - 1);
    if (patient == 0) return false;
    PyObject* nurse = PyTuple_GetItem(args_, custodian - 1);
    if (nurse == 0) return false;
    
    PyObject* life_support = python::objects::make_nurse_and_patient(nurse, patient);
    if (life_support == 0)
        return false;
    
    bool result = Base::precall(args_);
    
    if (!result)
        Py_XDECREF(life_support);
    
    return result;
}

template <std::size_t custodian, std::size_t ward, class Base>
PyObject* with_custodian_and_ward_postcall<custodian,ward,Base>::postcall(PyObject* args_, PyObject* result)
{
    BOOST_STATIC_ASSERT(custodian != ward);
    
    PyObject* patient = ward > 0 ? PyTuple_GetItem(args_, ward - 1) : result;
    if (patient == 0) return 0;
    
    PyObject* nurse = custodian > 0 ? PyTuple_GetItem(args_, custodian - 1) : result;
    if (nurse == 0) return 0;
    
    result = Base::postcall(args_, result);
    if (result == 0)
        return 0;
            
    if (python::objects::make_nurse_and_patient(nurse, patient) == 0)
    {
        Py_XDECREF(result);
        return 0;
    }
    return result;
}

}} // namespace boost::python

#endif // WITH_CUSTODIAN_AND_WARD_DWA2002131_HPP
