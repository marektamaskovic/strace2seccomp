#include "states.hpp"

template<class T> struct always_false : std::false_type {};

std::ostream& operator<< (std::ostream& os, const st2se::val_type_t& a)
{
    if(a == st2se::val_type_t::INTEGER)
        return os << "INTEGER";
    else if(a == st2se::val_type_t::STRING)
        return os << "STRING";
    else if(a == st2se::val_type_t::CONSTANT)
        return os << "CONSTANT";
    else if(a == st2se::val_type_t::POINTER)
        return os << "POINTER";
    else if(a == st2se::val_type_t::ARRAY)
        return os << "ARRAY";
    else if(a == st2se::val_type_t::STRUCTURE)
        return os << "STRUCTURE";
    else
        return os << "UNDEF";
}

namespace st2se {
    void States::push_parsed_val(argument_body_t &arg) {
        this->parsed_val.push_back(arg);
    }

    void States::pop_parsed_val() {
        this->parsed_val.pop_back();
    }

    bool States::process_val() {
        std::cerr << "IMPLEMENT " << __func__ << " !" << std::endl;
        return true;
    }

    void States::set_val_format(const val_format_t &fmt) {
        this->arg_format = fmt;
    }

    void States::set_val_type(const val_type_t &fmt) {
        this->last_arg_type = fmt;
    }

    const val_format_t &States::get_val_format() {
        return this->arg_format;
    }

    const val_type_t &States::get_val_type() {
        return this->last_arg_type;
    }

    void States::clear() {
        parsed_val.clear();
        processed_val.clear();
    }

    std::string States::argsStr() {
        std::string str {""};

        for(auto &w : this->parsed_val){
            std::string tmp = std::visit([](auto &&arg) -> std::string {
                    using T = std::decay_t<decltype(arg)>;
                    if constexpr (std::is_same_v<T, int>)
                        return std::to_string(arg);
                    else if constexpr (std::is_same_v<T, std::string>)
                        return arg;
                    else{
                        static_assert(always_false<T>::value, "non-exhaustive visitor!");
                        return "Err: Variant is empty";
                    }
                }, w.value);
            str.append(tmp + ", ");
        }

        return str;
    }

} // end of namespace
