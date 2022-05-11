#include <catch2/catch_test_macros.hpp>

#include <fr_musp/envelope/envelope_segment.h>

using namespace fr_musp::envelope;
using namespace std::chrono;
using namespace Catch;

TEST_CASE("The envelope segment containing a constant") {
    milliseconds length(1000);
    unsigned int sampleRate(40000);
    Constant constant(length, sampleRate);

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