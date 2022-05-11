#include <catch2/catch_test_macros.hpp>

#include <fr_musp/envelope/inverted_triangle.h>

using namespace fr_musp::envelope;
using namespace std::chrono;
using namespace Catch;

TEST_CASE("The inverted triangle") {
    milliseconds length(1000);
    unsigned int sampleRate(40000);
    InvertedTriangle invertedTriangle(length, sampleRate);

    SECTION("Should be 1.0f at the start") {
        REQUIRE(invertedTriangle[0] == 1.0f);
    }

    SECTION("Should be 1.0f at the end") {
        REQUIRE(invertedTriangle[39999] == 1.0f);
    }

    SECTION("Should be the triangle inverted") {
        Triangle triangle(length, sampleRate);
        for (unsigned int i = 0; i < 39999; i++) {
            REQUIRE(invertedTriangle[i] == 1.0f - triangle[i]);
        }
    }

    SECTION("Should be iterable") {
        unsigned int index{};
        for (auto value : invertedTriangle) {
            REQUIRE(invertedTriangle[index] == value);
            index++;
        }
    }
}
