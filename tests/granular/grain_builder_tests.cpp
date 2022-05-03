#include <catch2/catch_test_macros.hpp>
#include <fr_musp/granular/grain_builder.h>

#include <numeric>

using namespace fr_musp::granular;
using namespace std;

TEST_CASE("The grain builder") {
    vector<float> samples;
    vector<vector<float>> expectedGrainData = {
        vector<float> {1, 2, 3, 4, 5, 6, 7, 2},
        vector<float> {0, 3, 5, 6, 7, 8, 9, 5},
        vector<float> {0, 4, 4, 6, 6, 8, 8, 4, 4, 6},
        vector<float> {0, 4, 4, 6, 6, 8, 8, 4},
    };
    auto numberOfSamples = accumulate(
        expectedGrainData.begin(),
        expectedGrainData.end(), 0,
        [](size_t count, vector<float> v){ return count + v.size(); });
    samples.reserve(numberOfSamples);
    for (auto &v : expectedGrainData) {
        samples.insert(samples.end(), v.begin(), v.end());
    }
    GrainBuilder builder(samples);

    SECTION("Should be able to create grains at 0 crossings") {}
}
