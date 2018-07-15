// Copyright (c) 2018 Red Hat <mtamasko@redhat.com>
// Author: Marek Tamaskovic <tamaskovic.marek@gmail.com>
//
// This file is part of strace2seccomp tool.
//
// strace2seccomp tool is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// strace2seccomp tool is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with strace2seccomp tool.  If not, see <https://www.gnu.org/licenses/>.

#include "outputCPP.hpp"

namespace st2se {

    inline void outputCPP::openFiles() {
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

    inline void outputCPP::closeFiles() {
        template_file_begin.close();
        template_file_end.close();
        template_file_thread.close();
        output_source.close();
    }

    inline void outputCPP::writeFirstPart() {
        std::string line;

        while (getline(template_file_begin, line)) {
            output_source << line << std::endl;
        }
    }

    inline void outputCPP::writeLastPart() {
        std::string line;

        // print the end of the  template.c
        while (getline(template_file_end, line)) {
            output_source << line << std::endl;
        }
    }

    inline void outputCPP::writeThreadPart() {
        std::string line;

        while (getline(template_file_thread, line)) {
            output_source << line << std::endl;
        }
    }

    inline void outputCPP::setOutput(std::string o) {
        output_source_path = o;
    }


    void outputCPP::generate(Ids &ids) {

        openFiles();

        if (genProlog) {
            opt_indent = "    ";
            writeFirstPart();
        }

        if (genThreading) {
            writeThreadPart();
        }

        // ids.print();

        for (const auto &item : ids.data) {
            generateScRules(item);
        }

        if (genProlog) {
            writeLastPart();
        }

        closeFiles();

    }


    void outputCPP::generateScRules(std::pair<std::string, Syscall> sc_pair) {

        Syscall &sc = sc_pair.second;


        if (!sc.next.empty()) {
            unsigned pos {0};
            for (auto &item : sc.next) {
                rule_start = getRuleProlog(sc);
                generateRules(item, sc.clustered, pos++);
            }
            if(sc.clustered) {
                writeRule();
                batch.clear();
            }
        }

        printRules();

    }

    void outputCPP::generateRules(Argument &arg, bool clustered, unsigned pos) {
        if(!clustered) { // unclustered branch
            __genConditions(arg, /*pos=*/0);
        }
        else if(allowOnlySc) {
            return;
        }
        else { // clustered branch
            __genCluseteredConditions(arg, pos);
        }
    }

    void outputCPP::__genConditions(Argument &arg, unsigned pos) {
        std::string condition = getCondition(arg, pos);
        if(condition.compare(""))
            batch.push_back(condition);

        if(arg.next.empty()){
            writeRule();
        }
        else{
            for(auto &item : arg.next) {
                __genConditions(item, pos+1);
            }
        }

        if(condition.compare(""))
            batch.pop_back();
    }

    void outputCPP::__genCluseteredConditions(Argument &cluster, unsigned pos) {
        std::string condition = getClusteredCond(cluster, pos);
        if(condition.compare(""))
            batch.push_back(condition);
    }

    std::string outputCPP::getCondition(Argument &arg, unsigned pos) {

        if(arg.value_format == Value_format::EMPTY){
            return std::string {""};
        }

        std::string ret = fmt::format(",\n{}{}SCMP_A{}(", indent, opt_indent, pos);

        switch(arg.value_type){
            case Value_type::INTEGER:
                ret += fmt::format("SCMP_CMP_EQ, {})", arg2str(arg));
                break;
            case Value_type::CONSTANT:
                ret += fmt::format("SCMP_CMP_EQ, {})", arg2str(arg));
                break;
            case Value_type::BITFIELD:
                ret += fmt::format("SCMP_CMP_MASKED_EQ, {0}, {0}", arg2str(arg));
                break;

            default:
                ret = "";
                break;
        }
        return ret;
    }


    std::string outputCPP::getClusteredCond(Argument &cluster, unsigned pos){

        if(cluster.next.empty()){
            return std::string {""};
        }

        std::string ret = fmt::format(",\n{}{}SCMP_A{}(", indent, opt_indent, pos);

        switch(cluster.next.front().value_type){
            case Value_type::INTEGER:
                if(cluster.next.size() >= 2){
                    ret += fmt::format(
                        "SCMP_CMP_IN_RANGE, {1}u, {0}u)",
                        arg2str(cluster.next.front()),
                        arg2str(cluster.next.back())
                        );
                    break;
                }
                if(cluster.next.size() == 1){
                    ret += fmt::format(
                        "SCMP_CMP_EQ, {})",
                        arg2str(cluster.next.front())
                    );
                    break;
                }
                // if(cluster.next.size() > 2){
                //     ret += "WHOOA TOO BIG: " + std::to_string(cluster.next.size());
                // }
                break;
            case Value_type::CONSTANT:
                ret += fmt::format(
                    "SCMP_CMP_EQ, {})",
                    arg2str(cluster.next.front())
                );
                break;
            case Value_type::BITFIELD:
                ret += fmt::format(
                    "SCMP_CMP_MASKED_EQ, {0}, {0})",
                    arg2str(cluster.next.front())
                );
                break;
            default:
                ret = "";
                break;
        }

        return ret;
    }

    std::string outputCPP::getRuleProlog(Syscall &sc){
        std::string ret {""};

        ret = fmt::format(
            "{0}ret |= seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS({1})",
            opt_indent,
            sc.name
        );

        return ret;
    }

    void outputCPP::writeRule() {

        std::string buffer {""};

        buffer += fmt::format("{0}, {1}", rule_start, batch.size());

        if(!batch.empty()) {
            for(auto &item : batch) {
                buffer += fmt::format("{}", item);
            }
            buffer += fmt::format("\n{0});\n", opt_indent);
        }
        else{
            buffer += fmt::format(");\n");
        }

        ready2Print.push_back(buffer);
    }

    void outputCPP::printRules() {

        std::sort(ready2Print.begin(), ready2Print.end());
        auto end = std::unique(ready2Print.begin(), ready2Print.end());
        ready2Print.erase(end, ready2Print.end());

        for(auto &item : ready2Print)
            output_source << item;

        ready2Print.clear();

    }


} // namespace st2se
