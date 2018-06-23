#ifndef OPTIMIZER_HPP
#define OPTIMIZER_HPP

#include <iostream>

#include "algorithm.hpp"
#include "ids.hpp"

namespace st2se {

    class Optimizer {
        Algorithm *opt_adapter {nullptr}; // TODO uniq pointer
      public:
        Optimizer(Algorithm *_opt_adapter);
        Optimizer();
        void useAlgorithm(Algorithm *_opt_adapter);
        bool isInitialized();
        bool optimize(Ids &in, Ids &out);
    };

} // namespace st2se

#endif