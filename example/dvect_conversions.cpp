  // basics first: const reference converters
  boost::python::tuple const_dvect_reference_as_tuple(const vects::dvect& dv)
  {
    return dv.as_tuple();
  }

  // to_python smart pointer conversions
  std::auto_ptr<vects::dvect> dvect_as_auto_ptr(const vects::dvect& dv)
  {
    return std::auto_ptr<vects::dvect>(new vects::dvect(dv));
  }
  boost::shared_ptr<vects::dvect> dvect_as_shared_ptr(const vects::dvect& dv)
  {
    return boost::shared_ptr<vects::dvect>(new vects::dvect(dv));
  }

  // smart pointers passed by value
  boost::python::ref auto_ptr_value_dvect_as_tuple(std::auto_ptr<vects::dvect> dv)
  {
    if (dv.get() == 0) return boost::python::ref(Py_None, boost::python::ref::increment_count);
    return dv->as_tuple().reference();
  }
  boost::python::ref shared_ptr_value_dvect_as_tuple(boost::shared_ptr<vects::dvect> dv)
  {
    if (dv.get() == 0) return boost::python::ref(Py_None, boost::python::ref::increment_count);
    return dv->as_tuple().reference();
  }

  // smart pointers passed by reference
  boost::python::ref auto_ptr_reference_dvect_as_tuple(std::auto_ptr<vects::dvect>& dv)
  {
    if (dv.get() == 0) return boost::python::ref(Py_None, boost::python::ref::increment_count);
    return dv->as_tuple().reference();
  }
  boost::python::ref shared_ptr_reference_dvect_as_tuple(boost::shared_ptr<vects::dvect>& dv)
  {
    if (dv.get() == 0) return boost::python::ref(Py_None, boost::python::ref::increment_count);
    return dv->as_tuple().reference();
  }

  // smart pointers passed by const reference
  boost::python::ref auto_ptr_const_reference_dvect_as_tuple(const std::auto_ptr<vects::dvect>& dv)
  {
    if (dv.get() == 0) return boost::python::ref(Py_None, boost::python::ref::increment_count);
    return dv->as_tuple().reference();
  }
  boost::python::ref shared_ptr_const_reference_dvect_as_tuple(const boost::shared_ptr<vects::dvect>& dv)
  {
    if (dv.get() == 0) return boost::python::ref(Py_None, boost::python::ref::increment_count);
    return dv->as_tuple().reference();
  }
