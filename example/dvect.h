#ifndef DVECT_H
#define DVECT_H

#include <vector>
#include <boost/python/class_builder.hpp>

namespace vects {

  struct dvect : public std::vector<double>
  {
    dvect() : std::vector<double>() {}
    dvect(size_t n) : std::vector<double>(n) {}
    dvect(boost::python::tuple tuple) : std::vector<double>(tuple.size())
    {
      std::vector<double>::iterator v_it = begin();
      for (int i = 0; i < tuple.size(); i++)
        v_it[i] = BOOST_PYTHON_CONVERSION::from_python(tuple[i].get(),
          boost::python::type<double>());
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

#endif // DVECT_H
