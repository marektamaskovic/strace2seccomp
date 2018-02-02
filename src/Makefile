CC=g++
CXXFLAGS=-Wall -Wextra -pedantic -std=c++17 -g -Iinclude/
LDFLAGS=-Iinclude/

OBJ=main.o straceparser.o argparse.o ids.o

all: main

main: $(OBJ)

run: all
	./main strace_ls.out

astyle: astylerc
	astyle $(< ./astylerc) *.[ch]pp

clean:
	-rm *.o
	-rm main
