    this_module.def(ivect_as_auto_ptr, "ivect_as_auto_ptr");
    this_module.def(ivect_as_shared_ptr, "ivect_as_shared_ptr");

    this_module.def(const_ivect_reference_as_tuple, "const_ivect_reference_as_tuple");

    this_module.def(auto_ptr_value_ivect_as_tuple, "auto_ptr_value_ivect_as_tuple");
    this_module.def(shared_ptr_value_ivect_as_tuple, "shared_ptr_value_ivect_as_tuple");

    this_module.def(auto_ptr_reference_ivect_as_tuple, "auto_ptr_reference_ivect_as_tuple");
    this_module.def(shared_ptr_reference_ivect_as_tuple, "shared_ptr_reference_ivect_as_tuple");

    this_module.def(auto_ptr_const_reference_ivect_as_tuple, "auto_ptr_const_reference_ivect_as_tuple");
    this_module.def(shared_ptr_const_reference_ivect_as_tuple, "shared_ptr_const_reference_ivect_as_tuple");
