#ifndef _SRC_STRACEPARSER_ACTIONS
#define _SRC_STRACEPARSER_ACTIONS

#include <utility>

#include "tao/pegtl.hpp"
#include "tao/pegtl/contrib/tracer.hpp"

#include "straceparser_grammar.hpp"
#include "argparse.hpp"
#include "states.hpp"

extern int syscalls;

const std::map<std::string, int> signal_map {
    {"SIGHUP", 1},
    {"SIGINT", 2},
    {"SIGQUIT", 3},
    {"SIGILL", 4},
    {"SIGTRAP", 5},
    {"SIGABRT", 6},
    {"SIGBUS", 7},
    {"SIGFPE", 8},
    {"SIGKILL", 9},
    {"SIGUSR1", 10},
    {"SIGSEGV", 11},
    {"SIGUSR2", 12},
    {"SIGPIPE", 13},
    {"SIGALRM", 14},
    {"SIGTERM", 15},
    {"SIGSTKFLT", 16},
    {"SIGCHLD", 17},
    {"SIGCONT", 18},
    {"SIGSTOP", 19},
    {"SIGTSTP", 20},
    {"SIGTTIN", 21},
    {"SIGTTOU", 22},
    {"SIGURG", 23},
    {"SIGXCPU", 24},
    {"SIGXFSZ", 25},
    {"SIGVTALRM", 26},
    {"SIGPROF", 27},
    {"SIGWINCH", 28},
    {"SIGIO", 29},
    {"SIGPWR", 30},
    {"SIGSYS", 31},
    {"SIGEMT", 32},
};

// *INDENT-OFF*
#define divideKV(InputStr,Key,Val)                                  \
    do{                                                             \
        if (states.get_val_format() == val_format_t::KEY_VALUE) {   \
            std::string::size_type index;                           \
            index = (InputStr).string().find_first_of("=");         \
                                                                    \
            (Key) = (InputStr).string().substr(0, index);           \
        }                                                           \
        else {                                                      \
            (Val) = (InputStr).string();                            \
        }                                                           \
    }while(0)
// *INDENT-ON*

namespace st2se::grammar {
    template< typename Rule >
    struct action : tao::TAOCPP_PEGTL_NAMESPACE::nothing< Rule > {};

    template<>
    struct action< pointer > {
        template < typename Input >
        static void apply(const Input &in, st2se::Ids &out, Params &params, States &states) {
            (void) states;
            (void) out;
            (void) in;
            (void) params;

            states.set_val_type(val_type_t::POINTER);

            if (params.debug) {
                std::cout << "pointer: " << in.string() << std::endl;
            }
        }
    };

    template<>
    struct action< str_nullpointer > {
        template < typename Input >
        static void apply(const Input &in, st2se::Ids &out, Params &params, States &states) {
            (void) states;
            (void) out;
            (void) in;
            (void) params;

            states.set_val_type(val_type_t::POINTER);

            if (params.debug) {
                std::cout << "pointer: " << in.string() << std::endl;
            }
        }
    };

    template<>
    struct action< integer > {
        template < typename Input >
        static void apply(const Input &in, st2se::Ids &out, Params &params, States &states) {
            (void) states;
            (void) out;
            (void) in;
            (void) params;

            states.set_val_type(val_type_t::INTEGER);

            if (params.debug) {
                std::cout << "integer: " << in.string() << std::endl;
            }
        }
    };
    template<>
    struct action< string > {
        template < typename Input >
        static void apply(const Input &in, st2se::Ids &out, Params &params, States &states) {
            (void) states;
            (void) out;
            (void) in;
            (void) params;

            states.set_val_type(val_type_t::STRING);

            if (params.debug) {
                std::cout << "string: " << in.string() << std::endl;
            }
        }
    };

    template<>
    struct action< constants > {
        template < typename Input >
        static void apply(const Input &in, st2se::Ids &out, Params &params, States &states) {
            (void) states;
            (void) out;
            (void) in;
            (void) params;

            states.set_val_type(val_type_t::CONSTANT);


            std::string s = in.string();
            std::string delim = "|";
            std::vector<std::string> bitfields;

            auto start = 0U;
            auto end = s.find(delim);

            while (end != std::string::npos) {
                states.set_val_type(val_type_t::BITFIELD);
                bitfields.push_back(s.substr(start, end - start));
                start = end + delim.length();
                end = s.find(delim, start);
            }

            bitfields.push_back(s.substr(start, end));
            std::sort(bitfields.begin(), bitfields.end());

            std::string merge;

            for (unsigned i = 0; i < bitfields.size(); i++) {
                merge += bitfields[i] + "|";
            }

            merge.resize(merge.size() - 1);

            if (params.debug) {
                std::cout << "constants: " << merge << std::endl;
            }

            states.value = merge;
            states.set_bitfields(true);
        }
    };

    template<>
    struct action< array > {
        template < typename Input >
        static void apply(const Input &in, st2se::Ids &out, Params &params, States &states) {
            (void) states;
            (void) out;
            (void) in;
            (void) params;

            states.set_val_type(val_type_t::ARRAY);

            if (params.debug) {
                std::cout << "array: " << in.string() << std::endl;
            }
        }
    };

    template<>
    struct action< structure > {
        template < typename Input >
        static void apply(const Input &in, st2se::Ids &out, Params &params, States &states) {
            (void) states;
            (void) out;
            (void) in;
            (void) params;

            states.set_val_type(val_type_t::STRUCTURE);

            if (params.debug) {
                std::cout << "structure: " << in.string() << std::endl;
            }
        }
    };

    template<>
    struct action< value > {
        template < typename Input >
        static void apply(const Input &in, st2se::Ids &out, Params &params, States &states) {
            (void) states;
            (void) out;
            (void) in;
            (void) params;

            // states.set_val_format(val_format_t::VALUE);

            if (states.get_val_type() == val_type_t::INTEGER) {
                // FIXME rewrite it as a template
                try {
                    states.value = std::stol(in.string());
                }
                catch (std::out_of_range &e) {
                    throw tao::pegtl::parse_error("stol err '" + in.string() + "'", in);
                }
            }
            else if (states.get_val_type() == val_type_t::POINTER) {
                if (!in.string().compare("NULL") || !in.string().compare("nullptr")) {
                    states.value = 0;
                }
                else {
                    // FIXME rewrite it as a template
                    try {
                        states.value = std::stol(in.string(), nullptr, 16);
                    }
                    catch (std::out_of_range &e) {
                        throw tao::pegtl::parse_error("stol err '" + in.string() + "'", in);
                    }
                }
            }
            else {
                if (!states.get_bitfields()) {
                    states.value = in.string();
                }
            }

            if (params.debug) {
                std::cout << "value: " << in.string() << "  ?" << std::endl;
            }
        }
    };

    template<>
    struct action< key_value > {
        template < typename Input >
        static void apply(const Input &in, st2se::Ids &out, Params &params, States &states) {
            (void) states;
            (void) out;
            (void) in;
            (void) params;

            states.set_val_format(val_format_t::KEY_VALUE);

            if (params.debug) {
                std::cout << "key_value: " << in.string() << std::endl;
            }
        }
    };

    template<>
    struct action< syscall_name > {
        template < typename Input >
        static void apply(const Input &in, st2se::Ids &out, Params &params, States &states) {
            (void) states;
            (void) out;
            (void) in;
            (void) params;

            // clear states
            states.clear();

            states.set_name(in.string());

            if (params.debug) {
                std::cout << "\n\nsyscall_name: " << in.string() << std::endl;
            }
        }
    };

    template<>
    struct action< syscall_line > {
        template < typename Input >
        static void apply(const Input &in, st2se::Ids &out, Params &params, States &states) {
            (void) states;
            (void) out;
            (void) in;
            (void) params;

            // process
            states.process_val(out);

            if (params.debug) {
                std::cout << "syscall_line: " << in.string() << std::endl;
            }
        }
    };

    template<>
    struct action< argument > {
        template < typename Input >
        static void apply(const Input &in, st2se::Ids &out, Params &params, States &states) {
            (void) states;
            (void) out;
            (void) in;
            (void) params;

            std::string key {""};
            std::string val {""};
            states.arg_num++;
            divideKV(in, key, val);

            val_type_t _type = states.get_val_type();
            val_format_t _fmt = states.get_val_format();


            argument_t arg(_fmt, _type, key, states.value, {});
            states.push_parsed_val(arg);

            if (params.debug) {
                std::cout << "argument: " << in.string() << std::endl;
            }
        }
    };

    template<>
    struct action< strace_line > {
        template < typename Input >
        static void apply(const Input &in, st2se::Ids &out, Params &params, States &states) {
            (void) states;
            (void) out;
            (void) in;
            (void) params;

            ::syscalls++;

            // if (params.debug) {
            //     std::cout
            //     //     << "strace_line: "
            //     << in.string()            << std::endl
            //     << "------------------"   << std::endl
            //     << " pushed arguments: "  << std::endl
            //     << states.argsStr()       << std::endl
            //     << "------------------"   << std::endl
            //             << std::endl << std::endl << std::endl;
            // }
        }
    };

    template<>
    struct action< return_value > {
        template < typename Input >
        static void apply(const Input &in, st2se::Ids &out, Params &params, States &states) {
            (void) states;
            (void) out;

            if (params.debug) {
                std::cout << "return_value: '" << in.string() << "'" << std::endl;
            }
        }
    };

    template<>
    struct action< inline_comment > {
        template < typename Input >
        static void apply(const Input &in, st2se::Ids &out, Params &params, States &states) {
            (void) states;
            (void) out;

            if (params.debug) {
                std::cout << "inline_comment: '" << in.string() << "'" << std::endl;
            }
        }
    };

    template<>
    struct action< exit_line > {
        template < typename Input >
        static void apply(const Input &in, st2se::Ids &out, Params &params, States &states) {
            (void) states;
            (void) out;

            if (params.debug) {
                std::cout << "exit_line: '" << in.string() << "'" << std::endl;
            }
        }
    };
} // namespace st2se::grammar

#endif
