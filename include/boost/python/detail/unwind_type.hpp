// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef UNWIND_TYPE_DWA200222_HPP
# define UNWIND_TYPE_DWA200222_HPP

# include <boost/python/detail/cv_category.hpp>

namespace boost { namespace python { namespace detail { 

template <class Generator, class U>
inline typename Generator::result_type
unwind_type_cv(U* p, cv_unqualified, Generator* = 0)
{
    return Generator::execute(p);
}
    
template <class Generator, class U>
inline typename Generator::result_type
unwind_type_cv(U const* p, const_, Generator* = 0)
{
    return unwind_type(const_cast<U*>(p), (Generator*)0);
}
    
template <class Generator, class U>
inline typename Generator::result_type
unwind_type_cv(U volatile* p, volatile_, Generator* = 0)
{
    return unwind_type(const_cast<U*>(p), (Generator*)0);
}
    
template <class Generator, class U>
inline typename Generator::result_type
unwind_type_cv(U const volatile* p, const_volatile_, Generator* = 0)
{
    return unwind_type(const_cast<U*>(p), (Generator*)0);
}
    
template <class Generator, class U>
inline typename Generator::result_type
unwind_ptr_type(U* p, Generator* = 0)
{
    typedef typename cv_category<U>::type tag;
    return unwind_type_cv<Generator>(p, tag());
}

template <bool is_ptr>
struct unwind_helper
{
    template <class Generator, class U>
    static typename Generator::result_type
    execute(U p, Generator* = 0)
    {
        return unwind_ptr_type(p, (Generator*)0);
    }

    template <class Generator, class U>
    struct apply
    {
        static typename Generator::result_type
        execute()
        {
            return unwind_ptr_type(U(0),(Generator*)0);
        }
    };
};

template <>
struct unwind_helper<false>
{
    template <class Generator, class U>
    static typename Generator::result_type
    execute(U& p, Generator* = 0)
    {
        return unwind_ptr_type(&p, (Generator*)0);
    }

    template <class Generator, class U>
    struct apply
    {
        static typename Generator::result_type
        execute()
        {
            return unwind_ptr_type((U*)0,(Generator*)0);
        }
    };
};

template <class Generator, class U>
inline typename Generator::result_type
unwind_type(U& p, Generator* = 0)
{
    return unwind_helper<is_pointer<U>::value>::execute(p, (Generator*)0);
}

template <class Generator, class U>
inline typename Generator::result_type
unwind_type(U const& p, Generator* = 0)
{
    return unwind_helper<is_pointer<U>::value>::execute(p, (Generator*)0);
}

// Call this one with both template parameters explicitly specified
// and no function arguments:
//
//      return unwind_type<my_generator,T>();
//
template <class Generator, class U>
inline typename Generator::result_type
unwind_type(type<U>*p = 0, Generator* = 0)
{
    return unwind_helper<is_pointer<U>::value>::template apply<Generator,U>::execute();
}

}}} // namespace boost::python::detail

#endif // UNWIND_TYPE_DWA200222_HPP
