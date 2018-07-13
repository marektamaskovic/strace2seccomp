/**
 * @file output.hpp
 * @brief Interface for output implementation
 */
#ifndef SRC_OUTPUT_HPP
#define SRC_OUTPUT_HPP

#include "ids.hpp"

namespace st2se {

    /**
     * Virtual class interface for output
     * Virtual class used only for definition of interface for specific output
     * such as CPP or GO output
     */
    class Output {
      public:
        bool genThreading {false}; /**< switch for thread support*/
        bool genProlog {false};    /**< switch for filter wrapper generation*/
        bool bugSec {false};       /**< deprecated needs refactor*/
        bool allowOnlySc {false};  /**< switch for syscall only generation*/

        /**
         * Constructor
         * default constructor
         */
        Output() = default;
        /**
         * Destructor
         * virtual default destructor
         */
        virtual ~Output() = default;

        /**
         * Interface
         * this method will be called on optimizer startup
         * @param ids IDS to print in to output file
         */
        virtual void generate(Ids &ids) = 0;
        /**
         * Interface
         * This method will change output filename
         * @param o output filename
         */
        virtual void setOutput(std::string o) = 0;

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
        void setAllowOnlySc(bool b);
    };

} // namespace st2se

#endif