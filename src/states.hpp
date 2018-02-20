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
        std::vector<st2se::argument_body_t> parsed_val;
        std::vector<st2se::argument_body_t> processed_val;

        val_format_t arg_format;
        val_type_t last_arg_type;

      public:
        void push_parsed_val(argument_body_t &arg);
        void pop_parsed_val();
        bool process_val();
        void set_val_format(const val_format_t &fmt);
        void set_val_type(const val_type_t &fmt);
        const val_format_t &get_val_format();
        const val_type_t &get_val_type();
        std::string argsStr();
        void clear();

        States() = default;
        ~States() = default;

    };
}

#endif
