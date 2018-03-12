#ifndef STATES_HPP
#define STATES_HPP

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <variant>
#include <type_traits>
#include <iomanip>

#include "ids.hpp"


namespace st2se {
    class States {
        std::vector<st2se::argument_t> parsed_val;

        val_format_t arg_format;
        val_type_t last_arg_type;
        long long return_val;
        std::string name;
        bool bitfields;

      public:
        unsigned arg_num;
        std::variant<long, std::string> value;

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
}

std::ostream &operator<< (std::ostream &os, const st2se::val_type_t &a);

#endif
