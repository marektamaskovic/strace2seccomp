#include "outputCPP.hpp"

namespace st2se {

    void outputCPP::openFiles() {
        template_file_begin.open(template_file_b_path, std::ios::in);
        template_file_end.open(template_file_e_path, std::ios::in);
        template_file_thread.open(template_file_t_path, std::ios::in);
        output_source.open(output_source_path, std::ios_base::out | std::ios_base::trunc);

        if (!template_file_begin.is_open()) {
            throw (std::runtime_error("template_file_begin is not open"));
        }

        if (!template_file_end.is_open()) {
            throw (std::runtime_error("template_file_end is not open"));
        }

        if (!template_file_thread.is_open()) {
            throw (std::runtime_error("template_file_thread is not open"));
        }

        if (!output_source.is_open()) {
            throw (std::runtime_error("output_source is not open"));
        }
    }

    void outputCPP::closeFiles() {
        template_file_begin.close();
        template_file_end.close();
        template_file_thread.close();
        output_source.close();
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

    void outputCPP::writeThreadPart() {
        std::string line;

        while (getline(template_file_thread, line)) {
            output_source << line << std::endl;
        }
    }

    void outputCPP::setOutput(std::string o){
        output_source_path = o;
    }


    void outputCPP::generate(Ids &ids) {

        openFiles();

        if(genProlog)
            writeFirstPart();

        if(genThreading)
            writeThreadPart();

        ids.print();

        for (const auto &item : ids.data) {
            generateScRules(item);
        }

        if(genProlog)
            writeLastPart();

        closeFiles();

    }

    void outputCPP::generateScRules(std::pair<std::string, Syscall_t> sc_pair) {

        unsigned pos_num = 0;
        Syscall_t &sc = sc_pair.second;

        // Write zero when no arguments provided.
        writeZero = true;

        // it's writen this way for better readabilty

        writeSC(sc, 1);

        // TODO add param for syscall without args

        if (sc.clustered) {
            std::cout << "clustered branch" << std::endl;

            if (!sc.next.empty()) {
                for (auto &pos : sc.next) {
                    // TODO Find out  why this works ?
                    generateRules(pos, pos_num++, /*clustered =*/ true);
                }
            }
        }
        else {
            if (!sc.next.empty()) {
                for (auto &argument : sc.next) {
                    generateRules(argument, pos_num, /*clustered =*/ false);
                }
            }
        }

        writeClosingBracket();
    }

    void outputCPP::generateRules(argument_t arg, const unsigned pos, const bool clustered) {

        argument_t &cluster = arg;

        if (clustered) {

            // get minmax
            auto minmax = getMinMax(cluster);

            // std::cout << "\n\n\n\n" << arg2str(cluster) << " ." << cluster.next.size() << std::endl;
            // FIXME
            if (minmax.empty()) {
                return;
            }

            // std::cout << arg2str(minmax.first) << " " << arg2str(minmax.second) << std::endl;
            // print minmax
            std::cout << "minmax.size():" << minmax.size() << std::endl;

            // ENHANCEMENT add here param switch when program is running without ASLR
            if (isPointer(minmax)) {
                return;
            }

            if (minmax.size() == 1) {
                writeValue(minmax.front(), pos);
            }
            else {
                writeValue(minmax, pos);
            }

            // recursive descent
            if (!cluster.next.empty()) {
                if (!cluster.next.front().next.empty()) {
                    generateRules(cluster.next.front(), pos, clustered);
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
            // print arg as rule
            writeValue(arg, pos);

            // recursive descent over IDS
            for (auto x : arg.next) {
                generateRules(x, pos + 1, clustered);
            }
        }

    }

    std::vector<argument_t> outputCPP::getMinMax(argument_t &arg) {


        std::vector<argument_t> vec;

        if (!arg.next.empty()) {
            for (auto item : arg.next) {
                vec.push_back(item);
            }
        }

        // vec.push_back(arg);

        // std::cout << "arg.next.size()" << arg.next.size() << std::endl;

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

    void outputCPP::writeValue(minmax_t &range, unsigned pos) {

        // if(writeZero){
        //     output_source << std::endl;
        // }

        std::cout << range.back().value_type << std::endl;

        if (range.back().value_type == val_type_t::BITFIELD) {
            std::cout << "skiping bitfield" << std::endl;
            return;
        }

        writeZero = false;

        // std::cout << "TODO: print as rule: range:\t" << arg2str(range.front()) << " " << arg2str(range.back()) << std::endl;

        output_source << "," << std::endl;
        output_source << "        ";  // indentation 8 spaces
        output_source << "SCMP_A";
        output_source << pos;
        output_source << "(SCMP_CMP_IN_RANGE, ";
        output_source << arg2str(range.front());
        output_source << ", ";
        output_source << arg2str(range.back());
        output_source << ")";

        // output_source << std::endl;

        return;
    }
    void outputCPP::writeValue(argument_t &arg, unsigned pos) {

        // if(writeZero){
        //     output_source << std::endl;
        // }
        if (arg2str(arg).length() == 0) {
            return;
        }

        std::cout << arg.value_type << std::endl;

        if (arg.value_type == val_type_t::BITFIELD) {
            std::cout << "skiping bitfield" << std::endl;
            return;
        }

        writeZero = false;

        // std::cout << "TODO: print as rule: val:\t" << arg2str(arg) << std::endl;

        output_source << "," << std::endl;
        output_source << "        ";  // indentation 8 spaces
        output_source << "SCMP_A";
        output_source << pos;
        output_source << "(SCMP_CMP_EQ, ";
        output_source << arg2str(arg);
        output_source << ")";
        // output_source << std::endl;


        return;
    }

    void outputCPP::writeSC(Syscall_t &sc, unsigned tab_len) {

        for (unsigned i = 0; i < tab_len; ++i) {
            output_source << "    ";
        }

        output_source << "ret |= seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(";
        output_source << sc.name;
        output_source << "), ";
        output_source << sc.arg_num;

        return;
    }
    void outputCPP::writeClosingBracket() {

        if (writeZero) {
            output_source << ");" << std::endl;
            return;
        }

        output_source << std::endl;
        output_source << "    ";
        output_source << ");" << std::endl;
        return;
    }

    bool outputCPP::isPointer(minmax_t minmax) {

        if (minmax.size() == 1) {
            return minmax.front().value_type == val_type_t::POINTER ? true : false;
        }
        else {
            if (minmax.front().value_type == val_type_t::POINTER ||
                minmax.back().value_type == val_type_t::POINTER) {
                return true;
            }

            return false;

        }

    }



} // namespace st2se