LIBSRC = \
    extclass.cpp \
    init_function.cpp \
    py.cpp \
    module.cpp \
    subclass.cpp \
    functions.cpp \
    newtypes.cpp \
    objects.cpp
    
LIBOBJ = $(LIBSRC:.cpp=.o)
OBJ = $(LIBOBJ) extclass_demo.o


ifeq "$(OS)" "Windows_NT"
PYTHON_LIB=c:/tools/python/libs/python15.lib
INC = -Ic:/cygnus/usr/include/g++-3 -Ic:/cygnus/usr/include -Ic:/boost -Ic:/tools/python/include
MODULE_EXTENSION=dll
else
INC = -I/home/koethe/include -I/home/koethe/C++/boost -I/home/koethe/python/include/python1.5
MODULE_EXTENSION=so
endif

%.o: %.cpp
	g++ -fPIC $(INC) -c $*.cpp

%.d: %.cpp
	@echo creating $@
	@set -e; g++ -M $(INC) -c $*.cpp \
            | sed 's/\($*\)\.o[ :]*/\1.o $@ : /g' > $@; \
                [ -s $@ ] || rm -f $@

demo: extclass_demo.o libpycpp.a
	g++ -shared -o demomodule.$(MODULE_EXTENSION) $(PYTHON_LIB) extclass_demo.o -L. -lpycpp
	python test_extclass.py

clean:
	rm -rf *.o *.$(MODULE_EXTENSION) *.a *.d *.pyc *.bak a.out

libpycpp.a: $(LIBOBJ)
	rm -f libpycpp.a
	ar cq libpycpp.a $(LIBOBJ)

DEP = $(OBJ:.o=.d)

ifneq "$(MAKECMDGOALS)" "clean"
include $(DEP)
endif
