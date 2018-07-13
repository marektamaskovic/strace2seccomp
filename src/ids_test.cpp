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

#include <string>
#include <vector>

#include "catch2/catch.hpp"
#include "ids.hpp"

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

		auto val = std::get<unsigned long>(arg->value);
		REQUIRE( val == 5 );

		int size = arg->next.size();
		REQUIRE( size == 0 );

		delete arg;
	}
}

TEST_CASE("Support functions", "[others]") {
	SECTION("arg2str()") {
		st2se::val_format_t _type = st2se::val_format_t::VALUE;
        st2se::val_type_t _fmt = st2se::val_type_t::INTEGER;
        std::string _key = "key";
        std::string _val = "test_string";

		st2se::argument_t *arg = new st2se::argument_t( _type, _fmt, _key, _val, {});

		std::string val= std::get<std::string>(arg->value);

		REQUIRE_FALSE(val.compare(_val));

		delete arg;
	}
}

st2se::Syscall_t createSyscall(std::string name, int rc, std::string other, unsigned an, int a, std::string b, int c){
	st2se::Syscall_t sc;
	sc.name = name;
	sc.return_code = rc;
	sc.other = other;
	sc.arg_num = an;

	st2se::val_format_t _fmt = st2se::val_format_t::VALUE;
    st2se::val_type_t _type = st2se::val_type_t::INTEGER;
    std::string _key = "";


    st2se::argument_t arg1(_fmt, _type, _key, a, {});
	sc.next.push_back(arg1);


	_type = st2se::val_type_t::STRING;
	if(b.length() == 0){
		_type = st2se::val_type_t::EMPTY;
		_fmt = st2se::val_format_t::EMPTY;
	}
    st2se::argument_t arg2(_fmt, _type, _key, b, {});
	sc.next.front().next.push_back(arg2);


	_type = st2se::val_type_t::INTEGER;
	_fmt = st2se::val_format_t::VALUE;
    st2se::argument_t arg3(_fmt, _type, _key, c, {});
	sc.next.front().next.front().next.push_back(arg3);


	return sc;
}

TEST_CASE("Inertion into IDS", "[Ids]") {

	st2se::Ids ids;

	st2se::Syscall_t sc1 = createSyscall("write", 0, "", 3, 1, "asd", 3);
	st2se::Syscall_t sc2 = createSyscall("write", 0, "", 3, 1, "asd", 4);
	st2se::Syscall_t sc3 = createSyscall("write", 0, "", 3, 1, "asd", 5);

	ids.insert(sc1.name, sc1);
	ids.insert(sc2.name, sc2);
	ids.insert(sc3.name, sc3);

	REQUIRE(ids.data["write"].next.size() == 1);
	REQUIRE(ids.data["write"].next.front().next.size() == 1);
	REQUIRE(ids.data["write"].next.front().next.front().next.size() == 3);
}


TEST_CASE("argument compare", "[operators]") {

	SECTION("== integer"){
		st2se::argument_t l;
		st2se::argument_t r;

		l.value_type = st2se::val_type_t::INTEGER;
		r.value_type = st2se::val_type_t::INTEGER;

		l.value_format = st2se::val_format_t::VALUE;
		r.value_format = st2se::val_format_t::VALUE;

		l.value = 5;
		r.value = 5;

		REQUIRE(l == r);

		r.value = 6;
		REQUIRE_FALSE( l == r);

		REQUIRE( l < r);
	}

	SECTION("== string"){
		st2se::argument_t l;
		st2se::argument_t r;

		l.value_type = st2se::val_type_t::STRING;
		r.value_type = st2se::val_type_t::STRING;

		l.value_format = st2se::val_format_t::VALUE;
		r.value_format = st2se::val_format_t::VALUE;

		l.value = "Hello";
		r.value = "Hello";

		REQUIRE(l == r);

		r.value = "Ehlo";
		REQUIRE_FALSE( l == r);
	}

}
