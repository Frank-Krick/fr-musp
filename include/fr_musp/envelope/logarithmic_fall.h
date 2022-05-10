#ifndef FR_MUSP_LOGARITHMIC_FALL_H
#define FR_MUSP_LOGARITHMIC_FALL_H

#include <fr_musp/envelope/exponential_rise.h>

namespace fr_musp::envelope {

class LogarithmicFall {
  public:
    LogarithmicFall(const std::chrono::duration<float> duration,
                    const float curvature, const unsigned int sampleRate)
        : _sampleLength(floor(duration.count() * (float)sampleRate)),
          _endIndex((unsigned int)_sampleLength - 1),
          _exponentialFall(duration, curvature, sampleRate){};

    float operator[](const unsigned int position) const {
        return 1.0f - _exponentialFall[position];
    };

    OperatorBasedIterator<LogarithmicFall> begin() { return {this}; }

    OperatorBasedIterator<LogarithmicFall> end() {
        return {this, _endIndex + 1};
    }

  private:
    ExponentialRise _exponentialFall;
    float _sampleLength;
    unsigned int _endIndex;
};

} // namespace fr_musp::envelope

#endif // FR_MUSP_LOGARITHMIC_FALL_H
