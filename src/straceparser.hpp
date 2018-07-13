/**
 * @file straceparser.hpp
 * @brief Parser declarations
 */
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

    /**
     * Class that parses the input files and stores output in IDS
     */
    class StraceParser {
        std::string filename {""}; /**< input filename*/
        Ids &output; /**< output IDS*/
        States states(); /**< Parser inner states */

      public:
        /**
         * Constructor
         * @param _output an IDS in which will be stored output
         */
        explicit StraceParser(st2se::Ids &_output);
        /**
         * Constructor
         * @param _filename an input filename
         * @param _output an IDS in which will be stored output
         */
        StraceParser(std::string &_filename, st2se::Ids &_output);
        // ~StraceParser();

        /**
         * Parse method
         * @param _filename an input filename
         * @param _output an output IDS
         * @param _params switches from runtime arguments
         * @param _states inner states of parser
         * @return bool true on success, false otherwise
         */
        bool parse(const std::string &_filename, st2se::Ids &_output, Params &params, States &states);

        /**
         * Getter
         * Get filename
         * @return string filename
         */
        std::string getFilename();

        /**
         * Grammar analyzer
         * Run analysis on parser grammar
         * @return std::size_t number of errors in grammar
         */
        std::size_t AnalyzeGrammar();

    };

} // namespace st2se

#endif
