#include "algorithms.hpp"

namespace st2se {

    // WEAK //
    // FIXME make this operator visible for every .cpp file
    std::ostream &operator<< (std::ostream &os, const st2se::val_type_t &a) {

        if (a == st2se::val_type_t::POINTER) {
            os << "POINTER";
        }
        else if (a == st2se::val_type_t::INTEGER) {
            os << "INTEGER";
        }
        else if (a == st2se::val_type_t::STRING) {
            os << "STRING";
        }
        else if (a == st2se::val_type_t::CONSTANT) {
            os << "CONSTANT";
        }
        else if (a == st2se::val_type_t::ARRAY) {
            os << "ARRAY";
        }
        else if (a == st2se::val_type_t::STRUCTURE) {
            os << "STRUCTURE";
        }
        else if (a == st2se::val_type_t::EMPTY) {
            os << "EMPTY";
        }

        return os;
    }

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
                std::cout << "\t\tmax: " << arg2str(v.front()) << std::endl;
                std::cout << "\t\tmin: " << arg2str(v.back()) << std::endl;
            }
            else {
                std::cout << "\t\tval: " << arg2str(v.front()) << std::endl;
            }
        }


        return;
    }

    std::vector<argument_t> Algorithm::getArguemntsFromPos(
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

    void Algo_weak::findMinMax(Syscall_t &sc, Ids &out) {
        return;
    }

    // --------------------------------------------------------------------- //


    // STRICT //

    bool Algo_strict::optimize(Ids &in, Ids &out) {
        std::cout << "Algo_strict optimize emitted." << std::endl;
        return true;
    }

    // --------------------------------------------------------------------- //


    // Advanced //

    bool Algo_advanced::optimize(Ids &in, Ids &out) {
        std::cout << "Algo_advanced optimize emitted." << std::endl;

        for (const auto &item : in.data) {
            this->processSyscall(item.second, out);
        }

        return true;
    }

    void Algo_advanced::processSyscall(const Syscall_t &sc, Ids &out) {
        unsigned depth {0};

        std::cout << "max depth of `" << sc.name << "` is";

        // FIXME
        // make static function of this vvv
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

        // ------------------------------------
        // Algorithm:

        for (unsigned arg_pos = 0; arg_pos < depth; arg_pos++) {
            std::vector<argument_t> v;
            v = getArguemntsFromPos(sc.next, arg_pos);

            std::sort(v.begin(), v.end(), [](argument_t a, argument_t b) {
                return a.value > b.value;
            });

            // *INDENT-OFF*
            auto end =
                std::unique(v.begin(), v.end(), [](argument_t l, argument_t r)
            {
                return l.value == r.value;
            });
            // *INDENT-ON*

            v.erase(end, v.end());

            // Clustering:
            std::vector<argument_t> clusterd_v {};
            unsigned clusters = this->cluster(v, clusterd_v);

            if (clusters == 0) {
                throw (std::runtime_error("Clustering error"));
            }

            std::cout << "\targ no." << arg_pos << " is ";
            std::cout << v.size() << " items long" << std::endl;
            std::cout << "\t\tclusters: " << clusters << std::endl;
        }
    }

    // clustering algorithm which clusters the arguments
    // from vector 'in' and stores them in vector 'out'
    unsigned Algo_advanced::cluster(std::vector<argument_t> &in, std::vector<argument_t> &out) {

        int first {0};
        int second {0};

        auto smallest_pair = smallestDst(in);

        double eps = 2.0 * distance(smallest_pair.first, smallest_pair.second);

        while (true) {

        }

        return -1;
    }

    // find the closest pair of values
    std::pair<argument_t, argument_t> Algo_advanced::smallestDst(std::vector<argument_t> &in) {
        std::pair<argument_t, argument_t> p;
        double mem_dst {0.0};
        double tmp {0.0};

        for (unsigned i = 0; i < in.size(); i++) {
            for (unsigned l = i; l < in.size(); l++) {
                tmp = distance(in[i], in[l]);

                if (tmp != (-1.0)) {
                    continue;
                }
                else if (tmp <= mem_dst) {
                    mem_dst = tmp;
                    p = std::make_pair(in.at(i), in.at(l));
                }
            }
        }

        return p;
    }

    // computes distance for two arguments
    double Algo_advanced::distance(argument_t &left, argument_t &right) {
        double ret_val {-1.0};

        if (left.value_type == val_type_t::STRING) {
            // string distance ???
            auto a = *std::get_if<std::string>(&(left.value));
            auto b = *std::get_if<std::string>(&(left.value));
            return LevenshteinDistance(a, a.size(), b, b.size());
        }
        else if (
            left.value_type == val_type_t::POINTER ||
            left.value_type == val_type_t::INTEGER
        ) {
            // number distance ???
            auto a = std::get_if<long>(&(left.value));
            auto b = std::get_if<long>(&(left.value));

            ret_val = (a > b) ? a - b : b - a;

        }
        else if (left.value_type == val_type_t::BITFIELD) {
            // compute distance between bitfields
            auto a = convert2bitfield(left);
            auto b = convert2bitfield(right);
            ret_val = bitfieldDistance(a, b);
        }

        return ret_val;
    }

    // -------- //

    // convert argument string value to bitfield_t
    bitfield_t convert2bitfield(argument_t &in) {

        std::string s = *std::get_if<std::string>(&(in.value));
        std::string delim = "|";
        std::vector<std::string> bitfields;

        auto start = 0U;
        auto end = s.find(delim);

        while (end != std::string::npos) {
            bitfields.push_back(s.substr(start, end - start));
            start = end + delim.length();
            end = s.find(delim, start);
        }

        bitfields.push_back(s.substr(start, end));
        std::sort(bitfields.begin(), bitfields.end());

        return bitfields;
    }

    // Code taken from: https://en.wikipedia.org/wiki/Levenshtein_distance
    // len_s and len_t are the number of characters in string s and t respectively
    int LevenshteinDistance(const std::string &s, int len_s, const std::string &t, int len_t) {
        int cost;

        /* base case: empty strings */
        if (len_s == 0) {
            return len_t;
        }

        if (len_t == 0) {
            return len_s;
        }

        /* test if last characters of the strings match */
        if (s[len_s - 1] == t[len_t - 1]) {
            cost = 0;
        }
        else {
            cost = 1;
        }

        /* return minimum of delete char from s, delete char from t, and delete char from both */
        return minimum(
                LevenshteinDistance(s, len_s - 1, t, len_t) + 1,
                LevenshteinDistance(s, len_s, t, len_t - 1) + 1,
                LevenshteinDistance(s, len_s - 1, t, len_t - 1) + cost
            );
    }

    int minimum(int a, int b, int c) {
        if ((a < b) && (a < c)) {
            return a;
        }
        else if (b < c) {
            return b;
        }
        else {
            return c;
        }
    }

    int bitfieldDistance(bitfield_t &a, bitfield_t &b) {
        int ret_val {0};

        if (a.size() == 0 && b.size() == 0) {
            return 0;
        }
        else if (a.size() == 0) {
            return b.size();
        }
        else if (b.size() == 0) {
            return a.size();
        }
        else {
            if (a.size() < b.size()) {
                auto tmp = a;
                b = a;
                b = tmp;
            }

            int diff {0};

            //create uset of bitfields and initialize them with appropriate vectors
            std::unordered_set<std::string> uset_a {};
            std::unordered_set<std::string> uset_b {};

            for (auto item : a) {
                uset_a.insert(item);
            }

            for (auto item : b) {
                uset_b.insert(item);
            }

            // check if item from vector a is in uset_b
            // if not increment difference
            // else continue
            for (auto item = a.begin(); item != a.end(); item++) {
                auto search = uset_b.find(*item);

                if (search != uset_b.end()) {
                    continue;
                }
                else {
                    diff++;
                }
            }

            // the same as above but for item from vector b in uset_a
            for (auto item = b.begin(); item != b.end(); item++) {
                auto search = uset_a.find(*item);

                if (search != uset_a.end()) {
                    continue;
                }
                else {
                    diff++;
                }
            }

            // set ret_val with number of differences between bitfields
            ret_val = diff;
        }

        return ret_val;
    }

} // end of namespace
