// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef OBJECT_PROTOCOL_CORE_DWA2002615_HPP
# define OBJECT_PROTOCOL_CORE_DWA2002615_HPP

namespace boost { namespace python { 

class object;

BOOST_PYTHON_DECL object getattr(object const& target, object const& key);
BOOST_PYTHON_DECL void setattr(object const& target, object const& key, object const& value);
BOOST_PYTHON_DECL object getitem(object const& target, object const& key);
BOOST_PYTHON_DECL void setitem(object const& target, object const& key, object const& value);

}} // namespace boost::python

#endif // OBJECT_PROTOCOL_CORE_DWA2002615_HPP
