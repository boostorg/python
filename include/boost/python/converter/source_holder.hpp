// Copyright David Abrahams 2001. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef SOURCE_HOLDER_DWA20011215_HPP
# define SOURCE_HOLDER_DWA20011215_HPP

namespace boost { namespace python { namespace converter { 

struct source_holder_base
{
};

template <class T>
struct source_holder : source_holder_base
{
    source_holder(T x) : value(x) {}
    T value;
};

}}} // namespace boost::python::converter

#endif // SOURCE_HOLDER_DWA20011215_HPP
