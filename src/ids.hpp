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
 * @file ids.hpp
 * @brief Intermediate Data Structure, here is located the whole IDS declaration.
 */
#ifndef _SRC_IDS_HPP
#define _SRC_IDS_HPP

#include <algorithm>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <type_traits>

#if __cplusplus < 201703L
    #include <mpark/variant.hpp>
    namespace variant_ns = mpark;
#else
    #include <variant>
    namespace variant_ns = std;
#endif


#include <vector>

/**
 * @def POSITION_MACRO
 * @brief Print colorized position in project (filename, loc)
 */
#define POSITION_MACRO "\x1B[4m\x1B[34m" << __FILE__ << "\x1B[0m"  \
    << ":" << "\x1B[1m\x1B[31m" << __func__ << "()\x1B[0m"         \
    << ":\x1B[32m" << __LINE__ << "\x1B[0m:"

namespace st2se {

    /**
     * value format enum
     */
    enum class ValueFormat {
        KEY_VALUE,          /**< value is format key and value*/
        VALUE,              /**< value is format value*/
        EMPTY               /**< value is empty*/
    };

    /**
     * value type enum
     */
    enum class ValueType {
        POINTER,            /**< value type is pointer*/
        INTEGER,            /**< value type is integer */
        STRING,             /**< value type is string*/
        CONSTANT,           /**< value type is constant*/
        ARRAY,              /**< value type is array*/
        STRUCTURE,          /**< value type is structure*/
        BITFIELD,           /**< value type is bitfield*/
        CLUSTERS,           /**< value type is cluster*/
        EMPTY               /**< value is empty */
    };

    enum class NumberValues {
        EMPTY,              /**< Argument does not operate with multiple values or value is empty*/
        VALUE,              /**< Argument contains only one value */
        RANGE,              /**< Argument contains values as range */
        VALUES,             /**< Argument contains discrete values in vector */
        VALUES_INTERVAL     /**< Argument contains range and discrete values */
    };

    /**
     * Argument structure
     * This structure holds information about argument
     */
    struct _Argument;
    struct _Argument {

        #if __cplusplus < 201703L
        using Value = mpark::variant<unsigned long, std::string>; /**< Alias for value type */
        #else
        using Value = std::variant<unsigned long, std::string>; /**< Alias for value type */
        #endif
        ValueFormat valueFormat {ValueFormat::EMPTY};           /**< value type */
        ValueType valueType {ValueType::EMPTY};                 /**< value format */
        NumberValues numbervalues {NumberValues::EMPTY};        /**< nubmer of values */
        std::string key {""};                                   /**< key before value, typically key=value */
        Value value {""};                                       /**< this variable stores value of argument. */
        Value value_b {""};                                     /**< this variable stores value of argument. This variable is used only after opitmization phase */
        std::vector<Value> discrete_values {};                  /**< Here are stored discrete values. This variable is used only after opitmization phase */
        std::vector<_Argument> next;                            /**< next arguments */

        /**
         * Constructor
         * default constructor
         */
        _Argument();
        /**
         * Constructor
         * explicit constructor
         * @param _fmt an value format
         * @param _type an value type
         * @param _vec arguments that are on next position after this argument
         */
        _Argument(ValueFormat _fmt, ValueType _type, std::vector<_Argument> _vec);
        /**
         * Constructor
         * explicit constructor
         * @param _fmt an value format
         * @param _type an value type
         * @param _key an key before value
         * @param _value an value of argument
         * @param _vec arguments that are on next position after this argument
         */
        _Argument(ValueFormat &_fmt, ValueType &_type, std::string &_key, variant_ns::variant<unsigned long, std::string> _value,
            std::vector<_Argument> _next);
        /**
         * Print class variables.
         * This member will print all inner variables of this argument and much more.
         */
        void print();
    };

    using Argument = struct _Argument;

    /**
     * Data structure that holds information about syscall
     */
    struct Syscall {
        std::string name {""}; /**< syscall name */
        int return_code {0}; /**< return code */
        std::string other {""}; /**< content parsed after return code */
        unsigned arg_num {0}; /**< number of arguments in the syscall*/
        std::vector<Argument> next {}; /**< first arguments */
        bool clustered = false; /**< points if the content is clustered or not*/

        /**
         * Print syscall.
         */
        void print();

        /**
         * Print syscall if it's clustered.
         * This method is called from print()
         */
        void printClustered();
    };

    /**
     * Object that implements whole IDS
     */
    class Ids {
        using Sc_map = std::map<std::string, Syscall>;
      public:
        Sc_map data {}; /***< here are located syscalls */
        /**
         * Syscall inserter into IDS
         * @param name syscall name
         * @param sc syscall content
         * @return true if initialized false otherwise
         */
        bool insert(const std::string &name, Syscall &sc);
        /**
         * Argument inserter into a container
         * @param arg an argument
         * @param container in which to insert argument
         * @return vector of arguments
         */
        std::vector<Argument> &insertArg(Argument &arg, std::vector<Argument> &container);

        /**
         * Print syscall
         */
        void printSyscall();
        /**
         * Print IDS.
         */
        void print();
    };

    /**
     * Convert argument to string
     * @param arg an argument
     * @return string value represented as string
     */
    std::string arg2str(const Argument &arg);
    /**
     * Operator overload
     * This operator implements comparison of two arguments
     */
    bool operator== (const st2se::Argument &lhs, const st2se::Argument &rhs);
    /**
     * Operator overload
     * This operator implements less operator for two arguments
     */
    bool operator< (const st2se::Argument &lhs, const st2se::Argument &rhs);
    /**
     * Operator overload
     * This operator implements printing of IDS to output stream
     */
    std::ostream &operator<< (std::ostream &os, const st2se::Ids &a);
    /**
     * Operator overload
     * This operator implements printing of value type enumeration to output stream
     */
    std::ostream &operator<< (std::ostream &os, const st2se::ValueType &a);
    /**
     * Operator overload
     * This operator implements printing of value format enumeration to output stream
     */
    std::ostream &operator<< (std::ostream &os, const st2se::ValueFormat &a);

} // namespace st2se

#endif
