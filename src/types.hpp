#ifndef TYPES_HPP
#define TYPES_HPP

#include <string>
#include <vector>
#include <map>

namespace s2s{

	struct arg_t;
	struct sc_t;

	struct sc_t
	{
		std::vector<arg_t> arg;
		int return_code;
		std::string other;
	};

	struct arg_t{
		std::string name;
		std::string val;
		std::vector<arg_t> next_arg;
	};

	struct ids_t
	{
		std::map<std::string, sc_t> ids;
	// public:
		// ids_t();
		// ~ids_t();

	};

} // end of namespace

#endif

