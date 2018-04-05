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
                )
                    continue;

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

} // namespace st2se
