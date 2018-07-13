
/*! \mainpage strace2seccomp tool
 *
 * \section intro_sec Introduction
 *
 * This bachelor thesis is focused on an automatic generation of seccomp rules
 * from strace logs. The output is generated in C/C++ syntax. Input can be
 * optimized with three optimization algorithms. One is called strict, and it
 * will produce 1:1 output compared to input. Another one is called minimax or
 * weak. This algorithm will provide on the output only extremes as border
 * values for allowance interval. The last one is called advanced which
 * implements DBSCAN algorithm for clustering.
 *
 * Closer info is located here: https://github.com/tammar96/IBP
 */

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
