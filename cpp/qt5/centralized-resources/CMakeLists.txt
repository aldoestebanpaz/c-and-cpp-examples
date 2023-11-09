cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)

project(centralized-resources-sample)

message(STATUS "Building in SuperBuild mode.")
if (NOT DEFINED CMAKE_PREFIX_PATH AND NOT DEFINED ENV{CMAKE_PREFIX_PATH})
    message(FATAL_ERROR "CMAKE_PREFIX_PATH environment variable not set. When configuring for the first time, make sure CMAKE_PREFIX_PATH is set to the root of the build directory. It can be done by passing it to cmake as an command line parameter (e.g. cmake -DCMAKE_PREFIX_PATH=path_to_your_build_dir ..) OR by setting the CMAKE_PREFIX_PATH environment variable (e.g. export CMAKE_PREFIX_PATH=path_to_your_build_dir ..).")
endif()

add_subdirectory(shared-module)
add_subdirectory(libcentralizedresources)
add_subdirectory(assets-module)
add_subdirectory(sample-app-01)
