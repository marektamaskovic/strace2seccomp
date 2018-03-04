#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include <iostream>
#include <vector>
#include <algorithm>

#include "ids.hpp"

namespace st2se {

    class Algorithm {
        Algorithm() = default;

        friend class Algo_weak;
        friend class Algo_strict;
        friend class Algo_advanced;

      public:
        virtual bool optimize(Ids &in, Ids &out) = 0;
    };

    class Algo_weak : public Algorithm {
        bool optimize(Ids &in, Ids &out) override;
        void processSyscall(const Syscall_t &sc, Ids &out);
        unsigned getDepth(const argument_t &arg);
        void findMinMax(Syscall_t &sc, Ids &out);
        std::vector<argument_t> getArguemntsFromPos(const std::vector<argument_t> &args, unsigned lvl);


    };

    class Algo_strict : public Algorithm {
        bool optimize(Ids &in, Ids &out) override;
    };

    class Algo_advanced : public Algorithm {
        bool optimize(Ids &in, Ids &out) override;
    };

} // end of namespace

#endif
