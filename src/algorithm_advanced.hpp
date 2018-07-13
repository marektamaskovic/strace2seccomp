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
#include <utility>
#include <variant>
#include <vector>

#include "algorithm.hpp"
#include "ids.hpp"

namespace st2se {

    using bitfield_t = std::vector<std::string>;

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
        void processSyscall(const Syscall_t &sc, Ids &out);
        /**
         * Create cluster
         * This member will process arguments from input into cluster on the output
         * @param in an argument vector used as input
         * @param out an argument vector used as cluster output
         * @return unsigned number of members in cluster
         */
        unsigned cluster(std::vector<argument_t> &in, std::vector<argument_t> &out);
        /**
         * Return pair of two arguments which are the closest together
         * Method return two arguments which has clossest distance to each other
         * @param in an argument vector used as input
         * @return pair of nearest arguments
         */
        std::pair<argument_t, argument_t> smallestDst(std::vector<argument_t> &in);
        /**
         * Computes distance between two arguments
         * This member will compute the distance between two arguments
         * @param left an argument
         * @param right an argument
         * @return double distance between the two arguments
         */
        double distance(argument_t &left, argument_t &right);

        /**
         * deletes arguments from vector
         * This member will remove argument from vector
         * @param arg an argument which will be deleted
         * @param vec vector from which will be deleted
         * @return bool true on success false on error
         */
        bool removeItem(argument_t &arg, std::vector<argument_t> &vec);
        /**
         * returns closest items to argument with treshold
         * @param arg an argument
         * @param vec an vector of arguments
         * @param double eps between the two arguments
         * @return items in vector
         */
        std::vector<argument_t> closestItemsTo(argument_t &arg, std::vector<argument_t> &vec, double eps);
        /**
         * move cluster from x to y
         * This member will move cluster
         * @param cluster an cluster
         * @param out an space
         * @return bool true on success false on error
         */
        bool moveCluster(std::vector<argument_t> &cluster, std::vector<argument_t> &out);
        /**
         * This member will move first argument from vec1 to vec2
         * @param to an vector
         * @param from an vector
         * @return bool true on success false on error
         */
        bool moveFirstItem(std::vector<argument_t> &to, std::vector<argument_t> &from);
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
    int bitfieldDistance(bitfield_t &a, bitfield_t &b);
    /**
     * Convert any argument to bitfield
     * @param a an argument
     * @return bitfield_t bitfield
     */
    bitfield_t convert2bitfield(const argument_t &in);

} // namespace st2se

#endif