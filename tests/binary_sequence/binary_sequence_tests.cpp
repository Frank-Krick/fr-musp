#include <catch2/catch_test_macros.hpp>
#include <utility>

#include <fr_musp/binary_sequence/binary_sequence.h>

using namespace fr_musp;

TEST_CASE("Should output the binary sequence") {
    BinarySequence<4> binarySequence;

    SECTION("The initial sequence should be 0 and wrap around") {
        for (int i = 0; i < 8; i++) {
            auto currentValue = binarySequence();
            REQUIRE(currentValue == false);
        }
    }

    SECTION("It should loop the assigned binary number") {
        std::vector<bool> expectedValues = {true, true, false, false, true, true, false, false};
        binarySequence.setValue(3);
        for (auto expected: expectedValues) {
            auto currentValue = binarySequence();
            REQUIRE(currentValue == expected);
        }
    }

    SECTION("It should be possible to loop over less than max length") {
        std::vector<bool> expectedValues = {true, true, false, true, true, false};
        binarySequence.setValue(3);
        binarySequence.setLoopLength(3);
        for (auto expected: expectedValues) {
            auto currentValue = binarySequence();
            REQUIRE(currentValue == expected);
        }
    }

    SECTION("It should change the current position if loop length changes") {
        std::vector<bool> expectedValues = {true, true, false, false};
        binarySequence.setValue(3);
        auto currentValue = binarySequence();
        REQUIRE(true == currentValue);
        currentValue = binarySequence();
        REQUIRE(true == currentValue);
        currentValue = binarySequence();
        REQUIRE(false == currentValue);
        binarySequence.setLoopLength(3);
        currentValue = binarySequence();
        REQUIRE(true == currentValue);
    }
}