#########################################################
#
# makefile - Manhattan py_cpp makefile
#
# Author: David Abrahams
# Date: 04-May-2000
# Copyright (c) 2000 Dragon Systems, Inc.
#
# Revision history at bottom.
#
#########################################################

# Set up $(ROOT_DIR)
include ../make/userdirs.mak
include $(ROOT_DIR)/make/common.mak
include $(ROOT_DIR)/python/pythonhelp.mak
include $(ROOT_DIR)/utils/utilhelp.mak
include $(ROOT_DIR)/py_cpp/py_cpphelp.mak

MAKEFILE_INCLUDES = $(PYTHON_INCLUDES)

# Look in this directory, then the output subdirectory (BIN_DIR) for modules to load without qualification.
export PYTHONPATH := $(THISDIR)$(PYTHONPATH_SEP)$(THISDIR)/$(BIN_DIR)$(PYTHONPATH_SEP)$(PYTHONPATH)

# In order to get the automatic dependency generation working correctly, it
# is necessary to list the source files here.
SRC_FILES = extclass.cpp init_function.cpp subclass.cpp functions.cpp module.cpp newtypes.cpp py.cpp objects.cpp
SRC_FILES += extclass_demo.cpp example1.cpp

SRC_FILES += extclass_d.cpp init_function_d.cpp subclass_d.cpp functions_d.cpp module_d.cpp newtypes_d.cpp py_d.cpp objects_d.cpp
SRC_FILES += extclass_demo_d.cpp
LIBS=$(PYTHON_LIB) $(PYTHON_D_LIB)

test : demo
	$(PYTHON_EXE) test_extclass.py $(ARGS)

test_d : demo_d
	$(DEBUGGER) $(PYTHON_D_EXE) test_extclass.py $(ARGS)

ifndef PYTHON_D_LIB
PYTHON_D_LIB = $(SPACE_CHAR)
endif

-include py_cpp.mk1
-include py_cpp_d.mk1
-include demo.mk1
-include demo_d.mk1
-include example1.mk1