// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef WRAPPER_BASE_DWA2002110_HPP
# define WRAPPER_BASE_DWA2002110_HPP
# include <boost/python/detail/wrap_python.hpp>
# include <boost/python/converter/body.hpp>

namespace boost { namespace python { namespace converter { 

struct source_holder_base;
struct wrap_base;
template <class T> struct wrap_more_;

struct BOOST_PYTHON_DECL wrapper_base : body
{
 public:
    wrapper_base(type_id_t); // registers
    ~wrapper_base();         // unregisters
    
    virtual PyObject* do_conversion(wrap_base const&, source_holder_base const&) const = 0;
};

}}} // namespace boost::python::converter

#endif // WRAPPER_BASE_DWA2002110_HPP
