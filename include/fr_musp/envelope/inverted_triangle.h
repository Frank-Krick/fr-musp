#ifndef FR_MUSP_INVERTED_TRIANGLE_H
#define FR_MUSP_INVERTED_TRIANGLE_H

#include <fr_musp/envelope/triangle.h>

namespace fr_musp::envelope {

class InvertedTriangle {
  public:
    typedef OperatorBasedIterator<InvertedTriangle> iterator;
    InvertedTriangle(const std::chrono::duration<float> length,
                     const unsigned int sampleRate)
        : _triangle(length, sampleRate) {}

    float operator[](const unsigned int position) const {
        return 1.0f - _triangle[position];
    };

    iterator begin() { return {this}; }

    iterator end() { return {this, _triangle.size()}; }

    unsigned int size() const { return _triangle.size(); };

  private:
    Triangle _triangle;
};

} // namespace fr_musp::envelope
#endif // FR_MUSP_INVERTED_TRIANGLE_H
