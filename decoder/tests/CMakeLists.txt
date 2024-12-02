find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
enable_testing()


add_executable(decoder_tests)
target_link_libraries(decoder_tests PRIVATE GTest::GTest GTest::Main sim_decoder sim_common)

target_sources(decoder_tests PRIVATE src/decoder_tests.cpp)
