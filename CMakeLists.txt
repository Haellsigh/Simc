cmake_minimum_required(VERSION 3.19)

project(Simc
  VERSION 0.1.0
  DESCRIPTION "Simulation and control environment"
  LANGUAGES CXX)

# Vcpkg as a submodule
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake CACHE STRING "Vcpkg toolchain file")

add_subdirectory(src)
