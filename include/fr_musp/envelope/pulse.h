#ifndef FR_MUSP_PULSE_H
#define FR_MUSP_PULSE_H

#include <fr_musp/envelope/operator_based_iterator.h>
#include <chrono>

namespace fr_musp::envelope {

class Pulse {
  public:
    Pulse(const std::chrono::duration<float> duration, float dutyCycle,
          const unsigned int sampleRate)
        : _duration(duration), _dutyCycle(dutyCycle), _sampleRate(sampleRate),
          _sampleLength(floor(_duration.count() * (float)_sampleRate)),
          _endIndex((unsigned int)_sampleLength - 1),
          _switchSample((unsigned int)floor(_dutyCycle * (float)_sampleRate)) {}

    float operator[](const unsigned int position) const {
        if (position < _switchSample)
            return 1.0f;
        else
            return 0.0f;
    }

    OperatorBasedIterator<Pulse> begin() { return {this}; }

    OperatorBasedIterator<Pulse> end() { return {this, _endIndex + 1}; }

  private:
    std::chrono::duration<float> _duration;
    unsigned int _sampleRate;
    float _dutyCycle;
    unsigned int _switchSample;
    float _sampleLength;
    unsigned int _endIndex;
};

} // namespace fr_musp::envelope

#endif // FR_MUSP_PULSE_H
