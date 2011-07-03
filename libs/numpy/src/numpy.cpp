#define BOOST_NUMPY_INTERNAL_MAIN
#include <boost/numpy/internal.hpp>

namespace boost 
{
namespace numpy 
{

void initialize() 
{
  import_array();
  import_ufunc();
}

}
}
