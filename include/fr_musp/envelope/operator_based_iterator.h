#ifndef FR_MUSP_OPERATOR_BASED_ITERATOR_H
#define FR_MUSP_OPERATOR_BASED_ITERATOR_H

#include <iterator>

namespace fr_musp::envelope {

template <class Envelope> class OperatorBasedIterator {
  public:
    typedef ptrdiff_t difference_type;
    typedef float value_type;
    typedef const float &reference;
    typedef const float *pointer;
    typedef std::bidirectional_iterator_tag iterator_category;

    OperatorBasedIterator(Envelope *envelopePrt) : _envelopePtr(envelopePrt) {}

    OperatorBasedIterator(Envelope *envelopePrt, unsigned int position)
        : _envelopePtr(envelopePrt), _position(position) {}

    OperatorBasedIterator(const OperatorBasedIterator &) = default;

    OperatorBasedIterator() = default;

    ~OperatorBasedIterator() = default;

    OperatorBasedIterator<Envelope> &
    operator=(const OperatorBasedIterator &) = default;

    OperatorBasedIterator<Envelope> &operator++() {
        ++_position;
        return *this;
    }

    OperatorBasedIterator<Envelope> operator++(int) { // NOLINT(cert-dcl21-cpp)
        OperatorBasedIterator<Envelope> iterator(_envelopePtr, _position);
        ++_position;
        return iterator;
    }

    value_type operator*() const { return (*_envelopePtr)[_position]; };

    value_type operator->() const { return (*_envelopePtr)[_position]; };

    friend bool operator==(const OperatorBasedIterator &left,
                           const OperatorBasedIterator &right) = default;

    friend bool operator!=(const OperatorBasedIterator &left,
                           const OperatorBasedIterator &right) = default;

  private:
    Envelope *_envelopePtr;
    unsigned int _position{};
};

} // namespace fr_musp::envelope
#endif // FR_MUSP_OPERATOR_BASED_ITERATOR_H
