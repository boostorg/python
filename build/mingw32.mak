# Usage:
#
#   Create a new empty directory anywhere (preferably not in the boost tree).
#   Copy this Makefile to that new directory and rename it to "Makefile"
#   Set the BOOST_* pathnames below.
#
#   The idea is that the build directory is on a Unix filesystem that
#   is mounted on a PC using SAMBA. Use this makefile under both Unix
#   and Windows:
#
#   Unix: make softlinks     Create softlinks to source code and tests
#   Win:  make               Compile all sources
#   Win:  make test          Run doctest tests
#   Unix: make clean         Remove all object files
#   Unix: make unlink        Remove softlinks

# To install mingw32, follow instructions at:
#   http://starship.python.net/crew/kernr/mingw32/Notes.html
# In particular, install:
#   ftp://ftp.xraylith.wisc.edu/pub/khan/gnu-win32/mingw32/gcc-2.95.2/gcc-2.95.2-msvcrt.exe
#   ftp://ftp.xraylith.wisc.edu/pub/khan/gnu-win32/mingw32/gcc-2.95.2/fixes/quote-fix-msvcrt.exe
#   http://starship.python.net/crew/kernr/mingw32/Python-1.5.2-mingw32.zip
# Unpack the first two archives in the default locations and update your PATH.
# Unpack the third archive in \usr.

# Note: comprehensive.cpp generates compiler errors and later crashes.
#   L:\boost\boost\python\detail\extension_class.hpp:643: warning:
#   alignment of `vtable for class
#   boost::python::detail::held_instance<bpl_test::Derived1>'
#   is greater than maximum object file alignment. Using 16.
# Could this be fixed with compiler options?
# -fhuge-objects looks interesting, but requires recompiling the C++ library.
#                (what exactly does that mean?)
# -fvtable-thunks eliminates the compiler warning, but
#                 "import boost_python_test" still causes a crash.

BOOST_UNIX= /net/cci/rwgk/boost
BOOST_WIN= "L:\boost"

PYEXE= "C:\Program files\Python\python.exe"
PYINC= -I"C:\usr\include\python1.5"
PYLIB= "C:\usr\lib\libpython15.a"

STDOPTS= -ftemplate-depth-21
WARNOPTS=

CPP= g++
CPPOPTS= $(STLPORTINC) $(STLPORTOPTS) -I$(BOOST_WIN) $(PYINC) \
         $(STDOPTS) $(WARNOPTS) -g

LD= g++
LDOPTS= -shared

BPL_SRC = $(BOOST_UNIX)/libs/python/src
BPL_TST = $(BOOST_UNIX)/libs/python/test
BPL_EXA = $(BOOST_UNIX)/libs/python/example
SOFTLINKS = \
$(BPL_SRC)/classes.cpp \
$(BPL_SRC)/conversions.cpp \
$(BPL_SRC)/extension_class.cpp \
$(BPL_SRC)/functions.cpp \
$(BPL_SRC)/init_function.cpp \
$(BPL_SRC)/module_builder.cpp \
$(BPL_SRC)/objects.cpp \
$(BPL_SRC)/types.cpp \
$(BPL_SRC)/x_class_builder.cpp \
$(BPL_TST)/comprehensive.cpp \
$(BPL_TST)/comprehensive.hpp \
$(BPL_TST)/comprehensive.py \
$(BPL_TST)/doctest.py \
$(BPL_EXA)/abstract.cpp \
$(BPL_EXA)/getting_started1.cpp \
$(BPL_EXA)/getting_started2.cpp \
$(BPL_EXA)/getting_started3.cpp \
$(BPL_EXA)/getting_started4.cpp \
$(BPL_EXA)/getting_started5.cpp \
$(BPL_EXA)/pickle1.cpp \
$(BPL_EXA)/pickle2.cpp \
$(BPL_EXA)/pickle3.cpp \
$(BPL_EXA)/test_abstract.py \
$(BPL_EXA)/test_getting_started1.py \
$(BPL_EXA)/test_getting_started2.py \
$(BPL_EXA)/test_getting_started3.py \
$(BPL_EXA)/test_getting_started4.py \
$(BPL_EXA)/test_getting_started5.py \
$(BPL_EXA)/test_pickle1.py \
$(BPL_EXA)/test_pickle2.py \
$(BPL_EXA)/test_pickle3.py \
$(BPL_EXA)/noncopyable.h \
$(BPL_EXA)/noncopyable_export.cpp \
$(BPL_EXA)/noncopyable_import.cpp \
$(BPL_EXA)/tst_noncopyable.py \
$(BPL_EXA)/ivect.h \
$(BPL_EXA)/ivect.cpp \
$(BPL_EXA)/dvect.h \
$(BPL_EXA)/dvect.cpp \
$(BPL_EXA)/tst_ivect.py \
$(BPL_EXA)/tst_dvect.py

DEFS= \
boost_python_test \
abstract \
getting_started1 \
getting_started2 \
getting_started3 \
getting_started4 \
getting_started5 \
pickle1 \
pickle2 \
pickle3 \
noncopyable_export \
noncopyable_import \
ivect \
dvect

OBJ = classes.o conversions.o extension_class.o functions.o \
      init_function.o module_builder.o \
      objects.o types.o x_class_builder.o

.SUFFIXES: .o .cpp

all: libboost_python.a \
     boost_python_test.pyd \
     abstract.pyd \
     getting_started1.pyd getting_started2.pyd getting_started3.pyd \
     getting_started4.pyd getting_started5.pyd \
     pickle1.pyd pickle2.pyd pickle3.pyd \
     noncopyable_export.pyd noncopyable_import.pyd \
     ivect.pyd dvect.pyd

softlinks: defs
	@ for pn in $(SOFTLINKS); \
	  do \
            bn=`basename "$$pn"`; \
	    if [ ! -e "$$bn" ]; then \
              echo "ln -s $$pn ."; \
	      ln -s "$$pn" .; \
            else \
              echo "info: no softlink created (file exists): $$bn"; \
	    fi; \
	  done

unlink: rmdefs
	@ for pn in $(SOFTLINKS); \
	  do \
            bn=`basename "$$pn"`; \
	    if [ -L "$$bn" ]; then \
              echo "rm $$bn"; \
              rm -f "$$bn"; \
            elif [ -e "$$bn" ]; then \
              echo "info: not a softlink: $$bn"; \
	    fi; \
	  done

defs:
	@ for def in $(DEFS); \
	  do \
            echo "EXPORTS\n\tinit$$def" > $$def.def; \
	  done

rmdefs:
	@ for def in $(DEFS); \
	  do \
            rm -f $$def.def; \
	  done

libboost_python.a: $(OBJ)
	del libboost_python.a
	ar r libboost_python.a $(OBJ)

DLLWRAPOPTS= -s --driver-name g++ -s
             --entry _DllMainCRTStartup@12 --target=i386-mingw32

boost_python_test.pyd: $(OBJ) comprehensive.o
	dllwrap $(DLLWRAPOPTS) \
          --dllname boost_python_test.pyd \
          --def boost_python_test.def \
          $(OBJ) comprehensive.o $(PYLIB)

abstract.pyd: $(OBJ) abstract.o
	dllwrap $(DLLWRAPOPTS) \
          --dllname abstract.pyd \
          --def abstract.def \
          $(OBJ) abstract.o $(PYLIB)

getting_started1.pyd: $(OBJ) getting_started1.o
	dllwrap $(DLLWRAPOPTS) \
          --dllname getting_started1.pyd \
          --def getting_started1.def \
          $(OBJ) getting_started1.o $(PYLIB)

getting_started2.pyd: $(OBJ) getting_started2.o
	dllwrap $(DLLWRAPOPTS) \
          --dllname getting_started2.pyd \
          --def getting_started2.def \
          $(OBJ) getting_started2.o $(PYLIB)

getting_started3.pyd: $(OBJ) getting_started3.o
	dllwrap $(DLLWRAPOPTS) \
          --dllname getting_started3.pyd \
          --def getting_started3.def \
          $(OBJ) getting_started3.o $(PYLIB)

getting_started4.pyd: $(OBJ) getting_started4.o
	dllwrap $(DLLWRAPOPTS) \
          --dllname getting_started4.pyd \
          --def getting_started4.def \
          $(OBJ) getting_started4.o $(PYLIB)

getting_started5.pyd: $(OBJ) getting_started5.o
	dllwrap $(DLLWRAPOPTS) \
          --dllname getting_started5.pyd \
          --def getting_started5.def \
          $(OBJ) getting_started5.o $(PYLIB)

pickle1.pyd: $(OBJ) pickle1.o
	dllwrap $(DLLWRAPOPTS) \
          --dllname pickle1.pyd \
          --def pickle1.def \
          $(OBJ) pickle1.o $(PYLIB)

pickle2.pyd: $(OBJ) pickle2.o
	dllwrap $(DLLWRAPOPTS) \
          --dllname pickle2.pyd \
          --def pickle2.def \
          $(OBJ) pickle2.o $(PYLIB)

pickle3.pyd: $(OBJ) pickle3.o
	dllwrap $(DLLWRAPOPTS) \
          --dllname pickle3.pyd \
          --def pickle3.def \
          $(OBJ) pickle3.o $(PYLIB)

noncopyable_export.pyd: $(OBJ) noncopyable_export.o
	dllwrap $(DLLWRAPOPTS) \
          --dllname noncopyable_export.pyd \
          --def noncopyable_export.def \
          $(OBJ) noncopyable_export.o $(PYLIB)

noncopyable_import.pyd: $(OBJ) noncopyable_import.o
	dllwrap $(DLLWRAPOPTS) \
          --dllname noncopyable_import.pyd \
          --def noncopyable_import.def \
          $(OBJ) noncopyable_import.o $(PYLIB)

ivect.pyd: $(OBJ) ivect.o
	dllwrap $(DLLWRAPOPTS) \
          --dllname ivect.pyd \
          --def ivect.def \
          $(OBJ) ivect.o $(PYLIB)

dvect.pyd: $(OBJ) dvect.o
	dllwrap $(DLLWRAPOPTS) \
          --dllname dvect.pyd \
          --def dvect.def \
          $(OBJ) dvect.o $(PYLIB)

.cpp.o:
	$(CPP) $(CPPOPTS) -c $*.cpp

test:
#	$(PYEXE) comprehensive.py
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
	rm -f comprehensive.o boost_python_test.pyd
	rm -f abstract.o abstract.pyd
	rm -f getting_started1.o getting_started1.pyd
	rm -f getting_started2.o getting_started2.pyd
	rm -f getting_started3.o getting_started3.pyd
	rm -f getting_started4.o getting_started4.pyd
	rm -f getting_started5.o getting_started5.pyd
	rm -f pickle1.o pickle1.pyd
	rm -f pickle2.o pickle2.pyd
	rm -f pickle3.o pickle3.pyd
	rm -f noncopyable_export.o noncopyable_export.pyd
	rm -f noncopyable_import.o noncopyable_import.pyd
	rm -f ivect.o ivect.pyd
	rm -f dvect.o dvect.pyd
	rm -f so_locations *.pyc
	rm -rf cxx_repository
