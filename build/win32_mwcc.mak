# Usage:
#
#   make copy          Copy the sources and tests
#   make               Compile all sources
#   make test          Run doctest tests
#   make clean         Remove all object files
#   make del           Remove the sources and tests
#
# Revision history:
#   14 Dec 01 derived from vc60.mak (R.W. Grosse-Kunstleve)

ROOT=R:
BOOST_WIN="$(ROOT)\boostdev"
BOOST_UNIX=$(HOME)/boost

#PYEXE="C:\Program files\Python\python.exe"
#PYINC=-I"C:\Program files\Python\include"
#PYLIB="C:\Program files\Python\libs\python15.lib"
PYEXE="C:\Python21\python.exe"
PYINC=-I"C:\Python21\include"
PYLIB="C:\Python21\libs\python21.lib"

STDOPTS=-gccinc -prefix UseDLLPrefix.h
WARNOPTS=-warn on,nounusedexpr,nounused
OPTOPTS=-O

CPP=mwcc
CPPOPTS=$(STDOPTS) $(WARNOPTS) $(OPTOPTS) \
        $(STLPORTINC) $(STLPORTOPTS) -I$(BOOST_WIN) $(PYINC)

LD=mwld
LDOPTS=-export dllexport -shared

OBJ=classes.obj conversions.obj extension_class.obj functions.obj \
    init_function.obj module_builder.obj \
    objects.obj types.obj cross_module.obj

.SUFFIXES: .obj .cpp

all: libboost_python.lib \
     boost_python_test.pyd \
     abstract.pyd \
     getting_started1.pyd getting_started2.pyd \
     simple_vector.pyd \
     do_it_yourself_convts.pyd \
     nested.pyd \
     pickle1.pyd pickle2.pyd pickle3.pyd \
     noncopyable_export.pyd noncopyable_import.pyd \
     ivect.pyd dvect.pyd \
     richcmp1.pyd richcmp2.pyd richcmp3.pyd

libboost_python.lib: $(OBJ)
	$(LD) -library -o libboost_python.lib $(OBJ)

boost_python_test.pyd: $(OBJ) comprehensive.obj
	$(LD) $(LDOPTS) $(OBJ) comprehensive.obj $(PYLIB) -o boost_python_test.pyd

abstract.pyd: $(OBJ) abstract.obj
	$(LD) $(LDOPTS) $(OBJ) abstract.obj $(PYLIB)  -o abstract.pyd

getting_started1.pyd: $(OBJ) getting_started1.obj
	$(LD) $(LDOPTS) $(OBJ) getting_started1.obj $(PYLIB)  -o getting_started1.pyd

getting_started2.pyd: $(OBJ) getting_started2.obj
	$(LD) $(LDOPTS) $(OBJ) getting_started2.obj $(PYLIB)  -o getting_started2.pyd

simple_vector.pyd: $(OBJ) simple_vector.obj
	$(LD) $(LDOPTS) $(OBJ) simple_vector.obj $(PYLIB)  -o simple_vector.pyd

do_it_yourself_convts.pyd: $(OBJ) do_it_yourself_convts.obj
	$(LD) $(LDOPTS) $(OBJ) do_it_yourself_convts.obj $(PYLIB)  -o do_it_yourself_convts.pyd

nested.pyd: $(OBJ) nested.obj
	$(LD) $(LDOPTS) $(OBJ) nested.obj $(PYLIB)  -o nested.pyd

pickle1.pyd: $(OBJ) pickle1.obj
	$(LD) $(LDOPTS) $(OBJ) pickle1.obj $(PYLIB)  -o pickle1.pyd

pickle2.pyd: $(OBJ) pickle2.obj
	$(LD) $(LDOPTS) $(OBJ) pickle2.obj $(PYLIB)  -o pickle2.pyd

pickle3.pyd: $(OBJ) pickle3.obj
	$(LD) $(LDOPTS) $(OBJ) pickle3.obj $(PYLIB)  -o pickle3.pyd

noncopyable_export.pyd: $(OBJ) noncopyable_export.obj
	$(LD) $(LDOPTS) $(OBJ) noncopyable_export.obj $(PYLIB)  -o noncopyable_export.pyd

noncopyable_import.pyd: $(OBJ) noncopyable_import.obj
	$(LD) $(LDOPTS) $(OBJ) noncopyable_import.obj $(PYLIB)  -o noncopyable_import.pyd

ivect.pyd: $(OBJ) ivect.obj
	$(LD) $(LDOPTS) $(OBJ) ivect.obj $(PYLIB)  -o ivect.pyd

dvect.pyd: $(OBJ) dvect.obj
	$(LD) $(LDOPTS) $(OBJ) dvect.obj $(PYLIB)  -o dvect.pyd

richcmp1.pyd: $(OBJ) richcmp1.obj
	$(LD) $(LDOPTS) $(OBJ) richcmp1.obj $(PYLIB)  -o richcmp1.pyd

richcmp2.pyd: $(OBJ) richcmp2.obj
	$(LD) $(LDOPTS) $(OBJ) richcmp2.obj $(PYLIB)  -o richcmp2.pyd

richcmp3.pyd: $(OBJ) richcmp3.obj
	$(LD) $(LDOPTS) $(OBJ) richcmp3.obj $(PYLIB)  -o richcmp3.pyd

.cpp.obj:
	$(CPP) $(CPPOPTS) -c $*.cpp

test:
	$(PYEXE) comprehensive.py
	$(PYEXE) test_abstract.py
	$(PYEXE) test_getting_started1.py
	$(PYEXE) test_getting_started2.py
	$(PYEXE) test_simple_vector.py
	$(PYEXE) test_do_it_yourself_convts.py
	$(PYEXE) test_nested.py
	$(PYEXE) test_pickle1.py
	$(PYEXE) test_pickle2.py
	$(PYEXE) test_pickle3.py
	$(PYEXE) test_cross_module.py
	$(PYEXE) test_richcmp1.py
	$(PYEXE) test_richcmp2.py
	$(PYEXE) test_richcmp3.py

clean:
	-del *.obj
	-del *.lib
	-del *.exp
	-del *.idb
	-del *.pyd
	-del *.pyc

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
