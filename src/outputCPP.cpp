#include "outputCPP.hpp"

namespace st2se {

    void outputCPP::openFiles() {
        // FIXME use only onde dot
        template_file_begin.open(template_file_b_path, std::ios::in);
        template_file_end.open(template_file_e_path, std::ios::in);
        output_source.open(output_source_path, std::ios_base::out | std::ios_base::trunc);

        if (!template_file_begin.is_open()) {
            throw (std::runtime_error("template_file_begin is not open"));
        }

        if (!template_file_end.is_open()) {
            throw (std::runtime_error("template_file_begin is not open"));
        }

        if (!output_source.is_open()) {
            throw (std::runtime_error("output_source is not open"));
        }
    }


    void outputCPP::writeFirstPart() {
        std::string line;

        while(getline(template_file_begin, line)) {
            output_source << line << std::endl;
        }
    }

    void outputCPP::writeLastPart() {
        std::string line;

        // print the end of the  template.c
        while (getline(template_file_end, line)) {
            output_source << line << std::endl;
        }
    }

    void outputCPP::generate(Ids &ids) {

        openFiles();

        writeFirstPart();
        std::cout << "First part" << std::endl;

        std::cout << "Generator print" << std::endl;

        ids.print();

        for(const auto &item : ids.data){
            generateScRules(item);
        }

        output_source << "asdg" << std::endl;

        writeLastPart();
        std::cout << "last part" << std::endl;

    }

    void outputCPP::generateScRules(std::pair<std::string, Syscall_t> sc) {
        const unsigned pos = -1;

        for(auto argument : sc.second.next){
            
            // clustered tree is a little bit different
            if(sc.second.clustered == true){
                generateClusterRules(argument, pos);
            }
            else{
                generateRules(argument, pos + 1, /*clustered =*/ false);
            }
        }
    }

    void outputCPP::generateClusterRules(argument_t arg, const unsigned pos){

        // iterate over clusters
        for(auto cluster : arg.next){
            generateRules(cluster, pos + 1, /*clustered =*/ true);
        }

    }

    void outputCPP::generateRules(argument_t arg, const unsigned pos, const bool clustered){

        if(clustered) {
            
            // get minmax
            auto minmax = getMinMax(arg);

            // print minmax
            writeRangeValue(minmax);

            // recursive descent
            if(!arg.next.empty()){
                generateRules(arg.next.front(), pos + 1, clustered);
            }
        }
        else {
            // TODO maybe smarter way with backtracking?

            // print arg as rule
            writeValue(arg);

            // recursive descent over IDS
            for(auto x : arg.next) {
                generateRules(x, pos + 1, clustered);
            }
        }

    }

    std::pair<argument_t, argument_t> outputCPP::getMinMax(argument_t arg){
        return std::pair<argument_t, argument_t>();
    }

    void outputCPP::writeRangeValue(std::pair<argument_t, argument_t> &range) {
        return;
    }
    void outputCPP::writeValue(argument_t) {
        return;
    }


} // namespace st2se