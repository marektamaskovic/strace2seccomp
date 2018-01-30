#include "parser.hpp"
#include "tao/pegtl.hpp"

namespace s2s{
	straceParser::straceParser(std::string _filename, s2s::ids_t &_output):
	filename(_filename),
	output(_output)	{
	}

	std::string straceParser::getFilename() {
		return this->filename;
	}
}