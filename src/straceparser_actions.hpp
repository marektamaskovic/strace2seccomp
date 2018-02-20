#ifndef STRACEPARSER_ACTIONS
#define STRACEPARSER_ACTIONS

#include <utility>

#include "straceparser_grammar.hpp"
#include "argparse.hpp"
#include "states.hpp"

extern int syscalls;

#define divideKV(InputStr,Key,Val)  \
    do{                                                           \
        if (states.get_val_format() == val_format_t::KEY_VALUE) { \
            std::string::size_type index;                         \
            index = InputStr.string().find_first_of("=");         \
                                                                  \
            Key = InputStr.string().substr(0, index);             \
            Val = InputStr.string().substr(index + 1);            \
        }                                                         \
        else {                                                    \
            Val = InputStr.string();                              \
        }                                                         \
    }while(0)

namespace st2se::grammar {
    template< typename Rule >
    struct action : tao::TAOCPP_PEGTL_NAMESPACE::nothing< Rule > {};

    template<>
    struct action< pointer > {
        template < typename Input >
        static void apply(const Input &in, st2se::Ids &out, Params &params, States &states) {
            (void) states;
            (void) out;

            states.set_val_type(val_type_t::POINTER);

            if (params.debug || params.verbose) {
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

            states.set_val_type(val_type_t::INTEGER);

            if (params.debug || params.verbose) {
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

            states.set_val_type(val_type_t::STRING);

            if (params.debug || params.verbose) {
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

            states.set_val_type(val_type_t::CONSTANT);

            if (params.debug || params.verbose) {
                std::cout << "constants: " << in.string() << std::endl;
            }
        }
    };

    template<>
    struct action< array > {
        template < typename Input >
        static void apply(const Input &in, st2se::Ids &out, Params &params, States &states) {
            (void) states;
            (void) out;

            states.set_val_type(val_type_t::ARRAY);

            if (params.debug || params.verbose) {
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

            states.set_val_type(val_type_t::STRUCTURE);

            if (params.debug || params.verbose) {
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

            states.set_val_format(val_format_t::VALUE);

            if (params.debug || params.verbose) {
                std::cout << "value: " << in.string() << std::endl;
            }
        }
    };

    template<>
    struct action< key_value > {
        template < typename Input >
        static void apply(const Input &in, st2se::Ids &out, Params &params, States &states) {
            (void) states;
            (void) out;

            states.set_val_format(val_format_t::KEY_VALUE);

            if (params.debug || params.verbose) {
                std::cout << "key_value: " << in.string() << std::endl;
            }
        }
    };

    template<>
    struct action< syscall_name > {
        template < typename Input >
        static void apply(const Input &in, st2se::Ids &out, Params &params, States &states) {
            (void) out;

            // clear states
            states.clear();

            if (params.debug || params.verbose) {
                std::cout << "syscall_name: " << in.string() << std::endl;
                std::cout << "args:" << std::endl;
            }
        }
    };

    template<>
    struct action< argument > {
        template < typename Input >
        static void apply(const Input &in, st2se::Ids &out, Params &params, States &states) {
            (void) out;

            std::cout << "Argumnet_action" << std::endl;

            std::string key {""};
            std::string val {""};

            divideKV(in,key,val);

            argument_body_t arg {states.get_val_format(), states.get_val_type(), key, val};

            std::cout << "idem pushnut" << std::endl;
            states.push_parsed_val(arg);

            if (params.debug || params.verbose) {
                std::cout << "argument: " << in.string() << std::endl;
            }

            // StraceParser::parsed_args.push_back(in.string())
        }
    };

    template<>
    struct action< strace_line > {
        template < typename Input >
        static void apply(const Input &in, st2se::Ids &out, Params &params, States &states) {
            (void) states;
            (void) out;

            ::syscalls++;

            if (params.debug || params.verbose) {
                std::cout << "strace_line: "
                          << in.string()            << std::endl
                          << "------------------"   << std::endl
                          << " pushed arguments: "  << std::endl
                          << states.argsStr()       << std::endl
                          << "------------------"   << std::endl
                          << std::endl << std::endl << std::endl;
            }
        }
    };

    template<>
    struct action< return_value > {
        template < typename Input >
        static void apply(const Input &in, st2se::Ids &out, Params &params, States &states) {
            (void) states;
            (void) out;

            if (params.debug || params.verbose) {
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

            if (params.debug || params.verbose) {
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

            if (params.debug || params.verbose) {
                std::cout << "exit_line: '" << in.string() << "'" << std::endl;
            }
        }
    };
}

#endif
