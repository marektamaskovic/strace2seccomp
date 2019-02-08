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

#include "states.hpp"

template<class T> struct always_false : std::false_type {};

#if __cplusplus < 201703L // C++14 version and bellow
    #include "cpp14_support.hpp"
    namespace variant_ns = mpark;
#else // C++17
    namespace variant_ns = std;
#endif

namespace st2se {
    void States::push_parsed_val(Argument &arg) {
        parsed_val.push_back(arg);
    }

    void States::pop_parsed_val() {
        parsed_val.pop_back();
    }

    bool States::process_val(Ids &ids) {

        Syscall s = getSyscall();

        ids.insert(get_name(), s);

        // s.print();

        return true;
    }

    void States::set_val_format(const ValueFormat &fmt) {
        arg_format = fmt;
    }

    void States::set_val_type(const ValueType &fmt) {
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

    ValueFormat &States::get_val_format() {
        return arg_format;
    }

    ValueType &States::get_val_type() {
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
            std::string tmp;

            if (w.valueType == ValueType::INTEGER) {
                    tmp = std::to_string(variant_ns::get<unsigned long>(w.value));
            }
            else if (w.valueType == ValueType::STRING) {
                tmp = variant_ns::get<std::string>(w.value);
            }
            else {
                std::cerr << "Error: Variant is empty";
                tmp = "";
            }

            str.append(tmp + ",\n ");
        }

        return str;
    }

    Syscall States::getSyscall() {
        Syscall s;

        if (parsed_val.empty()) {
            // std::cerr << "Error: " << this->get_name() << ": Parsed val is empty." << std::endl;

            Argument a;

            s.next.emplace_back(a);
            s.arg_num = this->arg_num;
            s.return_code = this->return_val;
            s.name = this->get_name();

        }
        else {
            Argument a, b;

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
