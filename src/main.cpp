#include <iostream>

#include "tao/pegtl.hpp"

#include "argparse.hpp"
#include "straceparser.hpp"
#include "states.hpp"
#include "ids.hpp"

int main(int argc, char *argv[]) {
    Params *params = new Params(argc, argv);

    // std::cout << *params << std::endl;

    st2se::Ids a {};
    st2se::StraceParser o(a);
    st2se::States states {};

    for (const auto &fn : params->file_names) {
        // std::cout << fn << std::endl;
        o.parse(fn, a, *params, states);
    }

    a.print();
    a.printSyscall();

    delete params;

    return 0;

}
