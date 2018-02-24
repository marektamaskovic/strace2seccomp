#include "argparse.hpp"

static bool param_error{false};

std::ostream &operator<< (std::ostream &os, const Params &a) {
    return os << "-h: " << a.help << std::endl
        << "-w: " << a.weak << std::endl
        << "-s: " << a.strict << std::endl
        << "-a: " << a.advanced << std::endl
        << "-v: " << a.verbose << std::endl
        << "-d: " << a.verbose << std::endl
        << "Err flag: " << param_error;
}

Params::Params(int argc, char *argv[]) {
    std::string help_str{"-h"};
    // std::shared_ptr<char*> _argv {argv};

    int c;

    while (1) {
        static struct option long_options[] = {
            /* These options set a flag. */
            {"weak",     no_argument, &this->weak,     1},
            {"strict",   no_argument, &this->strict,   1},
            {"advanced", no_argument, &this->advanced, 1},
            {"verbose",  no_argument, &this->verbose,  1},
            {"debug",    no_argument, &this->debug,    1},
            {"tracing",  no_argument, &this->tracing,  1},
            {nullptr,    0,           nullptr,         0}
        };
        /* getopt_long stores the option index here. */
        int option_index = 0;

        c = getopt_long(argc, argv, "wsavdt",
                long_options, &option_index);

        /* Detect the end of the options. */
        if (c == -1) {
            break;
        }

        switch (c) {
        case 0:

            /* If this option set a flag, do nothing else now. */
            if (long_options[option_index].flag != nullptr) {
                break;
            }

            std::cout << "option " << long_options[option_index].name << std::endl;

            if (optarg) {
                std::cout << " with arg %s" << optarg << std::endl;
            }

            std::cout << std::endl;
            break;

        case 'w':
            this->weak = 1;
            break;

        case 's':
            this->strict = 1;
            break;

        case 'a':
            this->advanced = 1;
            break;

        case 'v':
            this->verbose = 1;
            break;

        case 'd':
            this->debug = 1;
            break;

        case 't':
            this->tracing = 1;
            break;

        case '?':
            /* getopt_long already printed an error message. */
            break;

        default:
            abort();
        }
    }

    /* Print any remaining command line arguments (not options). */
    if (optind < argc) {
        std::cout << "non-option ARGV-elements: " << std::endl;

        while (optind < argc) {
            // std::cout << argv[optind] << " " << std::endl;
            this->file_names.emplace_back(argv[optind++]);
        }

        std::cout << std::endl;
    }

}
