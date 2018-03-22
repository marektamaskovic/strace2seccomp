#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <variant>
#include <unordered_set>
#include <string>

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
        double distance(argument_t &left, argument_t &right);

    };

    int LevenshteinDistance(const std::string &s, int len_s, const std::string &t, int len_t);
    template<typename T>
    T minimum(T a, T b, T c);
    int bitfieldDistance(bitfield_t &a, bitfield_t &b);
    bitfield_t convert2bitfield(argument_t &in);

} // namespace st2se

#endif
