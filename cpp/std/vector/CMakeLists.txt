cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)

project(std_vector_sample)


message(STATUS "Building project '${PROJECT_NAME}'")

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

set(SAMPLECLIENT_NAME "StdVectorApp" CACHE STRING "application name")

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


# Installation
#=============================================================================

# targets
install(TARGETS
    ${SAMPLECLIENT_NAME}
    COMPONENT Runtime
)
