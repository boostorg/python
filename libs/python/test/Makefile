include ../build/Makefile

LIBBPL = ../src/$(TARGET_LIBFILENAME)

test: test_result
	@if [ ! -f test_result -o -s test_result ] ; then \
           echo "tests failed:" ; cat test_result ; exit 1; \
         else echo "tests OK" ; fi

test_result:   testmodule$(MODULE_EXTENSION) comprehensive.py
	@rm -f test_result 
	python comprehensive.py > test_result

testmodule$(MODULE_EXTENSION): $(LIBBPL) comprehensive.o
	$(CXX_SHARED_LINKER) -o testmodule$(MODULE_EXTENSION) comprehensive.o $(LIBBPL)

clean:
	rm -rf *.o *$(MODULE_EXTENSION) *.a *.d *.pyc *.bak a.out test_result

