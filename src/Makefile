# CXX=g++
CXX=clang++
# CXXFLAGS=-Wall -Wextra -pedantic -Iinclude/ -std=c++17 -lc++abi
CXXFLAGS_DEFAULT=-Wall -Wextra -pedantic -Iinclude/ -std=c++17 -stdlib=libc++ 
CXXFLAGS=-Wall 
FLAGS_1=-fprofile-generate
FLAGS_2=-emit-llvm -c
CXXFLAGS_PROFILING=-stdlib=libc++ -std=c++17 -Iinclude/

LDFLAGS=-Iinclude/

OBJ=main.o straceparser.o ids.o argparse.o states.o optimizer.o algorithms.o
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

cfg: CXXFLAGS += -fdump-tree-cfg
cfg: $(OBJ)

cfg: CXXFLAGS += -fdump-tree-cfg
cfg: $(OBJ)

effc++: CXXFLAGS += -Weffc++
effc++: all

tracing: CXXFLAGS += -DTRACING
tracing: all

afl: CXX = afl-g++
afl: CXXFLAGS += -O2
afl: st2se

st2se: $(OBJ)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(OBJ) -o $(BIN)

run:
	@echo "========= TEST 1 ========" >out
	@echo "========= TEST 1 ========" >err
	./st2se dataset -w -d -v >>out 2>>err
	@echo "========= TEST 2 ========" >>out
	@echo "========= TEST 2 ========" >>err
	./st2se dataset -s -d -v >>out 2>>err
	@echo "========= TEST 3 ========" >>out
	@echo "========= TEST 3 ========" >>err
	./st2se dataset -a -d -v >>out 2>>err
	@echo "========= TEST 4 ========" >>out
	@echo "========= TEST 4 ========" >>err
	./st2se dataset -a -t -d -v >>out 2>>err
	@echo "========= TEST 4 ========" >>out
	@echo "========= TEST 4 ========" >>err
	./st2se -A >>out 2>>err

astyle: astylerc
	./astyle_script.sh

llvm_figures: llvm_figures_1 run llvm_figures_2

llvm_figures_1: CXXFLAGS := $(CXXFLAGS_DEFAULT) -fprofile-generate
llvm_figures_1: $(OBJ)
	clang++ $(CXXFLAGS) $(FLAGS_1) $(OBJ) -o $(BIN)

llvm_figures_2: CXXFLAGS := $(CXXFLAGS_DEFAULT)
llvm_figures_2:
	$(eval PROFRAW_FILES=$(shell ls | grep profraw))
	$(shell llvm-profdata merge -output=merge.profdata $(PROFRAW_FILES))
	clang++ $(CXXFLAGS) -fprofile-use=merge.profdata $(FLAGS_2) main.cpp -o main.bc 
	clang++ $(CXXFLAGS) -fprofile-use=merge.profdata $(FLAGS_2) straceparser.cpp -o straceparser.bc
	clang++ $(CXXFLAGS) -fprofile-use=merge.profdata $(FLAGS_2) ids.cpp -o ids.bc
	clang++ $(CXXFLAGS) -fprofile-use=merge.profdata $(FLAGS_2) argparse.cpp -o argparse.bc
	clang++ $(CXXFLAGS) -fprofile-use=merge.profdata $(FLAGS_2) states.cpp -o states.bc
	clang++ $(CXXFLAGS) -fprofile-use=merge.profdata $(FLAGS_2) optimizer.cpp -o optimizer.bc
	clang++ $(CXXFLAGS) -fprofile-use=merge.profdata $(FLAGS_2) algorithms.cpp -o algorithms.bc

clean:
	-rm *.o
	-rm *.orig
	-rm $(BIN)
	-rm vgcore.* core.*
	-rm -r ./html
	-rm *.gcda *.gcno coverage.info
	-rm *.cfg *.bc 

# DEPS: generated with g++ -MM *.cpp -Iinclude # removed taopegtl stuff
algorithms.o: algorithms.cpp algorithms.hpp ids.hpp
argparse.o: argparse.cpp argparse.hpp
ids.o: ids.cpp ids.hpp
main.o: main.cpp straceparser_grammar.hpp states.hpp ids.hpp optimizer.hpp algorithms.hpp
optimizer.o: optimizer.cpp optimizer.hpp algorithms.hpp ids.hpp
states.o: states.cpp states.hpp ids.hpp
straceparser.o: straceparser.cpp straceparser.hpp straceparser_grammar.hpp argparse.hpp states.hpp ids.hpp
