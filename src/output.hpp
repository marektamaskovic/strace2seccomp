#ifndef SRC_OUTPUT_HPP
#define SRC_OUTPUT_HPP

#include "ids.hpp"

namespace st2se {
	
	class Output
	{
	public:
		Output() = default;
		~Output() = default;
		
		virtual void generate(Ids &ids) = 0;

	};

} // namespace st2se

#endif