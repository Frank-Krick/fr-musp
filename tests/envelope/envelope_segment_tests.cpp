#include <catch2/catch_test_macros.hpp>

#include <fr_musp/envelope/envelope_segment.h>

using namespace fr_musp::envelope;
using namespace std::chrono;
using namespace Catch;

TEST_CASE("The empty envelope segment") {
    EnvelopeSegment envelopeSegment;

    SECTION("Should be size 0") {
        REQUIRE(envelopeSegment.size() == 0);
    }

    SECTION("Should signal if it's empty") {
        REQUIRE(envelopeSegment.empty());
    }
}

TEST_CASE("The envelope segment containing a constant") {
    milliseconds length(1000);
    unsigned int sampleRate(40000);
    Constant constant(length, sampleRate);

    SECTION("Should not be empty") {
        EnvelopeSegment envelopeSegment(constant, 0.0f, 0.0f);
        REQUIRE_FALSE(envelopeSegment.empty());
    }

    SECTION("Should scale an envelope") {
        float scale(0.5f);
        EnvelopeSegment envelopeSegment(constant, scale, 0.0f);
        for (int i = 0; i < sampleRate; i++) {
            REQUIRE(envelopeSegment[i] == 0.5f);
        }
    }

    SECTION("Should offset an envelope") {
        float scale(1.0f);
        float offset(0.5f);
        EnvelopeSegment envelopeSegment(constant, scale, offset);
        for (int i = 0; i < sampleRate; i++) {
            REQUIRE(envelopeSegment[i] == 1.5f);
        }
    }

    SECTION("Should do both") {
        float offset(0.5f);
        float scale(4.0f);
        EnvelopeSegment envelopeSegment(constant, scale, offset);
        for (int i = 0; i < sampleRate; i++) {
            REQUIRE(envelopeSegment[i] == 4.5f);
        }
    }

    SECTION("Should be iterable") {
        float offset(0.5f);
        float scale(4.0f);
        EnvelopeSegment envelopeSegment(constant, scale, offset);
        unsigned int index{};
        for (auto value : envelopeSegment) {
            REQUIRE(constant[index] * scale + offset == value);
            index++;
        }
    }
}

TEST_CASE("The envelope segment containing the exponential fall") {
    milliseconds length(1000);
    unsigned int sampleRate(40000);
    float curvature(4);
    ExponentialFall exponentialFall(length, curvature, sampleRate);

    SECTION("Should scale and offset the envelope") {
        float offset(0.5f);
        float scale(4.0f);
        EnvelopeSegment envelopeSegment(exponentialFall, scale, offset);
        REQUIRE(envelopeSegment[0] == 4.5f);
    }

    SECTION("Should be iterable") {
        float offset(0.5f);
        float scale(4.0f);
        EnvelopeSegment envelopeSegment(exponentialFall, scale, offset);
        unsigned int index{};
        for (auto value : envelopeSegment) {
            REQUIRE(exponentialFall[index] * scale + offset == value);
            index++;
        }
    }
}

TEST_CASE("The envelope segment containing the exponential rise") {
    milliseconds length(1000);
    unsigned int sampleRate(40000);
    float curvature(4);
    ExponentialRise exponentialRise(length, curvature, sampleRate);

    SECTION("Should scale and offset the envelope") {
        float offset(0.5f);
        float scale(4.0f);
        EnvelopeSegment envelopeSegment(exponentialRise, scale, offset);
        REQUIRE(envelopeSegment[39999] == 4.5f);
    }

    SECTION("Should be iterable") {
        float offset(0.5f);
        float scale(4.0f);
        EnvelopeSegment envelopeSegment(exponentialRise, scale, offset);
        unsigned int index{};
        for (auto value : envelopeSegment) {
            REQUIRE(exponentialRise[index] * scale + offset == value);
            index++;
        }
    }
}

TEST_CASE("The envelope segment containing the inverted ramp") {
    milliseconds length(1000);
    unsigned int sampleRate(40000);
    InvertedRamp invertedRamp(length, sampleRate);

    SECTION("Should scale and offset the envelope") {
        float offset(0.5f);
        float scale(4.0f);
        EnvelopeSegment envelopeSegment(invertedRamp, scale, offset);
        REQUIRE(envelopeSegment[39999] == 0.5f);
    }

    SECTION("Should be iterable") {
        float offset(0.5f);
        float scale(4.0f);
        EnvelopeSegment envelopeSegment(invertedRamp, scale, offset);
        unsigned int index{};
        for (auto value : envelopeSegment) {
            REQUIRE(invertedRamp[index] * scale + offset == value);
            index++;
        }
    }
}
TEST_CASE("The envelope segment containing the logarithmic fall") {
    milliseconds length(1000);
    unsigned int sampleRate(40000);
    float curvature(2.0f);
    LogarithmicFall logarithmicFall(length, curvature, sampleRate);

    SECTION("Should be iterable") {
        float offset(0.5f);
        float scale(4.0f);
        EnvelopeSegment envelopeSegment(logarithmicFall, scale, offset);
        unsigned int index{};
        for (auto value : envelopeSegment) {
            REQUIRE(logarithmicFall[index] * scale + offset == value);
            index++;
        }
    }
}

TEST_CASE("The envelope segment containing the logarithmic rise") {
    milliseconds length(1000);
    unsigned int sampleRate(40000);
    float curvature(2.0f);
    LogarithmicRise logarithmicRise(length, curvature, sampleRate);

    SECTION("Should be iterable") {
        float offset(0.5f);
        float scale(4.0f);
        EnvelopeSegment envelopeSegment(logarithmicRise, scale, offset);
        unsigned int index{};
        for (auto value : envelopeSegment) {
            REQUIRE(logarithmicRise[index] * scale + offset == value);
            index++;
        }
    }
}

TEST_CASE("The envelope segment containing the pulse") {
    milliseconds length(1000);
    unsigned int sampleRate(40000);
    float curvature(2.0f);
    Pulse pulse(length, curvature, sampleRate);

    SECTION("Should be iterable") {
        float offset(0.5f);
        float scale(4.0f);
        EnvelopeSegment envelopeSegment(pulse, scale, offset);
        unsigned int index{};
        for (auto value : envelopeSegment) {
            REQUIRE(pulse[index] * scale + offset == value);
            index++;
        }
    }
}

TEST_CASE("The envelope segment containing the ramp") {
    milliseconds length(1000);
    unsigned int sampleRate(40000);
    Ramp ramp(length, sampleRate);

    SECTION("Should be iterable") {
        float offset(0.5f);
        float scale(4.0f);
        EnvelopeSegment envelopeSegment(ramp, scale, offset);
        unsigned int index{};
        for (auto value : envelopeSegment) {
            REQUIRE(ramp[index] * scale + offset == value);
            index++;
        }
    }
}

TEST_CASE("The envelope segment containing the triangle") {
    milliseconds length(1000);
    unsigned int sampleRate(40000);
    Triangle triangle(length, sampleRate);

    SECTION("Should be iterable") {
        float offset(0.5f);
        float scale(4.0f);
        EnvelopeSegment envelopeSegment(triangle, scale, offset);
        unsigned int index{};
        for (auto value : envelopeSegment) {
            REQUIRE(triangle[index] * scale + offset == value);
            index++;
        }
    }
}

TEST_CASE("The envelope segment containing the inverted triangle") {
    milliseconds length(1000);
    unsigned int sampleRate(40000);
    InvertedTriangle invertedTriangle(length, sampleRate);

    SECTION("Should be iterable") {
        float offset(0.5f);
        float scale(4.0f);
        EnvelopeSegment envelopeSegment(invertedTriangle, scale, offset);
        unsigned int index{};
        for (auto value : envelopeSegment) {
            REQUIRE(invertedTriangle[index] * scale + offset == value);
            index++;
        }
    }
}
