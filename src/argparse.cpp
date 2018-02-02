#include "argparse.hpp"

bool param_error{false};

std::ostream& operator<< (std::ostream& os, const Params& a) {
    return os << "-h: " << a.help << std::endl
        << "-w: " << a.weak << std::endl
        << "-s: " << a.strict << std::endl
        << "-a: " << a.advanced << std::endl
        << "-v: " << a.verbose << std::endl
        << "Err flag: " << param_error;
}

Params::Params(int argc, char* argv[]) {
    std::string help_str{"-h"};
    this->argc = argc;
    this->argv = argv;
    initArgMap();

    if (!this->checkForHelpSwitch()) {
        this->help = true;
        return;
    }

    this->getAllSwitchesAndValues();

    if (this->checkIntegrity()) {
        param_error = true;
    }

    this->getFileNames();

}

Params::~Params() {
    return;
}

int Params::checkForHelpSwitch() {
    std::string help_str{"-h"};

    for (int i = 0; i < this->argc; ++i) {
        if (!help_str.compare(this->argv[i])) {
            return 0;
        }
    }

    return 1;
}

int Params::getAllSwitchesAndValues() {
    // co si jak prerob to na makra
    // co si jak pridaj tam param_err premennu
    std::string verbose{"-v"}, weak{"-w"}, strict{"-s"}, advanced{"-a"};
    std::string where{"Error: Params: Parse: "};
    bool parse_error = false;

    for (int i = 0; i < this->argc; ++i) {
        if (!weak.compare(this->argv[i])) {
            this->weak          = true;
            this->arg_map[i]    = true;
            continue;
        }

        if (!strict.compare(this->argv[i])) {
            this->strict        = true;
            this->arg_map[i]    = true;
            continue;
        }

        if (!advanced.compare(this->argv[i])) {
            this->advanced      = true;
            this->arg_map[i]    = true;
            continue;
        }

        if (!verbose.compare(this->argv[i])) {
            this->verbose       = true;
            this->arg_map[i]    = true;
            continue;
        }
    }

    if (parse_error) {
        exit(1);
    }

    return 0;
}

int Params::checkIntegrity() {
    std::string where{"Error: Params: Integrity: "};

    if (
        (this->weak == true && this->advanced == true) ||
        (this->weak == true && this->strict == true) ||
        (this->strict == true && this->advanced == true)
    ) {
        std::cerr << where
            << "Multiple optimizations turned on! "
            << "Turn only one at a time!"
            << std::endl;
        return 1;
    }

    return 0;
}

int Params::getFileNames() {
    for (unsigned i = 1; i < this->arg_map.size(); ++i) {
        if (!this->arg_map[i]) {
            this->file_names.push_back(this->argv[i]);
        }
    }

    return 0;
}

void Params::initArgMap() {
    for (int i = 0; i < argc; ++i) {
        this->arg_map.push_back(false);
    }
}