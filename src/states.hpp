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
 * @file states.hpp
 * @brief Inner states for parser
 */
#ifndef _SRC_STATES_HPP
#define _SRC_STATES_HPP

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <type_traits>

#if __cplusplus < 201703L
    #include "Mpark.Variant/variant.hpp"
#else
    #include <variant>
#endif

#include <vector>

#include "ids.hpp"


namespace st2se {
    class States {
        // TODO
        // - define a copy constructor
        // - copy assignment operator
        // - move constructor
        // - move assignment operator

        std::vector<st2se::Argument> parsed_val {}; /**< all parsed values */

        ValueFormat arg_format {ValueFormat::EMPTY}; /**< value format*/
        ValueType last_arg_type {ValueType::EMPTY}; /**< value type*/
        long long return_val {0}; /**< return value */
        std::string name {}; /**< name of syscall */
        bool bitfields {false}; /**< bool that indicates if was bitfields recognized */

      public:
        unsigned arg_num {0}; /**< number of parsed arguments */
        
        #if __cplusplus < 201703L
        mpark::variant<unsigned long, std::string> value; /**< value */
        #else
        std::variant<unsigned long, std::string> value; /**< value */
        #endif

        void push_parsed_val(Argument &arg);
        void pop_parsed_val();
        /**
         * Move parsed syscall to ids
         * @param [out] ids IDS
         * @return bool true on success, false otherwise
         */
        bool process_val(Ids &ids);

        /**
         * Setter
         * set value format
         * @param fmt value format
         */
        void set_val_format(const ValueFormat &fmt);
        /**
         * Setter
         * set value type
         * @param fmt value type
         */
        void set_val_type(const ValueType &fmt);
        /**
         * Setter
         * set return value
         * @param str set return value
         */
        void set_ret_val(const std::string &str);
        /**
         * Setter
         * set syscall name
         * @param str syscall name
         */
        void set_name(const std::string &str);
        /**
         * Setter
         * set bitfield switch
         * @param b bitfield recognized
         */
        void set_bitfields(const bool &b);

        /**
         * Getter
         * get bitfields
         * @return bool if bitfield was recognized
         */
        bool &get_bitfields();
        /**
         * Getter
         * get return value
         * @return return value
         */
        int get_ret_val();
        /**
         * Getter
         * get syscall name
         * @return string name
         */
        std::string &get_name();
        /**
         * Getter
         * get value format
         * @return value format
         */
        ValueFormat &get_val_format();
        /**
         * Getter
         * get value type
         * @return value type
         */
        ValueType &get_val_type();

        /**
         * Converts arguemnts to string
         * @return argument in string
         */
        std::string argsStr();
        /**
         * Get syscall
         * @return syscall
         */
        Syscall getSyscall();
        /**
         * Clear states
         */
        void clear();

        /**
         * Constructor
         * default constructor
         */
        States() = default;
        /**
         * destructor
         * default destructor
         */
        ~States() = default;

    };
} // namespace st2se

#endif
