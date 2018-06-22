#include "generator.hpp"

namespace st2se {

    Generator::Generator(Output *_out): gnrt(_out) {
        if (gnrt == nullptr) {
            throw (std::runtime_error("Error constructing generator."));
        }
    }

    bool Generator::initialize(Output *_out) {
        if (_out == nullptr) {
            return false;
        }

        gnrt = _out;

        return true;
    }

    void Generator::threadSupport(bool b){
        gnrt->threadSupport(b);
    }

    void Generator::genFuncProlog(bool b){
        gnrt->genFuncProlog(b);
    }

    void Generator::setOutput(std::string o){
        gnrt->setOutput(o);
    }

    bool Generator::isInitialized() {
        return gnrt == nullptr ? false : true;
    }

    bool Generator::generate(Ids &ids) {

        gnrt->generate(ids);

        return true;
    }

    void Generator::removeOutput() {
        gnrt = nullptr;
    }

} // namespace st2se