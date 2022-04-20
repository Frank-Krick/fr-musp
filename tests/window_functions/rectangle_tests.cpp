#include <catch2/catch_test_macros.hpp>
#include <fr_musp/window_functions/rectangular.h>

using namespace fr_musp::windows;

TEST_CASE("The rectangular window") {
    Rectangular window(20);

    SECTION("Should be 0 outside of the window") {
        REQUIRE(window[20] == 0);
        REQUIRE(window[21] == 0);
        REQUIRE(window[45] == 0);
    }

    SECTION("Should be 1 inside the window") {
        for (size_t i = 0; i < 20; i++) {
            REQUIRE(window[i] == 1);
        }
    }
}