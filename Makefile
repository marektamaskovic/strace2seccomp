BIN=st2se

.PHONY: all clean run

all:
	@cd src/ && $(MAKE) $@
	mv ./src/$(BIN) ./

clean:
	rm $(BIN)
	@cd src/ && $(MAKE) clean

xtamas01.tar.gz: src/ Makefile README.md
	tar tar cvzf $@ $^

run:
	$(BIN)

