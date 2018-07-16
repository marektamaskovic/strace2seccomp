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

#include "catch2/catch.hpp"

#include "generator.hpp"
#include "output.hpp"

TEST_CASE("Generator initialization", "[generator]") {

    st2se::Generator gen;

    int a = 0;

    void *gnrt = &a;

    gen.initialize((st2se::Output *)gnrt);

    REQUIRE(gen.isInitialized());

    gen.removeOutput();

    REQUIRE_FALSE(gen.isInitialized());
}
