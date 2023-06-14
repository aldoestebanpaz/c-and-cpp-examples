
cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)

project(assets-module)


# Cpp, packages and modules
#=============================================================================

# Minimum Versions
set(SHAREDMODULE_MINIMUM_VERSION "0.1.0")

find_package(aldos-shared-module ${SHAREDMODULE_MINIMUM_VERSION} REQUIRED)

include(GNUInstallDirs)
include(SmPreventInSourceBuilds)
include(SmConfigVars)

add_subdirectory(graphics)
add_subdirectory(icons)
