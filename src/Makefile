# CXX=g++
CXX=clang++

OBJ=main.o straceparser.o ids.o argparse.o states.o optimizer.o algorithm.o\
	algorithm_weak.o algorithm_strict.o algorithm_advanced.o \
	generator.o output.o outputCPP.o
BIN=st2se
LDFLAGS=-Iinclude/
LINK.o = $(LINK.cpp)

ifeq ($(CXX),g++)
	CXXFLAGS:=-Wall -Wextra -pedantic -std=c++17 -Iinclude/ $(USER_DEFINES)
else
	CXXFLAGS:=-Wall -Wextra -pedantic -std=c++17 -stdlib=libc++ -Iinclude/ -I/usr/include/c++/7/ $(USER_DEFINES)
endif


all: CXXFLAGS += -g3 -fsanitize=address -fno-omit-frame-pointer
all: st2se

release: CXXFLAGS += -O2
release: st2se

coverage: CXXFLAGS += -fprofile-arcs -ftest-coverage
coverage: st2se run
	lcov --capture --directory ./ --output-file coverage.info
	genhtml coverage.info --output-directory=./html

tracing: CXXFLAGS += -DTRACING
tracing: all

st2se: $(OBJ)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(OBJ) -o $(BIN)

clangTidy:
	clang-tidy *.[ch]pp -checks=* -- -std=c++17 -stdlib=libc++ -I/usr/include/c++/7/ > lint.out

# Generate dependency tree for cpp files
dep:
	g++ *.cpp -Iinclude -MM >> Makefile

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

clean:
	-rm -f *.o
	-rm -f *.orig
	-rm -f $(BIN)
	-rm -f vgcore.* core.*
	-rm -rf ./html
	-rm -f *.gcda *.gcno coverage.info

# DEPS: generated with 'dep' recipe
algorithm_advanced.o: algorithm_advanced.cpp algorithm_advanced.hpp \
 ids.hpp algorithm.hpp
algorithm.o: algorithm.cpp algorithm.hpp ids.hpp
algorithm_strict.o: algorithm_strict.cpp algorithm_strict.hpp ids.hpp \
 algorithm.hpp
algorithm_weak.o: algorithm_weak.cpp algorithm_weak.hpp ids.hpp \
 algorithm.hpp
argparse.o: argparse.cpp argparse.hpp
generator.o: generator.cpp generator.hpp ids.hpp outputCPP.hpp output.hpp
ids.o: ids.cpp ids.hpp
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
 algorithm_advanced.hpp generator.hpp outputCPP.hpp output.hpp
optimizer.o: optimizer.cpp optimizer.hpp algorithm.hpp ids.hpp
output.o: output.cpp output.hpp ids.hpp
outputCPP.o: outputCPP.cpp outputCPP.hpp output.hpp ids.hpp
states.o: states.cpp states.hpp ids.hpp
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
