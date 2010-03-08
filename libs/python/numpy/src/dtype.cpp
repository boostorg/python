#define BOOST_PYTHON_NUMPY_INTERNAL
#include <boost/python/numpy/internal.hpp>

#define NUMPY_DTYPE_TRAITS_BUILTIN(ctype,code)                          \
    template <> struct dtype_traits<ctype> {                            \
        static dtype get() {                                            \
            return dtype(                                               \
                python::detail::new_reference(                          \
                    reinterpret_cast<PyObject*>(PyArray_DescrFromType(code)) \
                )                                                       \
            );                                                          \
        }                                                               \
    };                                                                  \
    template dtype dtype::get_builtin<ctype>()

#define NUMPY_DTYPE_TRAITS_COMPLEX(creal, ctype, code)                  \
    template <> struct dtype_traits< std::complex<creal> > {            \
        static dtype get() {                                            \
            if (sizeof(ctype) != sizeof(std::complex<creal>)) {         \
                PyErr_SetString(PyExc_TypeError, "Cannot reinterpret std::complex<T> as T[2]"); \
                throw_error_already_set();                              \
            }                                                           \
            return dtype(                                               \
                python::detail::new_reference(                          \
                    reinterpret_cast<PyObject*>(PyArray_DescrFromType(code)) \
                )                                                       \
            );                                                          \
        }                                                               \
    };                                                                  \
    template dtype dtype::get_builtin< std::complex<creal> >()

namespace boost { namespace python {
namespace numpy {

template <typename T> struct dtype_traits;

python::detail::new_reference dtype::convert(object const & arg, bool align) {
    PyArray_Descr* obj=NULL;
    if (align) {
        if (PyArray_DescrAlignConverter(arg.ptr(), &obj) < 0)
            throw_error_already_set();
    } else {
        if (PyArray_DescrConverter(arg.ptr(), &obj) < 0)
            throw_error_already_set();
    }
    return python::detail::new_reference(reinterpret_cast<PyObject*>(obj));
}

int dtype::get_itemsize() const {
    return reinterpret_cast<PyArray_Descr*>(ptr())->elsize;
}

template <typename T>
dtype dtype::get_builtin() { return dtype_traits<T>::get(); }

NUMPY_DTYPE_TRAITS_BUILTIN(npy_ubyte, NPY_UBYTE);
NUMPY_DTYPE_TRAITS_BUILTIN(npy_byte, NPY_BYTE);
NUMPY_DTYPE_TRAITS_BUILTIN(npy_ushort, NPY_USHORT);
NUMPY_DTYPE_TRAITS_BUILTIN(npy_short, NPY_SHORT);
NUMPY_DTYPE_TRAITS_BUILTIN(npy_uint, NPY_UINT);
NUMPY_DTYPE_TRAITS_BUILTIN(npy_int, NPY_INT);
NUMPY_DTYPE_TRAITS_BUILTIN(npy_ulong, NPY_ULONG);
NUMPY_DTYPE_TRAITS_BUILTIN(npy_long, NPY_LONG);
NUMPY_DTYPE_TRAITS_BUILTIN(npy_float, NPY_FLOAT);
NUMPY_DTYPE_TRAITS_BUILTIN(npy_double, NPY_DOUBLE);
NUMPY_DTYPE_TRAITS_BUILTIN(npy_longdouble, NPY_LONGDOUBLE);
NUMPY_DTYPE_TRAITS_BUILTIN(npy_cfloat, NPY_CFLOAT);
NUMPY_DTYPE_TRAITS_BUILTIN(npy_cdouble, NPY_CDOUBLE);
NUMPY_DTYPE_TRAITS_BUILTIN(npy_clongdouble, NPY_CLONGDOUBLE);
NUMPY_DTYPE_TRAITS_COMPLEX(float, npy_cfloat, NPY_CFLOAT);
NUMPY_DTYPE_TRAITS_COMPLEX(double, npy_cdouble, NPY_CDOUBLE);
NUMPY_DTYPE_TRAITS_COMPLEX(long double, npy_clongdouble, NPY_CLONGDOUBLE);

template <> struct dtype_traits<bool> {
    static dtype get() {
	if (sizeof(bool) == sizeof(npy_bool)) return dtype_traits<npy_bool>::get();
	if (sizeof(bool) == sizeof(npy_ubyte)) return dtype_traits<npy_ubyte>::get();
	PyErr_SetString(PyExc_TypeError, "Cannot determine numpy dtype corresponding to C++ bool.");
        throw_error_already_set();
    }
};
template dtype dtype::get_builtin<bool>();

}}} // namespace boost::python::numpy
