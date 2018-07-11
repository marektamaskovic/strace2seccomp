#include "output.hpp"

namespace st2se {

    void Output::threadSupport(bool b) {
        genThreading = b;
    }

    void Output::genFuncProlog(bool b) {
        genProlog = b;
    }

    void Output::setAllowOnlySc(bool b) {
    	allowOnlySc = b;
    }

} // namespace st2se