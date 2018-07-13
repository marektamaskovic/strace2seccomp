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
#include <variant>
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
    enum class val_format_t {
        KEY_VALUE, /**< value is format key and value*/
        VALUE,     /**< value is format value*/
        EMPTY      /**< value is empty*/
    };

    /**
     * value type enum
     */
    enum class val_type_t {
        POINTER,     /**< value type is pointer*/
        INTEGER,     /**< value type is integer */
        STRING,      /**< value type is string*/
        CONSTANT,    /**< value type is constant*/
        ARRAY,       /**< value type is array*/
        STRUCTURE,   /**< value type is structure*/
        BITFIELD,    /**< value type is bitfield*/
        CLUSTERS,    /**< value type is cluster*/
        EMPTY        /**< value is empty */
    };

    /**
     * argument_t structure
     * This structure holds information about argument
     */
    struct _argument_t;
    struct _argument_t {
        val_format_t value_format {val_format_t::EMPTY};      /**< value type*/
        val_type_t value_type {val_type_t::EMPTY};            /**< value format*/
        std::string key {""};                                 /**< key before value, typically key=value*/
        std::variant<unsigned long, std::string> value {""};  /**< this variable stores value of argument. it is a unsigned number or string*/
        std::vector<_argument_t> next;                        /**< next arguments */
        /**
         * Constructor
         * default constructor
         */
        _argument_t();
        /**
         * Constructor
         * explicit constructor
         * @param _fmt an value format
         * @param _type an value type
         * @param _vec arguments that are on next position after this argument
         */
        _argument_t(val_format_t _fmt, val_type_t _type, std::vector<_argument_t> _vec);
        /**
         * Constructor
         * explicit constructor
         * @param _fmt an value format
         * @param _type an value type
         * @param _key an key before value
         * @param _value an value of argument
         * @param _vec arguments that are on next position after this argument
         */
        _argument_t(val_format_t &_fmt, val_type_t &_type, std::string &_key, std::variant<unsigned long, std::string> _value,
            std::vector<_argument_t> _next);
        /**
         * Print class variables.
         * This member will print all inner variables of this argument and much more.
         */
        void print();
    };

    using argument_t = struct _argument_t;

    /**
     * Data structure that holds information about syscall
     */
    struct Syscall_t {
        std::string name {""}; /**< syscall name */
        int return_code {0}; /**< return code */
        std::string other {""}; /**< content parsed after return code */
        unsigned arg_num {0}; /**< number of arguments in the syscall*/
        std::vector<argument_t> next {}; /**< first arguments */
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
        using Sc_map = std::map<std::string, Syscall_t>;
      public:
        Sc_map data {}; /***< here are located syscalls */
        /**
         * Syscall inserter into IDS
         * @param name syscall name
         * @param sc syscall content
         * @return true if initialized false otherwise
         */
        bool insert(const std::string &name, Syscall_t &sc);
        /**
         * Argument inserter into a container
         * @param arg an argument
         * @param container in which to insert argument
         * @return vector of arguments
         */
        std::vector<argument_t> &insertArg(argument_t &arg, std::vector<argument_t> &container);

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
    std::string arg2str(const argument_t &arg);
    /**
     * Operator overload
     * This operator implements comparison of two arguments
     */
    bool operator== (const st2se::argument_t &lhs, const st2se::argument_t &rhs);
    /**
     * Operator overload
     * This operator implements less operator for two arguments
     */
    bool operator< (const st2se::argument_t &lhs, const st2se::argument_t &rhs);
    /**
     * Operator overload
     * This operator implements printing of IDS to output stream
     */
    std::ostream &operator<< (std::ostream &os, const st2se::Ids &a);
    /**
     * Operator overload
     * This operator implements printing of value type enumeration to output stream
     */
    std::ostream &operator<< (std::ostream &os, const st2se::val_type_t &a);
    /**
     * Operator overload
     * This operator implements printing of value format enumeration to output stream
     */
    std::ostream &operator<< (std::ostream &os, const st2se::val_format_t &a);

} // namespace st2se

#endif
