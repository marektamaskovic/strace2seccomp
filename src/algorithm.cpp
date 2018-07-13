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

#include "algorithm.hpp"

namespace st2se {

    std::vector<argument_t> Algorithm::getArguemntsFromPos(
        const std::vector<argument_t> &args,
        unsigned lvl
    ) {
        std::vector<argument_t> v;

        std::function<void(std::vector<argument_t>&, const std::vector<argument_t>&)> inserter;

        inserter = [](std::vector<argument_t> &to, const std::vector<argument_t> &in) {
            for (auto &item : in) {

                if (item.value_type == val_type_t::STRUCTURE ||
                    item.value_type == val_type_t::ARRAY ||
                    item.value_type == val_type_t::STRING
                ) {
                    to.emplace_back();
                    continue;
                }

                argument_t tmp;
                tmp.value_type = item.value_type;
                tmp.value_format = item.value_format;
                tmp.value = item.value;
                to.push_back(tmp);
            }
        };

        if (lvl == 0) {
            inserter(v, args);
        }
        else {
            for (auto arg : args) {
                auto x = getArguemntsFromPos(arg.next, lvl - 1);
                inserter(v, x);
            }
        }

        return v;
    }

    unsigned Algorithm::getDepth(const argument_t &arg) {
        unsigned depth {0};

        if (arg.next.empty()) {
            return 1u;
        }
        else {
            for (const auto &subarg : arg.next) {
                unsigned tmp;

                if ((tmp = getDepth(subarg)) > depth) {
                    depth = tmp;
                }

            }
        }

        return depth + 1;
    }

} // namespace st2se
