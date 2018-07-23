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

#include "algorithm_weak.hpp"

#define checkVecEndsForType(vec, type) \
    (((vec).front().valueType == type) && ((vec).back().valueType == type))


namespace st2se {

    std::vector<std::string> string_to_vector(std::string str, char delimeter) {
        std::vector<std::string> strings;
        if (str.empty()) {
            return strings;
        }

        std::stringstream list_str{str};
        std::string s;

        while (std::getline(list_str, s, delimeter)) {
            strings.push_back(s);
        }

        return strings;
    }

    bool Algo_weak::optimize(Ids &in, Ids &out) {
        std::cout << "Algo_weak optimize emitted." << std::endl;

        // iterate over syscalls
        for (auto &item : in.data) {
            processSyscall(item.second, out);
        }

        return true;
    }

    void Algo_weak::processSyscall(Syscall &sc, Ids &out) {

        unsigned depth {0};

        std::cout << "max depth of `" << sc.name << "` is";

        for (auto &arg : sc.next) {
            unsigned tmp;

            if ((tmp = getDepth(arg)) > depth) {
                if (depth != 0u) {
                    std::cout << " " << depth;
                }

                depth = tmp;
            }
        }

        std::cout << " " << depth << std::endl;

        out.data[sc.name].name = sc.name;
        out.data[sc.name].return_code = sc.return_code;
        out.data[sc.name].arg_num = sc.arg_num;
        out.data[sc.name].clustered = false;
        out.data[sc.name].next = bar(sc.next);

    }

    std::vector<Argument> Algo_weak::bar(std::vector<Argument> &vec) {


        for (auto &item : vec) {
            if (!item.next.empty()) {
                item.next = bar(item.next);
            }
        }

        std::vector<Argument> ret_vec {};

        if (checkVecEndsForType(vec, ValueType::INTEGER)) {
            Argument arg;
            arg.valueFormat = vec.front().valueFormat;
            arg.valueType = vec.front().valueType;
            arg.key = vec.front().key;

            if (vec.size() > 1) {
                std::pair<Argument, Argument> x = getMinMax(vec);
                arg.value = x.first.value;
                arg.value_b = x.second.value;
                arg.numbervalues = NumberValues::RANGE;
            }
            else {
                arg.value = vec.front().value;
                arg.numbervalues = NumberValues::VALUE;
            }

            ret_vec.push_back(arg);
        }
        else {
            for (auto item : vec) {
                Argument arg;
                arg.valueFormat = item.valueFormat;
                arg.valueType = item.valueType;
                arg.value = item.value;
                arg.key = item.key;
                arg.next = item.next;
                arg.numbervalues = NumberValues::VALUE;
                ret_vec.push_back(arg);
            }
        }

        return ret_vec;
    }

    std::pair<Argument, Argument> Algo_weak::getMinMax(std::vector<Argument> vec) {
        Argument min {vec.front()};
        Argument max {vec.back()};

        for (const auto &item : vec) {
            if (item < min) {
                min = item;
            }

            if (max < item) {
                max = item;
            }
        }

        return std::make_pair(min, max);
    }


    Argument Algo_weak::mergeConstants(std::vector<Argument> vec) {
        Argument arg;
        std::string text;
        std::vector<std::string> results;
        std::vector<std::string>::iterator it;

        //merge every item into one string
        for (auto &item : vec) {
            if (auto pval_int = std::get_if<unsigned long>(&item.value)) {
                unsigned long a = *pval_int;
                text += std::to_string(a) + "|";
            }
            else if (auto pval_str = std::get_if<std::string>(&item.value)) {
                std::string a = *pval_str;
                text += a + "|";
            }
        }

        // remove last separator
        text.resize(text.size() - 1);

        //split
        results = string_to_vector(text, '|');

        // uniq
        std::sort(results.begin(), results.end());
        it = std::unique(results.begin(), results.end());
        results.resize(std::distance(results.begin(), it));


        // merge back to string
        text = "";

        for (auto &item : results) {
            text += item + "|";
        }

        // remove last separator
        text.resize(text.size() - 1);

        arg.valueFormat = ValueFormat::VALUE;
        arg.valueType = ValueType::BITFIELD;
        arg.value = text;

        return arg;
    }


    void Algo_weak::findMinMax(Syscall &sc, Ids &out) {
        (void) sc;
        (void) out;
    }

} // namespace st2se