#include "algorithms.hpp"

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
                std::copy(x.begin(), x.end(), std::back_inserter(v));
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
        (void) sc;
        (void) out;
    }

    // --------------------------------------------------------------------- //


    // STRICT //

    bool Algo_strict::optimize(Ids &in, Ids &out) {
        (void) in;
        (void) out;
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
                if (depth != 0) {
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

            std::sort(v.begin(), v.end(),
            [](argument_t a, argument_t b) {
                return a.value > b.value;
            }
            );

            // *INDENT-OFF*
            auto end =
                std::unique(v.begin(), v.end(),
                    [](argument_t l, argument_t r){return l.value == r.value;}
                );
            // *INDENT-ON*

            v.erase(end, v.end());

            // Clustering:
            std::vector<argument_t> clusterd_v {};
            unsigned clusters = this->cluster(v, clusterd_v);

            if (clusters == 0) {
                throw (std::runtime_error("Clustering error"));
            }

            std::cout << "\targ no." << arg_pos << " is ";
            std::cout << clusterd_v.size() << " items long" << std::endl;
            std::cout << "\t\tclusters: " << clusters << std::endl;
        }
    }

    // clustering algorithm which clusters the arguments
    // from vector 'in' and stores them in vector 'out'
    unsigned Algo_advanced::cluster(std::vector<argument_t> &in, std::vector<argument_t> &out) {

        int first {0};
        int second {0};

        if (in.empty()) {
            return 0;
        }

        if (in.size() == 1) {
            out.push_back(in.front());
            return 1;
        }

        if (in.size() == 2) {
            out.push_back(in.front());
            out.push_back(in.back());
            return 2;
        }



        std::cout << POSITION_MACRO << arg2str(in.front()) << std::endl;


        std::cout << POSITION_MACRO << "in.size() is " << in.size() << std::endl;
        std::cout << POSITION_MACRO << "in is:" << std::endl;

        for (auto item : in) {
            std::cout << "\t" << arg2str(item) << std::endl;
        }

        std::vector<argument_t> reducing_input;

        std::cout << POSITION_MACRO << "reducing_input.size() is " << reducing_input.size() << std::endl;

        // duplicate in to reducing_input
        std::copy(in.begin(), in.end(),
            std::back_inserter(reducing_input));

        std::cout << POSITION_MACRO << "reducing_input.size() is " << reducing_input.size() << std::endl;
        std::cout << POSITION_MACRO << "reducing_input is:" << std::endl;

        for (auto item : reducing_input) {
            std::cout << "\t" << arg2str(item) << std::endl;
        }

        // helping vectors
        std::vector<argument_t> to_check {};
        std::vector<argument_t> cluster {};

        auto smallest_pair = smallestDst(in);
        double eps = 2.0 * distance(smallest_pair.first, smallest_pair.second);

        to_check.push_back(smallest_pair.first);
        to_check.push_back(smallest_pair.second);

        std::cout << POSITION_MACRO << arg2str(smallest_pair.first) << std::endl;
        std::cout << POSITION_MACRO << arg2str(smallest_pair.second) << std::endl;

        std::cout << "---------------------------------\n\n\n\n" << std::endl;

        while (true) {
            //------------------------------------------------------------------
            // Debug info:
            //------------------------------------------------------------------
            std::cout << POSITION_MACRO << "step 1: removeItem  to_check().front from reducing_input" << std::endl;
            std::cout << POSITION_MACRO << "to_check is:" << std::endl;

            for (auto item : to_check) {
                std::cout << "\t" << arg2str(item) << std::endl;
            }

            std::cout << POSITION_MACRO << "cluster is:" << std::endl;

            for (auto item : cluster) {
                std::cout << "\t" << arg2str(item) << std::endl;
            }

            std::cout << POSITION_MACRO << "reducing_input is:" << std::endl;

            for (auto item : reducing_input) {
                std::cout << "\t" << arg2str(item) << std::endl;
            }

            //------------------------------------------------------------------
            removeItem(to_check.front(), reducing_input);

            std::cout << POSITION_MACRO << "step 2: find closest items to " << std::endl;
            auto vec_tmp = closestItemsTo(to_check.front(), reducing_input);

            std::cout << POSITION_MACRO << "step 3" << std::endl;

            for (auto item : vec_tmp) {
                std::cout << POSITION_MACRO << "step 3.1: insert clossest items to `to_check` set" << std::endl;
                to_check.push_back(item);
                cluster.push_back(item);

                std::cout << POSITION_MACRO << "step 3.2: remove clossest item from `reducing_input` set" << std::endl;
                removeItem(item, reducing_input);
            }

            std::cout << POSITION_MACRO << "step 4: check if is `to_check` set empty" << std::endl;

            if (to_check.empty()) {
                moveCluster(cluster, out);
                cluster.clear();

                if (!reducing_input.empty()) {
                    std::cout << POSITION_MACRO << "step 4.1: `reducing_input` is not empty adding first item of it to to_check set" << std::endl;
                    to_check.push_back(reducing_input.front());
                }
                else {
                    std::cout << POSITION_MACRO << "step 4.2: `reducing_input` is empty() breaking out from loop" << std::endl;
                    break;
                }
            }

        }
        std::cout << POSITION_MACRO << "step 5: returning from cluster()" << std::endl;

        return out.size();
    }

    // asdf func()
    bool Algo_advanced::removeItem(argument_t &arg, std::vector<argument_t> &vec) {

        // std::cout << POSITION_MACRO << "arg is " << arg2str(arg) << std::endl;
        // std::cout << POSITION_MACRO << "vec is:" << std::endl;

        // for (auto item : vec) {
        //     std::cout << "\t" << arg2str(item) << std::endl;
        // }

        for (auto item = vec.begin(); item != vec.end(); item++) {
            // std::cout << POSITION_MACRO << "comparing:" << std::endl;
            // std::cout << "\t" << arg2str(arg) << std::endl;
            // std::cout << "\t" << arg2str(*item) << std::endl;

            if (*item == arg) {
                vec.erase(item);
                break;
            }
        }

        vec.shrink_to_fit();
        return true;
    }

    // asdf func()
    std::vector<argument_t> Algo_advanced::closestItemsTo(const argument_t &arg, std::vector<argument_t> &vec) {

        double(tmp) {
            0.0
        };
        std::vector<argument_t> ret_val {};

        if (vec.empty()) {
            return ret_val;
        }

        // std::cout << POSITION_MACRO << "computing distance:" << std::endl;
        // std::cout << "\t" << arg2str(vec.front()) << std::endl;
        // std::cout << "\t" << arg2str(vec.back()) << std::endl;

        double min = distance(vec.front(), vec.back());


        for (auto item : vec) {
            tmp = distance(item, arg);

            if (tmp < min) {
                min = tmp;
            }
        }

        for (auto item : vec) {
            if (distance(item, arg) == min) {
                ret_val.push_back(item);
            }
        }

        return ret_val;
    }

    // asdf func()
    bool Algo_advanced::moveCluster(std::vector<argument_t> &cluster, std::vector<argument_t> &out) {

        if (cluster.empty()) {
            return false;
        }

        out.push_back(cluster.back());
        cluster.pop_back();

        std::vector<argument_t> &place = out.front().next;

        for (auto item : cluster) {
            place.push_back(item);
        }

        cluster.clear();

        return true;
    }


    // find the closest pair of values
    std::pair<argument_t, argument_t> Algo_advanced::smallestDst(std::vector<argument_t> &in) {
        std::pair<argument_t, argument_t> p;
        double mem_dst = distance(in.front(), in.back());
        double tmp {0.0};

        std::cout << POSITION_MACRO << "distance:" << std::endl;

        std::cout << "\tin.size(): " << in.size() << std::endl;
        std::cout << "\tmem_dst: " << mem_dst << std::endl;
        std::cout << "\ti\tl\ttmp" << std::endl;

        for (unsigned i = 0; i < in.size(); i++) {
            for (unsigned l = i; l < in.size(); l++) {
                tmp = distance(in[i], in[l]);
                std::cout << "\t" << i << "\t" << l << "\t" << tmp << std::endl;

                if (tmp == (-1.0)) {
                    continue;
                }

                if (tmp != 0.0 && tmp <= mem_dst) {
                    mem_dst = tmp;
                    std::cout << "\tassigning: " << arg2str(in.at(i)) << std::endl;
                    std::cout << "\tassigning: " << arg2str(in.at(l)) << std::endl;
                    p.first = in.at(i);
                    p.second = in.at(l);
                }
            }
        }

        // std::cout << POSITION_MACRO << arg2str(in.front()) << std::endl;
        // std::cout << POSITION_MACRO << arg2str(p.first) << std::endl;
        // std::cout << POSITION_MACRO << arg2str(p.second) << std::endl;

        return p;
    }

    // computes distance for two arguments
    double Algo_advanced::distance(const argument_t &left, const argument_t &right) {
        double ret_val {-1.0};

        // std::cout << POSITION_MACRO << "value_type:" << left.value_type << std::endl;

        if (
            left.value_type == val_type_t::POINTER ||
            left.value_type == val_type_t::INTEGER
        ) {
            // number distance ???
            long a = *std::get_if<long>(&(left.value));
            long b = *std::get_if<long>(&(right.value));

            if (a > b) {
                ret_val = a - b;
            }
            else {
                ret_val = b - a;
            }
            // std::cout << POSITION_MACRO << "assigning:" << ((a > b) ? a - b : b - a) << std::endl;

        }

        if (left.value_type == val_type_t::BITFIELD) {
            // compute distance between bitfields
            auto a = convert2bitfield(left);
            auto b = convert2bitfield(right);
            ret_val = bitfieldDistance(a, b);
        }

        // std::cout << POSITION_MACRO << "ret_val:" << ret_val << std::endl;


        return ret_val;
    }

    // -------- //

    // convert argument string value to bitfield_t
    bitfield_t convert2bitfield(const argument_t &in) {

        std::string s;

        if (auto _s = std::get_if<std::string>(&(in.value))) {
            s = *_s;
        }
        else {
            return bitfield_t {};
        }

        std::string delim = "|";
        bitfield_t bitfields;

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

    int bitfieldDistance(bitfield_t &a, bitfield_t &b) {
        int ret_val {0};

        if (a.empty() && b.empty()) {
            return 0;
        }

        if (a.empty()) {
            return b.size();
        }

        if (b.empty()) {
            return a.size();
        }

        if (a.size() < b.size()) {
            const bitfield_t tmp = a;
            a = b;
            b = tmp;
        }

        int diff {0};

        // create uset of bitfields and initialize them with appropriate vectors
        std::unordered_set<std::string> uset_a {};
        std::unordered_set<std::string> uset_b {};

        for (const auto &item : a) {
            uset_a.insert(item);
        }

        for (const auto &item : b) {
            uset_b.insert(item);
        }

        // check if item from vector a is in uset_b
        // if not increment difference
        // else continue
        for (auto &item : a) {
            auto search = uset_b.find(item);

            if (search != uset_b.end()) {
                continue;
            }

            diff++;
        }

        // the same as above but for item from vector b in uset_a
        for (auto &item : b) {
            auto search = uset_a.find(item);

            if (search != uset_a.end()) {
                continue;
            }

            diff++;
        }

        // set ret_val with number of differences between bitfields
        ret_val = diff;

        return ret_val;
    }

} // namespace st2se
