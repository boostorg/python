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

PYEXE= /usr/local/Python-1.5.2/bin/python
PYINC= -I/usr/local/Python-1.5.2/include/python1.5
#PYEXE= /usr/local/Python-2.0/bin/python
#PYINC= -I/usr/local/Python-2.0/include/python2.0
#STLPORTINC= -I/usr/local/STLport-4.1b3/stlport
#STLPORTOPTS= \
# -D__USE_STD_IOSTREAM \
# -D__STL_NO_SGI_IOSTREAMS \
# -D__STL_USE_NATIVE_STRING \
# -D__STL_NO_NEW_C_HEADERS \
# -D_RWSTD_COMPILE_INSTANTIATE=1
#STLPORTINC= -I/usr/local/STLport-4.1b4/stlport
#STLPORTOPTS= -D__NO_USE_STD_IOSTREAM -D__STL_NO_SGI_IOSTREAMS
STLPORTINC= -I/net/cci/xp/C++_C_headers

STDOPTS= -std strict_ansi
WARNOPTS= -msg_disable 186,450,1115
# use -msg_display_number to obtain integer tags for -msg_disable

CPP= cxx
CPPOPTS= $(STLPORTINC) $(STLPORTOPTS) -I$(BOOST) $(PYINC) \
         $(STDOPTS) $(WARNOPTS) -g
MAKEDEP= -Em

LD= cxx
LDOPTS= -shared -expect_unresolved 'Py*' -expect_unresolved '_Py*'

#HIDDEN= -hidden

OBJ = classes.o conversions.o extension_class.o functions.o \
      init_function.o module_builder.o \
      objects.o types.o cross_module.o
DEPOBJ= $(OBJ) \
        comprehensive.o \
        abstract.o \
        getting_started1.o getting_started2.o getting_started3.o \
        getting_started4.o getting_started5.o \
        pickle1.o pickle2.o pickle3.o \
        noncopyable_export.o noncopyable_import.o \
        ivect.o dvect.o

.SUFFIXES: .o .cpp

all: libboost_python.a \
     boost_python_test.so \
     abstract.so \
     getting_started1.so getting_started2.so getting_started3.so \
     getting_started4.so getting_started5.so \
     pickle1.so pickle2.so pickle3.so \
     noncopyable_export.so

#     noncopyable_import.so \
#     ivect.so dvect.so

libboost_python.a: $(OBJ)
	rm -f libboost_python.a
	cd cxx_repository; \
          ls -1 > ../libboost_python.a.input; \
          ar r ../libboost_python.a -input ../libboost_python.a.input
	rm -f libboost_python.a.input
	ar r libboost_python.a $(OBJ)

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

getting_started4.so: $(OBJ) getting_started4.o
	$(LD) $(LDOPTS) $(OBJ) getting_started4.o -o getting_started4.so

getting_started5.so: $(OBJ) getting_started5.o
	$(LD) $(LDOPTS) $(OBJ) getting_started5.o -o getting_started5.so

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
	$(PYEXE) test_getting_started4.py
	$(PYEXE) test_getting_started5.py
	$(PYEXE) test_pickle1.py
	$(PYEXE) test_pickle2.py
	$(PYEXE) test_pickle3.py

tst:
	$(PYEXE) tst_noncopyable.py
	$(PYEXE) tst_ivect.py
	$(PYEXE) tst_dvect.py

clean:
	rm -f $(OBJ) libboost_python.a libboost_python.a.input
	rm -f comprehensive.o boost_python_test.so
	rm -f abstract.o abstract.so
	rm -f getting_started1.o getting_started1.so
	rm -f getting_started2.o getting_started2.so
	rm -f getting_started3.o getting_started3.so
	rm -f getting_started4.o getting_started4.so
	rm -f getting_started5.o getting_started5.so
	rm -f pickle1.o pickle1.so
	rm -f pickle2.o pickle2.so
	rm -f pickle3.o pickle3.so
	rm -f noncopyable_export.o noncopyable_export.so
	rm -f noncopyable_import.o noncopyable_import.so
	rm -f ivect.o ivect.so
	rm -f dvect.o dvect.so
	rm -f so_locations *.pyc
	rm -rf cxx_repository

softlinks:
	python $(BOOST)/libs/python/build/filemgr.py $(BOOST) softlinks

unlink:
	python $(BOOST)/libs/python/build/filemgr.py $(BOOST) unlink

cp:
	python $(BOOST)/libs/python/build/filemgr.py $(BOOST) cp

rm:
	python $(BOOST)/libs/python/build/filemgr.py $(BOOST) rm

depend:
	@ cat Makefile.nodepend; \
          for obj in $(DEPOBJ); \
          do \
            bn=`echo "$$obj" | cut -d. -f1`; \
            $(CPP) $(CPPOPTS) $(MAKEDEP) "$$bn".cpp; \
          done

