cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)

project(shared-module)


# Cpp, packages and modules
#=============================================================================

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

include(cmake/modules/SmPreventInSourceBuilds.cmake)


# Shared module version
#=============================================================================

set(SHARED_MODULE_MAJOR_VERSION 0)
set(SHARED_MODULE_MINOR_VERSION 1)
set(SHARED_MODULE_PATCH_VERSION 0)
set(SHARED_MODULE_VERSION ${SHARED_MODULE_MAJOR_VERSION}.${SHARED_MODULE_MINOR_VERSION}.${SHARED_MODULE_PATCH_VERSION})


# Common variables and definitions
#=============================================================================

set(MODULE_NAME "aldos-shared-module" CACHE STRING "CMake module name")

set(CENTRALIZED_RESOURCES_LIBRARY_NAME "centralized" CACHE STRING "linker name of the shared library")

set(CENTRALIZED_SHARE_DIR_NAME "centralized-resources")
set(CENTRALIZED_SHARE_DIR "${CMAKE_INSTALL_FULL_DATAROOTDIR}/${CENTRALIZED_SHARE_DIR_NAME}")

set(CENTRALIZED_TRANSLATIONS_DIR "${CENTRALIZED_SHARE_DIR}/translations")
set(CENTRALIZED_RELATIVE_TRANSLATIONS_DIR "${CENTRALIZED_SHARE_DIR_NAME}/translations")

set(CENTRALIZED_GRAPHICS_DIR "${CENTRALIZED_SHARE_DIR}/graphics")


# Files
#=============================================================================

file(GLOB toInstallModules
    "${PROJECT_SOURCE_DIR}/cmake/modules/*.cmake"
)

file(GLOB toInstallModulesForTranslation
    "${PROJECT_SOURCE_DIR}/cmake/modules/translations/*.cmake"
    "${PROJECT_SOURCE_DIR}/cmake/modules/translations/*.pl"
    "${PROJECT_SOURCE_DIR}/cmake/modules/translations/*.cpp.in"
)


# Target
#=============================================================================

#-----------------------------------------------------------------------------
# Superbuild mode
#-----------------------------------------------------------------------------

set(MODULES_INSTALL_DIR "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/${MODULE_NAME}/cmake/modules")

file(COPY
    ${toInstallModules}
    DESTINATION "${MODULES_INSTALL_DIR}"
)

file(COPY
    ${toInstallModulesForTranslation}
    DESTINATION "${MODULES_INSTALL_DIR}/translations"
)

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/shared-module-config.cmake.in"
    "${CMAKE_BINARY_DIR}/${MODULE_NAME}-config.cmake"
    INSTALL_DESTINATION "NOT-IMPORTANT"    # it will not be installed but generated using absolute dirs in PATH_VARS, so relative directories does not need to be calculated.
    PATH_VARS
        MODULES_INSTALL_DIR
)

# The package version file is common to superbuild and installable mode
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/shared-module-config-version.cmake.in"
    "${CMAKE_BINARY_DIR}/${MODULE_NAME}-config-version.cmake"
    @ONLY
)

configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/SmConfigVars.cmake.in"
    "${MODULES_INSTALL_DIR}/SmConfigVars.cmake"
    @ONLY
)

#-----------------------------------------------------------------------------
# Installable mode
#-----------------------------------------------------------------------------

set(CMAKECONFIG_INSTALL_DIR "${CMAKE_INSTALL_DATAROOTDIR}/cmake/${MODULE_NAME}/")
set(MODULES_INSTALL_DIR "${CMAKE_INSTALL_DATAROOTDIR}/cmake/${MODULE_NAME}/modules/")

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/shared-module-config.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/install/${MODULE_NAME}-config.cmake"
    INSTALL_DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
    PATH_VARS
        MODULES_INSTALL_DIR
)

configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/SmConfigVars.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/install/SmConfigVars.cmake"
    @ONLY
)

install(
    FILES
        "${CMAKE_CURRENT_BINARY_DIR}/install/${MODULE_NAME}-config.cmake"
        "${CMAKE_BINARY_DIR}/${MODULE_NAME}-config-version.cmake"
    DESTINATION
        "${CMAKECONFIG_INSTALL_DIR}"
)

install(
    FILES
        ${toInstallModules}
        "${CMAKE_CURRENT_BINARY_DIR}/install/SmConfigVars.cmake"
    DESTINATION
        "${MODULES_INSTALL_DIR}"
)

install(
    FILES
        ${toInstallModulesForTranslation}
    DESTINATION
        "${MODULES_INSTALL_DIR}/translations"
)
