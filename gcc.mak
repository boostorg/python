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

INC = -I/home/koethe/include -I/home/koethe/C++/boost -I/home/koethe/python/include/python1.5

%.o: %.cpp
	g++ -fPIC $(INC) -c $*.cpp

%.d: %.cpp
	@echo creating $@
	@set -e; g++ -M $(INC) -c $*.cpp \
            | sed 's/\($*\)\.o[ :]*/\1.o $@ : /g' > $@; \
                [ -s $@ ] || rm -f $@

demo: extclass_demo.o libpycpp.a
	g++ -shared -o demomodule.so extclass_demo.o  -L. -lpycpp
	python test_extclass.py

clean:
	rm -rf *.o *.so *.a *.d *.pyc *.bak a.out

libpycpp.a: $(LIBOBJ)
	rm -f libpycpp.a
	ar cq libpycpp.a $(LIBOBJ)

DEP = $(OBJ:.o=.d)

ifneq "$(MAKECMDGOALS)" "clean"
include $(DEP)
endif
