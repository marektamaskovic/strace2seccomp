BIN=st2se

.PHONY: all clean run

all:
	@cd src/ && $(MAKE) $@
	mv ./src/$(BIN) ./

clean:
	rm $(BIN)
	@cd src/ && $(MAKE) clean

check:
	@cd src/ && $(MAKE) check

doxygen:
	cd src/ && doxygen doxyfile

xtamas01.tar.gz: doc/man/ src/ Makefile README.md testsuite/ Vagrantfile
	tar cvzf $@ $^

run:
	$(BIN)

