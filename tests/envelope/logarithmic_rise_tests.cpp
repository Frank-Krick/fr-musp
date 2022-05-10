#include <catch2/catch_test_macros.hpp>

#include <fr_musp/envelope/logarithmic_rise.h>

using namespace fr_musp::envelope;
using namespace std::chrono;
using namespace Catch;

TEST_CASE("The logarithmic rise") {
    milliseconds length(1000);
    unsigned int sampleRate(40000);
    float curvature(6.0f);
    ExponentialFall exponentialFall(length, curvature, sampleRate);
    LogarithmicRise logarithmicRise(length, curvature, sampleRate);

    SECTION("Should be 0.0f at the beginning") {
        REQUIRE(logarithmicRise[0] == 0.0f);
    }

    SECTION("Should be 1.0f at the end") {
        REQUIRE(logarithmicRise[39999] == 1.0f);
    }

    SECTION("Should be inverted exponential fall") {
        for (unsigned int i = 0; i < 40000; i++) {
            REQUIRE(logarithmicRise[i] == 1.0f - exponentialFall[i]);
        }
    }

    SECTION("Should be iterable") {
        unsigned int index{};
        for (auto value : logarithmicRise) {
            REQUIRE(value == logarithmicRise[index]);
            index++;
        }
    }
}
