#ifndef _SRC_IDS_HPP
#define _SRC_IDS_HPP

#include <algorithm>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <type_traits>
#include <variant>
#include <vector>

#define POSITION_MACRO "\x1B[4m\x1B[34m" << __FILE__ << "\x1B[0m"  \
    << ":" << "\x1B[1m\x1B[31m" << __func__ << "()\x1B[0m"         \
    << ":\x1B[32m" << __LINE__ << "\x1B[0m:"

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
        BITFIELD,
        CLUSTERS,
        EMPTY
    };

    struct _argument_t;
    struct _argument_t {
        val_format_t value_format {val_format_t::EMPTY};
        val_type_t value_type {val_type_t::EMPTY};
        std::string key {""};
        std::variant<unsigned long, std::string> value {""};
        std::vector<_argument_t> next;
        _argument_t();
        _argument_t(val_format_t _fmt, val_type_t _type, std::vector<_argument_t> _vec);
        _argument_t(val_format_t &_fmt, val_type_t &_type, std::string &_key, std::variant<unsigned long, std::string> _value,
            std::vector<_argument_t> _next);

        void print();
    };

    using argument_t = struct _argument_t;

    struct Syscall_t {
        std::string name {""};
        int return_code {0};
        std::string other {""};
        unsigned arg_num {0};
        std::vector<argument_t> next {};
        bool clustered = false;

        void print();
        void printClustered();
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

    std::string arg2str(const argument_t &arg);
    bool operator== (const st2se::argument_t &lhs, const st2se::argument_t &rhs);
    bool operator< (const st2se::argument_t &lhs, const st2se::argument_t &rhs);
    std::ostream &operator<< (std::ostream &os, const st2se::Ids &a);
    std::ostream &operator<< (std::ostream &os, const st2se::val_type_t &a);
    std::ostream &operator<< (std::ostream &os, const st2se::val_format_t &a);

} // namespace st2se

#endif
