#include "argparse.hpp"

static bool param_error{false};

std::ostream &operator<< (std::ostream &os, const Params &a) {

    std::string acc {"files:\n"};

    for (auto item : a.file_names) {
        acc.append("\t- ");
        acc.append(item);
        acc.append("\n");
    }

    return os << "-h: " << a.help
        << "\n-w: " << a.weak
        << "\n-s: " << a.strict
        << "\n-a: " << a.advanced
        << "\n-v: " << a.verbose
        << "\n-d: " << a.debug
        << "\n-A: " << a.analysis
        << "\n-o: " << a.output
        << "\n--prolog: " << a.prolog
        << "\n--thread: " << a.thread
        << "\n--scOnly: " << a.scOnly
        << "\nErr flag: " << param_error
        << "\n" << acc;
}

void Params::printHelp() {

    std::string s4 {"    "}; // four spaces

    std::cout << "Usage:\n";
    std::cout << "\tst2se [OPTION] filename ...\n";

    std::cout << "Generic options:\n";
    std::cout << s4 << "-h [--help]\t\t\t: print this message\n";
    std::cout << s4 << "-v [--verbose]\t\t: turn on verbose mode\n";
    std::cout << s4 << "-d [--debug]\t\t: turn on debug mode\n";
    std::cout << s4 << "-t [--tracing]\t\t: turn on tracing mode\n";
    std::cout << s4 << "-A [--analyze-grammar] \t: analyze grammar\n";
    std::cout << s4 << "-o FILE [--output=FILE]\t: set output file\n";

    std::cout << "Configuration options:\n";
    std::cout << s4 << "-w [--weak]\t\t\t: use weak algorithm\n";
    std::cout << s4 << "-s [--strict]\t\t: use strict algorithm\n";
    std::cout << s4 << "-a [--advanced]\t\t: use advanced algorithm\n";
    std::cout << s4 << "--scOnly\t\t\t: generate only syscall allowance\n";
    std::cout << s4 << "--prolog\t\t\t: generate function prolog\n";
    std::cout << s4 << "--thread\t\t\t: add filter synchronization among threads/processes\n";
    std::cout << std::endl;

}

Params::Params(int argc, char *argv[]) {
    int c;

    while (true) {
        static struct option long_options[] = {
            /* These options set a flag. */
            {"weak",             no_argument, &this->weak,     1},
            {"strict",           no_argument, &this->strict,   1},
            {"advanced",         no_argument, &this->advanced, 1},
            {"verbose",          no_argument, nullptr,       'v'},
            {"debug",            no_argument, nullptr,       'd'},
            {"tracing",          no_argument, &this->tracing,  1},
            {"analyze-grammar",  no_argument, &this->analysis, 1},
            {"thread",           no_argument, &this->thread,   1},
            {"prolog",           no_argument, &this->prolog,   1},
            {"scOnly",           no_argument, &this->scOnly,   1},
            {"output",     optional_argument, nullptr,       'o'},
            {"help",       optional_argument, nullptr,       'h'},
            {nullptr,                      0, nullptr,         0}
        };
        /* getopt_long stores the option index here. */
        int option_index = 0;

        c = getopt_long(argc, argv, "wsavdtAo:ph",
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

        case 'h':
            printHelp();
            exit(0);

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

        case 'A':
            this->analysis = 1;
            break;

        case 'o':
            this->output = std::string(optarg);
            break;

        case 'p':
            this->prolog = 1;
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
        while (optind < argc) {
            this->file_names.emplace_back(argv[optind++]);
        }
    }

    if (help) {
        exit(0);
    }

}
