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


ifeq "$(OS)" "Windows_NT"
PYTHON_LIB=c:/tools/python/libs/python15.lib
INC = -Ic:/cygnus/usr/include/g++-3 -Ic:/cygnus/usr/include -Ic:/boost -Ic:/tools/python/include
MODULE_EXTENSION=dll
else
INC = -I/usr/local/include/python1.5
MODULE_EXTENSION=so
endif

%.o: ../src/%.cpp
	g++ -fPIC -Wall -W $(INC) -o $*.o -c $<

%.d: ../src/%.cpp
	@echo creating $@
	@set -e; g++ -M $(INC) -c $< \
            | sed 's/\($*\)\.o[ :]*/\1.o $@ : /g' > $@; \
                [ -s $@ ] || rm -f $@


example1: example1.o libpycpp.a
	g++ -shared -o ../example/hellomodule.$(MODULE_EXTENSION) $(PYHTON_LIB) example1.o -L. -lpycpp
	python ../example/test_example1.py

example1.o: ../example/example1.cpp
	g++ -fPIC -Wall -W $(INC) -o $*.o -c $<


clean:
	rm -rf *.o *.$(MODULE_EXTENSION) *.a *.d *.pyc *.bak a.out

libpycpp.a: $(LIBOBJ)
	rm -f libpycpp.a
	ar cq libpycpp.a $(LIBOBJ)

DEP = $(OBJ:.o=.d)

ifneq "$(MAKECMDGOALS)" "clean"
include $(DEP)
endif
