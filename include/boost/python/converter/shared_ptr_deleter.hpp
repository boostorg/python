// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef SHARED_PTR_DELETER_DWA2002121_HPP
# define SHARED_PTR_DELETER_DWA2002121_HPP

namespace boost { namespace python { namespace converter { 

struct shared_ptr_deleter
{
    shared_ptr_deleter(handle<> owner)
        : owner(owner) {}

    void operator()(void const*) { owner.reset(); }
        
    handle<> owner;
};

}}} // namespace boost::python::converter

#endif // SHARED_PTR_DELETER_DWA2002121_HPP
