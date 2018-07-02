#include "catch2/catch.hpp"

#include "generator.hpp"
#include "output.hpp"

TEST_CASE("Generator initialization", "[generator]") {

	st2se::Generator gen;

	int a = 0;

	void *gnrt = &a;

	gen.initialize((st2se::Output*)gnrt);

	REQUIRE(gen.isInitialized());

	gen.removeOutput();

	REQUIRE_FALSE(gen.isInitialized());
}
