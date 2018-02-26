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

coverage: CXXFLAGS += -fprofile-arcs -ftest-coverage
coverage: st2se run
	lcov --capture --directory ./ --output-file coverage.info
	genhtml coverage.info --output-directory=./html

st2se: $(OBJ)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(OBJ) -o $(BIN)

cfg: CXXFLAGS += -fdump-tree-cfg
cfg: $(OBJ)

effc++: CXXFLAGS += -Weffc++
effc++: all

tracing: CXXFLAGS += -DTRACING
tracing: all

run:
	./st2se test7871 -d -v >out 2>err

astyle: astylerc
	./astyle_script.sh

clean:
	-rm *.o
	-rm *.orig
	-rm $(BIN)
	-rm vgcore.*
	-rm -r ./html
	-rm *.gcda *.gcno coverage.info
	-rm *.cfg
