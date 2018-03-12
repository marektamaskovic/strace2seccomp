#include "ids.hpp"

template<class T> struct always_false : std::false_type {};

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
    return lhs.value_type == rhs.value_type &&
        lhs.value_format == rhs.value_format &&
        lhs.key == rhs.key &&
        lhs.value == rhs.value;
}


namespace st2se {

    bool Ids::insert(const std::string &name, Syscall_t &sc) {

        Syscall_t &root_sc = this->data[name];

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

    void Ids::print(void) {
        std::cout << *this << std::endl;

        for (auto item : data) {
            item.second.print();
        }
    }

    void Syscall_t::print() {
        std::cout << name << std::endl ;

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

            print_recursive("\t", this->next);
        }

        return;
    }

    // move this function to utilities
    std::string arg2str(argument_t &arg) {
        // *INDENT-OFF*
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
                    else{
                        return std::to_string(arg);
                    }
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

} // end of namespace
