add_library(fr_musp
  ../include/fr_musp/pink_noise/pink_noise.h
  pink_noise/pink_noise.cpp
  ../include/fr_musp/white_noise/white_noise.h
  white_noise/white_noise.cpp
  ../include/fr_musp/binary_sequence/binary_sequence.h
  binary_sequence/binary_sequence.cpp)

target_include_directories(fr_musp PUBLIC ../include)
