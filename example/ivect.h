#ifndef IVECT_H
#define IVECT_H

#include <vector>
#include <boost/python/class_builder.hpp>

namespace vects {

  struct ivect : public std::vector<int>
  {
    ivect() : std::vector<int>() {}
    ivect(size_t n) : std::vector<int>(n) {}
    ivect(boost::python::tuple tuple) : std::vector<int>(tuple.size())
    {
      std::vector<int>::iterator v_it = begin();
      for (int i = 0; i < tuple.size(); i++)
        v_it[i] = BOOST_PYTHON_CONVERSION::from_python(tuple[i].get(),
          boost::python::type<int>());
    }

    boost::python::tuple as_tuple() const
    {
      boost::python::tuple t(size());
      for (int i = 0; i < size(); i++)
        t.set_item(i,
          boost::python::ref(BOOST_PYTHON_CONVERSION::to_python((*this)[i])));
      return t;
    }
  };
}

#endif // IVECT_H
