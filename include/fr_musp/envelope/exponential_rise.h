#ifndef FR_MUSP_EXPONENTIAL_RISE_H
#define FR_MUSP_EXPONENTIAL_RISE_H

#include <chrono>
#include <fr_musp/envelope/operator_based_iterator.h>

namespace fr_musp::envelope {

class ExponentialRise {
  public:
    typedef OperatorBasedIterator<ExponentialRise> iterator;

    ExponentialRise(const std::chrono::duration<float> duration,
                    const float curvature, const unsigned int sampleRate)
        : _duration(duration), _curvature(curvature), _sampleRate(sampleRate),
          _sampleLength(floor(_duration.count() * (float)_sampleRate)),
          _endIndex((unsigned int)_sampleLength - 1),
          _curvatureExponential(exp(_curvature)) {}

    float operator[](const unsigned int position) const {
        if (position == 0)
            return 0;
        if (position == _endIndex)
            return 1.0f;

        return (pow(_curvatureExponential,
                    (float)position * (1.0f / (float)_sampleRate)) -
                1) /
               (_curvatureExponential - 1);
    }

    iterator begin() { return {this}; }

    iterator end() { return {this, _endIndex + 1}; }

  private:
    std::chrono::duration<float> _duration;
    unsigned int _sampleRate;
    float _curvature;
    float _curvatureExponential;
    float _sampleLength;
    unsigned int _endIndex;
};

} // namespace fr_musp::envelope

#endif // FR_MUSP_EXPONENTIAL_RISE_H
