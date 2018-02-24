CXX=g++
# CXX=clang++
CXXFLAGS=-Wall -Wextra -pedantic -Iinclude/ -std=c++17
LDFLAGS=-Iinclude/

OBJ=main.o straceparser.o ids.o argparse.o states.o
BIN=st2se
LINK.o = $(LINK.cpp)

all: CXXFLAGS += -g3
all: st2se

release: CXXFLAGS += -O2
release: st2se

st2se: $(OBJ)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(OBJ) -o $(BIN)

effc++: CXXFLAGS += -Weffc++
effc++: all

tracing: CXXFLAGS += -DTRACING
tracing: all

run:
	./st2se test20

astyle: astylerc
	./astyle_script.sh

clean:
	-rm *.o
	-rm *.orig
	-rm $(BIN)
	-rm vgcore.*
