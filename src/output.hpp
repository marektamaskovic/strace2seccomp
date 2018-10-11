// Copyright (c) 2018 Red Hat <mtamasko@redhat.com>
// Author: Marek Tamaskovic <tamaskovic.marek@gmail.com>
//
// This file is part of strace2seccomp tool.
//
// strace2seccomp tool is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// strace2seccomp tool is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with strace2seccomp tool.  If not, see <https://www.gnu.org/licenses/>.

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
        std::string funcName {};   /**< filter function name*/

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
        /**
         * Set filter function name
         * @param fn std::string function name
         */
        void setFuncName(std::string fn);

    };

} // namespace st2se

#endif