#include <catch2/catch_test_macros.hpp>

#include <fr_musp/envelope/constant.h>

using namespace fr_musp::envelope;
using namespace std::chrono;
using namespace Catch;

TEST_CASE("The constant envelope") {
    milliseconds length(1000);
    unsigned int sampleRate(40000);
    Constant constant(length, sampleRate);

    SECTION("Should always return 1.0f") {
        for (int i = 0; i < sampleRate; i++) {
            REQUIRE(constant[i] == 1.0f);
        }
    }

    SECTION("Should be iterable") {
        for (auto value : constant) {
            REQUIRE(value == 1.0f);
        }
    }
}
