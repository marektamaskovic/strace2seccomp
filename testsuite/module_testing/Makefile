CXX=g++
CXXFLAGS=-Wall -Wextra -pedantic -std=c++17 -I./catch2/ -g
LINK.o = $(LINK.cpp)

BIN=params_test ids_test

all: $(BIN)

params_test: params_test.o argparse.o

ids_test:ids_test.o ids.o

clean:
	-rm *.o
	-rm $(BIN)
