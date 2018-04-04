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

#ifndef NDEBUG
#define DEBUGprintArgumentSet(__set_variable) do {                      \
        std::cout << "\t\x1B[33m";                                      \
        for (auto item : __set_variable) {                              \
            std::cout << "  " << arg2str(item);                         \
        }                                                               \
        std::cout << "\x1B[0m" << std::endl;                            \
    } while(0)

#define DEBUGprint(__string_variable) do {                              \
        std::cout << POSITION_MACRO << __string_variable ;              \
    } while(0)
#else

    #define DEBUGprintArgumentSet(__set_variable)
    #define DEBUGprint(__string_variable)

#endif

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

        bool removeItem(argument_t &arg, std::vector<argument_t> &vec);
        std::vector<argument_t> closestItemsTo(argument_t &arg, std::vector<argument_t> &vec, double eps);
        bool moveCluster(std::vector<argument_t> &cluster, std::vector<argument_t> &out);
        bool moveFirstItem(std::vector<argument_t> &to, std::vector<argument_t> &from);


    };

    int bitfieldDistance(bitfield_t &a, bitfield_t &b);
    bitfield_t convert2bitfield(const argument_t &in);

} // namespace st2se

#endif
