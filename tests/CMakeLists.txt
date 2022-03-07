add_executable(fr_musp_tests pink_noise_tests.cpp)

target_link_libraries(fr_musp_tests
  PRIVATE Catch2::Catch2WithMain
  PRIVATE fr_musp)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/contrib)
