# Usage:
#
#   make copy          Copy the sources and tests
#   make               Compile all sources
#   make test          Run doctest tests
#   make clean         Remove all object files
#   make del           Remove the sources and tests

BOOST_WIN= "L:\boost"
BOOST_UNIX= /net/cci/rwgk/boost

PYEXE= "C:\Program files\Python\python.exe"
PYINC= /I"C:\Program files\Python\include"
PYLIB= "C:\Program files\Python\libs\python15.lib"

STDOPTS= /nologo /MD /GR /GX /FD /Zm200
WARNOPTS=

CPP= cl.exe
CPPOPTS= $(STLPORTINC) $(STLPORTOPTS) /I$(BOOST_WIN) $(PYINC) \
         $(STDOPTS) $(WARNOPTS)

LD= link.exe
LDOPTS= /nologo /dll /incremental:no

OBJ = classes.obj conversions.obj extension_class.obj functions.obj \
      init_function.obj module_builder.obj \
      objects.obj types.obj cross_module.obj

.SUFFIXES: .obj .cpp

all: libboost_python.a \
     boost_python_test.pyd \
     abstract.pyd \
     getting_started1.pyd getting_started2.pyd getting_started3.pyd \
     getting_started4.pyd getting_started5.pyd \
     pickle1.pyd pickle2.pyd pickle3.pyd \
     noncopyable_export.pyd noncopyable_import.pyd \
     ivect.pyd dvect.pyd

libboost_python.a: $(OBJ)

boost_python_test.pyd: $(OBJ) comprehensive.obj
	$(LD) $(LDOPTS) $(OBJ) comprehensive.obj $(PYLIB) /export:initboost_python_test /out:"boost_python_test.pyd"

abstract.pyd: $(OBJ) abstract.obj
	$(LD) $(LDOPTS) $(OBJ) abstract.obj $(PYLIB) /export:initabstract /out:"abstract.pyd"

getting_started1.pyd: $(OBJ) getting_started1.obj
	$(LD) $(LDOPTS) $(OBJ) getting_started1.obj $(PYLIB) /export:initgetting_started1 /out:"getting_started1.pyd"

getting_started2.pyd: $(OBJ) getting_started2.obj
	$(LD) $(LDOPTS) $(OBJ) getting_started2.obj $(PYLIB) /export:initgetting_started2 /out:"getting_started2.pyd"

getting_started3.pyd: $(OBJ) getting_started3.obj
	$(LD) $(LDOPTS) $(OBJ) getting_started3.obj $(PYLIB) /export:initgetting_started3 /out:"getting_started3.pyd"

getting_started4.pyd: $(OBJ) getting_started4.obj
	$(LD) $(LDOPTS) $(OBJ) getting_started4.obj $(PYLIB) /export:initgetting_started4 /out:"getting_started4.pyd"

getting_started5.pyd: $(OBJ) getting_started5.obj
	$(LD) $(LDOPTS) $(OBJ) getting_started5.obj $(PYLIB) /export:initgetting_started5 /out:"getting_started5.pyd"

pickle1.pyd: $(OBJ) pickle1.obj
	$(LD) $(LDOPTS) $(OBJ) pickle1.obj $(PYLIB) /export:initpickle1 /out:"pickle1.pyd"

pickle2.pyd: $(OBJ) pickle2.obj
	$(LD) $(LDOPTS) $(OBJ) pickle2.obj $(PYLIB) /export:initpickle2 /out:"pickle2.pyd"

pickle3.pyd: $(OBJ) pickle3.obj
	$(LD) $(LDOPTS) $(OBJ) pickle3.obj $(PYLIB) /export:initpickle3 /out:"pickle3.pyd"

noncopyable_export.pyd: $(OBJ) noncopyable_export.obj
	$(LD) $(LDOPTS) $(OBJ) noncopyable_export.obj $(PYLIB) /export:initnoncopyable_export /out:"noncopyable_export.pyd"

noncopyable_import.pyd: $(OBJ) noncopyable_import.obj
	$(LD) $(LDOPTS) $(OBJ) noncopyable_import.obj $(PYLIB) /export:initnoncopyable_import /out:"noncopyable_import.pyd"

ivect.pyd: $(OBJ) ivect.obj
	$(LD) $(LDOPTS) $(OBJ) ivect.obj $(PYLIB) /export:initivect /out:"ivect.pyd"

dvect.pyd: $(OBJ) dvect.obj
	$(LD) $(LDOPTS) $(OBJ) dvect.obj $(PYLIB) /export:initdvect /out:"dvect.pyd"

.cpp.obj:
	$(CPP) $(CPPOPTS) /c $*.cpp

test:
	$(PYEXE) comprehensive.py --broken-auto-ptr 
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
	del *.obj
	del *.lib
	del *.exp
	del *.idb
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
