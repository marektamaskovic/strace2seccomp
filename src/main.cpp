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

#include "tao/pegtl.hpp"

#include "argparse.hpp"
#include "ids.hpp"
#include "optimizer.hpp"
#include "states.hpp"
#include "straceparser.hpp"
#include "algorithm_weak.hpp"
#include "algorithm_strict.hpp"
#include "algorithm_advanced.hpp"
#include "generator.hpp"

int main(int argc, char *argv[]) {

    int ret_val {0};

    Params params(argc, argv);

    if (params.debug) {
        std::cout << params << std::endl;
    }

    // print usage when no algorithm was emitted
    if (!params.strict && !params.weak && !params.advanced){
        params.printHelp();
        exit(0);
    }

    st2se::Ids in {};
    st2se::Ids out {};
    st2se::States states {};
    st2se::StraceParser o(in);

    // run grammar analysis
    if (params.analysis != 0) {

        std::cout << "Analyzing grammar ..." << std::endl;

        const std::size_t issues = o.AnalyzeGrammar();

        std::cout << "Found " << issues << " issues." << std::endl;

        return ret_val;
    }

    // parse files
    for (const auto &fn : params.file_names) {
        o.parse(fn, in, params, states);
    }

    // optimize IDS
    std::unique_ptr<st2se::Algorithm> algo;

    if (params.weak != 0) {
        algo = std::make_unique<st2se::Algo_weak>();
    }
    else if (params.strict != 0) {
        algo = std::make_unique<st2se::Algo_strict>();
    }
    else {
        algo = std::make_unique<st2se::Algo_advanced>();
    }

    st2se::Optimizer opti;

    opti.useAlgorithm(algo.get());

    try {
        opti.optimize(in, out);
    }
    catch (std::runtime_error &e) {
        std::cerr << e.what() << std::endl
            << "Exiting with error ..." << std::endl;
        ret_val = 1;
    }

    st2se::Generator gen;

    std::unique_ptr<st2se::Output> cpp = std::make_unique<st2se::outputCPP>();

    // initialize and configure generator
    gen.initialize(cpp.get());
    gen.configure(params);

    gen.generate(out);

    // remove and dealloc output generator
    gen.removeOutput();

    return ret_val;

}
