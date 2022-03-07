#include <catch2/catch_test_macros.hpp>
#include <fr_musp/white_noise/white_noise.h>

using namespace fr_musp;

TEST_CASE("WhiteNoise") {
    WhiteNoise whiteNoise;

    SECTION("Should create pseudo-random values") {
        auto result = whiteNoise();
        REQUIRE(result == 16807 * 4.6566129e-010);
        result = whiteNoise();
        REQUIRE(result == 16807 * 16807 * 4.6566129e-010);
    }
}
