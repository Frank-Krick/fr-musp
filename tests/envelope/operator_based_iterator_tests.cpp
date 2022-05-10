#include <catch2/catch_test_macros.hpp>

#include <fr_musp/envelope/operator_based_iterator.h>

using namespace fr_musp::envelope;

class OpTest {
  public:
    float operator[](unsigned int position) { return (float)position; }

    OperatorBasedIterator<OpTest> begin() { return {this}; }

    OperatorBasedIterator<OpTest> end() { return {this, 1000}; }
};

TEST_CASE("The operator based iterator") {
    OpTest test;

    SECTION("Should increment the position and evaluate the iterated envelope "
            "at that position") {
        unsigned int index{};
        for (auto value : test) {
            REQUIRE(value == test[index]);
            index++;
        }
        REQUIRE(index == 1000);
    }
}
