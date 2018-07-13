#ifndef SRC_ALGORITHM_ADVANCED_HPP
#define SRC_ALGORITHM_ADVANCED_HPP

#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_set>
#include <utility>
#include <variant>
#include <vector>

#include "algorithm.hpp"
#include "ids.hpp"

namespace st2se {

    using bitfield_t = std::vector<std::string>;

    class Algo_advanced : public Algorithm {
        bool optimize(Ids &in, Ids &out) override;
        void processSyscall(const Syscall_t &sc, Ids &out);
        unsigned cluster(std::vector<argument_t> &in, std::vector<argument_t> &out);
        std::pair<argument_t, argument_t> smallestDst(std::vector<argument_t> &in);
        double distance(argument_t &left, argument_t &right);

        bool removeItem(argument_t &arg, std::vector<argument_t> &vec);
        std::vector<argument_t> closestItemsTo(argument_t &arg, std::vector<argument_t> &vec, double eps);
        bool moveCluster(std::vector<argument_t> &cluster, std::vector<argument_t> &out);
        bool moveFirstItem(std::vector<argument_t> &to, std::vector<argument_t> &from);
    };

    int bitfieldDistance(bitfield_t &a, bitfield_t &b);
    bitfield_t convert2bitfield(const argument_t &in);

} // namespace st2se

#endif