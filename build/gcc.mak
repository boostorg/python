#  Revision History

#  17 Apr 01 include cross-module support, compile getting_started1 (R.W. Grosse-Kunstleve)
#  17 Apr 01 build shared library (patch provided by Dan Nuffer)
#  04 Mar 01 Changed library name to libboost_python.a, various cleanups,
#            attempted Cygwin compatibility. Still needs testing on Linux
#            (David Abrahams)


LIBSRC = \
    classes.cpp \
    conversions.cpp \
    cross_module.cpp \
    extension_class.cpp \
    functions.cpp \
    init_function.cpp \
    module_builder.cpp \
    objects.cpp \
    types.cpp

LIBOBJ = $(LIBSRC:.cpp=.o)
OBJ = $(LIBOBJ)

LIBNAME = libboost_python
# libpython2.0.dll

ifeq "$(OS)" "Windows_NT"
ROOT=c:/cygnus
INC = -Ic:/cygnus/usr/include/g++-3 -Ic:/cygnus/usr/include -Ic:/boost -I$(PYTHON_INC)
MODULE_EXTENSION=dll
PYTHON_LIB=c:/cygnus/usr/local/lib/python2.0/config/libpython2.0.dll.a
SHARED_LIB = $(LIBNAME).dll
else
PYTHON_INC=$(ROOT)/usr/local/Python-2.0/include/python2.0
BOOST_INC=../../..
INC = -I$(BOOST_INC) -I$(PYTHON_INC)
MODULE_EXTENSION=so
VERSION=1
SHARED_LIB = $(LIBNAME).so.$(VERSION)
endif

%.o: ../src/%.cpp
	g++ -fPIC -Wall -W $(INC) $(CXXFLAGS) -o $*.o -c $<

%.d: ../src/%.cpp
	@echo creating $@
	@set -e; g++ -M $(INC) -c $< \
            | sed 's/\($*\)\.o[ :]*/\1.o $@ : /g' > $@; \
                [ -s $@ ] || rm -f $@


PYTHON = python

all: test $(SHARED_LIB) getting_started1

test: comprehensive.o $(LIBNAME).a $(SHARED_LIB)
	g++ $(CXXFLAGS) -shared -o ../test/boost_python_test.$(MODULE_EXTENSION) comprehensive.o -L. -lboost_python  $(PYTHON_LIB)
	$(PYTHON) ../test/comprehensive.py

comprehensive.o: ../test/comprehensive.cpp
	g++ $(CXXFLAGS) --template-depth-32 -fPIC -Wall -W $(INC) -o $*.o -c $<


getting_started1: getting_started1.o $(LIBNAME).a
	g++ $(CXXFLAGS) -shared -o ../example/getting_started1.$(MODULE_EXTENSION) getting_started1.o -L. -lboost_python  $(PYTHON_LIB)
	ln -s ../test/doctest.py ../example
	$(PYTHON) ../example/test_getting_started1.py

getting_started1.o: ../example/getting_started1.cpp
	g++ $(CXXFLAGS) --template-depth-32 -fPIC -Wall -W $(INC) -o $*.o -c $<


clean:
	rm -rf *.o *.$(MODULE_EXTENSION) *.a *.d *.pyc *.bak a.out

$(LIBNAME).a: $(LIBOBJ)
	rm -f $@
	ar cqs $@ $(LIBOBJ)

$(SHARED_LIB): $(LIBOBJ)
	g++ $(CXXFLAGS) -shared -o $@ -Wl,--soname=$(LIBNAME).$(MODULE_EXTENSION)

DEP = $(OBJ:.o=.d)

ifneq "$(MAKECMDGOALS)" "clean"
include $(DEP)
endif
