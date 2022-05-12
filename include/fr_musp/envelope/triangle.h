#ifndef FR_MUSP_TRIANGLE_H
#define FR_MUSP_TRIANGLE_H

#include <fr_musp/envelope/inverted_ramp.h>
#include <fr_musp/envelope/operator_based_iterator.h>
#include <fr_musp/envelope/ramp.h>

namespace fr_musp::envelope {

class Triangle {
  public:
    typedef OperatorBasedIterator<Triangle> iterator;

    Triangle(const std::chrono::duration<float> length,
             const unsigned int sampleRate)
        : _ramp(length / 2, sampleRate), _invertedRamp(length / 2, sampleRate),
          _sampleLength(floor(length.count() * (float)sampleRate)),
          _splitSample((unsigned int)_sampleLength / 2),
          _endIndex((unsigned int)_sampleLength - 1) {}

    float operator[](const unsigned int position) const {
        if (position < _splitSample) {
            return _ramp[position];
        } else {
            return _invertedRamp[position - _splitSample];
        }
    };

    iterator begin() { return {this}; }

    iterator end() { return {this, _endIndex + 1}; }

    unsigned int size() const { return _endIndex + 1; }

  private:
    Ramp _ramp;
    InvertedRamp _invertedRamp;
    float _sampleLength;
    unsigned int _endIndex;
    unsigned int _splitSample;
};

} // namespace fr_musp::envelope

#endif // FR_MUSP_TRIANGLE_H
