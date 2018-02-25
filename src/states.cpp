#include "states.hpp"

template<class T> struct always_false : std::false_type {};

std::ostream &operator<< (std::ostream &os, const st2se::val_type_t &a) {
    if (a == st2se::val_type_t::INTEGER) {
        return os << "INTEGER";
    }
    else if (a == st2se::val_type_t::STRING) {
        return os << "STRING";
    }
    else if (a == st2se::val_type_t::CONSTANT) {
        return os << "CONSTANT";
    }
    else if (a == st2se::val_type_t::POINTER) {
        return os << "POINTER";
    }
    else if (a == st2se::val_type_t::ARRAY) {
        return os << "ARRAY";
    }
    else if (a == st2se::val_type_t::STRUCTURE) {
        return os << "STRUCTURE";
    }
    else {
        return os << "UNDEF";
    }
}

namespace st2se {
    void States::push_parsed_val(argument_t &arg) {
        this->parsed_val.push_back(arg);
    }

    void States::pop_parsed_val() {
        this->parsed_val.pop_back();
    }

    bool States::process_val(Ids &ids) {
        std::cerr << "FIXME: " << __func__ << " !" << std::endl;

        Syscall_t s = this->getSyscall();

        ids.insert(this->get_name(), s);

        s.print();

        return true;
    }

    void States::set_val_format(const val_format_t &fmt) {
        this->arg_format = fmt;
    }

    void States::set_val_type(const val_type_t &fmt) {
        this->last_arg_type = fmt;
    }

    void States::set_ret_val(const std::string &str) {
        std::stringstream buf(str);
        buf >> this->return_val;
    }

    void States::set_name(const std::string &str) {
        this->name = str;
    }

    const std::string &States::get_name() {
        return this->name;
    }

    const val_format_t &States::get_val_format() {
        return this->arg_format;
    }

    const val_type_t &States::get_val_type() {
        return this->last_arg_type;
    }

    void States::clear() {
        parsed_val.clear();
        arg_num = 0;
    }

    std::string States::argsStr() {
        std::string str {" "};

        for (auto &w : this->parsed_val) {
            std::string tmp = std::visit([](auto &&arg) -> std::string {
                using T = std::decay_t<decltype(arg)>;

                if constexpr(std::is_same_v<T, int>)
                    return std::to_string(arg);
                else if constexpr(std::is_same_v<T, std::string>)
                    return arg;
                else {
                    static_assert(always_false<T>::value, "non-exhaustive visitor!");
                    return "Error: Variant is empty";
                }
            }, w.value);
            str.append(tmp + ",\n ");
        }

        return str;
    }

    Syscall_t States::getSyscall() {
        Syscall_t s;

        if (parsed_val.size() == 0) {
            std::cerr << "Error: Parsed val is empty." << std::endl;

            argument_t a {
                val_format_t::EMPTY,
                val_type_t::EMPTY,
                "",
                "",
                {}
            };

            s.next.emplace_back(a);
            s.arg_num = 0;
            s.return_code = this->return_val;
            s.name = this->get_name();

            return s;
        }

        argument_t a, b;

        a = parsed_val.back();
        parsed_val.pop_back();

        while (!parsed_val.empty()) {
            //check if empty
            b = parsed_val.back();
            b.next.push_back(a);
            a = b;
            parsed_val.pop_back();
        }

        s.next.emplace_back(a);

        s.arg_num = this->arg_num;
        s.return_code = this->return_val;
        s.name = this->get_name();

        return s;

    }

} // end of namespace
