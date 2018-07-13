#ifndef _SRC_STRACEPARSER_HPP
#define _SRC_STRACEPARSER_HPP

#include <fstream>
#include <iostream>
#include <map>
#include <string>

#include "tao/pegtl.hpp"
#include "tao/pegtl/contrib/tracer.hpp"
#include "tao/pegtl/analyze.hpp"

#include "straceparser_actions.hpp"
#include "ids.hpp"


namespace st2se {

    class StraceParser {
        std::string filename {""};
        Ids &output;
        States states();

      public:
        explicit StraceParser(st2se::Ids &_output);
        StraceParser(std::string &_filename, st2se::Ids &_output);
        // ~StraceParser();

        bool parse(const std::string &_filename, st2se::Ids &_output, Params &params, States &states);

        std::string getFilename();
        std::size_t AnalyzeGrammar();

    };

} // namespace st2se

#endif
