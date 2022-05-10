#include <catch2/catch_test_macros.hpp>

#include <fr_musp/envelope/logarithmic_fall.h>

using namespace fr_musp::envelope;
using namespace std::chrono;
using namespace Catch;

TEST_CASE("The logarithmic fall") {
    milliseconds length(1000);
    unsigned int sampleRate(40000);
    float curvature(6.0f);
    ExponentialRise exponentialRise(length, curvature, sampleRate);
    LogarithmicFall logarithmicFall(length, curvature, sampleRate);

    SECTION("Should be 1.0f at the beginning") {
        REQUIRE(logarithmicFall[0] == 1.0f);
    }

    SECTION("Should be 0.0f at the end") {
        REQUIRE(logarithmicFall[39999] == 0.0f);
    }

    SECTION("Should be inverted exponential rise") {
        for (unsigned int i = 0; i < 40000; i++) {
            REQUIRE(logarithmicFall[i] == 1.0f - exponentialRise[i]);
        }
    }

    SECTION("Should be iterable") {
        unsigned int index{};
        for (auto value : logarithmicFall) {
            REQUIRE(value == logarithmicFall[index]);
            index++;
        }
    }
}
