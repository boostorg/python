all: lib test


lib::
	@cd src ; $(MAKE) lib ; cd ..

test::
	@cd test ; $(MAKE) test ; cd ..

install: all
	@cd src ; $(MAKE) install ; cd ..

clean:
	@cd src ; $(MAKE) clean ; cd ..
	@cd test ; $(MAKE) clean ; cd ..
