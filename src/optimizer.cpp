#include "optimizer.hpp"

namespace st2se {
    // Optimizer::Optimizer() {
    //
    // }

    Optimizer::Optimizer(Algorithm *_opt_adapter) : opt_adapter(_opt_adapter) {}

    Optimizer::Optimizer() : Optimizer::Optimizer(nullptr) {}


    bool Optimizer::optimize(Ids &in, Ids &out) {
        if (!isInitialized()) {
            throw std::runtime_error("Algorithm is not provided.");
        }

        return opt_adapter->optimize(in, out);
    }

    void Optimizer::useAlgorithm(Algorithm *_opt_adapter) {
        if (_opt_adapter == nullptr) {
            std::cout << "Warning: Optimizer: setting algorithm to nullptr." << std::endl;
        }

        opt_adapter = _opt_adapter;
    }

    bool Optimizer::isInitialized() {
        return opt_adapter != nullptr;
    }

} // namespace st2se