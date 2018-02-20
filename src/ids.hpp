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

namespace st2se {

    enum class val_format_t {
        KEY_VALUE,
        VALUE
    };

    enum class val_type_t {
        POINTER,
        INTEGER,
        STRING,
        CONSTANT,
        ARRAY,
        STRUCTURE
    };

    using argument_t = std::variant<int, std::string>;

    struct _argument_body_t {
        val_format_t value_format;
        val_type_t value_type;
        std::string key;
        std::variant<int, std::string> value;
        // std::string value;
    };

    using argument_body_t = struct _argument_body_t;


    struct _arg_container_t;
    struct _arg_container_t {
        argument_body_t argument;
        std::vector<_arg_container_t> next;
    };
    typedef struct _arg_container_t arg_container_t;

    struct Syscall_t {
        int return_code;
        std::string other;
        std::vector<arg_container_t> arg;
    };

    class Ids {
        using Sc_map = std::map<std::string, Syscall_t>;
        Sc_map data {};
      public:
        bool insert(Syscall_t &sc);
        void printSyscall();

    };

} // end of namespace

#endif
