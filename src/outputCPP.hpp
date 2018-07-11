#ifndef SRC_OUTPUTCPP_HPP
#define SRC_OUTPUTCPP_HPP

#include <fstream>
#include <iostream>
#include <vector>
#include <optional>
#include <string>
#include <variant>

#include "fmt/core.h"
#include "fmt/format.h"

#include "output.hpp"
#include "ids.hpp"

namespace st2se {

    using minmax_t = std::vector<argument_t>;

    class outputCPP : public Output {

        std::ifstream template_file_begin;
        std::ifstream template_file_end;
        std::ifstream template_file_thread;
        std::ofstream output_source;

        std::string template_file_b_path = "../seccomp_template/template.c.begin";
        std::string template_file_e_path = "../seccomp_template/template.c.end";
        std::string template_file_t_path = "../seccomp_template/template.c.thread";
        std::string output_source_path = "./source.cpp";

        std::string rule_start {""};
        std::string indent {"    "};
        std::string opt_indent {""};
        std::vector<std::string> batch {};
        std::vector<std::string> ready2Print {};

        void writeFirstPart();
        void writeLastPart();
        void writeThreadPart();

      public:
        outputCPP() = default;

        void openFiles();
        void closeFiles();

        virtual void generate(Ids &ids);
        virtual void setOutput(std::string o);
        void generateScRules(std::pair<std::string, Syscall_t> sc);
        void generateRules(argument_t &cluster, bool clustered, unsigned pos);

        std::string getCondition(argument_t &arg, unsigned pos);

        void __genConditions(argument_t &arg, unsigned pos);
        void __genCluseteredConditions(argument_t &cluster, unsigned pos);
        std::string getClusteredCond(argument_t &cluster, unsigned pos);

        std::string getRuleProlog(Syscall_t &sc);
        void writeRule();
        void printRules();
    };

} // namespace st2se

#endif