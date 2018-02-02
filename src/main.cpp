#include <iostream>

#include "tao/pegtl.hpp"
// #include "tao/pegtl/contrib/json.hpp"

#include "argparse.hpp"
#include "straceparser.hpp"

int main(int argc, char* argv[]) {
    Params* params = new Params(argc, argv);

    // s2s::config_t config = parseArguments(argc, argv);

    std::cout << *params << std::endl;

    st2se::Ids a;
    // s2s::straceParser o("strace.out", a);


    for (const auto& fn : params->file_names) {
        // std::cout << fn << std::endl;
        st2se::StraceParser::parse(fn, a);

    }

    // std::cout << o.getFilename() << std::endl;

    delete params;

    return 0;

}
