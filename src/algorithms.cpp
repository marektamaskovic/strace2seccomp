#include "algorithms.hpp"

namespace st2se {

    // WEAK //

    bool Algo_weak::optimize(Ids &in, Ids &out) {
        std::cout << "Algo_weak optimize emitted." << std::endl;

        //iterate over syscalls
        for (const auto &item : in.data) {
            processSyscall(item.second, out);
        }

        return true;
    }

    void Algo_weak::processSyscall(const Syscall_t &sc, Ids &out) {

        unsigned depth {0};

        std::cout << "max depth of `" << sc.name << "` is";

        for (const auto &arg : sc.next) {
            unsigned tmp;

            if ((tmp = getDepth(arg)) > depth) {
                if (depth) {
                    std::cout << " " << depth;
                }

                depth = tmp;
            }
        }

        std::cout << " " << depth << std::endl;

        for (unsigned arg_pos = 0; arg_pos < depth; arg_pos++) {
            std::vector<argument_t> v;
            v = getArguemntsFromPos(sc.next, arg_pos);

            std::sort(v.begin(), v.end(), [](argument_t a, argument_t b) {
                return a.value > b.value;
            });

            auto end = std::unique(v.begin(), v.end(), [](argument_t l, argument_t r) {
                return l.value == r.value;
            });

            v.erase(end, v.end());

            std::cout << "\targ no." << arg_pos << " is " << v.size() << " items long" << std::endl;

            if (v.size() != 1) {
                std::cout << "\t\tmax: " << arg2str(v.front()) << std::endl
                    << "\t\tmin: " << arg2str(v.back()) << std::endl;
            }
            else {
                std::cout << "\t\tval: " << arg2str(v.front()) << std::endl;
            }
        }


        return;
    }

    std::vector<argument_t> Algo_weak::getArguemntsFromPos(
        const std::vector<argument_t> &args,
        unsigned lvl
    ) {
        if (lvl == 0) {
            return args;
        }
        else {
            std::vector<argument_t> v;

            for (auto arg : args) {
                auto x = getArguemntsFromPos(arg.next, lvl - 1);
                std::copy(x.begin(), x.end(),
                    std::back_inserter(v));
            }

            return v;
        }
    }

    unsigned Algo_weak::getDepth(const argument_t &arg) {
        unsigned depth {0};

        if (arg.next.empty()) {
            return 1;
        }
        else {
            for (const auto &arg : arg.next) {
                unsigned tmp;

                if ((tmp = getDepth(arg)) > depth) {
                    depth = tmp;
                }

            }
        }

        return depth + 1;
    }

    void Algo_weak::findMinMax(Syscall_t &sc, Ids &out) {
        return;
    }

    // ---- //


    // STRICT //

    bool Algo_strict::optimize(Ids &in, Ids &out) {
        std::cout << "Algo_strict optimize emitted." << std::endl;
        return true;
    }

    // ------ //


    // Advanced //

    bool Algo_advanced::optimize(Ids &in, Ids &out) {
        std::cout << "Algo_advanced optimize emitted." << std::endl;
        return true;
    }

    // -------- //

} // end of namespace
