// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef FROM_PYTHON_STAGE1_DATA_DWA2002223_HPP
# define FROM_PYTHON_STAGE1_DATA_DWA2002223_HPP

# include <boost/python/converter/from_python_function.hpp>

namespace boost { namespace python { namespace converter { 

struct rvalue_stage1_data
{
    void* convertible;
    constructor_function construct;
};

}}} // namespace boost::python::converter

#endif // FROM_PYTHON_STAGE1_DATA_DWA2002223_HPP
