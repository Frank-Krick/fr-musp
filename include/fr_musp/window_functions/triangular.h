#ifndef FR_MUSP_TRIANGULAR_H
#define FR_MUSP_TRIANGULAR_H

#include <cmath>

namespace fr_musp {

namespace windows {

class Triangular {
public:
    explicit Triangular(size_t length):
        _length(length),
        _halfLength((float) _length / 2.0f),
        _halfLengthPlusOne((float) (_length + 1) / 2.0f) {}

    float operator[](size_t position) const {
        if (position < _length) return 1.0f - abs(((float) position - _halfLength) / _halfLengthPlusOne);
        return 0;
    }

private:
    size_t _length;
    float _halfLength;
    float _halfLengthPlusOne;
};

} // namespace windows

} // namespace fr_musp

#endif //FR_MUSP_TRIANGULAR_H
