// Copyright David Abrahams 2004. Distributed under the Boost
// Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#ifndef WRAPPER_DWA2004720_HPP
# define WRAPPER_DWA2004720_HPP

# include <boost/python/detail/wrapper_base.hpp>
# include <boost/python/override.hpp>
# include <boost/python/converter/registered.hpp>
# include <boost/python/detail/sfinae.hpp>

namespace boost { namespace python { 

template <class T>
class wrapper : public detail::wrapper_base
{
#   if defined(BOOST_PYTHON_NO_SFINAE)
 public:
    typedef T _wrapper_wrapped_type_;
#   endif 
 protected:
    override get_override(char const* name) const
    {
        return this->detail::wrapper_base::get_override(
            name, converter::registered<T>::converters.get_class_object());
    }
};

}} // namespace boost::python

#endif // WRAPPER_DWA2004720_HPP
