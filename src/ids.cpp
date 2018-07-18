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

#include "ids.hpp"

template<class T> struct always_false : std::false_type {};

namespace st2se {

    std::ostream &operator<< (std::ostream &os, const st2se::Ids &a) {
        for (const auto &item : a.data) {
            os << item.first
                << " has "
                << item.second.next.size()
                << " arguments"
                << std::endl;
        }

        return os << std::endl << std::endl;
    }

    // Make sure you are putting two INTEGER values into this operator
    bool operator<(const st2se::Argument &lhs, const st2se::Argument &rhs) {

        if (lhs.value < rhs.value) {
            return true;
        }

        return false;
    }


    bool operator==(const st2se::Argument &lhs, const st2se::Argument &rhs) {
        // std::cout << POSITION_MACRO << "comapring:" << std::endl;
        // std::cout << "\t" << lhs.value_type << "\t" << rhs.value_type << std::endl;
        // std::cout << "\t" << lhs.value_format << "\t" << rhs.value_format << std::endl;
        // std::cout << "\t'" << lhs.key << "'\t'" << rhs.key << "'" << std::endl;
        // std::cout << "\t" << arg2str(lhs) << "\t" << arg2str(rhs) << std::endl;

        bool b_val = false;

        if (auto lval = std::get_if<unsigned long>(&lhs.value))
            if (auto rval = std::get_if<unsigned long>(&rhs.value))
                if (*lval == *rval) {
                    b_val = true;
                }

        if (auto lval = std::get_if<std::string>(&lhs.value))
            if (auto rval = std::get_if<std::string>(&rhs.value))
                if (!lval->compare(*rval)) {
                    b_val = true;
                }

        // std::cout << "\tb_val:" << b_val << std::endl;

        // std::cout << "\treturning:" << (lhs.value_type == rhs.value_type &&
        // lhs.value_format == rhs.value_format &&
        // !lhs.key.compare(rhs.key) &&
        // b_val) << std::endl;

        return lhs.value_type == rhs.value_type &&
            lhs.value_format == rhs.value_format &&
            !lhs.key.compare(rhs.key) &&
            b_val;
    }

    std::ostream &operator<< (std::ostream &os, const st2se::Value_format &a) {
        // TODO transformt this into switch case statement
        if (a == st2se::Value_format::KEY_VALUE) {
            return os << "KEY_VALUE";
        }

        if (a == st2se::Value_format::VALUE) {
            return os << "VALUE";
        }

        if (a == st2se::Value_format::EMPTY) {
            return os << "EMPTY";
        }

        return os << "UNDEF";
    }

    std::ostream &operator<< (std::ostream &os, const st2se::Value_type &a) {
        // TODO transformt this into switch case statement
        if (a == st2se::Value_type::INTEGER) {
            return os << "INTEGER";
        }

        if (a == st2se::Value_type::STRING) {
            return os << "STRING";
        }

        if (a == st2se::Value_type::CONSTANT) {
            return os << "CONSTANT";
        }

        if (a == st2se::Value_type::POINTER) {
            return os << "POINTER";
        }

        if (a == st2se::Value_type::ARRAY) {
            return os << "ARRAY";
        }

        if (a == st2se::Value_type::STRUCTURE) {
            return os << "STRUCTURE";
        }

        if (a == st2se::Value_type::BITFIELD) {
            return os << "BITFIELD";
        }

        if (a == st2se::Value_type::CLUSTERS) {
            return os << "CLUSTERS";
        }

        if (a == st2se::Value_type::EMPTY) {
            return os << "EMPTY";
        }

        return os << "UNDEF";
    }

    _Argument::_Argument(Value_format _fmt, Value_type _type, std::vector<_Argument> _vec)
        : value_format(_fmt), value_type(_type), next(_vec) {
    }

    _Argument::_Argument(Value_format &_fmt, Value_type &_type, std::string &_key,
        std::variant<unsigned long, std::string> _value, std::vector<_Argument> _next)
        : value_format(_fmt), value_type(_type), key(_key), value(_value), next(_next) {
    }

    _Argument::_Argument():
        value_format(Value_format::EMPTY),
        value_type(Value_type::EMPTY),
        key(""),
        value(""),
        next({}) {
    }

    void _Argument::print() {

        std::function<void(std::string, std::vector<Argument>)> print_recursive;

        print_recursive = [&print_recursive](std::string prefix, std::vector<Argument> container) {
            for (auto item : container) {
                std::string printing = prefix + " '" + arg2str(item) + "',";

                // if this is the last element print the whole string with arguments
                if (item.next.empty()) {
                    std::cout << printing << "\b " << std::endl;
                }
                else {
                    //recursive descent
                    print_recursive(printing, item.next);
                }
            }
        };

        print_recursive("\t" + arg2str(*this), next);
    }

    bool Ids::insert(const std::string &name, Syscall &sc) {

        Syscall &root_sc = data[name];

        if (root_sc.next.empty()) {
            root_sc.name = sc.name;
            root_sc.return_code = sc.return_code;
            root_sc.other = sc.other;
            root_sc.arg_num = sc.arg_num;
            std::copy(sc.next.begin(), sc.next.end(), std::back_inserter(root_sc.next));

            // std::cout << __func__ << "\tinserting new arg" << std::endl;

        }
        else {
            for (Argument arg : sc.next) {
                insertArg(arg, root_sc.next);
            }
        }

        // std::cout << "#### SC contains #####" << std::endl;
        // root_sc.print();
        // std::cout << "######################" << std::endl;

        return true;
    }

    std::vector<Argument> &Ids::insertArg(Argument &arg, std::vector<Argument> &container) {

        // std::cout << "-------------------------------------" << std::endl <<  std::endl;
        // std::cout << "Inserting Arg: " << arg2str(arg) << std::endl;
        // std::cout << "-------------------------------------" << std::endl <<  std::endl;

        for (auto &item : container) {
            if (item == arg) {
                // std::cout << "\t cmp: \t" << item.key+"=";
                // std::visit([](auto &&arg) {
                //     std::cout << "'" << arg << "'";
                // }, item.value);

                // std::cout << "  and  " << arg.key+"=";
                // std::visit([](auto &&arg) {
                //     std::cout << arg;
                // }, arg.value);

                // std::cout << std::endl;

                // std::cout << __func__ << "\tis there" << std::endl;

                if (arg.next.empty()) {
                    return container;
                }
                else {
                    insertArg(arg.next.front(), item.next);
                    return container;
                }
            }
        }

        // std::cout << __func__ << "\tnot_there" << std::endl;

        container.emplace_back(arg);

        // std::cout << "-------------------------------------\n\n\n" << std::endl;

        return container.back().next;
    }

    void Ids::print() {
        std::cout << *this << std::endl;

        for (auto item : data) {
            item.second.print();
        }
    }

    void Syscall::print() {
        std::cout << name << ":" << std::endl ;

        if (clustered) {
            printClustered();
            return;
        }

        if (next.empty()) {
            std::cout << "No args" << std::endl;
        }
        else {
            std::function<void(std::string, std::vector<Argument>)> print_recursive;

            // lambda for recursive descent over argumnet tree;
            print_recursive = [&print_recursive](std::string prefix, std::vector<Argument> container) {
                for (auto item : container) {
                    std::string printing = prefix + " '" + arg2str(item) + "',";

                    // if this is the last element print the whole string with arguments
                    if (item.next.empty()) {
                        std::cout << printing << "\b " << std::endl;
                    }
                    else {
                        //recursive descent
                        print_recursive(std::string(printing), item.next);
                    }
                }
            };

            print_recursive("\t", next);
        }
    }

    void Syscall::printClustered() {

        if (next.empty()) {
            std::cout << "No args" << std::endl;
        }
        else {
            // iterate through positions
            for (auto &pos : next) {
                std::cout << "Clusters for arg:" << std::endl;

                // iterate through clusters
                for (auto &cluster : pos.next) {
                    std::cout << "\t" << arg2str(cluster) << ", ";

                    // iterate in cluster
                    for (auto &item : cluster.next) {
                        std::cout << arg2str(item) << ", ";
                    }

                    std::cout << std::endl;
                }
            }
        }
    }

    // move this function to utilities
    std::string arg2str(const Argument &arg) {
        // *INDENT-OFF*
        const bool pointer = arg.value_type == Value_type::POINTER;
        return std::visit(
            [pointer](auto &&val) -> std::string {
                using T = std::decay_t<decltype(val)>;

                if constexpr(std::is_same_v<T, unsigned long>){
                    if(pointer){
                        std::stringstream ss;
                        std::string ret_val;

                        ss << std::hex << val;
                        ss >> ret_val;

                        return "0x" + ret_val;
                    }
                    return std::to_string(val);
                }
                else if constexpr(std::is_same_v<T, std::string>)
                    return val;
                else {
                    static_assert(always_false<T>::value, "non-exhaustive visitor!");
                    return "Error: Variant is empty";
                }
            },
            arg.value
        );
        // *INDENT-ON*
    }
} // namespace st2se
