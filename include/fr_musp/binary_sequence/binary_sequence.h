#ifndef FR_MUSP_BINARY_SEQUENCE_H
#define FR_MUSP_BINARY_SEQUENCE_H

#include <bitset>

namespace fr_musp {

template<size_t _sequence_length>
class BinarySequence {
public:
    BinarySequence() : _sequence(0), _currentPosition(0), _loopLength(_sequence_length) {};

    bool operator()() {
        auto value = _sequence[_currentPosition];
        _currentPosition = ++_currentPosition % _loopLength;
        return value;
    }

    void setValue(unsigned int value) {
        _sequence = value;
    }

    void setLoopLength(size_t loopLength) {
        _loopLength = loopLength;
        _currentPosition = _currentPosition % _loopLength;
    }

private:
    std::bitset<_sequence_length> _sequence;
    size_t _currentPosition;
    size_t _loopLength;
};

} // namespace fr_musp

#endif //FR_MUSP_BINARY_SEQUENCE_H
