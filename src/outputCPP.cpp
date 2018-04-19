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

        while (getline(template_file_begin, line)) {
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

        for (const auto &item : ids.data) {
            generateScRules(item);
        }

        output_source << "asdg" << std::endl;

        writeLastPart();
        std::cout << "last part" << std::endl;

    }

    void outputCPP::generateScRules(std::pair<std::string, Syscall_t> sc) {
        const unsigned pos_num = 0;

        // it's writen this way for better readabilty

        if (sc.second.clustered == true) {
            std::cout << "clustered branch" << std::endl;

            for (auto &pos : sc.second.next) {
                generateClusterRules(pos, pos_num);
            }
        }
        else {
            for (auto &argument : sc.second.next) {
                generateRules(argument, pos_num, /*clustered =*/ false);
            }
        }
    }

    void outputCPP::generateClusterRules(argument_t arg, const unsigned pos) {

        // iterate over clusters
        for (auto cluster : arg.next) {
            generateRules(cluster, pos, /*clustered =*/ true);
        }

    }

    void outputCPP::generateRules(argument_t arg, const unsigned pos, const bool clustered) {

        if (clustered) {

            // get minmax
            auto minmax = getMinMax(arg);

            if (minmax.empty()) {
                return;
            }

            // std::cout << arg2str(minmax.first) << " " << arg2str(minmax.second) << std::endl;
            // print minmax
            if (minmax.size() == 1) {
                writeValue(minmax.front());
            }
            else {
                writeValue(minmax);
            }

            // recursive descent
            if (!arg.next.empty()) {
                if (!arg.next.front().next.empty()) {
                    generateRules(arg.next.front(), pos + 1, clustered);
                }
                else {
                    // std::cout << "first not empty and second one is" << std::endl;
                    return;
                }
            }
            else {
                // std::cout << "first and second empty" << std::endl;
                return;
            }
        }
        else {
            // TODO maybe smarter way with backtracking?

            // print arg as rule
            writeValue(arg);

            // recursive descent over IDS
            for (auto x : arg.next) {
                generateRules(x, pos + 1, clustered);
            }
        }

    }

    std::vector<argument_t> outputCPP::getMinMax(argument_t &arg) {


        std::vector<argument_t> vec {arg.next.begin(), arg.next.end()};
        vec.push_back(arg);

        std::vector<argument_t> ret_val {};

        std::sort(vec.begin(), vec.end());

        if (vec.size() > 1) {
            ret_val.push_back(vec.front());
            ret_val.push_back(vec.back());
        }
        else if (vec.size() == 1) {
            ret_val.push_back(vec.front());
        }

        return ret_val;
    }

    void outputCPP::writeValue(minmax_t &range) {
        std::cout << "TODO: print as rule: range:\t" << arg2str(range.front()) << " " << arg2str(range.back()) << std::endl;
        return;
    }
    void outputCPP::writeValue(argument_t &arg) {
        std::cout << "TODO: print as rule: val:\t" << arg2str(arg) << std::endl;
        return;
    }


} // namespace st2se