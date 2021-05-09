cmake_minimum_required(VERSION 3.10)

project(gemm LANGUAGES CXX)


add_library(gemm_ref gemm_ref.cpp)

add_executable(driver driver.cpp)

target_link_libraries(driver gemm_ref)

add_library(catch INTERFACE)
target_include_directories(catch INTERFACE "${CMAKE_CURRENT_SOURCE_DIRECTORY}/catch")

enable_testing()
add_executable(tests tests.cpp)
target_link_libraries(tests PRIVATE catch gemm_ref)
add_test(NAME Testicles COMMAND tests)
