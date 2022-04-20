#ifndef FR_MUSP_TRIANGULAR_H
#define FR_MUSP_TRIANGULAR_H

#include <cmath>

namespace fr_musp {

namespace windows {

class Triangular {
public:
    explicit Triangular(size_t length):
        _length(length),
        _halfLength((double) _length / 2.0),
        _halfLengthPlusOne((double) (_length + 1) / 2.0) {}

    double operator[](size_t position) {
        if (position < _length) return 1 - abs(((double) position - _halfLength) / _halfLengthPlusOne);
        return 0;
    }

private:
    size_t _length;
    double _halfLength;
    double _halfLengthPlusOne;
};

} // namespace windows

} // namespace fr_musp

#endif //FR_MUSP_TRIANGULAR_H
