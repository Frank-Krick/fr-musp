#ifndef FR_MUSP_ENVELOPE_SEGMENT_H
#define FR_MUSP_ENVELOPE_SEGMENT_H

#include <fr_musp/envelope/constant.h>
#include <fr_musp/envelope/exponential_fall.h>
#include <fr_musp/envelope/exponential_rise.h>
#include <fr_musp/envelope/inverted_ramp.h>
#include <fr_musp/envelope/inverted_triangle.h>
#include <fr_musp/envelope/logarithmic_fall.h>
#include <fr_musp/envelope/logarithmic_rise.h>
#include <fr_musp/envelope/pulse.h>
#include <fr_musp/envelope/ramp.h>
#include <fr_musp/envelope/triangle.h>

#include <chrono>
#include <variant>

namespace fr_musp::envelope {

typedef std::variant<ExponentialFall, ExponentialRise, InvertedRamp,
                     LogarithmicFall, LogarithmicRise, Pulse, Ramp, Triangle,
                     InvertedTriangle, Constant>
    EnvelopeGeneratorVariant;

typedef std::variant<ExponentialFall::iterator, ExponentialRise::iterator,
                     InvertedRamp::iterator, LogarithmicFall::iterator,
                     LogarithmicRise::iterator, Pulse::iterator, Ramp::iterator,
                     Triangle::iterator, InvertedTriangle::iterator,
                     Constant::iterator>
    EnvelopeGeneratorIteratorVariant;

template <class EnvelopeSegment> class EnvelopeSegmentIterator {
  public:
    typedef ptrdiff_t difference_type;
    typedef float value_type;
    typedef const float &reference;
    typedef const float *pointer;
    typedef std::forward_iterator_tag iterator_category;

    EnvelopeSegmentIterator(EnvelopeGeneratorIteratorVariant &&iterator)
        : _iteratorVariant(iterator) {}

    ~EnvelopeSegmentIterator() = default;

    EnvelopeSegmentIterator &
    operator=(const EnvelopeSegmentIterator &) = default;

    EnvelopeSegmentIterator &operator++() {
        ++std::get<Constant::iterator>(_iteratorVariant);
        return *this;
    }

    EnvelopeSegmentIterator operator++(int) {
        EnvelopeSegmentIterator iterator(_iteratorVariant);
        ++std::get<Constant::iterator>(_iteratorVariant);
        return iterator;
    }

    value_type operator*() const {
        return *std::get<Constant::iterator>(_iteratorVariant);
    };

    value_type operator->() const {
        return *std::get<Constant::iterator>(_iteratorVariant);
    };

    friend bool operator==(const EnvelopeSegmentIterator &left,
                           const EnvelopeSegmentIterator &right) = default;

    friend bool operator!=(const EnvelopeSegmentIterator &left,
                           const EnvelopeSegmentIterator &right) = default;

  private:
    EnvelopeGeneratorIteratorVariant _iteratorVariant;
};

class EnvelopeSegment {
  public:
    explicit EnvelopeSegment(EnvelopeGeneratorVariant &&envelope, float scale,
                             float offset)
        : _envelope(envelope), _scale(scale), _offset(offset) {}

    float operator[](const unsigned int position) const {
        return std::get<Constant>(_envelope)[position] * _scale + _offset;
    };

    EnvelopeSegmentIterator<EnvelopeSegment> begin() {
        return {std::get<Constant>(_envelope).begin()};
    }

    EnvelopeSegmentIterator<EnvelopeSegment> end() {
        return {std::get<Constant>(_envelope).end()};
    }

  private:
    EnvelopeGeneratorVariant _envelope;
    float _scale;
    float _offset;
};

} // namespace fr_musp::envelope

#endif // FR_MUSP_ENVELOPE_SEGMENT_H
