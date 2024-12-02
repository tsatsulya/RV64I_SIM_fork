add_module(decoder)
target_link_libraries(decoder PUBLIC sim_logger sim_instruction sim_common fmt::fmt)
target_sources(decoder PRIVATE src/decoder.cpp)

add_subdirectory(tests)