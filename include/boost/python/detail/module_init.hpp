// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifdef BOOST_PYTHON_V2
# error obsolete
#endif 
#ifndef MODULE_INIT_DWA2002529_HPP
# define MODULE_INIT_DWA2002529_HPP

# ifndef BOOST_PYTHON_MODULE_INIT

#  if defined(_WIN32) || defined(__CYGWIN__)

#   define BOOST_PYTHON_MODULE_INIT(name)                       \
void init_module_##name();                                      \
extern "C" __declspec(dllexport) void init##name()              \
{                                                               \
    boost::python::handle_exception(&init_module_##name);       \
}                                                               \
void init_module_##name()

#  elif defined(_AIX)

#   include <boost/python/detail/aix_init_module.hpp>
#   define BOOST_PYTHON_MODULE_INIT(name)                                                               \
void init_module_##name();                                                                              \
extern "C"                                                                                              \
{                                                                                                       \
    extern PyObject* _PyImport_LoadDynamicModule(char*, char*, FILE *);                                 \
    void init##name()                                                                                   \
    {                                                                                                   \
        boost::python::detail::aix_init_module(_PyImport_LoadDynamicModule, &init_module_##name);       \
    }                                                                                                   \
}                                                                                                       \
void init_module_##name()

# else

#   define BOOST_PYTHON_MODULE_INIT(name)                       \
void init_module_##name();                                      \
extern "C"  void init##name()                                   \
{                                                               \
    boost::python::handle_exception(&init_module_##name);       \
}                                                               \
void init_module_##name()

#  endif

# endif 

#endif // MODULE_INIT_DWA2002529_HPP
