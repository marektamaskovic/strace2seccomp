#ifndef ARGPARSE_HPP
#define ARGPARSE_HPP

#include <fstream>
#include <getopt.h>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>



class Params {
  public:
    int help {0};
    int weak {0};
    int strict {0};
    int advanced {0};
    int verbose {0};
    int debug {0};
    int tracing {0};
    int analysis {0};
    int thread {0};
    int prolog {0};
    int scOnly {0};
    std::string output {};
    std::vector<std::string> file_names {};

    Params(int argc, char *argv[]);
    void printHelp();
    // ~Params();


};

std::ostream &operator<< (std::ostream &os, const Params &a);

#endif
