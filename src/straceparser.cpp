#include "straceparser.hpp"

namespace st2se {
    StraceParser::StraceParser(std::string _filename, st2se::Ids& _output):
        filename(_filename), output(_output)    {
    }

    std::string StraceParser::getFilename() {
        return this->filename;
    }

    bool StraceParser::parse(std::string _filename, st2se::Ids& _output) {
        (void) _output;
        std::cout << "parse: " << _filename << std::endl;

        tao::pegtl::file_input<> in (_filename);
        tao::pegtl::parse<st2se::grammar::grammar, st2se::grammar::action>(in, _output);

        return true;
    }
}