#include "catch2/catch.hpp"

#include "argparse.hpp"

struct values_t {
	int help {0};
    int weak {0};
    int strict {0};
    int advanced {0};
    int verbose {0};
    int debug {0};
    int tracing {0};
    int analysis {0};
    int thread {0};
    int prolog {0};
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

	return false;
}

std::string createArgv(const struct values_t &_values, const std::vector<std::string> &_file_names)
{
	std::string argv;

	if(_values.help != 0)
		argv.append("-h ");

	if(_values.weak != 0)
		argv.append("-w ");

	if(_values.strict != 0)
		argv.append("-s ");

	if(_values.advanced != 0)
		argv.append("-a ");

	if(_values.verbose != 0)
		argv.append("-v ");

	if(_values.debug != 0)
		argv.append("-d ");

	if(_values.tracing != 0)
		argv.append("-t ");

	if(_values.thread != 0)
		argv.append("--thread ");

	if(_values.prolog != 0)
		argv.append("--prolog ");

	if(_values.analysis != 0)
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

	std::string argv = createArgv(val, file_names);

	// Params p(argc, (char**)cnt);
}