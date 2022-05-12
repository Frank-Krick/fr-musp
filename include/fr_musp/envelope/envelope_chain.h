#ifndef FR_MUSP_ENVELOPE_CHAIN_H
#define FR_MUSP_ENVELOPE_CHAIN_H

#include <fr_musp/envelope/envelope_segment.h>

#include <array>
#include <numeric>

namespace fr_musp::envelope {

template <unsigned int _maximumChainLength> class EnvelopeChain {
  public:
    EnvelopeChain() = default;

    void set(unsigned int index, EnvelopeSegment envelopeSegment) {
        _segments[index] = envelopeSegment;
    }

    float operator[](unsigned int position) const {
        auto iterator = _segments.begin();
        unsigned int sum = 0;
        while (iterator->size() == 0 || iterator->size() + sum < position) {
            sum += iterator->size();
            iterator++;
            if (iterator == _segments.end()) {
                throw std::exception("Index out of bounds");
            }
        }
        return (*iterator)[position - sum];
    }

    unsigned int size() {
        return std::accumulate(_segments.begin(), _segments.end(), 0,
                               [](unsigned int sum, EnvelopeSegment &segment) {
                                   return segment.size() + sum;
                               });
    }

    OperatorBasedIterator<EnvelopeChain> begin() { return {this}; }

    OperatorBasedIterator<EnvelopeChain> end() { return {this, size()}; }

  private:
    std::array<EnvelopeSegment, _maximumChainLength> _segments{};
};

} // namespace fr_musp::envelope

#endif // FR_MUSP_ENVELOPE_CHAIN_H
