#include "algorithm_strict.hpp"

namespace st2se {

    bool Algo_strict::optimize(Ids &in, Ids &out) {
        std::cout << "Algo_strict optimize emitted." << std::endl;

        out = in;

        return true;
    }

} // namespace st2se