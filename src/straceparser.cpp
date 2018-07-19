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

#include "straceparser.hpp"

int syscalls = 0;
static int good_lines {0};
static int bad_lines {0};

namespace st2se {

    StraceParser::StraceParser(st2se::Ids &_output) : output(_output) {
    }

    StraceParser::StraceParser(std::string &_filename, st2se::Ids &_output):
        filename(_filename), output(_output) {
    }

    std::string StraceParser::getFilename() {
        return this->filename;
    }

    bool StraceParser::parse(const std::string &_filename, st2se::Ids &_output, Params &params, States &states) {

        unsigned long long linesCount = countLines(_filename);
        unsigned long long position {0};
        std::fstream input_file {_filename, std::ios_base::in};
        std::vector<std::string> bad_lines_str {};

        // iterate over lines in file
        for (std::string line; std::getline(input_file, line); position++) {

            // show progress
            if (params.showProgress) {
                fmt::print("\r Parsed: {0}/{1} lines", position, linesCount);
            }

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

            // increment statistics
            if (return_val) {
                good_lines++;
            }
            else {
                bad_lines++;
                bad_lines_str.push_back(line);
            }
        }

        // if there are some lines that cannot be parsed
        // then they will be stored in unpersed_lines file
        if (!bad_lines_str.empty()) {
            std::ofstream unparsed_lines {"unparsed_lines.st2se", std::ios_base::out | std::ios_base::trunc};

            for (const auto &line : bad_lines_str) {
                unparsed_lines << line << std::endl;
            }
        }

        // print statistics
        std::cout << "statistics: + " << good_lines << " - " << bad_lines << std::endl;
        return true;
    }

    std::size_t StraceParser::AnalyzeGrammar() {
        return tao::pegtl::analyze< st2se::grammar::strace_line >();
    }


} // namespace st2se

unsigned long long countLines(std::string filename) {

    unsigned long long ret {0};
    std::fstream input_file {filename, std::ios_base::in};

    for (std::string line; std::getline(input_file, line); ret++);

    input_file.close();
    return ret;
}
