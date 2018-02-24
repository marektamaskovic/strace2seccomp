#include "ids.hpp"

template<class T> struct always_false : std::false_type {};

std::ostream &operator<< (std::ostream &os, const st2se::Ids &a) {
    for (const auto &item : a.data) {
        os << item.first
            << " has "
            << item.second.arg.size()
            << " arguments"
            << std::endl;
    }

    return os << std::endl << std::endl;
}

bool operator==(const st2se::argument_body_t &lhs, const st2se::argument_body_t &rhs) {
    return lhs.value_type == rhs.value_type &&
        lhs.value_format == rhs.value_format &&
        lhs.key == rhs.key &&
        lhs.value == rhs.value;
}


namespace st2se {

    bool Ids::insert(const std::string &name, Syscall_t &sc) {

        std::cout << "=====================================" << std::endl;
        std::cout << __FILE__ << ":" << __func__ << std::endl;
        std::cout << "=====================================" << std::endl;

        Syscall_t &root_sc = this->data[name];

        std::cout << __func__ << "\targ_num:\t\t" << sc.arg_num << std::endl;
        std::cout << __func__ << "\tvec_size_before:\t" << sc.arg.size() << std::endl;
        std::cout << __func__ << "\tids_sc_uniq_arg:\t" << root_sc.arg.size() << std::endl;

        if (root_sc.arg.empty()) {
            root_sc.arg = sc.arg;
            root_sc.return_code = sc.return_code;
            root_sc.other = sc.other;
            std::cout << __func__ << "\tinserting new arg" << std::endl;

        }
        else {
            auto & inserting = sc.arg.front();
            auto & place = root_sc.arg;

            for(unsigned i = 0; i < sc.arg_num; i++){
                place = insertArg(inserting, place);
                if(inserting.next.empty())
                    break;
                inserting = inserting.next.front();
            }

            std::cout << __func__ << "\tids_sc_uniq_arg:" << root_sc.arg.size() << std::endl;

        }

        std::cout << "=====================================" << std::endl;
        // this->printSyscall();
        return true;
    }

    void Ids::print(void) {
        std::cout << *this << std::endl;
    }

    void Ids::printSyscall() {

        for(const auto & sc : this->data){
            std::cout << sc.first << std::endl;
            std::visit(
                [](auto&& arg){
                    std::cout << "\t" << arg;
                },
                sc.second.arg.front().argument.value
            );

            std::cout << std::endl;

        }

        return;
    }

    std::vector<arg_container_t> &Ids::insertArg(arg_container_t &arg, std::vector<arg_container_t> &container) {

        std::cout << "-------------------------------------" << std::endl;
        std::cout << __FILE__ << ":" << __func__ << std::endl;
        std::cout << "-------------------------------------" << std::endl;
        std::visit(
            [](auto&& arg){
                std::cout << "'" << arg << "'" << std::endl;
            },
            arg.argument.value
        );

        for (auto &item : container) {
            if (item.argument == arg.argument) {
                std::cout << "\t cmp: \t" << item.argument.key+"=";
                std::visit([](auto&& arg){std::cout << "'" << arg << "'";}, item.argument.value);

                std::cout << "  and  " << arg.argument.key+"=";
                std::visit([](auto&& arg){std::cout << arg;}, arg.argument.value);

                std::cout << std::endl;

                std::cout << __func__ << "\tis there" << std::endl;

                return item.next;
            }
        }

        std::cout << __func__ << "\templace_back" << std::endl;

        if(container.empty()){
            container.emplace_back(arg);
        }
        else{
            arg_container_t c;
            c.argument = arg.argument;
            container.push_back(c);
        }

        std::cout << "-------------------------------------" << std::endl <<  std::endl;

        return container.back().next;
    }

    void Syscall_t::print(){
        std::cout << name << std::endl;

        if(arg.empty()){
            std::cout << "No args" << std::endl;
        }
        else{
            auto container = arg;

            std::function<void(std::string, std::vector<arg_container_t>)> print_l;

            print_l = [print_l](std::string prefix, std::vector<arg_container_t> arg) {
                for(auto s : arg){
                    std::cout << prefix << ", ";
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
                    }, s.argument.value);

                    print_l(std::string(prefix+", "+tmp), s.next);
                }
            };

            print_l("\t", container);
        }

        return;
    }

} // end of namespace
