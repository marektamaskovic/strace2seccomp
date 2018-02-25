#ifndef TYPES_HPP
#define TYPES_HPP

#include <string>
#include <vector>
#include <map>
#include <iomanip>
#include <iostream>
#include <type_traits>
#include <variant>
#include <algorithm>
#include <vector>
#include <functional>
#include <algorithm>

namespace st2se {

    enum class val_format_t {
        KEY_VALUE,
        VALUE,
        EMPTY
    };

    enum class val_type_t {
        POINTER,
        INTEGER,
        STRING,
        CONSTANT,
        ARRAY,
        STRUCTURE,
        EMPTY
    };

    struct _argument_t;
    struct _argument_t {
        val_format_t value_format;
        val_type_t value_type;
        std::string key;
        std::variant<int, std::string> value;
        std::vector<_argument_t> next;
    };

    using argument_t = struct _argument_t;

    struct Syscall_t {
        std::string name;
        int return_code;
        std::string other;
        unsigned arg_num;
        std::vector<argument_t> next;

        void print();

    };

    class Ids {
        using Sc_map = std::map<std::string, Syscall_t>;
      public:
        Sc_map data {};
        bool insert(const std::string &name, Syscall_t &sc);
        std::vector<argument_t> &insertArg(argument_t &arg, std::vector<argument_t> &container);

        void printSyscall();
        void print();

    };

    std::string arg2str(argument_t &arg);

} // end of namespace

#endif
