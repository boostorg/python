// Copyright Stefan Seefeld 2007.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/python.hpp>

#include <boost/detail/lightweight_test.hpp>
#include <boost/bind/bind.hpp>
#include <iostream>
#include <thread>

namespace bpl = boost::python;

struct TestState 
{
  int x;
};

int get_state()
{
  TestState* state = reinterpret_cast<TestState*>(PyModule_GetState(bpl::import("multi_thread_import_").ptr()));
  if (state)
  {
    return state->x;
  }
  return -2;
}

bool set_state(int value)
{
  TestState* state = reinterpret_cast<TestState*>(PyModule_GetState(bpl::import("multi_thread_import_").ptr()));
  if (state)
  {
    state->x = value;
    return true;
  }
  return false;
}

BOOST_PYTHON_MODULE_WITH_STATE(multi_thread_import_, TestState) {
  state->x = -1;
  bpl::def("get_state", get_state);
  bpl::def("set_state", set_state);
}

void import_test(int thread_id)
{
  // Retrieve the main module
  bpl::object import_ = bpl::import("multi_thread_import_");
  bool result = bpl::extract<bool>(import_.attr("set_state")(thread_id)) BOOST_EXTRACT_WORKAROUND;
  BOOST_TEST(result);

  PyThreadState* _save = PyEval_SaveThread();
  std::this_thread::sleep_for(std::chrono::milliseconds(50));
  PyEval_RestoreThread(_save);

  import_ = bpl::import("multi_thread_import_");
  int value = bpl::extract<int>(import_.attr("get_state")()) BOOST_EXTRACT_WORKAROUND;
  std::cout << "Thread " << thread_id << ": " << value << std::endl;
  BOOST_TEST(value == thread_id);
}

void thread_func(int thread_id, PyInterpreterState* main_interp)
{
  // Initialize thread state for main interpreter in sub thread
  PyThreadState* main_tstate = PyThreadState_New(main_interp);

  if (!main_tstate) {
    BOOST_ERROR("Failed to create main thread state");
    return;
  }

  // Lock GIL before create sub interpreter
  PyEval_AcquireThread(main_tstate);

  // Create sub interpreter
  PyThreadState* sub_thread_state = Py_NewInterpreter();

  if (!sub_thread_state) {
    BOOST_ERROR("Failed to create sub-interpreter");
    // Release GIL
    PyEval_ReleaseThread(main_tstate);
    // Delete sub thread state
    PyThreadState_Delete(main_tstate);
    return;
  }

  if (bpl::handle_exception(boost::bind(import_test, thread_id)))
  {
    if (PyErr_Occurred())
    {
      BOOST_ERROR("Python Error detected");
      PyErr_Print();
    }
    else
    {
        BOOST_ERROR("A C++ exception was thrown  for which "
                    "there was no exception handler registered.");
    }
  }

  // Finish sub interpreter
  Py_EndInterpreter(sub_thread_state);

  // Lock GIL again after for main interpreter
  PyEval_AcquireThread(main_tstate);
  // Release GIL
  PyEval_ReleaseThread(main_tstate);
  // Delete sub thread state
  PyThreadState_Delete(main_tstate);
}

int main(int argc, char **argv)
{
  BOOST_TEST(argc == 1);

  // Register the module with the interpreter
  if (PyImport_AppendInittab(const_cast<char*>("multi_thread_import_"),
#if PY_VERSION_HEX >= 0x03000000 
                             PyInit_multi_thread_import_
#else 
                             multi_thread_import_
#endif 
                             ) == -1)
  {
    BOOST_ERROR("Failed to add import2_ to the interpreter's "
                 "builtin modules");
  }

  // Initialize the interpreter
  Py_Initialize();

  // Capture main interpreter state to pass it to sub threads
  PyInterpreterState* main_interp = PyThreadState_Get()->interp;

  const int num_threads = 5;
  std::vector<std::thread> threads;

  // Release the main thread's GIL
  PyThreadState* main_thread_state = PyEval_SaveThread();

  for (int i = 0; i < num_threads; ++i)
  {
    threads.emplace_back(thread_func, i, main_interp);
  }

  for (auto& t : threads)
  {
    t.join();
  }

  // Restore the main thread's GIL
  PyEval_RestoreThread(main_thread_state);
    
  // Boost.Python doesn't support Py_Finalize yet.
  // Py_Finalize();
  return boost::report_errors();
}

// Including this file makes sure
// that on Windows, any crashes (e.g. null pointer dereferences) invoke
// the debugger immediately, rather than being translated into structured
// exceptions that can interfere with debugging.
#include "module_tail.cpp"
