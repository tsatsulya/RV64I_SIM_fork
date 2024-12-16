add_module(basic_block)

target_link_libraries(basic_block PUBLIC sim_common sim_hart sim_instruction sim_decoder sim_logger fmt::fmt)

target_sources(basic_block PRIVATE src/basic_block.cpp
                                   src/basic_block_cache.cpp)