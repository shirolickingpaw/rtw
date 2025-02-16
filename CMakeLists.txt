cmake_minimum_required(VERSION 3.15)

project(weekend_ray_tracing VERSION 1.0.0)
set(CMAKE_OSX_ARCHITECTURES "arm64")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(out 
    src/main.cpp
    src/helper.cpp
    src/color.cpp
    src/ray.cpp
    src/sphere.cpp
    src/hittable_list.cpp
    src/camera.cpp
    src/interval.cpp
    src/material.cpp
)

# Enable vcpkg manifest mode
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake CACHE STRING "")

find_package(fmt CONFIG REQUIRED)
target_link_libraries(out PRIVATE fmt::fmt)

find_package(Armadillo CONFIG REQUIRED)
target_link_libraries(out PRIVATE armadillo)
