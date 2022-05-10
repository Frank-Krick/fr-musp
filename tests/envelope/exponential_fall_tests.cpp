#include <catch2/catch_test_macros.hpp>

#include <fr_musp/envelope/exponential_fall.h>

using namespace fr_musp::envelope;
using namespace std::chrono;
using namespace Catch;

TEST_CASE("The exponential fall") {
    milliseconds length(1000);
    unsigned int sampleRate(40000);
    float curvature(6.0f);
    ExponentialRise exponentialRise(length, curvature, sampleRate);
    ExponentialFall exponentialFall(length, curvature, sampleRate);

    SECTION("Is equal to the exponential rise evaluated at 1 - position / "
            "sampleRate") {
        for (unsigned int i = 0; i < 40000; i++) {
            REQUIRE(exponentialRise[i] == exponentialFall[39999 - i]);
        }
    }

    SECTION("Should be iterable") {
        unsigned int index{};
        for (auto value : exponentialFall) {
            REQUIRE(value == exponentialFall[index]);
            ++index;
        }
    }
}