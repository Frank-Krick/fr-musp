#ifndef FR_MUSP_GRAIN_H
#define FR_MUSP_GRAIN_H

#include <span>

namespace fr_musp::granular {

template<class Grain>
class GrainIterator {
public:
    typedef ptrdiff_t difference_type;
    typedef float value_type;
    typedef const float& reference;
    typedef const float* pointer;
    typedef std::bidirectional_iterator_tag iterator_category;

    explicit GrainIterator(Grain * grainPtr):
        _grainPtr(grainPtr),
        _position(0) {};

    GrainIterator(Grain * grainPtr, size_t position):
        _grainPtr(grainPtr),
        _position(position) {};

    GrainIterator(const GrainIterator& iterator) = default;

    GrainIterator() = default;

    ~GrainIterator() = default;

    GrainIterator<Grain>& operator=(const GrainIterator&) = default;
    GrainIterator<Grain>& operator++() {
        ++_position;
        return *this;
    };

    GrainIterator<Grain> operator++(int) { // NOLINT(cert-dcl21-cpp)
        GrainIterator<Grain> iterator(_grainPtr, _position);
        ++_position;
        return iterator;
    };

    GrainIterator<Grain>& operator--() {
        --_position;
        return *this;
    }

    GrainIterator<Grain> operator--(int) { // NOLINT(cert-dcl21-cpp)
        GrainIterator<Grain> iterator(_grainPtr, _position);
        --_position;
        return iterator;
    };

    value_type operator*() const {
        return (*_grainPtr)[_position];
    };

    value_type operator->() const {
        return (*_grainPtr)[_position];
    };

    friend bool operator==(const GrainIterator&, const GrainIterator&) = default;
    friend bool operator!=(const GrainIterator&, const GrainIterator&) = default;

private:
    Grain * _grainPtr;
    size_t _position{0};
};

template<class Window>
class Grain {
public:
    explicit Grain(std::span<float> samples):
        _samples(samples),
        _window(samples.size()) {}

    float operator[](size_t position) const {
        return _samples[position] * _window[position];
    }

    GrainIterator<Grain<Window>> begin() {
        return GrainIterator<Grain<Window>>(this);
    }

    GrainIterator<Grain<Window>> end() {
        return GrainIterator<Grain<Window>>(this, _samples.size());
    }

private:
    std::span<float> _samples;
    Window _window;
};

} // namespace fr_musp::granular

#endif //FR_MUSP_GRAIN_H
