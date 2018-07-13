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

#include "generator.hpp"

namespace st2se {

    Generator::Generator(Output *_out): gnrt(_out) {
        if (gnrt == nullptr) {
            throw (std::runtime_error("Error constructing generator."));
        }
    }

    bool Generator::initialize(Output *_out) {
        if (_out == nullptr) {
            return false;
        }

        gnrt = _out;

        return true;
    }

    void Generator::configure(const Params &p) {
        if (p.thread != 0) {
            threadSupport(/*turn on =*/true);
        }

        if (p.prolog != 0) {
            genFuncProlog(/*turn on =*/true);
        }

        if (!p.output.empty()) {
            setOutput(p.output);
        }

        if(p.scOnly != 0) {
            setAllowOnlySc(/*turn on =*/true);
        }
    }

    inline void Generator::threadSupport(bool b) {
        gnrt->threadSupport(b);
    }

    inline void Generator::genFuncProlog(bool b) {
        gnrt->genFuncProlog(b);
    }

    inline void Generator::setOutput(std::string o) {
        gnrt->setOutput(std::move(o));
    }

    inline void Generator::setAllowOnlySc(bool b) {
        gnrt->setAllowOnlySc(b);
    }


    bool Generator::isInitialized() {
        return gnrt != nullptr;
    }

    bool Generator::generate(Ids &ids) {

        gnrt->generate(ids);

        return true;
    }

    void Generator::removeOutput() {
        gnrt = nullptr;
    }

} // namespace st2se