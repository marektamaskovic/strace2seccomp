// Copyright (c) 2018 Red Hat <mtamasko@redhat.com>
// Author: Marek Tamaskovic <tamaskovic.marek@gmail.com>
//
// This file is part of strace2seccomp tool.
//
// strace2seccomp tool is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// strace2seccomp tool is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with strace2seccomp tool.  If not, see <https://www.gnu.org/licenses/>.

/**
 * @file straceparser_grammar.hpp
 * @brief Parser Grammar
 */
#ifndef _SRC_STRACEPARSER_GRAMMAR
#define _SRC_STRACEPARSER_GRAMMAR

namespace st2se{
    namespace grammar {

        using namespace tao::pegtl;

        struct str_hexprefix : TAOCPP_PEGTL_STRING("0x") {};
        struct exit_line_prefix : seq<one<'+'>, one<'+'>, one<'+'>> {};
        struct exit_line_suffix : seq<one<'+'>, one<'+'>, one<'+'>> {};
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
            static bool match(Input &in) {

                #ifdef MATCH_DEBUG
                // BULLSHIT AHEAD
                std::cout << "current:'" << std::string(in.current()).substr(0, in.size()) << '\'' << std::endl;
                std::cout << "size:" << in.size() << std::endl;
                #endif

                if (in.size() >= 2) {
                    if (in.current()[0] == open_char) {
                        int level;
                        size_t i;

                        for (i = 1, level = 1; i < in.size() && level > 0; ++i) {
                            switch (in.current()[i]) {
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

        struct comment_start : seq<one<'/'>, one<'*'>> {};
        struct comment_end : seq<one<'*'>, one<'/'>> {};
        struct comment_body : until<comment_end> {};
        struct inline_comment : seq< comment_start, comment_body> {};

        struct array : seq<opt<one<'~'>>, container<'[', ']'>> {};
        struct structure : container<'{', '}'> {};
        struct value : sor<pointer, str_nullpointer, integer, string, constants, array, structure> {};
        struct key_value : seq<ascii::identifier, one<'='>, value> {};
        struct argument : seq<sor<value, key_value, inline_comment, at<str_unfinished>>, star<space>, opt<inline_comment>> {};
        struct rest : star<ascii::any> {};
        struct return_value : seq<sor<pointer, integer, one<'?'>>, opt<until<eol>>> {};
        struct syscall_args : opt<list<argument, one<','>, ascii::space>> {};
        struct syscall_return : pad<one<'='>, ascii::space> {};
        struct syscall_full : seq<one<')'>, syscall_return, return_value> {};
        struct syscall_unfinished : pad<str_unfinished, ascii::space> {};
        struct syscall_end : sor<syscall_full, syscall_unfinished> {};
        struct syscall_name : ascii::identifier {};
        struct syscall_start : seq<syscall_name, one<'('>, syscall_args> {};
        struct syscall_line : seq<syscall_start, syscall_end> {};

        struct signal_line : seq<str_sigprefix> {};
        struct killed_line : seq<str_killprefix> {};
        struct exit_line : seq<exit_line_prefix, until<exit_line_suffix, any>> {};
        struct ignored_line : seq<sor</*signal_line, killed_line,*/ exit_line>, opt<until<eol>>> {};

        struct strace_line : sor<syscall_line, ignored_line> {};
        struct grammar : until<eof, must<strace_line>> {};

    } // namespace grammar
} // namespace st2se

#endif
