#ifndef SRC_ALGORITHM_STRICT_HPP
#define SRC_ALGORITHM_STRICT_HPP

#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_set>
#include <utility>
#include <variant>
#include <vector>

#include "ids.hpp"
#include "algorithm.hpp"

namespace st2se {

    class Algo_strict : public Algorithm {
        bool optimize(Ids &in, Ids &out) override;
    };

} // namespace st2se

#endif