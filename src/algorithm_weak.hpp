// Copyright (c) 2018 Red Hat <mtamasko@redhat.com>
// Author: Marek Tamaskovic <tamaskovic.marek@gmail.com>
//
// This file is part of strace2seccomp tool.
//
// strace2seccomp tool is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// strace2seccomp tool is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with strace2seccomp tool.  If not, see <https://www.gnu.org/licenses/>.

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

#if __cplusplus < 201703L
    #include <mpark/variant.hpp>
#else
    #include <variant>
#endif

#include <vector>

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
        void processSyscall(Syscall &sc, Ids &out);
        /**
         * Deprecated
         */
        void findMinMax(Syscall &sc, Ids &out);
        /**
         * Member will merge constants into a bitfield
         * @param vec vector of constants
         */
        Argument mergeConstants(std::vector<Argument> vec);

        std::pair<Argument, Argument> getMinMax(std::vector<Argument> vec);
        std::vector<Argument> bar(std::vector<Argument> &vec);
    };



} // namespace st2se

#endif