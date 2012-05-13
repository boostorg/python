#define BOOST_NUMPY_INTERNAL_MAIN
#include <boost/numpy/internal.hpp>
#include <boost/numpy/dtype.hpp>

namespace boost 
{
namespace numpy 
{

void initialize(bool register_scalar_converters) 
{
  import_array();
  import_ufunc();
  if (register_scalar_converters)
	dtype::register_scalar_converters();
}

}
}
