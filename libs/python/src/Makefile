include ../build/Makefile

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

lib: $(TARGET_LIBFILENAME)

install: lib
	@if [ ! -d $(TARGET_LIBDIR) ] ; then mkdir -p $(TARGET_LIBDIR) ; fi
	cp $(TARGET_LIBFILENAME) $(TARGET_LIBDIR)

$(TARGET_LIBFILENAME): $(LIBOBJ)
	rm -f $(TARGET_LIBFILENAME)
	ar cq $(TARGET_LIBFILENAME) $(LIBOBJ)

clean:
	rm -rf *.o *$(MODULE_EXTENSION) *.a *.d *.pyc *.bak a.out

