/**
 * @file algorithm_sttrict.hpp
 * @brief Algorithm_strict class is defined here. In this case none of the
 * algorithms is implemented.
 */

#ifndef SRC_ALGORITHM_STRICT_HPP
#define SRC_ALGORITHM_STRICT_HPP

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

    /**
     * Wrapper over strict algorithm implementation
     */
    class Algo_strict : public Algorithm {
    	/**
         * Optimization method
         * This member overrides the optimize memver in Algorithm class.
         * In this member is not located any algorithm. It simple copy the input
         * object to output object.
         * @param in an IDS used as input
         * @param out an IDS used as output
         * @return bool true on success false on error
         */
        bool optimize(Ids &in, Ids &out) override;
    };

} // namespace st2se

#endif