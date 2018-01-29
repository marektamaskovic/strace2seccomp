#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>

namespace s2s {

	class straceParser {
		std::string filename {""};
		ids_t &output;
	public:
		straceParser(std::string _filename, s2s::ids_t &_output);
		// ~straceParser();

		std::string getFilename();
	};

}

#endif