#ifndef SRC_OUTPUTCPP_HPP
#define SRC_OUTPUTCPP_HPP

#include <fstream>
#include <iostream>
#include <vector>
#include <optional>

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

        void openFiles();
        void writeFirstPart();
        void writeThreadPart();
        void writeLastPart();
        void closeFiles();

        bool writeZero = true;

      public:
        outputCPP() = default;


        virtual void generate(Ids &ids);
        void generateScRules(std::pair<std::string, Syscall_t> sc);
        void generateClusterRules(argument_t pos, const unsigned pos_num);
        void generateRules(Syscall_t &sc, argument_t arg, const unsigned pos, const bool clustered);

        std::vector<argument_t> getMinMax(argument_t &arg);

        void writeValue(minmax_t &range, unsigned pos);
        void writeValue(argument_t &arg, unsigned pos, int op);

        void writeSC(Syscall_t &sc, unsigned tab_len);
        void writeClosingBracket();
        bool isPointer(minmax_t minmax);
    };

} // namespace st2se

#endif