#  Revision History

#  04 Mar 01 Changed library name to libboost_python.a, various cleanups,
#            attempted Cygwin compatibility. Still needs testing on Linux
#            (David Abrahams)


LIBSRC = \
    classes.cpp \
    conversions.cpp \
    extension_class.cpp \
    functions.cpp \
    init_function.cpp \
    module_builder.cpp \
    objects.cpp \
    types.cpp

LIBOBJ = $(LIBSRC:.cpp=.o)
OBJ = $(LIBOBJ)

PYTHON_INC=$(ROOT)/usr/local/include/python2.0
# libpython2.0.dll

ifeq "$(OS)" "Windows_NT"
ROOT=c:/cygnus
INC = -Ic:/cygnus/usr/include/g++-3 -Ic:/cygnus/usr/include -Ic:/boost -I$(PYTHON_INC)
MODULE_EXTENSION=dll
PYTHON_LIB=c:/cygnus/usr/local/lib/python2.0/config/libpython2.0.dll.a
else
INC = -I$(PYTHON_INC)
MODULE_EXTENSION=so
endif

%.o: ../src/%.cpp
	g++ -fPIC -Wall -W $(INC) -o $*.o -c $<

%.d: ../src/%.cpp
	@echo creating $@
	@set -e; g++ -M $(INC) -c $< \
            | sed 's/\($*\)\.o[ :]*/\1.o $@ : /g' > $@; \
                [ -s $@ ] || rm -f $@


PYTHON = python

test: comprehensive.o libboost_python.a
	g++ $(CXXFLAGS) -shared -o ../test/boost_python_test.$(MODULE_EXTENSION) comprehensive.o -L. -lboost_python  $(PYTHON_LIB)
	$(PYTHON) ../test/comprehensive.py

comprehensive.o: ../test/comprehensive.cpp
	g++ $(CXXFLAGS) --template-depth-32 -fPIC -Wall -W $(INC) -o $*.o -c $<


example1: example1.o libboost_python.a
	g++ $(CXXFLAGS) -shared -o ../example/hellomodule.$(MODULE_EXTENSION) example1.o -L. -lboost_python  $(PYTHON_LIB)
	$(PYTHON) ../example/test_example1.py

example1.o: ../example/example1.cpp
	g++ $(CXXFLAGS) --template-depth-32 -fPIC -Wall -W $(INC) -o $*.o -c $<


clean:
	rm -rf *.o *.$(MODULE_EXTENSION) *.a *.d *.pyc *.bak a.out

libboost_python.a: $(LIBOBJ)
	rm -f libboost_python.a
	ar cq libboost_python.a $(LIBOBJ)

DEP = $(OBJ:.o=.d)

ifneq "$(MAKECMDGOALS)" "clean"
include $(DEP)
endif
