cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)

project(glib_util_strings_sample)


# Cpp, packages and modules
#=============================================================================

# Minimum Versions
set(GLIB_MINIMUM_VERSION "2.50.0")

message(STATUS "Building project '${PROJECT_NAME}'")

# additional cmake files
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

#include(GNUInstallDirs)

find_package(GLIB ${GLIB_MINIMUM_VERSION} REQUIRED)


# App version
#=============================================================================

set(SAMPLECLIENT_MAJOR_VERSION 0)
set(SAMPLECLIENT_MINOR_VERSION 1)
set(SAMPLECLIENT_PATCH_VERSION 0)
set(SAMPLECLIENT_VERSION ${SAMPLECLIENT_MAJOR_VERSION}.${SAMPLECLIENT_MINOR_VERSION}.${SAMPLECLIENT_PATCH_VERSION})
add_definitions(
    "-DSAMPLECLIENT_VERSION=\"${SAMPLECLIENT_VERSION}\""
)


# Common variables and definitions
#=============================================================================

set(SAMPLECLIENT_NAME "GlibUtilStringsSampleApp" CACHE STRING "application name")

set(SAMPLECLIENT_SOURCE_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")

set (CMAKE_CXX_STANDARD 11)


# Files
#=============================================================================

set(sampleclient_CPP_FILES
    ${SAMPLECLIENT_SOURCE_SRC_DIR}/main.cpp
)


# Target
#=============================================================================

add_executable(${SAMPLECLIENT_NAME}
    ${sampleclient_CPP_FILES}
)

target_link_libraries(${SAMPLECLIENT_NAME}
    ${GLIB_LIBRARIES}
)


target_include_directories(${SAMPLECLIENT_NAME}
    PRIVATE
        ${GLIB_INCLUDE_DIRS}
)


# Installation
#=============================================================================

# targets
install(TARGETS
    ${SAMPLECLIENT_NAME}
    COMPONENT Runtime
)
