#ifndef FR_MUSP_RAMP_H
#define FR_MUSP_RAMP_H

#include <chrono>

namespace fr_musp::envelope {

class Ramp {
  public:
    Ramp(const std::chrono::duration<float> duration,
         const unsigned int sampleRate)
        : _sampleRate(sampleRate), _duration(duration),
          _sampleLength(floor(_duration.count() * (float)_sampleRate)),
          _endIndex((unsigned int)_sampleLength - 1),
          _slope(1.0f / _sampleLength) {}

    float operator[](const unsigned int position) const {
        if (position == 0)
            return 0.0f;
        if (position == _endIndex)
            return 1.0f;
        return (float)position * _sampleLength;
    }

  private:
    std::chrono::duration<float> _duration;
    unsigned int _sampleRate;
    float _sampleLength;
    unsigned int _endIndex;
    float _slope;
};

} // namespace fr_musp::envelope

#endif // FR_MUSP_RAMP_H
