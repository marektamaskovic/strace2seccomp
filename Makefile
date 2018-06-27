BIN=st2se

.PHONY: all clean run

all:
	@cd src/ && $(MAKE) $@
	mv ./src/$(BIN) ./

clean:
	rm $(BIN)
	@cd src/ && $(MAKE) clean

check_unit:
	pwd
	ls `pwd`
	cd testsuite/module_testing/  && $(MAKE)
	cd testsuite/module_testing/  && $(MAKE) run

xtamas01.tar.gz: src/ Makefile README.md
	tar tar cvzf $@ $^

run:
	$(BIN)

