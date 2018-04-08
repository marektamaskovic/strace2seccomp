#include "straceparser.hpp"

int syscalls = 0;
static int good_lines {0};
static int bad_lines {0};

namespace st2se {

    StraceParser::StraceParser(st2se::Ids &_output) : output(_output) {
    }

    StraceParser::StraceParser(const std::string &_filename, st2se::Ids &_output):
        filename(_filename), output(_output) {
    }

    std::string StraceParser::getFilename() {
        return this->filename;
    }

    bool StraceParser::parse(const std::string &_filename, st2se::Ids &_output, Params &params, States &states) {

        std::fstream input_file {_filename, std::ios_base::in};

        std::vector<std::string> bad_lines_str {};

        for (std::string line; std::getline(input_file, line);) {

            tao::pegtl::string_input<> in (line, _filename);
            bool return_val;

            try {
                if (params.tracing) {
                    return_val = tao::pegtl::parse<st2se::grammar::strace_line, st2se::grammar::action, tao::pegtl::tracer>(in, _output, params,
                            states);
                }
                else {
                    return_val = tao::pegtl::parse<st2se::grammar::strace_line, st2se::grammar::action>(in, _output, params, states);
                }
            }
            catch (tao::pegtl::parse_error &e) {
                std::cout << e.what() << std::endl;
                std::cout << "'" << line << "'" << std::endl;
                return_val = false;
            }

            if (return_val) {
                good_lines++;
            }
            else {
                bad_lines++;
                bad_lines_str.push_back(line);
            }
        }

        if (!bad_lines_str.empty()) {
            std::ofstream unparsed_lines {"unparsed_lines.st2se", std::ios_base::out | std::ios_base::trunc};

            for (const auto &line : bad_lines_str) {
                unparsed_lines << line << std::endl;
            }
        }

        std::cout << "statistics: + " << good_lines << " - " << bad_lines << std::endl;
        std::cout << "sc:" << ::syscalls << std::endl;
        return true;
    }

    std::size_t StraceParser::AnalyzeGrammar() {
        return tao::pegtl::analyze< st2se::grammar::strace_line >();
    }
} // namespace st2se
