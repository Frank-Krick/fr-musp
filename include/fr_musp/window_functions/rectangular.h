#ifndef FR_MUSP_RECTANGULAR_H
#define FR_MUSP_RECTANGULAR_H

namespace fr_musp {

namespace windows {

class Rectangular {
public:
    explicit Rectangular(size_t length): _length(length) {}

    float operator[](size_t position) const {
        if (position < _length) return 1;
        return 0;
    }

private:
    size_t _length;
};

} // namespace windows

} // namespace fr_musp

#endif //FR_MUSP_RECTANGULAR_H
