//  (C) Copyright Joel de Guzman 2003.
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies. This
//  software is provided "as is" without express or implied warranty, and
//  with no claim as to its suitability for any purpose.

#ifndef INDEXING_SUITE_JDG20036_HPP
# define INDEXING_SUITE_JDG20036_HPP

# include <boost/python/class.hpp>
# include <boost/python/register_ptr_to_python.hpp>
# include <boost/python/indexing/detail/indexing_suite_detail.hpp>
# include <boost/python/return_internal_reference.hpp>
# include <boost/python/iterator.hpp>
# include <boost/mpl/or.hpp>
# include <boost/mpl/not.hpp>

namespace boost { namespace python {
            
    // indexing_suite class. This class is the protocol class for
    // the management of C++ containers intended to be integrated
    // to Python. The objective is make a C++ container look and
    // feel and behave exactly as we'd expect a Python container.
    // By default indexed elements are returned by proxy. This can be
    // disabled by supplying *true* in the NoProxy template parameter.
    // 
    // Derived classes provide the hooks needed by the indexing_suite
    // to do its job:
    //
    //      static element_type& 
    //      get_item(Container& container, index_type i);
    //
    //      static object 
    //      get_slice(Container& container, index_type from, index_type to);
    //
    //      static void 
    //      set_item(Container& container, index_type i, element_type const& v);
    //
    //      static void 
    //      set_slice(
    //         Container& container, index_type from, 
    //         index_type to, element_type const& v
    //      );
    //
    //      template <class Iter>
    //      static void 
    //      set_slice(Container& container, index_type from, 
    //          index_type to, Iter first, Iter last
    //      );
    //
    //      static void 
    //      delete_item(Container& container, index_type i);
    //        
    //      static void 
    //      delete_slice(Container& container, index_type from, index_type to);
    //        
    //      static size_t
    //      size(Container& container);
    //
    //      template <class T>
    //      static bool
    //      contains(Container& container, T const& val);
    //        
    //      static index_type
    //      convert_index(Container& container, PyObject* i);
    //        
    //      static index_type
    //      adjust_index(index_type current, index_type from, 
    //          index_type to, size_type len
    //      );
    //
    // Most of these policies are self explanatory. convert_index and 
    // adjust_index, however, deserves some explanation. 
    //
    // convert_index converts an Python index into a C++ index that the 
    // container can handle. For instance, negative indexes in Python, by 
    // convention, indexes from the right (e.g. C[-1] indexes the rightmost 
    // element in C). convert_index should handle the necessary conversion 
    // for the C++ container (e.g. convert -1 to C.size()-1). convert_index
    // should also be able to convert the type of the index (A dynamic Python
    // type) to the actual type that the C++ container expects.
    //
    // When a container expands or contracts, held indexes to its elements
    // must be adjusted to follow the movement of data. For instance, if
    // we erase 3 elements, starting from index 0 from a 5 element vector, 
    // what used to be at index 4 will now be at index 1:
    //
    //      [a][b][c][d][e] ---> [d][e]
    //                   ^           ^
    //                   4           1
    //
    // adjust_index takes care of the adjustment. Given a current index,
    // the function should return the adjusted index when data in the
    // container at index from..to is replaced by *len* elements.
    //
    template <
          class Container
        , class DerivedPolicies
        , bool NoProxy = false
        , class Element = typename Container::value_type
        , class Key = typename Container::value_type
        , class Index = typename Container::size_type
    >
    class indexing_suite 
        : public def_arg<
            indexing_suite<
              Container
            , DerivedPolicies
            , NoProxy
            , Element
            , Key
            , Index
        > >
    {
    private:
        
        typedef mpl::or_<
            mpl::bool_<NoProxy>
          , mpl::not_<is_class<Element> > > 
        no_proxy;
                    
        typedef detail::container_element<Container, Index, DerivedPolicies>
            container_element_t;
       
        typedef typename mpl::if_<
            no_proxy
          , iterator<Container>
          , iterator<Container, return_internal_reference<> > >::type
        def_iterator;
    
        static void
        register_container_element(mpl::false_)
        { 
            register_ptr_to_python<container_element_t>();
        }
        
        static void
        register_container_element(mpl::true_)
        { 
        }

    public:
      
        template <class Class>
        void visit(Class& cl) const
        {
            // Hook into the class_ generic visitation .def function
            register_container_element(no_proxy());
            
            cl
                .def("__len__", base_size)
                .def("__setitem__", &base_set_item)
                .def("__delitem__", &base_delete_item)
                .def("__getitem__", &base_get_item)
                .def("__contains__", &base_contains)
                .def("__iter__", def_iterator())

                .def("append", &base_append)
                .def("extend", &base_extend)
            ;
        }        
        
    private:
           
        static object
        base_get_item_(
            back_reference<Container&> const& container, 
            PyObject* i, mpl::false_)
        { 
            // Proxy  
            Index idx = DerivedPolicies::convert_index(container.get(), i);
            
            if (PyObject* shared = 
                container_element_t::get_links().find(container.get(), idx))
            {
                handle<> h(borrowed(shared));
                return object(h);
            }
            else
            {
                object prox(container_element_t(container.source(), idx));
                container_element_t::
                    get_links().add(prox.ptr(), container.get());
                return prox;
            }
        }

        static object
        base_get_item_(
            back_reference<Container&> const& container, 
            PyObject* i, mpl::true_)
        { 
            // No Proxy
            return object(
                DerivedPolicies::get_item(
                    container.get(), DerivedPolicies::
                        convert_index(container.get(), i)));
        }

        static object
        base_get_item(back_reference<Container&> container, PyObject* i)
        { 
            if (PySlice_Check(i))
                return base_get_slice(
                    container.get(), reinterpret_cast<PySliceObject*>(i));
            
            return base_get_item_(container, i, no_proxy());
         }

        static object 
        base_get_slice(Container& container, PySliceObject* slice)
        { 
            Index from, to;
            base_get_slice_data(container, slice, from, to);
            return DerivedPolicies::get_slice(container, from, to);
        }

        static void
        base_get_slice_data(
            Container& container, PySliceObject* slice, Index& from, Index& to)
        {
            if (Py_None == slice->start)
                from = 0;
            else 
                from = DerivedPolicies::convert_index(container, slice->start);

            if (Py_None == slice->stop)
                to = container.size();
            else 
                to = DerivedPolicies::convert_index(container, slice->stop);
        }        
        
        static void 
        base_set_item(Container& container, PyObject* i, PyObject* v)
        {
            if (PySlice_Check(i))
            {
                 base_set_slice(container, 
                     reinterpret_cast<PySliceObject*>(i), v);
            }
            else
            {
                extract<Element&> elem(v);
                // try if elem is an exact Element
                if (elem.check())
                {
                    DerivedPolicies::
                        set_item(container, 
                            DerivedPolicies::
                                convert_index(container, i), elem());
                }
                else
                {
                    //  try to convert elem to Element
                    extract<Element> elem(v);
                    if (elem.check())
                    {
                        DerivedPolicies::
                            set_item(container, 
                                DerivedPolicies::
                                    convert_index(container, i), elem());
                    }
                    else
                    {
                        PyErr_SetString(PyExc_TypeError, "Invalid assignment");
                        throw_error_already_set();
                    }
                }
            }
        }

        static void
        base_replace_indexes(
            Container& container, Index from, 
            Index to, Index n, mpl::false_)
        {
            //  Proxy
            container_element_t::get_links().replace(container, from, to, n);
        }

        static void
        base_replace_indexes(
            Container& container, Index from, 
            Index to, Index n, mpl::true_)
        {
            //  No Proxy
        }
        
        static void
        base_erase_indexes(
            Container& container, Index from, Index to, mpl::false_)
        {
            //  Proxy
            container_element_t::get_links().erase(container, from, to);
        }

        static void
        base_erase_indexes(
            Container& container, Index from, Index to, mpl::true_)
        {
            //  No Proxy
        }
   
        static void 
        base_set_slice(Container& container, PySliceObject* slice, PyObject* v)
        {
            Index from, to;
            base_get_slice_data(container, slice, from, to);
            
            extract<Element&> elem(v);
            // try if elem is an exact Element
            if (elem.check())
            {
                base_replace_indexes(container, from, to, 1, no_proxy());
                DerivedPolicies::set_slice(container, from, to, elem());
            }
            else
            {
                //  try to convert elem to Element
                extract<Element> elem(v);
                if (elem.check())
                {
                    base_replace_indexes(container, from, to, 1, no_proxy());
                    DerivedPolicies::set_slice(container, from, to, elem());
                }
                else
                {
                    //  Otherwise, it must be a list or some container
                    handle<> l_(borrowed(v));
                    object l(l_);
    
                    std::vector<Element> temp;
                    for (int i = 0; i < l.attr("__len__")(); i++)
                    {
                        object elem(l[i]);
                        extract<Element const&> x(elem);
                        //  try if elem is an exact Element type
                        if (x.check())
                        {
                            temp.push_back(x());
                        }
                        else
                        {
                            //  try to convert elem to Element type
                            extract<Element> x(elem);
                            if (x.check())
                            {
                                temp.push_back(x());
                            }
                            else
                            {
                                PyErr_SetString(PyExc_TypeError, 
                                    "Invalid sequence element");
                                throw_error_already_set();
                            }
                        }
                    }          
                  
                    base_replace_indexes(container, from, to, 
                        temp.end()-temp.begin(), no_proxy());
                    DerivedPolicies::set_slice(container, from, to, 
                        temp.begin(), temp.end());
                }
            }            
        }

        static void 
        base_delete_item(Container& container, PyObject* i)
        {
            if (PySlice_Check(i))
            {
                base_delete_slice(container, reinterpret_cast<PySliceObject*>(i));
                return;
            }
            
            Index index = DerivedPolicies::convert_index(container, i);
            base_erase_indexes(container, index, index+1, no_proxy());
            DerivedPolicies::delete_item(container, index);
        }
        
        static void 
        base_delete_slice(Container& container, PySliceObject* slice)
        { 
            Index from, to;
            base_get_slice_data(container, slice, from, to);
            base_erase_indexes(container, from, to, no_proxy());
            DerivedPolicies::delete_slice(container, from, to);
        }  

        static size_t
        base_size(Container& container)
        {
            return DerivedPolicies::size(container);
        }

        static bool
        base_contains(Container& container, PyObject* key)
        {
            extract<Key const&> x(key);
            //  try if key is an exact Key type
            if (x.check())
            {
                return DerivedPolicies::contains(container, x());
            }
            else
            {
                //  try to convert key to Key type
                extract<Key> x(key);
                if (x.check())
                    return DerivedPolicies::contains(container, x());
                else
                    return false;
            }            
        }
        
        static void
        base_append(Container& container, PyObject* v)
        {
            extract<Element&> elem(v);
            // try if elem is an exact Element
            if (elem.check())
            {
                DerivedPolicies::append(container, elem());
            }
            else
            {
                //  try to convert elem to Element
                extract<Element> elem(v);
                if (elem.check())
                {
                    DerivedPolicies::append(container, elem());
                }
                else
                {
                    PyErr_SetString(PyExc_TypeError, 
                        "Attempting to append an invalid type");
                    throw_error_already_set();
                }
            }
        }
        
        static void
        base_extend(Container& container, PyObject* v)
        {
            //  v must be a list or some container
            handle<> l_(borrowed(v));
            object l(l_);

            std::vector<Element> temp;
            for (int i = 0; i < l.attr("__len__")(); i++)
            {
                object elem(l[i]);
                extract<Element const&> x(elem);
                //  try if elem is an exact Element type
                if (x.check())
                {
                    temp.push_back(x());
                }
                else
                {
                    //  try to convert elem to Element type
                    extract<Element> x(elem);
                    if (x.check())
                    {
                        temp.push_back(x());
                    }
                    else
                    {
                        PyErr_SetString(PyExc_TypeError, 
                            "Invalid list element");
                        throw_error_already_set();
                    }
                }
            }          
          
            DerivedPolicies::extend(container, temp.begin(), temp.end());
        }

        static object 
        get_slice(Container& container, Index from, Index to)
        { 
            // default implementation
            PyErr_SetString(PyExc_RuntimeError, "Slicing not supported");
            throw_error_already_set();
            return object();
        }

        static void 
        set_slice(Container& container, Index from, 
            Index to, Element const& v)
        { 
            // default implementation
            PyErr_SetString(PyExc_RuntimeError, "Slicing not supported");
            throw_error_already_set();
        }

        template <class Iter>
        static void 
        set_slice(Container& container, Index from, 
            Index to, Iter first, Iter last)
        { 
            // default implementation
            PyErr_SetString(PyExc_RuntimeError, "Slicing not supported");
            throw_error_already_set();
        }

        static void 
        delete_slice(Container& container, Index from, Index to)
        { 
            // default implementation
            PyErr_SetString(PyExc_RuntimeError, "Slicing not supported");
            throw_error_already_set();
        }
    };            
       
}} // namespace boost::python 

#endif // INDEXING_SUITE_JDG20036_HPP
