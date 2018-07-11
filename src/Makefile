# Makefile for st2se
# ------------------
#  Author: Marek Tamaskovic
#  - xtamas01.stud.fit.vutbr.cz
#  - mtamasko.redhat.com
#  Project: strace2seccomp - st2se
#  Compiled:  insert uname -a
#  Note:

# Variables
# ---------

# CXX=/opt/intel/system_studio_2018/compilers_and_libraries/linux/bin/intel64/icc
CXX=g++
# CXX=clang++

OBJ=main.o straceparser.o ids.o argparse.o states.o optimizer.o algorithm.o \
	algorithm_weak.o algorithm_strict.o algorithm_advanced.o \
	generator.o output.o outputCPP.o format.o posix.o

OBJ_TEST=ids_test.o ids.o outputCPP_test.o outputCPP.o output.o argparse.o  \
		argparse_test.o generator.o generator_test.o states.o states_test.o \
		format.o posix.o test_main.o

BIN=st2se
BIN_TEST=module_tests
LINK.o = $(LINK.cpp)
DATASET=../testdata/dataset.reduced
CXXFLAGS:=-Wall -Wextra -pedantic -std=c++17 -Iinclude/ $(USER_DEFINES)


# Recipes
# -------
all: CXXFLAGS += -g3 -fsanitize=address,undefined -fno-omit-frame-pointer
# all: CXXFLAGS += -g3
all: st2se

release: CXXFLAGS += -Ofast -march=native -flto
release: st2se

coverage: CXXFLAGS += -fprofile-arcs -ftest-coverage
coverage: st2se run
	lcov --capture --directory ./ --output-file coverage.info
	genhtml coverage.info --output-directory=./html

tracing: CXXFLAGS += -DTRACING
tracing: all

st2se: $(OBJ)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(OBJ) -o $(BIN)

#Module tests
check: $(OBJ_TEST)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(OBJ_TEST) -o $(BIN_TEST)
	./$(BIN_TEST)


# static analysis
clangTidy:
	clang-tidy *.[ch]pp -checks=* -- -std=c++17 > lint.out

# Generate dependency tree for cpp files
dep:
	g++ *.cpp -Iinclude -MM >> Makefile

# TODO
# move to tests
# Paramatrize dataset file
run:
	@echo "========= TEST 1 ========" >out
	@echo "========= TEST 1 ========" >err
	./st2se $(DATASET) -w -d -v >>out 2>>err
	@echo "========= TEST 2 ========" >>out
	@echo "========= TEST 2 ========" >>err
	./st2se $(DATASET) -s -d -v >>out 2>>err
	@echo "========= TEST 3 ========" >>out
	@echo "========= TEST 3 ========" >>err
	./st2se $(DATASET) -a -d -v >>out 2>>err
	@echo "========= TEST 4 ========" >>out
	@echo "========= TEST 4 ========" >>err
	./st2se $(DATASET) -a -t -d -v >>out 2>>err
	@echo "========= TEST 4 ========" >>out
	@echo "========= TEST 4 ========" >>err
	./st2se -A >>out 2>>err

astyle: astylerc
	./astyle_script.sh

# Clean project folder
clean:
	-rm -f *.o
	-rm -f *.orig
	-rm -f $(BIN)
	-rm -f $(BIN_TEST)
	-rm -f vgcore.* core.* lint.out
	-rm -rf ./html
	-rm -f *.gcda *.gcno coverage.info

# DEPS: generated with 'dep' recipe
# ---------------------------------
algorithm_advanced.o: algorithm_advanced.cpp algorithm_advanced.hpp \
 ids.hpp algorithm.hpp
algorithm.o: algorithm.cpp algorithm.hpp ids.hpp
algorithm_strict.o: algorithm_strict.cpp algorithm_strict.hpp ids.hpp \
 algorithm.hpp
algorithm_weak.o: algorithm_weak.cpp algorithm_weak.hpp ids.hpp \
 algorithm.hpp
argparse.o: argparse.cpp argparse.hpp
argparse_test.o: argparse_test.cpp include/catch2/catch.hpp argparse.hpp
generator.o: generator.cpp generator.hpp ids.hpp outputCPP.hpp \
 include/fmt/core.h include/fmt/format.h include/fmt/core.h output.hpp \
 argparse.hpp
generator_test.o: generator_test.cpp include/catch2/catch.hpp \
 generator.hpp ids.hpp outputCPP.hpp include/fmt/core.h \
 include/fmt/format.h include/fmt/core.h output.hpp argparse.hpp
ids.o: ids.cpp ids.hpp
ids_test.o: ids_test.cpp include/catch2/catch.hpp ids.hpp
main.o: main.cpp include/tao/pegtl.hpp include/tao/pegtl/config.hpp \
 include/tao/pegtl/version.hpp include/tao/pegtl/ascii.hpp \
 include/tao/pegtl/config.hpp include/tao/pegtl/eol.hpp \
 include/tao/pegtl/internal/eol.hpp \
 include/tao/pegtl/internal/../config.hpp \
 include/tao/pegtl/internal/skip_control.hpp \
 include/tao/pegtl/internal/../analysis/generic.hpp \
 include/tao/pegtl/internal/../analysis/../config.hpp \
 include/tao/pegtl/internal/../analysis/grammar_info.hpp \
 include/tao/pegtl/internal/../analysis/../internal/demangle.hpp \
 include/tao/pegtl/internal/../analysis/../internal/../config.hpp \
 include/tao/pegtl/internal/../analysis/../internal/demangle_cxxabi.hpp \
 include/tao/pegtl/internal/../analysis/../internal/demangle_sanitise.hpp \
 include/tao/pegtl/internal/../analysis/rule_info.hpp \
 include/tao/pegtl/internal/../analysis/rule_type.hpp \
 include/tao/pegtl/internal/../analysis/insert_rules.hpp \
 include/tao/pegtl/internal/cr_crlf_eol.hpp \
 include/tao/pegtl/internal/../eol_pair.hpp \
 include/tao/pegtl/internal/../config.hpp \
 include/tao/pegtl/internal/cr_eol.hpp \
 include/tao/pegtl/internal/crlf_eol.hpp \
 include/tao/pegtl/internal/lf_crlf_eol.hpp \
 include/tao/pegtl/internal/lf_eol.hpp \
 include/tao/pegtl/internal/result_on_found.hpp \
 include/tao/pegtl/internal/rules.hpp \
 include/tao/pegtl/internal/action.hpp \
 include/tao/pegtl/internal/duseltronik.hpp \
 include/tao/pegtl/internal/../apply_mode.hpp \
 include/tao/pegtl/internal/../rewind_mode.hpp \
 include/tao/pegtl/internal/dusel_mode.hpp \
 include/tao/pegtl/internal/seq.hpp \
 include/tao/pegtl/internal/rule_conjunction.hpp \
 include/tao/pegtl/internal/trivial.hpp \
 include/tao/pegtl/internal/../analysis/counted.hpp \
 include/tao/pegtl/internal/../analysis/generic.hpp \
 include/tao/pegtl/internal/alnum.hpp \
 include/tao/pegtl/internal/peek_char.hpp \
 include/tao/pegtl/internal/input_pair.hpp \
 include/tao/pegtl/internal/ranges.hpp \
 include/tao/pegtl/internal/bump_help.hpp \
 include/tao/pegtl/internal/result_on_found.hpp \
 include/tao/pegtl/internal/range.hpp \
 include/tao/pegtl/internal/alpha.hpp include/tao/pegtl/internal/any.hpp \
 include/tao/pegtl/internal/apply.hpp \
 include/tao/pegtl/internal/apply_single.hpp \
 include/tao/pegtl/internal/apply0.hpp \
 include/tao/pegtl/internal/apply0_single.hpp \
 include/tao/pegtl/internal/at.hpp include/tao/pegtl/internal/bof.hpp \
 include/tao/pegtl/internal/bol.hpp include/tao/pegtl/internal/bytes.hpp \
 include/tao/pegtl/internal/control.hpp \
 include/tao/pegtl/internal/disable.hpp \
 include/tao/pegtl/internal/discard.hpp \
 include/tao/pegtl/internal/enable.hpp include/tao/pegtl/internal/eof.hpp \
 include/tao/pegtl/internal/eol.hpp include/tao/pegtl/internal/eolf.hpp \
 include/tao/pegtl/internal/identifier.hpp \
 include/tao/pegtl/internal/star.hpp \
 include/tao/pegtl/internal/if_apply.hpp \
 include/tao/pegtl/internal/if_must.hpp \
 include/tao/pegtl/internal/must.hpp include/tao/pegtl/internal/raise.hpp \
 include/tao/pegtl/internal/if_must_else.hpp \
 include/tao/pegtl/internal/if_then_else.hpp \
 include/tao/pegtl/internal/not_at.hpp include/tao/pegtl/internal/sor.hpp \
 include/tao/pegtl/internal/integer_sequence.hpp \
 include/tao/pegtl/internal/istring.hpp \
 include/tao/pegtl/internal/list.hpp \
 include/tao/pegtl/internal/list_must.hpp \
 include/tao/pegtl/internal/list_tail.hpp \
 include/tao/pegtl/internal/opt.hpp \
 include/tao/pegtl/internal/list_tail_pad.hpp \
 include/tao/pegtl/internal/pad.hpp include/tao/pegtl/internal/minus.hpp \
 include/tao/pegtl/internal/../memory_input.hpp \
 include/tao/pegtl/internal/../eol.hpp \
 include/tao/pegtl/internal/../position.hpp \
 include/tao/pegtl/internal/../internal/iterator.hpp \
 include/tao/pegtl/internal/../internal/../config.hpp \
 include/tao/pegtl/internal/../tracking_mode.hpp \
 include/tao/pegtl/internal/../internal/action_input.hpp \
 include/tao/pegtl/internal/../internal/iterator.hpp \
 include/tao/pegtl/internal/../internal/../position.hpp \
 include/tao/pegtl/internal/../internal/bump_impl.hpp \
 include/tao/pegtl/internal/../internal/marker.hpp \
 include/tao/pegtl/internal/../internal/../rewind_mode.hpp \
 include/tao/pegtl/internal/one.hpp \
 include/tao/pegtl/internal/pad_opt.hpp \
 include/tao/pegtl/internal/plus.hpp include/tao/pegtl/internal/rep.hpp \
 include/tao/pegtl/internal/rep_min.hpp \
 include/tao/pegtl/internal/rep_min_max.hpp \
 include/tao/pegtl/internal/rep_opt.hpp \
 include/tao/pegtl/internal/require.hpp \
 include/tao/pegtl/internal/star_must.hpp \
 include/tao/pegtl/internal/state.hpp \
 include/tao/pegtl/internal/string.hpp \
 include/tao/pegtl/internal/try_catch_type.hpp \
 include/tao/pegtl/internal/until.hpp \
 include/tao/pegtl/internal/pegtl_string.hpp \
 include/tao/pegtl/internal/../ascii.hpp include/tao/pegtl/parse.hpp \
 include/tao/pegtl/apply_mode.hpp include/tao/pegtl/normal.hpp \
 include/tao/pegtl/nothing.hpp include/tao/pegtl/parse_error.hpp \
 include/tao/pegtl/position.hpp include/tao/pegtl/rewind_mode.hpp \
 include/tao/pegtl/internal/demangle.hpp \
 include/tao/pegtl/internal/dusel_mode.hpp \
 include/tao/pegtl/internal/duseltronik.hpp \
 include/tao/pegtl/internal/has_apply.hpp \
 include/tao/pegtl/internal/has_apply0.hpp \
 include/tao/pegtl/internal/skip_control.hpp include/tao/pegtl/rules.hpp \
 include/tao/pegtl/utf16.hpp include/tao/pegtl/internal/peek_utf16.hpp \
 include/tao/pegtl/utf32.hpp include/tao/pegtl/internal/peek_utf32.hpp \
 include/tao/pegtl/utf8.hpp include/tao/pegtl/internal/peek_utf8.hpp \
 include/tao/pegtl/argv_input.hpp include/tao/pegtl/memory_input.hpp \
 include/tao/pegtl/tracking_mode.hpp include/tao/pegtl/buffer_input.hpp \
 include/tao/pegtl/internal/action_input.hpp \
 include/tao/pegtl/internal/bump_impl.hpp \
 include/tao/pegtl/internal/iterator.hpp \
 include/tao/pegtl/internal/marker.hpp \
 include/tao/pegtl/cstream_input.hpp include/tao/pegtl/buffer_input.hpp \
 include/tao/pegtl/internal/cstream_reader.hpp \
 include/tao/pegtl/internal/../input_error.hpp \
 include/tao/pegtl/file_input.hpp include/tao/pegtl/mmap_input.hpp \
 include/tao/pegtl/internal/file_mapper.hpp \
 include/tao/pegtl/internal/file_opener.hpp \
 include/tao/pegtl/istream_input.hpp \
 include/tao/pegtl/internal/istream_reader.hpp \
 include/tao/pegtl/memory_input.hpp include/tao/pegtl/read_input.hpp \
 include/tao/pegtl/string_input.hpp \
 include/tao/pegtl/internal/file_reader.hpp \
 include/tao/pegtl/string_input.hpp argparse.hpp ids.hpp optimizer.hpp \
 algorithm.hpp states.hpp straceparser.hpp \
 include/tao/pegtl/contrib/tracer.hpp \
 include/tao/pegtl/contrib/../config.hpp \
 include/tao/pegtl/contrib/../normal.hpp \
 include/tao/pegtl/contrib/../internal/demangle.hpp \
 include/tao/pegtl/analyze.hpp \
 include/tao/pegtl/analysis/analyze_cycles.hpp \
 include/tao/pegtl/analysis/../config.hpp \
 include/tao/pegtl/analysis/grammar_info.hpp \
 include/tao/pegtl/analysis/insert_guard.hpp straceparser_actions.hpp \
 straceparser_grammar.hpp algorithm_weak.hpp algorithm_strict.hpp \
 algorithm_advanced.hpp generator.hpp outputCPP.hpp include/fmt/core.h \
 include/fmt/format.h include/fmt/core.h output.hpp
optimizer.o: optimizer.cpp optimizer.hpp algorithm.hpp ids.hpp
output.o: output.cpp output.hpp ids.hpp
outputCPP.o: outputCPP.cpp outputCPP.hpp include/fmt/core.h \
 include/fmt/format.h include/fmt/core.h output.hpp ids.hpp
outputCPP_test.o: outputCPP_test.cpp include/catch2/catch.hpp ids.hpp \
 outputCPP.hpp include/fmt/core.h include/fmt/format.h include/fmt/core.h \
 output.hpp
params_test.o: params_test.cpp include/../../src/argparse.hpp
states.o: states.cpp states.hpp ids.hpp
states_test.o: states_test.cpp include/catch2/catch.hpp ids.hpp \
 states.hpp
straceparser.o: straceparser.cpp straceparser.hpp include/tao/pegtl.hpp \
 include/tao/pegtl/config.hpp include/tao/pegtl/version.hpp \
 include/tao/pegtl/ascii.hpp include/tao/pegtl/config.hpp \
 include/tao/pegtl/eol.hpp include/tao/pegtl/internal/eol.hpp \
 include/tao/pegtl/internal/../config.hpp \
 include/tao/pegtl/internal/skip_control.hpp \
 include/tao/pegtl/internal/../analysis/generic.hpp \
 include/tao/pegtl/internal/../analysis/../config.hpp \
 include/tao/pegtl/internal/../analysis/grammar_info.hpp \
 include/tao/pegtl/internal/../analysis/../internal/demangle.hpp \
 include/tao/pegtl/internal/../analysis/../internal/../config.hpp \
 include/tao/pegtl/internal/../analysis/../internal/demangle_cxxabi.hpp \
 include/tao/pegtl/internal/../analysis/../internal/demangle_sanitise.hpp \
 include/tao/pegtl/internal/../analysis/rule_info.hpp \
 include/tao/pegtl/internal/../analysis/rule_type.hpp \
 include/tao/pegtl/internal/../analysis/insert_rules.hpp \
 include/tao/pegtl/internal/cr_crlf_eol.hpp \
 include/tao/pegtl/internal/../eol_pair.hpp \
 include/tao/pegtl/internal/../config.hpp \
 include/tao/pegtl/internal/cr_eol.hpp \
 include/tao/pegtl/internal/crlf_eol.hpp \
 include/tao/pegtl/internal/lf_crlf_eol.hpp \
 include/tao/pegtl/internal/lf_eol.hpp \
 include/tao/pegtl/internal/result_on_found.hpp \
 include/tao/pegtl/internal/rules.hpp \
 include/tao/pegtl/internal/action.hpp \
 include/tao/pegtl/internal/duseltronik.hpp \
 include/tao/pegtl/internal/../apply_mode.hpp \
 include/tao/pegtl/internal/../rewind_mode.hpp \
 include/tao/pegtl/internal/dusel_mode.hpp \
 include/tao/pegtl/internal/seq.hpp \
 include/tao/pegtl/internal/rule_conjunction.hpp \
 include/tao/pegtl/internal/trivial.hpp \
 include/tao/pegtl/internal/../analysis/counted.hpp \
 include/tao/pegtl/internal/../analysis/generic.hpp \
 include/tao/pegtl/internal/alnum.hpp \
 include/tao/pegtl/internal/peek_char.hpp \
 include/tao/pegtl/internal/input_pair.hpp \
 include/tao/pegtl/internal/ranges.hpp \
 include/tao/pegtl/internal/bump_help.hpp \
 include/tao/pegtl/internal/result_on_found.hpp \
 include/tao/pegtl/internal/range.hpp \
 include/tao/pegtl/internal/alpha.hpp include/tao/pegtl/internal/any.hpp \
 include/tao/pegtl/internal/apply.hpp \
 include/tao/pegtl/internal/apply_single.hpp \
 include/tao/pegtl/internal/apply0.hpp \
 include/tao/pegtl/internal/apply0_single.hpp \
 include/tao/pegtl/internal/at.hpp include/tao/pegtl/internal/bof.hpp \
 include/tao/pegtl/internal/bol.hpp include/tao/pegtl/internal/bytes.hpp \
 include/tao/pegtl/internal/control.hpp \
 include/tao/pegtl/internal/disable.hpp \
 include/tao/pegtl/internal/discard.hpp \
 include/tao/pegtl/internal/enable.hpp include/tao/pegtl/internal/eof.hpp \
 include/tao/pegtl/internal/eol.hpp include/tao/pegtl/internal/eolf.hpp \
 include/tao/pegtl/internal/identifier.hpp \
 include/tao/pegtl/internal/star.hpp \
 include/tao/pegtl/internal/if_apply.hpp \
 include/tao/pegtl/internal/if_must.hpp \
 include/tao/pegtl/internal/must.hpp include/tao/pegtl/internal/raise.hpp \
 include/tao/pegtl/internal/if_must_else.hpp \
 include/tao/pegtl/internal/if_then_else.hpp \
 include/tao/pegtl/internal/not_at.hpp include/tao/pegtl/internal/sor.hpp \
 include/tao/pegtl/internal/integer_sequence.hpp \
 include/tao/pegtl/internal/istring.hpp \
 include/tao/pegtl/internal/list.hpp \
 include/tao/pegtl/internal/list_must.hpp \
 include/tao/pegtl/internal/list_tail.hpp \
 include/tao/pegtl/internal/opt.hpp \
 include/tao/pegtl/internal/list_tail_pad.hpp \
 include/tao/pegtl/internal/pad.hpp include/tao/pegtl/internal/minus.hpp \
 include/tao/pegtl/internal/../memory_input.hpp \
 include/tao/pegtl/internal/../eol.hpp \
 include/tao/pegtl/internal/../position.hpp \
 include/tao/pegtl/internal/../internal/iterator.hpp \
 include/tao/pegtl/internal/../internal/../config.hpp \
 include/tao/pegtl/internal/../tracking_mode.hpp \
 include/tao/pegtl/internal/../internal/action_input.hpp \
 include/tao/pegtl/internal/../internal/iterator.hpp \
 include/tao/pegtl/internal/../internal/../position.hpp \
 include/tao/pegtl/internal/../internal/bump_impl.hpp \
 include/tao/pegtl/internal/../internal/marker.hpp \
 include/tao/pegtl/internal/../internal/../rewind_mode.hpp \
 include/tao/pegtl/internal/one.hpp \
 include/tao/pegtl/internal/pad_opt.hpp \
 include/tao/pegtl/internal/plus.hpp include/tao/pegtl/internal/rep.hpp \
 include/tao/pegtl/internal/rep_min.hpp \
 include/tao/pegtl/internal/rep_min_max.hpp \
 include/tao/pegtl/internal/rep_opt.hpp \
 include/tao/pegtl/internal/require.hpp \
 include/tao/pegtl/internal/star_must.hpp \
 include/tao/pegtl/internal/state.hpp \
 include/tao/pegtl/internal/string.hpp \
 include/tao/pegtl/internal/try_catch_type.hpp \
 include/tao/pegtl/internal/until.hpp \
 include/tao/pegtl/internal/pegtl_string.hpp \
 include/tao/pegtl/internal/../ascii.hpp include/tao/pegtl/parse.hpp \
 include/tao/pegtl/apply_mode.hpp include/tao/pegtl/normal.hpp \
 include/tao/pegtl/nothing.hpp include/tao/pegtl/parse_error.hpp \
 include/tao/pegtl/position.hpp include/tao/pegtl/rewind_mode.hpp \
 include/tao/pegtl/internal/demangle.hpp \
 include/tao/pegtl/internal/dusel_mode.hpp \
 include/tao/pegtl/internal/duseltronik.hpp \
 include/tao/pegtl/internal/has_apply.hpp \
 include/tao/pegtl/internal/has_apply0.hpp \
 include/tao/pegtl/internal/skip_control.hpp include/tao/pegtl/rules.hpp \
 include/tao/pegtl/utf16.hpp include/tao/pegtl/internal/peek_utf16.hpp \
 include/tao/pegtl/utf32.hpp include/tao/pegtl/internal/peek_utf32.hpp \
 include/tao/pegtl/utf8.hpp include/tao/pegtl/internal/peek_utf8.hpp \
 include/tao/pegtl/argv_input.hpp include/tao/pegtl/memory_input.hpp \
 include/tao/pegtl/tracking_mode.hpp include/tao/pegtl/buffer_input.hpp \
 include/tao/pegtl/internal/action_input.hpp \
 include/tao/pegtl/internal/bump_impl.hpp \
 include/tao/pegtl/internal/iterator.hpp \
 include/tao/pegtl/internal/marker.hpp \
 include/tao/pegtl/cstream_input.hpp include/tao/pegtl/buffer_input.hpp \
 include/tao/pegtl/internal/cstream_reader.hpp \
 include/tao/pegtl/internal/../input_error.hpp \
 include/tao/pegtl/file_input.hpp include/tao/pegtl/mmap_input.hpp \
 include/tao/pegtl/internal/file_mapper.hpp \
 include/tao/pegtl/internal/file_opener.hpp \
 include/tao/pegtl/istream_input.hpp \
 include/tao/pegtl/internal/istream_reader.hpp \
 include/tao/pegtl/memory_input.hpp include/tao/pegtl/read_input.hpp \
 include/tao/pegtl/string_input.hpp \
 include/tao/pegtl/internal/file_reader.hpp \
 include/tao/pegtl/string_input.hpp include/tao/pegtl/contrib/tracer.hpp \
 include/tao/pegtl/contrib/../config.hpp \
 include/tao/pegtl/contrib/../normal.hpp \
 include/tao/pegtl/contrib/../internal/demangle.hpp \
 include/tao/pegtl/analyze.hpp \
 include/tao/pegtl/analysis/analyze_cycles.hpp \
 include/tao/pegtl/analysis/../config.hpp \
 include/tao/pegtl/analysis/grammar_info.hpp \
 include/tao/pegtl/analysis/insert_guard.hpp straceparser_actions.hpp \
 straceparser_grammar.hpp argparse.hpp states.hpp ids.hpp
test_main.o: test_main.cpp include/catch2/catch.hpp
