BIN=main

.PHONY: all clean run

all:
	@cd src/ && $(MAKE) $@
	mv ./src/$(BIN) ./

clean:
	rm $(BIN)
	@cd src/ && $(MAKE) clean

run:
	$(BIN)

