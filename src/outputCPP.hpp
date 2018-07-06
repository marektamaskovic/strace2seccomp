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

        void writeFirstPart();
        void writeLastPart();
        void writeThreadPart();

        bool writeZero = true;

      public:
        outputCPP() = default;

        void openFiles();
        void closeFiles();

        virtual void generate(Ids &ids);
        virtual void setOutput(std::string o);
        void generateScRules(std::pair<std::string, Syscall_t> sc);
        void generateClusterRules(argument_t pos, const unsigned pos_num);
        void generateRules(argument_t cluster, const unsigned pos, const bool clustered);
        void generateRules(argument_t &arg, const unsigned pos, const bool clustered, std::string prefix);

        std::vector<argument_t> getMinMax(argument_t &arg);

        void writeValue(minmax_t &range, unsigned pos);
        void writeValue(argument_t &arg, unsigned pos);
        void writeSC(Syscall_t &sc);
        void writeClosingBracket();
        void writeString(std::string &str);
        std::string sc2str(Syscall_t &sc);

        bool isPointer(minmax_t minmax);
        unsigned rulesCount(const Syscall_t &sc, const bool clustered);
    };

} // namespace st2se

#endif