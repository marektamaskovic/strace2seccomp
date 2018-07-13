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

#include "optimizer.hpp"

namespace st2se {
    // Optimizer::Optimizer() {
    //
    // }

    Optimizer::Optimizer(Algorithm *_opt_adapter) : opt_adapter(_opt_adapter) {}

    Optimizer::Optimizer() : Optimizer::Optimizer(nullptr) {}


    bool Optimizer::optimize(Ids &in, Ids &out) {

        if (!isInitialized()) {
            throw std::runtime_error("Algorithm is not provided.");
        }

        auto ret_val = opt_adapter->optimize(in, out);

        return ret_val;
    }

    void Optimizer::useAlgorithm(Algorithm *_opt_adapter) {

        if (_opt_adapter == nullptr) {
            std::cout << "Warning: Optimizer: setting algorithm to nullptr." << std::endl;
        }

        opt_adapter = _opt_adapter;
    }

    bool Optimizer::isInitialized() {

        return opt_adapter != nullptr;

    }

} // namespace st2se