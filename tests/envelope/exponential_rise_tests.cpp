#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

#include <fr_musp/envelope/exponential_rise.h>
#include <fr_musp/envelope/ramp.h>

using namespace fr_musp::envelope;
using namespace std::chrono;
using namespace Catch;

TEST_CASE("The exponential rise") {
    milliseconds length(1000);
    unsigned int sampleRate(40000);
    float curvature(6.0f);
    ExponentialRise exponentialRise(length, curvature, sampleRate);

    SECTION("It should be 0.0f at the beginning") {
        REQUIRE(exponentialRise[0] == 0.0f);
    }

    SECTION("It should be 1.0f at the end") {
        REQUIRE(exponentialRise[39999] == 1.0f);
    }

    SECTION("An exponential rise with higher curvature should be smaller, "
            "expect for at the beginning and end") {
        ExponentialRise higherCurvature(length, 7.0f, sampleRate);
        REQUIRE(exponentialRise[0] == higherCurvature[0]);
        REQUIRE(exponentialRise[39999] == higherCurvature[39999]);
        for (unsigned int i = 1; i < 39999; i++) {
            REQUIRE(exponentialRise[i] > higherCurvature[i]);
        }
    }

    SECTION("Should be strictly smaller than a ramp, except for at the "
            "beginning and the end") {
        Ramp ramp(length, sampleRate);
        REQUIRE(exponentialRise[0] == ramp[0]);
        REQUIRE(exponentialRise[39999] == ramp[39999]);
        for (unsigned int i = 1; i < 39999; i++) {
            REQUIRE(exponentialRise[i] < ramp[i]);
        }
    }

    SECTION("Should be iterable") {
        unsigned int index{};
        for (auto value : exponentialRise) {
            REQUIRE(exponentialRise[index] == value);
            index++;
        }
    }
}
