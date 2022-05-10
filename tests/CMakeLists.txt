add_executable(fr_musp_tests
  pink_noise/pink_noise_tests.cpp
  white_noise/white_noise_tests.cpp
  binary_sequence/binary_sequence_tests.cpp
  window_functions/rectangle_tests.cpp
  window_functions/triangular_tests.cpp
  granular/grain_tests.cpp
  granular/grain_builder_tests.cpp
  envelope/ramp_tests.cpp
  envelope/inverted_ramp_tests.cpp
  envelope/pulse_tests.cpp
  envelope/exponential_rise_tests.cpp
  envelope/operator_based_iterator_tests.cpp
  envelope/exponential_fall_tests.cpp
  envelope/constant_tests.cpp)

target_link_libraries(fr_musp_tests
  PRIVATE Catch2::Catch2WithMain
  PRIVATE fr_musp)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/contrib)
