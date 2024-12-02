add_module(hart)

add_library(elfio_lib INTERFACE)
target_include_directories(elfio_lib INTERFACE ${PROJECT_SOURCE_DIR}/../ELFIO)

target_link_libraries(hart PUBLIC sim_memory sim_common elfio_lib)
target_sources(hart PRIVATE src/hart.cpp)