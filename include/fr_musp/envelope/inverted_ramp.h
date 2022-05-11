#ifndef FR_MUSP_INVERTED_RAMP_H
#define FR_MUSP_INVERTED_RAMP_H

#include <fr_musp/envelope/ramp.h>

namespace fr_musp::envelope {

template <class Ramp, class InvertedRamp> class InvertedRampIterator {
  public:
    typedef ptrdiff_t difference_type;
    typedef float value_type;
    typedef const float &reference;
    typedef const float *pointer;
    typedef std::bidirectional_iterator_tag iterator_category;

    explicit InvertedRampIterator(RampIterator<Ramp> rampIterator)
        : _rampIterator(rampIterator) {}

    InvertedRampIterator() = default;

    ~InvertedRampIterator() = default;

    InvertedRampIterator<Ramp, InvertedRamp> &
    operator=(const InvertedRampIterator &) = default;

    InvertedRampIterator<Ramp, InvertedRamp> &operator++() {
        ++_rampIterator;
        return *this;
    }

    InvertedRampIterator<Ramp, InvertedRamp> // NOLINT(cert-dcl21-cpp)
    operator++(int) {
        InvertedRampIterator<Ramp, InvertedRamp> iterator(_rampIterator);
        ++_rampIterator;
        return iterator;
    }

    value_type operator*() const { return 1.0f - *_rampIterator; };

    value_type operator->() const { return 1.0f - *_rampIterator; };

    friend bool operator==(const InvertedRampIterator &left,
                           const InvertedRampIterator &right) = default;

    friend bool operator!=(const InvertedRampIterator &left,
                           const InvertedRampIterator &right) = default;

  private:
    RampIterator<Ramp> _rampIterator;
};

class InvertedRamp {
  public:
    typedef InvertedRampIterator<Ramp, InvertedRamp> iterator;

    InvertedRamp(const std::chrono::duration<float> duration,
                 const unsigned int sampleRate)
        : _ramp(duration, sampleRate) {}

    float operator[](unsigned int position) const {
        return 1.0f - _ramp[position];
    }

    iterator begin() {
        return InvertedRampIterator<Ramp, InvertedRamp>(_ramp.begin());
    }

    iterator end() {
        return InvertedRampIterator<Ramp, InvertedRamp>(_ramp.end());
    }

    unsigned int size() { return _ramp.size(); };

  private:
    Ramp _ramp;
};

} // namespace fr_musp::envelope

#endif // FR_MUSP_INVERTED_RAMP_H
