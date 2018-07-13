#ifndef SRC_ALGORITHM_WEAK_HPP
#define SRC_ALGORITHM_WEAK_HPP

#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_set>
#include <utility>
#include <variant>
#include <vector>

#include <boost/algorithm/string.hpp>

#include "algorithm.hpp"
#include "ids.hpp"

namespace st2se {

    class Algo_weak : public Algorithm {
        bool optimize(Ids &in, Ids &out) override;
        void processSyscall(const Syscall_t &sc, Ids &out);
        void findMinMax(Syscall_t &sc, Ids &out);
    	argument_t mergeConstants(std::vector<argument_t> vec);

    };

} // namespace st2se

#endif