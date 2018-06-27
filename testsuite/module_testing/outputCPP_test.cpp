#include "catch2/catch.hpp"

#include "outputCPP.hpp"

TEST_CASE( "Output methods", "[Output]") {
	st2se::outputCPP *o = new st2se::outputCPP;

	o->threadSupport(true);
	REQUIRE(o->Output::genThreading);

    o->genFuncProlog(true);
    REQUIRE(o->Output::genProlog);

	delete o;

}