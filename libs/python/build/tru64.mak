#
# Tested with:
# Compaq C++ V6.2-024 for Digital UNIX V5.0 (Rev. 910)
#
# Python 1.5.2 was installed without any customizations.
# boost_all.zip vers. 1.18.1 was unpacked using unzip -aa and not modified.
# STLport-4.1b3 was unpacked using unzip -aa and not modified.
#
# Initial version 2000-10-20: Ralf W. Grosse-Kunstleve, rwgk@cci.lbl.gov
#

PYINC= /usr/local/include/python1.5
BOOSTINC= /usr/local/boost_1_18_1
STLPORTINC= /usr/local/STLport-4.1b3/stlport
STLPORTOPTS= \
 -D__USE_STD_IOSTREAM \
 -D__STL_NO_SGI_IOSTREAMS \
 -D__STL_NO_NEW_C_HEADERS \
 -D_RWSTD_COMPILE_INSTANTIATE=1

STDOPTS= -std strict_ansi
WARNOPTS= -msg_disable 186,450,1115
# use -msg_display_number to obtain integer tags for -msg_disable

CPP= cxx
CPPOPTS= -I$(STLPORTINC) $(STLPORTOPTS) -I$(BOOSTINC) -I$(PYINC) \
         $(STDOPTS) $(WARNOPTS)

LD= cxx
LDOPTS= -shared -expect_unresolved '*'

OBJ = extclass.o functions.o init_function.o module.o newtypes.o \
      objects.o py.o subclass.o

.SUFFIXES: .o .cpp

all: demo.so hello.so

demo.so: $(OBJ) extclass_demo.o
	$(LD) $(LDOPTS) $(OBJ) extclass_demo.o -o demo.so

hello.so: $(OBJ) example1.o
	$(LD) $(LDOPTS) $(OBJ) example1.o -o hello.so

.cpp.o:
	-$(CPP) $(CPPOPTS) $(INC) -c $*.cpp

clean:
	rm -f $(OBJ) extclass_demo.o example1.o demo.so hello.so so_locations
	rm -rf cxx_repository
	rm -f *.pyc
