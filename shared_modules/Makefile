include ../build/Makefile

SRC = \
    m1.cpp \
    m2.cpp \
    shared.cpp

TARGETS = $(SRC:.cpp:module$(MODULE_EXTENSION))

LIBBPL = -L$(TARGET_LIBDIR) -l$(TARGET_LIBNAME)

all:   m1module$(MODULE_EXTENSION) m2module$(MODULE_EXTENSION) 
	python shared_modules.py

m1module.so: m1.o sharedmodule$(MODULE_EXTENSION)
	$(CXX_SHARED_LINKER) -o m1module.so m1.o sharedmodule$(MODULE_EXTENSION) $(LIBBPL)

m2module.so: m2.o sharedmodule$(MODULE_EXTENSION)
	$(CXX_SHARED_LINKER) -o m2module.so m2.o sharedmodule$(MODULE_EXTENSION) $(LIBBPL)

sharedmodule$(MODULE_EXTENSION): shared.o
	$(CXX_SHARED_LINKER) -o sharedmodule$(MODULE_EXTENSION) shared.o $(LIBBPL)

.PRECIOUS: so

clean:
	rm -rf *.o *$(MODULE_EXTENSION) *.a *.d *.pyc *.bak a.out

ifneq "$(MAKECMDGOALS)" "clean"
include $(SRC:.cpp=.d)
endif

