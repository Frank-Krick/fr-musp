#ifndef FR_MUSP_GRANULATOR_H
#define FR_MUSP_GRANULATOR_H

#include <fr_musp/granular/grain.h>

#include <span>

namespace fr_musp::granular {

class GrainBuilder {
public:
    explicit GrainBuilder(std::span<float> samples): _samples(samples) {}

    template <class Window>
    Grain<Window> build() {};

private:
    std::span<float> _samples;
};

} // namespace fr_musp::granular

#endif //FR_MUSP_GRANULATOR_H
