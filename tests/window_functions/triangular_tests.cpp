#include <catch2/catch_test_macros.hpp>
#include <fr_musp/window_functions/triangular.h>

using namespace fr_musp::windows;

TEST_CASE("The triangular window for odd length") {
    Triangular window(21);

    SECTION("Should be the highest in the middle") {
        REQUIRE(window[10] > window[9]);
        REQUIRE(window[10] == window[11]);
        REQUIRE(window[11] > window[12]);
    }

    SECTION("Should increase from beginning to middle") {
        for (size_t i = 0; i < 10; i++) {
            REQUIRE(window[i] < window[i + 1]);
        }
    }

    SECTION("Should decrease from middle to end") {
        for (size_t i = 11; i < 21; i++) {
            REQUIRE(window[i] > window[i + 1]);
        }
    }

    SECTION("Should be 0 outside of the window") {
        REQUIRE(window[21] == 0);
        REQUIRE(window[22] == 0);
        REQUIRE(window[45] == 0);
    }
}

TEST_CASE("The triangular window for even length") {
    Triangular window(20);

    SECTION("Should be 1 in the mid point") {
        REQUIRE(window[10] == 1);
    }

    SECTION("Should increase from beginning to middle") {
        for (size_t i = 0; i < 10; i++) {
            REQUIRE(window[i] < window[i + 1]);
        }
    }

    SECTION("Should decrease from middle to end") {
        for (size_t i = 11; i < 20; i++) {
            REQUIRE(window[i] > window[i + 1]);
        }
    }

    SECTION("Should be 0 outside of the window") {
        REQUIRE(window[20] == 0);
        REQUIRE(window[22] == 0);
        REQUIRE(window[45] == 0);
    }
}
