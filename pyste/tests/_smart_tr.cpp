
// Includes ====================================================================
#include <boost/python.hpp>
#include <smart_ptr.h>

// Using =======================================================================
using namespace boost::python;

// Declarations ================================================================


namespace  {


struct smart_ptr_A_Wrapper: smart_ptr::A
{
    smart_ptr_A_Wrapper(PyObject* self_, const smart_ptr::A & p0):
        smart_ptr::A(p0), self(self_) {}

    smart_ptr_A_Wrapper(PyObject* self_):
        smart_ptr::A(), self(self_) {}

    int f() {
        return call_method< int >(self, "f");
    }

    PyObject* self;
};



}// namespace 


// Module ======================================================================
BOOST_PYTHON_MODULE(_smart_tr)
{
    scope* smart_ptr_A_scope = new scope(
    class_< smart_ptr::A, boost::noncopyable, smart_ptr_A_Wrapper >("A", init<  >())
    );
    // Temporary code for smart pointers
    objects::class_value_wrapper< 
      boost::shared_ptr< smart_ptr::A >, objects::make_ptr_instance< 
        smart_ptr::A, objects::pointer_holder< 
          boost::shared_ptr< smart_ptr::A >, smart_ptr::A >
      >
    >();
    delete smart_ptr_A_scope;

    scope* smart_ptr_C_scope = new scope(
    class_< smart_ptr::C >("C", init<  >())
        .def(init< const smart_ptr::C & >())
        .def_readwrite("value", &smart_ptr::C::value)
    );
    // Temporary code for smart pointers
    objects::class_value_wrapper< 
      boost::shared_ptr< smart_ptr::C >, objects::make_ptr_instance< 
        smart_ptr::C, objects::pointer_holder< 
          boost::shared_ptr< smart_ptr::C >, smart_ptr::C >
      >
    >();
    delete smart_ptr_C_scope;

    scope* smart_ptr_D_scope = new scope(
    class_< smart_ptr::D >("D", init<  >())
        .def(init< const smart_ptr::D & >())
        .def("Get", &smart_ptr::D::Get)
        .def("Set", &smart_ptr::D::Set)
    );
    // Temporary code for smart pointers
    objects::class_value_wrapper< 
      std::auto_ptr< smart_ptr::D >, objects::make_ptr_instance< 
        smart_ptr::D, objects::pointer_holder< 
          std::auto_ptr< smart_ptr::D >, smart_ptr::D >
      >
    >();
    delete smart_ptr_D_scope;

    def("GetA", &smart_ptr::GetA);
    def("NewA", &smart_ptr::NewA);
    def("NewC", &smart_ptr::NewC);
    def("NewD", &smart_ptr::NewD);
}
