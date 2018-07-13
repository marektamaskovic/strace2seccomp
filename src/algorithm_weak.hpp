/**
 * @file algorithm_weak.hpp
 * @brief This algorithm contains implementation of minimax, i.e, weak
 */
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

	/**
	 * Wrapper over weak algorithm implementation
	 */
    class Algo_weak : public Algorithm {
    	/**
         * Optimization method
         * This member overrides the optimize memver in Algorithm class.
         * In this member is located the core implementation of DBSCAN algorithm
         * @param in an IDS used as input
         * @param out an IDS used as output
         * @return bool true on success false on error
         */
        bool optimize(Ids &in, Ids &out) override;
        /**
         * Process Syscall method
         * This member works only with one syscall
         * @param sc an Syscall used as input
         * @param out an IDS used as output
         * @return bool true on success false on error
         */
        void processSyscall(const Syscall_t &sc, Ids &out);
        /**
         * Deprecated
         */
        void findMinMax(Syscall_t &sc, Ids &out);
        /**
         * Member will merge constants into a bitfield
         * @param vec vector of constants
         */
    	argument_t mergeConstants(std::vector<argument_t> vec);
    };

} // namespace st2se

#endif