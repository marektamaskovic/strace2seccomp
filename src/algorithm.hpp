#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP

#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_set>
#include <utility>
#include <variant>
#include <vector>

#include "ids.hpp"

#ifndef NDEBUG
#define DEBUGprintArgumentSet(__set_variable) do {   \
        std::cout << "\t\x1B[33m";                   \
        for (auto item : (__set_variable)) {         \
            std::cout << "  " << arg2str(item);      \
        }                                            \
        std::cout << "\x1B[0m" << std::endl;         \
    } while(0)

#define DEBUGprint(__string_variable) do {                    \
        std::cout << POSITION_MACRO << (__string_variable) ;  \
    } while(0)
#else

#define DEBUGprintArgumentSet(__set_variable)
#define DEBUGprint(__string_variable)

#endif

namespace st2se {

    class Algorithm {

        Algorithm() = default;

        friend class Algo_weak;
        friend class Algo_strict;
        friend class Algo_advanced;

      public:
        virtual ~Algorithm() = default;
        virtual bool optimize(Ids &in, Ids &out) = 0;
        unsigned getDepth(const argument_t &arg);

        std::vector<argument_t> getArguemntsFromPos(const std::vector<argument_t> &args, unsigned lvl);
    };

} // namespace st2se

#endif
