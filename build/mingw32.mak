# Usage:
#
#   make copy          Copy the sources and tests
#   make               Compile all sources
#   make test          Run doctest tests
#   make clean         Remove all object files
#   make del           Remove the sources and tests

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

BOOST_WIN= "L:\boost"
BOOST_UNIX= /net/cci/rwgk/boost

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

OBJ = classes.o conversions.o extension_class.o functions.o \
      init_function.o module_builder.o \
      objects.o types.o cross_module.o

.SUFFIXES: .o .cpp

all: libboost_python.a \
     abstract.pyd \
     getting_started1.pyd getting_started2.pyd getting_started3.pyd \
     getting_started4.pyd getting_started5.pyd \
     pickle1.pyd pickle2.pyd pickle3.pyd \
     noncopyable_export.pyd noncopyable_import.pyd \
     ivect.pyd dvect.pyd

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
	$(PYEXE) tst_ivect1.py
	$(PYEXE) tst_dvect1.py
	$(PYEXE) tst_ivect2.py
	$(PYEXE) tst_dvect2.py

clean:
	del *.o
	del *.a
	del *.pyd
	del *.pyc

softlinks:
	python $(BOOST_UNIX)/libs/python/build/filemgr.py $(BOOST_UNIX) softlinks

unlink:
	python $(BOOST_UNIX)/libs/python/build/filemgr.py $(BOOST_UNIX) unlink

cp:
	python $(BOOST_UNIX)/libs/python/build/filemgr.py $(BOOST_UNIX) cp

rm:
	python $(BOOST_UNIX)/libs/python/build/filemgr.py $(BOOST_UNIX) rm

copy:
	$(PYEXE) $(BOOST_WIN)\libs\python\build\filemgr.py $(BOOST_WIN) copy

del:
	$(PYEXE) $(BOOST_WIN)\libs\python\build\filemgr.py $(BOOST_WIN) del
