add_module(executor)

target_link_libraries(executor PUBLIC sim_hart sim_instruction sim_decoder sim_basic_block fmt::fmt)
target_sources(executor PRIVATE src/executor.cpp)