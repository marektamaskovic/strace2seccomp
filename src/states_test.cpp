// Copyright (c) 2018 Red Hat <mtamasko@redhat.com>
// Author: Marek Tamaskovic <tamaskovic.marek@gmail.com>
//
// This file is part of strace2seccomp tool.
//
// strace2seccomp tool is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// strace2seccomp tool is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with strace2seccomp tool.  If not, see <https://www.gnu.org/licenses/>.

#include <sstream>

#include "catch2/catch.hpp"

#include "ids.hpp"
#include "states.hpp"

TEST_CASE("Setter and getters", "[States]") {
	SECTION("value format"){
		st2se::States states;
		st2se::val_format_t set = st2se::val_format_t::VALUE;
		st2se::val_format_t get;


		states.set_val_format(set);
		get = states.get_val_format();

		REQUIRE(set == get);
	}

	SECTION("value type"){
		st2se::States states;
		st2se::val_type_t set = st2se::val_type_t::INTEGER;
		st2se::val_type_t get;


		states.set_val_type(set);
		get = states.get_val_type();

		REQUIRE(set == get);
	}

	SECTION("return value"){
		st2se::States states;
		std::string _set = "42";
		int set {0};
		int get {0};

		states.set_ret_val(_set);
		get = states.get_ret_val();

		// convert string to number
		std::stringstream buf(_set);
        buf >> set;

		REQUIRE(set == get);
	}

	SECTION("name"){
		st2se::States states;
		std::string set = "Hello";
		std::string get;


		states.set_name(set);
		get = states.get_name();

		REQUIRE(set == get);
	}

	SECTION("bitfields"){
		st2se::States states;
		bool set = true;
		bool get;


		states.set_bitfields(set);
		get = states.get_bitfields();

		REQUIRE(set == get);
	}

}

TEST_CASE("Constructor", "[States]") {
	st2se::States states;

	st2se::val_format_t fmt = states.get_val_format();
	st2se::val_type_t type = states.get_val_type();
	int rc = states.get_ret_val();
	std::string name = states.get_name();
	bool bitfield = states.get_bitfields();


	REQUIRE(fmt == st2se::val_format_t::EMPTY);
	REQUIRE(type == st2se::val_type_t::EMPTY);
	REQUIRE(rc == 0);
	REQUIRE_FALSE(name.compare(""));
	REQUIRE(bitfield == false);
}

TEST_CASE("Clear method", "[States]") {
	st2se::States states;

	states.set_val_format(st2se::val_format_t::VALUE);
	states.set_val_type(st2se::val_type_t::INTEGER);
	states.set_ret_val("42");
	states.set_name("write");
	states.set_bitfields(true);

	states.clear();

	// st2se::val_format_t fmt = states.get_val_format();
	// st2se::val_type_t type = states.get_val_type();
	// int rc = states.get_ret_val();
	// std::string name = states.get_name();
	bool bitfield = states.get_bitfields();

	// TODO
	// check if you could reset these values as well
	// REQUIRE(fmt == st2se::val_format_t::EMPTY);
	// REQUIRE(type == st2se::val_type_t::EMPTY);
	// REQUIRE(rc == 0);
	// REQUIRE_FALSE(name.compare(""));
	REQUIRE(bitfield == false);

}