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

        std::vector<st2se::argument_t> parsed_val {};

        val_format_t arg_format {val_format_t::EMPTY};
        val_type_t last_arg_type {val_type_t::EMPTY};
        long long return_val {0};
        std::string name {};
        bool bitfields {false};

      public:
        unsigned arg_num;
        std::variant<unsigned long, std::string> value;

        void push_parsed_val(argument_t &arg);
        void pop_parsed_val();
        bool process_val(Ids &ids);

        void set_val_format(const val_format_t &fmt);
        void set_val_type(const val_type_t &fmt);
        void set_ret_val(const std::string &str);
        void set_name(const std::string &str);
        void set_bitfields(const bool &b);

        const bool &get_bitfields();
        const std::string &get_name();
        const val_format_t &get_val_format();
        const val_type_t &get_val_type();

        std::string argsStr();
        Syscall_t getSyscall();
        void clear();

        States() = default;
        ~States() = default;

    };
} // namespace st2se

#endif
