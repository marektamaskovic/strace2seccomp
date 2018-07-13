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
