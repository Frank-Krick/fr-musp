#ifndef FR_MUSP_PULSE_H
#define FR_MUSP_PULSE_H

#include <chrono>

namespace fr_musp::envelope {

template <class Pulse> class PulseIterator {
  public:
    typedef ptrdiff_t difference_type;
    typedef float value_type;
    typedef const float &reference;
    typedef const float *pointer;
    typedef std::bidirectional_iterator_tag iterator_category;

    PulseIterator(Pulse *pulsePrt) : _pulsePtr(pulsePrt) {}

    PulseIterator(Pulse *pulsePrt, unsigned int position)
        : _pulsePtr(pulsePrt), _position(position) {}

    PulseIterator(const PulseIterator &) = default;

    PulseIterator() = default;

    ~PulseIterator() = default;

    PulseIterator<Pulse> &operator=(const PulseIterator &) = default;

    PulseIterator<Pulse> &operator++() {
        ++_position;
        return *this;
    }

    PulseIterator<Pulse> operator++(int) { // NOLINT(cert-dcl21-cpp)
        PulseIterator<Pulse> iterator(_pulsePtr, _position);
        ++_position;
        return iterator;
    }

    value_type operator*() const { return (*_pulsePtr)[_position]; };

    value_type operator->() const { return (*_pulsePtr)[_position]; };

    friend bool operator==(const PulseIterator &left,
                           const PulseIterator &right) = default;

    friend bool operator!=(const PulseIterator &left,
                           const PulseIterator &right) = default;

  private:
    Pulse *_pulsePtr;
    unsigned int _position{};
};

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

    PulseIterator<Pulse> begin() {
        return {this};
    }

    PulseIterator<Pulse> end() {
        return {this, _endIndex + 1};
    }

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
