# Revision History:
# 17 Apr 01  include cross-module support, compile getting_started1 (R.W. Grosse-Kunstleve) UNTESTED!
# 06 Mar 01  Fixed typo in use of "PYTHON_LIB" (Dave Abrahams)
# 04 Mar 01  Changed library name to libboost_python.a (David Abrahams)

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


ifeq "$(OS)" "Windows_NT"
PYTHON_LIB=c:/tools/python/libs/python15.lib
INC = -Ic:/cygnus/usr/include/g++-3 -Ic:/cygnus/usr/include -Ic:/boost -Ic:/tools/python/include
MODULE_EXTENSION=dll
else
INC = -I/usr/local/include/python1.5
MODULE_EXTENSION=so
endif

%.o: ../src/%.cpp
	como --pic $(INC) -o $*.o -c $<

%.d: ../src/%.cpp
	@echo creating $@
	@set -e; como -M $(INC) -c $< \
            | sed 's/\($*\)\.o[ :]*/\1.o $@ : /g' > $@; \
                [ -s $@ ] || rm -f $@

getting_started1: getting_started1.o libboost_python.a
	como-dyn-link -o ../example/getting_started1.$(MODULE_EXTENSION) $(PYTHON_LIB) getting_started1.o -L. -lboost_python
	ln -s ../test/doctest.py ../example
	python ../example/test_getting_started1.py

getting_started1.o: ../example/getting_started1.cpp
	como --pic $(INC) -o $*.o -c $<

clean:
	rm -rf *.o *.$(MODULE_EXTENSION) *.a *.d *.pyc *.bak a.out

libboost_python.a: $(LIBOBJ)
	rm -f libboost_python.a
	ar cq libboost_python.a $(LIBOBJ)

DEP = $(OBJ:.o=.d)

ifneq "$(MAKECMDGOALS)" "clean"
include $(DEP)
endif
