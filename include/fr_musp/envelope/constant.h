#ifndef FR_MUSP_CONSTANT_H
#define FR_MUSP_CONSTANT_H

#include <fr_musp/envelope/operator_based_iterator.h>

namespace fr_musp::envelope {

class Constant {
  public:
    typedef OperatorBasedIterator<Constant> iterator;

    Constant(const std::chrono::duration<float> duration,
             const unsigned int sampleRate)
        : _sampleLength(
              (unsigned int)floor(duration.count() * (float)sampleRate)),
          _endIndex(_sampleLength - 1) {}

    float operator[](const unsigned int position) const { return 1.0f; }

    iterator begin() { return {this}; }

    iterator end() { return {this, _endIndex + 1}; }

    unsigned int size() const { return _endIndex + 1; }

  private:
    unsigned int _sampleLength;
    unsigned int _endIndex;
};

} // namespace fr_musp::envelope

#endif // FR_MUSP_CONSTANT_H
