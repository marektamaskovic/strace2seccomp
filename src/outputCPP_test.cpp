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

#include <fcntl.h>
#include <iostream>
#include <sstream>
#include <string>
#include <sys/stat.h>
#include <unistd.h>

#include "catch2/catch.hpp"

#include "ids.hpp"
#include "outputCPP.hpp"

st2se::Syscall createSyscall(std::string name, int rc, std::string other, unsigned an, int a, std::string b, int c);

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
    st2se::Argument cluster;
    cluster.valueType = st2se::ValueType::CLUSTERS;

    st2se::Argument arg;
    arg.valueType = st2se::ValueType::INTEGER;
    arg.valueFormat = st2se::ValueFormat::VALUE;
    arg.value = 1;

    cluster.next.push_back(arg);

    st2se::Syscall sc;
    sc.name = "write";
    sc.arg_num = 3;
    sc.next.push_back(cluster);
    sc.clustered = true;

    // second cluster
    cluster.next.clear();
    arg.valueType = st2se::ValueType::EMPTY;
    arg.valueFormat = st2se::ValueFormat::EMPTY;
    arg.value = "";

    cluster.next.push_back(arg);
    sc.next.push_back(cluster);

    // third cluster
    cluster.next.clear();
    arg.valueType = st2se::ValueType::INTEGER;
    arg.valueFormat = st2se::ValueFormat::VALUE;
    arg.value = 5;

    cluster.next.push_back(arg);
    arg.value = 3;
    cluster.next.push_back(arg);

    sc.next.push_back(cluster);

    ids.data["write"] = sc;
    std::pair<std::string, st2se::Syscall> item_sc {ids.data["write"].name, ids.data["write"]};
    // end of initialization

    // Here we create a needed files for source code generation.
    struct stat st;

    if (stat("../seccomp_template", &st) == -1) {
        FAIL("seccomp_template/ folder not found");
    }

    // GENERATE OUTPUT
    // ---------------

    o->openFiles();
    o->generateScRules(item_sc);

    std::string buf {};
    std::ifstream output {"./source.cpp"};
    std::vector<std::string> lines {
        {"ret |= seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(write), 2,"},
        {"    SCMP_A0(SCMP_CMP_EQ, 1u),"},
        {"    SCMP_A2(SCMP_CMP_IN_RANGE, 3u, 5u)"},
        {");"}
    };

    // read the source.cpp and compare it with expected output
    for (unsigned i = 0; i < 3; i++) {
        std::getline(output, buf);
        INFO("Expected:\t '" + lines.at(i) + "'");
        INFO("Got:\t\t '" + buf + "'");
        REQUIRE_FALSE(buf.compare(lines.at(i)));
    }

    // release, close and reset environment
    o->closeFiles();

    output.close();

    remove("./source.cpp");

    delete o;

}
