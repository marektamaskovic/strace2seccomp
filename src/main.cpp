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

    auto *params = new Params(argc, argv);

    // std::cout << *params << std::endl;

    st2se::Ids in {};
    st2se::Ids out {};
    st2se::StraceParser o(in);
    st2se::States states {};

    // run grammar analysis
    if (params->analysis != 0) {

        std::cout << "Analyzing grammar ..." << std::endl;

        const std::size_t issues = o.AnalyzeGrammar();

        std::cout << "Found " << issues << " issues." << std::endl;

        return 0;
    }

    // parse files
    for (const auto &fn : params->file_names) {
        // std::cout << fn << std::endl;
        o.parse(fn, in, *params, states);
    }

    // print IDS
    in.print();

    // optimize IDS
    st2se::Algorithm *algo {nullptr};

    // choose algorithm
    // TODO try to hide this to ctor of optimizer
    if (params->weak != 0) {
        algo = new st2se::Algo_weak();
    }
    else if (params->strict != 0) {
        algo = new st2se::Algo_strict();
    }
    else {
        algo = new st2se::Algo_advanced();
    }

    // TODO
    // make constructor which takes algorithm as a param
    st2se::Optimizer opti;

    opti.useAlgorithm(algo);

    try {
        opti.optimize(in, out);
    }
    catch (std::runtime_error &e) {
        std::cerr << e.what() << std::endl
            << "Exiting with error ..." << std::endl;
        ret_val = 1;
    }

    out.print();

    std::cout << "Generating output ..." << std::endl;

    // Generating source template
    st2se::Generator gen;
    st2se::outputCPP *cpp = new st2se::outputCPP();
    gen.initialize(cpp);
    gen.generate(out);



    // Exitint procedures
    std::cout << "Exiting ..." << std::endl;

    // remove and dealloc algorithm
    opti.useAlgorithm(nullptr);
    delete algo;

    // remove and dealloc output generator 
    gen.removeOutput();
    delete cpp;

    // delete params object
    delete params;

    return ret_val;

}
