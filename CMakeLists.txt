cmake_minimum_required(VERSION 3.14..3.26)

project(flame VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED OFF)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(ArrayFire REQUIRED)

add_library(flame ${CMAKE_CURRENT_LIST_DIR}/src/flame/raster.cpp)
target_include_directories(flame PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)
target_compile_options(flame PUBLIC $<IF:$<CONFIG:Debug>,-Wall -Wpedantic -Wextra,>)
target_link_libraries(flame INTERFACE ArrayFire::af)