// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef AUTO_PTR_GENERATOR_DWA2002123_HPP
# define AUTO_PTR_GENERATOR_DWA2002123_HPP
# include <memory>

namespace boost { namespace python { namespace object { 

struct auto_ptr_generator
{
    template <class T>
    struct apply
    {
        typedef std::auto_ptr<T> type;
    };
};

}}} // namespace boost::python::object

#endif // AUTO_PTR_GENERATOR_DWA2002123_HPP
