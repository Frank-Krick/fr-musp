#ifndef FR_MUSP_RAMP_TESTS_CPP
#define FR_MUSP_RAMP_TESTS_CPP

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

#include <fr_musp/envelope/ramp.h>

using namespace fr_musp::envelope;
using namespace std::chrono;
using namespace Catch;

TEST_CASE("The ramp") {
    milliseconds length(1000);
    unsigned int sampleRate(40000);
    Ramp ramp(length, sampleRate);

    SECTION("Should start with 0") {
        REQUIRE(ramp[0] == 0.0f);
    }

    SECTION("Should end with 1") {
        REQUIRE(ramp[40000 - 1] == 1.0f);
    }

    SECTION("Should increase by the slope") {
        float accum = 0.0f;
        for (size_t i = 0; i < 40000; i++) {
            REQUIRE(ramp[i] == Approx(accum).epsilon(0.001));
            accum += 1.0f / 40000.0f;
        }
    }

    SECTION("Should be iterable") {
        float accum = 0.0f;
        for (auto value : ramp) {
            REQUIRE(value == Approx(accum).epsilon(0.001));
            accum += 1.0f / 40000.0f;
        }
    }
}

#endif // FR_MUSP_RAMP_TESTS_CPP
