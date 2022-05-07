#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

#include <fr_musp/envelope/inverted_ramp.h>

using namespace fr_musp::envelope;
using namespace std::chrono;
using namespace Catch;

TEST_CASE("The inverted ramp") {
    unsigned int sampleRate(40000);
    milliseconds duration(1000);
    InvertedRamp invertedRamp(duration, sampleRate);

    SECTION("Should return 1.0 at the beginning") {
        REQUIRE(invertedRamp[0] == 1.0f);
    }

    SECTION("Should return 0.0 at the end") {
        REQUIRE(invertedRamp[sampleRate - 1] == 0.0f);
    }

    SECTION("Should decrease by the slope") {
        float accum = 1.0f;
        for (size_t i = 0; i < 40000; i++) {
            REQUIRE(invertedRamp[i] == Approx(accum).margin(0.001));
            accum -= 1.0f / 40000.0f;
        }
    }

    SECTION("Should be iterable") {
        float accum = 1.0f;
        for (auto value : invertedRamp) {
            REQUIRE(value == Approx(accum).margin(0.001));
            accum -= 1.0f / 40000.0f;
        }
    }
}