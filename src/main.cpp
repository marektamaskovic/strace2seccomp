#define TAOCPP_PEGTL_NAMESPACE mylib_pegtl

#include <iostream>

#include "tao/pegtl.hpp"
#include "tao/pegtl/contrib/json.hpp"

#include "parser.hpp"

int main()
{
   // if( argc > 1 ) {
   //   tao::mylib_pegtl::argv_input<> in( argv, 1 );
   //   tao::mylib_pegtl::parse< tao::mylib_pegtl::json::text >( in );
   // }

	// s2s::config_t config = parseArguments(argc, argv);

	s2s::straceParser o("strace.out");

	std::cout << o.getFilename() << std::endl;

	return 0;

}
