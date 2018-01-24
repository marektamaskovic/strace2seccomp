/******************************************************************************/
/* Data structures                                                            */
/******************************************************************************/


struct arg_t;

struct arg_t{
    std::string name;
    std:vector<struct arg_t> child_args;
}

typedef std::map<std::string, std::vector<arg_t>> ids_t;


/******************************************************************************/
/* Weak algorithm                                                             */
/******************************************************************************/

unsigned get_num_args(arg_t &arg){
    if(arg.child_args.length() != 0){
        return 1 + get_num_args(arg.child_args[0]);
    }
    else{
        return 0;
    }
}

std::pair get_minmax(struct arg_t arg, unsigned lvl){
    if(lvl == 0){
        std::vector<arg_t>::iterator result = std::minmax_element(std::begin(arg.child_args), std::begin(arg.child_args), arg_t_compare);
        return make_pair(result.first, result.second);
    }
    else{
        std::vector<minmax_t> results;

        for(auto arg_it : arg.child_args){
            results.emplace_back(get_minmax(arg_it, lvl - 1));
        }
        std::vector<arg_t>::iterator result = std::minmax_element(std::begin(results), std::begin(results), results_comp);
        return make_pair(result.first, result.second);
    }
}


// minmax algo 1
void weak_translation(rules_t rules, const ids_t &ids){
    for(const auto &sc : ids){
        for(const auto &arg : sc.child_args){
            std::vector<std::pair> intervals;
            unsigned num_args = get_num_args(arg);

            for(unsigned lvl = 0; lvl < num_args; ++lvl){
                intervals.emplace_back(get_minmax(arg, lvl));
            }

            rules.add(sc.first, intervals); // creates seccomp rule for this syscall.
        }
    }
}

/******************************************************************************/
/* Strict algorithm                                                           */
/******************************************************************************/


void foo(){}