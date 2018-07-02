CXX=g++
CXXFLAGS=-Wall -Wextra -pedantic -std=c++17 -I./catch2/ -g
LINK.o = $(LINK.cpp)

# BIN=params_test ids_test
BIN=test_main

all: $(BIN)

params_test: params_test.o argparse.o

test_main: ids_test.o ids.o outputCPP_test.o outputCPP.o output.o argparse.o \
			argparse_test.o generator.o generator_test.o states.o states_test.o\


run:
	./$(BIN)

clean:
	-rm *.o
	-rm $(BIN)
