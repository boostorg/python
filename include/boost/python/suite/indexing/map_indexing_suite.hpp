//  (C) Copyright Joel de Guzman 2003.
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies. This
//  software is provided "as is" without express or implied warranty, and
//  with no claim as to its suitability for any purpose.

#ifndef MAP_INDEXING_SUITE_JDG20038_HPP
# define MAP_INDEXING_SUITE_JDG20038_HPP

# include <boost/python/suite/indexing/indexing_suite.hpp>
# include <boost/python/iterator.hpp>

namespace boost { namespace python {
            
    // Forward declaration
    template <class Container, bool NoProxy, class DerivedPolicies>
    class map_indexing_suite;
    
    namespace detail
    {
        template <class Container, bool NoProxy>
        class final_map_derived_policies 
            : public map_indexing_suite<Container, 
                NoProxy, final_map_derived_policies<Container, NoProxy> > {};
    }

    // The map_indexing_suite class is a predefined indexing_suite derived 
    // class for wrapping std::vector (and std::vector like) classes. It provides
    // all the policies required by the indexing_suite (see indexing_suite).
    // Example usage:
    //
    //  class X {...};
    //
    //  ...
    //
    //      class_<std::map<std::string, X> >("XMap")
    //          .def(map_indexing_suite<std::map<std::string, X> >())
    //      ;
    //
    // By default indexed elements are returned by proxy. This can be
    // disabled by supplying *true* in the NoProxy template parameter.
    //
    template <
        class Container, 
        bool NoProxy = false,
        class DerivedPolicies 
            = detail::final_map_derived_policies<Container, NoProxy> >
    class map_indexing_suite 
        : public indexing_suite<
            Container
          , DerivedPolicies
          , NoProxy
          , true
          , typename Container::mapped_type
          , typename Container::key_type
          , typename Container::key_type
        >
    {
    public:
    
        typedef typename Container::mapped_type data_type;
        typedef typename Container::key_type key_type;
        typedef typename Container::key_type index_type;
        typedef typename Container::size_type size_type;
        typedef typename Container::difference_type difference_type;
        
        template <class Class>
        static void 
        extension_def(Class& cl)
        {
//             cl
//                 .def("append", &base_append)
//                 .def("extend", &base_extend)
//             ;
        }
        
        static data_type& 
        get_item(Container& container, index_type i_)
        { 
            typename Container::iterator i = container.find(i_);
            if (i == container.end())
            {
                PyErr_SetString(PyExc_KeyError, "Invalid key");
                throw_error_already_set();
            }
            return i->second;
        }

        static void 
        set_item(Container& container, index_type i, data_type const& v)
        { 
            container[i] = v;
        }

        static void 
        delete_item(Container& container, index_type i)
        { 
            container.erase(i);
        }
       
        static size_t
        size(Container& container)
        {
            return container.size();
        }
        
        static bool
        contains(Container& container, key_type const& key)
        {
            return container.find(key) != container.end();
        }
        
        static bool 
        compare_index(Container& container, index_type a, index_type b)
        {
            return container.key_comp()(a, b);
        }
                
        static index_type
        convert_index(Container& container, PyObject* i_)
        { 
            extract<key_type const&> i(i_);
            if (i.check())
            {
                return i();
            }
            else
            {
                extract<key_type> i(i_);
                if (i.check())
                    return i();
            }

            PyErr_SetString(PyExc_TypeError, "Invalid index type");
            throw_error_already_set();
            return index_type();
        }
    };
       
}} // namespace boost::python 

#endif // MAP_INDEXING_SUITE_JDG20038_HPP
