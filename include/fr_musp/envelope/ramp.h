#ifndef FR_MUSP_RAMP_H
#define FR_MUSP_RAMP_H

#include <chrono>

namespace fr_musp::envelope {

template <class Ramp> class RampIterator {
  public:
    typedef ptrdiff_t difference_type;
    typedef float value_type;
    typedef const float &reference;
    typedef const float *pointer;
    typedef std::bidirectional_iterator_tag iterator_category;

    explicit RampIterator(Ramp *rampPtr, const float slope)
        : _rampPtr(rampPtr), _position(0), _value(0), _slope(slope) {}

    explicit RampIterator(Ramp *rampPtr, const float slope,
                          unsigned int position, float value)
        : _rampPtr(rampPtr), _position(position), _value(value), _slope(slope) {
    }

    RampIterator(const RampIterator &iterator) = default;

    RampIterator() = default;

    ~RampIterator() = default;

    RampIterator<Ramp> &operator=(const RampIterator &) = default;

    RampIterator<Ramp> &operator++() {
        ++_position;
        _value += _slope;
        return *this;
    }

    RampIterator<Ramp> operator++(int) { // NOLINT(cert-dcl21-cpp)
        RampIterator<Ramp> iterator(_rampPtr, _position, _value);
        ++_position;
        _value += _slope;
        return iterator;
    }

    value_type operator*() const { return _value; };

    value_type operator->() const { return _value; };

    friend bool operator==(const RampIterator &left,
                           const RampIterator &right) {
        return left._position == right._position &&
               left._rampPtr == right._rampPtr;
    }
    friend bool operator!=(const RampIterator &left,
                           const RampIterator &right) = default;

  private:
    Ramp *_rampPtr;
    unsigned int _position;
    float _value;
    float _slope;
};

class Ramp {
  public:
    friend class RampIterator<Ramp>;

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
        return (float)position * _slope;
    }

    RampIterator<Ramp> begin() { return RampIterator<Ramp>(this, _slope); }

    RampIterator<Ramp> end() {
        return RampIterator<Ramp>(this, _slope, _endIndex + 1, 1.0f);
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
