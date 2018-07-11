#include "states.hpp"

template<class T> struct always_false : std::false_type {};

namespace st2se {
    void States::push_parsed_val(argument_t &arg) {
        parsed_val.push_back(arg);
    }

    void States::pop_parsed_val() {
        parsed_val.pop_back();
    }

    bool States::process_val(Ids &ids) {

        Syscall_t s = getSyscall();

        ids.insert(get_name(), s);

        // s.print();

        return true;
    }

    void States::set_val_format(const val_format_t &fmt) {
        arg_format = fmt;
    }

    void States::set_val_type(const val_type_t &fmt) {
        last_arg_type = fmt;
    }

    void States::set_ret_val(const std::string &str) {
        std::stringstream buf(str);
        buf >> return_val;
    }

    void States::set_name(const std::string &str) {
        name = str;
    }

    void States::set_bitfields(const bool &b) {
        bitfields = b;
    }

    int States::get_ret_val() {
        return return_val;
    }

    bool &States::get_bitfields() {
        return bitfields;
    }

    std::string &States::get_name() {
        return name;
    }

    val_format_t &States::get_val_format() {
        return arg_format;
    }

    val_type_t &States::get_val_type() {
        return last_arg_type;
    }

    void States::clear() {
        parsed_val.clear();
        arg_num = 0;
        bitfields = false;
    }

    std::string States::argsStr() {
        std::string str {" "};

        for (auto &w : parsed_val) {
            std::string tmp = std::visit([](auto &&arg) -> std::string {
                using T = std::decay_t<decltype(arg)>;

                if constexpr(std::is_same_v<T, unsigned long>)
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

        if (parsed_val.empty()) {
            // std::cerr << "Error: " << this->get_name() << ": Parsed val is empty." << std::endl;

            argument_t a;

            s.next.emplace_back(a);
            s.arg_num = this->arg_num;
            s.return_code = this->return_val;
            s.name = this->get_name();

        }
        else {
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
        }


        return s;

    }

} // namespace st2se
