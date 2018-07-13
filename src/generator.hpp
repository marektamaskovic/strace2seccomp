/**
 * @file generator.hpp
 * @brief Generator wrapper over implementation. Used d-pointer design pattern
 */
#ifndef SRC_GENERATOR_HPP
#define SRC_GENERATOR_HPP

#include "argparse.hpp"
#include "ids.hpp"
#include "outputCPP.hpp"

namespace st2se {

    /**
     * Language enum
     */
    enum class language {
        CPP, /**< CPP lang switch*/
        GO /**< GO lang switch*/
    };

    /**
     * Output generator
     * This class is designed as d-pointer design pattern to wrap
     * implementation from user.
     */
    class Generator {
        Output *gnrt {nullptr}; /**< Pointer to generator*/
      public:
        /**
         * Constructor
         * defualt constructor
         */
        Generator() = default;
        /**
         * Constructor
         * explicit constructor
         * @param _out an specific generator
         */
        explicit Generator(Output *_out);
        /**
         * Initializer
         * @param _out output implementation
         */
        bool initialize(Output *_out);
        /**
         * Configuration
         * @param p parameters extracted from command line
         * @return true on success otherwise return false
         */
        void configure(const Params &p);
        /**
         * Generator
         * This member is responsible for printing startup
         * @return true on success otherwise return false
         */
        bool generate(Ids &ids);
        /**
         * Initialization checker
         * Will check if the implementation of output generator is set up
         * @return true if initialized false otherwise
         */
        bool isInitialized();
        /**
         * Remove implementation from wrapper
         */
        void removeOutput();
        /**
         * Turn on thread support
         * @param b bool variable
         */
        void threadSupport(bool b);
        /**
         * Generate wrapper around output filter
         * @param b bool variable
         */
        void genFuncProlog(bool b);
        /**
         * Change output filename
         * @param b output filename
         */
        void setOutput(std::string o);
        /**
         * Generate only syscall filter
         * @param b bool variable
         */
        void setAllowOnlySc(bool b);

    };
} // namespace st2se


#endif