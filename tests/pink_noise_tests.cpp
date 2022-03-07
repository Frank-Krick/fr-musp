#include <catch2/catch_test_macros.hpp>
#include <utility>

#include <fr_musp/pink_noise/pink_noise.h>

using namespace fr_musp;

class TestNoiseSource {
public:
    unsigned int called;

    TestNoiseSource(): called(0) {}

    double operator()() {
        ++called;
        return called;
    };
};

TEST_CASE("Initialization") {
    TestNoiseSource noiseSource;

    SECTION("Should fill the white noise array") {
        std::array<double, 5> noiseSamples {};
        fill_white_noise_samples(noiseSource, noiseSamples);
        REQUIRE(noiseSamples == std::array<double, 5> {1, 2, 3, 4, 5});
    }

    SECTION("Should calculate the sum of all noise samples") {
        std::array<double, 5> noiseSamples {1, 2, 3, 4, 7};
        auto result = calculate_noise_sample_sum(noiseSamples);
        REQUIRE( result == (1.0 + 2.0 + 3.0 + 4.0 + 7.0) / 5.0);
    }
}

TEST_CASE("Calculating the next samples to update") {
    SECTION("Should calculate the noise samples to update when counter is 1") {
        auto result = calculate_noise_samples_to_update<5>(1);
        REQUIRE(result == std::pair<size_t, size_t> {0, 1});
    }

    SECTION("Should calculate the noise samples to update when counter is 2") {
        auto result = calculate_noise_samples_to_update<5>(2);
        REQUIRE(result == std::pair<size_t, size_t> {0, 2});
    }

    SECTION("Should calculate the noise samples to update when counter is 3") {
        auto result = calculate_noise_samples_to_update<5>(3);
        REQUIRE(result == std::pair<size_t, size_t> {0, 1});
    }

    SECTION("Should calculate the noise samples to update when counter is 4") {
        auto result = calculate_noise_samples_to_update<5>(4);
        REQUIRE(result == std::pair<size_t, size_t> {0, 3});
    }

    SECTION("Should calculate the indices to update when counter is max") {
        auto counter = maximum_counter_value<5>();
        auto result = calculate_noise_samples_to_update<5>(counter);
        REQUIRE(result == std::pair<size_t, size_t> {0, 4});
    }
}

TEST_CASE("Calculating the maximum counter") {
    SECTION("Should calculate the correct counter maximum") {
        auto maximumCounter = maximum_counter_value<4>();
        REQUIRE(maximumCounter == 8);
    }
}

class TestNoiseSource2 {
public:
    std::vector<double> numbers;

    explicit TestNoiseSource2(std::vector<double> initialNumbers): numbers(std::move(initialNumbers)) {}

    double operator()() {
        auto result = numbers.back();
        numbers.pop_back();
        return result;
    }
};

TEST_CASE("Should update the noise samples and current sum") {
    TestNoiseSource2 noiseSource({13, 7, 3});
    std::array<double, 5> noiseSamples {1, 1, 1, 1, 1};
    auto currentSum = std::accumulate(
        noiseSamples.begin(), noiseSamples.end(), 0.0) / 5.0;

    SECTION("Should update index 0 and 1") {
        auto sample = update_noise_samples_and_calculate_new_sum(
            noiseSource, currentSum, noiseSamples, {0, 1});
        std::array<double, 5> expectedArray {3, 7, 1, 1, 1};
        REQUIRE(noiseSamples == expectedArray);
        auto expected = calculate_noise_sample_sum<5>(expectedArray);
        REQUIRE(sample == expected);
    }
}

TEST_CASE("The pink noise generator generates noise") {
    PinkNoise<TestNoiseSource, 5> pinkNoise;

    SECTION("Returns a new noise value") {
        std::array<double, 5> expectedArray {6, 7, 3, 4, 5};
        auto sample = pinkNoise();
        auto expected = calculate_noise_sample_sum<5>(expectedArray);
        REQUIRE(sample == expected);
    }

    SECTION("Returns a second noise value") {
        std::array<double, 5> expectedArray {8, 7, 9, 4, 5};
        pinkNoise();
        auto sample = pinkNoise();
        auto expected = calculate_noise_sample_sum<5>(expectedArray);
        REQUIRE(sample == expected);
    }
}

TEST_CASE("Updates the counter") {
    PinkNoise<TestNoiseSource, 3> pinkNoise;

    SECTION("When it reaches the maximum") {
        std::array<double, 3> expectedArray {4, 5, 3};
        auto sample = pinkNoise();
        auto expected = calculate_noise_sample_sum<3>(expectedArray);
        REQUIRE(sample == expected);
        expectedArray = {6, 5, 7};
        sample = pinkNoise();
        expected = calculate_noise_sample_sum<3>(expectedArray);
        REQUIRE(sample == expected);
        expectedArray = {8, 9, 7};
        sample = pinkNoise();
        expected = calculate_noise_sample_sum<3>(expectedArray);
        REQUIRE(sample == expected);
        expectedArray = {10, 9, 11};
        sample = pinkNoise();
        expected = calculate_noise_sample_sum<3>(expectedArray);
        REQUIRE(sample == expected);
        expectedArray = {12, 13, 11};
        sample = pinkNoise();
        expected = calculate_noise_sample_sum<3>(expectedArray);
        REQUIRE(sample == expected);
    }
}