/**
 * @file outputCPP.hpp
 * @brief Implementation of C/C++ output
 */
#ifndef SRC_OUTPUTCPP_HPP
#define SRC_OUTPUTCPP_HPP

#include <fstream>
#include <iostream>
#include <optional>
#include <string>
#include <variant>
#include <vector>

#include "fmt/core.h"
#include "fmt/format.h"

#include "ids.hpp"
#include "output.hpp"

namespace st2se {

    using minmax_t = std::vector<argument_t>;

    /**
     * Class that implements output generation into C/C++
     */
    class outputCPP : public Output {

        std::ifstream template_file_begin; /**< stream for reading template begin */
        std::ifstream template_file_end;   /**< stream for reading template end*/
        std::ifstream template_file_thread;/**< stream for reading template thread support*/
        std::ofstream output_source;       /**< stream for writing output */

        std::string template_file_b_path = "../seccomp_template/template.c.begin"; /**< input template filename */
        std::string template_file_e_path = "../seccomp_template/template.c.end";   /**< input template filename */
        std::string template_file_t_path = "../seccomp_template/template.c.thread";/**< input template filename */
        std::string output_source_path = "./source.cpp"; /**< output filename */

        std::string rule_start {""}; /**< inner variable that holds function to add rule with X syscall */
        std::string indent {"    "}; /**<  indent*/
        std::string opt_indent {""}; /**<  optional indent used when filter wrapper is toggled*/
        std::vector<std::string> batch {};       /**<  batch of rules*/
        std::vector<std::string> ready2Print {}; /**<  whole function call ready to print*/

        /**
         * Write template begin in output file
         */
        void writeFirstPart();
        /**
         * Write template end in output file
         */
         void writeLastPart();
        /**
         * Write template thread in output file
         */
         void writeThreadPart();

      public:
        /**
         * Constructor
         * default constructor
         */
        outputCPP() = default;

        /**
         * Open all files
         * can throw exception
         */
        void openFiles();
        /**
         * Close all opened files
         */
        void closeFiles();

        /**
         * Interface
         * this method will be called on optimizer startup
         * @param ids IDS to print in to output file
         */
        void generate(Ids &ids) override;
        /**
         * Interface
         * This method will change output filename
         * @param o output filename
         */
        void setOutput(std::string o) override;
        /**
         * generate Syscall rule
         * @param sc_pair that holds syscall and syscall name
         */
        void generateScRules(std::pair<std::string, Syscall_t> sc_pair);
        /**
         * Generate rule for syscall
         * @param arg an argument
         * @param clustered an bool that indicates if arg is clustered or not
         * @param pos an argument position
         */
        void generateRules(argument_t &arg, bool clustered, unsigned pos);

        /**
         * Get condition from argument
         * @param arg an argument
         * @param pos an argument postion
         * @return string an string that holds the condition
         */
        std::string getCondition(argument_t &arg, unsigned pos);

        /**
         * Get condition from unclustered argument
         * @param arg an argument
         * @param pos an argument postion
         */
        void __genConditions(argument_t &arg, unsigned pos);
        /**
         * Get condition from clustered argument
         * @param arg an argument
         * @param pos an argument postion
         */
        void __genCluseteredConditions(argument_t &cluster, unsigned pos);
        /**
         * Get condition from unclustered argument
         * @param arg an argument
         * @param pos an argument postion
         * @return string an string that holds the condition
         */
        std::string getClusteredCond(argument_t &cluster, unsigned pos);
        /**
         * Get rule prolog that consist of function call rule add
         * @param sc a syscall
         * @return string an string that holds the prolog
         */
        std::string getRuleProlog(Syscall_t &sc);

        /**
         * Write rule to buffer
         */
        void writeRule();
        /**
         * Print buffer to output
         */
        void printRules();
    };

} // namespace st2se

#endif