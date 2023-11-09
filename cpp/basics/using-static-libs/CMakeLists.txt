cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)

project(using_static_libs_sample)


# Cpp, packages and modules
#=============================================================================

set(GLIB_MINIMUM_VERSION "2.50.0")

message(STATUS "Building project '${PROJECT_NAME}'")

#find_package(GLIB ${GLIB_MINIMUM_VERSION} REQUIRED)
#find_package(PkgConfig REQUIRED)

#pkg_check_modules(
#    GLIB_JSON
#    json-glib-1.0
#    REQUIRED
#)


# App version
#=============================================================================

set(SAMPLEAPP_MAJOR_VERSION 0)
set(SAMPLEAPP_MINOR_VERSION 1)
set(SAMPLEAPP_PATCH_VERSION 0)
set(SAMPLEAPP_VERSION ${SAMPLEAPP_MAJOR_VERSION}.${SAMPLEAPP_MINOR_VERSION}.${SAMPLEAPP_PATCH_VERSION})
add_definitions(
    "-DSAMPLEAPP_VERSION=\"${SAMPLEAPP_VERSION}\""
)


# Modules
#=============================================================================

add_subdirectory(lib-in-c)
add_subdirectory(lib-in-cpp-with-mangling)
add_subdirectory(lib-in-cpp-without-mangling)
add_subdirectory(app)
