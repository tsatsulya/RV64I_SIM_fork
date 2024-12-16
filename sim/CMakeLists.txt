set(TARGET_NAME sim)

add_executable(${TARGET_NAME} main.cpp)
target_link_libraries(${TARGET_NAME} PRIVATE sim_executor sim_instruction CLI11::CLI11)