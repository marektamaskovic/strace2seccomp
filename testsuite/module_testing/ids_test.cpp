#include <string>
#include <vector>

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch2/catch.hpp"
#include "ids.hpp"

unsigned int Factorial( unsigned int number ) {
    return number > 1 ? Factorial(number-1)*number : 1;
}

TEST_CASE( "constructors", "[argument_t]") {
	SECTION("without params") {
		//create argument;
		st2se::argument_t *arg = new st2se::argument_t;

		REQUIRE( arg->value_format == st2se::val_format_t::EMPTY );
		REQUIRE( arg->value_type == st2se::val_type_t::EMPTY );
		REQUIRE_FALSE( arg->key.compare("") );

		std::string str = std::get<std::string>(arg->value);

		REQUIRE_FALSE( str.compare("") );

		int size = arg->next.size();

		REQUIRE( size == 0 );
		//delete argument
		delete arg;
	}

	SECTION("with 3 params") {

		st2se::val_format_t _type = st2se::val_format_t::VALUE;
        st2se::val_type_t _fmt = st2se::val_type_t::INTEGER;

		st2se::argument_t *arg = new st2se::argument_t( _type, _fmt, {});

		REQUIRE( arg->value_format == st2se::val_format_t::VALUE );
		REQUIRE( arg->value_type == st2se::val_type_t::INTEGER );

		REQUIRE_FALSE( arg->key.compare("") );

		std::string str = std::get<std::string>(arg->value);

		REQUIRE_FALSE( str.compare("") );

		int size = arg->next.size();

		REQUIRE( size == 0 );

		delete arg;
	}



	SECTION("with 5 params") {

		st2se::val_format_t _type = st2se::val_format_t::VALUE;
        st2se::val_type_t _fmt = st2se::val_type_t::INTEGER;
        std::string _key = "key";

		st2se::argument_t *arg = new st2se::argument_t( _type, _fmt, _key, 5l, {});

		REQUIRE( arg->value_format == st2se::val_format_t::VALUE );
		REQUIRE( arg->value_type == st2se::val_type_t::INTEGER );

		REQUIRE_FALSE( arg->key.compare("key") );

		long val = std::get<long>(arg->value);
		REQUIRE( val == 5 );

		int size = arg->next.size();
		REQUIRE( size == 0 );

		delete arg;
	}
}
