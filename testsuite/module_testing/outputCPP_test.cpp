#include <iostream>
#include <sys/stat.h>
#include <fcntl.h>
#include <sstream>
#include <unistd.h>
#include <string>

#include "catch2/catch.hpp"

#include "outputCPP.hpp"
#include "ids.hpp"

st2se::Syscall_t createSyscall(std::string name, int rc, std::string other, unsigned an, int a, std::string b, int c);

TEST_CASE("Output methods", "[Output]") {
	st2se::outputCPP *o = new st2se::outputCPP;

	o->threadSupport(true);
	REQUIRE(o->Output::genThreading);

    o->genFuncProlog(true);
    REQUIRE(o->Output::genProlog);

	delete o;

}


// This testcase is complex because it includes an initialization of IDS and
// then generating the output.
TEST_CASE("OutputCPP write methods", "[OutputCPP]") {

	// SETUP PHASE
	// -----------

	st2se::outputCPP *o = new st2se::outputCPP;
	st2se::Ids ids;

	// in this section we create a cluster and then we add to a cluster values.
	// In the first case we create a cluster only with one value and that is 1
	// The second cluster is empty 'cus write has second argument a string which
	// will be printed. The last cluster has two values 3 and 5. It represent
	// a range of values.

	// first cluster
	st2se::argument_t cluster;
	cluster.value_type = st2se::val_type_t::CLUSTERS;

	st2se::argument_t arg;
	arg.value_type = st2se::val_type_t::INTEGER;
	arg.value_format = st2se::val_format_t::VALUE;
	arg.value = 1;

	cluster.next.push_back(arg);

	st2se::Syscall_t sc;
	sc.name = "write";
	sc.arg_num = 3;
	sc.next.push_back(cluster);
	sc.clustered = true;

	// second cluster
	cluster.next.clear();
	arg.value_type = st2se::val_type_t::EMPTY;
	arg.value_format = st2se::val_format_t::EMPTY;
	arg.value = "";

	cluster.next.push_back(arg);
	sc.next.push_back(cluster);

	// third cluster
	cluster.next.clear();
	arg.value_type = st2se::val_type_t::INTEGER;
	arg.value_format = st2se::val_format_t::VALUE;
	arg.value = 3;

	cluster.next.push_back(arg);
	arg.value = 5;
	cluster.next.push_back(arg);

	sc.next.push_back(cluster);

	ids.data["write"] = sc;
	std::pair<std::string, st2se::Syscall_t> item_sc {ids.data["write"].name, ids.data["write"]};
	// end of initialization

	// Here we create a needed files for source code generation.
	struct stat st;
	if (stat("../seccomp_template", &st) == -1) {
	    mkdir("../seccomp_template", 0700);
	}

	creat("../seccomp_template/template.c.begin", S_IRWXU|S_IRWXG|S_IRWXO );
	creat("../seccomp_template/template.c.end", S_IRWXU|S_IRWXG|S_IRWXO );
	creat("../seccomp_template/template.c.thread", S_IRWXU|S_IRWXG|S_IRWXO );

	// GENERATE OUTPUT
	// ---------------

	o->openFiles();
	o->generateScRules(item_sc);


	std::string buf {};
	std::ifstream output {"./source.cpp"};
	std::vector<std::string> lines {
		{"    ret |= seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(write), 2,"},
    	{"        SCMP_A0(SCMP_CMP_EQ, 1u),"},
    	{"        SCMP_A2(SCMP_CMP_IN_RANGE, 3u, 5u)"},
    	{");"}
	};

	// read the source.cpp and compare it with expected output
	for(unsigned i = 0; i < 3; i++){
		std::getline(output, buf);
		INFO("Expected:\t '"+lines.at(i)+"'");
		INFO("Got:\t\t '"+buf+"'");
		REQUIRE_FALSE(buf.compare(lines.at(i)));
	}

	// release, close and reset environment
	o->closeFiles();

	output.close();

	remove("../seccomp_template/template.c.begin");
	remove("../seccomp_template/template.c.end");
	remove("../seccomp_template/template.c.thread");
	remove("../seccomp_template");
	remove("./source.cpp");
	delete o;

}