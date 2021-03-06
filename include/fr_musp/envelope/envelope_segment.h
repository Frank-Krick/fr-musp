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

typedef std::variant<std::monostate, ExponentialFall, ExponentialRise,
                     InvertedRamp, LogarithmicFall, LogarithmicRise, Pulse,
                     Ramp, Triangle, InvertedTriangle, Constant>
    EnvelopeGeneratorVariant;

class EnvelopeSegment {
  public:
    EnvelopeSegment() = default;

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
        } else if (std::holds_alternative<LogarithmicFall>(_envelope)) {
            return std::get<LogarithmicFall>(_envelope)[position] * _scale +
                   _offset;
        } else if (std::holds_alternative<LogarithmicRise>(_envelope)) {
            return std::get<LogarithmicRise>(_envelope)[position] * _scale +
                   _offset;
        } else if (std::holds_alternative<Pulse>(_envelope)) {
            return std::get<Pulse>(_envelope)[position] * _scale + _offset;
        } else if (std::holds_alternative<Ramp>(_envelope)) {
            return std::get<Ramp>(_envelope)[position] * _scale + _offset;
        } else if (std::holds_alternative<Triangle>(_envelope)) {
            return std::get<Triangle>(_envelope)[position] * _scale + _offset;
        } else if (std::holds_alternative<InvertedTriangle>(_envelope)) {
            return std::get<InvertedTriangle>(_envelope)[position] * _scale +
                   _offset;
        } else {
            throw std::exception("Unknown envelope type");
        }
    };

    OperatorBasedIterator<EnvelopeSegment> begin() { return {this}; }

    OperatorBasedIterator<EnvelopeSegment> end() { return {this, size()}; }

    [[nodiscard]] bool empty() const {
        return std::holds_alternative<std::monostate>(_envelope);
    }

    [[nodiscard]] unsigned int size() const {
        if (std::holds_alternative<std::monostate>(_envelope)) {
            return false;
        } else if (std::holds_alternative<Constant>(_envelope)) {
            return std::get<Constant>(_envelope).size();
        } else if (std::holds_alternative<ExponentialFall>(_envelope)) {
            return std::get<ExponentialFall>(_envelope).size();
        } else if (std::holds_alternative<ExponentialRise>(_envelope)) {
            return std::get<ExponentialRise>(_envelope).size();
        } else if (std::holds_alternative<InvertedRamp>(_envelope)) {
            return std::get<InvertedRamp>(_envelope).size();
        } else if (std::holds_alternative<LogarithmicFall>(_envelope)) {
            return std::get<LogarithmicFall>(_envelope).size();
        } else if (std::holds_alternative<LogarithmicRise>(_envelope)) {
            return std::get<LogarithmicRise>(_envelope).size();
        } else if (std::holds_alternative<Pulse>(_envelope)) {
            return std::get<Pulse>(_envelope).size();
        } else if (std::holds_alternative<Ramp>(_envelope)) {
            return std::get<Ramp>(_envelope).size();
        } else if (std::holds_alternative<Triangle>(_envelope)) {
            return std::get<Triangle>(_envelope).size();
        } else if (std::holds_alternative<InvertedTriangle>(_envelope)) {
            return std::get<InvertedTriangle>(_envelope).size();
        } else {
            throw std::exception("Unknown envelope type");
        }
    }

  private:
    EnvelopeGeneratorVariant _envelope;
    float _scale{};
    float _offset{};
};

} // namespace fr_musp::envelope

#endif // FR_MUSP_ENVELOPE_SEGMENT_H
