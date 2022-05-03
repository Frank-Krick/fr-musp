#include <catch2/catch_test_macros.hpp>
#include <fr_musp/granular/grain.h>

#include <array>

using namespace fr_musp::granular;
using namespace std;

class TestWindow {
public:
    explicit TestWindow(size_t length) {}

    float operator[](size_t position) const {
        return 2.0f;
    }
};

TEST_CASE("The grain") {
    array<float, 10> data {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    Grain<TestWindow> grain(data);

    SECTION("Should return the samples multiplied by the window") {
        for (size_t i = 0; i < 10; i++) {
            REQUIRE(grain[i] == i * 2.0f);
        }
    }

    SECTION("Should be iterable with range based for") {
        int count = 0;
        for (auto sample : grain) {
            REQUIRE(sample == count * 2.0f);
            count++;
        }
    }
}
