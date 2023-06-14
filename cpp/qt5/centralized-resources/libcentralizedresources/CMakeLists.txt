cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)

project(libcentralizedresources)


# Cpp, packages and modules
#=============================================================================

# Minimum Versions
set(QT_MINIMUM_VERSION "5.12.0")
set(SHAREDMODULE_MINIMUM_VERSION "0.1.0")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

find_package(Qt5
    ${QT_MINIMUM_VERSION}
    CONFIG
    REQUIRED Widgets LinguistTools
)
message(STATUS "Building project '${PROJECT_NAME}' with Qt ${Qt5Core_VERSION}")

find_package(aldos-shared-module ${SHAREDMODULE_MINIMUM_VERSION} REQUIRED)
include(SmPreventInSourceBuilds)
include(SmCompilerSettings NO_POLICY_SCOPE)
include(translations/SmTranslateTs)
include(SmCreatePkgConfigFile)
include(SmCreatePortableHeaders)
include(SmConfigVars)


# Options
#=============================================================================

option(UPDATE_TRANSLATIONS "Update source translation translations/*.ts files" OFF)

message(STATUS "Update source translation translations/*.ts files: " ${UPDATE_TRANSLATIONS})


# Library version
#=============================================================================

# Major version, In sync with all client-apps/components
set(LIBCENTRALIZEDRESOURCES_MAJOR_VERSION 0)
# Minor version, belong to all components
set(LIBCENTRALIZEDRESOURCES_MINOR_VERSION 1)
#
# In a perfect world all components would have the same major- and minor- and
# patch-version as libcentralizedresources - in real life it will be fine if every component
# has it's own patch version within a major/minor life cyle.
#
set(LIBCENTRALIZEDRESOURCES_PATCH_VERSION 0)
#
set(LIBCENTRALIZEDRESOURCES_VERSION ${LIBCENTRALIZEDRESOURCES_MAJOR_VERSION}.${LIBCENTRALIZEDRESOURCES_MINOR_VERSION}.${LIBCENTRALIZEDRESOURCES_PATCH_VERSION})

message(STATUS "")
message(STATUS "libcentralizedresources version: ${LIBCENTRALIZEDRESOURCES_VERSION}")
message(STATUS "")


# Common variables and definitions
#=============================================================================

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(QT_LIBRARIES
    Qt5::Widgets
)

set(LIBCENTRALIZEDRESOURCES_NAME "lib${CENTRALIZED_RESOURCES_LIBRARY_NAME}" CACHE STRING "real library name without extension")
set(LIBCENTRALIZEDRESOURCES_DIR_NAME "${LIBCENTRALIZEDRESOURCES_NAME}" CACHE STRING "library dir name")

# path of generated include files
set(LIBCENTRALIZEDRESOURCES_INTREE_INCLUDE_DIR "${CMAKE_CURRENT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/include")
# path of installation of include files (<PREFIX>/include/<LIBNAME>)
set(LIBCENTRALIZEDRESOURCES_INSTALL_INCLUDE_DIR "${CMAKE_INSTALL_FULL_INCLUDEDIR}/${CENTRALIZED_RESOURCES_LIBRARY_NAME}")

# path of installation of cmake files (<PREFIX>/share/cmake/<LIBNAME>)
set(LIBCENTRALIZEDRESOURCES_INSTALL_CMAKE_DIR "${CMAKE_INSTALL_FULL_DATAROOTDIR}/cmake/${CENTRALIZED_RESOURCES_LIBRARY_NAME}")


# Files
#=============================================================================

set(libcentralizedresources_SRCS
    libtranslator.cpp
    selftranslationloader.cpp
)

set(libcentralizedresources_PUB_HDRS
    libglobals.h
    libtranslator.h
)

set(libcentralizedresources_LIBRARIES
    ${QT_LIBRARIES}
)


# Translations
#=============================================================================

translate_ts(libcentralizedresources_QM_FILES
    UPDATE_TRANSLATIONS
        ${UPDATE_TRANSLATIONS}
    SOURCES
        ${libcentralizedresources_SRCS}
    INSTALL_DIR
        "${CENTRALIZED_TRANSLATIONS_DIR}/${LIBCENTRALIZEDRESOURCES_DIR_NAME}"
    TEMPLATE
        "${LIBCENTRALIZEDRESOURCES_NAME}"
)


# Public headers
#=============================================================================

set(PORTABLE_HDR_NAMES
    Globals
    Translator
)

# Copy public headers
foreach(h ${libcentralizedresources_PUB_HDRS})
    get_filename_component(public_header_filename ${h} NAME)
    configure_file(${h} "${LIBCENTRALIZEDRESOURCES_INTREE_INCLUDE_DIR}/CentRes/${public_header_filename}" COPYONLY)
endforeach()

# Create the portable headers
sm_create_portable_headers(INTREE_PORTABLE_HEADERS
    NAME_PREFIX "lib"
    OUTPUT_DIR "${LIBCENTRALIZEDRESOURCES_INTREE_INCLUDE_DIR}/CentRes"
    HEADER_NAMES ${PORTABLE_HDR_NAMES}
)

install(FILES
    ${libcentralizedresources_PUB_HDRS}
    DESTINATION "${LIBCENTRALIZEDRESOURCES_INSTALL_INCLUDE_DIR}/CentRes"
    COMPONENT Devel
)

install(FILES
    ${INTREE_PORTABLE_HEADERS}
    DESTINATION "${LIBCENTRALIZEDRESOURCES_INSTALL_INCLUDE_DIR}/CentRes"
    COMPONENT Devel
)


# Target
#=============================================================================

add_library(${CENTRALIZED_RESOURCES_LIBRARY_NAME}
    SHARED ${libcentralizedresources_PUB_HDRS}
           ${libcentralizedresources_SRCS}
           ${libcentralizedresources_QM_FILES}
)

target_link_libraries(${CENTRALIZED_RESOURCES_LIBRARY_NAME}
    PUBLIC
        ${libcentralizedresources_LIBRARIES}
)

set_target_properties(${CENTRALIZED_RESOURCES_LIBRARY_NAME} PROPERTIES
    VERSION   ${LIBCENTRALIZEDRESOURCES_VERSION}
    SOVERSION ${LIBCENTRALIZEDRESOURCES_MAJOR_VERSION}
)

target_compile_definitions(${CENTRALIZED_RESOURCES_LIBRARY_NAME}
    PRIVATE
        "LIBCENTRALIZEDRESOURCES_DIR_NAME=\"${LIBCENTRALIZEDRESOURCES_DIR_NAME}\""
        #"CENTRALIZED_TRANSLATIONS_DIR=\"${CENTRALIZED_TRANSLATIONS_DIR}\""
        #"CENTRALIZED_RELATIVE_TRANSLATIONS_DIR=\"${CENTRALIZED_RELATIVE_TRANSLATIONS_DIR}\""
        "COMPILE_LIB"
        "$<$<CONFIG:Release>:QT_NO_DEBUG_OUTPUT>"
        "$<$<CONFIG:Release>:QT_NO_WARNING_OUTPUT>"
        "QT_NO_KEYWORDS"
)

target_include_directories(${CENTRALIZED_RESOURCES_LIBRARY_NAME}
    INTERFACE
        "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/${CENTRALIZED_RESOURCES_LIBRARY_NAME}>"
        "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/${CENTRALIZED_RESOURCES_LIBRARY_NAME}/CentRes>"
        "$<BUILD_INTERFACE:${LIBCENTRALIZEDRESOURCES_INTREE_INCLUDE_DIR}>"
        "$<BUILD_INTERFACE:${LIBCENTRALIZEDRESOURCES_INTREE_INCLUDE_DIR}/CentRes>"
)

install(TARGETS
    ${CENTRALIZED_RESOURCES_LIBRARY_NAME}
    DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    EXPORT ${CENTRALIZED_RESOURCES_LIBRARY_NAME}-targets
    LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    COMPONENT Runtime
)


# Cmake config files
#=============================================================================

# Create in-tree build infrastructure
configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/template-config.cmake.in"
    "${CMAKE_BINARY_DIR}/${CENTRALIZED_RESOURCES_LIBRARY_NAME}-config.cmake"
    INSTALL_DESTINATION "neverland"     # required, altough we don't install it
)


# Create installable build infrastructure
configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/template-config.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/install/${CENTRALIZED_RESOURCES_LIBRARY_NAME}-config.cmake"
    INSTALL_DESTINATION "${LIBCENTRALIZEDRESOURCES_INSTALL_CMAKE_DIR}"
)

write_basic_package_version_file(
    "${CMAKE_BINARY_DIR}/${CENTRALIZED_RESOURCES_LIBRARY_NAME}-config-version.cmake"
    VERSION ${LIBCENTRALIZEDRESOURCES_VERSION}
    COMPATIBILITY AnyNewerVersion
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/install/${CENTRALIZED_RESOURCES_LIBRARY_NAME}-config.cmake"
    "${CMAKE_BINARY_DIR}/${CENTRALIZED_RESOURCES_LIBRARY_NAME}-config-version.cmake"
    DESTINATION "${LIBCENTRALIZEDRESOURCES_INSTALL_CMAKE_DIR}"
    COMPONENT Devel
)

install(EXPORT
    ${CENTRALIZED_RESOURCES_LIBRARY_NAME}-targets
    DESTINATION "${LIBCENTRALIZEDRESOURCES_INSTALL_CMAKE_DIR}"
    COMPONENT Devel
)


# Create and install pkgconfig (.pc) file
#=============================================================================

sm_create_pkgconfig_file(
    PACKAGE_NAME ${CENTRALIZED_RESOURCES_LIBRARY_NAME}
    DESCRIPTIVE_NAME ${CENTRALIZED_RESOURCES_LIBRARY_NAME}
    DESCRIPTION "Example shared library"
    INCLUDEDIRS ${CENTRALIZED_RESOURCES_LIBRARY_NAME}
    LIBS ${CENTRALIZED_RESOURCES_LIBRARY_NAME}
    REQUIRES "Qt5Widgets >= ${QT_MINIMUM_VERSION}, Qt5Xml >= ${QT_MINIMUM_VERSION}"
    VERSION ${LIBCENTRALIZEDRESOURCES_VERSION}
    INSTALL
)
