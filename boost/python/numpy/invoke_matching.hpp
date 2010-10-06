#ifndef BOOST_PYTHON_NUMPY_INVOKE_MATCHING_HPP_INCLUDED
#define BOOST_PYTHON_NUMPY_INVOKE_MATCHING_HPP_INCLUDED

/**
 *  @file boost/python/numpy/ndarray.hpp
 *  @brief Object manager and various utilities for numpy.ndarray.
 */

#include <boost/python/numpy/dtype.hpp>
#include <boost/python/numpy/ndarray.hpp>

namespace boost { namespace python { namespace numpy {

namespace detail {

struct add_pointer_meta {

    template <typename T>
    struct apply {
        typedef typename boost::add_pointer<T>::type type;
    };

};

struct dtype_template_match_found {};
struct nd_template_match_found {};

template <typename Function>
struct dtype_template_invoker {
    
    template <typename T>
    void operator()(T * x) const {
        if (dtype::get_builtin<T>() == m_dtype) {
            m_func.apply(x);
            throw dtype_template_match_found();
        }
    }

    dtype_template_invoker(dtype const & dtype_, Function func) :
        m_dtype(dtype_), m_func(func) {}

private:
    dtype const & m_dtype;
    Function m_func;
};

template <typename Function>
struct dtype_template_invoker< boost::reference_wrapper<Function> > {
    
    template <typename T>
    void operator()(T * x) const {
        if (dtype::get_builtin<T>() == m_dtype) {
            m_func.apply(x);
            throw dtype_template_match_found();
        }
    }

    dtype_template_invoker(dtype const & dtype_, Function & func) :
        m_dtype(dtype_), m_func(func) {}

private:
    dtype const & m_dtype;
    Function & m_func;
};

template <typename Function>
struct nd_template_invoker {
    
    template <typename T>
    void operator()(T * x) const {
        if (m_nd == T::value) {
            m_func.apply(x);
            throw nd_template_match_found();
        }
    }

    nd_template_invoker(int nd, Function func) :
        m_nd(nd), m_func(func) {}

private:
    int m_nd;
    Function m_func;
};

template <typename Function>
struct nd_template_invoker< boost::reference_wrapper<Function> > {
    
    template <typename T>
    void operator()(T * x) const {
        if (m_nd == T::value) {
            m_func.apply(x);
            throw nd_template_match_found();
        }
    }

    nd_template_invoker(int nd, Function & func) :
        m_nd(nd), m_func(func) {}

private:
    int m_nd;
    Function & m_func;
};

} // namespace boost::python::numpy::detail

template <typename Sequence, typename Function>
void invoke_matching_nd(int nd, Function f) {
    detail::nd_template_invoker<Function> invoker(nd, f);
    try {
        boost::mpl::for_each< Sequence, detail::add_pointer_meta >(invoker);
    } catch (detail::nd_template_match_found &) {
        return;
    }
    PyErr_SetString(PyExc_TypeError, "number of dimensions not found in template list.");
    throw_error_already_set();
}

template <typename Sequence, typename Function>
void invoke_matching_dtype(dtype const & dtype_, Function f) {
    detail::dtype_template_invoker<Function> invoker(dtype_, f);
    try {
        boost::mpl::for_each< Sequence, detail::add_pointer_meta >(invoker);
    } catch (detail::dtype_template_match_found &) {
        return;
    }
    PyErr_SetString(PyExc_TypeError, "dtype not found in template list.");
    throw_error_already_set();
}

namespace detail {

template <typename DimSequence, typename Function>
struct array_template_invoker_wrapper {

    template <typename T>
    void apply(T * x) const {
        invoke_matching_nd<DimSequence>(m_nd, m_func.nest(x));
    }

    array_template_invoker_wrapper(int nd, Function func) :
        m_nd(nd), m_func(func) {}

private:
    int m_nd;
    Function m_func;
};

template <typename DimSequence, typename Function>
struct array_template_invoker_wrapper< DimSequence, boost::reference_wrapper<Function> > {

    template <typename T>
    void apply(T * x) const {
        invoke_matching_nd<DimSequence>(m_nd, m_func.nest(x));
    }

    array_template_invoker_wrapper(int nd, Function & func) :
        m_nd(nd), m_func(func) {}

private:
    int m_nd;
    Function & m_func;
};

} // namespace boost::python::numpy::detail

template <typename TypeSequence, typename DimSequence, typename Function>
void invoke_matching_array(ndarray const & array_, Function f) {
    detail::array_template_invoker_wrapper<DimSequence,Function> wrapper(array_.get_nd(), f);
    invoke_matching_dtype<TypeSequence>(array_.get_dtype(), wrapper);
}


}}} // namespace boost::python::numpy

#endif // !BOOST_PYTHON_NUMPY_INVOKE_MATCHING_HPP_INCLUDED
