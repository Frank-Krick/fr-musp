add_library(fr_musp
  ../include/fr_musp/pink_noise/pink_noise.h
  pink_noise/pink_noise.cpp
  ../include/fr_musp/white_noise/white_noise.h
  white_noise/white_noise.cpp
  ../include/fr_musp/binary_sequence/binary_sequence.h
  binary_sequence/binary_sequence.cpp
  ../include/fr_musp/granular/grain_builder.h
  ../include/fr_musp/granular/grain.h
  granular/grain.cpp
  ../include/fr_musp/window_functions/rectangular.h
  ../include/fr_musp/window_functions/triangular.h
  ../include/fr_musp/envelope/exponential_fall.h
  ../include/fr_musp/envelope/exponential_rise.h
  ../include/fr_musp/envelope/inverted_ramp.h
  ../include/fr_musp/envelope/logarithmic_fall.h
  ../include/fr_musp/envelope/logarithmic_rise.h
  ../include/fr_musp/envelope/pulse.h
  ../include/fr_musp/envelope/ramp.h
  ../include/fr_musp/envelope/triangle.h
  ../include/fr_musp/envelope/envelope_segment.h
  ../include/fr_musp/envelope/operator_based_iterator.h
  ../include/fr_musp/envelope/constant.h)

target_include_directories(fr_musp PUBLIC ../include)

target_compile_options(fr_musp PUBLIC /std:c++latest)