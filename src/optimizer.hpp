#ifndef OPTIMIZER_HPP
#define OPTIMIZER_HPP

#include <iostream>

#include "algorithms.hpp"
#include "ids.hpp"

namespace st2se {

    class Optimizer {
        Algorithm *opt_adapter {nullptr};
      public:
        Optimizer(Algorithm *_opt_adapter);
        Optimizer();
        void useAlgorithm(Algorithm *_opt_adapter);
        bool isInitialized();
        bool optimize(Ids &in, Ids &out);
    };

} // end of namespace

#endif