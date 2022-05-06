#ifndef FR_MUSP_PINK_NOISE_H
#define FR_MUSP_PINK_NOISE_H

#include <array>
#include <bitset>
#include <cmath>
#include <numeric>

namespace fr_musp {

template <class TNoiseSource, size_t _number_of_white_noise_sources>
void fill_white_noise_samples(
    TNoiseSource &noiseSource,
    std::array<double, _number_of_white_noise_sources> &noiseSamples) {

    std::generate(noiseSamples.begin(), noiseSamples.end(),
                  [&noiseSource] { return noiseSource(); });
}

template <size_t _number_of_white_noise_sources>
double calculate_noise_sample_sum(
    const std::array<double, _number_of_white_noise_sources> &noiseSamples) {
    return std::accumulate(noiseSamples.begin(), noiseSamples.end(), 0) /
           (double)_number_of_white_noise_sources;
}

template <size_t _number_of_white_noise_sources>
std::pair<size_t, size_t> calculate_noise_samples_to_update(size_t counter) {
    std::bitset<_number_of_white_noise_sources - 1> bitset(counter);
    size_t count(0);
    for (size_t i = 0; i < _number_of_white_noise_sources - 1; i++) {
        ++count;
        if (bitset[i] == 1)
            return {0, count};
    }
    return {0, count};
}

template <size_t _number_of_white_noise_sources>
constexpr size_t maximum_counter_value() {
    return pow(2, _number_of_white_noise_sources - 1);
}

template <class TNoiseSource, size_t _number_of_white_noise_sources>
double update_noise_samples_and_calculate_new_sum(
    TNoiseSource &noiseSource, const double currentSum,
    std::array<double, _number_of_white_noise_sources> &noiseSamples,
    std::pair<size_t, size_t> noiseSamplesToUpdate) {

    std::pair<double, double> oldValues(
        noiseSamples[noiseSamplesToUpdate.first],
        noiseSamples[noiseSamplesToUpdate.second]);

    auto firstRandom = noiseSource();
    auto secondRandom = noiseSource();

    noiseSamples[noiseSamplesToUpdate.first] = firstRandom;
    noiseSamples[noiseSamplesToUpdate.second] = secondRandom;

    return currentSum +
           (firstRandom + secondRandom - oldValues.first - oldValues.second) /
               (double)_number_of_white_noise_sources;
}

/*
 * PinkNoise uses the Voss algorithm to calculate pink noise, a noise with
 * a 3 dB/oct rolloff, by sampling a white noise source multiple times per
 * octave as described in: https://www.firstpr.com.au/dsp/pink-noise/
 */
template <class TNoiseSource, size_t _number_of_white_noise_sources>
class PinkNoise {
  public:
    PinkNoise()
        : _currentCounter(0),
          _maximumCounter(
              maximum_counter_value<_number_of_white_noise_sources>()) {
        fill_white_noise_samples(_noiseSource, _noiseSamples);
        _currentSum = calculate_noise_sample_sum(_noiseSamples);
    }

    double operator()() {
        ++_currentCounter;
        if (_currentCounter > _maximumCounter)
            _currentCounter = 1;
        auto sampleIndexToUpdate =
            calculate_noise_samples_to_update<_number_of_white_noise_sources>(
                _currentCounter);
        _currentSum = update_noise_samples_and_calculate_new_sum(
            _noiseSource, _currentSum, _noiseSamples, sampleIndexToUpdate);
        return _currentSum;
    }

  private:
    std::array<double, _number_of_white_noise_sources> _noiseSamples{};
    TNoiseSource _noiseSource{};
    double _currentSum;
    size_t _maximumCounter;
    size_t _currentCounter;
};

} // namespace fr_musp

#endif // FR_MUSP_PINK_NOISE_H
