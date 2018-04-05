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

            if (v.size() != 1) {
                std::cout << "\t\tmax: " << arg2str(v.front()) << std::endl;
                std::cout << "\t\tmin: " << arg2str(v.back()) << std::endl;
            }
            else {
                std::cout << "\t\tval: " << arg2str(v.front()) << std::endl;
            }
        }

        // TODO
        // put intervals into out structure
        (void) out;
    }

    void Algo_weak::findMinMax(Syscall_t &sc, Ids &out) {
        (void) sc;
        (void) out;
    }

} // namespace st2se