// Copyright (c) 2018 Red Hat <mtamasko@redhat.com>
// Author: Marek Tamaskovic <tamaskovic.marek@gmail.com>
//
// This file is part of strace2seccomp tool.
//
// strace2seccomp tool is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// strace2seccomp tool is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with strace2seccomp tool.  If not, see <https://www.gnu.org/licenses/>.

#include <iostream>

#include "../../src/argparse.hpp"

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
	return false;
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


int testClass(const struct values_t &_values, const std::vector<std::string> &_file_names)
{

	int argc = countArgv(_values, _file_names);

	(void) argc;

	char *cnt[argc];

	std::string argv = createArgv(_values, _file_names);

	Params p(argc, (char**)argv.data());

	return 0;
}

int main() {

	struct values_t val{1,1,0,0,0,0,0,1,1,1, "out"};
	std::vector<std::string> file_names {"filename1"};
	int ret {0};

	ret = testClass(val, file_names);

	return ret;
}
