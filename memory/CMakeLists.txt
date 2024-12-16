
add_module(memory)

target_link_libraries(memory PUBLIC sim_logger sim_common fmt::fmt)

target_sources(memory PRIVATE src/common_mem.cpp
                              src/memory.cpp
                              src/tlb.cpp
                              src/page_table_entry.cpp)
