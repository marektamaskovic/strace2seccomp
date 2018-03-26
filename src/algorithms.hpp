#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_set>
#include <utility>
#include <variant>
#include <vector>

#include "ids.hpp"

namespace st2se {

    using bitfield_t = std::vector<std::string>;

    class Algorithm {
        Algorithm() = default;

        friend class Algo_weak;
        friend class Algo_strict;
        friend class Algo_advanced;

      public:
        virtual bool optimize(Ids &in, Ids &out) = 0;
        unsigned getDepth(const argument_t &arg);
        std::vector<argument_t> getArguemntsFromPos(const std::vector<argument_t> &args, unsigned lvl);
    };

    class Algo_weak : public Algorithm {
        bool optimize(Ids &in, Ids &out) override;
        void processSyscall(const Syscall_t &sc, Ids &out);
        void findMinMax(Syscall_t &sc, Ids &out);


    };

    class Algo_strict : public Algorithm {
        bool optimize(Ids &in, Ids &out) override;
    };

    class Algo_advanced : public Algorithm {
        bool optimize(Ids &in, Ids &out) override;
        void processSyscall(const Syscall_t &sc, Ids &out);
        unsigned cluster(std::vector<argument_t> &in, std::vector<argument_t> &out);
        std::pair<argument_t, argument_t> smallestDst(std::vector<argument_t> &in);
        double distance(const argument_t &left, const argument_t &right);

        bool removeItem(argument_t &arg, std::vector<argument_t> &vec);
        std::vector<argument_t> closestItemsTo(const argument_t &arg, std::vector<argument_t> &vec);
        bool moveCluster(std::vector<argument_t> &cluster, std::vector<argument_t> &out);

    };

    int bitfieldDistance(bitfield_t &a, bitfield_t &b);
    bitfield_t convert2bitfield(const argument_t &in);

} // namespace st2se

#endif
