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

class EnvelopeSegment {
  public:
    explicit EnvelopeSegment(EnvelopeGeneratorVariant &&envelope, float scale,
                             float offset)
        : _envelope(envelope), _scale(scale), _offset(offset) {}

    float operator[](const unsigned int position) const {
        if (std::holds_alternative<Constant>(_envelope)) {
            return std::get<Constant>(_envelope)[position] * _scale + _offset;
        } else if (std::holds_alternative<ExponentialFall>(_envelope)) {
            return std::get<ExponentialFall>(_envelope)[position] * _scale +
                   _offset;
        } else if (std::holds_alternative<ExponentialRise>(_envelope)) {
            return std::get<ExponentialRise>(_envelope)[position] * _scale +
                   _offset;
        } else if (std::holds_alternative<InvertedRamp>(_envelope)) {
            return std::get<InvertedRamp>(_envelope)[position] * _scale +
                   _offset;
        } else {
            throw std::exception("Unknown envelope type");
        }
    };

    OperatorBasedIterator<EnvelopeSegment> begin() { return {this}; }

    OperatorBasedIterator<EnvelopeSegment> end() { return {this, size()}; }

  private:
    EnvelopeGeneratorVariant _envelope;
    float _scale;
    float _offset;

    unsigned int size() {
        if (std::holds_alternative<Constant>(_envelope)) {
            return std::get<Constant>(_envelope).size();
        } else if (std::holds_alternative<ExponentialFall>(_envelope)) {
            return std::get<ExponentialFall>(_envelope).size();
        } else if (std::holds_alternative<ExponentialRise>(_envelope)) {
            return std::get<ExponentialRise>(_envelope).size();
        } else if (std::holds_alternative<InvertedRamp>(_envelope)) {
            return std::get<InvertedRamp>(_envelope).size();
        } else {
            throw std::exception("Unknown envelope type");
        }
    }
};

} // namespace fr_musp::envelope

#endif // FR_MUSP_ENVELOPE_SEGMENT_H
