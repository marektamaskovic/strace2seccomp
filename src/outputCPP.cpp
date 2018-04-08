#include "outputCPP.hpp"

namespace st2se {

    void outputCPP::openFiles() {
        // FIXME use only onde dot
        template_file.open(template_file_path, std::ios::in);
        output_source.open(output_source_path, std::ios_base::out | std::ios_base::trunc);

        if (!template_file.is_open()) {
            throw (std::runtime_error("template_file is not open"));
        }

        if (!output_source.is_open()) {
            throw (std::runtime_error("output_source is not open"));
        }
    }


    void outputCPP::writeFirstPart() {
        std::string line;

        for (int i = 0; i < first_part_size; ++i) {
            getline(template_file, line);
            std::cout << line.size() << std::endl;
            output_source << line << std::endl;
        }
    }

    void outputCPP::writeLastPart() {
        std::string line;

        // print the end of the  template.c
        while (getline(template_file, line)) {
            output_source << line << std::endl;
        }
    }

    void outputCPP::generate(Ids &ids) {

        openFiles();

        writeFirstPart();
        std::cout << "First part" << std::endl;

        // for(const auto &item : ids.data){
        //  (void) item;
        //  ;
        // }

        output_source << "asdg" << std::endl;

        writeLastPart();
        std::cout << "last part" << std::endl;

    }

} // namespace st2se