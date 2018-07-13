/**
 * @file algorithm.hpp
 * @brief Algorithm class definition is located here. Algorithm class is used for interface definition
 */

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
/**
 * @def DEBUGprintArgumentSet(__set_variable)
 * @brief Macro for printing arguments from container.
 */
#define DEBUGprintArgumentSet(__set_variable) do {   \
        std::cout << "\t\x1B[33m";                   \
        for (auto item : (__set_variable)) {         \
            std::cout << "  " << arg2str(item);      \
        }                                            \
        std::cout << "\x1B[0m" << std::endl;         \
    } while(0)

/**
 * @def DEBUGprint(__string_variable)
 * @brief Macro for printing object and on which line it is located.
 */
#define DEBUGprint(__string_variable) do {                    \
        std::cout << POSITION_MACRO << (__string_variable) ;  \
    } while(0)
#else

#define DEBUGprintArgumentSet(__set_variable)
#define DEBUGprint(__string_variable)

#endif

namespace st2se {

    /**
     * Virtual class used only for interface definition
     */
    class Algorithm {

        /**
         * Constructor
         * Default constructor
         */
        Algorithm() = default;

        friend class Algo_weak;
        friend class Algo_strict;
        friend class Algo_advanced;

      public:
        /**
         * Destructor
         * Default destructor
         */
        virtual ~Algorithm() = default;

        /**
         * Optimization method
         * This method is pure virtual. It is only for specifying a interface.
         * @param in an IDS used as input
         * @param out an IDS used as output
         * @return bool true on success false on error
         */
        virtual bool optimize(Ids &in, Ids &out) = 0;
        /**
         * getDepth method
         * getDepth member will return number of structure levels
         * @param arg an argument
         * @return number of structure levels
         */
        unsigned getDepth(const argument_t &arg);

        /**
         * method will obtain arguments from \f$n\f$-th position
         * @param args arguments
         * @param lvl depth
         * @return vector of arguments
         */
        std::vector<argument_t> getArguemntsFromPos(const std::vector<argument_t> &args, unsigned lvl);
    };

} // namespace st2se

#endif
