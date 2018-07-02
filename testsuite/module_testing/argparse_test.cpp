#include "catch2/catch.hpp"

#include "argparse.hpp"

struct values_t {
	int help;
    int weak;
    int strict;
    int advanced;
    int verbose;
    int debug;
    int tracing;
    int analysis;
    int thread;
    int prolog;
    std::string output {};
};

bool operator==(const Params &a, const struct values_t &b) {
	if (
			(a.help == b.help) &&
			(a.weak == b.weak) &&
			(a.strict == b.strict) &&
			(a.advanced == b.advanced) &&
			(a.verbose == b.verbose) &&
			(a.debug == b.debug) &&
			(a.tracing == b.tracing) &&
			(a.analysis == b.analysis) &&
			(a.thread == b.thread) &&
			(a.prolog == b.prolog) &&
			!a.output.compare(b.output)
		)
	{
		return true;
	}
	else {
		return false;
	}
}

std::string createArgv(const struct values_t &_values, const std::vector<std::string> &_file_names)
{
	std::string argv;

	if(_values.help)
		argv.append("-h ");

	if(_values.weak)
		argv.append("-w ");

	if(_values.strict)
		argv.append("-s ");

	if(_values.advanced)
		argv.append("-a ");

	if(_values.verbose)
		argv.append("-v ");

	if(_values.debug)
		argv.append("-d ");

	if(_values.tracing)
		argv.append("-t ");

	if(_values.thread)
		argv.append("--thread ");

	if(_values.prolog)
		argv.append("--prolog ");

	if(_values.analysis)
		argv.append("-A ");

	for(auto item : _file_names){
		argv.append(item);
		argv.append(" ");
	}

	return argv;
}

int countArgv(const struct values_t &_values, const std::vector<std::string> &_file_names)
{
	int cnt = 0;

	if(_values.help)
		cnt++;

	if(_values.weak)
		cnt++;

	if(_values.strict)
		cnt++;

	if(_values.advanced)
		cnt++;

	if(_values.verbose)
		cnt++;

	if(_values.debug)
		cnt++;

	if(_values.tracing)
		cnt++;

	if(_values.thread)
		cnt++;

	if(_values.prolog)
		cnt++;


	if(_values.analysis)
		cnt++;

	cnt += _file_names.size();

	return cnt;
}

TEST_CASE("Argument parser", "[Argparse]") {

	struct values_t val{1,1,0,0,0,0,0,1,1,1, "out"};
	std::vector<std::string> file_names {"filename1"};

	int argc = countArgv(val, file_names);

	(void) argc;

	char cnt[argc][50] = {
		{'-', 'h', '\0'},
		{'-', 'w', '\0'},
		{'-', 'A', '\0'},
		{'-', '-', 't', 'h', 'r', 'e', 'a', 'd', '\0'},
		{'-', '-', 'p', 'r', 'o', 'l', 'o', 'g', '\0'},
		{'f', 'i', 'l', 'e', 'n', 'a', 'm', 'e', '1', '\0'}
	};

	std::string argv = createArgv(val, file_names);

	// Params p(argc, (char**)cnt);

	#warning
	// FIXME

}