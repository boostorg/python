  // basics first: const reference converters
  boost::python::tuple const_ivect_reference_as_tuple(const vects::ivect& iv)
  {
    return iv.as_tuple();
  }

  // to_python smart pointer conversions
  std::auto_ptr<vects::ivect> ivect_as_auto_ptr(const vects::ivect& iv)
  {
    return std::auto_ptr<vects::ivect>(new vects::ivect(iv));
  }
  boost::shared_ptr<vects::ivect> ivect_as_shared_ptr(const vects::ivect& iv)
  {
    return boost::shared_ptr<vects::ivect>(new vects::ivect(iv));
  }

  // smart pointers passed by value
  boost::python::ref auto_ptr_value_ivect_as_tuple(std::auto_ptr<vects::ivect> iv)
  {
    if (iv.get() == 0) return boost::python::ref(Py_None, boost::python::ref::increment_count);
    return iv->as_tuple().reference();
  }
  boost::python::ref shared_ptr_value_ivect_as_tuple(boost::shared_ptr<vects::ivect> iv)
  {
    if (iv.get() == 0) return boost::python::ref(Py_None, boost::python::ref::increment_count);
    return iv->as_tuple().reference();
  }

  // smart pointers passed by reference
  boost::python::ref auto_ptr_reference_ivect_as_tuple(std::auto_ptr<vects::ivect>& iv)
  {
    if (iv.get() == 0) return boost::python::ref(Py_None, boost::python::ref::increment_count);
    return iv->as_tuple().reference();
  }
  boost::python::ref shared_ptr_reference_ivect_as_tuple(boost::shared_ptr<vects::ivect>& iv)
  {
    if (iv.get() == 0) return boost::python::ref(Py_None, boost::python::ref::increment_count);
    return iv->as_tuple().reference();
  }

  // smart pointers passed by const reference
  boost::python::ref auto_ptr_const_reference_ivect_as_tuple(const std::auto_ptr<vects::ivect>& iv)
  {
    if (iv.get() == 0) return boost::python::ref(Py_None, boost::python::ref::increment_count);
    return iv->as_tuple().reference();
  }
  boost::python::ref shared_ptr_const_reference_ivect_as_tuple(const boost::shared_ptr<vects::ivect>& iv)
  {
    if (iv.get() == 0) return boost::python::ref(Py_None, boost::python::ref::increment_count);
    return iv->as_tuple().reference();
  }
