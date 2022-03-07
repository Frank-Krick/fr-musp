add_library(fr_musp
  pink_noise/pink_noise.cpp
  ../include/fr_musp/pink_noise/pink_noise.h
  white_noise/white_noise.cpp
  ../include/fr_musp/white_noise/white_noise.h)

target_include_directories(fr_musp PUBLIC ../include)
