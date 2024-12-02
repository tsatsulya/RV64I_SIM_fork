cmake_minimum_required(VERSION 3.27)

project(RV64I_SIM LANGUAGES CXX)

if (${PROJECT_SOURCE_DIR} STREQUAL ${PROJECT_BINARY_DIR})
    message(FATAL_ERROR "In-source build is forbidden")
endif()

find_package(CLI11 REQUIRED)
find_package(fmt REQUIRED)
find_package(Boost COMPONENTS log REQUIRED)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS        OFF)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)

function(add_module MODULE_NAME)
    add_library(${MODULE_NAME})
    add_library(sim_${MODULE_NAME} ALIAS ${MODULE_NAME})
    target_include_directories(${MODULE_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
endfunction(add_module)

function(add_header_only_module MODULE_NAME)
    add_library(${MODULE_NAME} INTERFACE)
    add_library(sim_${MODULE_NAME} ALIAS ${MODULE_NAME})
    target_include_directories(${MODULE_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
endfunction(add_header_only_module)

add_subdirectory(executor)
add_subdirectory(instruction)
add_subdirectory(memory)
add_subdirectory(logger)
add_subdirectory(hart)
add_subdirectory(decoder)
add_subdirectory(common)

set(TARGET_NAME sim)
add_executable(${TARGET_NAME} main.cpp)
target_link_libraries(${TARGET_NAME} PUBLIC sim_executor CLI11::CLI11)
