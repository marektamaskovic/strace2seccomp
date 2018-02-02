#ifndef PARSER_HPP
#define PARSER_HPP

#include <iostream>
#include <fstream>
#include <string>

#include "ids.hpp"
#include "tao/pegtl.hpp"


namespace st2se {

    class StraceParser {
        std::string filename {""};
        Ids& output;
      public:
        StraceParser();
        StraceParser(std::string _filename, st2se::Ids& _output);
        // ~StraceParser();

        static bool parse(std::string _filename, st2se::Ids& _output);

        std::string getFilename();
    };

    namespace grammar {

        using namespace tao::pegtl;

        struct arguments;


        // struct argument : plus< not_one<',', ')', '{', '}', '[', ']' > > {};
        // struct argument : seq< plus< any >, at<one<',', ')', '}', ']'>> > {};
        // struct structure : plus< one <'{'>, arguments, one <'}'>, at<one<',',')',']'> > > {};
        // struct array     : plus< one <'['>, arguments, one <']'>, at<one<',',')','}'> > > {};
        // struct quoted : seq< one<'"'>, plus< any >, one<'"'> > {};
        // struct expr : seq< identifier, istring<'='>, sor<array,argument,structure,quoted> > {};

        // struct sc_name : plus< not_one< '\n' >, at<one<'('>> > {};

        // struct sc_name : plus<not_one<'\n','('>> {};

        // struct argument: plus< identifier > {};
        // struct array : seq< one<'['>, any ,one<']'> > {};
        // struct structure : seq< one<'{'>, any ,one<'}'> > {};
        // struct quoted : seq< one<'"'>, star<any>, one<'"'>> {};
        // struct expr : seq< identifier, one<'='>, sor<argument, structure, array, quoted>> {};

        // struct arguments : plus< opt<plus<space>>, sor<quoted, structure, expr, array, argument>, one<',', ')', '}', ']'>, opt<plus<space>> > {};

        // struct return_val : plus< not_one< '\n', ' ' > > {};
        // struct other : until< eol > {};

        // struct system_call : if_must<sc_name, one < '(' >, opt<arguments>, opt<plus<spac>eme>, one < ')' >, opt<plus<space>>, one < '=' >, opt<plus<space>>, return_val, other > {};

        // struct exit_num : plus<digit> {};
        // struct exit_line : if_must< istring<'+', '+', '+'>, plus<space>, plus<sor<alpha, space>>, exit_num, istring<'+', '+', '+'> > {};

        // struct comment : if_must< one< '#' >, until< eol > > {};
        // struct empty_line : if_must< plus< sor< space, eol > > > {};
        // struct nothing : sor< empty_line, comment > {};

        // struct anything : sor< nothing, exit_line, system_call > {};
        // struct grammar : must< until<eof, anything> > {};

        struct str_hexprefix : TAOCPP_PEGTL_STRING("0x") {};
        struct str_unfinished : TAOCPP_PEGTL_STRING("<unfinished ...>") {};
        struct str_sigprefix : TAOCPP_PEGTL_STRING("+++") {};
        struct str_killprefix : TAOCPP_PEGTL_STRING("---") {};
        struct str_nullpointer : TAOCPP_PEGTL_STRING("NULL") {};
        struct str_ellipsis : TAOCPP_PEGTL_STRING("...") {};
        struct integer : seq<opt<one<'-'>>, plus<ascii::digit>> {};
        struct pointer : seq<str_hexprefix, plus<ascii::xdigit>> {};
        struct hexbyte : if_must<one<'x'>, xdigit, xdigit> {};
        struct decbyte : if_must<digit, rep_opt<2, digit>> {};
        struct single : one<'a', 'b', 'f', 'n', 'r', 't', 'v', '\\', '"', '\'', '0', '\n'> {};
        struct character_escaped : if_must<one<'\\'>, sor<hexbyte, decbyte, single>> {};
        struct character_regular : not_one<'\r', '\n'> {};
        struct character : sor<character_escaped, character_regular> {};
        struct string : seq<if_must<one<'"'>, until<one<'"'>, character>>, opt<str_ellipsis>> {};
        struct constant : seq<ranges<'A', 'Z', '_'>, star<ranges<'A', 'Z', '0', '9', '_'>>> {};
        struct constants : list_must<constant, one<'|'>> {};

        template<char open_char, char close_char>
        struct container {
            using analyze_t = analysis::generic<analysis::rule_type::ANY>;

            template<typename Input>
            static bool match(Input& in) {
                std::cout << "iterator:'" << in.iterator().data << '\'' << std::endl;

                if (in.size() >= 2) {
                    if (in.iterator().data[0] == open_char) {
                        int level;
                        size_t i;

                        for (i = 1, level = 1; i < in.size() && level > 0; ++i) {
                            switch (in.iterator().data[i]) {
                            case open_char:
                                ++level;
                                break;

                            case close_char:
                                --level;
                                break;
                            }
                        }

                        if (level == 0) {
                            in.bump(i);
                            return true;
                        }
                    }
                }

                return false;
            }
        };

        struct array : seq<opt<one<'~'>>, container<'[', ']'>> {};
        struct structure : container<'{', '}'> {};
        struct value : sor<pointer, integer, string, constants, array, structure> {};
        struct key_value : seq<ascii::identifier, one<'='>, value> {};
        struct argument : sor<value, key_value, at<str_unfinished>> {};
        struct rest : star<ascii::any> {};
        struct return_value : seq<sor<pointer, integer, one<'?'>>, opt<ascii::space, rest>> {};
        struct syscall_args : opt<list<argument, one<','>, ascii::space>> {};
        struct syscall_return : pad<one<'='>, ascii::space> {};
        struct syscall_full : seq<one<')'>, syscall_return, return_value> {};
        struct syscall_unfinished : pad<str_unfinished, ascii::space> {};
        struct syscall_end : sor<syscall_full, syscall_unfinished> {};
        struct syscall_name : ascii::identifier {};
        struct syscall_start : seq<syscall_name, one<'('>, syscall_args> {};
        struct syscall_line : seq<syscall_start, syscall_end> {};


        struct signal_line : seq<str_sigprefix, plus<ascii::any>> {};
        struct killed_line : seq<str_killprefix, plus<ascii::any>> {};
        struct ignored_line : sor<signal_line, killed_line> {};

        struct strace_line : sor<syscall_line, ignored_line> {};
        struct grammar : until<eof, must<strace_line>> {};

        template< typename Rule >
        struct action : tao::TAOCPP_PEGTL_NAMESPACE::nothing< Rule > {};

        template<>
        struct action< syscall_name > {
            template < typename Input >
            static void apply(const Input& in, st2se::Ids& out) {
                (void) out;
                std::cout << "syscall_name: " << in.string() << std::endl;
            }
        };

        template<>
        struct action< structure > {
            template < typename Input >
            static void apply(const Input& in, st2se::Ids& out) {
                (void) out;
                std::cout << "structure: " << in.string() << std::endl;
            }
        };

        template<>
        struct action< array > {
            template < typename Input >
            static void apply(const Input& in, st2se::Ids& out) {
                (void) out;
                std::cout << "array: " << in.string() << std::endl;
            }
        };

        template<>
        struct action< argument > {
            template < typename Input >
            static void apply(const Input& in, st2se::Ids& out) {
                (void) out;
                std::cout << "argument: " << in.string() << std::endl;
            }
        };

        template<>
        struct action< value > {
            template < typename Input >
            static void apply(const Input& in, st2se::Ids& out) {
                (void) out;
                std::cout << "value: " << in.string() << std::endl;
            }
        };

        template<>
        struct action< key_value > {
            template < typename Input >
            static void apply(const Input& in, st2se::Ids& out) {
                (void) out;
                std::cout << "key_value: " << in.string() << std::endl;
            }
        };

        // template<>
        // struct action< one  > {
        //  template < typename Input >
        //  static void apply(const Input& in, st2se::Ids & out )
        //  {
        //      (void) out;
        //      std::cout << "one: " << in.string() << std::endl;
        //  }
        // };

    }


}

#endif