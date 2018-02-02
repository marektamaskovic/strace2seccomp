#ifndef TYPES_HPP
#define TYPES_HPP

#include <string>
#include <vector>
#include <map>

namespace st2se {

    struct arg_t;

    struct arg_t {
        enum class type {VALUE, PATH, STRING, STRUCTURE, ARRAY, UNKNOWN};
        std::string key;
        std::string val;
        type arg_type;
        std::vector<arg_t> next_arg;
    };

    struct syscall_t {
        std::vector<arg_t> arg;
        int return_code;
        std::string other;
    };

    class Ids {
        using sc_map = std::map<std::string, syscall_t>;
        sc_map data;

      public:
        // Ids();
        bool insert(syscall_t& sc);
        void printSyscall();

    };

} // end of namespace

#endif
