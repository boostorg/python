// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef MODULE_INIT_DWA2002529_HPP
# define MODULE_INIT_DWA2002529_HPP

# ifndef BOOST_PYTHON_MODULE_INIT

#   define PRE_INIT_FUNC(name)                                  \
void init_module_base_##name()                                  \
{                                                               \
    boost::python::detail::module_info mi(#name);               \
    boost::python::detail::module_base::set_module_info(mi);    \
    boost::python::module();                                    \
    init_module_##name();                                       \
}

#  if defined(_WIN32) || defined(__CYGWIN__)

#   define BOOST_PYTHON_MODULE_INIT(name)                       \
void init_module_##name();                                      \
PRE_INIT_FUNC(name)                                             \
extern "C" __declspec(dllexport) void init##name()              \
{                                                               \
    boost::python::handle_exception(&init_module_base_##name);  \
}                                                               \
void init_module_##name()

#  elif defined(_AIX)

#   include <boost/python/detail/aix_init_module.hpp>
#   define BOOST_PYTHON_MODULE_INIT(name)                                                               \
PRE_INIT_FUNC(name)                                                                                     \
void init_module_##name();                                                                              \
extern "C"                                                                                              \
{                                                                                                       \
    extern PyObject* _PyImport_LoadDynamicModule(char*, char*, FILE *);                                 \
    void init##name()                                                                                   \
    {                                                                                                   \
        boost::python::detail::aix_init_module(_PyImport_LoadDynamicModule, &init_module_base_##name);  \
    }                                                                                                   \
}                                                                                                       \
void init_module_##name()

# else

#   define BOOST_PYTHON_MODULE_INIT(name)                       \
PRE_INIT_FUNC(name)                                             \
void init_module_##name();                                      \
extern "C"  void init##name()                                   \
{                                                               \
    boost::python::handle_exception(&init_module_base_##name);  \
}                                                               \
void init_module_##name()

#  endif

# endif 

#endif // MODULE_INIT_DWA2002529_HPP
