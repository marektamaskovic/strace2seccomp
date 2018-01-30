#ifndef ARGPARSE_HPP
#define ARGPARSE_HPP

#include <iostream>
#include <string>
#include <vector>


class Params {
    int argc{0};
    char** argv{nullptr};
    std::vector<bool> arg_map {};

    inline int checkForHelpSwitch();
    int getAllSwitchesAndValues();
    inline int checkIntegrity();

public:
    bool help {false};
    bool weak {false};
    bool strict {false};
    bool advanced {false};
    bool verbose {false};
    std::vector<std::string> file_names;

    Params(int argc, char* argv[]);

    ~Params();

    int getFileNames();
    void initArgMap();

};

std::ostream& operator<< (std::ostream& os, const Params& a);

#endif