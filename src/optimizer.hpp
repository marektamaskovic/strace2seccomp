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
 * @file optimizer.hpp
 * @brief Optimizer wrapper around algoritms implementation
 */
#ifndef OPTIMIZER_HPP
#define OPTIMIZER_HPP

#include <iostream>

#include "algorithm.hpp"
#include "ids.hpp"

namespace st2se {

    /**
     * Optimalizator
     * Uses d-pointer design pattern to hide implementation
     */
    class Optimizer {
        // TODO uniq pointer
        Algorithm *opt_adapter {nullptr}; /**< Pointer to optimization algorithm */
      public:
        /**
         * Constructor
         * explicit constructor
         * @param _opt_adapter an optimization algorithm
         */
        explicit Optimizer(Algorithm *_opt_adapter);
        /**
         * Constructor
         * defualt constructor
         */
        Optimizer();
        /**
         * set opt_adapter pointer to point on optimization algorithm
         * @param _opt_adapter an optimization algorithm
         */
        void useAlgorithm(Algorithm *_opt_adapter);
        /**
         * Initialization checker
         * Will check if the implementation of output generator is set up
         * @return true if initialized false otherwise
         */
        bool isInitialized();
        /**
         * Optimization method
         * This member overrides the optimize memver in Algorithm class.
         * In this member is located the core implementation of DBSCAN algorithm
         * @param in an IDS used as input
         * @param out an IDS used as output
         * @return bool true on success false on error
         */
        bool optimize(Ids &in, Ids &out);
    };

} // namespace st2se

#endif