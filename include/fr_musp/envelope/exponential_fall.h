#ifndef FR_MUSP_EXPONENTIAL_FALL_H
#define FR_MUSP_EXPONENTIAL_FALL_H

#include <fr_musp/envelope/exponential_rise.h>

namespace fr_musp::envelope {

class ExponentialFall {
  public:
    ExponentialFall(const std::chrono::duration<float> duration,
                    const float curvature, const unsigned int sampleRate)
        : _sampleLength(floor(duration.count() * (float)sampleRate)),
          _endIndex((unsigned int)_sampleLength - 1),
          _exponentialRise(duration, curvature, sampleRate){};

    float operator[](const unsigned int position) const {
        if (position == 0)
            return 1.0f;
        if (position == _endIndex)
            return 0.0f;
        return _exponentialRise[_endIndex - position];
    }

    OperatorBasedIterator<ExponentialFall> begin() { return {this}; }

    OperatorBasedIterator<ExponentialFall> end() {
        return {this, _endIndex + 1};
    }

  private:
    ExponentialRise _exponentialRise;
    float _sampleLength;
    unsigned int _endIndex;
};

} // namespace fr_musp::envelope

#endif // FR_MUSP_EXPONENTIAL_FALL_H
