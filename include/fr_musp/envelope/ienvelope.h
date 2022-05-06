#ifndef FR_MUSP_IENVELOPE_H
#define FR_MUSP_IENVELOPE_H

namespace fr_musp::envelope {

class IEnvelope {
public:
    explicit IEnvelope(const size_t sampleRateHz): _sampleRateHz(sampleRateHz) {}

    virtual float operator[](size_t position) = 0;
    virtual float size() = 0;

protected:
    size_t _sampleRateHz{0};
};

} // namespace fr_musp::envelope

#endif //FR_MUSP_IENVELOPE_H
