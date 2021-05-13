cmake_minimum_required(VERSION 3.10)

project(gemm LANGUAGES CXX)


add_library(gemm_ref gemm_ref.cpp)
add_library(gemm_compiler gemm_compiler_32_32_32_32_32_32.cpp)

add_executable(driver driver.cpp)

target_link_libraries(driver gemm_ref gemm_compiler)

add_library(catch INTERFACE)
target_include_directories(catch INTERFACE "${CMAKE_CURRENT_SOURCE_DIRECTORY}/catch")

enable_testing()
add_executable(tests tests.cpp)
target_link_libraries(tests PRIVATE catch gemm_ref gemm_compiler)
add_test(NAME Test COMMAND tests)

target_compile_options(gemm_ref PRIVATE -O3)
target_compile_options(gemm_compiler PRIVATE -O3)
