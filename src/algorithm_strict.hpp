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