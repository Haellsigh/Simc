cmake_minimum_required(VERSION 3.19)

add_executable(${PROJECT_NAME} "")
target_sources(${PROJECT_NAME} PRIVATE
  main.cc
  mainwindow.hh
  mainwindow.cc
  mainwindow.ui
  variable.hh
)

add_subdirectory(utilities)

add_subdirectory(controller)
add_subdirectory(integrator)
add_subdirectory(observer)
add_subdirectory(sensor)
add_subdirectory(system)

add_subdirectory(thirdparty)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Copy assets to build directory
add_custom_command(TARGET Simc PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/assets/ $<TARGET_FILE_DIR:Simc>/assets/)

##### Compilation options
# C++20
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_EXTENSIONS OFF)
if (MSVC)
  target_compile_options(${PROJECT_NAME} PUBLIC /Zc:__cplusplus)
endif()
# Enable Link Time Optimization if available
include(CheckIPOSupported)
check_ipo_supported(RESULT result)
if(result)
  set_target_properties(${PROJECT_NAME} PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE)
  message(STATUS "Enabled Link Time optimization")
endif()
# Warnings
if(MSVC)
  target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else()
  target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra)
endif()

##### Libraries
# Qt
find_package(Qt5 COMPONENTS Widgets PrintSupport REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets Qt5::PrintSupport)

# Eigen
find_package(Eigen3 CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE Eigen3::Eigen)
