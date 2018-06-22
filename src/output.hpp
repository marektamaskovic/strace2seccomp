#ifndef SRC_OUTPUT_HPP
#define SRC_OUTPUT_HPP

#include "ids.hpp"

namespace st2se {

    class Output {
      public:
      	bool genThreading {false};
      	bool genProlog {false};
        Output() = default;
        virtual ~Output() = default;

        virtual void generate(Ids &ids) = 0;
        virtual void setOutput(std::string o) = 0;

        void threadSupport(bool b);
		void genFuncProlog(bool b);

    };

} // namespace st2se

#endif