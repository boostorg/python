    this_module.def(dvect_as_auto_ptr, "dvect_as_auto_ptr");
    this_module.def(dvect_as_shared_ptr, "dvect_as_shared_ptr");

    this_module.def(const_dvect_reference_as_tuple, "const_dvect_reference_as_tuple");

    this_module.def(auto_ptr_value_dvect_as_tuple, "auto_ptr_value_dvect_as_tuple");
    this_module.def(shared_ptr_value_dvect_as_tuple, "shared_ptr_value_dvect_as_tuple");

    this_module.def(auto_ptr_reference_dvect_as_tuple, "auto_ptr_reference_dvect_as_tuple");
    this_module.def(shared_ptr_reference_dvect_as_tuple, "shared_ptr_reference_dvect_as_tuple");

    this_module.def(auto_ptr_const_reference_dvect_as_tuple, "auto_ptr_const_reference_dvect_as_tuple");
    this_module.def(shared_ptr_const_reference_dvect_as_tuple, "shared_ptr_const_reference_dvect_as_tuple");
