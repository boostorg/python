// Copyright David Abrahams 2001. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef MODULE_DWA2001128_HPP
# define MODULE_DWA2001128_HPP

# include <boost/config.hpp>

#if defined(_WIN32) || defined(__CYGWIN__)

# define BOOST_PYTHON_MODULE_INIT(name)                  \
void init_module_##name();                               \
extern "C" __declspec(dllexport) void init##name()       \
{                                                        \
    /*boost::python::handle_exception(*/init_module_##name()/*)*/; \
}                                                        \
void init_module_##name()

#else

# define BOOST_PYTHON_MODULE_INIT(name)                  \
void init_module_##name();                               \
extern "C" void init##name()                             \
{                                                        \
    /*boost::python::handle_exception(*/init_module_##name()/*)*/; \
}                                                        \
void init_module_##name()

#endif

namespace boost { namespace python {

}} // namespace boost::python

#endif // MODULE_DWA2001128_HPP
