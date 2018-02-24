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

    using argument_t = std::variant<int, std::string>;

    struct _argument_body_t {
        val_format_t value_format;
        val_type_t value_type;
        std::string key;
        std::variant<int, std::string> value;

    };

    using argument_body_t = struct _argument_body_t;


    struct _arg_container_t;
    struct _arg_container_t {
        argument_body_t argument;
        std::vector<_arg_container_t> next;
    };
    // typedef struct _arg_container_t arg_container_t;
    using arg_container_t = struct _arg_container_t;

    struct Syscall_t {
        std::string name;
        int return_code;
        std::string other;
        unsigned arg_num;
        std::vector<arg_container_t> arg;
        void print();

    };

    class Ids {
        using Sc_map = std::map<std::string, Syscall_t>;
      public:
        Sc_map data {};
        bool insert(const std::string &name, Syscall_t &sc);
        std::vector<arg_container_t> &insertArg(arg_container_t &arg, std::vector<arg_container_t> &container);

        void printSyscall();
        void print();

    };

} // end of namespace

#endif
