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

    unsigned outputCPP::getPrintable(argument_t & arg) {
        unsigned cnt {0};

        if(!arg.next.empty()) {
            for(auto &item : arg.next) {
                cnt += getPrintable(item);
            }
        }

        switch(arg.value_type) {
            case val_type_t::INTEGER:
            case val_type_t::CONSTANT:
            case val_type_t::BITFIELD:
                cnt++;
            default:
                break;
        }

        return cnt;
    }

    void outputCPP::generateScRules(std::pair<std::string, Syscall_t> sc_pair) {

        unsigned pos_num = 0;
        Syscall_t &sc = sc_pair.second;

        // Write zero when no arguments provided.
        writeZero = true;

        if (sc.clustered) { // clustered branch
            writeSC(sc);

            if (!sc.next.empty()) {
                for (auto &pos : sc.next) {
                    generateRules(pos, pos_num++, /*clustered =*/ true);
                }
            }

            writeClosingBracket();
        }
        else {  // unclustered branch
            std::string prefix {sc2str(sc)};

            if (!sc.next.empty()) {
                for (argument_t &argument : sc.next) {
                    generateRules(argument, pos_num, /*clustered =*/ false, prefix);
                }
            }

            writeString();
        }

    }

    void outputCPP::generateRules(argument_t cluster, const unsigned pos, const bool clustered) {

        if (clustered) {

            // get minmax
            auto minmax = getMinMax(cluster);

            if (minmax.empty()) {
                return;
            }

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
                    generateRules(cluster.next.front(), pos + 1, clustered);
                }
            }
        }
        else {
            std::cerr << "Error expected clustered argument" << std::endl;
        }
    }

    void outputCPP::generateRules(argument_t &arg, const unsigned pos, const bool clustered, std::string prefix) {
        std::string buffer {prefix};
        std::string s4 {"    "}; // four spaces

        switch(arg.value_type){
            case val_type_t::INTEGER:
                if (genProlog) {
                    buffer += s4;
                    s4 += s4;
                }

                buffer +=
                    fmt::format(",\n{0}SCMP_A{1}(SCMP_CMP_EQ, {2}u)",
                        s4,
                        std::to_string(pos),
                        arg2str(arg)
                    );
                break;
            case val_type_t::BITFIELD:
            case val_type_t::CONSTANT:
                if (genProlog) {
                    buffer += s4;
                    s4 += s4;
                }

                buffer +=
                    fmt::format(",\n{0}SCMP_A{1}(SCMP_CMP_MASKED_EQ, {2}, 1)",
                        s4,
                        std::to_string(pos),
                        arg2str(arg)
                    );
                break;
            default:
                break;
        }

        if (!arg.next.empty()) {
            for (auto &item : arg.next) {
                generateRules(item, pos + 1, clustered, buffer);
            }
        }
        else {
            if (prefix.back() != '0') {
                buffer += "\n";
            }

            if (genProlog) {
                buffer += s4;
            }

            buffer += ");";
            storeString(buffer);
        }
    }

    inline void outputCPP::storeString(std::string &str) {
        batch.push_back(str);
    }

    inline void outputCPP::writeString() {

        std::sort(batch.begin(), batch.end());
        std::vector<std::string>::iterator end = std::unique(batch.begin(), batch.end());
        batch.erase(end, batch.end());

        for(auto &item : batch) {
            output_source << item << std::endl;
        }

        batch.clear();

        // output_source << str << std::endl;
    }

    std::vector<argument_t> outputCPP::getMinMax(argument_t &arg) {


        std::vector<argument_t> vec;

        if (!arg.next.empty()) {
            for (auto item : arg.next) {
                vec.push_back(item);
            }
        }

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
        writeZero = false;

        std::string indent {"        "};  // 8 spaces
        std::string output {""};

        switch(range.back().value_type){
            case val_type_t::BITFIELD:
                output = fmt::format(
                    ",\n{0}SCMP_A{1}(SCMP_CMP_MASKED_EQ, -1u, -1u)",
                    indent,
                    pos
                );
                break;
            case val_type_t::CONSTANT:
                output = fmt::format(
                    ",\n{0}SCMP_A{1}(SCMP_CMP_MASKED_EQ, -1u, -1u)",
                    indent,
                    pos
                );
                break;
            default:
                output = fmt::format(
                    ",\n{0}SCMP_A{1}(SCMP_CMP_IN_RANGE, {2}u, {3}u)",
                    indent,
                    pos,
                    arg2str(range.front()),
                    arg2str(range.back())
                );
                break;
        }

        output_source << output;

        return;
    }

    void outputCPP::writeValue(argument_t &arg, unsigned pos) {

        if (arg2str(arg).length() == 0) {
            return;
        }

        writeZero = false;
        std::string indent {"        "};  // 8 spaces

        output_source << fmt::format(",\n{0}SCMP_A{1}", indent, pos);

        if (arg.value_type == val_type_t::BITFIELD) {
            output_source << fmt::format(
                "(SCMP_CMP_MASKED_EQ, {0}, -1u)",
                arg2str(arg)
            );
        }
        else if (arg.value_type == val_type_t::CONSTANT) {
            output_source << fmt::format(
                "(SCMP_CMP_MASKED_EQ, {0}, 1)",
                arg2str(arg)
            );
        }
        else {
            output_source << fmt::format("(SCMP_CMP_EQ, {0}u)", arg2str(arg));
        }

        return;
    }

    std::string outputCPP::sc2str(Syscall_t &sc) {

        std::string buffer {""};

        if (genProlog) { // if genProlog we need to indent rules
            output_source << "    ";
        }

        unsigned cnt = rulesCount(sc, sc.clustered);

        buffer += fmt::format("ret |= seccomp_rule_add(ctx, SCMP_ACT_ALLOW, "
                "SCMP_SYS({0}), {1}", sc.name, std::to_string(cnt));

        return buffer;
    }

    void outputCPP::writeSC(Syscall_t &sc) {

        if (genProlog) { // if genProlog we need to indent rules
            output_source << "    ";
        }

        output_source << fmt::format("ret |= seccomp_rule_add(ctx, "
                "SCMP_ACT_ALLOW, SCMP_SYS({0}), {1}", sc.name,
                rulesCount(sc, sc.clustered)
            );

        return;
    }

    void outputCPP::writeClosingBracket() {
        if (writeZero) {
            output_source << ");" << std::endl;
        }
        else{
            output_source << fmt::format("\n    );\n");
        }
        return;
    }

    bool outputCPP::isPointer(const minmax_t minmax) {

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

    unsigned outputCPP::rulesCount(const Syscall_t &sc, const bool clustered) {

        if (clustered) {
            unsigned cnt {0};

            for (auto item : sc.next) {
                if(!item.next.empty()){
                    cnt++;
                }
            }
            return cnt;
        }
        else {
            unsigned cnt {0};

            if (sc.next.empty()) {
                return cnt;
            }

            argument_t arg = sc.next.front();

            while (!arg.next.empty()) {
                switch (arg.value_type) {
                    case val_type_t::INTEGER :
                    case val_type_t::CONSTANT :
                    case val_type_t::BITFIELD :
                        break;

                    default:
                        argument_t tmp {arg.next.front()};
                        arg = tmp;
                        continue;
                }

                cnt++;
                argument_t tmp {arg.next.front()};
                arg = tmp;
            }

            return cnt;
        }

        return 0;
    }

} // namespace st2se
