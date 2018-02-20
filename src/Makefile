CXX=g++
# CXX=clang++
CXXFLAGS=-Wall -Wextra -pedantic -Iinclude/ -std=c++17
LDFLAGS=-Iinclude/

OBJ=main.o straceparser.o ids.o argparse.o states.o
LINK.o = $(LINK.cpp)

all: CXXFLAGS += -g
all: main

release: CXXFLAGS += -O2
release: main

main: $(OBJ)

effc++: CXXFLAGS += -Weffc++
effc++: all

tracing: CXXFLAGS += -DTRACING
tracing: all

run:
	echo $(OS_VER)
	./main strace_ls.out

astyle: astylerc
	./astyle_script.sh

clean:
	-rm *.o
	-rm *.orig
