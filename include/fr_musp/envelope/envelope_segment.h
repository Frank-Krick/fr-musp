#ifndef FR_MUSP_ENVELOPE_SEGMENT_H
#define FR_MUSP_ENVELOPE_SEGMENT_H

#include <fr_musp/envelope/exponential_fall.h>
#include <fr_musp/envelope/exponential_rise.h>
#include <fr_musp/envelope/inverted_ramp.h>
#include <fr_musp/envelope/logarithmic_fall.h>
#include <fr_musp/envelope/logarithmic_rise.h>
#include <fr_musp/envelope/pulse.h>
#include <fr_musp/envelope/ramp.h>
#include <fr_musp/envelope/triangle.h>

#include <chrono>
#include <variant>

namespace fr_musp::envelope {

typedef std::variant<ExponentialFall, ExponentialRise, InvertedRamp,
                     LogrithmicFall, LogarithmicRise, Pulse, Ramp, Triangle>
    EnvelopeGenerator;

class EnvelopeSegment {
  public:

  private:
    EnvelopeGenerator _generator;
};

} // namespace fr_musp::envelope

#endif // FR_MUSP_ENVELOPE_SEGMENT_H
