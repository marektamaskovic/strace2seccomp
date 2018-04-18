#include "algorithm_weak.hpp"

namespace st2se {

    bool Algo_weak::optimize(Ids &in, Ids &out) {
        std::cout << "Algo_weak optimize emitted." << std::endl;

        // iterate over syscalls
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
                if (depth != 0u) {
                    std::cout << " " << depth;
                }

                depth = tmp;
            }
        }

        std::cout << " " << depth << std::endl;

        for (unsigned arg_pos = 0; arg_pos < depth; arg_pos++) {
            std::vector<argument_t> v;
            v = getArguemntsFromPos(sc.next, arg_pos);

            /*INDENT-OFF*/
            std::sort(v.begin(), v.end(),
                [](argument_t a, argument_t b)
                    {return a.value > b.value;}
            );

            auto end = std::unique(v.begin(), v.end(),
                [](argument_t l, argument_t r)
                    {return l.value == r.value;}
            );
            /*INDENT-ON*/

            v.erase(end, v.end());

            std::cout << "\targ no." << arg_pos << " is " << v.size() << " items long" << std::endl;
            std::vector<argument_t> clustered_v {};

            if (v.size() != 1) {
                clustered_v.push_back(v.front());
                clustered_v.push_back(v.back());

                std::cout << "\t\tmax: " << arg2str(v.front()) << std::endl;
                std::cout << "\t\tmin: " << arg2str(v.back()) << std::endl;
            }
            else {
                clustered_v.push_back(v.front());
                std::cout << "\t\tval: " << arg2str(v.front()) << std::endl;
            }


            std::cout << "arg_pos: " << arg_pos << " v:" << std::endl;

            std::cout << "\targ no." << arg_pos << " is ";
            std::cout << clustered_v.size() << " items long" << std::endl;

            out.data[sc.name].next.emplace_back(val_format_t::EMPTY,
                val_type_t::CLUSTERS,
                clustered_v
            );

            std::cout << "out...next.size()" << out.data[sc.name].next.size() << std::endl;
            out.data[sc.name].clustered = true;
            std::cout << "\n" << std::endl;
        }

        std::cout << "\n\n" << std::endl;

        // TODO
        // put intervals into out structure
    }

    void Algo_weak::findMinMax(Syscall_t &sc, Ids &out) {
        (void) sc;
        (void) out;
    }

} // namespace st2se