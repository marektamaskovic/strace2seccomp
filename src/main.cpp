#define TAOCPP_PEGTL_NAMESPACE mylib_pegtl

#include <iostream>

#include "tao/pegtl.hpp"
// #include "tao/pegtl/contrib/json.hpp"

#include "argparse.hpp"
#include "parser.hpp"

int main(int argc, char *argv[])
{
	Params *params = new Params(argc, argv);

	// s2s::config_t config = parseArguments(argc, argv);

	s2s::ids_t a;

	s2s::straceParser o("strace.out", a);

	std::cout << *params << std::endl;

	for(const auto &fn : params->file_names){
		std::cout << fn << std::endl;
	}

	std::cout << o.getFilename() << std::endl;

	delete params;

	return 0;

}
