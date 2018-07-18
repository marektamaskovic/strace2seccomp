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
 * @file argparse.hpp
 * @brief argparse class is defiend here. The class is used as wrapper for
 * getopt.
 */

#ifndef ARGPARSE_HPP
#define ARGPARSE_HPP

#include <fstream>
#include <getopt.h>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>


/**
 * Wrapper for getopt.
 */
class Params {
  public:
    int help {0};                           /**< help switch*/
    int weak {0};                           /**< weak algorithm switch*/
    int strict {0};                         /**< strict algorithm switch*/
    int advanced {0};                       /**< advanced algorithm switch*/
    int verbose {0};                        /**< verbose mode switch*/
    int debug {0};                          /**< debug mode switch*/
    int tracing {0};                        /**< tracing mode switch*/
    int analysis {0};                       /**< analysis mode switch*/
    int thread {0};                         /**< print thread support switch*/
    int prolog {0};                         /**< print function wrapper around filter in output switch*/
    int scOnly {0};                         /**< syscall only output switch*/
    int showProgress {0};                   /**< syscall only output switch*/
    std::string output {};                  /**< output file name */
    std::vector<std::string> file_names {}; /**< input filenames */

    /**
     * Constructor
     * @param argc number of arguments provided as runtime arguments
     * @param argv is array of arguments provided as runtime arguments
     */
    Params(int argc, char *argv[]);
    /**
     * Print inner states.
     * This member will print all inner states of this wrapper.
     */
    void printHelp();
    // ~Params();


};

/**
 * Operator overload
 * This operator implements a way to print Params class
 */
std::ostream &operator<< (std::ostream &os, const Params &a);

#endif
