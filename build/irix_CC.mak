# Usage:
#
#   Create a new empty directory anywhere (preferably not in the boost tree).
#   Copy this Makefile to that new directory and rename it to "Makefile"
#   Set the BOOST pathname below.
#
#   make softlinks     Create softlinks to source code and tests
#   make               Compile all sources
#   make test          Run doctest tests
#   make clean         Remove all object files
#   make unlink        Remove softlinks

BOOST= /net/cci/rwgk/boost

#PYEXE= /usr/bin/python
#PYINC= -I/usr/include/python1.5
PYEXE= /usr/local/Python-1.5.2/bin/python
PYINC= -I/usr/local/Python-1.5.2/include/python1.5
#PYEXE= /usr/local/Python-2.0/bin/python
#PYINC= -I/usr/local/Python-2.0/include/python2.0
STLPORTINC= -I/net/cci/xp/C++_C_headers

STDOPTS=
WARNOPTS= -woff 1001,1234,1682

CPP= CC -LANG:std -n32 -mips4
CPPOPTS= $(STLPORTINC) $(STLPORTOPTS) -I$(BOOST) $(PYINC) \
         $(STDOPTS) $(WARNOPTS) -g
MAKEDEP= -M

LD= CC -LANG:std -n32 -mips4
LDOPTS= -shared

OBJ = classes.o conversions.o extension_class.o functions.o \
      init_function.o module_builder.o \
      objects.o types.o cross_module.o
DEPOBJ= $(OBJ) \
        comprehensive.o \
        abstract.o \
        getting_started1.o getting_started2.o getting_started3.o \
        simple_vector.o \
        do_it_yourself_converters.o \
        pickle1.o pickle2.o pickle3.o \
        noncopyable_export.o noncopyable_import.o \
        ivect.o dvect.o

.SUFFIXES: .o .cpp

all: libboost_python.a \
     boost_python_test.so \
     abstract.so \
     getting_started1.so getting_started2.so getting_started3.so \
     simple_vector.so \
     do_it_yourself_converters.so \
     pickle1.so pickle2.so pickle3.so \
     noncopyable_export.so noncopyable_import.so \
     ivect.so dvect.so

libboost_python.a: $(OBJ)
	rm -f libboost_python.a
	$(CPP) -ar -o libboost_python.a $(OBJ)

boost_python_test.so: $(OBJ) comprehensive.o
	$(LD) $(LDOPTS) $(OBJ) comprehensive.o -o boost_python_test.so -lm

abstract.so: $(OBJ) abstract.o
	$(LD) $(LDOPTS) $(OBJ) abstract.o -o abstract.so

getting_started1.so: $(OBJ) getting_started1.o
	$(LD) $(LDOPTS) $(OBJ) getting_started1.o -o getting_started1.so

getting_started2.so: $(OBJ) getting_started2.o
	$(LD) $(LDOPTS) $(OBJ) getting_started2.o -o getting_started2.so

getting_started3.so: $(OBJ) getting_started3.o
	$(LD) $(LDOPTS) $(OBJ) getting_started3.o -o getting_started3.so

simple_vector.so: $(OBJ) simple_vector.o
	$(LD) $(LDOPTS) $(OBJ) simple_vector.o -o simple_vector.so

do_it_yourself_converters.so: $(OBJ) do_it_yourself_converters.o
	$(LD) $(LDOPTS) $(OBJ) do_it_yourself_converters.o -o do_it_yourself_converters.so

pickle1.so: $(OBJ) pickle1.o
	$(LD) $(LDOPTS) $(OBJ) pickle1.o -o pickle1.so

pickle2.so: $(OBJ) pickle2.o
	$(LD) $(LDOPTS) $(OBJ) pickle2.o -o pickle2.so

pickle3.so: $(OBJ) pickle3.o
	$(LD) $(LDOPTS) $(OBJ) pickle3.o -o pickle3.so

noncopyable_export.so: $(OBJ) noncopyable_export.o
	$(LD) $(LDOPTS) $(OBJ) $(HIDDEN) \
          noncopyable_export.o -o noncopyable_export.so

noncopyable_import.so: $(OBJ) noncopyable_import.o
	$(LD) $(LDOPTS) $(OBJ) $(HIDDEN) \
          noncopyable_import.o -o noncopyable_import.so

ivect.so: $(OBJ) ivect.o
	$(LD) $(LDOPTS) $(OBJ) $(HIDDEN) ivect.o -o ivect.so

dvect.so: $(OBJ) dvect.o
	$(LD) $(LDOPTS) $(OBJ) $(HIDDEN) dvect.o -o dvect.so

.cpp.o:
	$(CPP) $(CPPOPTS) -c $*.cpp

test:
	$(PYEXE) comprehensive.py
	$(PYEXE) test_abstract.py
	$(PYEXE) test_getting_started1.py
	$(PYEXE) test_getting_started2.py
	$(PYEXE) test_getting_started3.py
	$(PYEXE) test_simple_vector.py
	$(PYEXE) test_do_it_yourself_converters.py
	$(PYEXE) test_pickle1.py
	$(PYEXE) test_pickle2.py
	$(PYEXE) test_pickle3.py

tst:
	$(PYEXE) tst_noncopyable.py
	$(PYEXE) tst_ivect1.py
	$(PYEXE) tst_dvect1.py
	$(PYEXE) tst_ivect2.py
	$(PYEXE) tst_dvect2.py

clean:
	rm -f $(OBJ) libboost_python.a libboost_python.a.input
	rm -f comprehensive.o boost_python_test.so
	rm -f abstract.o abstract.so
	rm -f getting_started1.o getting_started1.so
	rm -f getting_started2.o getting_started2.so
	rm -f getting_started3.o getting_started3.so
	rm -f simple_vector.o simple_vector.so
	rm -f do_it_yourself_converters.o do_it_yourself_converters.so
	rm -f pickle1.o pickle1.so
	rm -f pickle2.o pickle2.so
	rm -f pickle3.o pickle3.so
	rm -f noncopyable_export.o noncopyable_export.so
	rm -f noncopyable_import.o noncopyable_import.so
	rm -f ivect.o ivect.so
	rm -f dvect.o dvect.so
	rm -f so_locations *.pyc
	rm -rf ii_files

softlinks:
	$(PYEXE) $(BOOST)/libs/python/build/filemgr.py $(BOOST) softlinks

unlink:
	$(PYEXE) $(BOOST)/libs/python/build/filemgr.py $(BOOST) unlink

cp:
	$(PYEXE) $(BOOST)/libs/python/build/filemgr.py $(BOOST) cp

rm:
	$(PYEXE) $(BOOST)/libs/python/build/filemgr.py $(BOOST) rm

depend:
	@ cat Makefile.nodepend; \
          for obj in $(DEPOBJ); \
          do \
            bn=`echo "$$obj" | cut -d. -f1`; \
            $(CPP) $(CPPOPTS) $(MAKEDEP) "$$bn".cpp; \
          done

