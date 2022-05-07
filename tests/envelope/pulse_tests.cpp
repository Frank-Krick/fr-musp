#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

#include <fr_musp/envelope/pulse.h>

using namespace fr_musp::envelope;
using namespace std::chrono;
using namespace Catch;

TEST_CASE("The pulse envelope") {
    float dutyCycle(0.3f);
    unsigned int sampleRate(40000);
    milliseconds duration(1000);
    Pulse pulse(duration, dutyCycle, sampleRate);

    SECTION("Should be 1.0 at the beginning") { REQUIRE(pulse[0] == 1.0f); }

    SECTION("Should be 0.0 at the end") {
        REQUIRE(pulse[sampleRate - 1] == 0.0f);
    }

    SECTION("Should flip as determined by the duty cycle") {
        auto switchSample = (unsigned int)floor((float)sampleRate * dutyCycle);
        for (int i = 0; i < sampleRate; i++) {
            if (i < switchSample) {
                REQUIRE(pulse[i] == 1.0f);
            } else {
                REQUIRE(pulse[i] == 0.0f);
            }
        }
    }
}
