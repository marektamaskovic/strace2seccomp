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
#include <variant>
#include <vector>

#include "ids.hpp"


namespace st2se {
    class States {
        // TODO
        // - define a copy constructor
        // - copy assignment operator
        // - move constructor
        // - move assignment operator

        std::vector<st2se::argument_t> parsed_val {}; /**< all parsed values */

        val_format_t arg_format {val_format_t::EMPTY}; /**< value format*/
        val_type_t last_arg_type {val_type_t::EMPTY}; /**< value type*/
        long long return_val {0}; /**< return value */
        std::string name {}; /**< name of syscall */
        bool bitfields {false}; /**< bool that indicates if was bitfields recognized */

      public:
        unsigned arg_num {0}; /**< number of parsed arguments */
        std::variant<unsigned long, std::string> value; /**< value */

        void push_parsed_val(argument_t &arg);
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
        void set_val_format(const val_format_t &fmt);
        /**
         * Setter
         * set value type
         * @param fmt value type
         */
        void set_val_type(const val_type_t &fmt);
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
        val_format_t &get_val_format();
        /**
         * Getter
         * get value type
         * @return value type
         */
        val_type_t &get_val_type();

        /**
         * Converts arguemnts to string
         * @return argument in string
         */
        std::string argsStr();
        /**
         * Get syscall
         * @return syscall
         */
        Syscall_t getSyscall();
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
