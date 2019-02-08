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
 * @file algorithm_advanced.hpp
 * @brief Algorithm_advanced class is defiend here. The class implement DBSCAN
 * algorithm to cluster values.
 */

#ifndef SRC_ALGORITHM_ADVANCED_HPP
#define SRC_ALGORITHM_ADVANCED_HPP

#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_set>

#if __cplusplus < 201703L
    #include <mpark/variant.hpp>
#else
    #include <variant>
#endif

#include <vector>

#include "algorithm.hpp"
#include "ids.hpp"

namespace st2se {

    using Bitfield = std::vector<std::string>;

    /**
     * DBSCAN algorithm implementation
     */
    class Algo_advanced : public Algorithm {
        /**
         * Process Syscall method
         * This member works only with one syscall
         * @param sc an Syscall used as input
         * @param out an IDS used as output
         * @return bool true on success false on error
         */
        void processSyscall(const Syscall &sc, Ids &out);
        /**
         * Create cluster
         * This member will process arguments from input into cluster on the output
         * @param in an argument vector used as input
         * @param out an argument vector used as cluster output
         * @return unsigned number of members in cluster
         */
        unsigned cluster(std::vector<Argument> &in, std::vector<Argument> &out);
        /**
         * Return pair of two arguments which are the closest together
         * Method return two arguments which has clossest distance to each other
         * @param in an argument vector used as input
         * @return pair of nearest arguments
         */
        std::pair<Argument, Argument> smallestDst(std::vector<Argument> &in);
        /**
         * Computes distance between two arguments
         * This member will compute the distance between two arguments
         * @param left an argument
         * @param right an argument
         * @return double distance between the two arguments
         */
        double distance(Argument &left, Argument &right);

        /**
         * deletes arguments from vector
         * This member will remove argument from vector
         * @param arg an argument which will be deleted
         * @param vec vector from which will be deleted
         * @return bool true on success false on error
         */
        bool removeItem(Argument &arg, std::vector<Argument> &vec);
        /**
         * returns closest items to argument with treshold
         * @param arg an argument
         * @param vec an vector of arguments
         * @param double eps between the two arguments
         * @return items in vector
         */
        std::vector<Argument> closestItemsTo(Argument &arg, std::vector<Argument> &vec, double eps);
        /**
         * move cluster from x to y
         * This member will move cluster
         * @param cluster an cluster
         * @param out an space
         * @return bool true on success false on error
         */
        bool moveCluster(std::vector<Argument> &cluster, std::vector<Argument> &out);
        /**
         * This member will move first argument from vec1 to vec2
         * @param to an vector
         * @param from an vector
         * @return bool true on success false on error
         */
        bool moveFirstItem(std::vector<Argument> &to, std::vector<Argument> &from);
        /**
         * Optimization method
         * This member overrides the optimize memver in Algorithm class.
         * In this member is located the core implementation of DBSCAN algorithm
         * @param in an IDS used as input
         * @param out an IDS used as output
         * @return bool true on success false on error
         */
        bool optimize(Ids &in, Ids &out) override;
    };

    /**
     * Computes bitfield distance
     * @param a an bitfiled
     * @param b an bitfiled
     * @return int distance
     */
    int bitfieldDistance(Bitfield &a, Bitfield &b);
    /**
     * Convert any argument to bitfield
     * @param a an argument
     * @return Bitfield bitfield
     */
    Bitfield convert2bitfield(const Argument &in);

} // namespace st2se

#endif