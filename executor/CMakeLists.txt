add_module(executor)

target_link_libraries(executor PUBLIC sim_hart sim_instruction sim_decoder)
target_sources(executor PRIVATE src/executor.cpp)