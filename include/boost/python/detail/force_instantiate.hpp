// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef FORCE_INSTANTIATE_DWA200265_HPP
# define FORCE_INSTANTIATE_DWA200265_HPP

namespace boost { namespace python { namespace detail { 

// Allows us to force the argument to be instantiated without
// incurring unused variable warnings
template <class T>
inline void force_instantiate(T const&) {}

}}} // namespace boost::python::detail

#endif // FORCE_INSTANTIATE_DWA200265_HPP
