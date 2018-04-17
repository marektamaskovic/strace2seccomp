#ifndef SRC_OUTPUTCPP_HPP
#define SRC_OUTPUTCPP_HPP

#include <fstream>
#include <iostream>
#include <vector>

#include "output.hpp"
#include "ids.hpp"

namespace st2se {

    class outputCPP : public Output {

        std::ifstream template_file_begin;
        std::ifstream template_file_end;
        std::ofstream output_source;
        
        std::string template_file_b_path = "../seccomp_template/template.c.begin";
        std::string template_file_e_path = "../seccomp_template/template.c.end";
        std::string output_source_path = "./source.cpp";

        void openFiles();
        void writeFirstPart();
        void writeLastPart();

      public:
        outputCPP() = default;


        virtual void generate(Ids &ids);
    };

} // namespace st2se

#endif