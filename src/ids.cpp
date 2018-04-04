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

    bool operator==(const st2se::argument_t &lhs, const st2se::argument_t &rhs) {
        // std::cout << POSITION_MACRO << "comapring:" << std::endl;
        // std::cout << "\t" << lhs.value_type << "\t" << rhs.value_type << std::endl;
        // std::cout << "\t" << lhs.value_format << "\t" << rhs.value_format << std::endl;
        // std::cout << "\t'" << lhs.key << "'\t'" << rhs.key << "'" << std::endl;
        // std::cout << "\t" << arg2str(lhs) << "\t" << arg2str(rhs) << std::endl;

        bool b_val = false;

        if (auto lval = std::get_if<long>(&lhs.value))
            if (auto rval = std::get_if<long>(&rhs.value))
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

    std::ostream &operator<< (std::ostream &os, const st2se::val_format_t &a) {
        // TODO transformt this into switch case statement
        if (a == st2se::val_format_t::KEY_VALUE) {
            return os << "KEY_VALUE";
        }

        if (a == st2se::val_format_t::VALUE) {
            return os << "VALUE";
        }

        if (a == st2se::val_format_t::EMPTY) {
            return os << "EMPTY";
        }

        return os << "UNDEF";
    }

    std::ostream &operator<< (std::ostream &os, const st2se::val_type_t &a) {
        // TODO transformt this into switch case statement
        if (a == st2se::val_type_t::INTEGER) {
            return os << "INTEGER";
        }

        if (a == st2se::val_type_t::STRING) {
            return os << "STRING";
        }

        if (a == st2se::val_type_t::CONSTANT) {
            return os << "CONSTANT";
        }

        if (a == st2se::val_type_t::POINTER) {
            return os << "POINTER";
        }

        if (a == st2se::val_type_t::ARRAY) {
            return os << "ARRAY";
        }

        if (a == st2se::val_type_t::STRUCTURE) {
            return os << "STRUCTURE";
        }

        if (a == st2se::val_type_t::BITFIELD) {
            return os << "BITFIELD";
        }

        if (a == st2se::val_type_t::CLUSTERS) {
            return os << "CLUSTERS";
        }

        if (a == st2se::val_type_t::EMPTY) {
            return os << "EMPTY";
        }

        return os << "UNDEF";
    }

    _argument_t::_argument_t(val_format_t _fmt, val_type_t _type, std::vector<_argument_t> _vec):
        value_format(_fmt), value_type(_type), next(_vec) {
    }

    _argument_t::_argument_t(val_format_t &_fmt, val_type_t &_type, std::string &_key, std::variant<long, std::string> _value, std::vector<_argument_t> _next):
        value_format(_fmt), value_type(_type), key(_key), value(_value), next(_next) {
    }

    _argument_t::_argument_t():
        value_format(val_format_t::EMPTY),
        value_type(val_type_t::EMPTY),
        key(""),
        value(""),
        next({}) {
    }

    void _argument_t::print(){
    
        std::function<void(std::string, std::vector<argument_t>)> print_recursive;

        print_recursive = [&print_recursive](std::string prefix, std::vector<argument_t> container) {
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

        print_recursive("\t"+arg2str(*this), next);
    }

    bool Ids::insert(const std::string &name, Syscall_t &sc) {

        Syscall_t &root_sc = data[name];

        if (root_sc.next.empty()) {
            root_sc.name = sc.name;
            root_sc.return_code = sc.return_code;
            root_sc.other = sc.other;
            std::copy(sc.next.begin(), sc.next.end(), std::back_inserter(root_sc.next));

            // std::cout << __func__ << "\tinserting new arg" << std::endl;

        }
        else {
            for (argument_t arg : sc.next) {
                insertArg(arg, root_sc.next);
            }
        }

        // std::cout << "#### SC contains #####" << std::endl;
        // root_sc.print();
        // std::cout << "######################" << std::endl;

        return true;
    }

    std::vector<argument_t> &Ids::insertArg(argument_t &arg, std::vector<argument_t> &container) {

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

    void Syscall_t::print() {
        std::cout << name << ":" << std::endl ;

        if(clustered){
            printClustered();
            return;
        }

        if (next.empty()) {
            std::cout << "No args" << std::endl;
        }
        else {
            std::function<void(std::string, std::vector<argument_t>)> print_recursive;

            // lambda for recursive descent over argumnet tree;
            print_recursive = [&print_recursive](std::string prefix, std::vector<argument_t> container) {
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

    void Syscall_t::printClustered() {

        if (next.empty()) {
            std::cout << "No args" << std::endl;
        }
        else {
            for(auto &pos : next){
                std::cout << "Clusters for arg:" << std::endl;
                for(auto item1 : pos.next){
                    std::cout << "\t" << arg2str(item1) << ", ";
                    for(auto item2 : item1.next)
                        std::cout << arg2str(item2) << ", ";
                    std::cout << std::endl;
                }
            }
        }
    }

    // move this function to utilities
    std::string arg2str(const argument_t &arg) {
        // *INDENT-OFF*
        // std::cout << POSITION_MACRO << "\tval_type:" << arg.value_type << std::endl;
        // std::cout << POSITION_MACRO << "\tvalue:" << std::endl;
        const bool pointer = arg.value_type == val_type_t::POINTER;
        return std::visit(
            [pointer](auto &&arg) -> std::string {
                using T = std::decay_t<decltype(arg)>;

                if constexpr(std::is_same_v<T, long>){
                    if(pointer){
                        std::stringstream ss;
                        std::string ret_val;

                        ss << std::hex << arg;
                        ss >> ret_val;

                        return "0x" + ret_val;
                    }
                    return std::to_string(arg);
                }
                else if constexpr(std::is_same_v<T, std::string>)
                    return arg;
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
