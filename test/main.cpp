#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>


TEST_CASE("TEST", "[test]")
{
    REQUIRE(1 == 1);
}

TEST_CASE("TEST1", "[test]1")
{
    REQUIRE(1 == 1);
}
