BIN=st2se
NAME=strace2seccomp

.PHONY: all clean run

all:
	@cd src/ && $(MAKE) release
	mkdir -p bin && mv ./src/$(BIN) ./bin/
	@echo -e "\033[1;37m" "Binary is located in" "\033[1;32m" "[project_root]/bin/" "\033[0m"
clean:
	-rm $(BIN) $(NAME).*
	@cd src/ && $(MAKE) clean

check:
	@cd src/ && $(MAKE) check

doxygen:
	cd src/ && doxygen doxyfile

dist: doc/man/ src/ Makefile README.md testsuite/ LICENSE seccomp_template/
	tar cvzf $(NAME).tar.gz $^
	zip -r $(NAME).zip $^

run:
	$(BIN)

