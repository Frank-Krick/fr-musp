#ifndef FR_MUSP_WHITE_NOISE_H
#define FR_MUSP_WHITE_NOISE_H

#include <cstdint>

class WhiteNoise {
public:
    WhiteNoise(): _randomSeed(1) {}

    double operator()() {
        _randomSeed *= 16807;
        return _randomSeed * _coefficient;
    }

private:
    static constexpr double _coefficient = 4.6566129e-010;
    int32_t _randomSeed;
};

#endif //FR_MUSP_WHITE_NOISE_H
