# Usage:
#
#   make copy          Copy the sources and tests
#   make               Compile all sources
#   make test          Run doctest tests
#   make clean         Remove all object files
#   make del           Remove the sources and tests
#
# Revision history:
#   12 Apr 01 new macro ROOT to simplify configuration (R.W. Grosse-Kunstleve)
#   Initial version: R.W. Grosse-Kunstleve

ROOT=L:
BOOST_WIN="$(ROOT)\boost"
BOOST_UNIX=$(HOME)/boost

PYEXE="C:\Program files\Python\python.exe"
PYINC=/I"C:\Program files\Python\include"
PYLIB="C:\Program files\Python\libs\python15.lib"

STDOPTS=/nologo /MD /GR /GX /Zm200
WARNOPTS=
OPTOPTS=

CPP=cl.exe
CPPOPTS=$(STLPORTINC) $(STLPORTOPTS) /I$(BOOST_WIN) $(PYINC) \
        $(STDOPTS) $(WARNOPTS) $(OPTOPTS)

LD=link.exe
LDOPTS=/nologo /dll /incremental:no

OBJ=classes.obj conversions.obj extension_class.obj functions.obj \
    init_function.obj module_builder.obj \
    objects.obj types.obj cross_module.obj

.SUFFIXES: .obj .cpp

all: boost_python.lib \
     boost_python_test.pyd \
     abstract.pyd \
     getting_started1.pyd getting_started2.pyd \
     simple_vector.pyd \
     do_it_yourself_converters.pyd \
     pickle1.pyd pickle2.pyd pickle3.pyd \
     noncopyable_export.pyd noncopyable_import.pyd \
     ivect.pyd dvect.pyd \
     richcmp.pyd

boost_python.lib: $(OBJ)
	$(LD) -lib /nologo /out:boost_python.lib $(OBJ)

boost_python_test.pyd: $(OBJ) comprehensive.obj
	$(LD) $(LDOPTS) $(OBJ) comprehensive.obj $(PYLIB) /export:initboost_python_test /out:"boost_python_test.pyd"

abstract.pyd: $(OBJ) abstract.obj
	$(LD) $(LDOPTS) $(OBJ) abstract.obj $(PYLIB) /export:initabstract /out:"abstract.pyd"

getting_started1.pyd: $(OBJ) getting_started1.obj
	$(LD) $(LDOPTS) $(OBJ) getting_started1.obj $(PYLIB) /export:initgetting_started1 /out:"getting_started1.pyd"

getting_started2.pyd: $(OBJ) getting_started2.obj
	$(LD) $(LDOPTS) $(OBJ) getting_started2.obj $(PYLIB) /export:initgetting_started2 /out:"getting_started2.pyd"

simple_vector.pyd: $(OBJ) simple_vector.obj
	$(LD) $(LDOPTS) $(OBJ) simple_vector.obj $(PYLIB) /export:initsimple_vector /out:"simple_vector.pyd"

do_it_yourself_converters.pyd: $(OBJ) do_it_yourself_converters.obj
	$(LD) $(LDOPTS) $(OBJ) do_it_yourself_converters.obj $(PYLIB) /export:initdo_it_yourself_converters /out:"do_it_yourself_converters.pyd"

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

richcmp.pyd: $(OBJ) richcmp.obj
	$(LD) $(LDOPTS) $(OBJ) richcmp.obj $(PYLIB) /export:initrichcmp /out:"richcmp.pyd"

.cpp.obj:
	$(CPP) $(CPPOPTS) /c $*.cpp

test:
	$(PYEXE) comprehensive.py --broken-auto-ptr 
	$(PYEXE) test_abstract.py
	$(PYEXE) test_getting_started1.py
	$(PYEXE) test_getting_started2.py
	$(PYEXE) test_simple_vector.py
	$(PYEXE) test_do_it_yourself_converters.py
	$(PYEXE) test_pickle1.py
	$(PYEXE) test_pickle2.py
	$(PYEXE) test_pickle3.py
	$(PYEXE) test_cross_module.py --broken-auto-ptr

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
