// Copyright Jason Newton 2015
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#ifndef ALIGNMENT_OF_DWA2003224_HPP
# define ALIGNMENT_OF_DWA2003224_HPP

# include <boost/align/alignment_of.hpp>
# include <memory>

namespace boost { namespace python { namespace detail {

    //allow users to override the alignment through partial template specialization/SFINAE
    template<typename T, class Enable = void>
    struct alignment_of : public ::boost::alignment::alignment_of<T>{
    };

}}} // namespace boost::python::detail

#endif // ALIGNMENT_OF_DWA2003224_HPP

