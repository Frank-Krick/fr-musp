#include <catch2/catch_test_macros.hpp>

#include <fr_musp/envelope/triangle.h>

using namespace fr_musp::envelope;
using namespace std::chrono;
using namespace Catch;

TEST_CASE("The triangle for even length") {
    milliseconds length(1000);
    unsigned int sampleRate(40000);
    Triangle triangle(length, sampleRate);

    SECTION("Should be 0.0f at the start") { REQUIRE(triangle[0] == 0.0f); }

    SECTION("Should be 0.0f at the end") { REQUIRE(triangle[39999] == 0.0f); }

    SECTION("Should be a ramp for the first half") {
        Ramp ramp(length / 2, sampleRate);
        for (unsigned int i = 0; i < sampleRate / 2; i++) {
            REQUIRE(triangle[i] == ramp[i]);
        }
    }

    SECTION("Should be an inverted ramp for the second half") {
        InvertedRamp invertedRamp(length / 2, sampleRate);
        for (unsigned int i = sampleRate / 2; i < sampleRate; i++) {
            REQUIRE(triangle[i] == invertedRamp[i - sampleRate / 2]);
        }
    }

    SECTION("Should be iterable") {
        unsigned int index{};
        for (auto value : triangle) {
            REQUIRE(triangle[index] == value);
            index++;
        }
    }
}

TEST_CASE("The triangle for odd length") {
    milliseconds length(1000);
    unsigned int sampleRate(40001);
    Triangle triangle(length, sampleRate);

    SECTION("Should be 0.0f at the start") { REQUIRE(triangle[0] == 0.0f); }

    SECTION("Should be 0.0f at the end") { REQUIRE(triangle[40000] == 0.0f); }

    SECTION("Should be a ramp for the first half") {
        Ramp ramp(length / 2, sampleRate);
        for (unsigned int i = 0; i < sampleRate / 2; i++) {
            REQUIRE(triangle[i] == ramp[i]);
        }
    }

    SECTION("Should be an inverted ramp for the second half") {
        InvertedRamp invertedRamp(length / 2, sampleRate);
        for (unsigned int i = sampleRate / 2; i < sampleRate; i++) {
            REQUIRE(triangle[i] == invertedRamp[i - sampleRate / 2]);
        }
    }

    SECTION("Should be iterable") {
        unsigned int index{};
        for (auto value : triangle) {
            REQUIRE(triangle[index] == value);
            index++;
        }
    }
}